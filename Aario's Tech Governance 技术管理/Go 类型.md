```go
if s, ok := msg.(string); ok {
    m = s
} else if e, ok := msg.(error); ok {
    m = e.Error()
} 



switch reflect.TypeOf(pat).Kind() {
    case reflect.Bool:
        required = true
    case reflect.String:
        pattern, _ = pat.(string)
}
```

### Sample
```go
func t(a interface{}) {
	b, ok := a.(bool)
	fmt.Println("bool", b, ok)              // bool false false
	i, ok := a.(int)
	fmt.Println("int", i, ok)               // int 0 true

}

func main() {
	a := 0
	t(a)
}



```