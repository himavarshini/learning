package main

import "fmt"
import "net"
import "os"

func main() {
    conn, er := net.Dial("tcp", "127.0.0.1:8189")
    if er != nil {
        fmt.Println(er)
        os.Exit(1)
    }

    fmt.Println(conn)
}

