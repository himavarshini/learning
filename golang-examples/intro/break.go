package main

import "fmt"

func main() {
    for i := 0; i < 20; i++ {
        L:
        // one can not define any code below or near the break Lable
          //fmt.Println("the code jump ")
        for {
            for {
                break L
            }
        }
        fmt.Printf("%d\n", i)
    }
}
