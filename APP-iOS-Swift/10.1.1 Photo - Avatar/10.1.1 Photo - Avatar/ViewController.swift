

import UIKit
import Gifu
import Haneke
//import Alamofire
//import AlamofireImage

class ViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIScrollViewDelegate  {
    
    var scrollView: UIScrollView!
    
    weak var img: UIImageView!
    weak var avatar: UIImageView!
    weak var savingLoading: AnimatableImageView!
    //weak var saveBtn: UIButton!
    weak var maskerView : UIView!
    weak var moistAvatarMasker: UIImageView!
    
    var panAvatarLastTranslation: CGPoint = CGPoint(x: 0.0, y: 0.0)
    var enableRotation: Bool = false
    let imagePicker: UIImagePickerController! = UIImagePickerController()

    override func shouldAutorotate() -> Bool {
        return false
    }
    override func supportedInterfaceOrientations() -> UIInterfaceOrientationMask {
        return .Portrait
    }
    
    func handleAvatarOutOfBounds() {
        
        let standardAvatarBound: [String:CGFloat] = [
            "top": UIApplication.sharedApplication().statusBarFrame.height + UIScreen.mainScreen().bounds.width / 2 - Conf.Size.avatarSize.height / 2,
            "right": UIScreen.mainScreen().bounds.width / 2 + Conf.Size.avatarSize.width / 2,
            "bottom": UIApplication.sharedApplication().statusBarFrame.height + UIScreen.mainScreen().bounds.width / 2 + Conf.Size.avatarSize.height / 2,
            "left": UIScreen.mainScreen().bounds.width / 2 - Conf.Size.avatarSize.width / 2
        ]
        let avatarBound: [String:CGFloat] = [
            "top": self.avatar.center.y - self.avatar.frame.height / 2,
            "right": self.avatar.frame.width / 2 + self.avatar.center.x,
            "bottom": self.avatar.center.y + self.avatar.frame.height / 2,
            "left": self.avatar.center.x - self.avatar.frame.width / 2
        ]
        
        if (self.panAvatarLastTranslation.x < 0 && avatarBound["right"] < standardAvatarBound["right"]) {
            UIView.animateWithDuration(0.5, animations: {
                self.avatar.center.x += (standardAvatarBound["right"]! - avatarBound["right"]!)
            })
            if (Conf.Debug.Avatar.debugIsOutOfBounds) {
                print("Out of right bound")
            }
        }
        
        if(self.panAvatarLastTranslation.x > 0 && avatarBound["left"] > standardAvatarBound["left"]) {
            UIView.animateWithDuration(0.5, animations: {
                self.avatar.center.x -= (avatarBound["left"]! - standardAvatarBound["left"]!)
            })
            if (Conf.Debug.Avatar.debugIsOutOfBounds) {
                print("Out of left bound")
            }
        }
        
        if(self.panAvatarLastTranslation.y > 0 && avatarBound["top"] > standardAvatarBound["top"]) {
            UIView.animateWithDuration(0.5, animations: {
                self.avatar.center.y -= (avatarBound["top"]! - standardAvatarBound["top"]!)
            })
            if (Conf.Debug.Avatar.debugIsOutOfBounds) {
                print("Out of top bound")
            }
        }
        if(self.panAvatarLastTranslation.y < 0 && avatarBound["bottom"] < standardAvatarBound["bottom"]) {
            UIView.animateWithDuration(0.5, animations: {
                self.avatar.center.y += (standardAvatarBound["bottom"]! - avatarBound["bottom"]!)
            })
            if (Conf.Debug.Avatar.debugIsOutOfBounds) {
                print("Out of bottom bound")
            }
        }
    }
    
    
    func back(sender: UIButton) {
        
    }
    
    func changeAvatarTouchDown(sender: UIButton) {
        sender.setTitleColor(Conf.Theme.Avatar.focusedColor, forState: .Normal)
    }
    
