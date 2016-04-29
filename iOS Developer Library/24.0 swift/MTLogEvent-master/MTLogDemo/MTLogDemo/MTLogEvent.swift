//
//  MTLogEvent.swift
//  MTLogDemo
//
//  Created by Martin on 1/9/16.
//  Copyright © 2016 MT. All rights reserved.
//

import UIKit

protocol MTLog {
    var category: String {get}
    func logEvent(action: String, label: String?, value: NSNumber?)
    func debugPrint(message: String, filename: String , line: Int , funct: String)
    func logScreen(name: String)
}

extension MTLog {
    func debugPrint(message: String, filename: String = __FILE__, line: Int = __LINE__, funct: String = __FUNCTION__) {
        print("**************************\r   \((filename as NSString).lastPathComponent):\(line) \(funct):\r   \(message)")
    }
    func logScreen(name: String) {
        
        /*
        Google analytics code
        var tracker = GAI.sharedInstance().defaultTracker
        tracker.set(kGAIScreenName, value: name)
        
        var builder = GAIDictionaryBuilder.createScreenView()
        tracker.send(builder.build() as [NSObject : AnyObject])
        */
        print(self)
    }
    func logEvent(action: String, label: String? = nil, value: NSNumber? = nil ) {
        /*
        Google analytics code
        
        let tracker = GAI.sharedInstance().defaultTracker
        let builder = GAIDictionaryBuilder.createEventWithCategory(category, action: action, label: Label, value: Value)
        tracker.send(builder.build() as [NSObject : AnyObject])
        */
    }

}

extension MTLog where Self: UIViewController {
    func errorHandle(error: String) {

        let alertController = UIAlertController(title: nil, message: error, preferredStyle: .Alert)
        let cancelAction = UIAlertAction(title: "OK", style: .Cancel, handler: nil)
        alertController.addAction(cancelAction)

        self.presentViewController(alertController, animated: true, completion: nil)
    }
}
