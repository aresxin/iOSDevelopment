    //
//  AboutDocuworksViewController.m
//  DWViewer
//
//  Created by icd-lixin on 6/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AboutDocuworksViewController.h"
#import "DWViewerGUIConst.h"
#import "Utility.h"

@implementation AboutDocuworksViewController

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
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
	
	self.title = NSLocalizedString(@"TITLE_ALERT_APPNAME", nil);
	// init back button.
	UIBarButtonItem *buttonClose = [[UIBarButtonItem alloc]
									initWithTitle:NSLocalizedString(@"BUTTON_TITLE_BACK", nil) 
								    style:UIBarButtonItemStyleBordered 											 
								    target:self 											
								    action:@selector(actionTouchCloseButton)];
	self.navigationItem.leftBarButtonItem = buttonClose;
	[buttonClose release];
	
	// init support button	
	UIBarButtonItem *closeItem = [[[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"BUTTON_TITLE_LINK", nil)
																   style:UIBarButtonItemStyleBordered 
																  target:self
																  action:@selector(actionTouchSupportButton) ] 
								  autorelease];
	
	self.navigationItem.rightBarButtonItem = closeItem;
	
	// init navigation controller
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	self.navigationController.navigationBarHidden = NO;
	
	// init image view
	UIImageView* imageView = [[UIImageView alloc] 
							  initWithImage:[UIImage imageNamed:[self getImageNameWithInterfaceOrientation:self.interfaceOrientation]]];
	CGRect screenRect = [UIScreen mainScreen].bounds;
	imageView.frame = CGRectMake(0, 45, screenRect.size.width, screenRect.size.height);
	[self.view addSubview:imageView];
	[imageView release];
    
    // liuqw 20120206 start
    // init payment message.
    labelPaymentMessage_ = [[UILabel alloc]init];
    labelPaymentMessage_.numberOfLines = 0;
    labelPaymentMessage_.frame = [self getPaymentMessageLabelRectWithOrientation:self.interfaceOrientation];
    labelPaymentMessage_.text = NSLocalizedString(@"MSG_PAYMENT_NOTICE", nil);
    if (Utility::UIDeviceIsiPad() == NO)
    {
        labelPaymentMessage_.font = [UIFont systemFontOfSize:8];
    }
    else
    {
        labelPaymentMessage_.font = [UIFont systemFontOfSize:22];
    }
    [self.view addSubview:labelPaymentMessage_];
    // liuqw 20120206 end
}

- (void)viewWillAppear:(BOOL)animated
{
	[[UIApplication sharedApplication] setStatusBarHidden:NO];
    [self willAnimateRotationToInterfaceOrientation:self.interfaceOrientation duration:0];
    [super viewWillAppear:animated];
}

#pragma mark -
#pragma mark action for button
- (void) actionTouchCloseButton
{
	[self.parentViewController dismissModalViewControllerAnimated:YES];
	
}

- (void) actionTouchSupportButton
{
	NSURL* url = [NSURL URLWithString:NSLocalizedString(@"URL_SUPPORT", nil)];
	[[UIApplication sharedApplication] openURL:url];  
}

#pragma mark -
#pragma mark action for rotation
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Overriden to allow any orientation.
    if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
	if ( [self.view subviews] )
	{
		for (UIView *subview in [self.view subviews] )
		{
			[subview removeFromSuperview];
		}
	}
	
	// init image view
	UIImageView* imageView = [[UIImageView alloc] 
							  initWithImage:[UIImage imageNamed:[self getImageNameWithInterfaceOrientation:toInterfaceOrientation]]];
	
	CGRect screenRect = [UIScreen mainScreen].bounds;

	if (toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown
		|| toInterfaceOrientation == UIInterfaceOrientationPortrait)
	{
		imageView.frame = CGRectMake(0, 45, screenRect.size.width, screenRect.size.height);
	}
	else
	{
		imageView.frame = CGRectMake(0, 45, screenRect.size.height, screenRect.size.width);
	}
	
	[self.view addSubview:imageView];
	[imageView release];
    
    // liuqw 20120206 start
    [labelPaymentMessage_ removeFromSuperview];
    labelPaymentMessage_.frame = [self getPaymentMessageLabelRectWithOrientation:toInterfaceOrientation];
    [self.view addSubview:labelPaymentMessage_];
    // liuqw 20120206 end
}

- (NSString*) getImageNameWithInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	if (Utility::UIDeviceIsiPad() == NO)
	{
		if (UIInterfaceOrientationIsPortrait(toInterfaceOrientation))
		{
			return _ABOUTAPPLICATION_IPHONE_PORTRAIT_IMAGE_;
		}
		else
		{
			return _ABOUTAPPLICATION_IPHONE_LANDSCAPE_IMAGE_;
		}
		
	}
	else
	{
		if (UIInterfaceOrientationIsPortrait(toInterfaceOrientation))
		{
			return _ABOUTAPPLICATION_IPAD_PORTRAIT_IMAGE_;
		}
		else
		{
			return _ABOUTAPPLICATION_IPAD_LANDSCAPE_IMAGE_;
		}
		
	}
}

// liuqw 20120206 start
- (CGRect) getPaymentMessageLabelRectWithOrientation:(UIInterfaceOrientation)orientation
{
    float originX       = 0.0f;
    float originY       = 0.0f;
    float width         = 0.0f;
    float height        = 0.0f;
    
    CGRect screenRect   = [UIScreen mainScreen].bounds;
    float screenWidth   = screenRect.size.width;
    float screenHeight  = screenRect.size.height;
    
    if (Utility::UIDeviceIsiPad() == NO)
    {
        if (UIInterfaceOrientationIsPortrait(orientation)) 
        {
            originX = 10.0f;
            originY = screenHeight - 77;
            width   = screenWidth - 20;
            height  = 55;
        }
        else
        {
            originX = screenHeight / 2 + 10;
            originY = screenWidth - 110;
            width   = screenHeight / 2 - 10;
            height  = 90;
        }
    }
    else
    {
        if (UIInterfaceOrientationIsPortrait(orientation)) 
        {
            originX = 20.0f;
            originY = screenHeight - 200;
            width   = screenWidth - 40;
            height  = 160;
        }
        else
        {
            originX = screenHeight / 2 + 150;
            originY = screenWidth - 300;
            width   = screenHeight / 2 - 160;
            height  = 270;
        }
    }
    
    return CGRectMake(originX, originY, width, height);
}
// liuqw 20120206 end

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc
{
    // liuqw 20120206 start
    [labelPaymentMessage_ release];
    // liuqw 20120206 end
    
    [super dealloc];
}


@end
