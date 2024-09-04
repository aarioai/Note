/**
 * Notify
 *  alert    =  error | success
 *  error
 *  success
 */

import UIKit

enum NotificationStyle : Int {
    case Alert          // Warning
    case Error
    case Success
}
class Notifier {
    
    func alert(title: String? = nil, message: String?, style: NotificationStyle = .Alert, action: (() -> Void)? = nil) {
        Aa.sweetAlert().showAlert(message!)
        if (action != nil) {
            action!()
        }
    }
    
    func error(title: String? = nil, message: String?, style: NotificationStyle = .Error, action: (() -> Void)? = nil) {
        Aa.sweetAlert().showAlert(message!)
        if (action != nil) {
            action!()
        }
    }
    
    func success(title: String? = nil, message: String?, style: NotificationStyle = .Success, action: (() -> Void)? = nil) {
        if title == nil {
            Aa.sweetAlert().showAlert(message!, subTitle: nil, style: .Success)
        } else {
            Aa.sweetAlert().showAlert(title!, subTitle: message, style: .Success)
        }
        if (action != nil) {
            action!()
        }
        //
        //        let alert = UIAlertController(title: "", message: "Saved", preferredStyle: .Alert)
        //        let alertAction = UIAlertAction(title: "OK", style: .Default, handler: {
        //            alertAction in
        //            action!()
        //
        //        })
        //
        //        alert.addAction(action)
        //        presentViewController(alert, animated: true, completion: nil)
        //        
        //
    }
    
    
    
}