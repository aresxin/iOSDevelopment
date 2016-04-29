
//
//  ViewController.swift
//  Browser
//
//  Created by yangjinxin on 15/10/12.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

import UIKit

protocol SampleProtocol
{
    func didTapGoButton()
}


class ViewController: UIViewController ,UITextFieldDelegate, UIWebViewDelegate{
    
    @IBOutlet weak var goButton: UIButton!
    @IBOutlet weak var urlTextField: UITextField!
    @IBOutlet weak var urlWebView: UIWebView!
    
    @IBOutlet weak var preButton: UIButton!

    @IBOutlet weak var nextButton: UIButton!
    
    @IBOutlet weak var searchButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        setupUI()
        
        loadWebViewURL("www.apple.com")
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func setupUI() {
        self.title = "Browser"
        
        // previous 
        //let bPre = UIBarButtonItem(barButtonSystemItem: .Rewind, target: self, action:"goBack")
        
        // space
        //let bSpace = UIBarButtonItem(barButtonSystemItem: .FlexibleSpace, target: self, action: nil)
        
        // next
        //let bNext = UIBarButtonItem(barButtonSystemItem: .FastForward, target: self, action:"goForward")
        
        // search
        //let bSearch = UIBarButtonItem(barButtonSystemItem: .Search, target: self, action:"goSearch")

        //self.toolbarItems = [bSpace, bPre,bSpace,bNext,bSpace];
        
//        let toolItems = NSMutableArray()
//        toolItems.addObject(bPre)
//        toolItems.addObject(bSpace)
//        toolItems.addObject(bNext)
//        toolItems.addObject(bSearch)
        
        //self.toolbarItems = toolItems as? NSArray
        
        //self.navigationController?.toolbar.items = toolItems
        //var items = [AnyObject]()
        
        self.urlTextField?.delegate = self
        self.urlWebView?.delegate = self;
        
        setupToolBarStatue()
        
    }
    
    
    @IBAction func goButtonClicked(sender: UIButton) {
        
        
        
//        let tableS : SwiftTableViewController = SwiftTableViewController();
        let sbd = UIStoryboard(name: "Main", bundle: nil)
        let tableSw  = sbd.instantiateViewControllerWithIdentifier("TableS")
        self.navigationController?.pushViewController(tableSw, animated: false)
        
        return;
        
//        urlTextField?.resignFirstResponder()
//        
//        if(urlTextField!.text?.lengthOfBytesUsingEncoding(NSUTF8StringEncoding) == 0) {
//            return
//        }
//
//        loadWebViewURL((self.urlTextField?.text)!)
    }
    
    
    @IBAction func goBackClicked(sender: UIButton) {
        urlWebView?.goBack()
    }
    
    
    @IBAction func goForwardClicked(sender: UIButton) {
        urlWebView?.goForward()
    }
    
    func goBack() {
        urlWebView?.goBack()
    }
    
    func goForward() {
        urlWebView?.goForward()
    }
    
    
    func goSearch() {
        
    }
    
    func setupToolBarStatue() {
        
        if urlWebView?.canGoForward == false {
            nextButton?.enabled = false
        } else {
            nextButton?.enabled = true
        }
        
        if urlWebView?.canGoBack == false {
            preButton?.enabled = false
        } else {
            preButton?.enabled = true
        }
        
        /*old
        if((urlWebView?.canGoForward) == false) {
            NSLog("false")
            nextButton?.enabled = false
        } else {
            NSLog("true")
            nextButton?.enabled = true
        }
        
        if((urlWebView?.canGoBack) == false) {
            NSLog("false")
            preButton?.enabled = false
        } else {
            NSLog("true")
            preButton?.enabled = true
        }
        */
    }
    
    func loadWebViewURL(urlString: NSString) {
        //
        let httpURL = NSString(format:"http://%@", urlString)
        let httpUTF8URL = httpURL.stringByAddingPercentEscapesUsingEncoding(NSUTF8StringEncoding)
        let url = NSURL (string: httpUTF8URL!)
        let requestObj = NSURLRequest(URL: url!)
        urlWebView!.loadRequest(requestObj)
    }
    
    //类方法, 通过 class func 关键词声明
//    class func blackColor() -> UIColor {
//        return UIColor.redColor()
//    }
    
    
    // UITextFiedl Delegate
    func textFieldShouldReturn(textField: UITextField) -> Bool {   //delegate method
        textField.resignFirstResponder()
        
        if(textField.text?.lengthOfBytesUsingEncoding(NSUTF8StringEncoding) == 0) {
            return true
        }
        
        loadWebViewURL(textField.text!)
        return true
    }
    
    // UIWebView Delegate
    func webViewDidFinishLoad(webView: UIWebView) {
        setupToolBarStatue()
    }
    
    func webView(webView: UIWebView, didFailLoadWithError error: NSError?) {
        //loadWebViewURL("www.apple.com")
    }

}

