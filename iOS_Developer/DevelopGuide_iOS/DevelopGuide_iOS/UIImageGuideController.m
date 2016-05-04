//
//  UIImageGuideController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-12.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "UIImageGuideController.h"
#import "UIImageCategory.h"
#import "DrawImageView.h"
#import "SEImage.h"
#import <QuartzCore/QuartzCore.h>

@implementation UIImageGuideController

//@synthesize tableView_;
//@synthesize imageView_;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
//    [tableView_ release];
//    [imageView_ release];
//    [functionList release];
    [drawImgView release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
        
    UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
    drawImgView = [[DrawImageView alloc] initWithFrame:CGRectMake(0, 0, 320, 480)];
    drawImgView.drawImg = img;
    [self.view addSubview:drawImgView];
    
    // 3.0 init toolbar
    [self initToolBar];
   
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void) initToolBar
{
    UIBarButtonItem  *buttonItem = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemEdit target:self action:@selector(actionButton)] autorelease];
    NSMutableArray *items = [[NSMutableArray alloc] init];
    [items addObject:buttonItem];
    self.toolbarItems = items;
    [items release];
}

#pragma make
#pragma make action button
- (void) actionButton
{
    UIActionSheet *actionSheet_ = [[UIActionSheet alloc] initWithTitle:@"UIImage Guide" 
                                                             delegate:self 
                                                    cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:@"还原图片", 
                                                                     @"改变图片的尺寸",
                                                                   @"用颜色将图片遮罩",
                                                                   @"用图片将图片遮罩",
                                                            @"根据颜色和size生产image",
                                                               @"根据rect矩形截图图片",
                                                            @"缩放image到targetSize",
                                                            @"imageByScalingToSize",
                                                            @"imageRotatedByRadians",
                                                             @"imageRotatedByDegrees",
                                                                        @"给图片画倒影",
                                                                        @"切割图片效果",
                                                                                nil];
    [actionSheet_ showInView:self.view];
    [actionSheet_ release];
}

#pragma make
#pragma make actionSheet
- (void) actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) 
    {
         UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
         drawImgView.drawImg = img;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 1) 
    {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img transformWidth:320 height:240];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
     
    if (buttonIndex == 2) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [UIImage colorizeImage:img withColor:[UIColor yellowColor]];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 3) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *markImg = [UIImage imageNamed:@"maskImage.png"];
        UIImage  *newImg = [UIImage maskImage:img withImage:markImg];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 4) {
        UIImage  *newImg = [UIImage imageWithColor:[UIColor greenColor] 
                                           andSize:CGSizeMake(320, 480)];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 5) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img imageAtRect:CGRectMake(50, 50, 200, 200)];  
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 6) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img imageByScalingProportionallyToMinimumSize:CGSizeMake(320, 240)];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 7) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img imageByScalingProportionallyToSize:CGSizeMake(320, 240)];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 8) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img imageRotatedByRadians:90];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 9) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img imageRotatedByDegrees:90];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 10) {
        UIImage  *img = [UIImage imageNamed:@"apple_big.png"];
        UIImage  *newImg = [img addImageReflection:5];
        drawImgView.drawImg = newImg;
        [drawImgView setNeedsDisplay];
    }
    
    if (buttonIndex == 11) {
        
        drawImgView.drawImg = nil;
        [drawImgView setNeedsDisplay];
        
        NSDictionary*dict=[SEImage SeparateImage:[UIImage imageNamed:@"apple_big.png"] ByX:4 andY:4 cacheQuality:.8];
        CABasicAnimation*rotation=[CABasicAnimation animationWithKeyPath:@"transform.rotation.x"];
        rotation.duration=4.0;
        rotation.fromValue=[NSNumber numberWithFloat:M_PI/2.0];
        rotation.toValue=[NSNumber numberWithFloat:0];
        rotation.timingFunction=[CAMediaTimingFunction functionWithName: kCAMediaTimingFunctionEaseIn];
        rotation.autoreverses=YES;
        rotation.repeatCount=9;
        NSArray*keys=[dict allKeys];
        for (int count=0; count<15; count++) 
        {
            NSString*key=[keys objectAtIndex:count];
            UIImageView*imageView=[dict objectForKey:key];
            [imageView.layer addAnimation:rotation forKey:@"rotation"];
            [self.view addSubview:imageView];
            [imageView release];
        }

    }
}

@end
