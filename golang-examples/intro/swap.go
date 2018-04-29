package main

import "fmt"

func stringswap(x, y string) (string, string) {
    return y, x
}

func floatswap(x, y float32) (float32, float32) {
    return y, x
}

func intswap(x, y int) (int, int) {
    return y, x
}

func main() {
    fmt.Printf("Hello\n")
	fmt.Printf("    1. string swap\n")
	fmt.Printf("    2. float swap\n")
	fmt.Printf("    3. int swap\n")

	var choice int
	var string_x, string_y string
	var float_x, float_y float32
	var int_x, int_y int

	fmt.Scanf("%d", &choice)

	switch choice {
	case 1:
	    fmt.Scanf("%s %s", &string_x, &string_y)
		string_x, string_y = stringswap(string_x, string_y)
		fmt.Printf("swapped %s %s\n", string_x, string_y)
	case 2:
	    fmt.Scanf("%g %g", &float_x, &float_y)
		float_x, float_y = floatswap(float_x, float_y)
		fmt.Printf("swapped %g %g\n", float_x, float_y)
	case 3:
	    fmt.Scanf("%d %d", &int_x, &int_y)
		int_x, int_y = intswap(int_x, int_y)
		fmt.Printf("swapped %d %d\n", int_x, int_y)
	}
}

