package main

import "os"
import "fmt"

func args_checker(needed_args int) int {
    var ret int

    ret = 0
    if len(os.Args) - 1 != needed_args {
	    fmt.Println("invalid number of arguments")
		ret = -1
	}

	return ret
}

