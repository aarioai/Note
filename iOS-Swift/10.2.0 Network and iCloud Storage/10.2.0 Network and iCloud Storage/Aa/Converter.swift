//
//  Converter.swift
//  10.1.1 Photo - Avatar
//
//  Created by Aario on 3/22/16.
//  Copyright © 2016 Aario. All rights reserved.
//

import UIKit

class Converter {
    static func  UIColorFromRGB(rgb: UInt, _ alpha : CGFloat = 1.0) -> UIColor {
        return UIColor(
            red: CGFloat((rgb & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((rgb & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(rgb & 0x0000FF) / 255.0,
            alpha: alpha
        )
    }
}