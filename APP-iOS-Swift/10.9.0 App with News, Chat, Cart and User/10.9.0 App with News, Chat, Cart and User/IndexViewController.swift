//
//  IndexViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/6/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//


import UIKit

class IndexViewController: UIViewController {
    
    func segmentActions() {
        
    }
    
    func nav() {
        let segCtrl = UISegmentedControl(items: [UIImage(named: "tabFanhui")!, UIImage(named: "tabFanhuiPress")!])
        segCtrl.frame = CGRectMake(0, 0, 90, 40)
        //segCtrl.segmentedControlStyle = .UISegmentedControlStyleBar
        segCtrl.momentary  = true
        segCtrl.addTarget(self, action: #selector(IndexViewController.segmentActions), forControlEvents: .TouchDown)
        //let segBarItem = UIBarButtonItem(customView: segCtrl)
        //navigationItem.rightBarButtonItem = segBarItem
        navigationItem.titleView = segCtrl
        
        title = "首页"
        
        //navigationController?.hidesBarsOnTap = true
        
        //print(tabBarController == parentViewController)
        
        //navigationController?.tabBarItem.title = "首3页"
        
        
        //navigationController?.tabBarItem.image = UIImage(named: Conf.Assets.Tab.index)
        
        //navigationController?.tabBarItem.selectedImage = UIImage(named: Conf.Assets.Tab.indexSelected)
        
        // the red hint on the right-top
        //navigationController?.tabBarItem.badgeValue = "5"

    }
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor.redColor()
        
        nav()
        
        
        let testViewCtrl = IndexTestViewController()
        //addChildViewController(testViewCtrl)
        view.addSubview(testViewCtrl.view)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}