#!/usr/bin/python

import os
import sys
import time
import subprocess

gitcmd='git log | grep commit | head -1 | cut -d " " -f 2'
oldsha1 = sha1 = subprocess.check_output(gitcmd, shell=True)

while True:
    sha1=subprocess.check_output(gitcmd, shell=True)
    if oldsha1 != sha1:
        print "new commit.."
        oldsha1 = sha1

    time.sleep(1)
