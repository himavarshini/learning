package main
import "fmt"
// Mathematics include
import "math"

const s string = "constant"

func main() {
	fmt.Println(s)

    // macros 
	const n = 500000

	const d = 3e20/n

    // fmt. is already looks OBJ oriented approach

	fmt.Println(d)
	fmt.Println(int64(d))
	// invoking the math library function call
	fmt.Println(math.Sin(n))
}