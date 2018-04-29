package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Printf("hour : %d\n", time.Hour)
	fmt.Printf("minute : %d\n", time.Minute)
	fmt.Printf("second : %d\n", time.Second)
	fmt.Printf("millisecond : %d\n", time.Millisecond)
	fmt.Printf("microsecond : %d\n", time.Microsecond)
	fmt.Printf("nanosecond : %d\n", time.Nanosecond)
}

