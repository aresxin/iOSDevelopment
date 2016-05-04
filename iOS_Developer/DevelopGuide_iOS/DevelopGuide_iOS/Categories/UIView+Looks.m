//
//  UIView+Looks.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 14/11/13.
//
//

#import "UIView+Looks.h"

@implementation UIView (Looks)
-(void)fadeTail
{
    CAGradientLayer *gradient = [CAGradientLayer layer];
    gradient.frame = self.bounds;
    gradient.colors = @[
                        (id)[[UIColor whiteColor] CGColor],
                        (id)[[UIColor clearColor] CGColor]
                        ];
    gradient.startPoint = CGPointMake(0.5, 0.93);
    gradient.endPoint = CGPointMake(0.5, 1);
    
    [self.layer setMask:gradient];
}

@end
