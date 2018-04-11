//
//  Haneke.swift
//  10.3.0 Storage and Cache
//
//  Created by Aario on 4/13/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
import Haneke
class HanekeDemo : UIViewController {
    static var imageViewURL = "https://avatars.githubusercontent.com/u/8835297?v=3"
    
    func hanekeParseJson() {
        let cache = Cache<JSON>(name: "github")
        let URL = NSURL(string: "https://api.github.com/users/AarioAi")!
        
        cache.fetch(URL: URL).onSuccess { data in
            print(data)
            if let url = data.dictionary?["avatar_url"] as? String {
                self.dynamicType.imageViewURL = url
            }
        }
    }
    
    func hanekeCacheMedia() {
        let cache = Shared.dataCache
        
        //cache.set(value: "DATA", key: "funny-games.mp4")
        
        // Eventually...
        
        cache.fetch(key: "funny-games.mp4").onSuccess { data in
            // Do something with data
        }
        
    }
    func hanekeDisplayRemoteImage() {
        let imageView = UIImageView(frame: CGRectMake(0, 0, 100, 100))
        imageView.hnk_setImageFromURL(NSURL(string: self.dynamicType.imageViewURL)!)
        view.addSubview(imageView)
    }
    
    func hanekeFormats() {
        let cache = Shared.imageCache
        
        let iconFormat = Format<UIImage>(name: "icons", diskCapacity: 10 * 1024 * 1024) { image in
            print("DDD")
            image.drawInRect(CGRectMake(0, 0 ,10, 10), blendMode: .ColorDodge, alpha: 0.5)
            return image
        }
        cache.addFormat(iconFormat)
        
        let URL = NSURL(string: self.dynamicType.imageViewURL)!
        cache.fetch(URL: URL, formatName: "icons").onSuccess { image in
            print("DD")
            let imv = UIImageView(frame: CGRectMake(180, 180, 100, 100))
            
            imv.image = image
            
            self.view.addSubview(imv)
            
        }
        
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        hanekeParseJson()
        hanekeDisplayRemoteImage()
        hanekeFormats()
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

}
