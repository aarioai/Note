package Go

type field struct {
    name string
}

func (p *field) print() {
    fmt.Println(p.name)
}


/**
@NOTE
    Go 的协程都是外部变量都是使用指针地址，协程内修改会修改外面的值

    v := 0
    for i:=0; i< 3; i++ {
        v++
        go func(){
            fmt.Println(v)   //
            v=100
        }()
    }

    fmt.Println(v)      // 100  因为协程内是指针引用


    v := 0
    for i:=0; i< 3; i++ {
        v++
        v:=v       // 每次 for ，这个临时变量 v 都是新地址，所以
        go func(){
            fmt.Println(v)   //  逐次 1  2 3
            v=100
        }()
    }

    fmt.Println(v)      // 3


     */


func coroutineRef() {
    data := []string{"one", "two", "three"}
    /*
    for语句中的迭代变量在每次迭代时被重新使用。这就意味着你在for循环中创建的闭包（即函数字面量）将会引用同一个变量（而在那些goroutine开始执行时就会得到那个变量的值）。
     */
    for _, v := range data {
        go func() {

            fmt.Println(v)
        }()
    }
    time.Sleep(3 * time.Second)
    // 输出：three, three, three
}

func coroutineRefSenior() {
    data := []field{{"one"}, {"two"}, {"three"} }
    for _, v := range data {
        go v.print()
    }
    time.Sleep(3 * time.Second)
    // 输出: three, three, three
}

func coroutine() {
    data := []string{"one", "two", "three"}
    for _, v := range data {
        vcopy := v // 最简单的解决方法（不需要修改goroutine）是，在for循环代码块内把当前迭代的变量值保存到一个局部变量中。
        go func() {
            fmt.Println(vcopy)
        }()
    }
    time.Sleep(3 * time.Second)
    // 输出：one, two, three
}

func coroutineSenior() {
    data := []field{{"one"}, {"two"}, {"three"} }
    for _, v := range data {
        v := v
        go v.print()
    }
    time.Sleep(3 * time.Second)
    // 输出：one, two, three
}

func coroutine2() {
    data := []string{"one", "two", "three"}
    for _, v := range data {
        go func(in string) {
            fmt.Println(in)
        }(v)
    }

    time.Sleep(3 * time.Second)
    // 输出：one, two, three
}

func coroutineSeniorX() {
    data := []*field{{"one"}, {"two"}, {"three"} }
    for _, v := range data {
        go v.print()
    }
    time.Sleep(3 * time.Second)
    // 输出：three, two, one
}