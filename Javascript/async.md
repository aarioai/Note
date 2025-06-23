# async

```javascript

function asleep(delay: number, ...args: unknown[]) {
    return new Promise(resolve => setTimeout(resolve, delay, ...args))
}

function gainLock(){
    return Math.random() >= 0.5
}

async function awaitLock(maxWaitTime = 5 * Seconds) {
    const interval = 200 * Milliseconds
    const startTime = Date.now()
    while (Date.now() - startTime < maxWaitTime) {
        if (this.gainLock()) {
            return true
        }
        await asleep(interval)
    }
    log.warn(`${this.name}(#${this.id}) dead lock!`)
    return false
}

```

如上，awaitLock 使用 async 装饰，表示异步代码同步化。async 装饰的代码，必须要使用 try-catch 捕获异常，而不能使用 then-catch 方式捕获。
```javascript
try {
    const ok = await awaitLock()
} catch (err){
    
}

// 也可以写成异步方式，但是这种写法，并不能通过 then-catch 方式捕获所有异常，因此必须要依赖 try-catch
try{
    awaitLock().then(ok=>{
        
    })
} catch (err){
    
}
```

纯异步写法，可以使用 then-catch 捕获所有错误，不用依赖外层 try-catch。

```javascript

function waitLock(maxWaitTime = 5 * Seconds)  {
    return this.awaitLock(maxWaitTime).then((ok) => {
        if (!ok) {
            return Promise.reject(E_DeadLock)
        }
        return Promise.resolve(undefined)
    })
}

waitLock().then().catch(err=>{
    
})
```
