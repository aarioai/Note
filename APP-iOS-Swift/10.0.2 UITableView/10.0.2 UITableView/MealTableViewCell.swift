//
//  MealTableViewCell.swift
//  FoodTracker
//
//  Created by Jane Appleseed on 5/27/15.
//  Copyright © 2015 Apple Inc. All rights reserved.
//  See LICENSE.txt for this sample’s licensing information.
//

import UIKit

class MealTableViewCell: UITableViewCell {
    // MARK: Properties
    
    
    let imageSize = CGSize(width: CGFloat(90), height: CGFloat(90))
    let imageMargin: CGFloat = 9
    var nameLabel: UILabel! = UILabel()
    @IBOutlet weak var photoImageView: UIImageView!
    @IBOutlet weak var ratingControl: RatingControl!
    
    override init(style: UITableViewCellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        separatorInset = UIEdgeInsets(top: 0, left: 100, bottom: 0, right: -100)
        

    }
    
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override func layoutSubviews() {
        
        nameLabel?.frame = CGRectMake(imageSize.width + imageMargin, 0, 200, 50)
    }
    

    override func awakeFromNib() {
        super.awakeFromNib()
        
        contentView.addSubview(nameLabel)

        if let t = nameLabel?.text {
            print(t)
        }

    }

    override func setSelected(selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
