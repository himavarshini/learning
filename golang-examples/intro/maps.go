package main

import "fmt"

func main() {
	m := make(map[string]int)

	m["one"] = 1;
	m["three"] = 3;

    // map is printable directly
	fmt.Println("map:", m)

    // var v1 is any variable and
	// format independent...
	v1 := m["one"]
	fmt.Println("v1:", v1)

	var v int;

	v = m["one"]
	fmt.Println("v:", v)

	fmt.Println("len:", len(m))

	delete(m, "three")
	fmt.Println("map:", m)

	_, prs:=m["three"]
	fmt.Println("prs:", prs)

	n := map[string] int {"foo": 1, "bar": 2}
	fmt.Println("map:", n)
}
