package main

import "fmt"

func main() {
	s := make(map[string]string)

	s["dev"] = "naga"
	s["naga"] = "dev"

	fmt.Println("s:", s)

	fmt.Println("s[dev] is:", s["dev"])
	fmt.Println("s[naga] is:", s["naga"])

	fmt.Println("s[any] is:", s["any"])

	fmt.Println("len of s:", len(s))

}
