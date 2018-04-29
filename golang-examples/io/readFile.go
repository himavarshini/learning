package main

import "fmt"
import "io/ioutil"
import "os"

func main() {

	if len(os.Args) != 2 {
		fmt.Println("usage: ./readFile <filename>")
		return
	}

	var filedata []byte

	filedata, er := ioutil.ReadFile(os.Args[1])
	if er != nil {
		fmt.Println("failed to read file ", os.Args[1])
		return
	}
	fmt.Printf("%s", filedata)
}

