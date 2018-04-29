package main

import "fmt"

func main() {
    // initialisation
    i := 1
    // default or normal way of declaring a variable
    var j int

    for i <= 3 {
        fmt.Println(i)
        i = i + 1
    }

    for j = 1; j <= 3; j++ {
        fmt.Println("J = ", j);
    }
}
