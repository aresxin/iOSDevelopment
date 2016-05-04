//
//  UIView+AutoLayoutHelpers.m
//  JXFramework
//
//  Created by yangjinxin on 15/7/27.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "UIView+AutoLayoutHelpers.h"

@implementation UIView (AutoLayoutHelpers)
+ (void)leftAlignAndVerticallySpaceOutViews:(NSArray *)views
                             distance:(CGFloat)distance
{
    for (NSUInteger i = 1; i < views.count; i++) {
        UIView *firstView = views[i - 1];
        UIView *secondView = views[i];
        [firstView setTranslatesAutoresizingMaskIntoConstraints:NO];
        [secondView setTranslatesAutoresizingMaskIntoConstraints:NO];
        
        NSLayoutConstraint *c1 = [NSLayoutConstraint
                                  constraintWithItem:firstView
                                  attribute:NSLayoutAttributeBottom
                                  relatedBy:NSLayoutRelationEqual
                                  toItem:secondView
                                  attribute:NSLayoutAttributeTop
                                  multiplier:1.0f
                                  constant:distance];
        
        NSLayoutConstraint *c2 = [NSLayoutConstraint
                                  constraintWithItem:firstView
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationEqual
                                  toItem:secondView
                                  attribute:NSLayoutAttributeLeading
                                  multiplier:1.0f
                                  constant:0.0f];
        
        [firstView.superview addConstraints:@[c1, c2]];
    }
}
@end
