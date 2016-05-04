    //
//  DWFreehandAnnPropertySettingsController.m
//  DWViewer
//
//  Created by liuqw on 11-8-25.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DWFreehandAnnPropertySettingsController.h"
#import "DWViewerGUIConst.h"

const int      screenDistance               = 10;
const int      colorButtonHeight            = 25;
const int      portraitTopDistance          = 50;
const int      landscapeTopDistance         = 40;
const int      portraitDistance             = 20;
const int      landscapeDistance            = 20;

// wangpp 2012.3.9 start
// freehand transparent
const int      portraitTableViewHeight       = 185;
const int      landscapeTableViewHeight      = 65;
// wangpp 2012.3.9 end

const int      ipadButtonDistance           = 10;
const int      ipadButtonSize               = 40;
const int      buttonCornerRadius           = 4;
const CGFloat  buttonBorderWidth            = 2.5;
const CGFloat  buttonSelectTransform        = 1.1;

#define _TAG_LINECOLOR_TITLELABEL_          10000
#define _TAG_LINESIZE_TITLELABEL_           10001
#define _TAG_LINESIZE_TABLEVIEW_            10002
#define _TAG_LINESIZE_CELL_DEMOLINE_        10003
#define _TAG_LINESIZE_CELL_TITLELABEL_      10004

// wangpp 2012.3.27 start
// freehand transparent
#define _TAG_LINETRANSPARENT_BG_			10005
#define _TAG_TRANSPARENT_SWITCHBUTTON_      10006
// wangpp 2012.3.27 end

#define _TAG_LINECOLOR_BUTTON_MIN_          10099
#define _TAG_LINESIZE_BUTTON_MIN_           10199

#define RGB(r,g,b)  ((b << 16) | (g << 8) | r)

// iPad class
@implementation DWLineSizeButton

@synthesize lineSize = lineSize_;

- (id)initWithLineSize:(int)lineSize
{
    if (self = [super init])
	{
		self.lineSize = lineSize;
    }
    return self;
}

@end



@implementation DWFreehandAnnPropertySettingsController
@synthesize delegate;
@synthesize freehandLineColor = freehandLineColor_;
@synthesize freehandLineSize = freehandLineSize_;

// wangpp 2012.2.29 start
// freehand transparent
@synthesize  freehandTransparent = freehandTransparent_;
// wangpp 2012.2.29 end

// wangpp 2012.2.29 start
// freehand transparent

// 2012.02.14 M.Chikyu start.
/*
- (id) initWithLineColor:(UIColor*)lineColor withLineSize:(int)lineSize
 */
/*
- (id) initWithLineColor:(UIColor*)lineColor
			withLineSize:(int)lineSize
		 withOrientation:(UIInterfaceOrientation)orientation
 */
// 2012.02.14 M.Chikyu end.

- (id) initWithLineColor:(UIColor*)lineColor
			withLineSize:(int)lineSize
	   withIsTransparent:(BOOL)transparent
		 withOrientation:(UIInterfaceOrientation)orientation
// wangpp 2012.2.29 end

