package main

import "log"
import "os"

func main() {
    log := log.New(os.Stderr, "Fatal: ", log.Ldate | log.Ltime)

	log.Fatal("This fatal logging.. ")

	log.Print("This message will never get printed..")
}

