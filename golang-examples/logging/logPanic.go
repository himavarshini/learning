package main

import "log"
import "os"

func main() {
    log := log.New(os.Stderr, "Panic: ", log.Ldate | log.Ltime)

	log.Panic("panic!")

	log.Print("This message will not come ..")
}

