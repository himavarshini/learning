#!/usr/bin/python

import psutil

get_cpus=psutil.cpu_count(logical=False)
print "num cpus " + str(get_cpus)
