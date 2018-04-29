package main

import "md5sum"
import "fmt"
import "os"

func main() {
    if len(os.Args) != 2 {
        fmt.Println("usage: ./md5sum <filename>")
		return
	}

	fmt.Printf("md5sum: %x\n", md5sum.Md5sum(os.Args[1]))
}

