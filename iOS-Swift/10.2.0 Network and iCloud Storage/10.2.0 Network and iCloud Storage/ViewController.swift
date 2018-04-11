//
//  ViewController.swift
//  10.2.0 Network and iCloud Storage
//
//  Created by Aario on 3/23/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//


import UIKit
import Alamofire
//import AlamofireImage


class ViewController: UIViewController {
    
    func request() {
        Alamofire.request(.GET, Conf.URL.requestJSON, parameters: ["name": "Aario"])
            .validate(statusCode: 200..<300)
            //  .validate(contentType: ["application/json"])
            .responseString {
                response in
            }
            .responseJSON {
                response in
                debugPrint(response)
                print(response.request)  // original URL request
                print(response.response) // URL response
                print(response.data)     // server data
                print(response.result)   // result of response serialization
                
                if let JSON = response.result.value {
                    print("JSON: \(JSON)")
                }
        }
    }
    
    
    func uploadFile() {
        if let fileURL = NSBundle.mainBundle().URLForResource("AarioAi", withExtension: "jpeg"){
            var imageData : NSData? = nil
            if let image = UIImage(named: "loading2.gif") {
                let filetype = "gif"
                switch filetype {
                case "jpeg", "jpg":
                    imageData = UIImageJPEGRepresentation(image, 1.0)
                //case "gif":   // animated GIF is not supported
                    //imageData = UIImagePNGRepresentation(image)
                    //imageData = NSData(contentsOfFile: "animated.gif")
                case "png":
                    imageData = UIImagePNGRepresentation(image)
                default:
                    imageData = UIImagePNGRepresentation(image)
                }
            }
            
            let gifURL = NSBundle.mainBundle().URLForResource("animated2", withExtension: "gif")!
            
            Alamofire.upload(.POST, Conf.URL.uploadFile, headers: nil, multipartFormData: {
                // POST file[]=xxxx&&file[]=xxxxx
                multipartFormData in
                multipartFormData.appendBodyPart(fileURL: fileURL, name: "file[]")
                multipartFormData.appendBodyPart(data: imageData!, name: "file[]", fileName: "loading2.gif", mimeType: "image/gif")
                multipartFormData.appendBodyPart(fileURL: gifURL, name: "file[]")
                },
                             encodingCompletion: {
                                encodingResult in
                                switch encodingResult {
                                case .Success(let upload, _, _):
                                    upload.responseJSON { response in
                                        debugPrint(response)
                                    }
                                case .Failure(let encodingError):
                                    print(encodingError)
                                }
            })
        }
    }
    
    
        override func viewDidLoad() {
        super.viewDidLoad()
        
        
        //request()
        uploadFile()
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}
