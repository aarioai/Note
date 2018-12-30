# 文件名

## 官方

* _test.go  单元测试
* _$platform  平台环境，windows, unix, posix, plan9, darwin, bsd, linux, freebsd, nacl, netbsd, openbsd, solaris, dragonfly, bsd, notbsd， android，stubs
* _$platform_$cpu CPU，如  _linux_amd64.go
* _$version  版本号，如  _linux_1.5.go

### 变量

* func makeT() T{return T{}}
* func newT() *T{return &T{}}
* new/make 出来的struct结果没有 error，如果存在因为参数导致的error问题，应当用 setX()/load() 来做

GetXX/PostXX/PutXX  ... 表示http方式处理
recvKcp
recvTcp