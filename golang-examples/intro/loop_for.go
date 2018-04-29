package main

import "fmt"

func main() {
    loop := 1

    for loop > 0 {
        fmt.Printf("How many?\n")
        fmt.Scanf("%d", &loop)

        for i := 0; i < loop; i++ {
            fmt.Printf("%d ", i)
        }
        fmt.Println()
    }
}
