
# 文件 Close 问题

如下，最后输出文件大小会是什么情况？

```go
func zip() {
    f := "/tmp/pensive.zip"
    zf, _ := os.Create(f)
    w := zip.NewWriter(zf)
    defer w.Close()
    fw.Write(....)
    w.Flush()
    
    fi, _ := ioutil.ReadFile(f)
    fmt.Println(len(fi))
}
```

可能会出现文件尺寸小的问题，因为 `w.Close()` 是 `defer`。故安全操作不应该用 `defer`，而是直接在使用之后关闭。