package main

import "fmt"
import "log"
import "net"

func main() {
	ln, er := net.Listen("tcp", ":8189")
	if er != nil {
	    fmt.Println("cannot create tcp connection")
		return
	}

	log.Println("listen")

	for {
	    conn, er := ln.Accept()
		if er != nil {
		    fmt.Println("cannot add conn")
			return
		}

		log.Print("new conn", conn)
	}
}

