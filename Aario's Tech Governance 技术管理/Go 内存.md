# Escape analyze

在继续研究闭包的实现之前，先看一看Go的一个语言特性：

```go
func f() *Cursor {
    var c Cursor
    c.X = 500
    noinline()
    return &c
}
```
Cursor是一个结构体，这种写法在C语言中是不允许的，因为变量c是在栈上分配的，当函数f返回后c的空间就失效了。但是，在Go语言规范中有说明，这种写法在Go语言中合法的。语言会自动地识别出这种情况并在堆上分配c的内存，而不是函数f的栈上。

# Go 非抢占式
Goroutine 不是抢占式的，一个goroutine只有在涉及到加锁，读写通道或者主动让出CPU等操作时才会触发切换。