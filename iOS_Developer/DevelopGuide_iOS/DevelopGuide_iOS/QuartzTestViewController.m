//
//  QuartzTestViewController.m
//  QuartzTest
//
//  Created by tuyuer tuyuer on 10/23/11.
//  Copyright tuyuer 2011. All rights reserved.
//

#import "QuartzTestViewController.h"
#import "ImageBlockView.h"

@implementation QuartzTestViewController

- (void)viewDidLoad{
	//init a image
	for (int i=0; i<4; i++) {
		for (int j=0; j<6; j++) {
			ImageBlockView * ibView=[[ImageBlockView alloc] initWithiValue:i jValue:j];
			ibView.frame=CGRectMake(i*80,j*80, 80, 80);
			[self.view addSubview:ibView];
		}
	}
	
	
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
