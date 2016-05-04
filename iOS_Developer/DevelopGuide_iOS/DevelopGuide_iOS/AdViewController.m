//
//  AdViewController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-4-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AdViewController.h"

@implementation AdViewController
@synthesize adView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
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
    
    self.adView = [[[ADBannerView alloc] initWithFrame:CGRectZero] autorelease];
    adView.backgroundColor = [UIColor yellowColor];
    adView.currentContentSizeIdentifier = ADBannerContentSizeIdentifierPortrait;
    adView.delegate = self;
    adView.frame = CGRectOffset(adView.frame, 0, self.view.frame.size.height - self.adView.frame.size.height);
    //NSLog(@"adView Frame is %@",NSStringFromCGRect(adView.frame));
    [self.view addSubview:adView];
}

- (void) viewWillAppear:(BOOL)animated
{
    self.navigationController.toolbar.hidden = YES;
}

- (void) viewWillDisappear:(BOOL)animated
{
      self.navigationController.toolbar.hidden = NO;
}

- (void) dealloc
{
    [adView release];
    [super dealloc];
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

- (void)bannerViewWillLoadAd:(ADBannerView *)banner 
{
    
}
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    
}
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    adView.frame = CGRectOffset(adView.frame, 0, self.view.frame.size.height - adView.frame.size.height);
}
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    return YES;
}

- (void)bannerViewActionDidFinish:(ADBannerView *)banner;
{
    
}
@end
