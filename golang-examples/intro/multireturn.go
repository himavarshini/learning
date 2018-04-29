package main

import "fmt"

// both a and b are integers and the function returns two integers
// return the smallest one first
func func1(a, b int) (int, int) {
    if a > b {
        return b, a
    }
    
    return a, b
}

func main() {
    val1, val2 := func1(3, 2)
    
    fmt.Println("val1 and val2 ", val1, val2)
}
