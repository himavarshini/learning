package main

import (
	"fmt"
	"time"
)

func main() {
	time_now := time.Now()

	yy, mm, dd := time_now.Date()

	fmt.Printf("year %d month %d date %d\n", yy, mm, dd)
	fmt.Printf("hour %d minute %d second %d\n", time_now.Hours(),
					time_now.Minutes(),
					time_now.Seconds())

	fmt.Println(time_now)
	fmt.Println(time_now.Month())
	fmt.Println(time_now.Date())
}

