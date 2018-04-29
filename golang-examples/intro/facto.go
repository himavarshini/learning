package main

import "fmt"

func fact(number int) (int) {
    value := 1
    for i:=1; i <= number; i++ {
        value *= i;
    }
    
    return value
}

func main() {
    fmt.Println("factorial of 5 is ", fact(5))
}
