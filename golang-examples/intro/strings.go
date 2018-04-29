package main

import "fmt"

func PrintStrings(vals []string) {
    for _, val := range vals {
	    fmt.Println(val)
	}
}

func main() {
    names := []string{"orange", "onion", "oyester"}
	PrintStrings(names)

	new_string := "dev" + " " + "naga" // comment here
	fmt.Println(new_string);
}
