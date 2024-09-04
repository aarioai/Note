/**
 * @see https://developer.apple.com/library/ios/documentation/UIKit/Reference/UIKit_Framework/
 * Setting status bar tint color
 *  1. Add `View controller-based status bar appearance` in info.plist
 *  2. UIApplication.sharedApplication().statusBarStyle = .LightContent 
 */

/**
 * 
 */

color: UIColor
alpha: CGFloat  0.0...1.0
UIImageResizingMode {Titl,Stretch}
UIViewTintAdjustmentMode {Automatic,Normal,Dimmed}
UIViewContentMode {ScaleToFill,ScaleAspectFit, ScaleAspectFill, Redraw,
                   Center,Top,Bottom,Left,Right,TopLeft,TopRight,BottomLeft,
                   BottomRight}



NSObject
#   UIResponder
##  UIApplication
enum UIInterfaceOrientation : Int {
    Unknown
    Portrait
    PortraitUpsideDown
    LandscapeLeft
    LandscapeRIght
}
struct UIInterfaceOrientationMask : OptionSetType {
    Portrait
    LandscapeLeft
    LandscapeRight
    PortraitUpsideDown
    Landscape
    All
    AllButUpsideDown
}
/*
Prevent autorotate

class ViewController {
    override func shouldAutoroate() -> Bool { return false }
    override func supportInterfaceOrientations() -> UIInterfaceOrientationMask {
        return .Portrait
    }
}
 */

    .sharedApplication() -> UIApplication   // the singleton app instance
    .delegate: UIApplicationDelegate?
    .keyWindow: UIWindow? { get }
    .windows: [UIWindow] { get }
    .applicationState: UIApplicationState { get }
    // App Appearance
    .statusBarFrame: CGRect { get }     // status bar
    .statusBarOrientationAnimationDuration: NSTimeInterval { get }
    .networkActivityIndicatorVisible: Bool
    .applicationIconBadgeNumber: Int
    .userInterfaceLayoutDirection: UIUserInterfaceLayoutDirection { get }
    preferredContentSizeCategory: String { get }
    
##  UIView : UIReponder
struct UIViewAnimationOptions : OptionSetType {
    LayoutSubViews,             // animated along with parent