{
	if (self = [super init])
	{
		lineColorArray_ = [[NSArray alloc] initWithObjects:
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(192.0 / 255.0) green:(192.0 / 255.0) blue:(192.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           (UIColor*)nil];
		
		lineSizeArray_ = [[NSArray alloc] initWithObjects:
                          @"1pt", @"2pt", @"3pt", @"4pt", @"5pt",
						  @"7pt", @"9pt", @"11pt", @"13pt", (NSString*)nil];
		
		self.freehandLineColor = lineColor;
		self.freehandLineSize = lineSize;
		
		// wangpp 2012.2.29 start
		// freehand transparent
		self.freehandTransparent = transparent;
		// wangpp 2012.2.29 end
		
		deviceIsiPad_ = NO;
		propertyType_ = UIPropertyTypeAll;

		// 2012.02.14 M.Chikyu start.
		orientation_ = orientation;
		// 2012.02.14 M.Chikyu end.
	}

	return self;
}

// wangpp 2012.2.29 start
// freehand transparent
/*
- (id) initForiPadWithPropertyType:(UIPropertyType)type 
                     withLineColor:(UIColor*)lineColor 
                      withLineSize:(int)lineSize;
 */
- (id) initForiPadWithPropertyType:(UIPropertyType)type 
                     withLineColor:(UIColor*)lineColor 
                      withLineSize:(int)lineSize
				 withIsTransparent:(BOOL)transparent;
// wangpp 2012.2.29 end

{
	if (self = [super init])
	{
		lineColorArray_ = [[NSArray alloc] initWithObjects:
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(192.0 / 255.0) green:(192.0 / 255.0) blue:(192.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           (UIColor*)nil];
		
		lineSizeButtonImageArray_ = [[NSArray alloc] initWithObjects:
									 _ICON_FREEHAND_LINESIZE_BUTTON_01PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_02PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_03PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_04PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_05PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_07PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_09PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_11PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_12PIX,
									 (char*) nil];
		
		lineSizeArray_ = [[NSArray alloc] initWithObjects:
                          @"1pt", @"2pt", @"3pt", @"4pt", @"5pt",
						  @"7pt", @"9pt", @"11pt", @"13pt", (NSString*)nil];
		
		propertyType_ = type;
		self.freehandLineColor = lineColor;
		self.freehandLineSize = lineSize;
		
		// wangpp 2012.2.29 start
		// freehand transparent
		self.freehandTransparent = transparent;
		// wangpp 2012.2.29 end
		
		deviceIsiPad_ = YES;
	}

	return self;
}


- (id) initForiPadWithLineColor:(UIColor*)lineColor
{
	if (self = [super init])
	{
		lineColorArray_ = [[NSArray alloc] initWithObjects:
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(0.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(80.0 / 255.0) green:(80.0 / 255.0) blue:(80.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(192.0 / 255.0) green:(192.0 / 255.0) blue:(192.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(0.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(0.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(0.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                           (UIColor*)nil];
		
		lineSizeButtonImageArray_ = [[NSArray alloc] initWithObjects:
									 _ICON_FREEHAND_LINESIZE_BUTTON_01PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_02PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_03PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_04PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_05PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_07PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_09PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_11PIX,
									 _ICON_FREEHAND_LINESIZE_BUTTON_12PIX,
									 (char*) nil];
				
		self.freehandLineColor = lineColor;
		self.freehandLineSize = 0;
		
		deviceIsiPad_ = YES;
		propertyType_ = UIPropertyTypeLineColor;
	}

	return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    selectGhostView_ = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[self getSelectColorImageName]]];
    selectGhostView_.backgroundColor = [UIColor clearColor];
	
	switch (propertyType_)
	{
		case UIPropertyTypeAll:
			self.view.backgroundColor = [UIColor darkGrayColor];
			[self initNavigationController];
			[self initPropertySettingView];
			break;

		case UIPropertyTypeLineColor:
			self.view.backgroundColor = [UIColor lightGrayColor];
			[self initColorPropertySettingView];
			break;

		case UIPropertyTypeLineSize:
			self.view.backgroundColor = [UIColor lightGrayColor];
			[self initSizePropertySettingView];
			break;

		// wangpp 2012.3.5 start
		// freehand transparent
		case UIPropertyTypeTransparent:
			self.view.backgroundColor = [UIColor lightGrayColor];
			[self initTransparentSettingView];
            break;
		// wangpp 2012.3.5 end
			
		default:
			break;
	}
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	activeIndicator_ = [[UIActivityIndicatorView alloc]
						initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	
	if (activeIndicator_ != nil)
	{
		activeIndicator_.frame = CGRectMake(0, 0, 40, 40);
//		[activeIndicator_ setBackgroundColor:[UIColor whiteColor]];
//		[activeIndicator_ setAlpha:0.8];

		if ([activeIndicator_ respondsToSelector:@selector(color)])
		{
			activeIndicator_.color = [UIColor blackColor];
		}
		// 2012.02.14 M.Chikyu start.
		else
		{
			if ([[UIScreen mainScreen] scale] == 2.0)
			{
				activeIndicator_.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
			}
		}
		// 2012.02.14 M.Chikyu end.
		
		[self.view addSubview:activeIndicator_];
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
}

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void)viewWillDisappear:(BOOL)animated
{
	[self displayIndicator];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[self hideIndicator];
}
// 2012.02.01(Ver2.1 New) M.Chikyu


#pragma mark -
#pragma mark draw for iphone

- (void) initNavigationController
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
    [[UIApplication sharedApplication] setStatusBarHidden:NO 
                                            withAnimation:UIStatusBarAnimationNone];
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	// init navigationController
	self.title = NSLocalizedString(@"TITLE_FREEHAND_PROPERTYTITLE", nil);

	// init back button.
	UIButton* backButton = [UIButton buttonWithType:(UIButtonType)101];
    [backButton setTitle:NSLocalizedString(@"BUTTON_TITLE_BACK", nil) 
				forState:UIControlStateNormal];
    [backButton addTarget:self 
				   action:@selector(actionTouchBackButton:) 
		 forControlEvents:UIControlEventTouchDown];
    UIBarButtonItem* backButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backButton];
    self.navigationItem.leftBarButtonItem = backButtonItem;
    [backButtonItem release];
	
	
	// init navigation controller
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	self.navigationController.navigationBarHidden = NO;
}


- (void) initPropertySettingView
{
	int viewWidth = [self getViewWidth];
	int viewHeight = [self getViewHeight];
	int heightDistace = [self getPropertyDistance];
	int topDistance = [self getTopDistance];
	
	// wangpp 2012.3.9 start
	// freehand transparent
	int tableViewHeight = [self getTableViewHeight];
	// wangpp 2012.3.9  end
	
	int buttonWidth = (viewWidth-screenDistance*2)/8;
	
	COLORREF colorRefSrcColor = 0;
	COLORREF colorRefDstColor = 0;
	
	[self transformUIColorToColorRef:self.freehandLineColor  
						withColorRef:&colorRefSrcColor];
	
	// 1.1 add line color title
	CGRect lineColorTitleLabelRect = CGRectMake(screenDistance, topDistance, 200, 30);
	UILabel* lineColorTitleLabel = [[UILabel alloc] initWithFrame:lineColorTitleLabelRect];
	lineColorTitleLabel.tag = _TAG_LINECOLOR_TITLELABEL_;
	lineColorTitleLabel.backgroundColor = [UIColor clearColor];
	lineColorTitleLabel.textColor = [UIColor whiteColor];
	lineColorTitleLabel.text = NSLocalizedString(@"TITLE_FREEHAND_LINECOLOR", nil);
	[self.view addSubview:lineColorTitleLabel];
	[lineColorTitleLabel release];
	
	// 1.2 add line color button 
	int lineColorButtonCount = [lineColorArray_ count];
	for (int i = 0; i < lineColorButtonCount; i++)
	{
        float originX = screenDistance + buttonWidth * i;
        float originY = topDistance + 35;
        if (i >= 8) {
            originX = screenDistance + buttonWidth * (i - 8);
            originY = topDistance + colorButtonHeight + 35;
        }
		CGRect buttonRect = CGRectMake(originX,
									   originY, 
									   buttonWidth, 
									   colorButtonHeight);
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		
		colorButton.tag = _TAG_LINECOLOR_BUTTON_MIN_+i;
		colorButton.backgroundColor = [lineColorArray_ objectAtIndex:i];
		
		[colorButton setFrame:buttonRect];
		[colorButton addTarget:self
						action:@selector(actionTouchLineColorButton:) 
			  forControlEvents:UIControlEventTouchUpInside];
		
		// check select
		UIColor* bgColor = (UIColor*)[lineColorArray_ objectAtIndex:i];
		[self transformUIColorToColorRef:bgColor  withColorRef:&colorRefDstColor];
		
		// 選択枠の追加 の対応
		[self.view addSubview:colorButton];
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame];
		}
	}
	
	// 2.1 add line size title
	CGRect lineSizeTitleLabelRect = CGRectMake(screenDistance, 
											   topDistance+35+colorButtonHeight * 2+heightDistace, 
											   200, 
											   30);
	UILabel* lineSizeTitleLabel = [[UILabel alloc] initWithFrame:lineSizeTitleLabelRect];
	lineSizeTitleLabel.tag = _TAG_LINESIZE_TITLELABEL_;
	lineSizeTitleLabel.backgroundColor = [UIColor clearColor];
	lineSizeTitleLabel.textColor = [UIColor whiteColor];
	lineSizeTitleLabel.text = NSLocalizedString(@"TITLE_FREEHAND_LINESIZE", nil);
	[self.view addSubview:lineSizeTitleLabel];
	[lineSizeTitleLabel release];
	
	// 2.2 add line size table view
	
	// wangpp 2012.2.28 start
	// freehand transparent
	/*
	CGRect textColorTitleLabelRect = CGRectMake(screenDistance, 
												topDistance+35*2+colorButtonHeight*2+heightDistace, 
												viewWidth-screenDistance*2, 
												viewHeight-(topDistance+35*2+colorButtonHeight*2+heightDistace)
												-screenDistance*3);
	 */
	
	CGRect textColorTitleLabelRect = CGRectMake(screenDistance, 
												topDistance+35*2+colorButtonHeight*2+heightDistace, 
												viewWidth-screenDistance*2, 
												tableViewHeight);
	
	// wangpp 2012.2.28 end
	
	UITableView* lineSizeTableView = [[UITableView alloc] initWithFrame:textColorTitleLabelRect
																  style:UITableViewStylePlain];
	lineSizeTableView.tag = _TAG_LINESIZE_TABLEVIEW_;
	lineSizeTableView.delegate = self;
	lineSizeTableView.dataSource = self;
	lineSizeTableView.separatorColor = [UIColor blackColor];
	lineSizeTableView.layer.cornerRadius = 7.0f;
	lineSizeTableView.layer.borderColor = [UIColor blackColor].CGColor;
	lineSizeTableView.layer.borderWidth = 1.0;
	[self.view addSubview:lineSizeTableView];
	[lineSizeTableView release];
	
	// wangpp 2012.2.28 start
	// freehand transparent
	
	// 2.3 add line trans label.
	CGRect bgViewTransRect = CGRectMake(screenDistance,
										topDistance+35*2+colorButtonHeight*2+heightDistace+tableViewHeight+30, 
										viewWidth-screenDistance*2, 
										screenDistance*3.5);
	UIView* bgViewTrans_ = [[UIView alloc]initWithFrame:bgViewTransRect];
	bgViewTrans_.backgroundColor = [UIColor whiteColor];
	bgViewTrans_.layer.borderWidth = 1.0;
	bgViewTrans_.layer.borderColor = [UIColor blackColor].CGColor;
	bgViewTrans_.tag = _TAG_LINETRANSPARENT_BG_;
	
	CGRect transparentLabelRect = CGRectMake(10, 0, 200, screenDistance*3.5);
	UILabel* transparentLabel = [[UILabel alloc] initWithFrame:transparentLabelRect];
	NSString* labelText = NSLocalizedString(@"TITLE_FREEHAND_TRANSPARENT",nil);
	transparentLabel.text = labelText;
	[bgViewTrans_ addSubview:transparentLabel];
	[transparentLabel release];
	
	UISwitch* transparentSwitchButton = [[UISwitch alloc] init]; 
	transparentSwitchButton.frame = CGRectMake(bgViewTransRect.size.width - transparentSwitchButton.frame.size.width,
											   (bgViewTransRect.size.height - transparentSwitchButton.frame.size.height) / 2, 
											   transparentSwitchButton.frame.size.width, 
											   transparentSwitchButton.frame.size.height);
	transparentSwitchButton.on = self.freehandTransparent ; 
	[transparentSwitchButton addTarget:self
								action:@selector(actionTouchLineTransButton:)
					  forControlEvents:UIControlEventValueChanged];
	transparentSwitchButton.tag = _TAG_TRANSPARENT_SWITCHBUTTON_;
	[bgViewTrans_ addSubview:transparentSwitchButton];
	[transparentSwitchButton release];

	[self.view addSubview:bgViewTrans_];
	[bgViewTrans_ release];
	
	// wangpp 2012.2.28 end
}


- (void) resetPropertySettingViewFrame
{
	int viewWidth = [self getViewWidth];
	int viewHeight = [self getViewHeight];
	int heightDistace = [self getPropertyDistance];
	int buttonWidth = (viewWidth-screenDistance*2)/8;
	int topDistance = [self getTopDistance];

	//  wangpp 2012.3.27 start
	// freehand transparent
	int tableViewHeight = [self getTableViewHeight];
	//  wangpp 2012.3.27  end
	
	// 1.1 reset background color title label frame
	UIView* lineColorTitleLabel = [self.view viewWithTag:_TAG_LINECOLOR_TITLELABEL_];
	if (lineColorTitleLabel != nil)
	{
		CGRect lineColorLabelRect = lineColorTitleLabel.frame;
		lineColorLabelRect.origin.y = topDistance;
		[lineColorTitleLabel setFrame:lineColorLabelRect];
	}
	
	// 1.2 reset background color button
	// 選択枠の追加 の対応
	COLORREF colorRefSrcColor = 0;	
	[self transformUIColorToColorRef:self.freehandLineColor  
						withColorRef:&colorRefSrcColor];
    
	int lineColorButtonCount = [lineColorArray_ count];
	for (int i = 0; i < lineColorButtonCount; i++)
	{
		UIView* colorButton = [self.view viewWithTag:_TAG_LINECOLOR_BUTTON_MIN_+i];
		if (colorButton != nil)
		{
			CGRect buttonRect = colorButton.frame;
            if (i < 8) {
                buttonRect.origin.x = screenDistance + buttonWidth * i;
                buttonRect.origin.y = topDistance + 35;
            } else {
                buttonRect.origin.x = screenDistance + buttonWidth * (i - 8);
                buttonRect.origin.y = topDistance + colorButtonHeight + 35;
            }
			buttonRect.size.width = buttonWidth;
			
			[colorButton setFrame:buttonRect];
		}
		
		// 選択枠の追加 の対応
        COLORREF colorRefDstColor = 0;
		UIColor* color_ = (UIColor*)[lineColorArray_ objectAtIndex:i];
		[self transformUIColorToColorRef:color_  withColorRef:&colorRefDstColor];
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame];
		}
	}
	
	// 2.1 reset line size title
	UIView* lineSizeTitleLabel = [self.view viewWithTag:_TAG_LINESIZE_TITLELABEL_];
	if (lineSizeTitleLabel != nil)
	{
		CGRect lineSizeTitleLabelRect = lineSizeTitleLabel.frame;
		lineSizeTitleLabelRect.origin.y = topDistance+35+colorButtonHeight*2+heightDistace;
		[lineSizeTitleLabel setFrame:lineSizeTitleLabelRect];
	}
	
	// 2.2 add line size table view
	UITableView* lineSizeTableView = (UITableView*)[self.view viewWithTag:_TAG_LINESIZE_TABLEVIEW_];
	if (lineSizeTableView != nil)
	{
		CGRect textColorTitleLabelRect = lineSizeTableView.frame;
		
		textColorTitleLabelRect.origin.y    = topDistance+35*2+colorButtonHeight*2+heightDistace;
		textColorTitleLabelRect.size.width  = viewWidth-screenDistance*2;
		
		// wangpp 2012.3.27 start
		// freehand transparent
		/*
		textColorTitleLabelRect.size.height = viewHeight-(topDistance+35*2+colorButtonHeight*2+heightDistace)
		                                      -screenDistance*3;
		*/
		textColorTitleLabelRect.size.height = tableViewHeight; 
		// wangpp 2012.3.27 end
		
		[lineSizeTableView setFrame:textColorTitleLabelRect];
		[lineSizeTableView reloadData];
	}
	
	
	// wangpp 2012.3.27 start
	// freehand transparent
	UIView*  bgViewTrans_ = (UIView*)[self.view viewWithTag:_TAG_LINETRANSPARENT_BG_];
	if (bgViewTrans_ != nil) 
	{
		CGRect bgViewTransRect	 = bgViewTrans_.frame;
		bgViewTransRect.origin.y = topDistance+35*2+colorButtonHeight*2+heightDistace+tableViewHeight+30;
		bgViewTrans_.frame		 = bgViewTransRect;
		
		UISwitch* transparentSwitchButton = (UISwitch*)[bgViewTrans_ viewWithTag:_TAG_TRANSPARENT_SWITCHBUTTON_];
		if (transparentSwitchButton != nil) 
		{
			CGRect switchButtonRect   = transparentSwitchButton.frame;
			switchButtonRect.origin.x = bgViewTransRect.size.width - transparentSwitchButton.frame.size.width;
			bgViewTrans_.frame		  = switchButtonRect;
		}
	}
	// wangpp 2012.3.27 end
}


#pragma mark -
#pragma mark draw for ipad
- (void) initColorPropertySettingView
{
	COLORREF colorRefSrcColor = 0;
	COLORREF colorRefDstColor = 0;
	
	[self transformUIColorToColorRef:self.freehandLineColor  
						withColorRef:&colorRefSrcColor];
	
	int i = 0;
	int colorButtonCount = [lineColorArray_ count];
	
	for (i=0; i<colorButtonCount; i++)
	{
        CGRect buttonRect = CGRectMake(screenDistance+(screenDistance+ipadButtonSize)*(i%(colorButtonCount/2)), 
									   screenDistance+(ipadButtonSize+screenDistance)*(i/(colorButtonCount/2)), 
									   ipadButtonSize, 
									   ipadButtonSize);
        
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		
		colorButton.tag = _TAG_LINECOLOR_BUTTON_MIN_+i;
		colorButton.backgroundColor = [lineColorArray_ objectAtIndex:i];
		
		[colorButton setFrame:buttonRect];
		[colorButton addTarget:self
						action:@selector(actionTouchLineColorButton:) 
			  forControlEvents:UIControlEventTouchUpInside];
		
		// check select
		UIColor* bgColor = (UIColor*)[lineColorArray_ objectAtIndex:i];
		[self transformUIColorToColorRef:bgColor  withColorRef:&colorRefDstColor];
		
		// 選択枠の追加 の対応
		colorButton.layer.cornerRadius = buttonCornerRadius;
		colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
		colorButton.layer.borderWidth = buttonBorderWidth;
		[self.view addSubview:colorButton];
		
		if (colorRefSrcColor == colorRefDstColor)
		{
			[self selectColorButtonWithButtonFrame:colorButton.frame];
		}
	}

    [self.view setFrame:CGRectMake(0, 
								   0, 
								   screenDistance*(colorButtonCount/2+1)
								   +ipadButtonSize*colorButtonCount/2, 
								   screenDistance*3+ipadButtonSize*2)];
}


- (void) initSizePropertySettingView
{
	int i = 0;
	int sizeButtonCount = [lineSizeArray_ count];
	
	for (i=0; i<sizeButtonCount; i++)
	{
		CGRect buttonRect = CGRectMake(screenDistance+(ipadButtonDistance-1)*i+ipadButtonSize*i, 
									   screenDistance, 
									   ipadButtonSize, 
									   ipadButtonSize);
		
		// get select size
		NSString* text = [lineSizeArray_ objectAtIndex:i];	
		NSRange range = [text rangeOfString:@"p"];
		int size = [[text substringToIndex:range.location] intValue];
		
		DWLineSizeButton* sizeButton = [[DWLineSizeButton alloc] initWithLineSize:size];
		[sizeButton setImage:[UIImage imageNamed:[lineSizeButtonImageArray_ objectAtIndex:i]]
					forState:UIControlStateNormal];
		
		sizeButton.tag = _TAG_LINESIZE_BUTTON_MIN_+i;
		
		[sizeButton setFrame:buttonRect];
		[sizeButton addTarget:self
						action:@selector(actionTouchLineSizeButton:) 
			  forControlEvents:UIControlEventTouchUpInside];
		
		// 選択枠の追加 の対応
		sizeButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
		sizeButton.layer.borderWidth = buttonBorderWidth;
		[self.view addSubview:sizeButton];
        [sizeButton release];
		
		if (self.freehandLineSize == size)
		{
            [self selectColorButtonWithButtonFrame:sizeButton.frame];
		}
	}
	
	CGRect viewRect = CGRectMake(0, 
								 0, 
								 screenDistance*2+ipadButtonDistance*(sizeButtonCount-1)+ipadButtonSize*sizeButtonCount, 
								 screenDistance*2+ipadButtonSize);
	[self.view setFrame:viewRect];
}

// wangpp 2012.2.28 start
// freehand transparent
- (void) initTransparentSettingView
{
	CGRect bgViewTransRect = CGRectMake(screenDistance, 
										screenDistance, 
										screenDistance*34,
										screenDistance*4);
	UIView* bgViewTrans_ = [[UIView alloc]initWithFrame:bgViewTransRect];
	bgViewTrans_.backgroundColor = [UIColor whiteColor];
	bgViewTrans_.layer.borderWidth = 1.0;
	bgViewTrans_.layer.borderColor = [UIColor blackColor].CGColor;
	bgViewTrans_.tag = _TAG_LINETRANSPARENT_BG_;
	
	CGRect transparentLabelRect = CGRectMake(5, screenDistance * 0.25, 200, screenDistance*3.5);
	UILabel* transparentLabel = [[UILabel alloc] initWithFrame:transparentLabelRect];
	NSString* labelText = NSLocalizedString(@"TITLE_FREEHAND_TRANSPARENT",nil);
	transparentLabel.text = labelText;
	[bgViewTrans_ addSubview:transparentLabel];
	[transparentLabel release];
	
	UISwitch* transparentSwitchButton = [[UISwitch alloc] init]; 
	transparentSwitchButton.frame = CGRectMake(bgViewTransRect.size.width - transparentSwitchButton.frame.size.width,
											   (bgViewTransRect.size.height - transparentSwitchButton.frame.size.height) / 2, 
											   transparentSwitchButton.frame.size.width, 
											   transparentSwitchButton.frame.size.height);
	transparentSwitchButton.on = self.freehandTransparent ; 
	[transparentSwitchButton addTarget:self
								action:@selector(actionTouchLineTransButton:)
					  forControlEvents:UIControlEventValueChanged];
	transparentSwitchButton.tag = _TAG_TRANSPARENT_SWITCHBUTTON_;
	[bgViewTrans_ addSubview:transparentSwitchButton];
	[transparentSwitchButton release];
	
	[self.view addSubview:bgViewTrans_];
	[bgViewTrans_ release];
	
	self.view.frame = CGRectMake(0, 0, 
								 bgViewTrans_.frame.size.width + screenDistance * 2, 
								 bgViewTrans_.frame.size.height + screenDistance * 2);
}
//  wangpp 2012.2.28 end



#pragma mark -
#pragma mark get screen state
- (BOOL) UIDeviceIsPortrait
{
	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		return YES;
	}
	else
	{
		return NO;
	}
}

