package main

import "os"
import "fmt"

func usage() {
   fmt.Println("usage: ./usage_example\n")
}

func main() {
   var length int

   length = len(os.Args)

   if length != 1 {
       usage()
   }
}

