#!/usr/bin/python

### only has seconds resolution
import time
import os

class Profile:
    def profile_start(self):
        self.start = time.gmtime()
    def profile_stop(self):
        self.stop = time.gmtime()
    def profile_display(self):
        secs_elapsed = ((self.stop.tm_hour * 60 * 60) + (self.stop.tm_min * 60) + (self.stop.tm_sec)) - ((self.start.tm_hour * 60 * 60) + (self.start.tm_min * 60) + (self.start.tm_sec))
        print "executed for " + str(secs_elapsed) + " seconds"

prof = Profile()
prof.profile_start()
time.sleep(66)
prof.profile_stop()
prof.profile_display()
