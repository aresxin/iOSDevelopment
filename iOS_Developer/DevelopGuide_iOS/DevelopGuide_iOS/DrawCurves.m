//
//  DrawCurves.m
//  DrawLine
//
//  Created by neusoft  on 11-7-12.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawCurves.h"


@implementation DrawCurves


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.backgroundColor = [UIColor blackColor];
    }
    return self;
}

- (void) drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx
{
	// 描绘圆
	// Drawing with a white stroke color
	// 设定Stroke
	CGContextSetRGBStrokeColor(ctx, 1.0, 1.0, 1.0, 1.0);
	// And draw with a blue fill color
	// 设定Fill
	CGContextSetRGBFillColor(ctx, 0.0, 0.0, 1.0, 1.0);
	// Draw them with a 2.0 stroke width so they are a bit more visible.
	CGContextSetLineWidth(ctx, 2.0);
	
	// Add an ellipse circumscribed in the given rect to the current path, then stroke it
	CGContextAddEllipseInRect(ctx, CGRectMake(30.0, 30.0, 60.0, 60.0));
	// 描绘路径
	CGContextStrokePath(ctx);
	
	// Stroke ellipse convenience that is equivalent to AddEllipseInRect(); StrokePath();
	// 描绘圆路径在矩形区域
	CGContextStrokeEllipseInRect(ctx, CGRectMake(30.0, 120.0, 60.0, 60.0));
	
	// Fill rect convenience equivalent to AddEllipseInRect(); FillPath();
	// 填充一个圆在居矩形区域
	CGContextFillEllipseInRect(ctx, CGRectMake(30.0, 210.0, 60.0, 60.0));
	// 关闭上一个描绘的路径
	CGContextClosePath(ctx);
	
	// 画矩形
	CGContextSetRGBStrokeColor(ctx, 1.0, 0.0, 0.0, 1.0);
	CGContextSetRGBFillColor(ctx, 0.0, 1.0, 1.0, 1.0);
	CGContextSetLineWidth(ctx, 5.0);
	// 添加一个矩形路径
	CGContextAddRect(ctx, CGRectMake(160, 30, 60, 60));
	CGContextStrokePath(ctx);
	
	CGContextStrokeRect(ctx, CGRectMake(160, 120, 60, 60));
	
	CGContextFillRect(ctx, CGRectMake(160, 210, 60, 60));
	
	CGContextAddRect(ctx, CGRectMake(160, 300, 60, 60));
	CGContextDrawPath(ctx, kCGPathFillStroke);
	/*
	kCGPathFill,
    kCGPathEOFill,
    kCGPathStroke,
    kCGPathFillStroke,
    kCGPathEOFillStroke
	*/
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
}

- (void)dealloc {
    [super dealloc];
}


@end
