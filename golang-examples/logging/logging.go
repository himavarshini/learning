package main

import "bytes"
import "fmt"
import "log"

func main() {
    var buf bytes.Buffer

	logger := log.New(&buf, "logger: ", log.Lshortfile)
	logger.Print("Hello ")


	fmt.Print(&buf)
}

