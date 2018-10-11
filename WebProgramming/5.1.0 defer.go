package Go
/*
被defer的调用会在包含的函数的末尾执行，而不是包含代码块的末尾。
被defer的函数的参数会在defer声明时求值（而不是在函数实际执行时）。
 */

func deferParam() {
    var i int = 1
    defer fmt.Println("result =>",func() int { return i * 2 }())
    i++
    //prints: result => 2 (not ok if you expected 4)
}