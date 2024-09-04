/**
 * @see https://developer.apple.com/library/ios/documentation/GraphicsImaging/Reference/QuartzCoreRefCollection/index.html
 */

#   CALayer : NSObject
##      CADisplayLink
        /**
         * 60Hz = 60 times / sec
         */
        .init(target:AnyObject, :Selector) -> CADisplayLink
        .addToRunLoop(_:NSRunLoop, forMode:String)
        .removeFromRunLoop(_:NSRunLoop, forMode:String)
        .invalidate() // removes the display link from all run loop modes
        .paused: Bool       // whether the notifications are suspended
        .duration: CFTimeInterval { get }
        .frameInterval: Int
        .timestamp: CFTimeInterval { get }  // the last displayed frame 
##      CASharpLayer : CALayer : NSObject
            .path: CGPath?
            .fillColor: CGColor?
            /**
             *  kCAFillRulNonZero
             *   Count each left-to-right path as + 1 and each right-to-left
             *   path as -1. 0 is outside, nonzero inside
             *  kCAFillRuleEvenOdd
             *   Count the total number of path crossings. Even is outside, 
             *   odd is inside.
             *      +----------------+
             *      |////////////////|
             *      |//+----------+//|
             *      |//|  +-----+ |//|
             *      |//|  |/////| |//|
             *      |//|  +-----+ |//|
             *      |//+----------+//|
             *      |////////////////|
             *      +----------------+
             */
            .fillRule: String   
                kCAFillRuleNonZero
                kCAFillRuleEvenOdd
            /**
             *  kCALineCapButt      ---------
             *  kCALineCapRound     •--------•
             *  kCALineCapSquare    ▪--------▪ 
             */
            .lineWidth: CGFloat
            .lineCap: String
                kCALineCapButt
                kCALineCapRound
                kCALineCapSquare
            .lineDashPattern: [NSNumber]?
            .lineDashPhase: CGFloat
            /**
             *  kCALineJoinMiter
             *      /\
             *     / \
             *  kCALineJoinRound
             *      ⌒ 
             *     / \
             *    /  \
             *  kCALineJoinBevel
             *      -
             *     / \
             *    /  \
             */
            .lineJoin: String
                kCALineJoinMiter
                kCALineJoinRound
                kCALineJoinBevel
            .miterLimit: CGFloat
            .strokeColor： CGColor?
            .strokeStart: CGFloat
            .strokeEnd: CGFloat