- (int) getViewWidth
{
	CGRect screenRect = [UIScreen mainScreen].bounds;
	if ([self UIDeviceIsPortrait] == YES)
	{
		return screenRect.size.width;
	}
	else
	{
		return screenRect.size.height;
	}
	
}

- (int) getViewHeight
{
	CGRect screenRect = [UIScreen mainScreen].bounds;
	if ([self UIDeviceIsPortrait] == YES)
	{
		return screenRect.size.height;
	}
	else
	{
		return screenRect.size.width;
	}
	
}

- (int) getPropertyDistance
{
	if ([self UIDeviceIsPortrait] == YES)
	{
		return portraitDistance;
	}
	else
	{
		return landscapeDistance;
	}
}

- (int) getTopDistance
{
	if ([self UIDeviceIsPortrait] == YES)
	{
		return portraitTopDistance;
	}
	else
	{
		return landscapeTopDistance;
	}
}

// wangpp 2012.3.9 start
// freehand transparent
- (int) getTableViewHeight
{
	if ([self UIDeviceIsPortrait] == YES) 
	{
		return portraitTableViewHeight;
	}
	else
	{
		return landscapeTableViewHeight;
	}
}
//  wangpp 2012.3.9 end

// 選択枠の追加 の対応
- (void) selectColorButtonWithButtonFrame:(CGRect)rect
{
    CGRect ghostViewRect = CGRectZero;
    if (deviceIsiPad_ == YES)
	{
		ghostViewRect = rect;
	}
	else
	{
		ghostViewRect = CGRectMake(rect.origin.x - 0.5, 
                                   rect.origin.y, 
                                   rect.size.width + 1, 
                                   rect.size.height);
	}
    
    selectGhostView_.frame = ghostViewRect;
    [self.view addSubview:selectGhostView_];
    [self.view bringSubviewToFront:selectGhostView_];
}


