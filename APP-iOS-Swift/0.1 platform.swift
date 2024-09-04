/**
 * @available
 *  iOS, iOSApplicationExtension, OSX, OSXApplicationExtension, watchOS
 *  watchOSApplicationExtension, tvOS, tvOSApplicationExtension
 */
@available(iOS 8.0, OSX 10.10, *)
class Deprecate {
    
}



protocol Obsoleted {
}
protocol Previaling {
}
@available(*, unavailable, renamed="Previaling")
typealias Obsolted = Previaling
/**
 * os()  OSX, iOS, watchOS, tvOS, Linux
 * arch()   i386, x86_64, arm, arm64
 * swift()  >= $version
 */


if #available(iOS 9, OSX 10.10, *) {
  
} else {
  
}


/**
 * A `#selector` expression lets you access the selector used to refer to a method
 *  in Objective-C.
 */
class Parentheses: NSObject {
    @objc(disambiguate:)
    func signatures(x: Int) { }
}
let parentheses = Parentheses()
let selector = #selector(parentheses.signatures(_:))
/**
 * #file: String   the name of the file, __FILE__ for 2.1
 * #line: Int, __LINE__ for 2.1
 * #column: Int, __COLUMN__
 * #function: String, __FUNCTION__
 *  Inside a function, it's the name of that function
 *  Inside a method, it's the name of that method
 *  Inside a property getter or setter, it's the name of that property
 *  Inside init or subscript, it's the name of that keyword
 */

func eminent(utter: String = #function) {
    print("\(#file): \(#line) \(utter)")
}

func sheer() {
    eminent()           // print: sheer()
}