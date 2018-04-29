#!/usr/bin/python

import os
import sys

if len(sys.argv) == 1:
    print "./template <filename> <package name> <imports>"
    exit(0)

filename=sys.argv[1]
packagename=sys.argv[2]

file = open(filename, 'w')

file.write("package " + "main\n\n")
for argv in sys.argv[3:]:
    final_string="import "
    argv = "\"%s\"" % argv
    file.write("import " + argv + "\n")

file.write("\n")
file.write("func main() {" + "\n" + "}")
file.close()
