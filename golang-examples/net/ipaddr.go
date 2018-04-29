package main

import "os"
import "net"
import "log"

func main() {

    addr, err := net.InterfaceAddrs()
    if err != nil {
        log.Fatal(err)
    }

    for _, a:= range addr {
        if ipnet, ok := a.(*net.IPNet); ok {
            if ipnet.IP.To4() != nil {
                os.Stdout.WriteString(ipnet.IP.String() + "\n")
            }
        }
    }
}

