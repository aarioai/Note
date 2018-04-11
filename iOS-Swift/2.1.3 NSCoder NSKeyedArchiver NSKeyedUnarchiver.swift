
# NSCoder
/**
 * @see https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/Classes/NSCoder_Class/index.html#//apple_ref/occ/cl/NSCoder
 */

.encode<T>(_: <T>, forKey: String)

## NSKeyedArchiver : NSCoder : NSObject
enum NSPropertyListFormat : UInt {
    OpenStepFormat
    XMLFormat_v1_0
    BinaryFormat_v1_0
}
/**
 * NSKeyedArchiver, a concrete subclass of NSCoder, provides a way to encode objects (and scalar values) into an architecture-independent format that can be stored in a file. 
 */

.initforWritingWithMutableData data: NSMutableData)


.archivedDataWithRootObject(_: AnyObject) -> NSData)
.archiveRootObject(_ rootObject: AnyObject, toFile path: String) -> Bool
    
.finishEncoding()
.outputFormat: NSPropertyListFormat    // ASCII, XML, Binary
.requiresSecureCoding: Bool

## NSKeyedUnarchiver : NSCoder : NSObject
    .unarchiveObjectWithData(_: AnyObject) -> AnyObject?
    .unarchiveObjectWithFile(_ path: String) -> AnyObject?
