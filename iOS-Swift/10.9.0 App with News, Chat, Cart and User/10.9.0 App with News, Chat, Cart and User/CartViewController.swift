//
//  CartViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/6/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class CartViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.backgroundColor = UIColor.cyanColor()
        tabBarItem.title = "商城"
        tabBarItem.image = UIImage(named: Conf.Assets.Tab.cart)
        tabBarItem.selectedImage = UIImage(named: Conf.Assets.Tab.cartSelected)
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}
