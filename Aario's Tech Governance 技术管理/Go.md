# Go coroutine 外面变量与并发读写map

下面程序 map 会输出什么？

```go
func main() {
	m := make(map[string]int, 3)
	for i := 1; i < 4; i++ {
		go func() {
			m["a"] = i
		}()
		go func() {
			m["b"] = i
		}()
		go func() {
			m["c"] = i
		}()
	}
	runtime.Gosched()
	fmt.Println(m)
}
```

解释：会报错！不仅仅考察Go coroutine 外面参数 i ，同时也考察并发读写map

# Go coroutine 执行顺序

下面程序会输出什么
```go
var mmutext sync.RWMutex
func a() int {
	fmt.Println("a")
	time.Sleep(time.Second * 5)
	return 1
}
func b() int {
	fmt.Println("b")
	time.Sleep(time.Second * 2)
	return 2
}
func c() int {
	fmt.Println("c")
	time.Sleep(time.Second * 1)
	return 3
}

func main() {
	m := make(map[string]int, 3)
	go func() {
		m["a"] = a()
	}()

	go func() {
		m["c"] = c()
	}()

	go func() {
		m["b"] = b()
	}()
	runtime.Gosched()
	for i := 0; i < 10; i++ {
		time.Sleep(time.Second)
		fmt.Println(m)
	}
}
```
解释：协程是由后往前运行，而Go Map是无序的，故输出可能如下：
```
b
a
c
map[]
map[c:3]
map[b:2 c:3]
map[c:3 b:2]
map[c:3 b:2 a:1]
map[b:2 a:1 c:3]
map[a:1 c:3 b:2]
map[c:3 b:2 a:1]
map[c:3 b:2 a:1]
map[c:3 b:2 a:1]
```
但是这个可能会出现并发读写Map的crash，所以应当对map读写加 RWMutex 锁。

```go
var mMutex sync.RWMutex

func a() int {
	log.Println("a")
	time.Sleep(time.Second * 5)
	return 1
}
func b() int {
	log.Println("b")
	time.Sleep(time.Second * 2)
	return 2
}
func c() int {
	log.Println("c")
	time.Sleep(time.Second * 1)
	return 3
}

func main() {
	m := make(map[string]int, 3)
	go func() {
		mMutex.Lock()
		m["a"] = a()
		mMutex.Unlock()
	}()

	go func() {
		mMutex.Lock()
		m["c"] = c()
		mMutex.Unlock()
	}()

	go func() {
		mMutex.Lock()
		m["b"] = b()
		mMutex.Unlock()
	}()
	runtime.Gosched()
	for i := 0; i < 10; i++ {
		time.Sleep(time.Second)
		mMutex.RLock()
		log.Println(m)
		mMutex.RUnlock()
	}
}
```

输出如下：

```
2018/09/18 14:26:31 b
2018/09/18 14:26:33 map[b:2]
2018/09/18 14:26:33 a
2018/09/18 14:26:38 map[b:2 a:1]
2018/09/18 14:26:38 c
2018/09/18 14:26:39 map[b:2 a:1 c:3]
2018/09/18 14:26:40 map[b:2 a:1 c:3]
2018/09/18 14:26:41 map[a:1 c:3 b:2]
2018/09/18 14:26:42 map[c:3 b:2 a:1]
2018/09/18 14:26:43 map[b:2 a:1 c:3]
2018/09/18 14:26:44 map[a:1 c:3 b:2]
2018/09/18 14:26:45 map[c:3 b:2 a:1]
2018/09/18 14:26:46 map[b:2 a:1 c:3]
```

# Go defer 在return前执行 与 return 的非原子性
defer 在 return前执行，但是`return 是非原子性的`。多个defer，会用栈方式调用，越后面defer先执行。
## 坑1
```go
func f() (result int) {
	defer func() {
		result++
	}()
	return 0
}

```

这里会返回 1，而不是 0；先赋值，再defer，最后 return 空；如同下：

```go
func f() (result int) {
	result = 0
	func() {
		result++
	}()
	return
}
```
## 坑2
```go
func f() (r int) {
     t := 5
     defer func() {
       t = t + 5
     }()
     return t     // --->   r = t ; return
}
```
这里会返回 5。

```go
func f() (r int) {
	 t := 5
     defer func() {
       t = t + 5
	 }()

	 r = t
     return
}
```

## 坑3

```go
func f() (r int) {
	defer func(r int) {
		r = r + 5
		fmt.Print(r)
	}(r)
	return 1
}
```
这里返回的是 1 ，而不是 6

```go
func f() (r int) {
	defer func(r int) {
		r = r + 5
	}(r)			// r = 0，r 作为参数，里面不会修改外面的 r

	r = 1
	return
}
```