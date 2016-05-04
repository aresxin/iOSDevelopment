//
//  DrawChart.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "DrawChart.h"

@implementation DrawChart

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
    /*
     饼图由两条弧构成
     第一条弧占20％
     第二条弧占80％
     */
    float startAngle = 0;

    CGContextRef ref = UIGraphicsGetCurrentContext();
    // Drawing code
    CGContextSetRGBStrokeColor(ref, 1.0, 1.0, 1.0, 1.0);
    CGContextSetRGBFillColor(ref, 1.0, 0.0, 0.0, 0.5);
    
    // 设定弧的顶点
    CGContextMoveToPoint(ref, 105 ,150);
    CGContextAddArc(ref, 105, 150, 100, startAngle, startAngle + 2*M_PI*0.2, 0);
//    CGContextAddArc(CGContextRef c, CGFloat x, CGFloat y,
//                    CGFloat radius, CGFloat startAngle, CGFloat endAngle, int clockwise)
    // x 弧顶点x坐标
    // y 弧订单y坐标
    // radius弧的半径
    // startAngle开始角度
    // endAngle结束角度
    // clockwise 1为顺时针描画，0为逆时针描画
    CGContextClosePath(ref);
    CGContextFillPath(ref);
    
    
    // 第二条弧度的start为第一条弧的end 
    startAngle = startAngle + 0 + 2*M_PI*0.2;
    CGContextSetRGBFillColor(ref, 1.0, 0.0, 1.0, 0.5);
    CGContextMoveToPoint(ref, 105 ,150);
    CGContextAddArc(ref, 105, 150, 100, startAngle, startAngle + 2*M_PI*0.8, 0);
    CGContextClosePath(ref);
    CGContextFillPath(ref);


}

@end
