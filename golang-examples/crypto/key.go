package main

import "crypto/rand"

func main() {
    key := make([]byte, 32)

    _, err := rand.Read(key)
    if err != nil {
        panic(err)
    }
}

