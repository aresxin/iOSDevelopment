//
//  DrawImageView.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-14.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "DrawImageView.h"
#import "SEImage.h"

@implementation DrawImageView

@synthesize drawImg = drawImg_;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor scrollViewTexturedBackgroundColor];
    }
    return self;
}

- (id) initWithFrame:(CGRect)frame with:(UIImage *)image
{
    self = [super initWithFrame:frame];
    if (self) {
        self.drawImg = image;
    }
    return self;
}
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    //Drawing first 在指定的位置绘制图片
	//将图片左右翻转
	CGContextScaleCTM(ctx, 1.0, -1.0);
	//从图片的（0，－CGImageGetHeight(imgRef)）开始画，图片的原点在左上角，context的原点在左下角
	CGContextTranslateCTM(ctx, 0, -self.bounds.size.height);
    
    [SEImage drawImage:ctx Image:drawImg_.CGImage AtPoint:CGPointMake(0, 0)];
}


- (void)dealloc
{
    [drawImg_ release];
    [super dealloc];
}

@end
