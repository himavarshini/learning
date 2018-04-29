package main

import "fmt"

func main() {
    // if else statements does not need to have braces
    if 7 % 2 == 0 {
        fmt.Println("even")
    } else {
        fmt.Println("odd")
    }

    if 8 % 4 == 0 {
        fmt.Println("even")
    } else {
        fmt.Println("odd")
    }

    // the if condition executes from left to right
    // as since the variable n can only be available
    // unless it is declared
    if n:=9; n < 0 {
        fmt.Println(n, "is -ve")
    } else if n < 10 {
        fmt.Println(n, "is less than 10")
    } else {
        fmt.Println(n, "has multiple digits")
    }
}
