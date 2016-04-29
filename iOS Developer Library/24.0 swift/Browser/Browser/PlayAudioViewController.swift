//
//  PlayAudioViewController.swift
//  Browser
//
//  Created by yangjinxin on 15/10/13.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

import UIKit

import AVFoundation





extension UIViewControllerContextTransitioning {
    // Mock the indicated view by replacing it with its own snapshot. Useful when we don't want to render a view's subviews during animation, such as when applying transforms.
//    func mockViewWithKey(key: String) -> UIView? {
//        if let view = self.viewForKey(key), container = self.containerView() {
//            let snapshot = view.snapshotViewAfterScreenUpdates(false)
//            snapshot.frame = view.frame
//            
//            container.insertSubview(snapshot, aboveSubview: view)
//            view.removeFromSuperview()
//            return snapshot
//        }
//        
//        return nil
//    }
    
    // Add a background to the container view. Useful for modal presentations, such as showing a partially translucent background behind our modal content.
    func addBackgroundView(color: UIColor) -> UIView? {
        if let container = self.containerView() {
            let bg = UIView(frame: container.bounds)
            bg.backgroundColor = color
            
            container.addSubview(bg)
            container.sendSubviewToBack(bg)
            return bg
        }
        return nil
    }
}



class PlayAudioViewController: UIViewController {

     var songPlayer: AVPlayer!

    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.view.backgroundColor = UIColor.yellowColor()
        self.playAudio()
        
        self.setupUI()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func setupUI () {
        let nextButton = UIButton(type: .Custom)
        nextButton.setTitle("Next", forState: .Normal)
        nextButton.frame = CGRectMake(10, 100, 100, 60)
        nextButton.addTarget(self, action: "actionNextButton:", forControlEvents:.TouchDown)
        self.view.addSubview(nextButton)
        
        //nextButton.setTranslatesAutoresizingMaskIntoConstraints(false)
        
        //nextButton.s
        
        // creat null array array has NSLayoutConstraint
        var constraints: [NSLayoutConstraint] = []
        
        // add object to array
        constraints += nextButton.layoutInside(self.view, insets: Inset(120, from: .Top), Inset(60, from: .Left))
        constraints += nextButton.constrainWidth(.Equal, toWidth: 44)
        constraints += nextButton.constrainHeight(.Equal, toHeight: 44)
    }
    
    
    
    func actionNextButton(sender: UIButton) {
        let sbd = UIStoryboard(name: "Main", bundle: nil)
        let collectSw  = sbd.instantiateViewControllerWithIdentifier("sCollectionView")
        self.navigationController?.pushViewController(collectSw, animated: false)
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    func playAudio() {
        

        let audioSession = AVAudioSession.sharedInstance()
        
        do {
            try audioSession.setActive(true)
        } catch let error as NSError {
            print("Error: \(error.domain)")
        }
        
        do {
           try audioSession.setCategory(AVAudioSessionCategoryPlayAndRecord)
        } catch let error as NSError {
            print("Error: \(error.domain)")
        }
    
//        audioSession.setCategory(AVAudioSessionCategoryPlayAndRecord, error: nil)
//        audioSession.setActive(true, error: nil)
        
        let songURL = NSURL(string: "http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8")
        let player = AVPlayer(URL: songURL!)
        self.songPlayer = player
        player.play()

    }
   
    func play() {
        
    }
    
    func pasue() {
        self.songPlayer.pause()
    }
    
    func pauseAudio() {
    
    }
    
    // throws error
    // throws
    func playError(errorMess : String) throws {
        if errorMess.hasPrefix("dsds") {
        } else {
            throw NSError(domain: "do", code: 100, userInfo:nil)
        }
    }
    
    
}
