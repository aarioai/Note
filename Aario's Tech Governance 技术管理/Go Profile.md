```shell
sh$ go run -race test.go     // 竞争检测器只能发现在运行期确实发生的数据竞争

sh$ go test  单元测试
sh$ go test -bench    压力测试

sh$ go build -gcflags "-N -l" test.go
sh$ gdb test

sh$ go vet .       vet工具可以帮我们静态分析我们的源码存在的各种问题, 例如多余的代码, 提前return的逻辑, struct的tag是否符合标准等.

sh$ go build main.go
sh$ GODEBUG=schedtrace=1000 ./main
sh$ GODEBUG=gctrace=1,allocfreetrace=1,schedtrace=1000 ./main
|[
    1004ms: gomaxprocs=4 idleprocs=0 threads=11 idlethreads=4 runqueue=8 [20 1 0 3]
    ....
]|

1004ms: time since program start
gomaxprocs: current value of GOMAXPROCS
idelprocs: the number of idling processors
threads: number of worker threads created by the scheduler, can be in 3 states:
    - Execute Go code (gomaxproc-idleprocs)
    - Execute syscall/cgocalls
    - Idle
runqueue: the length of global queue with runnable goroutines
[20 1 0 3]: lengths of per-processor queues with runnable goroutines
```

### GODEBUG
当一个程序不与 GOMAXPROCS 成线性比例和/或没有消耗 100% 的 CPU 时间，调度器追踪就显得非常有用。理想的情况是：所有的处理器都在忙碌地运行 Go 代码，线程数合理，所有队列都有充足的任务且任务是合理均匀的分布的：

gomaxprocs=8 idleprocs=0 threads=40 idlethreads=5 runqueue=10 [20 20 20 20 20 20 20 20]