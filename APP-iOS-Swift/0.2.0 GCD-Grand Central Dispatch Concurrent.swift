/**
 * Queuing Tasks for Dispatch
 *  Main: tasks execute serially on your application’s main thread
 *  Concurrent: tasks are dequeued in FIFO order, but run concurrently
 *  Serial: tasks execute one at a time in FIFO order
 */





print("------------------------------------------- Start: Asynchronous Demo")

var passingAsyncData: String? = nil
let mainQueue = dispatch_get_main_queue()
let globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)


let inferiors = [100, 200, 300, 400]
dispatch_apply(inferiors.count, globalQueue) {
    i -> Void in
    print("dispatch_apply(\(inferiors[i])) : blocks following")
}

print("^^^^^^^^^^^^^^^^^^^ C ~> S ^^^^^^^^^^^^^^^^^")
dispatch_async(globalQueue) {
    passingAsyncData = "Asynchronous"
    print("Start: {Concurrent} ~> {Serial}")
    dispatch_async(mainQueue) { print(passingAsyncData!) }
    dispatch_apply(inferiors.count, globalQueue) {  // a block run N times
        i -> Void in
        print("In thread: dispatch_apply(\(inferiors[i])) : blocks following")
    }
    print("End: {Concurrent} ~> {Serial}")
}


var dispatchOnceToken : dispatch_once_t = 0
dispatch_once(&dispatchOnceToken) {
    print("dispatch_once_1")
}
dispatch_once(&dispatchOnceToken) {
    print("dispatch_once_2")
}


dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(5 * NSEC_PER_SEC)), globalQueue) { print("Run after 5 seconds") }

// let semaphore =  dispatch_semaphore_create(1) // dispatch_semaphore_t = 1
for _ in 0...2 {
    dispatch_async(globalQueue, {       // create 4 threads
        // dispatch_semaphore_t -- = 0
        //dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER)
        print("semaphore--")
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(2 * NSEC_PER_SEC)), globalQueue) {
            print("Run after 2 seconds")
            print("Before: semaphore++")
           // dispatch_semaphore_signal(semaphore)
            print("After: semaphore++")
            
        }
    })
}
print("------------------------------------------- End: Asynchronous Demo")


/***************************************************************************
------------------------------------------- Start: Asynchronous Demo
dispatch_apply(100) : blocks following
dispatch_apply(200) : blocks following
dispatch_apply(300) : blocks following
dispatch_apply(400) : blocks following
^^^^^^^^^^^^^^^^^^^ C ~> S ^^^^^^^^^^^^^^^^^
dispatch_once_1
Start: {Concurrent} ~> {Serial}
------------------------------------------- End: Asynchronous Demo
semaphore--
In thread: dispatch_apply(100) : blocks following
semaphore--
semaphore--
In thread: dispatch_apply(200) : blocks following
In thread: dispatch_apply(300) : blocks following
In thread: dispatch_apply(400) : blocks following
End: {Concurrent} ~> {Serial}
Asynchronous
Run after 2 seconds
Run after 2 seconds
Run after 2 seconds
Before: semaphore++
Before: semaphore++
Before: semaphore++
After: semaphore++
After: semaphore++
After: semaphore++
Run after 5 seconds
**************************************************************************/





print("------------------------------------------ Start: Asynchronous Demo")

let mainQueue = dispatch_get_main_queue()
let globalQueueLow = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0)
let globalQueueHigh = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0)
let globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)

print("^^^^^^^^^^^^^^^^^^^ dispatch_async(mainQueue) ^^^^^^^^^^^^^^^^^")
dispatch_async(mainQueue) { print("serial1-before-C~>S") }
dispatch_async(mainQueue) { print("serial2-before-C~>S") }
dispatch_async(mainQueue) { print("serial3-before-C~>S") }

print("^^^^^^^^^^^^^^^^^^^ dispatch_async(mainQueue) ^^^^^^^^^^^^^^^^^")
dispatch_async(mainQueue) { print("serial1-after-C~>S") }
dispatch_async(mainQueue) { print("serial2-after-C~>S") }
dispatch_async(mainQueue) { print("serial3-after-C~>S") }

