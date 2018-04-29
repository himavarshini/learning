package main

import "os"
import "github.com/Sirupsen/logrus"

var log = logrus.New()

func main() {
    log.Out = os.Stderr

	log.WithFields(logrus.Fields{
	    "level": "warn",
	}).Warn("Warn level")
}

