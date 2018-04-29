package main

import "fmt"
import "time"

func main() {

	time_val := time.Now()

	time.Sleep(10 * time.Millisecond)

	fmt.Println(time.Since(time_val))
}

