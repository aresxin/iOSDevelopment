//
//  DrawLine.m
//  DevelopGuide_iOS
//
//  Created by clay on 12-12-3.
//
//

#import "DrawLine.h"

@implementation DrawLine

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
    // Drawing code
    // 获得内容
	CGContextRef context = UIGraphicsGetCurrentContext();
    
    // 0. 线的属性，颜色，宽度等
    // Drawing lines stroke color
	//CGContextSetRGBStrokeColor(context, 1.0, 1.0, 1.0, 1.0);
    CGContextSetStrokeColorWithColor(context, [UIColor yellowColor].CGColor);
    //CGContextSetFillColorWithColor(CGContextRef c, CGColorRef color)
    CGContextSetLineWidth(context, 5.0);
    //CGContextStrokePath(context);
    
    // 1. 画一条直线
    CGContextSetLineCap(context, kCGLineCapRound);
    CGContextMoveToPoint(context, 10.0, 50.0);
	CGContextAddLineToPoint(context, 300.0, 50.0);
    CGContextStrokePath(context);
    CGContextClosePath(context);
    
    
    // 2. 画一条虚线
    CGContextSaveGState(context);
    CGContextMoveToPoint(context, 10.0, 100.0);
	CGContextAddLineToPoint(context, 300.0, 100.0);
    CGFloat floats[] = {10.0 , 5.0};
    CGContextSetLineDash(context, 10.0, floats, 2);
    CGContextStrokePath(context);
    CGContextClosePath(context);
    CGContextRestoreGState(context);
    
    
    // 3. 画一个三角型
    CGContextSaveGState(context);
    //CGContextSetLineCap(context, kCGLineCapRound);
    CGContextSetLineJoin(context, kCGLineJoinRound);
    CGContextMoveToPoint(context, 10.0, 150.0);
	CGContextAddLineToPoint(context, 300.0, 150.0);
    CGContextAddLineToPoint(context, 150.0, 200.0);
    CGContextAddLineToPoint(context, 10.0, 150.0);
    CGContextStrokePath(context);
    CGContextClosePath(context);
    CGContextRestoreGState(context);
    // 4. 线的join ,cap
//    enum CGLineCap {
//        kCGLineCapButt,
//        kCGLineCapRound,
//        kCGLineCapSquare
//    };
//    typedef enum CGLineCap CGLineCap;

   
    
//    enum CGLineJoin {
//        kCGLineJoinMiter,//斜
//        kCGLineJoinRound,
//        kCGLineJoinBevel //斜角
//    };
//    typedef enum CGLineJoin CGLineJoin;
    
    
    // 5. end draw
    // 描绘路径
	//CGContextStrokePath(context);
    
}


@end
