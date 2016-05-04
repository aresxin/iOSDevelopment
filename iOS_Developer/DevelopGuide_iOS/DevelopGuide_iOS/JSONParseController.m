//
//  JSONParseController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "JSONParseController.h"
#import "JOSNParse.h"
#import "JSONAutoSerializer.h"
@implementation JSONParseController
@synthesize textView_;

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
    [textView_ release];
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

- (IBAction) parserJSON:(id)sender
{
    NSString *str = [JOSNParse parseJOSN];
    textView_.text = str;
}

//将对象封装成json格式
- (IBAction) packageJSON:(id)sender
{
    People *pelple_ = [[[People alloc] init] autorelease];
    pelple_.name = @"bug";
    pelple_.info = @"json text object";
    /*
    NSDictionary *dic = [NSDictionary dictionaryWithObject:pelple_.name forKey:@"name"];
    NSArray *arr = [NSArray arrayWithObjects:@"1",@"2" ,nil];
    NSString *jsonvlue = [arr JSONRepresentation];
    */ 
    NSString *jsonvlue = [[JSONAutoSerializer sharedSerializer] serializeObject:pelple_];
    textView_.text = jsonvlue;
}
@end

@implementation People
@synthesize name = _name;
@synthesize info = _info;
- (id) init
{
    self = [super init];
    if (self) 
    {
        
    }
    return self;
}
- (void) dealloc
{
    [_name release];
    [_info release];
    [super dealloc];
}

@end
