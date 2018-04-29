package main

import "fmt"
import "os"

func main() {
    if len(os.Args) != 2 {
	    fmt.Printf("./exist <file>\n")
		return
	}

	st_buf, er := os.Stat(os.Args[1])
	if er != nil {
	    fmt.Printf("%s does not exist\n", os.Args[1])
		return
	}

	if st_buf.IsDir() {
	    fmt.Printf("%s is a directory\n", os.Args[1])
	}

    if st_buf.Mode().IsRegular() {
	    fmt.Printf("%s is a file\n", os.Args[1])
	}

}

