package main

import "os"
import "fmt"

func main() {
    if len(os.Args) != 3 {
	    fmt.Println("./symlink <file> <newlink>")
		return
	}

	er := os.Symlink(os.Args[1], os.Args[2])
	if er != nil {
	    fmt.Println("cannot create link")
		return
	}
}
