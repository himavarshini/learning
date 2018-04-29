package main

import "fmt"
import "os"

func main() {
    if len(os.Args) != 2 {
	    fmt.Printf("createDir <directory>\n")
		return
	}

	er := os.Mkdir(os.Args[1], 0755)
	if er != nil {
	    fmt.Printf("failed to create directory %s\n", os.Args[1])
		return
	}
}
