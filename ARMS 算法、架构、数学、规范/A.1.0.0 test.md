# Reverse Integer
```go
func reverse(x int) int {
	const max = 1<<31 - 1
	const min = -1 << 31
	neg := x < 0
	if neg {
		x = -x
	}
	s := []byte(strconv.Itoa(x))
	l := len(s)
	for i := 0; i < (l >> 1); i++ {
		tmp := s[i]
		s[i] = s[l-i-1]
		s[l-i-1] = tmp
	}
	r, e := strconv.Atoi(string(s))
	if e != nil {
		panic(e)
	}
	if neg {
		r = -r
	}
	if r > max || r < min {
		return 0
	}
	return r
}
```

```go
func reverse(x int) int {
	const max = 1<<31 - 1
	const min = -1 << 31
	neg := x < 0
	if neg {
		x = -x
	}
	s := "0"
	for {
		if x <= 0 {
			break
		}

		s = s + strconv.Itoa(x%10)
		x = x / 10

	}

	r, e := strconv.Atoi(s)
	if e != nil {
		panic(e)
	}
	if neg {
		r = -r
	}
	if r > max || r < min {
		return 0
	}
	return r
}
```

