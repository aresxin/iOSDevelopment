//
//  UIColor+HexColor.m
//  SnapMovie
//
//  Created by CN40436 on 15/1/28.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "UIColor+HexColor.h"

@implementation UIColor (HexColor)

+ (instancetype)colorWithHex:(NSString *)hexString
{
    NSString *string = hexString;
    if ([string hasPrefix:@"#"]) {
        string = [string substringFromIndex:1];
    }
    NSInteger length = string.length;
    if (length != 6 && length != 8) {
        return nil;
    }
    
    NSScanner *scanner = [NSScanner scannerWithString:string];
    unsigned hexNum;
    if (![scanner scanHexInt: &hexNum]) {
        return nil;
    }
    
    int r, g, b, a;
    
    if (length == 6) {
        r = (hexNum >> 16) & 0xFF;
        g = (hexNum >> 8) & 0xFF;
        b = (hexNum) & 0xFF;
        a = 255;
    } else {
        r = (hexNum >> 24) & 0xFF;
        g = (hexNum >> 16) & 0xFF;
        b = (hexNum >> 8) & 0xFF;
        a = (hexNum) & 0xFF;
    }
    
    return [UIColor colorWithRed:r / 255.0f
                           green:g / 255.0f
                            blue:b / 255.0f
                           alpha:a / 255.0f];
}

+ (instancetype)colorWithHex:(NSString *)hexString alpha:(CGFloat)alpha;
{
    NSString *string = hexString;
    if ([string hasPrefix:@"#"]) {
        string = [string substringFromIndex:1];
    }
    NSInteger length = string.length;
    if (length != 6 && length != 8) {
        return nil;
    }
    
    NSScanner *scanner = [NSScanner scannerWithString:string];
    unsigned hexNum;
    if (![scanner scanHexInt: &hexNum]) {
        return nil;
    }
    
    int r, g, b;
    
    if (length == 6) {
        r = (hexNum >> 16) & 0xFF;
        g = (hexNum >> 8) & 0xFF;
        b = (hexNum) & 0xFF;
    } else {
        r = (hexNum >> 24) & 0xFF;
        g = (hexNum >> 16) & 0xFF;
        b = (hexNum >> 8) & 0xFF;
    }
    
    return [UIColor colorWithRed:r / 255.0f
                           green:g / 255.0f
                            blue:b / 255.0f
                           alpha:alpha];
}
@end
