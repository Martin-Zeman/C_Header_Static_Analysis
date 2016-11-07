# C_Header_Static_Analysis
Given a C header file.
Find all the C struct, the size of each struct and the size of padding. All sizes need to be in bytes.

Input: 
1)some_header_file.h 
2)memory alignment option (2,4,8 bytes) 
Output: 
a CSV file with name of struct , size of struct, size of padding bytes.


Please write a python module which can do the above calculation.
Please also write test code.

Note:
The basic data types in C header file are 

char of size 1 byte. 
int of size 4 byte. 
double of size 8 byte.
Arrays of above types
Structs of above types.

Example of a header file 

/* header file start */
struct A1
{
    char m1[3];
    double m2;
    char m3;
};

struct A2
{
    char m1;
    double m2;
    char m3;
};

struct A3
{
    A1 S1;
    A2 S2;
}
/* header file End */

