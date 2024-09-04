/**
 * @see https://developer.apple.com/library/mac/documentation/Cocoa/Reference/Foundation/ObjC_classic/index.html
 */
 
 #  NSBundle

    // Getting

    /**
     * Returns the NSBundle that corresponds to the directory where the 
     *  the current application executable is located
     */
    .mainBundle() -> NSBundle 

    // e.g. file:///Users/aa/Library/Developer/CoreSimulator/Devices/25C4D6CF-2482-40CA-9A6E-9493A918DDBA/data/Containers/Bundle/Application/D1F6DE41-0EB8-43A6-B4DC-70AA524E9620/10.1.1%20Photo%20-%20Avatar.app/
    .bundleURL: NSURL { get }
    .bundlePath: String { get }

#   NSURL
    .init?(string URLString:String) -> NSURL    
    /**
     * e.g.
     *  let baseURL = NSURL(string: "file:///path/app/")
     *  let s = NSURL(string: "Resources/Aario.gif", relativeToURL: baseURL)
     */
    .init?(string, relativeToURL:USNURL?) -> NSURL
    
    /**
     * e.g.
     *  let bundle = NSBundle.mainBundle().bundleURL  // file:///app/
     *  let path = bundle.URLByAppendingPathComponent("Aario.gif")
     *              // file:///app/Aario.gif
     *  let path2 = bundle.URLByAppendingPahtComponent("Resources", isDirectory: true)
     *              // file:///app/Resources/
     */
    .URLByAppendingPathComponent(_:String[, isDirectory: Bool]) -> NSURL
    /**
     * e.g. 
     *  let path = NSBundle.mainBundle().URLForResource("Aario.gif", 
     *              withExtension: "")      // file:///app/Araio.gif
     *  let path = NSBundle.mainBundle().URLForResource("Aario",
    *               withExtension: "gif")
     */
    .URLForResource(_ filename: String?, withExtension: String?
                    [, subdirectory: String?, inBundleWithURL: NSURL])
    .URLForResource(_ filename?, withExtension?) -> NSURL
    .URLsForResourcesWithExtension(_ ext?, subdirectory?) -> [NSURL]?



    
# NSFileManager
enum NSSearchPathDirectory : UInt {
    ApplicationDirectory            // /Applications
    DemoApplicationDirectory        // unsupported applications
    DeveloperApplicationDirectory   // /Developer/Applications
    AdminApplicationDirectory       
    LibraryDirectory                // /Library
    DeveloperDirectory              // /Developer
    UserDirectory                   // /Users
    DocumentationDirectory
    DocumentDirectory               
    CoreServiceDirectory            // System/Library/CoreServices
    AutosavedInformationDirectory   // Library/Autosave
    DesktopDirectory
    CachesDirectory
    ApplicationSupportDirectory
    DownloadsDirectory
    InputMethodsDirectory
    MoviesDirectory
    MusicDirectory
    PicturesDirectory
    PrinterDescriptionDirectory
    SharedPublicDirectory
    PreferencePanesDirectory
    ApplicationScriptsDirectory
    ItemReplacementDirectory
    AllApplicationsDirectory
    AllLibrariesDirectory
    TrashDirectory    
}

struct NSSearchPathDomainMask : OptionSetType {
    UserDomainMask      // user's home directory, personal items
    LocalDomainMask     // available to everyone on this machine
    NetworkDomainMask   // available on network (/Network)
    SystemDomainMask    // Provided by Apple, can't be modified(/System)
    AllDomainsMask
}
    .defaultManager() -> NSFileManager  // return the shared file manager
    
    // Locating System Directories

    /**
     * Locates (and optionally creats) a directory
        let desktopURL = NSURL(fileURLWithPath: "/Users/aa/Library/Test")
        do {
            let tmpURL = try NSFileManager.defaultManager().URLForDirectory(.ItemReplacementDirectory, inDomain: .UserDomainMask, appropriateForURL: desktopURL, create: true)
            print(tmpURL)
        } catch {
        }
        // It creates a new temporary directory in the form of `file:///Users/aa/Library/(A%20Document%20Being%20Saved%20By%2010.9.0%20App%20with%20News,%20Chat,%20Cart%20and%20User%204)/`
     */
    .URLForDirectory(_: NSSearchPathDirectory, 
                    inDomain domain: NSSearchPathDomainMask,
                    appropriateForURL url: NSURL?, 
                    create shouldCreate: Bool) throws -> NSURL
    
    .URLsForDirectory(_: NSSearchPathDirectory,
                      inDomain domainMask) -> [NSURL]
