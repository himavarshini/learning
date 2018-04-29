package main

import "fmt"
import "os"
import "io/ioutil"
import "crypto/sha1"
import "crypto/md5"

func main() {

    if len(os.Args) != 3 {
	    fmt.Println("usage: ./hashio <algorithm> <filename>")
		os.Exit(1)
	}

    file := os.Args[2]
    filename, err := ioutil.ReadFile(file)
	if err != nil {
	    fmt.Printf("failed to open %s\n", file)
		os.Exit(1)
	}

    if os.Args[1] == "md5" {
		hash_val := md5.Sum(filename)
	    fmt.Printf("Alg: %s and csum: %x\n", os.Args[1], hash_val)
	} else if os.Args[1] == "sha1" {
		hash_val := sha1.Sum(filename)
	    fmt.Printf("Alg: %s and csum: %x\n", os.Args[1], hash_val)
	}

}
