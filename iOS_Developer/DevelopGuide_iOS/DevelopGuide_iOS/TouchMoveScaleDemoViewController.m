//
//  TouchMoveScaleDemoViewController.m
//  TouchMoveScaleDemo
//
//  Created by jimney on 07/05/10.
//  Copyright 2010 OpenSource. All rights reserved.
//	Welcome to my HomePage In CocoaChina:http://www.cocoachina.com/bbs/u.php?action=topic

#import "TouchMoveScaleDemoViewController.h"
#import "TouchMoveScaleView.h"
@implementation TouchMoveScaleDemoViewController


/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad 
{
    [super viewDidLoad];
	//更改你添加的图片名
	UIImage* image = [UIImage imageNamed:@"image.jpg"];
	m_pTouchMoveScaleView = [[TouchMoveScaleView alloc] initWithFrame:[UIScreen mainScreen].bounds 
																image:image];
	[self.view addSubview:m_pTouchMoveScaleView];
}



// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
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
	[m_pTouchMoveScaleView release];
    [super dealloc];
}

@end
