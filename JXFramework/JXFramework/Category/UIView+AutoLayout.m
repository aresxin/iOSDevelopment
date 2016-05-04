//
//  UIView+AutoLayout.m
//  JXFramework
//
//  Created by yangjinxin on 15/10/15.
//  Copyright © 2015年 yangjinxin. All rights reserved.
//

#import "UIView+AutoLayout.h"

@implementation UIView (AutoLayout)
- (NSLayoutConstraint *)constrainDimension:(NSLayoutAttribute)dimension
                                  relation:(NSLayoutRelation)relation
                                  constant:(CGFloat)constant
{
    return [NSLayoutConstraint constraintWithItem:self
                                        attribute:dimension
                                        relatedBy:relation
                                           toItem:nil
                                        attribute:NSLayoutAttributeNotAnAttribute
                                       multiplier:1.0
                                         constant:constant];
}


- (NSLayoutConstraint *)constrainWidth:(CGFloat)constant
{
    return [self constrainWidth:constant
                       relation:NSLayoutRelationEqual];
}

- (NSLayoutConstraint *)constrainWidth:(CGFloat)constant
                              relation:(NSLayoutRelation)relation
{
    return [self constrainDimension:NSLayoutAttributeWidth
                           relation:relation
                           constant:constant];
}

- (NSLayoutConstraint *)constrainHeight:(CGFloat)constant
{
    return [self constrainHeight:constant
                        relation:NSLayoutRelationEqual];
}

- (NSLayoutConstraint *)constrainHeight:(CGFloat)constant
                               relation:(NSLayoutRelation)relation
{
    return [self constrainDimension:NSLayoutAttributeHeight
                           relation:relation
                           constant:constant];
}

@end
