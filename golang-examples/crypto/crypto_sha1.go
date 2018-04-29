package main

import "fmt"
import "crypto/sha1"

func main() {
    fmt.Println("blocksize bytes ", sha1.BlockSize)
    fmt.Println("Size of SHA1 checksum bytes ", sha1.Size)
    
    data := []byte("SHA1")
    fmt.Println(sha1.Sum(data))
}
