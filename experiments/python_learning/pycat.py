#!/usr/bin/python
import sys

# A basic 'cat' command in linux written in py

def readfile(filename):
	f = open(filename)

	for line in f:
		print(line),

if len(sys.argv) != 2:
	print("./pycat filename\n"),
else:
	readfile(sys.argv[1])
