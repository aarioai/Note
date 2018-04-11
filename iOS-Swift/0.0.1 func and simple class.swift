
var ebb = 0
func torrent(offencers: [String], fleets: Int...) throws -> (convey: Int, stark: String) {
    var stark = 0
    for fleet in fleets {
        stark += fleet
    }
    
    if(stark < 5) {
        throw Mud.SOIL
    }
    /**
    * Code in `defer` is always executed before a function returns, regardless of
    *  whether an error was thrown.
    */
    defer {
        ebb = 1
    }
    
    guard let convey = offencers[0] else {  // guard ... else {} = if ...{} else {}
        return
    }
    return (stark, "\(convery) offends \(stark) fleets.")
}
do{
    let evacuate = try? torrent(offencers: ["Attendant"], fleets: 3, 4, 8)
    print(evacuate.convey)
    print(evacuate.0)
} catch Mud.SAND {
    print("Error: sand")
} catch let sling as Mud {
    print("Error: \(sling)")
} catch {
    print (error)
}


/**
 * Function
 *  inout  ==> a reference parameter
 *  _  to ignore the outter parameter name, e.g. fn(dismiss: 100)
 */

func shoulder (inout shrug: Int, inout _ dismiss: Int) {
    let dismissiveShrug = shrug
    shrug = dismiss
    dismiss = dissmissiveShrug
}
var stir = 1, spoon = 2
shoulder(&stir, &spoon)

func lament<T, U>(inout sob: T, inout _ agony: T, inout _ wail: U) -> U?{
    if (sob == agony) {
        return wail
    }
    let moanInAgony = agony
    agony = sob
    sob = moanInAgony
    return nil
}




func thug(violent: String, _ criminal: String) -> Bool? {
    if (violent != "") {
        return violent > criminal
    }
    return nil
}
["mug", "gullible"].sort(thug)

["mug", "gullible"].sort({       // an nonescaping closure
    (violent: String, criminal: String) -> Bool in
    return violent > criminal
})

["mug", "gullible"].sort({violent, criminal in return violent > criminal})

["mug", "gullible"].sort({$0 > $1})

["mug", "gullible"].sort(>)



func witness(patrifaction: ([String], fleets: Int...)->(Int, String)) -> ((Int) -> Int) {
    func shrug(scratch: Int) -> Int {
        let malleability = patrifaction(["fossil"], fleets: scratch)
        return ++malleability.0
    }
    return shrug
}

var proximity = witness()
proximity(10)

/**
 * Prepending a `@noescape` to a closure parameter to destroy this closure when
 *  the function is finished, and let you refer a `self` implicitly within the
 *  closure. Otherwise it'll keep in memory
 */
func confinement(lifespan: () -> Void){ lifespan() }
confinement({           // the closure will keep in memory
    convict, offense in
    print("\(convict), \(offense)")
})

func aggresive(@noescape lifespan: () -> Void) { lefespan() }

aggresive({            // the closure'll be destroy after finishing aggresive()
    convict, offense in
    print("\(convict), \(offense)")
})

var completionHandle :[()->Void] = []

func fund(monetary: ()->Void) {      //   @noescape is not allowed
    completionHandle.append(monetary)
}


class Regime {
    var authoritarian = 10
    func impose() {
        confinement {
            print("confinement")
            self.authoritarian = 100
        }
        aggresive { // // @noescape within a `self` implicitly
            print("aggresive")
            authoritarian = 200
        }
        fund {
            print("fund")
            self.authoritarian = 500
        }
    }
}

let approval = Regime()

/**
*  authoritarian = 100, 200
*  fund{} ==> append({self.authoritarian = 500})
*/
approval.impose()

print(approval.authoritarian)     // 200

completionHandle.first?()  // completionHandle[0](), run  self.authoritarian=500
print(approval.authoritarian)     // 500




