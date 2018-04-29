package main

import "bufio"
import "fmt"
import "os"

func main() {
    // get new scanner object from an fd
    scanner := bufio.NewScanner(os.Stdin)

    // read until you get an error
	for scanner.Scan() { // read input
	    fmt.Println(scanner.Text())
	}
	if err := scanner.Err(); err != nil {
	   fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}
}