    func changeAvatar(sender: UIButton) {
        sender.setTitleColor(Conf.Theme.Avatar.tintColor, forState: .Normal)
        let changeAvatarAlert = UIAlertController(title:nil, message: nil, preferredStyle: .ActionSheet)
        changeAvatarAlert.addAction(UIAlertAction(title: "Calcel", style: .Cancel, handler: {
            action in
        }))
        
        changeAvatarAlert.addAction(UIAlertAction(title: "Take Profile Photo", style: .Default, handler: {
            action in
            if (UIImagePickerController.isSourceTypeAvailable(.Camera)) {
                if UIImagePickerController.availableCaptureModesForCameraDevice(.Rear) != nil {
                    self.imagePicker.allowsEditing = true
                    self.imagePicker.sourceType = .Camera
                    self.imagePicker.cameraCaptureMode = .Photo
                    self.presentViewController(self.imagePicker, animated: true, completion: nil)
                } else {
                    Aa.notifier().error(message: "Cannot access the camera.")
                }
            } else {
                Aa.notifier().error(message: "Camera inaccessable.")
            }

        }))
        
        changeAvatarAlert.addAction(UIAlertAction(title: "Choose from Library", style: .Default, handler: {
            action in
            self.imagePicker.allowsEditing = true
            self.imagePicker.sourceType = .PhotoLibrary
            self.presentViewController(self.imagePicker, animated: true, completion: nil)
        }))

        presentViewController(changeAvatarAlert,animated: true, completion: nil)
    }
    func imagePickerController(picker: UIImagePickerController, didFinishPickingMediaWithInfo info : [String : AnyObject]) {
        if let pickedImage : UIImage = (info[UIImagePickerControllerOriginalImage]) as? UIImage {
            initAvatar(pickedImage)
            opaqueMasker(false)
            if (self.imagePicker.sourceType == .Camera) {
                UIImageWriteToSavedPhotosAlbum(pickedImage, nil, nil, nil)
            }
        }
        imagePicker.dismissViewControllerAnimated(true, completion: {
            // Anything you want to happen when the user saves an image
        })

    }
    
    func saveAvatar(sender: UIButton) {
        
        let avatarMaskCenter:CGPoint = CGPoint(x: UIScreen.mainScreen().bounds.width / 2, y: UIApplication.sharedApplication().statusBarFrame.height + UIScreen.mainScreen().bounds.width / 2)
        let cropingCenter = CGPoint(x: avatarMaskCenter.x - avatar.frame.origin.x, y: avatarMaskCenter.y - self.avatar.frame.origin.y)
        let cropingOrigin = CGPoint(x: cropingCenter.x - Conf.Size.avatarSize.width / 2, y: cropingCenter.y - Conf.Size.avatarSize.height / 2)
        
        if let img = avatar.image {
            let imgWidthScale: CGFloat =  img.size.width * img.scale / avatar.frame.width
            let imgHeightScale: CGFloat =  img.size.height * img.scale / avatar.frame.height
            let rect: CGRect = CGRectMake(ceil(cropingOrigin.x * imgWidthScale), ceil(cropingOrigin.y * imgHeightScale), Conf.Size.avatarSize.width * imgWidthScale, Conf.Size.avatarSize.height * imgHeightScale)
            
            let imgRef: CGImageRef = CGImageCreateWithImageInRect(img.CGImage, rect)!
            var croppedImg = UIImage(CGImage: imgRef, scale: img.scale, orientation: img.imageOrientation)
            
            if (Conf.Size.saveAvatarFixedSize) {
                let imgSize = CGSize(width: Conf.Size.avatarSize.width * Conf.Size.avatarScale, height: Conf.Size.avatarSize.width * Conf.Size.avatarScale)
                UIGraphicsBeginImageContextWithOptions(imgSize, false, 1.0)
                croppedImg.drawInRect(CGRect(origin: CGPointZero, size: imgSize))
                let savingImgContext = UIGraphicsGetCurrentContext()
                UIGraphicsEndImageContext()
                
                if let savingImgRef: CGImageRef = CGBitmapContextCreateImage(savingImgContext) {
                    croppedImg = UIImage(CGImage: savingImgRef, scale: Conf.Size.avatarScale, orientation: .Up)
                }
            }
            
            initAvatar(croppedImg)
            opaqueMasker(true)
            
            dispatch_async(dispatch_get_main_queue()) {
                UIImageWriteToSavedPhotosAlbum(croppedImg, nil, nil, nil)
            }
            
            
            
            if (Conf.Debug.Avatar.savingPosition) {
                print(rect.origin)
                print("Size: img=\(img.size) CGImage=(\(CGImageGetWidth(img.CGImage)), \(CGImageGetHeight(img.CGImage))) frame=\(avatar.frame.size)")
                print("Size: rect=\(rect.size) imgRef=(\(CGImageGetWidth(imgRef)), \(CGImageGetHeight(imgRef))) cropped=\(croppedImg.size)")
                print("screenCenter=(\(UIScreen.mainScreen().bounds.width / 2), \(UIApplication.sharedApplication().statusBarFrame.height + UIScreen.mainScreen().bounds.width / 2)) center=\(self.avatar.center)")
            }
        }
        
        
        Aa.notifier().success(message: "Avatar saved")  {
            self.savingLoading?.hidden = true
            self.savingLoading?.stopAnimatingGIF()
            sender.hidden = false
        }
    }
    