print("^^^^^^^^^^^^^^^ dispatch_async(globalQueueLow) ^^^^^^^^^^^^^^^^")
dispatch_async(globalQueueLow) { print("lowConcurrent1") }

print("^^^^^^^^^^^^^^ dispatch_barrier_async(globalQueue) ^^^^^^^^^^^^")
dispatch_barrier_async(globalQueue) {print("wait finishing all the block")}
dispatch_async(globalQueueLow) { print("lowConcurrent2") }
dispatch_async(globalQueueLow) { print("lowConcurrent3") }

print("^^^^^^^^^^^^^^ dispatch_async(globalQueueHigh) ^^^^^^^^^^^^^^^^")
dispatch_async(globalQueueHigh) { print("highconcurrent1-before-dispatch_group_wait") }
dispatch_async(globalQueueHigh) { print("highconcurrent2-before-dispatch_group_wait") }
dispatch_async(globalQueueHigh) { print("highconcurrent3-before-dispatch_group_wait") }

print("^^^^^^^^^^^^^^^^^^^^ dispatch_group_async() ^^^^^^^^^^^^^^^^^^^")
let g = dispatch_group_create()
dispatch_group_async(g, globalQueue) { print("gConcurrent1") }
dispatch_group_async(g, globalQueue) { print("gConcurrent2") }
dispatch_group_async(g, globalQueue) { print("gConcurrent3") }
dispatch_group_notify(g, globalQueue) { print("g-notify") }
dispatch_group_wait(g, DISPATCH_TIME_FOREVER)
print("g-wait-DISPATCH_TIME_FOREVER")

print("^^^^^^^^^^^^^^^ dispatch_async(globalQueueHigh) ^^^^^^^^^^^^^^^")
dispatch_async(globalQueueHigh) { print("highconcurrent1-after-dispatch_group_wait") }
dispatch_async(globalQueueHigh) { print("highconcurrent2-before-dispatch_group_wait") }
dispatch_async(globalQueueHigh) { print("highconcurrent3-before-dispatch_group_wait") }

print("-------------------------------------------- End: Asynchronous Demo")
/***************************************************************************
------------------------------------------ Start: Asynchronous Demo
^^^^^^^^^^^^^^^^^^^ dispatch_async(mainQueue) ^^^^^^^^^^^^^^^^^
^^^^^^^^^^^^^^^^^^^ dispatch_async(mainQueue) ^^^^^^^^^^^^^^^^^
^^^^^^^^^^^^^^^ dispatch_async(globalQueueLow) ^^^^^^^^^^^^^^^^
^^^^^^^^^^^^^^ dispatch_barrier_async(globalQueue) ^^^^^^^^^^^^
lowConcurrent1
^^^^^^^^^^^^^^ dispatch_async(globalQueueHigh) ^^^^^^^^^^^^^^^^
wait finishing all the block
lowConcurrent2
lowConcurrent3
^^^^^^^^^^^^^^^^^^^^ dispatch_group_async() ^^^^^^^^^^^^^^^^^^^
highconcurrent1-before-dispatch_group_wait
highconcurrent2-before-dispatch_group_wait
highconcurrent3-before-dispatch_group_wait
gConcurrent1
gConcurrent2
gConcurrent3
g-wait-DISPATCH_TIME_FOREVER
g-notify
^^^^^^^^^^^^^^^ dispatch_async(globalQueueHigh) ^^^^^^^^^^^^^^^
-------------------------------------------- End: Asynchronous Demo
highconcurrent1-after-dispatch_group_wait
highconcurrent3-before-dispatch_group_wait
highconcurrent2-before-dispatch_group_wait
serial1-before-C~>S
serial2-before-C~>S
serial3-before-C~>S
serial1-after-C~>S
serial2-after-C~>S
serial3-after-C~>S
***************************************************************************/

