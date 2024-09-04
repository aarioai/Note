/**
 * z-index
 */
UIViewController.view
    .bringSubviewToFront(_:)   // z-index : front
    .senderSubviewToBack(_:)   // z-index : back

/**
 * align
 */
public enum UIControlContentHorizontalAlignment : Int {
    case Center
    case Left
    case Right
    case Fill
}

public enum UIControlContentVerticalAlignment : Int {
    case Center
    case Top
    case Bottom
    case Fill
}

UIButton
    .contentHorizontalAlignment = .Left         // text-align: left
    .contentVerticalAlignment = .Center         // vertical-aligin: center

.frame.offsetInPlace(dx: CGFloat, dy: CGFloat) // reset position
