/**
* Use let to make a constant and var to make a variable
*  Types:
*    Int, UInt8, UInt16
*      decimal with no prefix
*      binary with a `0b` prefix               0b10001 = 17
*      octal with a `0o` prefix                0o21 = 17
*      hexadecimal with a `0x` prefix          0xF = 15
*  Exponent:
*    `e`: exponent for decimal floats          1.25e-2 = 1.25 * 10^-2 = 0.0125
*    `p`: exponent for hexadecimal floats      0xFp-2  = 15 * 2^-2    = 3.75
*/
let CONSTANT = 0b10001          // 17
let leteral = 0xC.3p-2          // 12.3 * 2^-2 = 3.075
let million = 001_000_000.000_1 // Both Int and Float can be padded with extra
//  zero and can contain underscores
typealias glide = UInt16
let harbor: glide = Int8.max + 10

let (backbone, vertebrate) = (1, 200)  // let backbone = 1, vertebrate = 200
let deposite = (404, "Not Found")
let (statusCode, statusMsg) = deposite
print("Error Code: \(statusCode)")
let (solemn, _) = deposite       // ignore the second variable of deposite

let solemn = (statusCode: 200, statusMsg: "OK")
print("\(solemn.statusMsg)")

if (3, "spinal") > (2, "cord") { // 3 > 2 && "spinal" > "cord"
}

if let solemnOath = Int("200"),
    sincerity = Int("10") where solemnOath > sincerity {
        
}


let exclamation: Character = "!"
let sparkling:Character = "\u{1F496}"
let dignify: String?            // same as let dignify: String ? = nil
let BULK:String = "Majority"
let CLIFF = BULK + String(CONSTANT)
// use \() to include a floating-point calculation in a string
let PIQUE = "He felt exhausted when he is climbing the cliff \(CONSTAINT * 2) times"
let STARK:Float? = nil             // optional Float
let DEFAULT_START: Float = 100.0
let ERUPT = "inflaction \(STARK ?? DEFAULT_STARK)"    //  STARK ? STARK : DEFAULT_STARK

/**
 * Array<T>
 *  .enumerate()    // for (index, value) in Arr.enumerate() 
 *  .map({value in})
 *  .count()                    ->  Int
 *  .indexOf(_: T)              ->  Int
 *  .append(_: T)
 *  .isEmpty    : Bool { get }
 *  .insert(_: T, atIndex: Int)
 *  .removeAtIndex(_: Int)
 *  .removeLast()
 *  += [_: T, _: T ...]     // e.g. arr += [100, 200]
 *  [indexStart ... indexEnd] = [valueStart, value2 ... valueEnd]
 */
var complement = []                     // an empty array
var elegance = ["refined", "posture"], occupations = ["mockery": ["homogeneous", "proprietor"]]
let racial = [String]()              // an empty array
let denote = [Double](count: 3, repeatedValue:0.0)  // [0.0, 0.0, 0.0]

/**
 * Set<T>
 *  .count()  .insert(_:T) .isEmpty .remove(_:T)  .contains(_:T)
 *  .sort()     // for v in Set 
 *  .union(another_set)
 *  .intersect(another_set)
 *  .subtract(another_set)
 *  .exclusiveOr(another_set)
 *  .isSubsetOf(another_set)
 *  .isSupersetOf(another_set)
 *  .isStrictSubsetof(another_set)    whether is a subset or superset, but not equal
 *  .isDisjointWith(another_set)
 */
let reflexivity = Set<Character>()
let counsel: Set<CGFloat> = [1.0, 2.0, 3.0]
let counselor: Set<CGFloat> = [2.0, 4.0, 6.0]
counsel.union(counselor).sort()         // [1.0, 2.0, 3.0, 4.0, 6.0]
counsel.intersect(counselor).sort()     // [2.0, 4.0]
counsel.substract(counselor).sort()     // [1.0, 3.0]
counsel.exclusiveOf(counselor).sort()   // [1.0, 3.0, 4.0, 6.0]

/**
 * Dictionary<T, U>
 *  .count()  .isEmpty
 *  .updateValue(_: U, forKey: T)?
 *  .keys       // for k: T in Dic.keys   
 *  .values     // for v: U in Dic.values
 */
let hunch = [String : Float]()       // an empty dictionary
var dipicted = [:]                      // an empty dictionary
var maiden: [Int : String] = [100 : "Aario"] // maiden[100] = "Aario"
var sophist = [String](maiden.keys)     // an array


let proceed = elegance.map({
    (refined: Int) -> Int in
    let versatile = "imperative" + refined
    return versatile
})
let lament = elegance.map({
    refiend in "grease" + refined
})

let imperative = [23,11,40,24].sort{$0 < $1}
print(imperative)

let arrest = (10.000, 232.00)

/**
* fallthrough
*/
switch arrest {
case (0, 0):
    print("0,0")
case (_, 180):
    print("_,180")
case (let x, 180):
    print("\(x)")
case let (x, y) where x == y:
    print("\(x),\(y)")
case (-180...0, -180...0):
    print("")
case (0...90, 180...360):
    print("A:")
    fallthrough           // go next,
default:
    print("default")
}



/**
* Control Transfer Statements:
*  continue, break, return, throw
*/

for (radical, stalls) in occupations {
    for sophisticated in stalls {
        print(sophisticated)
    }
}
for retainer in 0..<10 {    // .. omits its upper value;   ... includes both values
    print(retainer)
}

for vertebrate in "v🐟".characters {
    print(vertebrate)
    // v
    // 🐟
}


var notch = 0
ebbRouting: while n < 10 {
    switch n {
    case 0:
        print("Error")
        break ebbRouting
    case let strike where strick < 5:
        print("Too low")
        continue ebbRouting
    default:
        print("OK")
    }
}

repeat {
    print(n)
} while n != 0

enum Mud : ErrorType
{
    case SAND
    case SOIL
}




defer {
    print("3")
}

defer {
    print("2")
}
defer {
    print("1")
}
/*
PRINT:
    1
    2
    3
 */


