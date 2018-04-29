package main

import "fmt"
import "bufio"
import "os"

func main() {
	reader := bufio.NewReader(os.Stdin)

	for {
	    fmt.Print("input: ")
		str, er := reader.ReadString('\n')
		if er != nil {
			fmt.Println("failed to read input")
			return
		}
		fmt.Printf("output: %s", str)
	}
}

