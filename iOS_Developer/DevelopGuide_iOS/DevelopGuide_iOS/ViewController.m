//
//  ViewController.m
//  TestBlock
//
//  Created by liu AISIDE on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "TapView.h"
static NSInteger tagtag;
@implementation ViewController

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
   
    /*Block作为方法参数*/
    TapView *tapView=[[TapView alloc] initWithFrame:CGRectMake(35, 100, 250, 250)  
                                     EditBeginBlcok:^(int tag) {
                                         NSLog(@"点击按钮:%d",tag);
                                         tagtag = tag;
                                         [ViewController gototo:tag];
                                     }];
    
    //NSLog(@"tag tag is %@",tagtag);
    [tapView setBackgroundColor:[UIColor blueColor]];
    [self.view addSubview:tapView];
    [tapView release];
    
    
}

+ (NSInteger) gototo:(NSInteger)tagu
{
     NSLog(@"点击按钮:%d",tagu);
    return tagu;
}

- (NSInteger) getTagaaaa:(NSInteger )tags
{
    NSLog(@"tag is %d",tags);
    return tags;
}
- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
