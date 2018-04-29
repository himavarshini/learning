package main

import "log"
import "os"

func main() {
    info_logging := log.New(os.Stdout, "Info: ", log.Ldate | log.Ltime | log.Lshortfile)

	info_logging.Print("Hello")
}

