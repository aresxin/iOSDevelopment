//
//  ViewController.swift
//  MTLogDemo
//
//  Created by Martin on 1/9/16.
//  Copyright © 2016 MT. All rights reserved.
//

import UIKit

class ViewController: UIViewController, MTLog {

    var category: String = "view"
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //Add screen tracking
        logScreen("root view")
        
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func testButtonAction(sender: AnyObject) {
        
        //print debug information
        debugPrint("Button trigered")
        
        //Add tracking event
        logEvent("Button", label: "test button trigered")

        //show error message
        errorHandle("error")
    }

}

