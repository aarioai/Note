/**
 * @see https://developer.apple.com/library/ios/documentation/UIKit/Reference/UIKitFunctionReference/#//apple_ref/c/func/UIGraphicsBeginImageContextWithOptions
 */

/**
 * Create a bitmap-based graphics context
 * @example
    let imgOrigin = UIImage(named: "Aario.png")     // 2240 * 1500
    let imgSize = CGSize(width:180, height:180)
    UIGraphicsBeginImageContextWithOptions(imgSize, false, 1.0)
    imgOrigin.drawinRect(CGRect(origin: CGPointZero, size: imgSize))
    let imgContext = UIGraphicsGetCurrentContext()
    UIGraphicsEndImageContext()
    if let imgRef: CGImageRef = CGBitmapContextCreateImage(imgContext) {
        let img = UIImage(CGImage: imgRef, scale: 1, orientation: .Up)
        UIImageWriteToSavedPhotosAlbum(img, nil, nil, nil) 
    }
 *  
 */ 
UIGraphicsBeginImageContextWithOptions(_:CGSize, _ opaque:Bool, _ scale)
UIGraphicsGetImageFromCurrentImageContext()
UIGraphicsGetCurrentContext() -> CGContext?

# Image and Movie Saving
UIImageWriteToSavedPhotosAlbum(_:UIImage, _ completionTarget: AnyObject?,
                               _ completionSelector: Selector,
                               _ contextInfo: UnsafeMutablePointer<Void>)