/**
 * @see https://developer.apple.com/library/ios/documentation/General/Conceptual/CocoaEncyclopedia/ReceptionistPattern/ReceptionistPattern.html
 * @see https://developer.apple.com/library/ios/documentation/Performance/Reference/GCD_libdispatch_Ref
 * GCD offers three kinds of queues:
 *  Main:       tasks execute serially on your applications' main thread
 *              it's automatically created by the system and assoicated with
 *              the main thread
 *  Concurrent: tasks are dequeued in FIFO order, but run concurrently and
 *              can finish in any order; multi-threads
 *              dispatch_get_global_queue(_ identifier:Int, _ flags: UInt)
 *  Serial:     tasks execute one at a time in FIFO order; one-thread
 *              dispatch_get_main_queue()
 */



dispatch_suspend(globalQueue)    // suspend a queue
dispatch_resume(globalQueue)     // resume a suspended queue



/**
 *  dispatch_async(_: dispatch_queue_t, _ block: dispatch_block_t)
 */
dispatch_async(_: dispatch_queue_t) {}  // create a thread
dispatch_apply()                        // a block run N times

 
dispatch_get_main_queue() -> dispatch_queue_t   // Serial Dispatch Queue
/**
 * Concurrent Dispatch Queue
    * @param identifier
 * A quality of service class defined in qos_class_t or a priority defined in
 * dispatch_queue_priority_t.
 *
 * It is recommended to use quality of service class values to identify the
 * well-known global concurrent queues:
 *  - QOS_CLASS_USER_INTERACTIVE
 *  - QOS_CLASS_USER_INITIATED
 *  - QOS_CLASS_DEFAULT
 *  - QOS_CLASS_UTILITY
 *  - QOS_CLASS_BACKGROUND
 *
 * The global concurrent queues may still be identified by their priority,
 * which map to the following QOS classes:
 *  - DISPATCH_QUEUE_PRIORITY_HIGH:         QOS_CLASS_USER_INITIATED
 *  - DISPATCH_QUEUE_PRIORITY_DEFAULT:      QOS_CLASS_DEFAULT
 *  - DISPATCH_QUEUE_PRIORITY_LOW:          QOS_CLASS_UTILITY
 *  - DISPATCH_QUEUE_PRIORITY_BACKGROUND:   QOS_CLASS_BACKGROUND
 *
 * @param flags
 * Reserved for future use. Passing 0.
 */
dispatch_get_global_queue(_ identifier: Int, _ flags: UInt)

/**
 * @param label
 * @param attr  DISPATCH_QUEUE_SERIAL(or nil) || DISPATCH_QUEUE_CONCURRENT
 */
dispatch_queue_create(label: UnsafePointer<Int8>, _ attr: dispatch_queue_attr_t!) -> dispatch_queue_t!

let q: dispatch_queue_t = dispatch_queue_create("com.xxx", nil)
dispatch_async(q) { () -> Void in print("in Block") }


dispatch_after(_: dispatch_time_t, _: dispatch_queue_t, _: dispatch_block_t)
dispatch_time(_: dispatch_time_t, _ delta: Int64) -> dispatch_time_t

dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(10 * NSEC_PER_SEC)), dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
    () -> Void in
    print("Run 10 secs later")
}

/**
 * dispatch_group_wait(group, DISPATCH_TIME_FOREVER) runs after finishing
 *  all the dispatch_group_async()
 * dispatch_group_notify() runs after blocking, it dosen't belong to the
 *  queue, so it runs after dispatch_group_wait(g, DISPATCH_TIME_FOREVER)
 * It may display:
 *  1-3. [gConcurrent1 gConcurrent2 gConcurrent3] // unpredictable sequence
 *  4.   g-wait-DISPATCH_TIME_FOREVER
 *  5.   g-nofity
 */
let g = dispatch_group_create()
dispatch_group_async(g, globalQueue) { print("gConcurrent1") }
dispatch_group_async(g, globalQueue) { print("gConcurrent2") }
dispatch_group_async(g, globalQueue) { print("gConcurrent3") }
dispatch_group_notify(g, globalQueue) { print("g-notify") }
dispatch_group_wait(g, DISPATCH_TIME_FOREVER)
print("g-wait-DISPATCH_TIME_FOREVER")



/**
 * Dispatch Semaphore
 * @param value
 *  Passing zero for the value is useful for when two threads need to 
 *  reconcile the completion of a particular event. Passing a value 
 *  greather than zero is useful for managing a finite pool of resources, 
 *  where the pool size is equal to the value.
 */
