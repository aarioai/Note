//
//  UserLoginData.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/11/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserLoginData<T> {
    var avatar: UIImage = UIImage(named: "icon_xiro")!
    var username: String
    var nickname: String?
    init(username: String, avatarResource: T? = nil, nickname: String? = nil) {
        self.username = username
        
        if avatarResource != nil {
            if (avatarResource is String.Type){  // named
                avatar = UIImage(named: String(avatarResource))!
            } else if(avatarResource is UIImage.Type) {
                avatar = avatarResource as! UIImage
            }
        }
        
        self.nickname = nickname == nil ? username : nickname
    }
}