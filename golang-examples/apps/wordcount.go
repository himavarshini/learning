package main

import "fmt"
import "bufio"
import "os"

func main() {
    if len(os.Args) != 2 {
        fmt.Println("usage: ./wordcount <filename>")
        return
    }
    
    file, _ := os.Open(os.Args[1])
    reader := bufio.NewReader(file)
    
    count := 1
    
    for {
        c, er := reader.ReadByte()
        if er != nil {
            fmt.Println(count)
            return
        }
        
        if c == ' ' {
            count++;
        }
    }
}
