//
//  LocationViewController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "LocationViewController.h"


@implementation LocationViewController

@synthesize infoTextView = infoTextView_;

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
    [infoTextView_ release];
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

#pragma make -
#pragma make action
- (IBAction) actionStartLocationButton:(id)sender
{
    CoreLocationMgr *location = [[CoreLocationMgr alloc] init];
    [location startUpdataLocation];
}

#pragma make
#pragma make CoreLocation delegate
- (void) didFinishGetLocation:(CLLocation *)location_
{
    NSLog(@"经纬度 is ----%gm, %gm",location_.coordinate.latitude,
          location_.coordinate.longitude);
    infoTextView_.text = [infoTextView_.text stringByAppendingFormat:@"%f,%f",location_.coordinate.latitude,location_.coordinate.longitude];
    NSLog(@"范围半径 is -----%gm",location_.horizontalAccuracy);
    
    NSLog(@"海拔 is -----%gm",location_.altitude);
    
    NSLog(@"海拔精确程度 is -----%gm",location_.verticalAccuracy);

}
@end
