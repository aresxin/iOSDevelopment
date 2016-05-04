//
//  ImageBlockView.m
//  QuartzTest
//
//  Created by tuyuer tuyuer on 10/24/11.
//  Copyright 2011 tuyuer. All rights reserved.
//

#import "ImageBlockView.h"
#import <QuartzCore/QuartzCore.h>

@implementation ImageBlockView

- (id)initWithiValue:(int)i jValue:(int)j{
	if (self=[super init]) {
		iValue=i;
		jValue=j;
		self.layer.borderWidth=1;
		self.layer.borderColor=[UIColor blueColor].CGColor;
	}
	return self;
}

- (id)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		[self setUserInteractionEnabled:YES];
    }
    return self;
}
- (void)drawRect:(CGRect)rect{
	UIImage * sliceImage=[UIImage imageNamed:@"temp.jpg"];
	
	CGContextRef currentContext=UIGraphicsGetCurrentContext();
	CGAffineTransform currentTransform=CGContextGetCTM(currentContext);
	CGAffineTransform invertTransform=CGAffineTransformInvert(currentTransform);
	CGContextConcatCTM(currentContext, invertTransform);
	CGContextTranslateCTM(currentContext, -80*iValue, -80*jValue);
	CGRect clipRect=CGRectMake(iValue*80,jValue*80,80,80);
	//CGContextTranslateCTM(currentContext, -i*80, -j*80);
	CGContextClipToRect(currentContext, clipRect);
	CGContextDrawImage(currentContext, CGRectMake(0, 0, 320, 480), sliceImage.CGImage);
}
- (void)sliceWithImage:(UIImage *)imageTemp iValue:(int)i jValue:(int)j{
	
	
}

- (void)dealloc {
    [super dealloc];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
	[[self superview] bringSubviewToFront:self];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
	UITouch * touch=[touches anyObject];
	CGPoint currentPoint=[touch locationInView:[self superview]];
	CGPoint lastPoint=[touch previousLocationInView:[self superview]];
	float moveX=currentPoint.x-lastPoint.x;
	float moveY=currentPoint.y-lastPoint.y;
	CGRect myRect=self.frame;
	CGRect newRect=CGRectMake(myRect.origin.x+moveX, myRect.origin.y+moveY, myRect.size.width, myRect.size.height);
	self.frame=newRect;
}

@end































