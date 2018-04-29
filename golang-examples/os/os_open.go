package main

import "fmt"
import "os"
import "log"

func main() {
    f, err := os.Open("./os_open.go")
    if err != nil {
        log.Fatal(err)
    }
    
    fmt.Println("file opened succefully\n");
    
    data := make([]byte, 400)
    
    count, err := f.Read(data)
    if err != nil {
        log.Fatal(err)
    }
    
    fmt.Printf("read %d bytes: %q\n", count, data[:count])

    f.Close()
}
