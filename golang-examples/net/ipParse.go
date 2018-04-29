package main

import "net"
import "os"
import "fmt"

func main() {
    if len(os.Args) != 2 {
	    fmt.Fprintf(os.Stderr, "usage : %s ip-addr\n", os.Args[0])
		os.Exit(1)
	}

	name := os.Args[1]

	addr := net.ParseIP(name)
	if addr == nil {
		fmt.Fprintln(os.Stderr, "invalid ip")
	} else {
		fmt.Println("the address is ", addr.String())
	}
}

