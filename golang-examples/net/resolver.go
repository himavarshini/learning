package main

import "net"
import "os"
import "fmt"

func main() {
    if len(os.Args) != 2 {
	    fmt.Println("usage: ./resolver url")
        return
	}

	name := os.Args[1]


	addr, er := net.ResolveIPAddr("ip", name)
	if er != nil {
	    fmt.Println("resolver error\n")
	} else {
	    fmt.Println("%s",  addr.String())
	}
}

