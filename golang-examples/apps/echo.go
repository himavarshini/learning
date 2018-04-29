package main

import "fmt"
import "os"

func main() {
    
    if len(os.Args) == 1 {
        fmt.Printf("\n")
    } else {
        for line := 1; line < len(os.Args); line++ {
            fmt.Printf("%s\n", os.Args[line])
        }
    }
}
