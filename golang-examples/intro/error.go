package main

import "fmt"
import "errors"

func main() {
    err := errors.New("error ..")
    if err != nil {
        fmt.Println(err)
    }
}

