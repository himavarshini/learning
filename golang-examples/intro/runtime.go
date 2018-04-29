package main

import "fmt"
import "runtime"

// this function gets called automatically
func init() {
    if runtime.GOOS == "linux" {
	    fmt.Println("linux")
	} else {
	    fmt.Println(runtime.GOOS)
	}
}

func main() {
}
