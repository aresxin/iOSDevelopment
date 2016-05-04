//
//  UIView+AutoLayout.h
//  JXFramework
//
//  Created by yangjinxin on 15/10/15.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (AutoLayout)

/*
 * set width by autolayout
 */
- (NSLayoutConstraint *)constrainWidth:(CGFloat)constant;

/*
 * set height by autolayout
 */
- (NSLayoutConstraint *)constrainHeight:(CGFloat)constant;
@end
