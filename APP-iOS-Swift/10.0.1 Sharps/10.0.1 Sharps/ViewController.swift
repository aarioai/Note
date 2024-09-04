//
//  ViewController.swift
//  10.0.1 Sharps
//
//  Created by Aario on 3/10/16.
//  Copyright © 2016 Aario. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    let path:CGMutablePath = CGPathCreateMutable()

    func drawOpenCircle() {
        CGPathAddArc(self.path, nil, 90, 90, 90, -3.14 * 2, 3.14 * 2, false)
    }
    func drawClosedCircle() {
        CGPathAddArc(self.path, nil, 180, 180, 50, 0, 3.14 * 2, false)
    }
    func drawRectangle() {
        let rect = CGRectMake(0, 100, 50, 50)
        CGPathAddRect(path, nil, rect)
    }
    func drawTriangle() {

        let rect = CGRectMake(0, 0, 50, 50)
        /**
        * Another way to draw a rectangle
        */
        CGPathMoveToPoint(self.path, nil, CGRectGetMinX(rect), CGRectGetMinY(rect))
        CGPathAddLineToPoint(self.path, nil, CGRectGetMaxX(rect), CGRectGetMinY(rect))
        CGPathAddLineToPoint(self.path, nil, CGRectGetMaxX(rect), CGRectGetMaxY(rect))
        //CGPathAddLineToPoint(self.path, nil, CGRectGetMinX(rect), CGRectGetMaxY(rect))
        CGPathCloseSubpath(self.path)
    }
    func drawCustomImage(size: CGSize) -> UIImage {
        // Setup our context
        let bounds = CGRect(origin: CGPoint.zero, size: size)
        let opaque = true
        let scale: CGFloat = 0
        UIGraphicsBeginImageContextWithOptions(size, opaque, scale)
        let context = UIGraphicsGetCurrentContext()
        
        // Setup complete, do drawing here
        CGContextSetStrokeColorWithColor(context, UIColor.redColor().CGColor)
        CGContextSetLineWidth(context, 2.0)
        
        CGContextStrokeRect(context, bounds)
        
        CGContextBeginPath(context)
        CGContextMoveToPoint(context, CGRectGetMinX(bounds), CGRectGetMinY(bounds))
        CGContextAddLineToPoint(context, CGRectGetMaxX(bounds), CGRectGetMaxY(bounds))
        CGContextMoveToPoint(context, CGRectGetMaxX(bounds), CGRectGetMinY(bounds))
        CGContextAddLineToPoint(context, CGRectGetMinX(bounds), CGRectGetMaxY(bounds))
        CGContextStrokePath(context)
        
        // Drawing complete, retrieve the finished image and cleanup
        let image = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        return image
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.view.backgroundColor = UIColor.blackColor()
        let rectFrame = CGRectMake(200, 300, 118, 40)
        let rectView = UIImageView(frame:rectFrame)
        rectView.backgroundColor = UIColor.greenColor()
        self.view.addSubview(rectView)
        let image = drawCustomImage(CGSize(width:200, height:200))
        rectView.image = image

        
        
        
        
        
        
        
        drawOpenCircle()
        drawTriangle()
        drawClosedCircle()
        drawRectangle()
        
        let maskLayer = CAShapeLayer()
        maskLayer.backgroundColor = UIColor.whiteColor().CGColor
        maskLayer.path = self.path
        maskLayer.fillColor = UIColor.redColor().CGColor
        maskLayer.fillRule = kCAFillRuleEvenOdd
        
        let img = UIImageView(image:UIImage(named:"default.jpeg"))
        img.frame = CGRect(x: 0, y: 0, width: UIScreen.mainScreen().bounds.width, height: UIScreen.mainScreen().bounds.width)
        img.contentMode = .ScaleToFill
        img.userInteractionEnabled = true
        img.clipsToBounds = true
        img.backgroundColor = UIColor.grayColor()

        
        
        img.layer.mask = maskLayer
        self.view.addSubview(img)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

