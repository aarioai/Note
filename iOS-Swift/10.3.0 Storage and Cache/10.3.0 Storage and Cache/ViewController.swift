//
//  ViewController.swift
//  10.3.0 Storage and Cache
//
//  Created by Aario on 4/13/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
import Haneke

class ViewController: UIViewController {
    static let demos = ["Haneke": HanekeDemo(), "NSURLCache": NSURLCacheDemo()]
    var demos = [UIButton : UIViewController]()
    
    func goNextViewController(sender: UIButton!) {
        if let nextViewController = demos[sender] {
            navigationController?.pushViewController(nextViewController, animated: true)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        var i = 0
        for (buttonTitle, nextViewController) in self.dynamicType.demos {
            
            let button = UIButton(frame: CGRectMake(10, 220 + 35 * CGFloat(i), 180, 25))
            button.backgroundColor = UIColor.cyanColor()
            
            button.setTitle(buttonTitle, forState: .Normal)
            button.addTarget(self, action: #selector(ViewController.goNextViewController(_:)), forControlEvents: .TouchDown)
            view.addSubview(button)
            demos[button] = nextViewController
            i += 1
        }
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

