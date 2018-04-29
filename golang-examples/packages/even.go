package even


func Even(i int) bool {
    return i%2==0
}

func odd(i int) bool {
    return !Even(i)
}

func Odd(i int) bool {
    return odd(i)
}
