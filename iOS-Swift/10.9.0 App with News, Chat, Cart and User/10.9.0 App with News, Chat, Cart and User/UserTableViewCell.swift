//
//  UserTableViewCell.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/7/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserTableViewCell: UITableViewCell {
    
    
    //var nameLabel: UILabel! = UILabel()
    
    //var detailImageView =
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        backgroundColor = UIColor.whiteColor()

        //layoutMargins = UIEdgeInsets(top: 9, left:29, bottom: 9, right: 9)
        contentView.preservesSuperviewLayoutMargins = false
        //contentView.addSubview(nameLabel)
        contentView.addSubview(textLabel!)
        contentView.addSubview(imageView!)
        
        accessoryView = UIImageView(image: UIImage(named: "icon_entersetting"))

        contentView.addSubview(accessoryView!)
        //separatorInset = UIEdgeInsets(top: 10, left: 10, bottom: 0, right: -100)
        //separatorInset = UIEdgeInsetsZero
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
        contentView.frame.origin = CGPoint(x: Conf.Size.TableView.cellMargins.top, y: Conf.Size.TableView.cellMargins.left)
        
        imageView!.frame = CGRectMake(0, 0, Conf.Size.TableView.cellHeight, Conf.Size.TableView.cellHeight)

        textLabel!.frame = CGRectMake(imageView!.frame.width + Conf.Size.TableView.cellMargins.left, 0, 200, 24)
        
        accessoryView!.frame = CGRectMake(frame.width - Conf.Size.TableView.cellHeight, (Conf.Size.TableView.cellHeight - Conf.Size.TableView.detailViewImageSize.height) / 2, Conf.Size.TableView.detailViewImageSize.width, Conf.Size.TableView.detailViewImageSize.height)
    }


    
    override func awakeFromNib() {
        super.awakeFromNib()
        
    }
    
    override func setSelected(selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
        
        // Configure the view for the selected state
    }

}