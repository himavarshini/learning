package main

import "fmt"
import "strconv"

type metaStruct struct {
    name string
	id int
}


func meta_init() ([]metaStruct) {
    elems := make([]metaStruct, 20)
	for i:= 0; i < 20; i++ {
	    elems[i].name = "a" + strconv.Itoa(i)
		elems[i].id = i + 10
	}

	return elems
}

func main() {
    elems := meta_init()

	for i:= 0; i < 20; i++ {
	    fmt.Printf("name %s id %d\n", elems[i].name, elems[i].id);
	}
}
