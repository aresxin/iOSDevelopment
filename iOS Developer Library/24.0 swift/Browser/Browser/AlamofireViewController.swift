//
//  AlamofireViewController.swift
//  Browser
//
//  Created by yangjinxin on 15/10/16.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

import UIKit
//import Alamofire


class AlamofireViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.view.backgroundColor = UIColor.brownColor()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    func sendGetRequest() {
       // Alamofire.request(.GET, "https://httpbin.org/get")
    }

}
