package main

import "fmt"

// prime number calculation method
func prime_eratosthene(num int) (int, []int) {
    list:=make([]int, num)

    k:=0
    
    for i:=2; i< num; i++ {
        count:=0
        for j:=2; j <=i; j++ {
            if i % j == 0 {
                count++;
            }
        }
        if count == 1 {
            list[k] = i
            k++
        }
    }
    
    return k, list
}

func main() {
    k, list:=prime_eratosthene(10000)
    
    for i:= 0; i <k ; i++ {
        fmt.Printf("%d  ", list[i])
    }
    fmt.Println()
}
