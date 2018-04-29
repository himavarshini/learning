package main

import "fmt"
import "os"
import "crypto/sha1"

func main() {

    // os.Args[0] is the program name
    // os.Args[1:] gives the remaining arguments

    args := os.Args[1:]

    // len() is a general API that finds the length of the arguments
    if len(args) != 1 {
        fmt.Println(os.Args[0] + " <input password>")
        os.Exit(1);
    }
    
    // bytes is a group of numbers. The given string is converted into
    // a group of bytes
    password := []byte(os.Args[1])
    
    // find the sha1 output of the given password
	sha1hash := sha1.Sum(password)
	
	// create a new file called sha1hash
	pwfile, err := os.Create("sha1hash")
	if err != nil {
		fmt.Println("cannot create file sha1hash")
		panic(err)
	}
	// write the password into the hash file. 0:20 is very important to tell
	// that its a fixed buffer and only needs to write this portion of the bytes
	pwfile.Write(sha1hash[0:20])
	pwfile.Sync()
	
	// close the file
	pwfile.Close()
	
	// this below code is for checking again if the data entered is correct
	pwfile, err = os.Open("sha1hash")
	
	// create a byte array of 100 bytes in length
	data_in := make([]byte, 100)
	
	// pass the byte array to read API
	char_count, err := pwfile.Read(data_in)
	if err != nil {
		fmt.Println("cannot read file sha1hash")
		panic(err)
	}
	fmt.Println("read %d bytes: %q\n", char_count, data_in[:char_count])
}
