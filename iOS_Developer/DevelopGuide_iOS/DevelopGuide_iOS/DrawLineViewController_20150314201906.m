//
//  DrawLineViewController.m
//  DrawLine
//
//  Created by neusoft  on 11-7-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawLineViewController.h"

@implementation DrawLineViewController


int i = 10;
/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
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
- (void)viewDidLoad {
    [super viewDidLoad];
    DrawLine *drawLine = [[DrawLine alloc] init];
    drawLine.frame = CGRectMake(0, 0, 320, 480);
    [self.view addSubview:drawLine];
    [drawLine release];
    
    /*
	lineView = [[QuatzeLine alloc] init];
	lineView.frame = CGRectMake(0, 0, 320, 400);
	[self.view addSubview:lineView];
	//[lineView release];
	*/
}

- (IBAction) setNeedPlay:(id)sender
{
	NSLog(@"111");
	i = i+5;
	lineView.mywidth = i;
	[lineView setNeedsDisplay];
	
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

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
	[lineView release];
    [super dealloc];
}

@end
