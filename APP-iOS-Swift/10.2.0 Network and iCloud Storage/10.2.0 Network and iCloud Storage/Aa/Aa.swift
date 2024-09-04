import UIKit
import Gifu
import Haneke

enum HttpMethod : Int {
    case GET
    case POST
    case PUT
    case PATCH
    case DELETE
}
struct URLParamStruct <T> {
    var key: String
    var value: T? = nil
    //static let dataType =
    var regexp: String?
    var required: Bool
    init(key: String, required: Bool, regexp: String? = nil, defaultValue: T? = nil) {
        self.key = key
        self.regexp = regexp
        self.required = required
        self.value = defaultValue
    }
}

class Aa {
    
    
    private static let notifierSingleton = Notifier()            // singleton
    private static let converterSingleton = Converter()
    
    static func notifier() -> Notifier {
        return notifierSingleton
    }
    static func converter() -> Converter {
        return converterSingleton
    }
    
    // third-party libraries
    static func sweetAlert() -> SweetAlert {
        return SweetAlert()
    }
    static func animatableImageView() -> AnimatableImageView {
        return AnimatableImageView()               // Gifu
    }
    

}