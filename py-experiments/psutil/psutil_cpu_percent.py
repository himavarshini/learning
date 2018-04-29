#!/usr/bin/python

import psutil

for x in range(3):
    print psutil.cpu_percent(interval=1)
