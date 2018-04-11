//
//  UseHeaderNotLoginedTableViewCell.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/11/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserHeaderNotLoginedTableViewCell: UITableViewCell {
    static var username: String = "Not Login"
    static var nickname: String = "未登录"
    static var test: Int = 100
    
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        backgroundColor = UIColor.whiteColor()
        imageView!.image = UIImage(named: "icon_xiro")!
        
        contentView.addSubview(imageView!)
        
    }
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        //fatalError("init(coder:) has not been implemented")
    }
    
    override func drawRect(rect: CGRect) {
        let context = UIGraphicsGetCurrentContext()
        CGContextSetFillColorWithColor(context, UIColor.whiteColor().CGColor)
        CGContextFillRect(context, rect)
        CGContextSetStrokeColorWithColor(context, UIColor.init(red: 0xE2/255.0, green: 0xE2/255.0, blue: 0xE2/255.0, alpha: 1).CGColor)
        CGContextStrokeRect(context, CGRectMake(0, rect.size.height - 1, rect.size.width, 1))
        
    }
    override func layoutSubviews() {
        imageView!.frame = CGRectMake(0, 0, 90, 90)
    }
    
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
        
        
        
    }
    
    override func setSelected(selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
        
        // Configure the view for the selected state
    }
    
}