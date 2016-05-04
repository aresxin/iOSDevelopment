//
//  DrawClipping.m
//  DrawLine
//
//  Created by neusoft  on 11-7-13.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawClipping.h"


@implementation DrawClipping


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.backgroundColor =[UIColor groupTableViewBackgroundColor]; 
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
	UIImage *drawImage = [UIImage imageNamed:@"maskImage.png"];
	CGImageRef img = drawImage.CGImage;
    // Drawing code.
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGFloat height = self.bounds.size.height;
	CGContextTranslateCTM(context, 0.0, height);
	CGContextScaleCTM(context, 1.0, -1.0);
	
	CGContextSetRGBFillColor(context, 1.0, 0.0, 0.0, 1.0);
	CGContextDrawImage(context, CGRectMake(10.0, height - 100.0, 90.0, 90.0), img);
	
	
	CGContextSaveGState(context);
	
	CGRect clips[] =
	{
		CGRectMake(110.0, height - 100.0, 35.0, 90.0),
		CGRectMake(165.0, height - 100.0, 35.0, 90.0),
	};
	// While convinient, this is just the equivalent of adding each rectangle to the current path,
	// then calling CGContextClip().
	//切割多个矩形，将举行切割的区域描画
	CGContextClipToRects(context, clips, sizeof(clips) / sizeof(clips[0]));
	CGContextDrawImage(context, CGRectMake(110.0, height - 100.0, 90.0, 90.0), img);
	
	CGContextRestoreGState(context);
	
	CGContextSaveGState(context);
	//clip 是画clip的区域，将clip以外的其他区域清除
	CGContextClipToRect(context,CGRectMake(120, height - 300, 30, 90));
    CGContextDrawImage(context, CGRectMake(100.0, height - 300.0, 90.0, 90.0), img);
	CGContextRestoreGState(context);
	
	// Clip to the current path using the even-odd rule.
	CGContextFillRect(context, CGRectMake(210.0, height - 190.0, 90.0, 90.0));
	CGContextEOClip(context);
}


- (void)dealloc {
    [super dealloc];
}


@end
