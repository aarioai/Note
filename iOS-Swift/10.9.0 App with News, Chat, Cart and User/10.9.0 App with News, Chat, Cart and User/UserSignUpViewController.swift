//
//  UserSignUpViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/7/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserSignUpViewController: UIViewController {
    
    func back(sender: UIBarButtonItem) {
        
        
        dismissViewControllerAnimated(true, completion: {
            //print("DD")
        })
    }
    func header() {
        let headerBg = UIView(frame: CGRect(x:0, y:0, width: UIScreen.mainScreen().bounds.width, height: 100))
        headerBg.backgroundColor = UIColor.lightGrayColor()
        view.addSubview(headerBg)
        
        let header = UIView(frame: CGRect(x: 0, y: UIApplication.sharedApplication().statusBarFrame.height, width: UIScreen.mainScreen().bounds.width, height: headerBg.frame.size.height - UIApplication.sharedApplication().statusBarFrame.height))
        headerBg.addSubview(header)
        let backBtn = UIButton(frame: CGRect(x:0, y:0, width:50, height:50))
        backBtn.setTitle("X", forState: .Normal)
        backBtn.addTarget(self, action: #selector(UserSignInViewController.back), forControlEvents: .TouchDown)
        header.addSubview(backBtn)
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor.orangeColor()
        title = "注册"
        header()
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
}