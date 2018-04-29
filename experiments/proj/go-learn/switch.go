package main
import "fmt"
import "time"

func main() {
    i := 2
    // Print function does not add
    // any spaces or new lines
    fmt.Print("write ", i," as ")

    // there is no break statement
    // needed after every switch to
    // avoid the case flow
    switch i {
        case 1:
            fmt.Println("one")
        case 2:
            fmt.Println("two")
        case 3:
            fmt.Println("three")
    }

    switch time.Now().Weekday() {
        // the below are ENUM
        case time.Saturday, time.Sunday:
            fmt.Println("its the weekend")
        default:
            fmt.Println("its a weekday")
    }

    t := time.Now()
    switch {
        case t.Hour() < 12:
            fmt.Println("its a before noon")
        default:
            fmt.Println("its after noon")
    }
}