- (NSString*) getSelectColorImageName
{
	if (deviceIsiPad_ == YES)
	{
		return SELECTCOLOR_IMAGE_IPAD;
	}
	else if ([self UIDeviceIsPortrait] == YES)
	{
		return SELECTCOLOR_IMAGE_PORTRAIT;
	}
	else
	{
		return SELECTCOLOR_IMAGE_LANDSCAPE;
	}
}


- (void) transformUIColorToColorRef:(UIColor *)color 
					   withColorRef:(COLORREF *)colorRef
{
	NSString *RGBValue = [NSString stringWithFormat:@"%@",color];
	NSArray *RGBArr = [RGBValue componentsSeparatedByString:@" "];
	
	int colorR = [[RGBArr objectAtIndex:1] floatValue] * 255;
	int colorG = [[RGBArr objectAtIndex:2] floatValue] * 255;
	int colorB = [[RGBArr objectAtIndex:3] floatValue] * 255;
	
	*colorRef = RGB(colorR, colorG, colorB);
}


#pragma mark -
#pragma mark action
- (IBAction) actionTouchBackButton:(id)sender
{
	// wangpp 2012.2.29 start
	// freehand transparent
	
	/*[delegate updateFreehandAnnPropertyWithLineColor:self.freehandLineColor withLineSize:self.freehandLineSize];*/
	[delegate updateFreehandAnnPropertyWithLineColor:self.freehandLineColor 
										withLineSize:self.freehandLineSize  
									   withLineTrans:self.freehandTransparent];
	// wangpp 2012.2.29 end
	
	[self.parentViewController dismissModalViewControllerAnimated:YES];
}


