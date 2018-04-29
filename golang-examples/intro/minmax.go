package main

import "fmt"

func min_num(a, b int) int {
    if a < b {
        return a
    }
    
    return b
}

func max_num(a, b int) int {
    if a > b {
        return a
    }
    
    return b
}

func main() {
    fmt.Printf("min %d max %d\n", min_num(2, 1), max_num(2, 1))
}
