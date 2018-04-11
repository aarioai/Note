# Raft
* Follower: 每一个新服务器加入，都是 follower。被动接收请求（不会发送任何请求），只会响应来自 leader 或 candidate 的请求（如心跳包）。如果接受来自 client 的请求，就会转发给 leader
* TermId: 选举生成任期ID，每个 term 只能有一个 leader，每个服务器在一个 term 内只能 vote 一次
* Leader: 
    - Raft系统只能有一个leader，向所有 follower 发送心跳包
    - 所有请求都由 leader 处理，leader 发送同步请求，当 quorum （多数派，类似拜占庭将军问题）响应后才返回给 client
    - leader 从来不修改自身日志，只追加（append entities）
    - 日志只从 leader 流向 follower
    - 不依赖各个节点物理时序保证一致性，通过逻辑递增的termId 和 logId 保证
    
* Candidate: 当 follower 接收心跳超时，则进入 candidate 状态

# Election

![RaftElection](https://raw.githubusercontent.com/AarioAi/Note/master/_asset/RaftElection.png)


## Leader 选举流程
服务器启动初始或 leader 挂掉后都是 follower，如果超时未收到 leader 发送的心跳包，则进入 candidate 状态进行 election，只要得票最多的就可以成为 leader。

如果出现得票相同，Raft 利用随机选举超时（election timeout）机制避免同票问题。Election timeout 从一个区间随机选择，每台服务器的 election timeout 时间都不同。Election timeout 时间最短且拥有日志最多的 candidate 最先开始重新选主（自增自身 currentTermId，进行下一轮选举）。一旦 candidate 成为 leader，就会向其他服务器发送心跳包阻止新一轮的选举开始。

```
leader.SendLog(termId, candidateId, lastLogTerm, lastLogIndex)
leader.SendSnapshot(leaderTermId, lastIndex, lastTermId, offset, data[], done_flag)
```

## Candidate 选举流程
自增 currentTermId，设置超时时间，向所有节点广播 request vote：
1. 若 quorum 回应，则成为 leader
2. 若收到 leader 心跳，且 leader termId >= currentTermId，则成为 follower
3. 若超时没有 quorum 回应，也没收到 leader 心跳包，则自增 currentTerm，进行下一轮 election

* 若 candidate 状态收到了新 leader 日志，而新 leader 返回的 termId < currentTermId，将 currentTermId 返回给 leader。Leader 发现该服务器 termId 比自己大，且没有达成多数派，则 leader 变成 follower，使 termId 更大的成为 leader。
* 并不保证 termId 大就一定会成为 leader，还需要 quorum 认可。

## Follower 选举流程
1. 若 candidateTermId < currentTermId，表示自己更新，则返回给 candidate；
2. 该 termId 周期内，还未投票且 candidate 的日志（lastLogTerm, lastLogIndex）和本地日志一样或更加新，则投票给它。

# 日志复制
## Leader 日志复制流程
1. 接收 client 请求，本地持久化日志；
2. 将日志广播到各个 follower；
3. 达成 quorum，进行 commit，返回给 client


## Follower 日志复制流程
1. 比较收到的 termId 和自身的 currentTermId，若 termId < currentTerm，则返回 false；
2. 若 prevLogIndex, prevLogTerm 不存在，说明还差日志，返回 false
3. 若 prevLogIndex, prevLogTerm 与已有日志冲突，以 leader 为准，删除自身日志
4. 将 leader 传来的日志追加到尾部（append entities）

# Q&A
## Raft 活锁
死锁是多个线程互相锁等待；活锁是指多个线程（节点）都正常，但是整体无法运行。
1. Raft 日志复制只有一阶段提交，不存在活锁问题；
2. Election 同票就会导致活锁，进行下一轮选举问题也会依旧；
3. 通过随机超时机制可以解决 election 活锁问题

## 如何保证 leader 拥有所有日志
1. 日志只能从 leader 流向 follower，发生冲突时以 leader 日志为准；
2. Election 时采用（logTerm, logIndex）谁最新谁优先，且需要 quorum 认可；
