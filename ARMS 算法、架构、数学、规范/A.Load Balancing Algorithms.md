## Catalogue
*
*
* [Round-Robin Scheduling 轮询调度](#round_robin_scheduling)
* [Weighted Round-Robin Scheduling 权重轮询调度算法](#weighted_round_robin_scheduling)

# Round-Robin Scheduling 轮询调度	<a id="round_robin_scheduling"></a>
Round-robin scheduling is simple, easy to implement, and starvation-free (无状态).
　轮询调度算法假设所有服务器的处理性能都相同，不关心每台服务器的当前连接数和响应速度。当请求服务间隔时间变化比较大时，轮询调度算法容易导致服务器间的负载不平衡。

　　所以此种均衡算法适合于服务器组中的所有服务器都有相同的软硬件配置并且平均服务请求相对均衡的情况。
```
servers = [s0, s1, s2...]
alives = {s0: w0, s1: w1, s2: w2...}
int n = count(servers)
int i = n - 1	// last scheduled server id, initialize it to n - 1 when not set

function roundRobinScheduling() {
	while(true) {
		i = (i + 1) mod n
		if (alives[i] > 0) {
			return servers[i]
		}
	}
}

```
在系统实现时，我们引入了一个额外条件，当服务器的权值为零时，表示该服务器不可用而不被调度。这样做的目的是将服务器切出服务（如屏蔽服务器故障和系统维护），同时与其他加权算法保持一致。

# Weighted Round-Robin Scheduling 权重轮询调度算法	<a id="weighted_round_robin_scheduling"></a>
我们根据服务器的不同处理能力，给每个服务器分配不同的权值，使其能够接受相应权值数的服务请求。
```

weights = {s0: 10, s1: 2, s2: 8, s3: 8, s4: 10}
w_gcd = gcd(10, 2, 8, 8, 10) = 2     // Greatest Common Divisor
loop1: weight>=10,  s0,             s4  
loop2: weight>=8,   s0,     s2, s3, s4
loop3: weight>=6,   s0,     s2, s3, s4
loop4: weight>=4,	s0,     s2, s3, s4
loop5: weight>=2,	s0, s1, s2, s3, s4
loop6: weight=0,	reset weight = 10

You'll find that in a period, weight=10, runs 5 times; weight=8, runs 4 times; and weight=2 runs only 1 time.

weights = {s0: 10, s1: 2, s2: 5, s3: 8, S4: 10}
w_gcd = gcd(10, 2, 5, 8, 10) = 1	
loop1: weight>=10,  s0,             s4  
loop2: weight>=9,   s0,             s4
...
loop9: weight>=2,	s0, s1, s2, s3, s4
loopX: weight>=1,	s0, s1, s2, s3, s4
loopN: weight=0,	reset weight = 10

```
```
servers = [s0, s1, s2...]
weights = {s0: w0, s1: w1, s2: w2...}		// weight = 0 when not works
int max_weight = max(weights)
int weights_gcd = gcd(weights)
int n = count(servers)
int i = n - 1

int cw = 0							// current weight
function weightedRoundRobinScheduling() {
	while(true) {
		i = (i + 1) mod n
		if (i == 0) {				// a period
			cw -= weight_gcd
			if (cw <= 0) {
				cw = max_weight
			}
		}
		if (weights[servers[i]] >= cw) {
			return servers[i];
		}
	}
}
```