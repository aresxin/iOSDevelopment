//
//  UIFont+Convenience.h
//  SnapMovie
//
//  Created by CN40436 on 15/2/11.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIFont (Convenience)

// Returns a instance of UIFont named HelveticaNeue-Regular and the given size.
+ (UIFont *)helveticaFontOfSize:(CGFloat)fontSize;

// Returns a instance of UIFont named HelveticaNeue-Light and the given size.
+ (UIFont *)lightHelveticaFontOfSize:(CGFloat)fontSize;

+ (UIFont *)fontWithName:(NSString *)fontName maxFontSize:(CGFloat)maxFontSize text:(NSString *)text rect:(CGRect)rect actualRect:(CGRect *)actualRect scale:(CGFloat)scale;
+ (UIFont *)fontWithName:(NSString *)fontName maxFontSize:(CGFloat)maxFontSize text:(NSString *)text drawSize:(CGSize)drawSize actualSize:(CGSize *)actualSize;
@end