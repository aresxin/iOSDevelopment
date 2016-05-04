//
//  CoreGraphics.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-30.
//
//

#import "CoreGraphics.h"

@implementation CoreGraphics

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    // Drawing code
    CGContextSaveGState(ctx);
    
    // draw 1
    CGContextRestoreGState(ctx);
    
    
    CGContextSaveGState(ctx);

    // draw2
    CGContextRestoreGState(ctx);
}


@end
