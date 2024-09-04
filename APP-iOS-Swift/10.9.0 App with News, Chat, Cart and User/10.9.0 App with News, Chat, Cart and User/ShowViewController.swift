//
//  ShowViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/6/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class ShowViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor.redColor()
        tabBarItem.image = UIImage(named: Conf.Assets.Tab.show)
        tabBarItem.selectedImage = UIImage(named: Conf.Assets.Tab.showSelected)
        tabBarItem.title = "晒单"

        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}