package main

import "fmt"

func main() {
    var a[5] int
    fmt.Println("emp:", a)

    // like in C and Python the first index
    // of the array starts from 0
    a [4] = 100
    fmt.Println("set:", a)
    fmt.Println("get:", a[4])

    // keyword : len() more of a sizeof() in C
    fmt.Println("len:", len(a))

    b := [5] int {1, 2, 3, 4, 5}
    fmt.Println("dcl:", b)

    var twoD [2] [3] int

    // the variables i and j are only the
    // for variable scope and they are not
    // function scope
    for i := 0; i < 2; i++ {
        for j := 0; j < 3; j++ {
            twoD[i][j] = i + j
        }
    }

    // Println provides a way to print
    // 2-D arrays in a pretty way
    fmt.Println("2d: ", twoD)

    // for the sake of comparing it
    // with C here is the other way to
    // print
    for i := 0; i < 2; i++ {
        for j := 0; j < 3; j++ {
            fmt.Println("elem:", twoD[i][j])
        }
    }

    fmt.Println("size of array dimension =" , len(twoD), len(twoD[0]))
}
