
import UIKit

class ConversationsViewController: UITableViewController {

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {

        var initialCount = 0
        let pageSize = 50

        var dataSource: FakeDataSource!
        if segue.identifier == "0 messages" {
            initialCount = 0
        } else if segue.identifier == "2 messages" {
            initialCount = 2
        } else if segue.identifier == "10000 messages" {
            initialCount = 10000
        } else if segue.identifier == "overview" {
            dataSource = FakeDataSource(messages: TutorialMessageFactory.createMessages().map { $0 }, pageSize: pageSize)
        } else {
            assert(false, "segue not handled!")
        }

        let chatController = segue.destinationViewController as! DemoChatViewController
        if dataSource == nil {
            dataSource = FakeDataSource(count: initialCount, pageSize: pageSize)
        }
        chatController.dataSource = dataSource
        chatController.messageSender = dataSource.messageSender
    }
}
