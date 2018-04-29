package main
import "fmt"

func main() {
    const red = 1 << iota
    const green = 1 << iota
    const blue = 1 << iota
/*
    const (
        Apple = iota
        Banana
        Orange
    )
    */
    fmt.Printf("red %d green %d blue %d\n", red, green, blue)
    //fmt.Printf("Apple %d Banana %d Orange %d\n", Apple, Banana, Orange)
}
