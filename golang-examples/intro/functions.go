package main

import "fmt"
import "time"
import "os"
import "os/exec"

func add(x float32, y float32) float32 {
    return x + y
}

func sub(x float32, y float32) float32 {
    return x - y
}

func mul(x float32, y float32) float32 {
    return x * y
}

func div(x float32, y float32) float32 {
    return x / y
}

func main() {
	var choice int
	var a, b float32

	for {
	    cmd := exec.Command("clear")
		cmd.Stdout = os.Stdout
		cmd.Run()
        fmt.Printf("Hello \n")
	    fmt.Printf("  1. Add \n")
	    fmt.Printf("  2. Sub \n")
	    fmt.Printf("  3. Mul \n")
	    fmt.Printf("  4. Div \n")

	    fmt.Scanf("%d", &choice)

        if choice < 1 || choice > 4 {
	        fmt.Printf("Invalid choice\n")
		    return
	    }

	    fmt.Printf("Enter numbers:\n  ")
	    fmt.Scanf("%g %g", &a, &b)

	    switch choice {
	        case 1:
		        fmt.Printf("Add %g\n", add(a, b))
		    case 2:
		        fmt.Printf("Sub %g\n", sub(a, b))
		    case 3:
		        fmt.Printf("Mul %g\n", mul(a, b))
		    case 4:
		        fmt.Printf("Div %g\n", div(a, b))
	    }
		time.Sleep(time.Second * 2)
	}
}
