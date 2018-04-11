//
//  NSURLDemo.swift
//  10.3.0 Storage and Cache
//
//  Created by Aario on 4/13/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit


class NSURLCacheDemo : UIViewController {
    var removeCache = false
    let url = NSURL(string: "https://api.github.com/users/AarioAi")!
    
    
    func httpGet(request: NSURLRequest!, callback: (String, String?) -> Void) {
        let session = NSURLSession.sharedSession()
        let task = session.dataTaskWithRequest(request){
            (data, response, error) -> Void in
            if error != nil {
                callback("", error!.localizedDescription)
            } else {
                let result = NSString(data: data!, encoding:
                    NSASCIIStringEncoding)!
                callback(result as String, nil)
            }
        }
        task.resume()
    }
    
    func callHTTPGet() {
        let request = NSMutableURLRequest(URL: url)
        httpGet(request){
            (data, error) -> Void in
            if error != nil {
                print(error)
            } else {
                print(data)
            }
        }
    }
    
    func request() {
        let request = NSMutableURLRequest(URL: url)
        request.cachePolicy = .ReturnCacheDataElseLoad
        
        //let params = ["name" : "Aario"]
        //let params = NSKeyedArchiver.archivedDataWithRootObject(params)
        //print(httpBody)
        //print(NSKeyedUnarchiver.unarchiveObjectWithData(httpBody))
        
        //request.HTTPBody = httpBody
        
        if !cachedResponseForRequest(request) {
            let session = NSURLSession.sharedSession()
            let task = session.dataTaskWithRequest(request) { data, response, error in
                print("--- task closure: ----")
                if error != nil {
                    print(error!.localizedDescription)
                } else {
                    self.handleNSDataToJson(data!)
                    let cache = NSURLCache.sharedURLCache()
                    let cachedURLResponse = NSCachedURLResponse(response: response!, data: data!)
                    cache.storeCachedResponse(cachedURLResponse, forRequest: request)
                }
            }
            task.resume()
            
            //            let taskURL = session.dataTaskWithURL(url) { data, response, error in
            //
            //                print("taskURL closure: ")
            //                self.handleNSDataToJson(data!)
            //            }
            //            taskURL.resume()
            
        }
        
    }
    
    func cachedResponseForRequest(request: NSURLRequest) -> Bool {
        let cache = NSURLCache.sharedURLCache()
        let response = cache.cachedResponseForRequest(request)
        if (removeCache) {
            cache.removeCachedResponseForRequest(request)
            cache.removeAllCachedResponses()
            print("Cache Removed")
            removeCache = !removeCache
            return true
        }
        
        if response == nil {
            print("No cache")
            return false
        } else {
            print("Cache exists")
            self.handleNSDataToJson(response!.data)
            return true
        }
    }
    
    func handleNSDataToJson(data: NSData) {
        do {
            let json = try NSJSONSerialization.JSONObjectWithData(data, options: .AllowFragments)
            print(json)
            print(json["avatar_url"])
        } catch {
            let j = NSString(data: data, encoding:
                NSASCIIStringEncoding)! as String
            print(j)
        }
    }
    func resend(sender: UIButton!) {
        request()
    }
    func removeCahce(sender: UIButton!) {
        removeCache = true
        request()
    }
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor.whiteColor()
        
        //callHTTPGet()
        request()
        
        let resendButton = UIButton(frame: CGRectMake(10, 100, 200, 30))
        resendButton.backgroundColor = UIColor.greenColor()
        resendButton.setTitle("Re-Send", forState: .Normal)
        resendButton.addTarget(self, action: #selector(NSURLCacheDemo.resend(_:)), forControlEvents: .TouchDown)
        view.addSubview(resendButton)
        
        let removeCacheButton = UIButton(frame: CGRectMake(10, 140, 200, 30))
        removeCacheButton.backgroundColor = UIColor.greenColor()
        removeCacheButton.setTitle("Remove Cache", forState: .Normal)
        removeCacheButton.addTarget(self, action: #selector(NSURLCacheDemo.removeCahce(_:)), forControlEvents: .TouchDown)
        view.addSubview(removeCacheButton)
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}