package main

import "fmt"

func main() {

    // explicit const for every variable
    const (
	a = iota
	b = iota
    )

    // implicit const for every variable
    const (
	a1 = iota
	b1
    )

    fmt.Println(a, b);
    fmt.Println(a1, b1);
}
