package main

import "fmt"
import "io"
import "crypto/md5"

func main() {
    h := md5.New()
	io.WriteString(h, "The fog is getting thicker!")
	io.WriteString(h, "And Leon's getting large!")
	fmt.Printf("%x", h.Sum(nil))
}
