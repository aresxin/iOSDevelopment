//
//  ColoredTextLayerDelegate.m
//  DevelopGuide_iOS
//
//  Created by clay on 12-11-30.
//
//

#import "ColoredTextLayerDelegate.h"
#import "ColoredTextLayer.h"

@implementation ColoredTextLayerDelegate
/*!
 *  @override
 */
- (id)init
{
    self = [super init];
    if (self) {
        _cursor = CGPointMake(0, 0);
    }
    return self;
}

/*!
 *  @override
 */
- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx
{
    UIGraphicsPushContext(ctx);
    if ([layer isKindOfClass:[ColoredTextLayer class]]) {
        ColoredTextLayer * coloredLayer = (ColoredTextLayer *)layer;
        for (int i = 0; i < coloredLayer.textNSArray.count; i++) {
            NSString * string = [coloredLayer.textNSArray objectAtIndex:i];
            UIColor * color = [coloredLayer.colorNSArray objectAtIndex:i];
            CGSize size = [string sizeWithFont:coloredLayer.font];
            NSInteger restWidth = coloredLayer.frame.size.width - _cursor.x;
            NSInteger restHeight = coloredLayer.frame.size.height - _cursor.y;
            
            [color setFill];
            if (size.width <= restWidth && size.height < restHeight) {      //can draw in current line
                CGSize stringSize = [string drawAtPoint:_cursor withFont:coloredLayer.font];
                _cursor.x = _cursor.x + stringSize.width + coloredLayer.wordSpace;
            } else if (size.width > restWidth && size.height * 2 < restHeight) {    //can draw in next line
                _cursor.x = 0;
                _cursor.y = _cursor.y + size.height + coloredLayer.lineSpace;
                CGSize stringSize = [string drawAtPoint:_cursor withFont:coloredLayer.font];
                _cursor.x = _cursor.x + stringSize.width + coloredLayer.wordSpace;
            } else {
                return;
            }
        }
    }
    UIGraphicsPopContext();
}
@end
