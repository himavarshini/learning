package main

import "fmt"
import "net"
import "os"
import "strconv"

func main() {

    if len(os.Args) != 2 {
        fmt.Println("usage : ./getifbyindex <ifindex>")
        return
    }

    ifindex, _ := strconv.Atoi(os.Args[1])

    Iface, er := net.InterfaceByIndex(ifindex)
    if er != nil {
        fmt.Println("failed to get ifname")
    } else {
        fmt.Println("inteface: ", Iface.Name)
    }
}

