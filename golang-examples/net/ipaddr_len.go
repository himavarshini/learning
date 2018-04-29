package main

import "fmt"
import "net"

func main() {
    fmt.Printf("ipv4 len :%d ipv6 len :%d\n", net.IPv4len, net.IPv6len)
    // the net package provides the common functions and there are 
    // sub packages that define specific app
}

