package main

import "fmt"

type todolist struct{
    listid int
}

func main() {
    todolist1 := []todolist{{1}, {2},{3}}
	fmt.Println(todolist1)
}
