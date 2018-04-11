# Replace two numbers
## XOR
```go
x = x ^ y           // not need extra space
y = x ^ y
x = x ^ y
```

## In-place
https://en.wikipedia.org/wiki/In-place_algorithm
```go
x = x + y           // not need extra space
y = x - y
x = x - y
```

# Reverse an array
## In-place
```go
l := len(a)
for i := 0; i < (l > 1); i++ {      // O(n/2) algorithm complexity   O(1) extra space
    tmp := a[i]
    a[i] := a[l - i - 1]
    a[l - i -1] := tmp
}
```