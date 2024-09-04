//
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/10/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit

class UserTableViewList: NSObject, NSCoding {
    // MARK: Properties
    
    var savingFilename : String? {
        set {
            if newValue != nil {
                saveData(self)
            }
        }
        get {
            return self.savingFilename
        }
    }
    
    var didSelectRowAction: Selector?
    var nextViewController: UIViewController?
    
    var name: String
    var photo: UIImage?
    var cellBadgeValue: Int?
    
    
    static let DocumentsDirectory = NSFileManager().URLsForDirectory(.DocumentDirectory, inDomains: .UserDomainMask).first!
    static let ArchiveURL = DocumentsDirectory.URLByAppendingPathComponent("TableViewData", isDirectory: true).URLByAppendingPathComponent("sss.tbvData")
    
    
    func saveData(data: UserTableViewList) {
        let isSuccessfulSave = NSKeyedArchiver.archiveRootObject(data, toFile: UserTableViewList.ArchiveURL.path!)
        if !isSuccessfulSave {
            print("Failed to save meals...")
        }
    }
    
    func loadData() -> [UserTableViewList]? {
        return NSKeyedUnarchiver.unarchiveObjectWithFile(UserTableViewList.ArchiveURL.path!) as? [UserTableViewList]
    }
    
    // MARK: Types
    
    struct PropertyKey {
        static let imageViewKey = ""
        static let textLabelKey = ""
        static let detailLabelKey = ""
        static let accessoryViewKey = ""
        
        
        static let nameKey = "name"
        static let photoKey = "photo"
        static let ratingKey = "rating"
    }
    
    // MARK: Initialization
    
    init?(name: String, photo: UIImage? = nil, nextViewController: UIViewController? = nil, cellBadgeValue: Int? = nil) {
        // Initialize stored properties.
        self.name = name
        self.photo = photo
        self.cellBadgeValue = cellBadgeValue
        self.nextViewController = nextViewController
        super.init()
        
    }
    
    // MARK: NSCoding
    
    func encodeWithCoder(aCoder: NSCoder) {
        aCoder.encodeObject(name, forKey: PropertyKey.nameKey)
    }
    
    required convenience init?(coder aDecoder: NSCoder) {
        let name = "TEST"
        let photo = UIImage(named: "icon_xiro")
        self.init(name: name, photo: photo)
    }
    
}