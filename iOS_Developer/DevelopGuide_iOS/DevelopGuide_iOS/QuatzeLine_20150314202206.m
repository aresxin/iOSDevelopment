//
//  QuatzeLine.m
//  DrawLine
//
//  Created by neusoft  on 11-7-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "QuatzeLine.h"


@implementation QuatzeLine
@synthesize mywidth;

- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.backgroundColor = [UIColor clearColor];  
		self.mywidth = 10;
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.

- (void)drawRect:(CGRect)rect {
    // Drawing code.
	// 获得内容
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	// Drawing lines with a white stroke color
	CGContextSetRGBStrokeColor(context, 1.0, 1.0, 1.0, 1.0);
	
	// Preserve the current drawing state
	 //CGContextSaveGState(context);
	
	// Setup the horizontal line to demostrate caps
	// 添加线
	CGContextMoveToPoint(context, 40.0, 30.0);
	CGContextAddLineToPoint(context, 280.0, 30.0);
	//CGContextRestoreGState(context);
	
	
	// Preserve the current drawing state
	//CGContextSaveGState(context);
	// 添加正方形
	//CGContextSetRGBStrokeColor(context, 0.0, 1.0, 0.0, 1.0);
	//CGContextAddRect(context, CGRectMake(10.0, 30.0, 100.0, 100.0));
	//CGContextRestoreGState(context);
	
	// Preserve the current drawing state
	//CGContextSaveGState(context);
	// 添加圆
	//CGContextSetRGBStrokeColor(context, 0.0, 0.0, 1.0, 1.0);
	//CGContextAddEllipseInRect(context, CGRectMake(210.0, 30.0, 100.0, 100.0));
	//CGContextRestoreGState(context);
	
	// Set the line width & cap for the cap demo
	CGContextSetLineWidth(context, mywidth);	
	CGContextSetLineCap(context, 2);
	
	CGContextStrokePath(context);
	
	
	
    CGContextSetRGBStrokeColor(context, 0.0, 1.0, 0.0, 1.0);
	// 添加正方形路径
	CGContextAddRect(context, CGRectMake(10.0, 30.0, 100.0, 100.0));
	// 添加圆路径
	CGContextAddEllipseInRect(context, CGRectMake(210.0, 30.0, 100.0, 100.0));
	// 描绘路径
	CGContextStrokePath(context);
	
    
    
    
	CGContextSetRGBStrokeColor(context, 1.0, 1.0, 0.0, 1.0);
    CGContextSetLineWidth(context, 10);
    //UIColor *color = [UIColor redColor];
    //CGContextSetFillColorWithColor(context, color.CGColor);
	// Draw a connected sequence of line segments
//	CGPoint addLines[] =
//	{
//		CGPointMake(10.0, 90.0),
//		CGPointMake(70.0, 60.0),
//		CGPointMake(130.0, 90.0),
//		CGPointMake(190.0, 60.0),
//		CGPointMake(250.0, 90.0),
//		CGPointMake(310.0, 60.0),
//	};
//	// Bulk call to add lines to the current path.
//	// Equivalent to MoveToPoint(points[0]); for(i=1; i<count; ++i) AddLineToPoint(points[i]);
//	CGContextAddLines(context, addLines, sizeof(addLines)/sizeof(addLines[0]));
//	CGContextStrokePath(context);
	
	
	CGPoint Lines[] =
	{
		CGPointMake(10.0, 300.0),
		CGPointMake(300.0, 300.0),
		CGPointMake(300.0, 360.0),
		CGPointMake(150.0, 360.0),
		CGPointMake(140.0, 370.0),
		CGPointMake(100.0, 360.0),
		CGPointMake(10.0, 360.0),
		CGPointMake(10.0, 300.0),
	};
	// Bulk call to add lines to the current path.
	// Equivalent to MoveToPoint(points[0]); for(i=1; i<count; ++i) AddLineToPoint(points[i]);
	CGContextAddLines(context, Lines, sizeof(Lines)/sizeof(Lines[0]));
	CGContextStrokePath(context);
	//CGContextDrawPath(context, kCGPathEOFill);
	
	/*
	// Restore the previous drawing state, and save it again.
	CGContextRestoreGState(context);
	CGContextSaveGState(context);
	
	CGContextSetRGBStrokeColor(context, 1.0, 0.0, 0.0, 1.0);
	 //Setup the angled line to demonstrate joins
	CGContextMoveToPoint(context, 40.0, 190.0);
	CGContextAddLineToPoint(context, 160.0, 70.0);
	CGContextAddLineToPoint(context, 280.0, 190.0);
	
	// Set the line width & join for the join demo
	CGContextSetLineWidth(context, 10);
	CGContextSetLineJoin(context, 2);
	CGContextSetLineCap(context, 1);
	CGContextStrokePath(context);
	
	// Restore the previous drawing state.
	CGContextRestoreGState(context);
	*/
	CGRect imageRect = CGRectMake(160, 300, 80, 80);
	// 设定填充颜色
	CGContextSetRGBFillColor(context, 1.0, 0.0, 0.0, 0.5);
	// 设定填充的矩形
	CGContextFillRect(context, imageRect);
	
		
	// draw the stroke, line by line, with rounded joints
	// 设定描绘路径颜色
	CGContextSetRGBStrokeColor(context, 1.0, 0.0, 0.0, 1.0);
	//[[UIColor redColor] set];		
	
	//获得路径
	UIBezierPath* pathLines = [UIBezierPath bezierPath];
	CGPoint pointStart = CGPointMake(40, 190);
	// 设定路径起点
	[pathLines moveToPoint:pointStart];
    // 向路径中添加点
	[pathLines addLineToPoint:CGPointMake(200, 190)];
	[pathLines addLineToPoint:CGPointMake(40, 70)];
	[pathLines addLineToPoint:CGPointMake(160, 260)];
	[pathLines addLineToPoint:CGPointMake(160, 70)];
	[pathLines addLineToPoint:CGPointMake(40, 190)];
	CGFloat d = 10.0;
	[pathLines setLineDash:&d count:10 phase:0];
	// 设定线的属性
    pathLines.lineWidth = mywidth;
	pathLines.lineJoinStyle = kCGLineJoinRound;
	pathLines.lineCapStyle = kCGLineCapRound;
	
	// 路径描绘
	[pathLines stroke];
	
	
}

// Start new dictionary for each touch, with points and color
- (void) touchesBegan:(NSSet *) touches withEvent:(UIEvent *) event
{
	NSLog(@"thouchesBegan");
	startPon = [[touches anyObject] locationInView:self];
}

// Add each point to points array
- (void) touchesMoved:(NSSet *) touches withEvent:(UIEvent *) event
{
	NSLog(@"thouchesMoved");
	movePon = [[touches anyObject] locationInView:self];
	[self setNeedsDisplay];
}
/*
- (void)drawRect:(CGRect)rect
{
	// Drawing code.
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	// Drawing lines with a white stroke color
	CGContextSetRGBStrokeColor(context, 1.0, 1.0, 1.0, 1.0);
	
	CGContextMoveToPoint(context, startPon.x, startPon.y);
	CGContextAddLineToPoint(context, movePon.x, movePon.x);
	CGContextSetLineWidth(context, 10);	
	CGContextSetLineCap(context, 2);
	CGContextStrokePath(context);
	
	
	
}
*/


- (void)dealloc {
    [super dealloc];
}


@end
