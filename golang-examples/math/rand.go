package main

import "fmt"
import "math/rand"
import "time"

func main() {
    rand.Seed((int64)(time.Now().UnixNano()))
    fmt.Println("number is ", rand.Intn(100))
}
