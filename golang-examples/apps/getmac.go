package main

import "fmt"
import "os"
import "net"

func main() {
    if len(os.Args) != 2 {
        fmt.Println("usage: ./getmac <interface name>")
    } else {
        ifdata, er := net.InterfaceByName(os.Args[1])
        if er != nil {
            fmt.Println("failed to get mac id from ", os.Args[1])
            os.Exit(1)
        }

        fmt.Println("mac id is ", ifdata.HardwareAddr)
    }
}

