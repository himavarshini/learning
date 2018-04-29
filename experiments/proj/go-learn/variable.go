package main
// Println
import "fmt"

func main() {

	var a string = "initial"
	fmt.Println(a)

    // b is 1 and c is 2
    // go adds a space between the two variable print statements
	var b, c int = 1, 2
	fmt.Println(b,c)

	var d = true
	fmt.Println(d)

    // by default the value is inited to '0'
	var e int
	fmt.Println(e)

    // implicit assignment "string"
	f:="short"
	fmt.Println(f)
}
