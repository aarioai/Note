# Bisiness Algorithm

## Retry Pattern 重试算法

* Backoff 退避算法：  适合非持续性瞬时故障 (non long-lasting transient faults)
  * Exponential Backoff 指数退避重试：指数时间间隔（如微信15s/15s/30s/3m/10m/20m/30m/30m/30m/60m/3h/3h/3h/6h/6h，共10次）退避重试，广泛运用于DNS, switches, load balancers, wechat payment callback。
    * With exponential backoff, our retry algorithm will look like following:
      1. identify if the fault is a transient fault.
      2. define the maximum retry count (such as 10).
      3. if the call is failing even after maximum retries, let the caller module know that target service is unavailable.
* Circuit Breaker ：  适用持续性瞬时故障（long-lasting transient faults）
  * if the number of retry failures reaches above a certain threshold value, we'll make the circuit as OPEN with some timeout period.
  * the circuit'll move to HALF-OPEN state after specified timeout period. It'll allow a service call which will determine if the circuit should go back to OPEN state with more timeout period or move to CLOSED state.
  * play again
* WRR(Weighted Round-Robin Scheduling 权重轮询调度算法)：每台服务器加权重，适用于负载均衡重试
