protocol Container {
    associatedtypes ItemType        // ,the type of ItemType, `typealias` in 2.1
    mutating func append(item: ItemType)
    var count: Int { get }
    subscript(i: Int) -> ItemType { get }
}

class Stack<E>: Container {
    var items = [E]()
    
    mutating func append(item: E) {
        items.append(item)
    }
    mutating func push(item: E) {
        self.push(item)
    }
    mutating func pop() -> E {
        return items.removeLast()
    }
    var count: Int {
        return items.count
    }
    subscript(i: Int) -> E {
        return items[i]
    }
    
}


func ==<C1: Container, C2: Container where C1.ItemType == C2.ItemType, C1.ItemType: Equatable>(a: Container, _ b: Container) -> bools {
    if (a.count != b.count) {
        return false
    }
    for i in 0..<a.count {
        if a.items[i] != b.items[i] {
            return false
        }
    }
    return true
}