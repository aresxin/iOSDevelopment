//
//  TouchFrameViewController.m
//  TouchFrame
//
//  Created by 廖 海龙 on 12-2-17.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "TouchFrameViewController.h"
#import <QuartzCore/QuartzCore.h>
@implementation TouchFrameViewController

-(void)addNewRoom{
	touchTest = [[TouchImage alloc] initWithColor:[UIColor clearColor]];
	touchTest.frame = CGRectMake(300, 200, 200, 200);
	[bgView addSubview:touchTest];
	[touchTest addTouchButton];
	[touchTest release];
}

-(void)removeAllRoom{
	for(UIView *a in [bgView subviews]){
		[a removeFromSuperview];
		
//		if ([a isKindOfClass:[TouchImage class]]) {
//			UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//			[button setTitle:@"X" forState:UIControlStateNormal];
//			[button addTarget:self action:@selector(removeOne:) forControlEvents:UIControlEventTouchUpInside];
//			[button setFrame:CGRectMake(0, 0, 40, 40)];
//			[button setCenter:CGPointMake(a.center.x, a.center.y)];
//			[a addSubview:button];
//		}
	}
}

-(void)removeOne:(UIButton *)bt{
	for(UIView *a in [bt.superview subviews]){
		[a removeFromSuperview];
	}
	[bt.superview removeFromSuperview];
}

-(void)showOrHiddenAllPoint:(UIButton *)button{
	if ([[button titleForState:UIControlStateNormal] isEqualToString:@"编辑"]) {
		for(UIView *bt in [bgView subviews]){
			if ([bt isKindOfClass:[UIImageView class]]) {
				[bt setHidden:NO];
			}
		}
		[button setTitle:@"完成" forState:UIControlStateNormal];
	}else {
		for(UIView *bt in [bgView subviews]){
			if ([bt isKindOfClass:[UIImageView class]]) {
				[bt setHidden:YES];
			}
		}
		[button setTitle:@"编辑" forState:UIControlStateNormal];
	}
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 50, 320, 40)];
    label.text = @"Demo下载地址\nhttp://www.cocoachina.com/bbs/read.php?tid=95340";
    //[label sizeToFit];
    label.font = [UIFont systemFontOfSize:13];
    label.numberOfLines = 2;
    [self.view addSubview:label];
    [label release];
    
	bgView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 480)];
	[self.view addSubview:bgView];
	[bgView release];
	
	touchTest = [[TouchImage alloc] initWithColor:[UIColor clearColor]];
	touchTest.frame = CGRectMake(10, 100, 80, 80);
	[bgView addSubview:touchTest];
	[touchTest addTouchButton];
	[touchTest release];
	
	touchTest = [[TouchImage alloc] initWithColor:[UIColor greenColor]];
	touchTest.frame = CGRectMake(10, 200, 80, 80);
	[bgView addSubview:touchTest];
	[touchTest addTouchButton];
	[touchTest release];
	
	touchTest = [[TouchImage alloc] initWithColor:[UIColor blueColor]];
	touchTest.frame = CGRectMake(10, 300, 80, 80);
	[bgView addSubview:touchTest];
	[touchTest addTouchButton];
	[touchTest release];
	
	
	UIImageView *bg = [[UIImageView alloc] init];
	//bg.userInteractionEnabled = YES;
	//[bg setImage:[UIImage imageNamed:@"a1.png"]];
	bg.frame = CGRectMake(0, 0, 320, 480);
	[self.view addSubview:bg];
	[bg release];
	
	UIButton *addButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[addButton setTitle:@"添加" forState:UIControlStateNormal];
	[addButton addTarget:self action:@selector(addNewRoom) forControlEvents:UIControlEventTouchUpInside];
	[addButton setFrame:CGRectMake(200, 200, 150, 40)];
	[self.view addSubview:addButton];
	
	UIButton *removeButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[removeButton setTitle:@"移除所有" forState:UIControlStateNormal];
	[removeButton addTarget:self action:@selector(removeAllRoom) forControlEvents:UIControlEventTouchUpInside];
	[removeButton setFrame:CGRectMake(200, 260, 150, 40)];
	[self.view addSubview:removeButton];
	
	UIButton *showPointButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[showPointButton setTitle:@"编辑" forState:UIControlStateNormal];
	[showPointButton addTarget:self action:@selector(showOrHiddenAllPoint:) forControlEvents:UIControlEventTouchUpInside];
	[showPointButton setFrame:CGRectMake(200, 320, 150, 40)];
	[self.view addSubview:showPointButton];
}



// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

@end