- (IBAction) actionTouchLineColorButton:(id)sender
{
	// 選択枠の追加 の対応
	UIButton* selectColorButton = (UIButton*)sender;
    [self selectColorButtonWithButtonFrame:selectColorButton.frame];
	
	self.freehandLineColor = selectColorButton.backgroundColor;
	// 選択枠の追加 の対応
	[self.view setNeedsDisplay];
	
	if (deviceIsiPad_ == YES)
	{
		// wangpp 2012.2.29 start
		// freehand transparent
		
		/*
		 [delegate updateFreehandAnnPropertyForiPadWithLineColor:self.freehandLineColor
													withLineSize:self.freehandLineSize];
		 */
		
		[delegate updateFreehandAnnPropertyForiPadWithLineColor:self.freehandLineColor
												   withLineSize:self.freehandLineSize
												  withLineTrans:self.freehandTransparent];
		
		// wangpp 2012.2.29 end
	}
}


- (IBAction) actionTouchLineSizeButton:(id)sender
{
	// 選択枠の追加 の対応
	DWLineSizeButton* selectSizeButton = (DWLineSizeButton*)sender;
    [self selectColorButtonWithButtonFrame:selectSizeButton.frame];
    
	self.freehandLineSize = selectSizeButton.lineSize;
	[self.view setNeedsDisplay];
	
	if (deviceIsiPad_ == YES)
	{
		// wangpp 2012.2.29 start
		// freehand transparent
		
		/*
		 [delegate updateFreehandAnnPropertyForiPadWithLineColor:self.freehandLineColor
		                                            withLineSize:self.freehandLineSize];
		 */
		
		[delegate updateFreehandAnnPropertyForiPadWithLineColor:self.freehandLineColor
												   withLineSize:self.freehandLineSize
												  withLineTrans:self.freehandTransparent];
		
		// wangpp 2012.2.29 end
	}
}

