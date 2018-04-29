package main

import "net"
import "fmt"

func main() {
    l, er := net.Listen("unix", "unix.sock")
	if er != nil {
	    fmt.Println("listener error")
		return
	}

	for {
	    fd, er := l.Accept()
		if er != nil {
		    fmt.Println("accept error")
			return
		}
		fmt.Println("client connected", fd)
	}
}

