package main

import "even"
import "fmt"

func main() {
	i := 5
	fmt.Printf("Is %d even ? %v \n", i, even.Even(i))
	fmt.Printf("Is %d odd ? %v \n", i, even.Odd(i))
}

