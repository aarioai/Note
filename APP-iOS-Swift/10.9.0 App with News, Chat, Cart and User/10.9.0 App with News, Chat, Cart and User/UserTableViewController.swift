//
//  UserTableViewController.swift
//  10.9.0 App with News, Chat, Cart and User
//
//  Created by Aario on 4/7/16.
//  Copyright © 2016 Luexu.com. All rights reserved.
//

import UIKit
class UserTableViewController: UITableViewController {
    
    
    var cells = [UserTableViewList]()
    var systemSettings = [UserTableViewList]()
    
   
    //var ulTableView = UITableView()
    let cellIdentifier = "UserTableViewCell"
    
    func loadData() {
        let photo1 = UIImage(named: "icon_album")!
        let cell1 = UserTableViewList(name: "我的订单", photo: photo1)!
        
        let photo2 = UIImage(named: "ic_g_airplane")!
        let cell2 = UserTableViewList(name: "我的财富", photo: photo2)!
        
        let photo3 = UIImage(named: "icon_credits")!
        let cell3 = UserTableViewList(name: "售后客服", photo: photo3)!
        
        
        
         cells += [cell1, cell2, cell3]
        
        
        let settingImage = UIImage(named: "ic_newseting")!
        let settingCell = UserTableViewList(name: "设置", photo: settingImage, nextViewController: UserSettingTableViewController(), cellBadgeValue: 3)!
        
        systemSettings += [settingCell]
        tableView.reloadData()

    }
    
    func handleNavigation() {
        title = "我的"
    }
    override func viewDidLoad() {
        
        //print(NSFileManager().URLsForDirectory(.DocumentDirectory, inDomains: .UserDomainMask).first!)
        let desktopURL = NSURL(fileURLWithPath: "/Users/aa/Library/Test")
        do {
            let tmpURL = try NSFileManager.defaultManager().URLForDirectory(.ItemReplacementDirectory, inDomain: .UserDomainMask, appropriateForURL: desktopURL, create: true)
            print(tmpURL)
        } catch {
            print("EEE")
        }

        
        super.viewDidLoad()
        
        handleNavigation()
        
        automaticallyAdjustsScrollViewInsets = false
        
        
        //let avatarViewController = UserAvatarViewController()
        //addChildViewController(avatarViewController)
        //tableView.addSubview(avatarViewController.view)
        
        
        
        
        //tableView.layoutMargins = UIEdgeInsets(top: 9, left:9, bottom: 9, right: 9)
        
       // tableView.contentInset = UIEdgeInsets(top: 9, left:9, bottom: 9, right: 9)

        
        tableView.backgroundColor = UIColor(red: 0xfd / 255.0, green: 0xfd / 255, blue: 0xfd / 255, alpha: 1)
        tableView.separatorStyle = .None
        //tableView.cellLayoutMarginsFollowReadableWidth = false
        tableView.registerClass(UserTableViewCell.self, forCellReuseIdentifier: cellIdentifier)
        
        
        
        refreshControl = UIRefreshControl()
        
        refreshControl?.addTarget(self, action: #selector(UserTableViewController.refreshData), forControlEvents: .ValueChanged)
        refreshControl?.attributedTitle = NSAttributedString(string: "松开后自动刷新")
        tableView.addSubview(refreshControl!)
        tableView.sendSubviewToBack(refreshControl!)
        
        let bg = UIImageView(image: UIImage(named: "img_loding1"))
        bg.frame = CGRectMake(tableView.frame.width - 8, 8, 16, 16)
        tableView.backgroundView = bg
        tableView.sendSubviewToBack(bg)

        
        
        loadData()
        
    }
    
    func refreshData() {
        print("refreshData")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    // MARK: - Table view data source
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 3
    }
    //override func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
   //     return 90
   // }

    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        switch section {
        case 0:
            return 1
        case 1:
            return cells.count
        case 2:
            return 1
        default :
            return 0
        }
    }
    
    override func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        switch indexPath.section {
        case 0:
            return 100
        case 1:
            return Conf.Size.TableView.cellHeight + Conf.Size.TableView.cellMargins.top + Conf.Size.TableView.cellMargins.top
        case 2:
            return Conf.Size.TableView.cellHeight + Conf.Size.TableView.cellMargins.top + Conf.Size.TableView.cellMargins.top
        default:
            return 0
        }
    }
    override func tableView(tableView: UITableView, heightForFooterInSection section: NSInteger) -> CGFloat {
        return 10
    }
    
//    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String {
//        return "header title"
//    }
//    
//    override func tableView(tableView: UITableView, titleForFooterInSection section: Int) -> String {
//        return "footter title"
//    }
    
    
    
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        
        if (indexPath.section == 0) {
            let cell = UserHeaderLoginedTableViewCell(style: .Default, reuseIdentifier: "UserAvatarTableViewCell")
            //cell.dynamicType.username = "Aario"
            //cell.dynamicType.nickname = "Aario"
            //UserAvatarTableViewCell.username = "Aario"
            //UserAvatarTableViewCell.nickname = "Aario"
            cell.textLabel!.text = "Aario " + String(indexPath.row)
            //cell.detailTextLabel!.text = "APP ID: Aario"
            
            cell.imageView!.image = UIImage(named: "icon_accounts")!
            
            return cell
        } else if (indexPath.section == 1) {
            let cell = UserTableViewCell(style: .Default, reuseIdentifier: "UserTableViewCell")
            let cellData = cells[indexPath.row]
            cell.textLabel!.text = cellData.name
            cell.imageView!.image = cellData.photo
            return cell
        } else {
            let cell = UserTableViewCell(style: .Default, reuseIdentifier: "UserTableViewCell")
            let cellData = systemSettings[indexPath.row]
            cell.textLabel!.text = cellData.name
            cell.imageView!.image = cellData.photo
            return cell

        }
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        tableView.deselectRowAtIndexPath(indexPath, animated: true)
        
        if (indexPath.section == 2) {
            if let nextViewController = systemSettings[indexPath.row].nextViewController {
                navigationController?.pushViewController(nextViewController, animated: true)
            }
        } else {
            if let nextViewController = cells[indexPath.row].nextViewController {
                navigationController?.pushViewController(nextViewController, animated: true)
            }
            
        }
        
    }

    
    // Override to support conditional editing of the table view.
    override func tableView(tableView: UITableView, canEditRowAtIndexPath indexPath: NSIndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    
    
    // Override to support editing the table view.
    override func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath) {
        if editingStyle == .Delete {
            // Delete the row from the data source
           // meals.removeAtIndex(indexPath.row)
           // saveMeals()
            tableView.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Fade)
        } else if editingStyle == .Insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        }
    }
    
    
}
