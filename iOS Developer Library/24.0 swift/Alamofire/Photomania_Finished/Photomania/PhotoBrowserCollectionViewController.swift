//
//  PhotoBrowserCollectionViewController.swift
//  Photomania
//
//  Created by Essan Parto on 2014-08-20.
//  Copyright (c) 2014 Essan Parto. All rights reserved.
//

import UIKit
import Alamofire

class PhotoBrowserCollectionViewController: UICollectionViewController, UICollectionViewDelegateFlowLayout {
  // The model
  var photos = NSMutableOrderedSet()
  
  let imageCache = NSCache()
  
  let refreshControl = UIRefreshControl()
  
  var populatingPhotos = false
  var currentPage = 1
  
  let PhotoBrowserCellIdentifier = "PhotoBrowserCell"
  let PhotoBrowserFooterViewIdentifier = "PhotoBrowserFooterView"
  
   // MARK: Life-cycle
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    setupView()
    
    populatePhotos()
  }
  
  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    
    // Empty local image cache as they can be re-downloaded
    self.imageCache.removeAllObjects()
  }
  
  // MARK: CollectionView
  
  override func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
    return photos.count
  }
  
  override func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
    let cell = collectionView.dequeueReusableCellWithReuseIdentifier(PhotoBrowserCellIdentifier, forIndexPath: indexPath) as PhotoBrowserCollectionViewCell
    
    let imageURL = (photos.objectAtIndex(indexPath.row) as PhotoInfo).url
    
    // Cancel the request if it's not for the same photo after dequeue
    if cell.request?.request.URLString != imageURL {
      cell.request?.cancel()
    }
    
    if let image = self.imageCache.objectForKey(imageURL) as? UIImage { // Use the local cache if possible
      cell.imageView.image = image
    } else { // Download from the internet
      cell.imageView.image = nil

      cell.request = Alamofire.request(.GET, imageURL).validate(contentType: ["image/*"]).responseImage() {
        (request, _, image, error) in
        if error == nil && image != nil {
          // The image is downloaded, cache it anyways even if the cell is dequeued and we're not displaying the image
          self.imageCache.setObject(image!, forKey: request.URLString)
          
          // Make sure that by the time this line is executed, the cell is supposed the display the same image with the same URL.
          if request.URLString == cell.request?.request.URLString {
            cell.imageView.image = image
          }
        } else {
          /*
          If the cell went off-screen before the image was downloaded, we cancel it and
          an NSURLErrorDomain (-999: cancelled) is returned. This is a normal behavior.
          */
        }
      }
    }
    
    return cell
  }
  
  // Used to display a spinner at the bottom when we're waiting to load more photos
  override func collectionView(collectionView: UICollectionView, viewForSupplementaryElementOfKind kind: String, atIndexPath indexPath: NSIndexPath) -> UICollectionReusableView {
    return collectionView.dequeueReusableSupplementaryViewOfKind(kind, withReuseIdentifier: PhotoBrowserFooterViewIdentifier, forIndexPath: indexPath) as UICollectionReusableView
  }
  
  override func collectionView(collectionView: UICollectionView, didSelectItemAtIndexPath indexPath: NSIndexPath) {
    performSegueWithIdentifier("ShowPhoto", sender: (self.photos.objectAtIndex(indexPath.item) as PhotoInfo).id)
  }
  
  // MARK: Helper
  
  func setupView() {
    navigationController?.setNavigationBarHidden(false, animated: true)
    
    // Using a standard UICollectionViewFlowLayout, displaying 3 cells in each row
    let layout = UICollectionViewFlowLayout()
    let itemWidth = (view.bounds.size.width - 2) / 3
    layout.itemSize = CGSize(width: itemWidth, height: itemWidth)
    layout.minimumInteritemSpacing = 1.0
    layout.minimumLineSpacing = 1.0
    layout.footerReferenceSize = CGSize(width: collectionView!.bounds.size.width, height: 100.0)
    
    collectionView!.collectionViewLayout = layout
    
    navigationItem.title = "Featured"
    
    collectionView!.registerClass(PhotoBrowserCollectionViewCell.classForCoder(), forCellWithReuseIdentifier: PhotoBrowserCellIdentifier)
    collectionView!.registerClass(PhotoBrowserCollectionViewLoadingCell.classForCoder(), forSupplementaryViewOfKind: UICollectionElementKindSectionFooter, withReuseIdentifier: PhotoBrowserFooterViewIdentifier)
    
    refreshControl.tintColor = UIColor.whiteColor()
    refreshControl.addTarget(self, action: "handleRefresh", forControlEvents: .ValueChanged)
    collectionView!.addSubview(refreshControl)
  }
  
  override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
    if segue.identifier == "ShowPhoto" {
      (segue.destinationViewController as PhotoViewerViewController).photoID = sender!.integerValue
      (segue.destinationViewController as PhotoViewerViewController).hidesBottomBarWhenPushed = true
    }
  }
  
  override func scrollViewDidScroll(scrollView: UIScrollView) {
    // Populate more photos when the scrollbar indicator is at 80%
    if scrollView.contentOffset.y + view.frame.size.height > scrollView.contentSize.height * 0.8 {
      populatePhotos()
    }
  }
  
  func populatePhotos() {
    if populatingPhotos { // Do not populate more photos if we're in the process of loading a page
      return
    }
    
    populatingPhotos = true
    
    Alamofire.request(Five100px.Router.PopularPhotos(self.currentPage)).validate().responseJSON() {
      (_, _, JSON, error) in
      
      if error == nil {
        // Processing the photos and updating the model takes a while, do not dispatch on the main queue.
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0)) {
          let photoInfos = ((JSON as NSDictionary).valueForKey("photos") as [NSDictionary]).filter({ ($0["nsfw"] as Bool) == false }).map { PhotoInfo(id: $0["id"] as Int, url: $0["image_url"] as String) }
          
          let lastItem = self.photos.count
          self.photos.addObjectsFromArray(photoInfos)
          
          // Needed for insertItemsAtIndexPaths
          let indexPaths = (lastItem..<self.photos.count).map { NSIndexPath(forItem: $0, inSection: 0) }
          
          dispatch_async(dispatch_get_main_queue()) {
            // Better than self.collectionview!.reloadData() as it only adds new items instead of reloading the entire collection view
            self.collectionView!.insertItemsAtIndexPaths(indexPaths)
          }
          
          self.currentPage++
        }
      } else {
        println("Have you set your consumer key? Error: \(error!)")
      }
      self.populatingPhotos = false
    }
  }
  
  func handleRefresh() {
    refreshControl.beginRefreshing()
    
    // Reset the model
    self.photos.removeAllObjects()
    self.currentPage = 1
    
    // Refresh the UI
    self.collectionView!.reloadData()
    
    // We have our own spinner
    refreshControl.endRefreshing()
    
    populatePhotos()
  }
}

class PhotoBrowserCollectionViewCell: UICollectionViewCell {
  // request stored for cancellation and checking the original URLString
  var request: Alamofire.Request?
  let imageView = UIImageView()
  
  required init(coder aDecoder: NSCoder) {
    super.init(coder: aDecoder)
  }
  
  override init(frame: CGRect) {
    super.init(frame: frame)
    
    backgroundColor = UIColor(white: 0.1, alpha: 1.0)
    
    imageView.frame = bounds
    addSubview(imageView)
  }
}

class PhotoBrowserCollectionViewLoadingCell: UICollectionReusableView {
  let spinner = UIActivityIndicatorView(activityIndicatorStyle: UIActivityIndicatorViewStyle.WhiteLarge)
  
  required init(coder aDecoder: NSCoder) {
    super.init(coder: aDecoder)
  }
  
  override init(frame: CGRect) {
    super.init(frame: frame)
    
    spinner.startAnimating()
    spinner.center = self.center
    addSubview(spinner)
  }
}
