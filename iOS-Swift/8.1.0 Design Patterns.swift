/**
 * Singleton
 * OC or swift 1.2-
 *  class Feast {
 *      class var instance: Feast {
 *          struct Static {
 *              static var onceToken : dispatch_once_t = 0
 *              static var instance : Feast? = nil
 *          }
 *          dispatch_once(&Static.onceToken) {
 *              Static.instance = Feast()
 *          }
 *          return Static.instance!
 *      }
 *  }
 * The obvious port of dispatch_once to Swift is understandable but it seems *  verbose for a common pattern in a new language. It turns out that we 
 *  can construct a singleton using type properties in significantly less 
 *  code in Swift 1.2+:  `static let singleton = SingletonClass()`
 */
class Verbose {
    static let feast = Feast()
}