dispatch_semaphore_create(_ value: Int) -> dispatch_semaphore_t!

/**
 * Decrement the dispatch_semaphore_t. If the resulting value is less than 0
 *  it waits for a signal to occur before returning.
 * @param :dispatch_semaphore_t
 *  
 * @result
 *  Returns 0 on success, or non-zer if the timeout occurred
 */
dispatch_semaphore_wait(_:dispatch_semaphore_t, _ timeout: dispatch_time_t) -> Int

/**
 * Increment the dispatch_semaphore_t. If the previous value was less than 0
 *  it wakes a waiting thread before returning.
 */
dispatch_semaphore_signal(_:dispatch_sempaphore_t) -> Int


let globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)

/**
 * Creates 3 theads, runs 2 senconds in total
[Thread1] dispatch_semaphore_t--
[Thread2] dispatch_semaphore_t--
[Thread3] dispatch_semaphore_t--
-------------------------- 2 seconds --------------------
[Thread1] Run after 2 seconds
[Thread2] Run after 2 seconds
[Thread3] Run after 2 seconds
*/
for _ in 0...2 {
    dispatch_async(globalQueue, {       // create 3 threads
        print("dispatch_semaphore_t--")
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(2 * NSEC_PER_SEC)), globalQueue) {
            print("Run after 2 seconds") 
        }
    })
}


/**
 * 
[Thread 1] dispatch_semaphore_t--
[Thread 2] dispatch_semaphore_t--
----------------------------------------------------- 2 sec --------
[Thread 1] Run after 2 seconds
[Thread 2] Run after 2 seconds 
*/
let semaphore =  dispatch_semaphore_create(2)  // dispatch_semaphore_t = 1
for _ in 0...2 {
    dispatch_async(globalQueue, {       // create 2 threads
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER)
        print("dispatch_semaphore_t--")
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(2 * NSEC_PER_SEC)), globalQueue) {
            print("Run after 2 seconds")            
        }
    })
}


/**
dispatch_semaphore_t--
Before: dispatch_semaphore_t++
After: dispatch_semaphore_t++
dispatch_semaphore_t--
----------------------------------------------2 sec-------------------------
Run after 2 seconds
Run after 2 seconds 
 */
let semaphore =  dispatch_semaphore_create(1)  // dispatch_semaphore_t = 1
for _ in 0...2 {
    dispatch_async(globalQueue, {       // create 2 threads
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER)
        print("dispatch_semaphore_t--")
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(2 * NSEC_PER_SEC)), globalQueue) {
            print("Run after 2 seconds")            
        }
    })
}
print("Before: dispatch_semaphore_t++")
dispatch_semaphore_signal(semaphore)
print("After: dispatch_semaphore_t++")





/*
semaphore--
semaphore--
semaphore--
Run after 2 seconds
Run after 2 seconds
Run after 2 seconds
Before: semaphore++
Before: semaphore++
Before: semaphore++
After: semaphore++
After: semaphore++
After: semaphore++
 */



/*
dispatch_semaphore_t--  
                    // semaphore = 0, block on creating [thread2]
------------------------------------------- 2 sec --------------------------
Run after 2 seconds
Before: dispatch_semaphore_t++
                    // semaphore = 1, [thread2] is going to be created
After: dispatch_semaphore_t++
dispatch_semaphore_t--

------------------------------------------- 2 sec --------------------------
Run after 2 seconds
Before: dispatch_semaphore_t++
After: dispatch_semaphore_t++
dispatch_semaphore_t--

------------------------------------------- 2 sec --------------------------
Run after 2 seconds
Before: dispatch_semaphore_t++
After: dispatch_semaphore_t++
 */
let semaphore =  dispatch_semaphore_create(1) // dispatch_semaphore_t = 1
for _ in 0...2 {
    dispatch_async(globalQueue, {       // create 3 threads
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER)
        print("dispatch_semaphore_t--")        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (Int64)(2 * NSEC_PER_SEC)), globalQueue) {
            print("Run after 2 seconds")
            print("Before: dispatch_semaphore_t++")
            dispatch_semaphore_signal(semaphore)
            print("After: dispatch_semaphore_t++")
        }
    })
}






