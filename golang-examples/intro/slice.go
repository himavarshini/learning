package main

import "fmt"

func main() {
    s := make([]string, 3)
    fmt.Println("emp:", s)

    s[0] = "d"
    s[1] = "e"
    s[2] = "v"


    fmt.Println("set", s)
    fmt.Println("get", s[2])

    fmt.Println("len:", len(s))

    s = append(s, "e")
    s = append(s, "n")
    s = append(s, "d")

    c := make([]string, len(s))
    copy(c, s)

    // copy and assignment are similar
    c = s

    fmt.Println("copy:", c)

    // copy from position 2 with len 5 - 2 = 3
    l := s[2:5]
    fmt.Println("l2-5:", l)

    // copy the first five
    l1 := s[:5]
    fmt.Println("l1:5:", l1)

    // copy from the position 2
    l2 := s[2:]
    fmt.Println("l22::", l2)
}