    func showSavingLoading(sender: UIButton) {
        if (savingLoading == nil) {
            let savingLoadingTmp = Aa.animatableImageView()
            savingLoadingTmp.animateWithImage(named: "loading2.gif")
            savingLoadingTmp.frame = CGRect(x: UIScreen.mainScreen().bounds.width - 60, y: UIApplication.sharedApplication().statusBarFrame.height, width:30, height:30)
            savingLoading = savingLoadingTmp
            view.addSubview(savingLoading)
            view.bringSubviewToFront(savingLoading)
        } else {
            savingLoading.startAnimatingGIF()
            savingLoading.hidden = false
        }
        
        sender.hidden = true
    }
    
    func resizeByDoubleTap(sender: UITapGestureRecognizer) {
        opaqueMasker(false)
        sender.numberOfTapsRequired = 2
        
        let scale: CGFloat = 1.2
        
        UIView.animateWithDuration(0.5, animations: {
            self.avatar.transform = CGAffineTransformScale(self.avatar.transform, scale, scale)
            })
    }
    func resizeAvatar(sender: UIPinchGestureRecognizer) {
        opaqueMasker(false)

        if (Conf.Debug.Avatar.recognizeGestures) {
            print("resize")
        }
        var scale: CGFloat = sender.scale
        
        avatar.transform = CGAffineTransformScale(avatar.transform, scale, scale)
        
        if (scale < 1 && (avatar.frame.width < Conf.Size.avatarSize.width || avatar.frame.height < Conf.Size.avatarSize.height)) {
            scale = 2.01 - scale     // zoom out,  ceil(20 - scale * 10) / 10
            avatar.transform = CGAffineTransformScale(avatar.transform, scale, scale)
        }
        sender.scale = 1.0
        handleAvatarOutOfBounds()
    }

    
    /**
     * Rotate may leave something wrong to Pan
     */
    func rotateAvatar(sender: UIRotationGestureRecognizer) {
        opaqueMasker(false)

        if (Conf.Debug.Avatar.recognizeGestures) {
            print("rotate")
        }
        let rotation =  sender.velocity * 0.05
        avatar.transform = CGAffineTransformRotate(avatar.transform, rotation)
    }
    func moveAvatar(sender:UIPanGestureRecognizer) {
        sender.maximumNumberOfTouches = 1
        sender.minimumNumberOfTouches = 1
        if (Conf.Debug.Avatar.recognizeGestures) {
            print("pan")
        }
        let translation = sender.translationInView(self.avatar)
        
        if (self.avatar.frame.width <  Conf.Size.avatarSize.width) {
            self.avatar.frame = CGRect(origin: self.avatar.frame.origin, size: CGSize(width: Conf.Size.avatarSize.width, height:Conf.Size.avatarSize.height))
        }
        if let view = sender.view {
            switch sender.state {
            case .Began:
                opaqueMasker(false)
            case .Changed:
                if (Conf.Debug.Avatar.panningVelocity) {
                    print("Changed: velocity: \(sender.velocityInView(view))  translation: \(translation)")
                }
                panAvatarLastTranslation = translation
                self.avatar.center = CGPoint(x: self.avatar.center.x + translation.x, y: self.avatar.center.y + translation.y)
            case .Ended:
                var velocityDistance = sqrt(pow(sender.velocityInView(view).x, CGFloat(2)) + pow(sender.velocityInView(view).y, CGFloat(2)))
                
                if (Conf.Debug.Avatar.panningVelocity) {
                    print("Ended: velocity: \(sender.velocityInView(view))  translation: \(translation)")
                    print("velocityDistance: \(velocityDistance)")
                }
                
                if (velocityDistance > 50) {
                    let inertiaDelay: NSTimeInterval = 0.5
                    if (velocityDistance > 1500) {
                        velocityDistance = 1500
                    }
                    // 60HZ = 60 / sec
                    let inertiaDistance : CGFloat = velocityDistance * CGFloat(inertiaDelay) * (1/60)
                    let inertiaX:CGFloat = self.panAvatarLastTranslation.x * inertiaDistance
                    let inertiaY:CGFloat = self.panAvatarLastTranslation.y * inertiaDistance
                                        //sqrt(pow(inertiaX, CGFloat(2)) + pow(inertiaY, CGFloat(2)))
                    //print("inertiaDelay: \(inertiaDelay)")
                    UIView.animateWithDuration(inertiaDelay, delay: 0, usingSpringWithDamping: 0.8, initialSpringVelocity: 6, options: UIViewAnimationOptions.AllowUserInteraction, animations: {
                        self.avatar.center.x += inertiaX
                        self.avatar.center.y += inertiaY
                    }, completion: nil)
                }
            default:
                print("default")
            }
            self.handleAvatarOutOfBounds()
        }
        sender.setTranslation(CGPointZero, inView: view)
    }
    
