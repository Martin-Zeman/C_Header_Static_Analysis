#!/usr/bin/python

import os
import subprocess
import csv
import re

print("Testing header struct parsing...\n")

files = [f for f in os.listdir('.') if os.path.isfile(f)]
for i in files:
    if i.endswith(".h"):
        print("Testing header file:", i)
        header_number = re.findall('\d+', i )[0]

        alignment_set = (2, 4, 8)

        for align in alignment_set:

            #call the script with an alignment argument of 2
            subprocess.call("python ../parse_c_header.py " + i + " " + str(align), shell=True)

            print("\tOption alignment = "+str(align)+":")

            #construct the name of the csv file to be checked
            target_csv_name = "test_csv_align_"+str(align)+"_"+header_number+".csv"
            with open("output_csv.csv", newline='') as current_csv:
                with open(target_csv_name, newline='') as target_csv:
                    cr = csv.reader(current_csv, delimiter=';',quotechar='|', quoting=csv.QUOTE_MINIMAL)
                    tr = csv.reader(target_csv, delimiter=';', quotechar='|', quoting=csv.QUOTE_MINIMAL)
                    rows1 = [row for row in cr]
                    rows2 = [row for row in tr]
                    if (rows1 == rows2):
                        print("\tTEST OK!")
                    else:
                        print("\tTEST FAILED!")
                        print("\t\tGenerated output:",rows1)
                        print("\t\tExpected output:",rows2)

