//
//  CreatePDFViewController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CreatePDFViewController.h"
#import "FileManager.h"
#import "GenerationgPDFManager.h"

@implementation CreatePDFViewController

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

- (IBAction) createdPDF:(id)sender
{
    NSString *pdfPath = [FileManager createFilePath:@"temp"];
    NSString *pdfName = [pdfPath stringByAppendingPathComponent:@"testSuper.pdf"];
    GenerationgPDFManager *pdfMge = [[GenerationgPDFManager alloc] init];
    CGRect rect = CGRectMake(0, 0, 595, 842);
    [pdfMge GenerationgPDFWithFilePath:pdfName 
                              withRect:rect 
                        withPDFInfoDic:nil];
    [pdfMge release];
}
@end
