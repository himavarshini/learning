package main

import "os"
import "fmt"

func main() {
    if len(os.Args) != 1 {
	    fmt.Println("./hostname")
		return
	}

	fmt.Println(os.Hostname())
}

