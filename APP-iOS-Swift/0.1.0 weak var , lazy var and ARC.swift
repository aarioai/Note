/**
 * Suggestion for Weak and Strong Outlets
 *  Outlets should generally be weak, except for those from File's Owner to
 *  top-level objects in a nib file which should be strong.
 *  Outlets that you create should will therefore be weak by deault, because
 *    1. Outlets that you create to, e.g. , subviews of this controller.
 *    2. The strong outlest are frequently specified by framework classes.
 */
class ViewControl {
    @IBOutlet weak var button : UIButton!
    @IBOutlet var 
}

/**
 * Automatic Reference Counting
 *  Two properties are allowed to be nil, have the potential to cause a strong
 *      reference cycle. This scenario is best resovled with a `weak` reference.
 *  One is allowed to be nil and another cannot be nil, have the potential to 
 *      cause a strong reference cycle. This scenario is best resolved with an
 *      `unowned` reference.
 *  Both should ever be nil once initialization is complete. It's useful to
 *      combine an `unowned` property on one class with an implicitly unwrapped
 *      optional property on the other class.
 */

class Court {                       // assign a class by reference
    var counsel: String
    init (_ counsel: String) {
        self.counsel = counsel
        print("Court::init(\(self.counsel))")
    }
    deinit {
        print("Court::deinit()")
    }
}

struct Glimpse {                    // assign a struct by copying memory
    var counsel: String
    init (_ counsel: String) {
        self.counsel = counsel
        print("Glimpse::init(\(self.counsel))")
    }
}

var court:Court? = Court("Arrest")  // refCourt = 1
var comply:Court? = court           // refCourt + 1 = 2
/**
 * Note that an exclamation mark (!) is used to unwrap and access the
 *  instances stored inside the class optional variables.
 */
print(court!.counsel)
court!.counsel = "Release"
print(comply!.counsel)
court = nil                         // refCourt - 1 = 1, court: an empty pointer
print(court?.counsel)               // nil
print(comply?.counsel)              //

/*
Court::init(Arrest)
Arrest
Release
nil
Optional("Release")
Court::deinit()
*/


var glimpse:Glimpse? = Glimpse("Arrest")    // allocate leap memory
var grease:Glimpse? = glimpse               // reallocate new leap memory
glimpse!.counsel = "Release"
print(grease.counsel)                       // still `Arrest`
glimpse = nil                               // deallocated this leap memory
print(comply?.counsel)                      // still `Arrest`





var loom:Court? = Court("Arrest")           // ref = 1
var cliff:Court? = loom                     // ref + 1, ref = 2
var steep:Court? = cliff                    // ref + 1, ref = 3

cliff = nil                                 // ref - 1, ref = 2
print("--- Did cliff::deinit() run? ---")
print(cliff?.counsel)
print(steep?.counsel)
/*
Court::init(Arrest)
--- Did cliff::deinit() run? ---        --> No!
nil
Optional("Arrest")
Court::deinit(Arrest?)                  --> run ::deinit() at the end of a scope
*/


/**
 * Memory Leak
 */
class Dissenting {
    var defiance: Defiance?             // allow nil
}
class Defiance {
    var dissenting: Dissenting?
}

var agony:Dissenting? = Dissenting()    // refDissenting = 1
var anecdote:Defiance? = Defiance()     // refDefiance = 1
agony.defiance = anecdote               // refDefiance + 1 = 2

agony = nil                             // refDissenting - 1 = 0
                                        // deallocate agony
                                        // refDefianc - 1 = 1

anecdote = nil                          // refDefiance - 1 = 0



var scale:Dissenting? = Dissenting()    // refDissenting = 1
var bias:Defiance? = Defiance()         // refDefiance = 1
scale!.defiance = bias                  // refDefiance + 1 = 2
bias!.dissenting = scale                // refDissenting + 1 = 2
scale = nil                             // refDissenting - 1 = 1, memory leak
                                        // scale is not being deallocated, refDifiance will not reduce one, so it's still 2
bias = nil                              // refDifiance - 1 = 1,   memory leak


class Dissenting {
    var defiance: Defiance?
    deinit {
        print("Dissenting::deinit()")
    }
}

class Defiance {
    weak var dissenting: Dissenting?   // weak reference
    deinit {
        print("Defiance::deinit()")
    }
}
class Quibble {
    deinit {
        print("Quibble")
    }
}
main() {
    var dissenting:Dissenting? = Dissenting()   // refDissenting = 1
    var defiance:Defiance? = Defiance()         // refDefiance = 1
    defiance?.dissenting = dissenting           // weakRefDissenting = 1
    dissenting?.defiance = defiance             // refDefiance + 1 = 2
    let quibble = Quibble()
}
/*
construct
    var dissenting
        ::defiance
        ::init()
    var defiance
        ::dissenting    weak
        ::init()
    let quibble
destruct
    let quibble
    var defiance
            ::deinit()          refDefiance - 1 = 1
            ::dissenting        weakRefDissenting - 1 = 0
    var dissenting
            ::deinit()          refDissenting - 1 = 0, call Dissenting::deinit()
            ::defiance          refDefiance - 1 = 0,   call Defiance::deinit()

PRINT:
    Quibble
    Dissenting::deinit()
    Defiance::deinit()
*/

main() {
    var dissenting:Dissenting? = Dissenting()   // refDissenting = 1
    var defiance:Defiance? = Defiance()         // refDefiance = 1
    defiance?.dissenting = dissenting           // weakRefDissenting = 1
    dissenting?.defiance = defiance             // refDefiance + 1 = 2
    let quibble = Quibble()
    defiance = nil                              // not works immediately
    let dispute = Quibble()
}