// wangpp 2012.2.29 start
// freehand transparent
- (IBAction) actionTouchLineTransButton:(id)sender
{
	UISwitch*  switchButton = (UISwitch*)sender;
	self.freehandTransparent = switchButton.isOn;
	if (deviceIsiPad_ == YES) 
	{
		[delegate updateFreehandAnnPropertyForiPadWithLineColor:self.freehandLineColor
												   withLineSize:self.freehandLineSize
												  withLineTrans:self.freehandTransparent];
	}
}
// wangpp 2012.2.29 end

#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [lineSizeArray_ count];
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 40;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault 
									   reuseIdentifier:CellIdentifier] autorelease];
    }
	
	int viewWidth = [self getViewWidth];
	
	// 1. draw title label
	CGRect textLabelRect = CGRectMake(screenDistance, screenDistance, 50, 30);
	UILabel* textLabel = (UILabel*)[cell.contentView viewWithTag:_TAG_LINESIZE_CELL_TITLELABEL_];
	if (textLabel == nil)
	{
		textLabel = [[UILabel alloc] initWithFrame:textLabelRect];
		textLabel.tag = _TAG_LINESIZE_CELL_TITLELABEL_;
		textLabel.text = [lineSizeArray_ objectAtIndex:[indexPath row]];
		[cell.contentView addSubview:textLabel];
		[textLabel release];
	}
	else
	{
		[textLabel setFrame:textLabelRect];
		textLabel.text = [lineSizeArray_ objectAtIndex:[indexPath row]];
	}
	
	// 2. draw demo line
	NSRange range = [textLabel.text rangeOfString:@"p"];
    int size = [[textLabel.text substringToIndex:range.location] intValue];
	
	CGRect demoLineViewRect = CGRectMake(screenDistance*2+50, 
										 cell.frame.size.height/2-size/2, 
										 viewWidth-(screenDistance*2+50)-60, 
										 size);
	UIView* demoLineView = [cell.contentView viewWithTag:_TAG_LINESIZE_CELL_DEMOLINE_];
	if (demoLineView == nil)
	{
		demoLineView = [[UIView alloc] initWithFrame:demoLineViewRect];
		demoLineView.tag = _TAG_LINESIZE_CELL_DEMOLINE_;
		demoLineView.backgroundColor = [UIColor blackColor];
		[cell.contentView addSubview:demoLineView];
		[demoLineView release];
	}
	else
	{
		[demoLineView setFrame:demoLineViewRect];
	}
	
	
	// 3. draw accessory view
	if (freehandLineSize_ == size)
	{
		cell.accessoryType = UITableViewCellAccessoryCheckmark;
	}
	else
	{
		cell.accessoryType = UITableViewCellAccessoryNone;
	}
	
    return cell;
}


