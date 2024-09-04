//
//  IndexNavigationController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/7/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class IndexNavigationController: UINavigationController {
    
    func segmentActions() {
        
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        navigationBar.tintColor = UIColor.redColor()
        //navigationBar.barTintColor = UIColor.blueColor()
        
        tabBarItem.image = UIImage(named: Conf.Assets.Tab.index)
        tabBarItem.selectedImage = UIImage(named: Conf.Assets.Tab.indexSelected)
        tabBarItem.title = "首页"

        // the red hint on the right-top
        // tabBarItem.badgeValue = "5"

        
        //setNavigationBarHidden(true, animated: true)
        hidesBarsOnTap = true
        

        //viewControllers = []
        view.backgroundColor = UIColor.yellowColor()
        
        
        toolbarHidden = false

    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}