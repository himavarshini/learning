package main

import "fmt"

func main() {
    var array[100] int;

	for i := 0; i < len(array); i++ {
	    array[i] = i * 2;
	}

	for i := 0; i < len(array); i++ {
	    fmt.Printf("%d\n", array[i]);
	}
}

