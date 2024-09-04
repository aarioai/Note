//
//  TabBarController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/6/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class TabBarController: UITabBarController {
    override func viewDidLoad() {
        
        let indexViewCtrl = IndexViewController()
        let indexNavCtrl = IndexNavigationController(rootViewController: indexViewCtrl)
        
        let userViewCtrl = UserTableViewController(style: .Grouped)
        let userNavCtrl = UserNavigationController(rootViewController: userViewCtrl)
        
        viewControllers = [indexNavCtrl, UserTableViewController(), CartViewController(), ShowViewController(), userNavCtrl]
        
        
        //hidesBottomBarWhenPushed = true
        
        for ctrl in viewControllers! {
            let _ = ctrl.view
        }
        
        for nav in [indexNavCtrl, userNavCtrl] {
            let _ = nav.topViewController!.view
        }
        
            
    }
}
