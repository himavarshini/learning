#!/usr/bin/python

import sys

fd = open(sys.argv[1])
for line in fd:
    print line,
fd.close()
