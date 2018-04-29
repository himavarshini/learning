package main

import "os"

import "fmt"

func main() {
    var length int

	length = len(os.Args)
	fmt.Println("length of args ", length);
}

