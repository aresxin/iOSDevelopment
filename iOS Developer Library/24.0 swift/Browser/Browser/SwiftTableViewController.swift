//
//  SwiftTableViewController.swift
//  Browser
//
//  Created by yangjinxin on 15/10/13.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

import UIKit


//extension UITableViewDelegate {
//    
//    func cellHeight(tableView: UITableView) -> CGFloat {
//        let height:CGFloat = 0.0
//        
//        
//        return height
//    }
//}

//extension UIScrollViewDelegate {
//    // Convenience method to update a UIPageControl with the correct page.
//    func updatePageControl(pageControl: UIPageControl, scrollView: UIScrollView) {
//        pageControl.currentPage = lroundf(Float(scrollView.contentOffset.x / (scrollView.contentSize.width / CGFloat(pageControl.numberOfPages))));
//    }
//    
//    
//    func getScrollViewZoomView(scrollView: UIScrollView) -> UIView {
//        return self.viewForZoomingInScrollView!(scrollView)!
//    }
//}
//

//extension UIViewControllerContextTransitioning {
//    // Mock the indicated view by replacing it with its own snapshot. Useful when we don't want to render a view's subviews during animation, such as when applying transforms.
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
//    
//    // Add a background to the container view. Useful for modal presentations, such as showing a partially translucent background behind our modal content.
//    func addBackgroundView(color: UIColor) -> UIView? {
//        if let container = self.containerView() {
//            let bg = UIView(frame: container.bounds)
//            bg.backgroundColor = color
//            
//            container.addSubview(bg)
//            container.sendSubviewToBack(bg)
//            return bg
//        }
//        return nil
//    }
//}


class SwiftTableViewController: UIViewController,UITableViewDataSource,UITableViewDelegate{

    
    @IBOutlet weak var stableView: UITableView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.automaticallyAdjustsScrollViewInsets = false;
        
        
        let rowsCount:Int = self.totalRows(stableView)
        
        NSLog("%d", rowsCount)
        
        //stableView.estimatedRowHeight = 68.0
        //stableView.rowHeight = UITableViewAutomaticDimension
        stableView.tableViewAutomaticCellHeight();
        
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "didChangePreferredContentSize:", name: UIContentSizeCategoryDidChangeNotification, object: nil)
        
        // add Notification
    }
    
    
    
    func didChangePreferredContentSize(noti:NSNotification) {
        stableView.reloadData()
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    
    
    // MARK: - TableViewDelegate
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 100
    }
    
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell  {
//        let cell: UITableViewCell = tableView.dequeueReusableCellWithIdentifier(CellIdentifier, forIndexPath: indexPath) as UITableViewCell
         let cell:UITableViewCell = UITableViewCell(style: .Default, reuseIdentifier:"cellide")
        
        
        if indexPath.row == 0 {
            cell.textLabel?.text = "custom cell"
        } else if indexPath.row == 1 {
             cell.textLabel!.text = "sdssddsjlljljjjjjjjjjjjjjjjjjllllllllllllljjjjjjjjjjjjjjjjjoooooooooooooooppppppppppppppppppppppoooooooooooohhhhhhhhhhhhhhhhhhhhhhh"
        } else {
             cell.textLabel!.text = "sdssddsjlljljjjjjjjjjjjjjjjjllllllllllllljjjjjjjjjjjjjjjjjoooooooooooooooppppppppppppppppppppppoooooooooooohhhhhhhhhhhhhhhhhhhhhhhsdssddsjlljljjjjjjjjjjjjjjjjllllllllllllljjjjjjjjjjjjjjjjjoooooooooooooooppppppppppppppppppppppoooooooooooohhhhhhhhhhhhhhhhhhhhhhh"
        }
       
        cell.textLabel!.numberOfLines = 0
        
        return cell
    }
    
    
    /*old
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
    
//    let cell:UITableViewCell = tableView.dequeueReusableCellWithIdentifier("CustomCell",forIndexPath: indexPath)
//    
//    cell.textLabel?.numberOfLines = 0
//    
//    if indexPath.row == 0 {
//        cell.textLabel?.text = "custom cell"
//
//    } else {
//        cell.textLabel?.text = "custom dssd dsdsd dsdsds dsds dsdsd dsds dsdsd dsdsds dsd ds dsd  ds dsdsds sds  dsd  cell size to this long size to thie long long llong long eft space sdjl"
//
//    }
//    
//    return cell;
    
    
//    let cell: UITableViewCell = tableView.dequeueReusableCellWithIdentifier("CustomCell", forIndexPath: indexPath) as UITableViewCell
//    
    
    let cell:UITableViewCell = UITableViewCell(style: .Default, reuseIdentifier:"cellide")
    
    //cell.textLabel.text = reviews[indexPath.row] as? String
    
    if indexPath.row == 0 {
        cell.textLabel?.text = "custom cell"
        
    } else {
        cell.textLabel?.text = "custom dssd dsdsd dsdsds dsds dsdsd dsds dsdsd dsdsds dsd ds dsd  ds dsdsds sds  dsd  cell size to this long size to thie long long llong long eft space sdjl"
        
    }

    cell.textLabel!.numberOfLines = 0;
    

    return cell

    }
    */
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        // TODO: Play
        let playAudioController:PlayAudioViewController = PlayAudioViewController()
        
        self.navigationController?.pushViewController(playAudioController, animated:false)
        
    }

}
