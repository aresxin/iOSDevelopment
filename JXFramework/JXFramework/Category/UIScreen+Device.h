//
//  UIScreen+Device.h
//  SnapMovie
//
//  Created by CN40436 on 15/2/6.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, UIScreenIdiom) {
    UIScreenIdiomPhone4,
    UIScreenIdiomPhone5,
    UIScreenIdiomPhone6,
    UIScreenIdiomPhone6Plus,
    UIScreenIdiomPad
};

@interface UIScreen (Device)
/**
 Indicates the screen idiom for current device.
 */
+ (UIScreenIdiom)mainScreenIdiom;
@end
