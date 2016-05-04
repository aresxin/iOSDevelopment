//
//  CAImageLayerDelegate.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-23.
//
//

#import "CAImageLayerDelegate.h"
#import "CAImageLayer.h"
@implementation CAImageLayerDelegate



- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx
{
    
     UIGraphicsPushContext(ctx);
    
    NSLog(@"sel is call is %@",NSStringFromSelector(_cmd));
    if ([layer isKindOfClass:[CAImageLayer class]])
    {
        CAImageLayer * coloredLayer = (CAImageLayer *)layer;
        
        [coloredLayer.image drawInRect:layer.frame];
        NSString *string = @"sdsdsdsd";
        [string drawAtPoint:CGPointMake(0, 0) withFont:[UIFont systemFontOfSize:15]];
    }
    UIGraphicsPopContext();
}

@end
