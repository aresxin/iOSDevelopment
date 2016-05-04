//
//  SocketController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "SocketController.h"
#import "AsyncSocketImpl.h"
#import "GUIConst.h"

@implementation SocketController

@synthesize sendBtn;
@synthesize messageView;
@synthesize ipTextField;
@synthesize numtextField;

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
    [sendBtn release];
    [messageView release];
    [ipTextField release];
    [numtextField release];
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

#pragma make
#pragma make thouch
- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [messageView resignFirstResponder];
    [ipTextField resignFirstResponder];
    [numtextField resignFirstResponder];
}

- (IBAction) sendMessage:(id)sender
{
    [messageView resignFirstResponder];
    [ipTextField resignFirstResponder];
    [numtextField resignFirstResponder];
    
    if ([ipTextField.text length] > 0 && [numtextField.text length] > 0
        && [messageView.text length] > 0) 
    {
        AsyncSocketImpl *client = [AsyncSocketImpl sharedAsyncSocketImpl];
        
        if ([client  connectServer:ipTextField.text 
                              port:[numtextField.text intValue]]) 
        {
            [client sendMessage:messageView.text 
                        withTag:0];
        }
        else
        {
            UIAlertView *alert = 
            [[UIAlertView alloc]initWithTitle:NSLocalizedString(ERROR_TITLE, nil) 
                                      message:@"发送信息不成功"
                                     delegate:self
                            cancelButtonTitle:NSLocalizedString(ERROR_OK , nil)
                            otherButtonTitles:nil];	
            [alert show];
            [alert release];

        }
    }
    else
    {
        UIAlertView *alert = 
        [[UIAlertView alloc]initWithTitle:NSLocalizedString(ERROR_TITLE, nil) 
                                  message:@"请添写信息"
                                 delegate:self
                        cancelButtonTitle:NSLocalizedString(ERROR_OK , nil)
                        otherButtonTitles:nil];	
        [alert show];
        [alert release];
    }
}
@end
