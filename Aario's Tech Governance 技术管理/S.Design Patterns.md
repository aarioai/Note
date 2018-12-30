## Category
*   [Singleton](#Singleton)     单例模式
*   [Delegate](#Delegate)       委托模式
*   [Proxy](#Proxy)             代理模式
*   [Command](#Command)         命令模式
*   [Mediator](#Mediator)       中介模式
*   
# Delegate <a id="Delegate"></a>


# Proxy <a id="Proxy"></a>
```
[Client]  ~~~~> [<Protocol>.doActions()]  ◅-------[instance.doActions()]
                        △                               ∧
                        |                               |
                        |                               |
                ［Proxy.doActions()] --------------------+
```


# Command <a id="Command"></a>
```
[Client] ----> [Receiver.actions()] <------- [ConcreteCmd.cmds()]
                                                    |
                                                    ▿
                   [Invoker.call()]◇------> [AbstractCmd.cmds()]

```
```swift
protocol SwitchCommand {        // AbstractCmd
    func execute()
}

class SwitchOnCommand : SwitchCommand {     // ConcreteCmd
    let equipment: String!
    required init(_ equipment: String) {
        self.equipment = equipment
    }
    func execute() {
        print("Switch On")
    }
}

class SwitchOffCommand : SwitchCommand {    // ConcreteCmd
    let equipment: String!
    required init(_ equipment: String) {
        self.equipment = equipment
    }
    func execute() {
        print("Switch Off")
    }
}

class Random1000Controller {       // Invoker
    let switchOnCmd: SwitchCommand!
    let switchOffCmd: SwitchCommand!
    init(_ equipment: String) {
        switchOnCmd = SwitchOnCommand(equipment)
        swithOffCmd = SwitchOffCommand(equipment)
    }
    func switchOn() {
        switchOnCmd.execute()
    }
    func switchOff() {
        switchOffCmd.execute()
    }
    
}

let equipment = "electric razor"    // receiver
let controller = Random1000Controller(equipment)        // Invoker
controller.switchOn()   // Invoker.call()
controller.switchOff()  // Invoker.call()


```
# Mediator <a id="Mediator"></a>
The mediator pattern is used to reduce coupling between classes that communicate with each other. Instead of classes communicating directly, and thus requiring knowledge of their implementation, the classes send messages via a mediator object.

```swift

```
