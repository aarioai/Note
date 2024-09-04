import UIKit
import Gifu
import Haneke


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