package main
import "fmt"

type Example struct {
    Val string
    count int
}

func struct_receive(str Example) (Example) {
    str.count = 20
    str.Val = "dev"
    return str
}

func main() {
    var a Example // define a variable a of type struct Example
    a.count = 10

    // access of this variable is similar
    fmt.Printf("Count %d\n", a.count)

    new_struct := struct_receive(a)
    fmt.Printf("string : %s count : %d\n", new_struct.Val, new_struct.count)
}
