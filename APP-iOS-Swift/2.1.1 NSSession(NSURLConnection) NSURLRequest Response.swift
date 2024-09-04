/*
 @note Allow host in xcode Info.plist first

[Client] NSURLRequest  ---- NSURLConnection ---> [Server]


 */


enum NSURLRequestCachePolicy : UInt {
    UseProtocolCachePolicy
    ReloadIgnoringLocalCacheData
    ReloadIgnoringLocalAndRemoteCacheData
    static var ReloadIgnoringCacheData: NSURLRequestCachePolicy { get }
    ReturnCacheDataElseLoad
    ReturnCacheDataDontLoad
    ReloadRevalidatingCacheData
}

# NSURLConnection : 
    Using NSSession to replace
# NSSession : NSObject
    .init(:NSURLSessionConfiguration, :NSURLSessionDelegate? = nil, :NSOperationQueue? = nil)
    .sharedSession() -> NSURLSession
    
    .configuration
    .delegate
    .delegateQueue
    .sessionDescription
    
    .dataTaskWithURL(_: NSURL
                     , completionHandler: (NSData?, NSURLResponse?, NSError?) -> Void ? = nil)
        ) -> NSURLSessionDataTask
    
    .dataTaskWithRequest(_: NSURLRequest, completionHandler? = nil)
            -> NSURLSessionDataTask
    
# NSURLSessionTask : NSObject
    .cancel()
    .resume()           // start
    .suspend()
    .state()
    .priority()
    
    .countOfBytesExpectedToReceive: Int64 { get }
    .countOfBytesReceived: Int64 { get }
    .countOfBytesExpectedToSend: Int64 { get }
    .countOfBytesSent: Int64 { get }

    .currentRequest: NSURLRequest? { get }
    .originalRequest: NSURLRequest? { get }
    .response: NSURLResponse? { get }
    .taskDescription: String?
    .taskIdentifier: Int { get }
    .error: NSError? { get }
    
# NSURLRequest : NSObject
    convenience .init(:NSURL)
    init(:NSURL, :NSURLRequestCachePolicy, timeoutInterval: NSTimeInterval)
    .cachePolicy: NSURLRequestCachePolicy { get }

    // whether the request should continue transmitting data before receiving a response from an earlier transmission. 
    .HTTPShouldUsePipelining: Bool { get }
    .mainDocumentURL: NSURL? { get }
    .timeoutInterval: NSTimeInterval { get }
    .networkServiceType: NSURLRequestNetworkServiceType { get }
    .URL: NSURL? { get }

    .allHTTPHeaderFields: [String : String]? { get }
    .HTTPBody: NSData? { get }
    .HTTPBodyStream: NSInputStream? { get }
    .HTTPMethod: String? { get }
    .HTTPShouldHandleCookies: Bool { get }
    .valueForHTTPHeaderField(_ field: String) -> String?
    .allowsCellularAccess : Bool { get }
    
## NSMutableURLRequest : NSURLRequest : NSObject


# NSCachedURLResponse
    .init(:NSURLResponse, :NSData)
    .init(:NSURLResponse, :NSData, userInfo: [NSObject : AnyObject]?, 
          :NSURLCacheStoragePolicy)
    
    .data: NSData { get }
    .response: NSURLResponse { get }
    .storagePolicy: NSURLCacheStoragePolicy { get }
    .userInfo: [NSObject : AnyObject]? { get }
    
