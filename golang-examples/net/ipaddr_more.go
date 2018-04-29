package main

import "fmt"
import "net"
import "log"

func main() {

    addr, err := net.InterfaceAddrs()
    if err != nil {
        log.Fatal(err)
    }

    for _, a:= range addr {
        fmt.Println("network address: ", a)
    }
}

