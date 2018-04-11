/**
 * @see https://developer.apple.com/library/ios/documentation/GraphicsImaging/Reference/CGPath/index.html#//apple_ref/doc/uid/TP30000959
 */

struct CGRect {origin:CGPoint, size: CGSize}
# CGPath : NSObject
    // Creating and Managing Paths
    CGPathCreateMutable() -> CGMutablePath
    

    // Modifying Quartz Paths
    /**
     * x, y: the x,y of the center point of the arc
     *  startAngle: in radians, 1 radians = 1 * 180/PI
     *  endAngle:
     * @example
     *  startAngle = 0, endAngle = 3.14 / 2
     *                      |
     *                      |
     *          -----------0,0----0,r->  startAngle = 0 rad = 0 degree
     *                      |  /)
     *                      | /)
     *                      |/)
     *           endAngle = 3.14 rad / 2 = 90 degree
     *  A_arc = A_sector - A_triangle
     *        = (90 / 360) * (2 * PI * r) - (r * r) / 2
     * @example
     *  startAngle = 3.14 / 4, endAngle = 3.14
     *                      |
     *                      |
     *         ------------0,0----------->
     *   endAngle       (\  |
     *                   (\\| 
     *                    (\|\\ 
     *                      ︶︶ 
     *                         startAngle = 3.14 rad / 4 = 45 degree
     * @notice
     *  open circle:    -3.14 * 2, 3.14 * 2
     *  close circle:   0, 3.14 * 2
     */
    CGPathAddArc(_:CGMutablePath, _ m:UnsafePointer<CGAffineTransform>,
                 _ x:CGFloat, _ y:CGFloat, _ radius:CGFloat,
                 _ startAngle: CGFloat, _ endAngle: CGFloat, 
                 _clockwise:Bool)
    
    
    CGPathMoveToPoint(_:?, _ m, _ x, _ y) 
    CGPathAddLineToPoint(_:?, _ m, _ x, _ y)
    CGPathCloseSubpath(_:?)   
    
    /**
     * @note This is a convenience function that adds a rectangle to a path,
     *   using the following sequence of operations:
     *      start at origin:    CGPathMoveToPoint()
     *              CGRectGetMinX(rect), CGRectGetMinY(rect)
     *      add bottom edge:    CGPathAddLineToPoint()
     *              CGRectGetMaxX(rect), CGRectGetMinY(rect)
     *      add right edge:     CGPathAddLineToPoint()
     *              CGRectGetMaxX(rect), CGRectGetMaxY(rect)
     *      add top edge:       CGPathAddLineToPoint()
     *              CGRectGetMinX(rect), CGRectGetMaxY(rect)
     *      add left edge:      CGPathCLoseSubpath(_:CGMutablePath)
     */
    CGPathAddRect(_:CGMutablePath, _ m:UnsafePointer<CGAffineTransform>, 
                  _ :CGRect)

# CGImage
    // Creating Bitmap Images

    /**
     * @notice if CGRect's origin is not a nature number, it'll crop a
     *  rectangle in the CGImage 1 px wider and 1 px taller than the CGRect
     *  e.g. 
     *      let img = UIImageView(image: UIImage(named:"Aario.png"))s
     *      let cg = img.image.CGImage
     *      let rect = CGRectMaker(0.1111, 10.6666, 180, 180)
     *      let im: CGImageRef = CGImageCreateWithImageInRect(cg, rect)
     *      // it'll crop from (0, 10), 
     *      //    and calculate from (1, 11), and width 180 
     *      print(rect.size)                                 // (180, 180)
     *      print(CGImageGetWidth(im), CGImageGetHeight(im)) // 181,181
     */
    .CGImageCreateWithImageInRect(_:CGImage?, _:CGRect) -> CGImage?
    // Creating an Image Mask
    // Getting Information

    // UIImage.CGImage
    .CGImageGetWidth(_:CGImage?) -> Int
    .CGImageGetHeight(_:CGImage?) -> Int

# CGAffineTransform

/**
 * Known:
 *  Any a point(x, y) tranfroms by matrix CGAffineTransform, the tranformed
 *    point(x', y')   
 *    [x' y' 1] = [x y 1] * CGAffineTransform
 *    x' = ax + cy + tx
 *    y' = bx + dy + ty
 */
struct CGAffineTransform {
    [ a   b  0 ]
    [ c   d  0 ]
    [ tx  ty 1 ]
}
    /**
     * @example resize an image to half size
     *  let img = UIImageView(image: UIImage(named: "Aario.png"))
     *  let matrix = CGAffineTransform(0.5, 0.5)
     *  let transformedRect = CGRectApplyAffineTransform(img.frame, matrix)
     *  
     */
    CGRectApplyAffineTransform(_:CGRect, _:CGAffineTransform) -> CGRect
    
