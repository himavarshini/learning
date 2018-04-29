package main

import "fmt"
import "net"

func main() {
    conn, er := net.Dial("tcp", "www.google.com:80")
    if er != nil {
        fmt.Println("cannot connect to the website")
    } else {
        fmt.Println("connected ", conn)
    }
}