    /**
     * 
     */
    AllUserInteraction,
    BeginFromCurrentState,      
    Repeat,
    Autoreverse,
    OverrideInheritedDuration,
    OverrideInheritedCurve,
    AllowAnimatedContent,
    ShowHideTransitionViews,
    OverrideInheritedOptions,
    CurveEaseInOut,
    CurveEaseIn,
    CurveEaseOut,
    CurveLinear,
    TransitionNone,
    TransitionFlipFromLeft,
    TransitionFlipFromRight,
    TransitionCurlUp,
    TransitionCurlDown,
    TransitionCrossDissolve,
    TransitionFlipFromTop,
    TransitionFlipFromBotton
}
struct UIViewAutoresizing : OptionSetType {
    None,FlexibleLeftMargin,FlexibleWidth,FlexibleRightMargin,FlexibleTopMargin,
    FlexibleHeight,FlexibleBottomMargin
}
struct UIViewAnimationCurve : Int {
    EaseInOut,EaseIn,EaseOut,Linear
}
    .init(frame: CGRect)
    .backgroundColor
    .hidden
    .alpha
    .opaque
    .tintColor
    .tintAdjustmentMode
    .clipsToBounds
    .clearsContextBeforeDrawing
    .maskView
    .layer
    .layClass()
    // Configuring the Event-Related Behavior
    .userInteractionEnabled: Bool
    .multipleTouchEnabled: Bool
    .exclusiveTouch: Bool

    // Conguring the Bounds and Frame Rectagles
    .frame: CGRect
    .bounds: CGRect
    .center: CGPoint
    .transform: CGAffineTransform

    // Managing the View Hierarchy/ˈhaɪərɑ:rki/
    .superview
    .subviews
    .window
    .addSubview(_:)
    .insertSubview(_:, [atIndex: Int | aboveSubview: | belowSubview:])
    .exchangeSubviewAtIndex(_ idx1: Int, withSubviewAtIndex idx2:Int)
    .bringSubviewToFront(_:)
    .sendSubviewToBack(_:)
    .removeFromSuperview()
    .isDescendantOfView(_:) -> Bool

    // Configuring the Resizing Behavior
    .autoresizingMask: UIViewAutoresizing
    .autoresizesSubviews: Bool
    .contentMode: UIViewContentMode
    .sizeThatFits(_:)
    .sizeToFit()
    
    // Laying out Subviews
    .layoutSubviews()
    .setNeedsLayouts()
    .layoutIfNeeded()
    .requiresConstraintBasedLayout()
    .translatesAutoresizingMaskIntoConstraints
    
    // Creating Constraints Using Layout Anchors
    .bottomAnchor
    
    // Aligning Views in Auto Layout

    // Drawing and Updating the View
    .drawRect(_:)
    .setNeedsDisplay()
    .setNeedsDisplayInRect(:_)
    .contentScaleFactor
    .tintColorDidChange()
    
    // Managing Gesture Recognizers
    .addGestureRecognizer(_:UIGestureRecoginzer)
    .removeGestureRecognizer(_:UIGestureRecognizer)
    .gestureRecognizers: [UIGestureRecoginzer]?
    .gestureRecognizerShouldBegin(_:UIGestureRecoginzer)

    .clipsToBounds
    .clearsContextBeforeDrawing
    .maskView
    .layer: CALayer { get }
    .layerClass()

    // Animating Views
    .animateWithDuration(_ duration: NSTimeInterval  // in seconds
                          [, delay: NSTimeInterval]   // in seconds
                          [, :UIViewAnimationOptions]
                          animations: () -> Void
                          [, completion: ((Bool) -> Void?)]
    /**
     * usingSpringWithDamping
     *  1 no oscillation, to zero increase oscillation
     * initialSpringVelocity = total distance / velocity (as you want)
     *  For smooth start to the animation. E.g. If the distance is 100,
     *  and you want to match a view of velocity 50pt/s, use a value 0.5
     */
    .animateWithDuration(_ duration, delay
                         , usingSpringWithDamping: CGFloat
                         , initialSpringVelocity: CGFloat
                         , options: UIViewAnimationOptions,
                         , animations
                         , completion)

    // Configuring the Resizing Behavior
    .autoresizingMask: UIViewAutoresizing   //the resize way to fit superview's
    .autoresizesSubviews: Bool              // whether resize subviews
    .sizeToFit()

    // Observing Focus
    .canBecomeFocused() -> Bool
    .focused : Bool { get }
    .inheritedAnimationDuration() -> NSTimeInterval
    
### UITableViewCell : UIView : UIResponder
enum UITableViewCellStyle : Int { Default, Value1, Value2, Subtitle }

    .init(:UITableViewCellStyle, reuseIdentifier: String?)

### UIControl : UIView : UIResponder
UIControlContentVerticalAlignment {Center,Top,Bottom,Fill}
UIControlContentHorizontalAlignment {Center,Left,Right,Fill}
struct UIControlEvents: OptionSetType {
    init(rawValue: UInt)
    TouchDown
    TouchDownRepeat
    TouchDragInside
    TouchDragOutside
    TouchDragEnter
    TouchDrageExit
    TouchUpInside
    TouchUpOutside
    TouchCancel
    ValueChanged
    PrimaryActionTrigged
    EditingDidBegin
    EditingChanged
    EditingDidEnd
    EditingDidEndOnExit
    AllTouchEvents
    AllEditingEvents
    ApplicationReserved
    SystemReserved
    AllEvents
}
struct UIControlState: OptionSetType {
    init(rawValue:UInt)
    Normal,Highlighted,Disabled,Selected,Focused,Application,Reserved
}
    // Setting and Getting Control Attributes
    .state: UIControlState { get }
    .enabled: Bool
    .selected: Bool
    .highlighted: Bool
    .contentVerticalAlignment: UIControlContentVerticalAlignment
    .contentHorizontalAlignment: UIControlContentHorizontalAlignment
    
    // Tracking Touches and Redrawing Controls
    
    
####UIButton : UIControl : UIView : UIResponder
enum UIButtonType {
    Custom,System,DetailDisclosure,InfoLight,InfoDark,ContactAdd,
    static var RoundedRect:UIButtonType { get }
}
        .init(type:UIButtonType)
        .titleLabel
        .titleForState(_:UIControlState) -> String?
        

### UIImageView : UIView : UIResponder
        .init(image:UIImage? [, highlightedImage: UIImage?])
        .image: UIImage?
        .hightedImage
        .layer
        .contentMode
        .userInteractionEnabled: Bool   // whether listen event queue
        .highlighted: Bool  // whether the image is highlighted
        .tintColor          // tint color in the view hierachy

        .clipsToBounds: Bool

        // Animating
        .animationImages: [UIImage]?
        .highlightedAnimationImages
        .animationDuration
        .animationRepeatCount
        .startAnimating()
        .stopAnimating()
        .isAnimating()

##  UIViewController
### UINavigationController
####UIImagePickerController
UIImagePickerControllerSourceType {
    PhotoLibrary    // PhotoLibrary includes SavedPhotosAlbum
    Camera      // use `cameraDevice` to indicate the specific camera
    SavedPhotosAlbum
}
UIImagePickerControllerCameraCaptureMode { Photo, Video }
UIImagePickerControllerCameraDevice { Rear, Front }
UIImagePickerContollerQualityType {
    TypeHight, TypeMedium, TypeLow, 
    Type640x480, TypeIFrame1280x720, TypeIFrame960x540
}
UIImagePickerControllerCameraFlashMode { Off, Auto, On }
struct CGAffineTransform {...}  // hold an affine transformation matrix
    // Setting the Picker Source
    .availableMediaTypesForSourceType(_:UIImagePickerControllerSourceType)
    .isSourceTypeAvailable(_:UIImagePickerControllerSourceType) -> Bool
    .sourceType: UIImagePickerControllerSourceType

    .allowEditing: Bool
    weak var .delegate: protocol<UIImagePickerControllerDelegate, UINavigationControllerDelegate>?
    .mediaTypes: [String]
    .videoQuality: UIImagePickerControllerQualityType
    .videoMaximumDuration: NSTimeInterval  // sec, default 600 seconds
    .showCameraControls: Bool
    .cameraOverlayView: UIView?
    .cameraViewTransform: CGAffineTransform
    .cameraDevice: UIImagePickerControllerCameraDevice
    .isCameraDeviceAvailable(_:UIImagePickerControllerCameraDevice)
    .availableCaptureModesForCameraDevice(_:UIImagePickerControllerCameraDeive) -> [NSNumber]?
    .cameraCaptureMode: UIImagePickerControllerCameraCaptureMode
    .cameraFlashMode: UIImagePickerControllerCameraFlashMode
    // Capturing Still Images or Movies
    .takePicture()
    .startVideoCapture()
    .stopVideoCapture()
    
####UIVideoEditor
/**/
UIImageOrientation {Up,Down,Left,Right,?Mirrored}        
#   UIImage
        .init(named filename: String[, NSBundle?, UITraitCollection?])
        .init?(contentsOfFile:String) -> UIImage
        .init?(data:NSData) -> UIImage
        .init?(data:NSData, scale:CGFloat) -> UIImage
        
        /**
         *  scale: 
         *  orientation: 
         */
        .init(:CGImage[, scale:CGFloat, orientation:UIImageOrientation)
        .init(:CIImage[, scale, orientation])
        .imageOrientation:UIImageOrientation .size:CGSize 

        /**
         *  UIImageView.image.size   the origin size of an image
         *  UIImageView.frame.size   the displaying size of an image  
         */
        .size: CGSize { get }
        .scale:CGFloat          // default 1.0,    scale * size = real size
        .flipsForRightToLeftLayoutDirection
        .resizingMode:UIImageResizingMode
        .CGImage .CIImage .images .duration .capInsets
        .alignmentRectInsets .imageAsset .traitCollection .renderingMode
        drawAtPoint(:CGPoint[, :CGBlendMode, alpha])
        drawInRect(:CGRect[, :CGBlendMode, alpha])
        drawAsPatternInRect(:CGRect)
        
        // Creating New Images

        /**
         * to load a gif image
         */
        .animatedImageNamed(_ name:String, duration:NSTimeInterval)->UIImage
        .animatedImageWithImages(_:[UIImage], duration) -> UIImage?
            
/**/
UIGestureRecognizerState {
    Possible,
    Began,      // to a continuous gesture
    Changed,    // to a continuous gesture
    Ended,      // to a continuous gesture
    Cancelled,
    Failed,
    static var Recognized: UIGestureRecognizerState { get }
}
/**/
#   UIGestureRecognizer : NSObject 
        .init(target: AnyObject?, action: Selector) -> UIGestureRecognizers
        .addTarget(_ target, action)
        .removeTarget(_ target?, action)
        // Recognizer's State and View
        .state: UIGestureRecognizerState { get }
        .view: UIView? { get }
        .enabled: Bool  whether the gesture recognizer is enabled
        // Canceling and Delaying Touches
        .cancelsTouchesInView: Bool
##      UILongPressGestureRecoginzer : UIGestureRecognizer
##      UIPanGestureRecognizer : UIGestureRecognizer   
        /**
         * A panning(dragging) gesture is continuous. It begins (UIGestureRecognizerStateBegan) when the minimum number of fingers allowed (minimumNumberOfTouches) has moved enough to be considered a pan. It changes (UIGestureRecognizerStateChanged) when a finger moves while at least the minimum number of fingers are pressed down. It ends (UIGestureRecognizerStateEnded) when all fingers are lifted.
         */
         .maximumNumberOfTouches   // max number of fingers
         .miniumNumberOfTouches
         // Tracking the Location and Velocity
         .translationInView(_:UIView?) -> CGPoint
         .setTranslation(_:CGPoint, inView:UIView)
         .velocityInView(_:UIView?) -> CGPoint   // point per second
###         UIScreenEdgePanGestureRecognizer : UIPanGestureRecognizer 
            : UIGestureRecognizer
            var edges: UIRectEdge   // the acceptable starting edges for
##  UIPinchGestureRecognizer
##  UIRotationGestureRecognizer
##  UISwipeGestureRecognizer
##  UITapGestureRecgonizer

#   UIBezierPath : NSObject, NSCopying, NSCoding
        .init(rect:CGRect)  -> UIBezierPath
        .init(ovalInRect:CGRect)  -> UIBezierPath
        .init(rounderRect:CGRect, cornerRadius:CGFLoat) -> UIBezierPath
        .init(roundRect, byRoundingCorners:UIRectCorner, 
              cornerRadii: CGSize) -> UIBezierPath
        /**
         *   180 degree = M_PI radius
         */
        .init(arcCenter:CGPoint, radius: CGFloat, startAngle: UIBezierPath,
              endAngle:CGFloat, clockwise: Bool) -> UIBezierPath
        convenience init(:CGPath)
        .bezierPathByReversingPath() -> UIBezierPath
        // Constructing a Path
        .moveToPoint(_:CGPoint)
        .addLineToPoint(_:CGPoint)
        .addArcWithCenter(_ center, radius, startAngle, endAngle, clockwise)
        /**
         *  A cubic Bézier curve
         *        ■   controlPoint1
         *       /                    ●  endPoint
         *      /   ～ ～ ～       ～/ 
         *     /  ～          ～ ～ /
         *    ● ～                 ■  controlPoint2
         *  startPoint(using the moveToPoint)
         */
        .addCurveToPoint(_ endPoint:CGPoint, controlPoint1: CGPoint,
                         controlPoint2)
    

