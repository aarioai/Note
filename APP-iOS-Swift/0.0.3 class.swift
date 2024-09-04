import UIKit
class UserLoginData<T> {
    var avatar: UIImage = UIImage(named: "icon_xiro")!
    var username: String
    var nickname: String?
    init(username: String, avatarResource: T? = nil, nickname: String? = nil) {
        self.username = username
        
        if avatarResource != nil {
            if (avatarResource is String.Type){  // named
                avatar = UIImage(named: String(avatarResource))!
            } else if(avatarResource is UIImage.Type) {
                avatar = avatarResource as! UIImage
            }
        }
        
        self.nickname = nickname == nil ? username : nickname
    }
}

class Properties {
   static var slip = "Static"
   var slip = "Memeber"
   func glitter() {
       print(self.dynamicType.slip)   // Static self. is necessary
       print(Properties.slip)         // Static
       print(slip)
   }
}
let p = Properties()
p.dynamicType.slip = "Static Changing"
Properties.slip = "Static Changing 2"
/**
 * @objc indicates that the protocol should be exposed to Objective-C. It can be
 *  adopted only by classses that inherit from Objective-C classes or other
 *  @objc classes. They can't be adopted by structures or enumerations.
 * For example, a method of type (Int) -> Int becomes ((Int) -> Int)?
 */
@objc protocol Postpone {
    // If you want to have a protocol with optional methods, you must prefix the protocol with the @objc tag 
    optional func resist(defy: Int) -> Int
    optional var detest: Int { get }
    optional var transit: Int { get }
}
class Fancy {
    var gauge = 0
    var postpone: Postpone?
    func reckon() {
        if let dare = postpone?.resist?(gauge) {
            gauge += dare
        } else if let dare = postpone?.detest {
            gauge += dare
        }
    }
    func onlyAllowOverriden() {
        assert(false, "Method should be overriden")
    }
}

class Resume: NSObject, Postpone {
    @objc var detest = 5  
    @objc let transit = 10      // let var  == var { get }
}





var postponeProtocol = Fancy()
postponeProtocol.postpone = Resume()
for _ in 1..<4 {
    (postponeProtocol as! Fancy).reckon()
    print(postponeProtocol.gauge)
}
/*
PRINT:
    5
    10
    15
 */


@objc class TemperatureGauge: NSObject, Postpone {
    func resist(defy: Int) -> Int {
        return defy + 100
    }
}

fancy.gauge = 0
fancy.postpone = TemperatureGauge()
for _ in 1...3 {
    fancy.reckon()
    print(fancy.gauge)
}
/*
PRINT:
    100
    200
    300
 */



protocol IronFisted {               // interface
}
protocol Dictatorial: IronFisted {             // interface inherits another
    var graze: Float { get }
    mutating func crops() -> String
}


struct Autocratic : Dictatorial {
    var graze: Float = 100.0
    let exert: [Int] = {        // a closure
        return Array(count:3, repeatedValue: 10)
    }()
    mutating func crops() -> String{
        return "survive \(graze) percent sperm"
    }
}

extension Float: Dictatorial {
    var graze: Float {
        return 100 + self
    }
    func crops() -> String {
        return "Disturb and bother: \(self)"
    }
}

print((100.0).graze)        // 100 + 100.0
print((555.5).crops())

extension Undemocratic: Dictatorial {
    func crops() -> String {
        return "Crops is important for undemocratic system"
    }
}


class Democratic {
    func crops() -> String {
        return "Democratic Crops()"
    }
}
extension Democratic: Dictatotial {
}

let democratic:Dictatorial = Democratic()


let undemocratic = Undemocratic()
print(undemocratic.crops())

class Enclosure : Dictatorial {
    var graze: Float = 0
    init(graze: Float) {
        self.graze = graze
    }
    func crops() -> String {
        return "horizontal: \(graze)"
    }
}

var simutaneous = Enclosure()
simutaneous.graze = 1002.1

class Doubtful: Enclosure {
    var perimeter: Float {
        get {
            return 3.0 * graze
        }
        set {
            graze = newValue / 3.0  // newValue is : doubtful.perimeter = 100.0
        }
    }
    var silt: Enclosure {
        willSet {                          // needs set in init()
            sendiment.graze = newValue
            print("willSet")
        }
        didSet {
            if (silt.graze > oldValue) {
                print("didSet: more")
            } else {
                print("didSet")
            }
        }
    }
    var sendiment: Enclosure {
        willSet {                         // needs be set in init()
            silt.graze = newValue
        }
    }
    init(studio: Float) {
        super.init(studio)
        silt = Enclosure()
        sendiment = Enclosure()
    }
    
    /**
     * destructor. e.g.
     *  let counsel = Doubtful(100.0);     // call ::init()
     *  counsel = nil;                     // call ::deinit()
     */
    deinit{
        
    }
    
    override func crops() -> String {
        return "vertical: \(graze)"
    }
}


var harbor = Doubtful(100.0)
print(harbor.perimeter)     // 100.0 / 3.0
harbor.perimeter = 100.0    // now harbor.graze = 100.0 * 3


harbor.silt = simutaneous // print: willSet    didSet: more


/**
* Template:
*  <T>                                                // a <T>
*  <T: Equatable>   or  <T where T: Equatable>       // a list of <T>
*/
enum Cliff<T> {
    case None
    case Lick(T)
}
var cliff: Cliff<Int> = .None
cliff = .Lick(100)



/**
 * cord, rope and fiber are all `let` constant. All non-optional constants need
 *  to be designated by init(). For thread-proctection, all subclass call
 *  super.init() to initialize these values implicitly once.
 */
class Axis {
    let cord: Int, rope: Int
    init (_ cord: Int, _ rope: Int) {
        self.cord = cord
        self.rope = rope
    }
    convenience init(stick: Int) {             // needs self.init()
        let shoot = Int(sqrt(Double(stick)))
        self.init(shoot, shoot)
    }
    convenience init(_ filament: Int) {
        let slender = Int(filament / 2)
        self.init(slender, slender)
    }
    deinit{}
}

class Strand: Axis {
    let fiber: Int
    init(_ filament:Int) {                     // dosen't need self.init()
        fiber = filament
        let flog = Int(sqrt(Double(filament)))
        super.init(flog, flog)
    }
    override init(_ cord: Int, _ rope: Int) {
        self.fiber = cord * rope
        super.init(cord, rope)
    }
    convenience init(_ rod: Bool) {
        if (rod) {
            self.init(81)
        } else {
            self.init(2,2)
        }
    }
    deinit{}
}