    func opaqueMasker(opaque: Bool = false) {
        if (opaque) {
            maskerView.alpha = 1.0
        } else {
            moistAvatarMasker.image = nil
            maskerView.alpha = 0.5
        }
    }
    func maskAvatar(){
        
        let v = UIView(frame: CGRect(x:0, y:UIApplication.sharedApplication().statusBarFrame.height, width: UIScreen.mainScreen().bounds.width, height: UIScreen.mainScreen().bounds.width))
        
        maskerView = v
        maskerView.backgroundColor = UIColor.blackColor()

        
        let range: CGFloat = UIScreen.mainScreen().bounds.width
        let radius: CGFloat = Conf.Size.avatarSize.width / 2
        
        // Create a path with the rectangle in it.
        let path = CGPathCreateMutable()
        let rect = CGRectMake(0, 0, range, range)
        CGPathMoveToPoint(path, nil, CGRectGetMinX(rect), CGRectGetMinY(rect))
        CGPathAddLineToPoint(path, nil, CGRectGetMaxX(rect), CGRectGetMinY(rect))
        CGPathAddLineToPoint(path, nil, CGRectGetMaxX(rect), CGRectGetMaxY(rect))
        CGPathAddLineToPoint(path, nil, CGRectGetMinX(rect), CGRectGetMaxY(rect))
        CGPathCloseSubpath(path)
        
        
        CGPathMoveToPoint(path, nil, range / 2 + radius, range / 2 + radius)
        CGPathAddArc(path, nil, range / 2, range / 2, radius, 0, CGFloat(M_PI * 2), false)
        
        let maskerFill = CAShapeLayer()
        maskerFill.path = path
        maskerFill.fillColor = UIColor.blackColor().CGColor
        maskerFill.fillRule = kCAFillRuleEvenOdd
        maskerView.layer.mask = maskerFill

       
        view.addSubview(maskerView)
        
        
        // moist avatar background
        let moistAvatarMasker = UIImageView(image: UIImage(named: "default"))
        moistAvatarMasker.frame = CGRect(origin: CGPoint(x: 0, y: 0), size: maskerView.frame.size)
        let vsEffect = UIVisualEffectView(effect: UIBlurEffect(style: .Dark))
        vsEffect.frame = moistAvatarMasker.frame
        moistAvatarMasker.insertSubview(vsEffect, atIndex: 0)
        maskerView.insertSubview(moistAvatarMasker, atIndex: 0)
        self.moistAvatarMasker = moistAvatarMasker

        
        
        // circle
        let circlePath = UIBezierPath(arcCenter: CGPoint(x: range / 2,y: range / 2), radius: radius, startAngle: CGFloat(0), endAngle:CGFloat(M_PI * 2), clockwise: true)
        
        let shapeLayer = CAShapeLayer()
        shapeLayer.path = circlePath.CGPath
        
        //change the fill color
        shapeLayer.fillColor = UIColor.clearColor().CGColor
        //you can change the stroke color
        shapeLayer.strokeColor = UIColor.whiteColor().CGColor
        //you can change the line width
        shapeLayer.lineWidth = 3.0

        
        
        maskerView.layer.addSublayer(shapeLayer)
        
        maskerView.addGestureRecognizer(UIPanGestureRecognizer(target: self, action: #selector(ViewController.moveAvatar(_:))))
        maskerView.addGestureRecognizer(UIPinchGestureRecognizer(target: self, action: #selector(ViewController.resizeAvatar(_:))))
        maskerView.addGestureRecognizer(UITapGestureRecognizer(target: self, action: #selector(ViewController.resizeByDoubleTap(_:))))
        if (enableRotation) {
            maskerView.addGestureRecognizer(UIRotationGestureRecognizer(target: self, action: #selector(ViewController.rotateAvatar(_:))))
        }
        
    }

    func fetchImageByHanekeSwift(infoJsonURL: NSURL) {
        let cache = Shared.JSONCache
        cache.fetch(URL: infoJsonURL).onSuccess {
            jsonData in
            if let avatarUrlStr = jsonData.dictionary["avatar_url"] {
                if let avatarUrl = NSURL(string: String(avatarUrlStr)) {
                    let fetcher = NetworkFetcher<UIImage>(URL: avatarUrl)
                    self.avatar.hnk_setImageFromFetcher(fetcher, success: {
                        image -> () in
                        self.handleRemoteImage(image)
                    })
                    
                }
            }
        }
    }
    
    func handleRemoteImage(image: UIImage) {
        let imgSize = CGSize(width: Conf.Size.avatarSize.width * Conf.Size.avatarScale, height: Conf.Size.avatarSize.width * Conf.Size.avatarScale)
        UIGraphicsBeginImageContextWithOptions(imgSize, false, 1.0)
        image.drawInRect(CGRect(origin: CGPointZero, size: imgSize))
        let savingImgContext = UIGraphicsGetCurrentContext()
        UIGraphicsEndImageContext()
        
        var croppedImage = image
        if let savingImgRef: CGImageRef = CGBitmapContextCreateImage(savingImgContext) {
            croppedImage = UIImage(CGImage: savingImgRef, scale: Conf.Size.avatarScale, orientation: .Up)
            self.avatar.image = croppedImage
        }
        
        self.initAvatar(croppedImage)
        self.opaqueMasker(true)
    }

    func initAvatar(image: UIImage) {
        //print("centerBefore: \(avatar.center)")
        avatar.image = image
        moistAvatarMasker.image = image
        initAvatarPosition(avatar)
        //print("centerAfter: \(avatar.center)")
    }
    func initAvatarPosition(avatar: UIImageView) {
        if let img = avatar.image {
            var avatarX:CGFloat = 0
            var avatarY: CGFloat = UIApplication.sharedApplication().statusBarFrame.height
            var avatarWidth:CGFloat = img.size.width
            var avatarHeight:CGFloat = img.size.height
            
            let avatarImgProportion = img.size.width / img.size.height
            
            if (img.size.width == img.size.height) {
                avatarWidth = Conf.Size.avatarSize.width
                avatarHeight = Conf.Size.avatarSize.height
            } else if (img.size.width > img.size.height) {
                    avatarHeight = Conf.Size.avatarSize.height
                    avatarWidth = avatarImgProportion * avatarHeight
            } else {
                    avatarWidth = Conf.Size.avatarSize.width
                    avatarHeight = avatarWidth / avatarImgProportion
            }
            
            if (avatarWidth < UIScreen.mainScreen().bounds.width) {
                avatarX += (UIScreen.mainScreen().bounds.width - avatarWidth) / 2
            }
            if (avatarHeight < UIScreen.mainScreen().bounds.width) {
                avatarY += (UIScreen.mainScreen().bounds.width - avatarHeight) / 2
            }
            avatar.frame = CGRect(x: avatarX, y: avatarY, width: avatarWidth, height: avatarHeight)
            if (Conf.Debug.Avatar.savingPosition) {
                print("initOrientation: \(img.imageOrientation.rawValue)")
                print("origin=\(img.size) scale=\(img.scale) CGImage=(\(CGImageGetWidth(img.CGImage)), \(CGImageGetHeight(img.CGImage))) now=\(avatarWidth) \(avatarHeight)")
            }
        }
    }
    
    var hasDecoration: Bool = false
    struct DecorationPatternsData {
        let patternImageName: String
        init(patternImageName: String) {
            self.patternImageName = patternImageName
        }
    }
    var decorationPatterns : [DecorationPatternsData] = [DecorationPatternsData(patternImageName: "decoration1.gif"), DecorationPatternsData(patternImageName: "decoration1.gif"), DecorationPatternsData(patternImageName: "decoration1.gif")]
    
    var clickedDecorationBtn : UIButton? = nil
    var patternSelectors = [UIButton : DecorationPatternsData]()

    weak var decorateBtn: UIButton!
    weak var decorationView: AnimatableImageView!
    func decorate(sender: UIButton) {
        if (decorationView == nil) {
            let decView = Aa.animatableImageView()
            decView.animateWithImage(named: decorationPatterns[0].patternImageName)
            decView.frame = CGRect(x: (UIScreen.mainScreen().bounds.width - Conf.Size.avatarSize.width) / 2, y: UIApplication.sharedApplication().statusBarFrame.height + (UIScreen.mainScreen().bounds.width - Conf.Size.avatarSize.height) / 2, width: Conf.Size.avatarSize.width, height:Conf.Size.avatarSize.height)
            decView.hidden = true
            view.addSubview(decView)
            view.bringSubviewToFront(decView)
            decorationView = decView
        }
        
        if let data = patternSelectors[sender] {        // decoration iamge buttons
            clickedDecorationBtn = sender
            hasDecoration = true
            decorateBtn.setTitle("Origin", forState: .Normal)
            decorationView.hidden = false
            decorationView.animateWithImage(named: data.patternImageName)
        } else {                        // Decorate/Origin button
            if (!hasDecoration) {
                decorateBtn.setTitle("Origin", forState: .Normal)
                decorationView.hidden = false
            } else {
                decorateBtn.setTitle("Decorate", forState: .Normal)
                decorationView.hidden = true
            }
            
            if let clickedDecorationBtn = clickedDecorationBtn {
                if let decorationBtn = patternSelectors[clickedDecorationBtn] {
                    decorationView.animateWithImage(named: decorationBtn.patternImageName)
                }
            }
            hasDecoration = !hasDecoration
        }
        
    
        
    }
    
    func selectDecoration(sender: UIButton) {
        if let data = patternSelectors[sender] {
            print(data.patternImageName)
            if let clickedBtn = clickedDecorationBtn {
                clickedBtn.layer.borderWidth = 0
            }
            sender.layer.borderWidth = 1.0
            decorate(sender)
        }
    }
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        imagePicker.delegate = self
        
        let statusBarBg = UIImageView(frame: CGRect(x:0, y:0, width: UIApplication.sharedApplication().statusBarFrame.size.width, height: UIApplication.sharedApplication().statusBarFrame.size.height))
        statusBarBg.backgroundColor = UIColor.blackColor()
        self.view.addSubview(statusBarBg)
        
        
        let backBtn = UIButton(frame: CGRect(origin: CGPointMake(10.0, 20.0), size: CGSizeMake(80, 30)))
        backBtn.setTitle("< Back", forState: UIControlState.Normal)
        backBtn.contentHorizontalAlignment = .Left
        backBtn.contentVerticalAlignment = .Center
        backBtn.addTarget(self, action: #selector(back(_:)), forControlEvents: UIControlEvents.TouchUpInside)
        view.addSubview(backBtn)
        
        let saveBtn = UIButton(frame: CGRect(x: UIScreen.mainScreen().bounds.width - 60, y: UIApplication.sharedApplication().statusBarFrame.height, width: 60, height: 30))
        saveBtn.setTitle("Save", forState: .Normal)
        saveBtn.addTarget(self, action: #selector(ViewController.showSavingLoading(_:)), forControlEvents: UIControlEvents.TouchDown)
        saveBtn.addTarget(self, action: #selector(ViewController.saveAvatar(_:)), forControlEvents: UIControlEvents.TouchUpInside)
        view.addSubview(saveBtn)
        
       
        
        

        
        
        let avatarView = UIImageView()
        avatarView.contentMode = .ScaleToFill
        avatarView.userInteractionEnabled = true
        //avatarView.alpha = 1
        avatarView.backgroundColor = UIColor.blackColor()
        avatarView.clipsToBounds = true
        avatar = avatarView
        maskAvatar()
        self.view.addSubview(avatar)

        if let avatarImg = UIImage(named: "swift2") {
            initAvatar(avatarImg)
            opaqueMasker(true)
        }
                
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0)) {
            if let infoJsonURL = NSURL(string: "https://api.github.com/users/AarioAi") {
                self.fetchImageByHanekeSwift(infoJsonURL)
            }
        }

        
        
        
        let margin: CGFloat = 20.0
        let btnWidth: CGFloat = 90.0
        let btnHeight: CGFloat = 26.0
        let changeAvatarBtnX = UIScreen.mainScreen().bounds.width / 2 - btnWidth - margin
        let changeAvatarBtnY = UIScreen.mainScreen().bounds.width + UIApplication.sharedApplication().statusBarFrame.height - btnHeight * 2.5
        let changeAvatarBtn = UIButton(frame: CGRect(x: changeAvatarBtnX, y: changeAvatarBtnY, width: btnWidth, height: btnHeight))
        changeAvatarBtn.setTitle("Change", forState: UIControlState.Normal)
        changeAvatarBtn.opaque = true
        changeAvatarBtn.layer.cornerRadius = btnHeight / 2
        changeAvatarBtn.layer.borderColor = UIColor.grayColor().CGColor
        changeAvatarBtn.layer.borderWidth = 1
        changeAvatarBtn.layer.opaque = true
        changeAvatarBtn.addTarget(self, action: #selector(ViewController.changeAvatarTouchDown(_:)), forControlEvents: .TouchDown)
        changeAvatarBtn.addTarget(self, action: #selector(ViewController.changeAvatar(_:)), forControlEvents: .TouchUpInside)
        self.view.addSubview(changeAvatarBtn)
        
        
        let decorationBtnX = UIScreen.mainScreen().bounds.width / 2 + margin
        let decorationBtn = UIButton(frame: CGRect(x: decorationBtnX, y: changeAvatarBtnY, width: btnWidth, height: btnHeight))
        decorationBtn.setTitle("Decorate", forState: .Normal)
        decorationBtn.opaque = true
        decorationBtn.layer.opaque = true
        decorationBtn.layer.cornerRadius = 13
        decorationBtn.layer.borderColor = UIColor.grayColor().CGColor
        decorationBtn.layer.borderWidth = 1
        decorationBtn.addTarget(self, action: #selector(ViewController.decorate(_:)), forControlEvents: .TouchUpInside)
        self.view.addSubview(decorationBtn)
        decorateBtn = decorationBtn

        
        
        
        
        

        
        let decorationNavHeight:CGFloat = 38
        let decorationNavY = UIScreen.mainScreen().bounds.height - decorationNavHeight
        
        let decorationNav = UIImageView(frame: CGRect(x: 0, y: decorationNavY, width: UIScreen.mainScreen().bounds.width, height: decorationNavHeight))
        decorationNav.backgroundColor = UIColor(white: 0.88888888, alpha: 1)
        self.view.addSubview(decorationNav)
        
        
        
        
        let decorationY = UIScreen.mainScreen().bounds.width + UIApplication.sharedApplication().statusBarFrame.size.height
        let decorationHeight = UIScreen.mainScreen().bounds.height - decorationY - decorationNavHeight
        
        let decorationBg = UIImageView(frame: CGRect(x: 0, y: decorationY, width: UIApplication.sharedApplication().statusBarFrame.width, height: decorationHeight))
        decorationBg.tintColor = UIColor.blackColor()
        decorationBg.backgroundColor = UIColor.whiteColor()
        self.view.addSubview(decorationBg)
        
        
        let decorationSelectionTitleHeight: CGFloat = 50.0
        let decorationSelectionTitle = UILabel(frame:CGRect(origin: CGPointMake(Conf.Size.margin, Conf.Size.margin), size: CGSizeMake(200, decorationSelectionTitleHeight - Conf.Size.margin * 2)))
        decorationSelectionTitle.text = "SELECT DECORATION"
        decorationSelectionTitle.tintColor = UIColor.blackColor()
        decorationSelectionTitle.font = UIFont(name:"HelveticaNeue", size: 18.0)
        decorationBg.addSubview(decorationSelectionTitle)
        
        
        
        let patternSelectorHeight = UIScreen.mainScreen().bounds.height - UIApplication.sharedApplication().statusBarFrame.height - UIScreen.mainScreen().bounds.width - decorationNavHeight - decorationSelectionTitleHeight - Conf.Size.margin
        
        decorationBg.userInteractionEnabled = true
        
        scrollView = UIScrollView(frame: CGRect(x:0 ,y:decorationSelectionTitleHeight, width: UIScreen.mainScreen().bounds.width, height: patternSelectorHeight))
        scrollView.userInteractionEnabled = true
        scrollView.contentSize.height = patternSelectorHeight
        //scrollView.backgroundColor = UIColor.redColor()
        scrollView.showsVerticalScrollIndicator = false
        scrollView.showsHorizontalScrollIndicator = false
        scrollView.delegate = self

        decorationBg.addSubview(scrollView)
        for (index, pattern) in decorationPatterns.enumerate() {
            
            let patternSelector = UIImageView(image: UIImage(named: "test.jpg"))
            if let p = patternSelector.image {
                let proportion = p.size.width / p.size.height
                let w = proportion * patternSelectorHeight
                
                let patternX: CGFloat = (w + Conf.Size.margin) * CGFloat(index) + Conf.Size.margin
                let patternOrigin = CGPoint(x: patternX, y: 0)
               

                
                patternSelector.userInteractionEnabled = true
                patternSelector.accessibilityLabel = "pattern"
                patternSelector.accessibilityValue = pattern.patternImageName
                
                patternSelector.frame = CGRect(origin: patternOrigin, size: CGSize(width: w, height: patternSelectorHeight))
                //patternSelector.addGestureRecognizer(UITapGestureRecognizer(target: self, action: #selector(ViewController.selectDecoration(_:))))
                
                
                let decorationBtn = UIButton(frame: patternSelector.frame)
                decorationBtn.layer.borderWidth = 0
                decorationBtn.layer.borderColor = UIColor.orangeColor().CGColor
                decorationBtn.layer.cornerRadius = 5.0
                decorationBtn.addTarget(self, action: #selector(ViewController.selectDecoration(_:)), forControlEvents: .TouchUpInside)
                //decorationBg.addSubview(decorationBtn)
                
                
                patternSelectors[decorationBtn] = pattern
                scrollView.addSubview(patternSelector)
                scrollView.bringSubviewToFront(patternSelector)

                scrollView.addSubview(decorationBtn)
                scrollView.bringSubviewToFront(decorationBtn)
                scrollView.contentSize.width = patternX + w

            }
        }

        
        
        
        
        
        self.view.backgroundColor = UIColor.blackColor()
        self.view.tintColor = UIColor.whiteColor()
        UIApplication.sharedApplication().statusBarStyle = .LightContent
        
        self.view.sendSubviewToBack(avatarView)
        //self.view.sendSubviewToBack(avatarView)
        
        self.view.bringSubviewToFront(changeAvatarBtn)
        self.view.bringSubviewToFront(decorationBtn)
        self.view.bringSubviewToFront(backBtn)
        self.view.bringSubviewToFront(saveBtn)
        
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}