#pragma mark -
#pragma mark Table view delegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	// get select size
	NSString* text = [lineSizeArray_ objectAtIndex:[indexPath row]];	
	NSRange range = [text rangeOfString:@"p"];
    int size = [[text substringToIndex:range.location] intValue];
	
	freehandLineSize_ = size;
	
	[tableView reloadData];
}


#pragma mark -
#pragma mark rotate delegate
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
	 */
	
	// 2012.02.14 M.Chikyu start.
	/*
	if (interfaceOrientation == self.interfaceOrientation)
	 */
	if (interfaceOrientation == orientation_)
	// 2012.02.14 M.Chikyu end.
	{
		return YES;
	}
	else
	{
		return NO;
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
}


- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
	[self resetPropertySettingViewFrame];
}


#pragma mark -
#pragma mark memory leaks

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
}


- (void)dealloc
{
	if (lineColorArray_ != nil)
	{
		[lineColorArray_ release];
	}
	
	if (lineSizeArray_ != nil)
	{
		[lineSizeArray_ release];
	}
	
	if (lineSizeButtonImageArray_ != nil)
	{
		[lineSizeButtonImageArray_ release];
	}
	self.freehandLineColor = nil;
    
    // 選択枠の追加 の対応
    [selectGhostView_ release];
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	if (activeIndicator_ != nil)
	{
		[activeIndicator_ removeFromSuperview];
		[activeIndicator_ release];
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu

    [super dealloc];
}


// 2012.02.01(Ver2.1 New) M.Chikyu

- (void) displayIndicator
{
	
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	if (activeIndicator_.isAnimating == YES)
	{
		return;
	}
	
	activeIndicator_.center = self.view.center;
	
	[activeIndicator_ performSelectorInBackground:@selector(startAnimating)
									   withObject:nil];
}

- (void) hideIndicator
{
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	[self.view bringSubviewToFront:activeIndicator_];
	
	if (activeIndicator_.isAnimating == NO)
	{
		return;
	}
	
	[activeIndicator_ stopAnimating];
}

// 2012.02.01(Ver2.1 New) M.Chikyu

@end
