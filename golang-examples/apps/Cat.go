package main

import "fmt"
import "bufio"
import "os"
import "io/ioutil"

func main() {
	if len(os.Args) == 1 {
		reader := bufio.NewReader(os.Stdin)
		for {
		    text, er := reader.ReadString('\n')
		    if er != nil {
			    fmt.Println("failed to read input")
			    return
		    }
		    fmt.Print(text)
		}
	} else if len(os.Args) != 0 {
		for _, item := range os.Args[1:] {
		    filedata, er := ioutil.ReadFile(item)
		    if er != nil {
			    fmt.Println("failed to read file")
			    return
		    }
		    fmt.Printf("%s", filedata)
		}
	}
}

