//
//  UIView+AutoLayoutHelpers.h
//  JXFramework
//
//  Created by yangjinxin on 15/7/27.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (AutoLayoutHelpers)
+ (void)leftAlignAndVerticallySpaceOutViews:(NSArray *)views
                                   distance:(CGFloat)distance;
@end
