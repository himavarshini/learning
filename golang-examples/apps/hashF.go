package main

import "fmt"
import "os"
import "io/ioutil"
import "crypto/md5"

func main() {
    var filedata []byte

    filedata, err := ioutil.ReadFile("hashF.go")
    if err != nil {
        fmt.Println("failed to read file")
        os.Exit(0)
    }

    fmt.Printf("%x\n", md5.Sum(filedata))

}
