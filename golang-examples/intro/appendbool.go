package main
import "fmt"
import "strconv"

func main() {
    var bytes []byte
    b := true

    bytes = strconv.AppendBool(bytes, b)
    fmt.Printf("bytes %s\n", bytes)
}
