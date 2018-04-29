package main

import "os"
import "fmt"

func main() {
    argslen := len(os.Args)

	for i:=0; i < argslen; i++ {
	    fmt.Printf("Arg[%d] : %s\n", i + 1, os.Args[i]);
	}
}