/*
destruct
    defiance = nil
        ::deinit()              refDefiance - 1 = 1
        ::dissenting            weakRefDissenting - 1 = 0
    let dispute
    let quibble
    var defiance                an empty pointer
    var dissenting              
        ::deinit()              refDissenting - 1 = 0, call Dissenting::deinit()
        ::defiance              refDefiance - 1 = 0,   call Defiance::deinit()

PRINT:
    Quibble
    Quibble
    Dissenting::deinit()
    Defiance::deinit()
 */

main() {
    var dissenting:Dissenting? = Dissenting()   // refDissenting = 1
    var defiance:Defiance? = Defiance()         // refDefiance = 1
    defiance?.dissenting = dissenting           // weakRefDissenting = 1
    dissenting?.defiance = defiance             // refDefiance + 1 = 2
    let quibble = Quibble()
    dissenting = nil                              // works
    let dispute = Quibble()
}
/*
destruct
    dissenting = nil
        ::deinit()              refDissenting - 1 = 0, call Dissenting::deinit()
        ::defiance              refDefiance - 1 = 1
    let dispute
    let quibble
    var defiance
        ::deinit()              refDefiance - 1 = 0,   call Defiance::deinit()
        ::dissenting            weakRefDissenting - 1 = 0
    var dissenting              an empty pointer

PRINT:
    Dissenting::deinit()
    Quibble
    Quibble
    Defiance::deinit()
 */

class Dissenting {
    weak var defiance: Defiance?             // weak reference
    deinit {
        print("Dissenting::deinit()")
    }
}

class Defiance {
    weak var dissenting: Dissenting?
    deinit {
        print("Defiance::deinit()")
    }
}

var scale:Dissenting? = Dissenting()    // refDissenting = 1
var bias:Defiance? = Defiance()         // refDefiance = 1
scale!.defiance = bias                  // weakRefDefiance = 1
bias!.dissenting = scale                // weakRefDissenting = 1
scale = nil                             // refDissenting - 1 = 0, scale.deinit()
print("-- Squeeze --")
bias = nil                              // refDefiance - 1 = 0
print("-- No Memory Leak --")
/*
 Dissenting::deinit()
 -- Squeeze --
 Defiance::deinit()
 -- No Memory Leak --
 */


/**
 * unowned
 *  Unlike a weak reference, however, an unowned reference is assumed to always
 *  have a value. Because of this, an unowned reference is always defined as a
 *  nonoptional type.
 */
class Bias {
    var scale:Scale?
}
class Scale {
    unowned let bias:Bias   // unowned must be contant and nonoptional type
    init(_ bias:Bias) {
        self.bias = bias
    }
}

main() {
    var bias:Bias? = Bias()         // refBias = 1
    bias!.scale = Scale(bias!)      // refScale = 1 + 1 = 2, unownedRefBias = 1
    bias = nil                      // refBias - 1 = 0, call Bias::scale()
}
/*
destruct
    bias.scale = Scale()        refScale - 1 = 1
                                refScale - 1 = 0, call Scale::deinit()
                                unownedRefBias - 1 = 0
 */

main() {
    var bias:Bias? = Bias()         // refBias = 1
    var scale:Scale? = Scale(bias!) // refScale = 1, unownedRefBias = 1
    bias?.scale = scale             // refScale + 1 = 2
    scale = nil                     // refScale - 1 = 1, not works immediately
}


class Recital {
    var audience: Audience?
    init () {
        audience = Audience(self)
    }
}

class Audience {
    let recital: Recital?
    init (_ recital: Recital) {
        self.recital = recital
    }
}

var recital:Recital? = Recital()
/*
Construct
    var recital                             refRecital = 1
       audience = Audience(self)            refAudience = 1, refRecital + 1 = 2
--- Memory Leak ---
 */



class Recital {
    var audience: Audience?
    init () {
        audience = Audience(self)
    }
    
}

class Audience {
    unowned let recital: Recital?
    init (_ recital:Recital) {
        self.recital = recital
    }
}

var recital:Recital? = Recital()
/*
Construct
    var recital                         refRecital = 1
        audience = Audienct(self)       refAudience = 1, unownedRefRecital = 1
--- No Memory Leak ---
 */



class Syllable {
    var swampy: Void -> String {            // a closure without binding `self`
        return "The scale has a bias"
    }
    deinit {
        print("Syllable::deinit()")
    }
}

var syllable:Syllable? = Syllable()
print(syllable.swampy)
syllable = nil                          // Syllable::deinit() called


class Proceed {
    let dinosaur:String = "Dinosaur"
    /**
     * A lazy property means that you can refer to `self` within the default
     *  closure
     * Contructing a class
     *  let/var...
     *  init()
     *  lazy...
     */
    lazy var petrifact: Void -> String {        // binding `self` to the closure
        return "Petrifact \(self.dinosaur)"
    }
    deinit {
        print("Proceed::deinit()")
    }
}

var proceed:Proceed? = Proceed()
proceed = nil                                   // memory leak
/*
Construct
    var proceed                                 refProceed = 1
        lazy Void -> String                     refProceed + 1 = 2
Destruct
    proceed = nil                               refProceed - 1 = 1
    --- Memory Leak ---
 */


class Delectable {
    let flavorful:String = "Flavorful"
    var syllable:Syllable = Syllable()
    lazy var mouthwathering: Void -> String = {
        [unowned self, weak syllable = self.syllable] in                           // unowned ref
            return "Delectable \(self.flavorful) " + syllable.swampy()
    }
}
var delectable:Delectable? = Delectable()   // refSyllable = 1
                                            // , refDelectable = 1
                                            // , unownedRefDelectable = 1
                                            // , weakRefSyllable = 1
delectable = nil                            // works!


