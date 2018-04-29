package main

import "fmt"

func main() {
	message := make(chan int)

	go func() {
		message <- 2
	}()

	msg := <-message

	fmt.Println(msg)
}

