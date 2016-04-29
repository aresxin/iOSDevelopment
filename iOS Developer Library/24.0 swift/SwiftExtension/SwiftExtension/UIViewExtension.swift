//
//  UIViewExtension.swift
//  Browser
//
//  Created by yangjinxin on 15/10/15.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

import UIKit
import Foundation

// MARK: UIView
// MARK: UIView Extension AutoLayout
struct Inset {
    let value: CGFloat
    let attr: NSLayoutAttribute
    
    init(_ value: CGFloat, from attr: NSLayoutAttribute) {
        self.attr = attr;
        switch (attr) {
        case .Right, .Bottom:  self.value = -value
        default: self.value = value
        }
    }
}

extension UIView {
    func addSubviews(views: UIView...) {
        for view in views {
            self.addSubview(view)
        }
    }
    
    func layoutInside(otherView: UIView, insets: Inset...) -> [NSLayoutConstraint] {
        var constraints: [NSLayoutConstraint] = []
        for inset in insets {
            constraints.append(NSLayoutConstraint(item: self, attribute: inset.attr, relatedBy: NSLayoutRelation.Equal, toItem: otherView, attribute: inset.attr, multiplier: 1.0, constant: inset.value))
        }
        return constraints
    }
    
    func constrainDimension(dimension: NSLayoutAttribute, relation: NSLayoutRelation, constant: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: dimension, relatedBy: relation, toItem: nil, attribute: .NotAnAttribute, multiplier: 1, constant: constant)]
    }
    
    func constrainDimension(dimension: NSLayoutAttribute, relation: NSLayoutRelation, toView otherView: UIView, constant: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: dimension, relatedBy: relation, toItem: otherView, attribute: dimension, multiplier: 1, constant: constant)]
    }
    
    func constrainWidth(relation: NSLayoutRelation, toWidth constant: CGFloat) -> [NSLayoutConstraint] {
        return constrainDimension(.Width, relation: relation, constant: constant)
    }
    
    func constrainWidth(relation: NSLayoutRelation, toView otherView: UIView, plus constant: CGFloat) -> [NSLayoutConstraint] {
        return constrainDimension(.Width, relation: relation, toView: otherView, constant: constant)
    }
    
    func constrainHeight(relation: NSLayoutRelation, toHeight constant: CGFloat) -> [NSLayoutConstraint] {
        return constrainDimension(.Height, relation: relation, constant: constant)
    }
    
    func constrainHeight(relation: NSLayoutRelation, toView otherView: UIView, plus constant: CGFloat) -> [NSLayoutConstraint] {
        return constrainDimension(.Height, relation: relation, toView: otherView, constant: constant)
    }
    
    func layoutBelow(otherView: UIView, distance: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: .Top, relatedBy: .Equal, toItem: otherView, attribute: .Bottom, multiplier: 1, constant: distance)]
    }
    
    func layoutAfter(otherView: UIView, distance: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: .Left, relatedBy: .Equal, toItem: otherView, attribute: .Right, multiplier: 1, constant: distance)]
    }
    
    func alignWith(otherView: UIView, edge: NSLayoutAttribute, offsetBy constant: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: edge, relatedBy: .Equal, toItem: otherView, attribute: edge, multiplier: 1, constant: constant)]
    }
    
    func alignBaselineWith(otherView: UIView, offsetBy constant: CGFloat) -> [NSLayoutConstraint] {
        return [NSLayoutConstraint(item: self, attribute: .Baseline, relatedBy: .Equal, toItem: otherView, attribute: .Baseline, multiplier: 1, constant: constant)]
    }
}

extension Array {
    func withPriority(priority: UILayoutPriority) -> [NSLayoutConstraint] {
        var members: [NSLayoutConstraint] = []
        for member in self {
            switch member {
            case let constraint as NSLayoutConstraint:
                constraint.priority = priority
                members.append(constraint)
            default: break
            }
        }
        return members
    }
}


// MARK: UIScrollView
// MARK: UIScrollViewDelegate Extension  PageControl
extension UIScrollViewDelegate {
    // Convenience method to update a UIPageControl with the correct page.
    func updatePageControl(pageControl: UIPageControl, scrollView: UIScrollView) {
        pageControl.currentPage = lroundf(Float(scrollView.contentOffset.x / (scrollView.contentSize.width / CGFloat(pageControl.numberOfPages))));
    }
}


// MARK: UITableView
// MARK: UITableViewDataSource Extension  totalRows
extension UITableViewDataSource {
    // Returns the total # of rows in a table view.
    func totalRows(tableView: UITableView) -> Int {
        let totalSections = self.numberOfSectionsInTableView?(tableView) ?? 1
        var s = 0, t = 0
        while s < totalSections {
            t += self.tableView(tableView, numberOfRowsInSection: s)
            s += 1
        }
        return t
    }
}


// MARK: UITableViewDelegate Extension 
extension UITableView {
    // delete footer view
    func deleteFooterViewLine() {
        self.tableFooterView = UIView()
    }
    
    // when iOS8 viewDidLoad call this method
    // table view cell automatic cell height
    func tableViewAutomaticCellHeight () {
        self.estimatedRowHeight = 44.0
        self.rowHeight = UITableViewAutomaticDimension
    }
}


extension UITableView {
    
}




typealias Task = (cancel : Bool) -> ()

func delay(time:NSTimeInterval, task:()->()) ->  Task? {
    
    func dispatch_later(block:()->()) {
        dispatch_after(
            dispatch_time(
                DISPATCH_TIME_NOW,
                Int64(time * Double(NSEC_PER_SEC))),
            dispatch_get_main_queue(),
            block)
    }
    
    var closure: dispatch_block_t? = task
    var result: Task?
    
    let delayedClosure: Task = {
        cancel in
        if let internalClosure = closure {
            if (cancel == false) {
                dispatch_async(dispatch_get_main_queue(), internalClosure);
            }
        }
        closure = nil
        result = nil
    }
    
    result = delayedClosure
    
    dispatch_later {
        if let delayedClosure = result {
            delayedClosure(cancel: false)
        }
    }
    
    return result;
}

func cancel(task:Task?) {
    task?(cancel: true)
}

