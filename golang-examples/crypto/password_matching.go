package main

import ("fmt"
		"os"
		"crypto/sha1"
		"bytes"
)

func main() {
    if len(os.Args[1:]) != 1 {
        fmt.Println(os.Args[0] + " password")
        os.Exit(1)
    }
    
    password := []byte(os.Args[1])
    
    sha1hash := sha1.Sum(password)
    
    hash_file,err := os.Open("sha1hash")
    if err != nil {
    	panic(err)
    }
    
    hash_stored := make([]byte, 100)
    
    bytes_len, err := hash_file.Read(hash_stored)
    if err != nil {
        panic(err)
    }
    
    if bytes.Compare(hash_stored[0:bytes_len], sha1hash[0:20]) != 0 {
    	fmt.Println("password did not match")
    } else {
    	fmt.Println("password match")
    }
}

