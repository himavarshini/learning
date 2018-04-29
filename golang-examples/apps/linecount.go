package main

import "fmt"
import "os"
import "bufio"

func main() {
	if len(os.Args) != 2 {
		fmt.Println("usage: ./linecount <filename>")
		return
	}

	file, _ := os.Open(os.Args[1])

	scanner := bufio.NewScanner(file)

	count := 0
	for scanner.Scan() {
		count++
	}

	fmt.Println("lines ", count)
}

