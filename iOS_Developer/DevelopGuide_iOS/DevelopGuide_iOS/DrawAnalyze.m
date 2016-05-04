//
//  DrawAnalyze.m
//  DrawLine
//
//  Created by neusoft  on 11-7-12.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawAnalyze.h"


@implementation DrawAnalyze


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.backgroundColor = [UIColor groupTableViewBackgroundColor];
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
	CGContextRef ctx = UIGraphicsGetCurrentContext();
	
	CGContextSetRGBStrokeColor(ctx, 1.0, 1.0, 1.0, 1.0);
	CGContextSetRGBFillColor(ctx, 0.0, 1.0, 1.0, 1.0);
	CGContextSetLineWidth(ctx, 2.0);	
	for (int i = 0; i < 5 ; i++) {
		CGContextAddRect(ctx, CGRectMake(80 + i*20, 10 + i*30 , 20, 160 - i*30));
		CGContextDrawPath(ctx, kCGPathFillStroke);
		//CGContextClosePath(ctx);
	}
	CGContextClosePath(ctx);
	
	/* Drawing modes for paths. */
	/*
	enum CGPathDrawingMode {
		kCGPathFill,
		kCGPathEOFill,
		kCGPathStroke,
		kCGPathFillStroke,
		kCGPathEOFillStroke
	};
	*/
	// Drawing code.
	CGContextSetRGBFillColor(ctx, 1.0, 1.0, 1.0, 1.0);
	CGContextSetRGBStrokeColor(ctx, 1.0, 0.0, 0.0, 1.0);
	// 设定描绘的字体
	CGContextSelectFont(ctx, "Helvetica", 8.0, kCGEncodingMacRoman);
	CGContextSetTextMatrix(ctx, CGAffineTransformMakeScale(1.0, -1.0));
	// 描绘的位置与描绘的方式
	//CGContextSetTextDrawingMode(context, kCGTextFill);
	//CGContextShowTextAtPoint(context, 10.0, 160.0, @"2011",strlen(@"2011"));
	char *show[5] = {"2011","2010","2009","2008","2007"};
	for (int i = 0; i < 5 ; i++) {
		CGContextSetTextDrawingMode(ctx, kCGTextStroke);
		CGContextShowTextAtPoint(ctx, 80 + i*20, 180.0, show[i],strlen(show[i]));
		
	}
	
	//字体描绘方式
	/*
	 enum CGTextDrawingMode {
	 kCGTextFill,
	 kCGTextStroke,
	 kCGTextFillStroke,
	 kCGTextInvisible,
	 kCGTextFillClip,
	 kCGTextStrokeClip,
	 kCGTextFillStrokeClip,
	 kCGTextClip
	 };
	 */
	
	
}


- (void)dealloc {
    [super dealloc];
}


@end
