package main

import "os"
import "fmt"

// the go compiler cannot determine (ofcourse none of the current
// compilers) what would be the output of the program
// but not restricting the usage of the variable beyond checking
// the lengths of the os.Args looks bad
func main() {
    argsWithProg := os.Args
    argsWithoutProg := os.Args[1:]

    arg1 := os.Args[0]
    fmt.Println("first arg ", arg1);

    arg := os.Args[3]

    fmt.Println(argsWithProg)
    fmt.Println(argsWithoutProg)
    fmt.Println(arg)

    //similar to python's len() API
    fmt.Println("length of the args is %d\n", len(os.Args))
}

