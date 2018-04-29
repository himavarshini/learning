package main

import (
    "fmt"
    "encoding/hex"
    "os"
)

func main() {
    if len(os.Args) != 2 {
        fmt.Println("invalid number of arguments\n")
        return
    }

    hex, err := hex.DecodeString(os.Args[1])
    if err != nil {
        panic(err)
    }

    fmt.Println(hex)
}

