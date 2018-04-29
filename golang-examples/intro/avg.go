package main

import "fmt"

func avg(xs []float64) (average float64) {
    sum := 0.0

    if len(xs) == 0 {
        average = 0
    } else {
        for _,v := range xs {
            sum += v
        }
        average = sum / float64(len(xs))
    }

    return
}

func main() {
    var xs = []float64 {1, 2, 3, 4, 5}

    fmt.Println("Avg is", avg(xs))
}

