//
//  ViewController.swift
//  10.0.0 GCD
//
//  Created by Aario on 4/14/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    let buttons = ["GCD": GCD()]
    var nextViewControllers = [UIButton : UIViewController]()
    
    func buttonTouched(sender: UIButton!) {
        if let nextViewController = nextViewControllers[sender] {
            navigationController!.pushViewController(nextViewController, animated: true)
        }
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        var i: Int = 0
        for (title, nextViewController) in buttons {
            i += 1
            let button = UIButton(frame: CGRectMake(10, CGFloat(i) * 40, 200, 30))
            button.setTitle(title, forState: .Normal)
            button.backgroundColor = UIColor.orangeColor()
            button.addTarget(self, action: #selector(ViewController.buttonTouched(_:)), forControlEvents: .TouchDown)
            view.addSubview(button)
            nextViewControllers[button] = nextViewController
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }


}

