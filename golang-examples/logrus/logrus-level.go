package main

import log "github.com/Sirupsen/logrus"

func main() {
    log.WithFields(log.Fields{
	    "level":"info",
	}).Info("This is info level..")

	log.WithFields(log.Fields{
	    "level":"warn",
	}).Warn("This is warn level..")

	log.WithFields(log.Fields{
	    "levels":"Fatal",
	}).Fatal("This is fatal level..")
}

