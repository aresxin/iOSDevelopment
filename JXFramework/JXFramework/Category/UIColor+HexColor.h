//
//  UIColor+HexColor.h
//  SnapMovie
//
//  Created by CN40436 on 15/1/28.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (HexColor)

/**
 Create a instance of UIColor with the given hex string of RGB value.
 */
+ (instancetype)colorWithHex:(NSString *)hexString;

/**
 Create a instance of UIColor with the given hex string of RGB value and alpha value.
 */
+ (instancetype)colorWithHex:(NSString *)hexString alpha:(CGFloat)alpha;

@end
