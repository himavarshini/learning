package main

import "net"
import "fmt"

func main() {
    c, er := net.Dial("unix", "unix.sock")
	if er != nil {
	    fmt.Println("connect error")
		return
	}

	fmt.Println("connected", c)
}

