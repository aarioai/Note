package Go

/*
默认情况下，Go仅使用一个执行上下文/OS线程（在当前的版本）。这个数量可以通过设置GOMAXPROCS来提高。

一个常见的误解是，GOMAXPROCS表示了CPU的数量，Go将使用这个数量来运行goroutine。而runtime.GOMAXPROCS()函数的文档让人更加的迷茫。GOMAXPROCS变量描述（https://golang.org/pkg/runtime/）所讨论OS线程的内容比较好。

你可以设置GOMAXPROCS的数量大于CPU的数量。GOMAXPROCS 范围是 [1, 256]。
 */
