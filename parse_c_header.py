#!/usr/bin/python
"""
Dummy module docstring
"""

import sys
import csv
import collections

import pyparsing  # Pyparsing v2.1.4 needs to be installed

class HeaderParser(object):
    """A parser class that takes the text of a C header file as an input and outputs the sizes of
    all structs found to a defined csv file.

    Arguments:
        input_text -- text of a header file to be parsed
        csv_file -- A name of the csv file to output the results to. It will be overwritten if it
        already exists.
        alignment -- defines the number of bytes to which the structs are aligned to (default is 4)
    """

    # The context free grammar of a simplified C struct
    __struct_cfg = None

    #size of basic variables
    var_sizes = {'char': 1, 'int': 4, 'double': 8}

    # these are constants representing sizes of different types of lists
    (DECL_W_DEF, DECL_W_DEF_ARR, DECL, DECL_ARR) = (4, 7, 3, 4)

    def __init__(self, input_text, alignment=2):
        self.__input_text = input_text
        self.__alignment = alignment
        self.__struct_sizes = collections.OrderedDict()  # Keeps the order deterministic
        self.__parsed_list = None

        # Defining the context free grammar
        # Capital letters seem to be the standard when using pyparsing
        STRUCT_DEC = pyparsing.Forward()  # Forward declaration of the struct declaration
        INTEGER = pyparsing.Word(pyparsing.nums)
        IDENTIFIER = pyparsing.Word(pyparsing.alphas + '_',
                                    pyparsing.alphas + pyparsing.nums + '_$')
        LBRACE = pyparsing.Literal('{').suppress()
        RBRACE = pyparsing.Literal('}').suppress()
        SEMICOLON = pyparsing.Literal(';').suppress()
        TYPENAME_NAME = IDENTIFIER
        VARIABLE_NAME = IDENTIFIER

        # Other types are not allowed here, neither is unsigned or pointers...
        BASIC_TYPES = pyparsing.oneOf('char int double')

        # Variable name with the possibility of declaring arrays
        VAR_NAME_ARR = (VARIABLE_NAME + pyparsing.Optional('[' + INTEGER + ']'))

        # Member of a struct declaration (can be another struct)
        MEMBER_DEC = pyparsing.Group(
            (BASIC_TYPES | (pyparsing.Word('struct') + IDENTIFIER) | TYPENAME_NAME) +
            pyparsing.Group(pyparsing.delimitedList(VAR_NAME_ARR)) + SEMICOLON) | STRUCT_DEC

        # Struct declaration (unions are not allowed). Forward declared object needs to be assigned
        # with '<<'
        STRUCT_DEC << pyparsing.Group(
            pyparsing.Word('struct') +
            IDENTIFIER +
            pyparsing.Group(LBRACE + pyparsing.ZeroOrMore(MEMBER_DEC) + RBRACE) +
            pyparsing.Optional(VAR_NAME_ARR) + SEMICOLON)

        HeaderParser.__struct_cfg = pyparsing.ZeroOrMore(STRUCT_DEC)  # Get all of them

        # Ignoring comments
        HeaderParser.__struct_cfg.ignore(pyparsing.cStyleComment)  # C style comment
        HeaderParser.__struct_cfg.ignore(pyparsing.Literal('//') + pyparsing.restOfLine)

    def __process_member(self, align, member_info, tot_info, maximum):
        """Method for the calculation of the needed offset for a given struct member. It also
        adjusts offset, total size and total padding counters. The maximum variable size is updated
        if needed.

        Arguments:
            align -- size of the current member in bytes
            size -- size of the struct member (may differ from align in case of arrays/structs)
            offset -- current offset in the struct
            tot_size -- total size of the struct so far
            tot_padding -- total padding of the struct so far
            max -- size of the largest found variable in the struct so far
        """
        # Calculate padding
        align = self.__alignment if self.__alignment > align else align
        maximum = align if align > maximum else maximum
        padding = (align - (member_info['Offset'] % align)) % align

        # Adjust the global counters
        tot_info['Tot_padding'] += padding
        tot_info['Tot_size'] += member_info['Size'] + padding
        member_info['Offset'] += member_info['Size'] + padding

        return [member_info['Offset'], tot_info['Tot_size'], tot_info['Tot_padding'], maximum]

    def __process_struct(self, struct_content, max_):
        """A recursive method that is responsible for calculation the size and padding of a single
        struct. It also outputs the size of the largest member variable found.

        Arguments:
            struct_content -- A list format of the struct content
            max -- largest element found so far. This can be passed from a parent struct to a nested
                    struct
        """
        offset = 0
        size = 0
        padding = 0
        for member in struct_content:
            if member[0] == 'struct':  # Found a struct member variable
                if len(member) == HeaderParser.DECL:  # Just declaration, must be previously defined
                    try:
                        if member[1] in self.__struct_sizes:

                            s_size = self.__struct_sizes[member[1]][0]
                            s_padding = self.__struct_sizes[member[1]][1]
                            s_max = self.__struct_sizes[member[1]][2]

                            if len(member[2]) == HeaderParser.DECL_ARR:  # Takes care of arrays
                                array_length = int(member[2][2])
                                s_size *= array_length
                                s_padding *= array_length

                            # We already know the structs size so we just look at its alignment
                            # requirements
                            member_info = {'Size': s_size, 'Offset' : offset}
                            total_counter = {'Tot_size': 0, 'Tot_padding': 0}
                            ret = self.__process_member(s_max, member_info, total_counter, max_)

                            offset += s_size
                            size += s_size
                            # Nested struct's internal padding plus whole struct's padding
                            padding += s_padding + ret[2]
                            max_ = ret[3]  # Maximum may have been changed
                        else:
                            raise KeyError('Declaring an undefined struct! The header is '
                                           'syntactically invalid!')
                    except KeyError:  # Should not happen in a syntactically correct C header file
                        continue
                elif len(member) >= HeaderParser.DECL_W_DEF:  # Declaration with definition
                    # The max in ret[2] is now a local max of the nested struct
                    ret = self.__process_struct(member[2], 1)
                    try:
                        if member[1] in self.__struct_sizes:
                            raise KeyError('Struct with the same name is already in the '
                                           'dictionary!')
                        # Add it to the dictionary
                        self.__struct_sizes[member[1]] = (ret[0], ret[1], ret[2], False)
                    except KeyError:  # Should not happen in a syntactically correct C header file
                        continue

                    if len(member) == HeaderParser.DECL_W_DEF_ARR:  # This takes care of arrays
                        array_length = int(member[5])
                        ret[0] *= array_length  # Size
                        ret[1] *= array_length  # Padding

                    # Find out if the nested struct needs padding by considering its largest element
                    member_info = {'Size': ret[2], 'Offset': offset}
                    total_counter = {'Tot_size': 0, 'Tot_padding': 0}
                    ret2 = self.__process_member(ret[2], member_info, total_counter, max_)

                    # ret2[2] is the padding that the whole nested struct needs
                    # Size of the nested struct plus whole struct's padding
                    offset += ret[0] + ret2[2]
                    size += ret[0] + ret2[2]

                    # Nested struct's internal padding plus whole struct's padding
                    padding += ret[1] + ret2[2]
                    max_ = ret2[3] # Maximum may have been changed
                else:
                    raise ValueError('A struct with a undefined list length found!')

            else:  # Found a non-struct member variable
                if len(member[1]) == 4:  # An array
                    array_length = int(member[1][2])
                    memb_algn = HeaderParser.var_sizes[member[0]]
                    memb_size = memb_algn * array_length

                    member_info = {'Size': memb_size, 'Offset': offset}
                    total_counter = {'Tot_size': size, 'Tot_padding': padding}
                    ret = self.__process_member(memb_algn, member_info, total_counter, max_)

                    offset = ret[0]
                    size = ret[1]
                    padding = ret[2]
                    max_ = ret[3]

                else:  # A non-array variable
                    memb_algn = HeaderParser.var_sizes[member[0]]
                    member_info = {'Size': memb_algn, 'Offset': offset}
                    total_counter = {'Tot_size': size, 'Tot_padding': padding}
                    ret = self.__process_member(memb_algn, member_info, total_counter, max_)
                    offset = ret[0]
                    size = ret[1]
                    padding = ret[2]
                    max_ = ret[3]

        # The last member is padded with a number of bytes required so that the total size of the
        # structure should be a multiple of the largest alignment of any structure member
        final_padding = (max_ - (size % max_)) % max_
        size += final_padding
        padding += final_padding

        return [size, padding, max_]

    def extract_struct_sizes(self):
        """This function first parses __input_text as a header file. Afterwards it determines the
        sizes of all top-level structs. Lastly, it writes the results into a csv file.
        Padding is only inserted when a structure member is followed by a member with a larger
        alignment requirement or at the end of the structure.
        """

        # Parse the header file
        self.__parsed_list = HeaderParser.__struct_cfg.parseString(self.__input_text).asList()

        # Sync we're assuming a syntactically correct C header file I don't have to check the
        # correctness.
        # All the identifiers should be known if I simply search the top-level structs from top to
        # bottom
        self.__struct_sizes.clear()  # Clear dictionary before parsing TODO we'll see about this
        for item in self.__parsed_list:
            ret = self.__process_struct(item[2], 1)
            try:
                if item[1] in self.__struct_sizes:
                    raise KeyError('Struct with the same name is already in the dictionary!')
                self.__struct_sizes[item[1]] = (ret[0], ret[1], ret[2], True)  # Add it to the dict
            except KeyError:  # This should not happen in a syntactically correct C header file
                continue



    def output_to_csv(self, csv_file):
        """Output the internal variables filled with parsed data to a csv file.

        Arguments:
            csv_file -- a string specifying the name of the output csv file
        """
        with open(csv_file, 'w', newline='') as csv_file_:
            wr_ = csv.writer(csv_file_, delimiter=';', quotechar='|', quoting=csv.QUOTE_MINIMAL)
            wr_.writerow([('Struct name'), ('Size'), ('Padding')])
            for item, values in self.__struct_sizes.items():
                if values[3]:  # Filtering only top level structs
                    wr_.writerow([(item), (values[0]), (values[1])])

if len(sys.argv) != 3:
    print('Invalid number of arguments!')
    sys.exit()
else:
    try:
        ALIGNMENT_OPTIONS = int(sys.argv[2])
    except ValueError:
        print("The alignment option can't be converted to integer")
        sys.exit()
    if ALIGNMENT_OPTIONS != 2 and ALIGNMENT_OPTIONS != 4 and ALIGNMENT_OPTIONS != 8:
        print('The alignment has an invalid value. Only values 2, 4 and 8 are permitted!')
        sys.exit()
    with open(sys.argv[1], 'r') as header_file:
        HEADER_TEXT = header_file.read()
        HP = HeaderParser(HEADER_TEXT, ALIGNMENT_OPTIONS)
        HP.extract_struct_sizes()
        HP.output_to_csv('output_csv.csv')
