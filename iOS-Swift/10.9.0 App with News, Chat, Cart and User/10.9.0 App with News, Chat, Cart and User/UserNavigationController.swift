//
//  UserNavigationController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/7/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class UserNavigationController: UINavigationController {
    
    func segmentActions() {
        
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        
        //hidesBarsOnTap = true
        //viewControllers = []
        view.backgroundColor = UIColor.yellowColor()
        
        tabBarItem.image = UIImage(named: Conf.Assets.Tab.user)
        tabBarItem.selectedImage = UIImage(named: Conf.Assets.Tab.userSelected)
        // the red hint on the right-top
        tabBarItem.badgeValue = "5"
        tabBarItem.title = "我的"
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}