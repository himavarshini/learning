package main

import "net"
import "os"
import "fmt"

func main() {
    if len(os.Args) != 2 {
	    fmt.Printf("usage: %s url\n", os.Args[0])
		return;
	}

	name := os.Args[1]

	addr, er := net.LookupHost(name)
	if er != nil {
	    fmt.Println("error", er. Error())
		return
	}

	for _, s := range addr {
	    fmt.Println(s)
	}

}

