//
//  DrawMaskImage.m
//  DrawLine
//
//  Created by neusoft  on 11-7-12.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawMaskImage.h"


@implementation DrawMaskImage


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
		self.backgroundColor = [UIColor whiteColor];
    }
    return self;
}

/*
//为一个图片画遮罩
+(UIImage *)maskImage:(UIImage *)baseImage withImage:(UIImage *)theMaskImage
{
	UIGraphicsBeginImageContext(baseImage.size);
	CGContextRef ctx = UIGraphicsGetCurrentContext();
	CGRect area = CGRectMake(0, 0, baseImage.size.width, baseImage.size.height);
	CGContextScaleCTM(ctx, 1, -1);
    CGContextTranslateCTM(ctx, 0, -area.size.height);
	
	CGImageRef maskRef = theMaskImage.CGImage;
	
	CGImageRef maskImage = CGImageMaskCreate(CGImageGetWidth(maskRef),
											 CGImageGetHeight(maskRef),
											 CGImageGetBitsPerComponent(maskRef),
											 CGImageGetBitsPerPixel(maskRef),
											 CGImageGetBytesPerRow(maskRef),
											 CGImageGetDataProvider(maskRef), NULL, false);
	
	CGImageRef masked = CGImageCreateWithMask([baseImage CGImage], maskImage);
	CGImageRelease(maskImage);
	CGImageRelease(maskRef);
	
	CGContextDrawImage(ctx, area, masked);
	CGImageRelease(masked);
	UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
	
	return newImage;
}

*/

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
	UIImage *baseImage = [UIImage imageNamed:@"maskImage.png"];
	UIImage *maskImage = [UIImage imageNamed:@"king.jpg"];
	
	//UIGraphicsBeginImageContext(baseImage.size);
	CGContextRef ctx = UIGraphicsGetCurrentContext();
	
	CGRect area = CGRectMake(0, 0, baseImage.size.width, baseImage.size.height);
	//反转坐标系
	CGContextScaleCTM(ctx, 1, -1);
    CGContextTranslateCTM(ctx, 0, -area.size.height);
	
	
	CGImageRef maskRef = maskImage.CGImage;
	//创建遮罩imageRef
	CGImageRef themaskImage = CGImageMaskCreate(CGImageGetWidth(maskRef),
											 CGImageGetHeight(maskRef),
											 CGImageGetBitsPerComponent(maskRef),
											 CGImageGetBitsPerPixel(maskRef),
											 CGImageGetBytesPerRow(maskRef),
											 CGImageGetDataProvider(maskRef), NULL, false);
	//获得遮罩后的图片
	CGImageRef masked = CGImageCreateWithMask([baseImage CGImage], themaskImage);
	CGImageRelease(themaskImage);
	//CGImageRelease(maskRef);
	 
	CGContextDrawImage(ctx, area, masked);
	
	CGImageRelease(masked);
	
	//UIGraphicsEndImageContext();

	
}


- (void)dealloc {
    [super dealloc];
}


@end
