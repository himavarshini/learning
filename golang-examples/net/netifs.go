package main

import "fmt"
import "net"

func main() {
    ifs, er := net.Interfaces()
    if er != nil {
        fmt.Println("failed to get network interface\n")
    } else {
        // list of 'type interface struct'
        for _, ifn := range ifs {
            fmt.Println(ifn.Index, ifn.MTU, ifn.Name, ifn.HardwareAddr, ifn.Flags)
        }
    }
}

