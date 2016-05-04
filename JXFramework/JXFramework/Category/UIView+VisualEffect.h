//
//  UIView+VisualEffect.h
//  SnapMovie
//
//  Created by CN40436 on 15/2/2.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (VisualEffect)

// generate a blur effected image with the given still image.
- (UIImage *)applyBlurEffectWithStillImage:(UIImage *)stillImage;
@end
