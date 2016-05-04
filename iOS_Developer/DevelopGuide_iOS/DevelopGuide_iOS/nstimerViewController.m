//
//  nstimerViewController.m
//  nstimer
//
//  Created by scottlin on 09-7-8.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "nstimerViewController.h"
#import "nstimer.h"

@implementation nstimerViewController

@synthesize label,timer;

/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
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
	
	timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(timerupdata) userInfo:nil repeats:YES]; 
}

-(void)timerupdata
{
	static NSUInteger w_Dat = 0;
	w_Dat ++;
	label.text = [[NSNumber numberWithInt:w_Dat]stringValue];
}

-(IBAction)timerpause
{
	static NSUInteger w_Flag = 0;
	w_Flag++;
	if(w_Flag % 2)
	{
		[timer pause];
	}
	else
	{
		[timer resume];
	}
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
	[timer invalidate];
	[label release];
    [super dealloc];
}

@end
