//
//  GCD.swift
//  10.0.0 GCD
//
//  Created by Aario on 4/14/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class GCD : UIViewController {
    
    func serialQueue() {
        print("--- Start: Serial Queue ---")
        let mainQueue = dispatch_get_main_queue()
        
        print("--- Stop: Serial Queue ---")
    }
    
    func concurrentQueue() {
        print("--- Start: Concurrent Queue ---")
        let globalQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
        
        print("--- Stop: Concurrent Queue ---")

    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
