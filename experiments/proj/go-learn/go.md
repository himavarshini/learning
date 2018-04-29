go doc builtin

go manual pages ...

type safe and there is no typecasting needed

post fix types:

var a int -> declare a variable named a as an integer , which is similar
to the natural language description

in Golang the libs are called packages

building: go build progr.go

variables in go , when declared, are automatically initialized to zero

initialisation of (explicit) vars can also be done using := operator

ex: a:=200

multiple var declarations can also be grouped

ex: 

var (
    x int
	b bool
)

the declaration

a, b := 20, 16

will assign 20 to a and 16 to b

_ is a special variable. Anything that is assigned to this var
is discarded.

ex:

_, b := 34, 35

34 is discarded.

Declared but otherwise unused variables are compiler error in Go.

package main
func main() {
    var i int
}

'bool'ean type is 'bool'. Two values: true, or false.

strings initialized :  s:= "Hello" or var s string = "Hello"
once assigned to a variable, strings can not be changed. strings in
Go are immutable.

var s string = "Hello"
s[0] = 'c'   -> will result in an error

complex numbers are denoted by complex128 (64 bit real , 64 bit imaginary)
and complex64 (32 bit real, 32 bit imaginary).
