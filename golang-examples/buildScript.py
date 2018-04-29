#!/usr/bin/python

import time
import subprocess
import glob, os
import sys

if len(sys.argv) != 2:
    print 'usage: ./buildScript.py build / clean'
    exit(0)

dirs =   ["net",
          "net/tcpclient_server",
          "os",
          "intro",
          "time",
          "basic",
          "crypto",
          "io",
          "io/bufio",
          "apps",
          "math",
          "encoding",
          "logging"
         ]

class BuildData:
    name = ""
    directory = ""
    cmd = ""

dirlist = []

start = time.gmtime()

for dirname in dirs:
    buildinfo = BuildData()
    buildinfo.directory = dirname
    count = dirname.count("/")
    buildinfo.cmd = "../"
    while 1:
        count = count - 1
        if count < 0:
            break
        buildinfo.cmd = buildinfo.cmd + "../"

    dirlist.append(buildinfo)

cmd_name="go build "
clean="go clean "

if sys.argv[1] == 'build':
    for direntry in dirlist:
        os.chdir(direntry.directory)
        print "Entering %s" % direntry.directory
        for file in glob.glob("*.go"):
            cmd = cmd_name + file
            val = os.system(cmd)
            if val != 0:
                print ("failed to compile " + file)
                exit(1)
            print "  .. %s" % file
        os.chdir(direntry.cmd)
    stop = time.gmtime()
    file = open("stats", "w")
    took = ((stop.tm_min * 60) + stop.tm_sec) - ((start.tm_min * 60) + start.tm_sec)
    file.write(str(took))
    file.close()
elif sys.argv[1] == 'clean':
    print "Cleaning"
    for direntry in dirlist:
        print "  ..%s" % direntry.directory
        os.chdir(direntry.directory)
        val = os.system(clean)
        if val != 0:
            print ("failed to clean " + direntry.directory)
            exit(1)
        os.chdir(direntry.cmd)
    stop = time.gmtime()
    file = open("stats", "w")
    took = ((stop.tm_min * 60) + stop.tm_sec) - ((start.tm_min * 60) + start.tm_sec)
    file.write(str(took))
    file.close()

if sys.argv[1] == 'stats':
    file = open("stats")
    stats = file.read()
    print ("build took " + stats + " seconds")
    file.close()
