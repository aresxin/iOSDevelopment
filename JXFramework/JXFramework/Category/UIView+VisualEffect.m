//
//  UIView+VisualEffect.m
//  SnapMovie
//
//  Created by CN40436 on 15/2/2.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "UIView+VisualEffect.h"
#import "UIImage+ImageEffects.h"

@implementation UIView (VisualEffect)

- (UIImage *)applyBlurEffectWithStillImage:(UIImage *)stillImage
{
    // generate image from view
    UIGraphicsBeginImageContextWithOptions(self.bounds.size, NO, [[UIScreen mainScreen] scale]);
    CGContextRef context = UIGraphicsGetCurrentContext();
    [self.layer renderInContext:context];
    
    // draw still image over it
    if (stillImage) {
        CGRect rect = CGRectMake(0.0f, 0.0f, self.bounds.size.width, self.bounds.size.width);
        [stillImage drawInRect:rect];
    }
    
    // add blur effect
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return [image applyLightEffect];
}
@end
