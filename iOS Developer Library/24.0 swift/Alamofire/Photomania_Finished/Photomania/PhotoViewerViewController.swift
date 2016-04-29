//
//  PhotoViewerViewController.swift
//  Photomania
//
//  Created by Essan Parto on 2014-08-24.
//  Copyright (c) 2014 Essan Parto. All rights reserved.
//

import UIKit
import QuartzCore
import Alamofire

class PhotoViewerViewController: UIViewController, UIScrollViewDelegate, UIPopoverPresentationControllerDelegate, UIActionSheetDelegate {
  var photoID: Int = 0 // Is set by the collection view while performing a segue to this controller.
  
  let scrollView = UIScrollView()
  let imageView = UIImageView()
  let spinner = UIActivityIndicatorView(activityIndicatorStyle: .WhiteLarge)
  
  var photoInfo: PhotoInfo?
  
  // MARK: Life-Cycle
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    navigationController?.setNavigationBarHidden(false, animated: true)

    setupView()
    
    loadPhoto()
  }
  
  func setupView() {
    // Visual feedback to the user, so they know we're busy loading an image
    spinner.center = CGPoint(x: view.center.x, y: view.center.y - view.bounds.origin.y / 2.0)
    spinner.hidesWhenStopped = true
    spinner.startAnimating()
    view.addSubview(spinner)
    
    // A scroll view is used to allow zooming
    scrollView.frame = view.bounds
    scrollView.delegate = self
    scrollView.minimumZoomScale = 1.0
    scrollView.maximumZoomScale = 3.0
    scrollView.zoomScale = 1.0
    view.addSubview(scrollView)
    
    imageView.contentMode = .ScaleAspectFill
    scrollView.addSubview(imageView)
    
    let doubleTapRecognizer = UITapGestureRecognizer(target: self, action: "handleDoubleTap:")
    doubleTapRecognizer.numberOfTapsRequired = 2
    doubleTapRecognizer.numberOfTouchesRequired = 1
    scrollView.addGestureRecognizer(doubleTapRecognizer)
  }
  
  func loadPhoto() {
    Alamofire.request(Five100px.Router.PhotoInfo(self.photoID, .Large)).validate().responseObject() {
      (_, _, photoInfo: PhotoInfo?, error) in
      
      if error == nil {
        // Store it for Details Controller
        self.photoInfo = photoInfo
        
        dispatch_async(dispatch_get_main_queue()) {
          self.addButtomBar()
          self.title = photoInfo!.name
        }
        
        Alamofire.request(.GET, photoInfo!.url).validate().responseImage() {
          (_, _, image, error) in
          
          if error == nil && image != nil {
            self.imageView.image = image
            self.imageView.frame = self.centerFrameFromImage(image)
            
            self.spinner.stopAnimating()
            
            self.centerScrollViewContents()
          }
        }
      } else {
        println("Could not get photo info: \(error!)")
      }
    }
  }
  
  override func viewWillAppear(animated: Bool) {
    super.viewWillAppear(animated)
    
    // If the network is fast, the photo may be loaded before the view appears, but we still want an animation
    if photoInfo != nil {
      navigationController?.setToolbarHidden(false, animated: true)
    }
  }
  
  override func viewWillDisappear(animated: Bool) {
    super.viewWillDisappear(animated)
    navigationController?.setToolbarHidden(true, animated: true)
  }
  
  // MARK: Bottom Bar
  
  func addButtomBar() {
    var items = [UIBarButtonItem]()
    
    let flexibleSpace = UIBarButtonItem(barButtonSystemItem: .FlexibleSpace, target: nil, action: nil)
    
    items.append(barButtonItemWithImageNamed("hamburger", title: nil, action: "showDetails"))
    
    if photoInfo?.commentsCount > 0 {
      items.append(barButtonItemWithImageNamed("bubble", title: "\(photoInfo?.commentsCount ?? 0)", action: "showComments"))
    }
    
    items.append(flexibleSpace)
    items.append(UIBarButtonItem(barButtonSystemItem: UIBarButtonSystemItem.Action, target: self, action: "showActions"))
    items.append(flexibleSpace)
    
    items.append(barButtonItemWithImageNamed("like", title: "\(photoInfo?.votesCount ?? 0)"))
    items.append(barButtonItemWithImageNamed("heart", title: "\(photoInfo?.favoritesCount ?? 0)"))
    
    self.setToolbarItems(items, animated: true)
    navigationController?.setToolbarHidden(false, animated: true)
  }
  
  func showDetails() {
    let photoDetailsViewController = storyboard?.instantiateViewControllerWithIdentifier("PhotoDetails") as? PhotoDetailsViewController
    photoDetailsViewController?.modalPresentationStyle = .OverCurrentContext
    photoDetailsViewController?.modalTransitionStyle = .CoverVertical
    photoDetailsViewController?.photoInfo = photoInfo
    
    presentViewController(photoDetailsViewController!, animated: true, completion: nil)
  }
  
  func showComments() {
    let photoCommentsViewController = storyboard?.instantiateViewControllerWithIdentifier("PhotoComments") as? PhotoCommentsViewController
    photoCommentsViewController?.modalPresentationStyle = .Popover
    photoCommentsViewController?.modalTransitionStyle = .CoverVertical
    photoCommentsViewController?.photoID = photoID
    photoCommentsViewController?.popoverPresentationController?.delegate = self
    presentViewController(photoCommentsViewController!, animated: true, completion: nil)
  }
  
  // Needed for the Comments Popover
  func adaptivePresentationStyleForPresentationController(controller: UIPresentationController!) -> UIModalPresentationStyle {
    return UIModalPresentationStyle.OverCurrentContext
  }
  
  // Needed for the Comments Popover
  func presentationController(controller: UIPresentationController!, viewControllerForAdaptivePresentationStyle style: UIModalPresentationStyle) -> UIViewController! {
    let navController = UINavigationController(rootViewController: controller.presentedViewController)
    
    return navController
  }
  
  func barButtonItemWithImageNamed(imageName: String?, title: String?, action: Selector? = nil) -> UIBarButtonItem {
    let button = UIButton.buttonWithType(.Custom) as UIButton
    
    if imageName != nil {
      button.setImage(UIImage(named: imageName!)!.imageWithRenderingMode(.AlwaysTemplate), forState: .Normal)
    }
    
    if title != nil {
      button.setTitle(title, forState: .Normal)
      button.titleEdgeInsets = UIEdgeInsets(top: 0.0, left: 10.0, bottom: 0.0, right: 0.0)
      
      let font = UIFont.preferredFontForTextStyle(UIFontTextStyleFootnote)
      button.titleLabel?.font = font
    }
    
    let size = button.sizeThatFits(CGSize(width: 90.0, height: 30.0))
    button.frame.size = CGSize(width: min(size.width + 10.0, 60), height: size.height)
    
    if action != nil {
      button.addTarget(self, action: action!, forControlEvents: .TouchUpInside)
    }
    
    let barButton = UIBarButtonItem(customView: button)
    
    return barButton
  }
  
  // MARK: Download Photo
  
  func downloadPhoto() {
    // We already have the photoInfo but we prefer to request a new one with XLarge photo size URL
    Alamofire.request(Five100px.Router.PhotoInfo(photoInfo!.id, .XLarge)).validate().responseObject() {
      (_, _, photoInfo: PhotoInfo?, error) in
      
      if error == nil && photoInfo != nil {
        let imageURL = photoInfo!.url
        
        let destination: (NSURL, NSHTTPURLResponse) -> (NSURL) = {
          (temporaryURL, response) in
          
          if let directoryURL = NSFileManager.defaultManager().URLsForDirectory(.DocumentDirectory, inDomains: .UserDomainMask)[0] as? NSURL {
            return directoryURL.URLByAppendingPathComponent("\(self.photoInfo!.id).\(response.suggestedFilename)")
          }
          
          return temporaryURL
        }
        
        let progressIndicatorView = UIProgressView(frame: CGRect(x: 0.0, y: 80.0, width: self.view.bounds.width, height: 10.0))
        progressIndicatorView.tintColor = UIColor.blueColor()
        self.view.addSubview(progressIndicatorView)
        
        Alamofire.download(.GET, imageURL, destination).progress {
          (_, totalBytesRead, totalBytesExpectedToRead) in
          
          dispatch_async(dispatch_get_main_queue()) {
            progressIndicatorView.setProgress(Float(totalBytesRead) / Float(totalBytesExpectedToRead), animated: true)
            
            if totalBytesRead == totalBytesExpectedToRead {
              progressIndicatorView.removeFromSuperview()
            }
          }
        }
        
      }
    }
  }
  
  func showActions() {
    let actionSheet = UIActionSheet(title: nil, delegate: self, cancelButtonTitle: "Cancel", destructiveButtonTitle: nil, otherButtonTitles: "Download Photo")
    actionSheet.showFromToolbar(navigationController?.toolbar)
  }
  
  func actionSheet(actionSheet: UIActionSheet!, clickedButtonAtIndex buttonIndex: Int) {
    if buttonIndex == 1 {
      downloadPhoto()
    }
  }

  // MARK: Gesture Recognizers
  
  func handleDoubleTap(recognizer: UITapGestureRecognizer!) {
    let pointInView = recognizer.locationInView(self.imageView)
    self.zoomInZoomOut(pointInView)
  }
  
  // MARK: ScrollView
  
  func centerFrameFromImage(image: UIImage?) -> CGRect {
    if image == nil {
      return CGRectZero
    }
    
    let scaleFactor = scrollView.frame.size.width / image!.size.width
    let newHeight = image!.size.height * scaleFactor
    
    var newImageSize = CGSize(width: scrollView.frame.size.width, height: newHeight)
    
    newImageSize.height = min(scrollView.frame.size.height, newImageSize.height)
    
    let centerFrame = CGRect(x: 0.0, y: scrollView.frame.size.height/2 - newImageSize.height/2, width: newImageSize.width, height: newImageSize.height)
    
    return centerFrame
  }
  
  func scrollViewDidZoom(scrollView: UIScrollView!) {
    self.centerScrollViewContents()
  }
  
  func centerScrollViewContents() {
    let boundsSize = scrollView.frame
    var contentsFrame = self.imageView.frame
    
    if contentsFrame.size.width < boundsSize.width {
      contentsFrame.origin.x = (boundsSize.width - contentsFrame.size.width) / 2.0
    } else {
      contentsFrame.origin.x = 0.0
    }
    
    if contentsFrame.size.height < boundsSize.height {
      contentsFrame.origin.y = (boundsSize.height - scrollView.scrollIndicatorInsets.top - scrollView.scrollIndicatorInsets.bottom - contentsFrame.size.height) / 2.0
    } else {
      contentsFrame.origin.y = 0.0
    }
    
    self.imageView.frame = contentsFrame
  }
  
  func viewForZoomingInScrollView(scrollView: UIScrollView!) -> UIView! {
    return self.imageView
  }
  
  func zoomInZoomOut(point: CGPoint!) {
    let newZoomScale = self.scrollView.zoomScale > (self.scrollView.maximumZoomScale/2) ? self.scrollView.minimumZoomScale : self.scrollView.maximumZoomScale
    
    let scrollViewSize = self.scrollView.bounds.size
    
    let width = scrollViewSize.width / newZoomScale
    let height = scrollViewSize.height / newZoomScale
    let x = point.x - (width / 2.0)
    let y = point.y - (height / 2.0)
    
    let rectToZoom = CGRect(x: x, y: y, width: width, height: height)
    
    self.scrollView.zoomToRect(rectToZoom, animated: true)
  }
}
