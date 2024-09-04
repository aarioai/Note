/**
 * @see https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/Classes/NSURLCache_Class/
 * The NSURLCache class implements the caching of responses to URL load requests by mapping NSURLRequest objects to NSCachedURLResponse objects. It provides a composite in-memory and on-disk cache, and lets you manipulate the sizes of both the in-memory and on-disk portions. You can also control the path where cache data is stored persistently.
 */
# NSURLCache : NSObject
    .sharedURLCache() -> NSURLCache
    .setSharedURLCache(_: NSURLCache)

    init(memoryCapacity: Int, diskCapacity: Int, diskPath: String?)
    
    .cachedResponseForRequest(_: NSURLRequest) -> NSCachedURLResponse?
    .storeCacheResponse(_: NSCachedURLResponse, forRequest: NSURLRequest)

    .removeAllCachedResponses()
    .removeCachedResponseForRequest(_: NSURLRequest)

    .currentDiskUsage: Int { get }
    .diskCapacity: Int
    .currentMemroryUsage: Int { get }
    .memoryCapacity: Int
