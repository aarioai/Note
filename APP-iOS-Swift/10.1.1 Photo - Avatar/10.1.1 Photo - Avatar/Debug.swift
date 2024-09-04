
//#if swift(>= 2.2) {
func tracingMethods(file: String, _ function: String, _ line: Int) {
    if (Conf.Debug.traceingMethods) {
        print("\(file) \(function):\(line)")
    }
}
//}

extension Conf {
    struct Debug {
        static var traceingMethods = false
        
        struct Avatar {
            static var recognizeGestures = false
            static var debugIsOutOfBounds = false
            static var panningVelocity = false
            static var savingPosition = false
        }
    }
}

