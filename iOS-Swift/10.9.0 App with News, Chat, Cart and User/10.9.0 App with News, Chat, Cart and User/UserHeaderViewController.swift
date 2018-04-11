//
//  UserHeaderViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/10/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserHeaderViewController: UIViewController {
    func settingView(sender: UIButton) {
        presentViewController(UserSignUpViewController(), animated:true, completion:nil)
    }
    
    func signUpView(sender: UIButton) {
        presentViewController(UserSignUpViewController(), animated:true, completion:nil)
    }
    
    func signInView(sender: UIButton) {
        // let storyBoard = UIStoryboard(name: "Main", bundle:nil)
        
        //let nextViewController = storyBoard.instantiateViewControllerWithIdentifier("nextView") as! UserSignInViewController
        presentViewController(UserSignInViewController(), animated:true, completion:nil)
        
    }
    func topView() {
        //let topBg = UIImage(named: "")
        let topBg = UIView()
        topBg.frame = CGRect(x:0, y:0, width: UIScreen.mainScreen().bounds.width,height: 200)
        topBg.backgroundColor = UIColor.purpleColor()
        view.addSubview(topBg)
        view.sendSubviewToBack(topBg)
        
        
        let top = UIView(frame: topBg.frame)
       // top.frame.origin.y = (navigationController?.navigationBar.bounds.height)! + UIApplication.sharedApplication().statusBarFrame.height
        top.frame.size.height -= top.frame.origin.y
        top.backgroundColor = UIColor.greenColor()
        topBg.addSubview(top)
        
        
        let settingBtnSize = CGSize(width: 80, height: 26)
        let settingBtnMarginRight: CGFloat = 20
        let settingBtn = UIButton(frame: CGRect(origin: CGPoint(x: UIScreen.mainScreen().bounds.width - settingBtnSize.width - settingBtnMarginRight, y: 0), size: settingBtnSize))
        
        settingBtn.layer.borderColor = UIColor.lightGrayColor().CGColor
        settingBtn.layer.borderWidth = 1
        settingBtn.layer.cornerRadius = settingBtnSize.height / 2
        //settingBtn.alpha = 0.5
        settingBtn.opaque = true
        settingBtn.layer.opaque = true
        settingBtn.setTitle("设置", forState: .Normal)
        settingBtn.addTarget(self, action: #selector(UserHeaderViewController.settingView(_:)), forControlEvents: .TouchDown)
        
        top.addSubview(settingBtn)
        
        
        
        ///let avatar =
        let signBtnSize = CGSize(width: 100, height: 50)
        let signUpBtn = UIButton(frame: CGRect(origin: CGPoint(x: CGFloat(0), y: CGFloat(0)), size: signBtnSize))
        signUpBtn.setTitle("注册", forState: .Normal)
        signUpBtn.addTarget(self, action: #selector(UserHeaderViewController.signUpView(_:)), forControlEvents: .TouchDown)
        top.addSubview(signUpBtn)
        
        
        let signInBtn = UIButton(frame: CGRect(origin: CGPoint(x:100, y:0), size: signBtnSize))
        signInBtn.setTitle("登陆", forState: .Normal)
        signInBtn.addTarget(self, action: #selector(UserHeaderViewController.signInView(_:)), forControlEvents: .TouchDown)
        top.addSubview(signInBtn)
        
        
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        topView()
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}