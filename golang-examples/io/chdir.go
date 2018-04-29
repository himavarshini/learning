package main

import "os"
import "fmt"

func main() {
    if len(os.Args) != 2 {
	    fmt.Println("./chdir <directory>")
		return
	}

	er := os.Chdir(os.Args[1])
	if er != nil {
	    fmt.Printf("changing to %s directory failed\n", os.Args[1])
		return
	}

	dir, er := os.Getwd()
	if er != nil {
	    fmt.Printf("cannot figure current directory\n")
		return
	}

	fmt.Println("the current directory is ", dir)
}
