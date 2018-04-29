package main

import "fmt"

type array_list struct {
    prime bool
	member int
}

func array_gen() [100] array_list {
    var array[100] array_list

    for i:= 0; i < len(array); i++ {
	    fmt.Printf("i value is %d\n", i)
		array[i].prime = false
	    array[i].member = i
	}

	return array;
}

func main() {
	list := array_gen()

    for i := 2; i < len(list); i++ {
	    count := 0
		fmt.Println(list[i].member)
	    for j := 2; j < len(list); j++ {
		    if list[i].member % j == 0 {
			    count++
			}

			if count > 1 {
			    break
			}
		}
		if count <= 1 {
		    list[i].prime = true
		}
	}

	for i := 0; i < len(list); i++ {
	    if list[i].prime {
		    fmt.Printf("number: %d\n", list[i].member)
		}
	}
}

