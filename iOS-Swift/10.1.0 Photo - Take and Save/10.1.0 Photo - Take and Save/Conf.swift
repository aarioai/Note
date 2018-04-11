//
//  Conf.swift
//  10.1.0 Photo - Take and Save
//
//  Created by Aario on 3/9/16.
//  Copyright © 2016 Aario. All rights reserved.
//

import UIKit

struct Conf {
    struct Theme {
        static let tintColor = UIColor(red: CGFloat(153.0/255), green: CGFloat(222.0/255.0), blue: CGFloat(64.0/255.0), alpha: 1)
        static let bgColor = UIColor(red: CGFloat(153.0/255), green: CGFloat(222.0/255.0), blue: CGFloat(64.0/255.0), alpha: 1)
        
        struct btnDefault {
            static let defaultColor = bgColor
            
            static let hoverColor = UIColor.lightGrayColor()

            static let disabledColor = UIColor(red:0.2431, green:0.5216, blue:0.6196, alpha:0.25)
        }
        
        
    }
}