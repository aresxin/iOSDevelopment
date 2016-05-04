//
//  DocumentEditController.m
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DocumentEditController.h"
#import "DocumentHandle.h"
#import "PageViewManager.h"
#import "PageEditManager.h"
#import "DWAnnotationInfo.h"
#import "DWScrollView.h"
#import "DWPageView.h"
#import "Utility.h"
#import "DWViewerAppDelegate.h"
#import "DWViewerGUIConst.h"

#define TAG_PROPERTYBAR_BORDER_VIEW 1001

#define TOOLBAR_HEIGHT_H            44
#define TOOLBAR_HEIGHT_V            32

#define TAG_BORDER_VIEW             301
#define TAG_SHADOW_VIEW             302
#define TAG_FREEHAND_VIEW           303
#define TAG_HIDDEN_VIEW             309

#define MAX_LINE_TEXT_COUNT         25
#define MAX_LINE_COUNT              20
#define MAX_ALL_TEXT_COUNT          500

// lixin 2011/09/15 start 
// NS-AR1007 の対応
#define TAG_ALERTVIEW_EDITFAIL      1007
// lixin 2011/09/15 end

// wangpp 2012.4.12 start
// login
#define TAG_ALERTVIEW_PERMIT_LOGIN  1100
#define INDEX_BUTTON_ITEM_ANNLIST_REGIST		6
// wangpp 2012.4.12 end


#define INDEX_BUTTON_ITEM_SELECT_DELETE			0

#define INDEX_BUTTON_ITEM_LINE_DELETE			0
#define INDEX_BUTTON_ITEM_LINE_COLOR			2
#define INDEX_BUTTON_ITEM_LINE_COLOR_DEMO		3
#define INDEX_BUTTON_ITEM_LINE_SIZE				5
#define INDEX_BUTTON_ITEM_LINE_SIZE_DEMO		6

// wangpp 2012.2.29 start
// freehand transparent
#define INDEX_BUTTON_ITEM_LINE_TRANSPARENT      8
// wangpp 2012.2.29 end

// wangpp 2012.4.12 start
// login
#define INDEX_BUTTON_ITEM_LINE_REGIST			10
// wangpp 2012.4.12 end

#define INDEX_BUTTON_ITEM_NOTE_DELETE			0
#define INDEX_BUTTON_ITEM_NOTE_COLOR			2
#define INDEX_BUTTON_ITEM_NOTE_COLOR_DEMO		3
#define INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR		5
#define INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR_DEMO	6
#define INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE		8
#define INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE_DEMO	9

// wangpp 2012.4.12 start
// login
#define INDEX_BUTTON_ITEM_NOTE_TEXT_REGIST		11

#define INDEX_BUTTON_ITEM_NORMAL_REGIST			3
// wangpp 2012.4.12 end

// wangpp 2012.3.29 start
// logIn
#define INDEX_BUTTON_ITEM_LOGIN_DELETE			0
#define INDEX_BUTTON_ITEM_LOGIN_SELECT          2
// wangpp 2012.3.29 end

/*
#define INDEX_BUTTON_ITEM_SELECT_DELETE			2

#define INDEX_BUTTON_ITEM_LINE_COLOR			2
#define INDEX_BUTTON_ITEM_LINE_COLOR_DEMO		3
#define INDEX_BUTTON_ITEM_LINE_SIZE				5
#define INDEX_BUTTON_ITEM_LINE_SIZE_DEMO		6
#define INDEX_BUTTON_ITEM_LINE_DELETE			8

#define INDEX_BUTTON_ITEM_NOTE_COLOR			2
#define INDEX_BUTTON_ITEM_NOTE_COLOR_DEMO		3
#define INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR		5
#define INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR_DEMO	6
#define INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE		8
#define INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE_DEMO	9
#define INDEX_BUTTON_ITEM_NOTE_DELETE			11
 */

// wangpp 2012.3.28 start
//const long ANTYPE_LOGIN = 10000;
// wangpp 2012.3.28 end

// DWBorderView
// -----------------------------------------
@implementation DWBorderView
@synthesize contentColor = contentColor_;
@synthesize frameColor = frameColor_;

- (id) initWithColor:(UIColor*)color
{
	if ((self = [super initWithFrame:RECT_ANNOTATIONTOOLBAR_DEMOVIEW]))
	{
		self.frameColor = [UIColor lightGrayColor];
		self.contentColor = color;
	}
	
	return self;
}

- (void)addAction:(SEL)action target:(id)target
{
	UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
	button.showsTouchWhenHighlighted = YES;

	[button setFrame:self.frame];
	[button addTarget:target
			   action:action
	 forControlEvents:UIControlEventTouchUpInside];
	
	[self addSubview:button];
}

- (void)drawRect:(CGRect)rect
{
    CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextAddRect(context, CGRectMake(1, 1, rect.size.width - 2, rect.size.height - 2));
	CGContextSetStrokeColorWithColor(context, frameColor_.CGColor);
	CGContextSetLineWidth(context, 2);
	CGContextStrokePath(context);
	
	CGRect innerRect = CGRectMake(2, 2, rect.size.width - 4, rect.size.height - 4);	
	if (!CGRectIsEmpty(innerRect)) 
	{
		CGContextAddRect(context, innerRect);
		CGContextSetFillColorWithColor(context, self.contentColor.CGColor);
		CGContextDrawPath(context, kCGPathFill);
	}
}

- (void)dealloc
{
    self.contentColor = nil;
	self.frameColor = nil;
    [super dealloc];
}

@end


@implementation DWSizeButton

- (void)addAction:(SEL)action target:(id)target
{
	self.showsTouchWhenHighlighted = YES;
	[self setFrame:RECT_ANNOTATIONTOOLBAR_DEMOVIEW];

	[self addTarget:target
			 action:action
   forControlEvents:UIControlEventTouchUpInside];
}

- (void) setTextColor:(UIColor*)color
{
	[self setTitleColor:color
			   forState:UIControlStateNormal];
//	self.titleLabel.backgroundColor = TEXTLABEL_BACKGROUNDCOLOR_ANNOTATIONTOOLBAR_DEMOVIEW_;
}

- (void)setSize:(int)size
{
	[self setTitle:[NSString stringWithFormat:@"%d", size]
		  forState:UIControlStateNormal];
	[self setContentHorizontalAlignment:UIControlContentHorizontalAlignmentLeft];
}

- (void)dealloc
{
    [super dealloc];
}

@end

// DocumentEditController
// ------------------------------------------------
@implementation DocumentEditController

@synthesize dwAnnoInfo = dwAnnoInfo_;
@synthesize dwInputToolbar = dwInputToolbar_;
@synthesize dwInputField = dwInputField_;
@synthesize dwFreehandGhostView;
@synthesize freehandColor = freehandColor_;
@synthesize freehandLineSize = freehandLineSize_;

// wangpp 2012.2.28 start
// freehand transparent
@synthesize freehandTransparent = freehandTransparent_;
// wangpp 2012.2.28 end

@synthesize textNotepadColor = textNotepadColor_;
@synthesize textNotepadFontColor = textNotepadFontColor_;
@synthesize textNotepadFontSize = textNotepadFontSize_;
@synthesize pageView_;
@synthesize dwFinishToolbar = dwFinishToolbar_;

// wangpp 2012.4.13 start
// login
@synthesize   loginAnnoIndex = loginAnnoIndex_;
// wangpp 2012.4.13 end

@synthesize dwAnnPropertyNavController;
@synthesize dwAnnPropertyPopController;
@synthesize editMode;


#pragma mark -
#pragma mark init controller and view.

// AR19008
// 2012.02.20 M.Chikyu start.
/*
- (id) initWithPageViewManager:(PageViewManager*)mgr
                 withPageIndex:(int)pageIndex 
                 withPageScale:(long)scale
                withPageOffset:(CGPoint)offset
 */

- (id) initWithPageViewManager:(PageViewManager*)mgr
                 withPageIndex:(int)pageIndex 
                 withPageScale:(long)scale
                withPageOffset:(CGPoint)offset
			   withOrientation:(UIInterfaceOrientation)orientation;
// 2012.02.20 M.Chikyu end.
{
    if (self = [super init])
	{
        if (mgr != nil)
		{
            pageViewManager_ = mgr;
            
            if (pageViewManager_.handleDocument != NULL)
			{
                pageEditManager_ = [[PageEditManager alloc]initWithDocumentHandle:pageViewManager_.handleDocument 
                                                                     withDWDrawer:pageViewManager_.dwDrawer];
                
                if (pageEditManager_ == nil)
				{
                    return nil;
                }
            }
            
			applicationDelegate_ = (DWViewerAppDelegate*)[[UIApplication sharedApplication] delegate];

			// AR19008
			// 2012.02.20 M.Chikyu start.
			/*
			pageEditManager_.interfaceOrientation = self.interfaceOrientation;
			 */

			pageEditManager_.interfaceOrientation = orientation;
			// 2012.02.20 M.Chikyu end.
            
            pageIndex_ = pageIndex;
            
            // page status
            pageScale = scale;
			if (pageViewManager_.facingMode == MODE_REGULAR)
			{
				pageOffset = offset;
			}
			else
			{
                if ([self UIDeviceIsPortrait] == YES)
				{
                    pageOffset = offset;
                }
				else
				{
                    pageOffset = CGPointZero;
                }
			}

			// init property default value.
			self.freehandColor	= applicationDelegate_.freehandSettingColor;
			freehandLineSize_	= applicationDelegate_.freehandSettingLineSize;

			// wangpp 2012.2.28 start
            // freehand transparent
            self.freehandTransparent = applicationDelegate_.freehandSettingTransparent;
            // wangpp 2012.2.28 end
			
			self.textNotepadColor		= applicationDelegate_.textNotepadSettingColor;
			self.textNotepadFontColor	= applicationDelegate_.textNotepadSettingFontColor;
			textNotepadFontSize_		= applicationDelegate_.textNotepadSettingFontSize;
			
            isDrawFreehandLine = NO;
            
            popIndex = -1;
        }

		// AR19008
		// 2012.02.20 M.Chikyu start.
		orientation_ = orientation;
		// 2012.02.20 M.Chikyu end.
		
		// wangpp 2012.4.13 start
		// login
		loginAnnoCount_ = 0;
		// wangpp 2012.4.13 end
	}
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    isDeviceIsiPad = Utility::UIDeviceIsiPad();
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	editMode = kTopMenu;

	// サイズ表示の文字色を決定
	if (isDeviceIsiPad == YES)
	{
		dwSizeButtonColor = TEXTLABEL_TEXTCOLOR_ANNOTATIONTOOLBAR_DEMOVIEW_IPAD;
	}
	else
	{
		dwSizeButtonColor = TEXTLABEL_TEXTCOLOR_ANNOTATIONTOOLBAR_DEMOVIEW_IPHONE;
	}

	fontSizeLabelWidth = RECT_ANNOTATIONTOOLBAR_DEMOVIEW.size.width;
	// 2012.02.01(Ver2.1 New) M.Chikyu
    
    // 1. set bar status.
    if (!isDeviceIsiPad)
	{
		[[UIApplication sharedApplication] setStatusBarHidden:YES 
                                                withAnimation:UIStatusBarAnimationNone];
	}
	
    self.navigationController.toolbar.barStyle		= UIBarStyleBlackOpaque;
    self.navigationController.navigationBar.hidden	= YES;
	self.navigationController.toolbar.hidden		= YES;
    
    // 2. init toolbar items.
    //.....
    
	// 3. init controller controls.

    // 3.1 init single tap gesuture.
    singleTapGestureRecognizer
	= [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(actionOnSingleTapGesture:)];

    [singleTapGestureRecognizer setDelaysTouchesBegan:YES];
    [singleTapGestureRecognizer setNumberOfTapsRequired:1];


    // 3.4
	NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];

	[notificationCenter addObserver:self 
                           selector:@selector(actionOnKeyboardDidShow:) 
                               name:UIKeyboardWillShowNotification
                             object:nil];

    // 3.5
	longPressTapGestureRecognizer
	= [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(actionOnLongPressGesture:)];

	[longPressTapGestureRecognizer setMinimumPressDuration:1.5];
    
    // 3.6
	panGestureRecognizer
	= [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(actionOnFlipDragGesture:)];

	[panGestureRecognizer setMaximumNumberOfTouches:1];

	// 3.7
	pinchGestureRecognizer
	= [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(actionOnPinchGesture:)];
	
    self.dwInputToolbar = [[UIToolbar alloc]init];
    dwInputToolbar_.barStyle = UIBarStyleDefault;
    
    // finish toolbar...
	dwFinishToolbar_ = [[UIToolbar alloc] init];
	dwFinishToolbar_.barStyle = UIBarStyleBlack;
    
	UIBarButtonItem* commitButtonItem
	= [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
													target:self
													action:@selector(exitAddTextNotepadAnnotation:)];

	UIBarButtonItem* flexSpace
	= [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
													 target:self
													 action:nil] autorelease];

	NSMutableArray* commitToolbarItem = [[NSMutableArray alloc] init];

	[commitToolbarItem addObject:flexSpace];
	[commitToolbarItem addObject:commitButtonItem];

	dwFinishToolbar_.items = commitToolbarItem;
	[commitToolbarItem release];

	// 2.1 init nomal items
	self.dwInputField = [[UITextView alloc]init];

	dwInputField_.textColor				= [UIColor blackColor];
	dwInputField_.backgroundColor		= [UIColor whiteColor];
	dwInputField_.layer.cornerRadius	= 6;
	dwInputField_.layer.masksToBounds	= YES;
	dwInputField_.delegate				= self;
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	dwInputField_.font = [UIFont systemFontOfSize:17.0];
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// 3.3 add gesture recognizer to background view.
	[self.view addGestureRecognizer:singleTapGestureRecognizer];
	[self.view addGestureRecognizer:longPressTapGestureRecognizer];
	[self.view addGestureRecognizer:pinchGestureRecognizer];

	/*
	// 4. init edit page view.
	self.pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_];
	[self.view addSubview:pageView_];

	// 5. inherit page view status.
	[self inheritPageViewStatus];
	 */
	
	// 2012.02.14 M.Chikyu start.
	UIView* bgView = [[[UIView alloc]initWithFrame:[pageEditManager_ getScreenRect]]autorelease];
	bgView.backgroundColor = [UIColor grayColor];
	
	[self.view addSubview:bgView];
	// 2012.02.14 M.Chikyu end.
	
    // 6. init ghost view.
    isKeyboardShowed = NO;
	
	keyboardSize = CGSizeZero;

	// iPadのツールバーの上部に境界線を入れる の対応
	if (isDeviceIsiPad == YES)
	{
		menubarStartPositionY = MENUBAR_DARKGRAYLINE_HEIGHT_IPAD;
	}
	else
	{
		menubarStartPositionY = 0.0;
	}

	// 2012.02.01(Ver2.1 New) M.Chikyu

	activeIndicator_ = [[UIActivityIndicatorView alloc]
					   initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	isIndicatorAnimating = NO;

	if (activeIndicator_ != nil)
	{
		activeIndicator_.frame = CGRectMake(0, 0, 40, 40);

		// 2012.02.14 M.Chikyu start.
		/*
		[activeIndicator_ setBackgroundColor:[UIColor whiteColor]];
		[activeIndicator_ setAlpha:0.8];
		
		if ([activeIndicator_ respondsToSelector:@selector(color)])
		{
			activeIndicator_.color = [UIColor blackColor];
		}
		 */
		// 2012.02.14 M.Chikyu end.

		[self.view addSubview:activeIndicator_];

		[self displayIndicator];
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
}


- (void)viewWillAppear:(BOOL)animated
{
	[[UIApplication sharedApplication] setStatusBarHidden:YES];
	[self.navigationController setNavigationBarHidden:YES];
	[self.navigationController setToolbarHidden:YES];

	if (bgViewMenubar_ == nil)
	{
        [self initMenubarControls];
	}
	else
	{
		[self updateMenubarFrameForRotation];

		[pageView_.page setNeedsLayout];
		UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
		if (dwBorderView != nil)
		{
			[dwBorderView setNeedsLayout];
		}
	}
}

- (void)viewDidAppear:(BOOL)animated
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	if (pageView_ == nil)
	{
		self.pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_];
		[self.view addSubview:pageView_];
		
		[self inheritPageViewStatus];
		
		[self hideIndicator];
		
		// 2012.02.14 M.Chikyu start.
		[activeIndicator_ setBackgroundColor:[UIColor whiteColor]];
		if ([activeIndicator_ respondsToSelector:@selector(color)])
		{
			activeIndicator_.color = [UIColor blackColor];
		}
		else
		{
			if ([[UIScreen mainScreen] scale] == 2.0)
			{
				activeIndicator_.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
			}
		}
		// 2012.02.14 M.Chikyu end.
	}
	/*
	else
	{
		[pageView_.page setNeedsLayout];
	}
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu
}


- (void)viewWillDisappear:(BOOL)animated
{
	// Briefcaseと連携機能の追加
	if (self.dwAnnPropertyPopController != nil)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:NO];
	}
}


#pragma mark -
#pragma mark init method.

- (void) initMenubarControls
{    
    // 1. init menu bar items.
    // 1.1 init annotation bar.
	[self initAnnotationBarItem];    
    
    // 1.2 init normal property bar.
	[self initNormalPropertyBarItem];
	
    // 1.3 init notepad property bar.
	[self initNotepadPropertyBarItem];
    
    // 1.4 init freehand property item.
	[self initFreehandPropertyBarItem];
    
    // wangpp 2012.3.28 start
    // 1.5 init login annotation property item
    [self initLoginAnnotPropertyBarItem];
    // wangpp 2012.3.28 end
	
    // 2. init annotation bar.
    float width = [self getDeviceScreenRect].size.width;
	
	float height = self.navigationController.toolbar.frame.size.height + menubarStartPositionY;
	
    annotationbar_ = [[UIToolbar alloc] init];
	
	annotationbar_.barStyle = UIBarStyleDefault;
	
	[annotationbar_ setFrame:CGRectMake(0.0, menubarStartPositionY, width, height - menubarStartPositionY)];
	
	[annotationbar_ setItems:annotationbarItem_ animated:NO];
    
    // 3. init property bar.
    propertybar_ = [[UIToolbar alloc] init];
	
	propertybar_.barStyle = UIBarStyleDefault;
	
	[propertybar_ setFrame:CGRectMake(width, menubarStartPositionY, width, height - menubarStartPositionY)];
	
	propertybar_.items = propertybarItemNormal_;

	if (dwAnnoInfo_ != nil)
	{
		if (dwAnnoInfo_.annoType == ANTYPE_FREEHAND)
		{
			propertybar_.items = propertybarItemFreehand_;
		}
		else if (dwAnnoInfo_.annoType == ANTYPE_NOTEPAD )
		{
			propertybar_.items = propertybarItemNotepad_;
		}
	}
	else
	{
		if (editMode == kAddFreehand)
		{
			propertybar_.items = propertybarItemFreehand_;
		}
		else if (editMode == kAddNotepad)
		{
			propertybar_.items = propertybarItemNotepad_;
		}
	}
    
    // 4. init menubar bg view.
    float originX = 0.0;
    float originY = [self getDeviceScreenRect].size.height - height;
    width = [self getDeviceScreenRect].size.width;
    bgViewMenubar_ = [[UIScrollView alloc]initWithFrame:CGRectMake(originX, 
                                                                   originY, 
                                                                   width, 
                                                                   height)];
	[bgViewMenubar_ setBackgroundColor:[UIColor darkGrayColor]];
    
    bgViewMenubar_.showsHorizontalScrollIndicator	= NO;
	bgViewMenubar_.showsVerticalScrollIndicator		= NO;
	bgViewMenubar_.scrollEnabled					= NO;

	[bgViewMenubar_ setContentSize:CGSizeMake(width * 2, height)];
    [bgViewMenubar_ setContentOffset:CGPointMake(0, 0)];
    [bgViewMenubar_ addSubview:annotationbar_];
    [bgViewMenubar_ addSubview:propertybar_];

	[self.navigationController.view addSubview:bgViewMenubar_];
}


- (void) initAnnotationBarItem
{
    annotationbarItem_ = [[NSMutableArray alloc] init];
    
    // 1. init edit button item.
    UIBarButtonItem* editButtonItem = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
                                                                                   target:self 
                                                                                   action:@selector(actionOnTouchDoneButton)];
	
    // 2. init freehand button item.
	UIBarButtonItem* freehandButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFreehandButtonIcon]]
																		   style:UIBarButtonItemStylePlain 
																		  target:self 
																		  action:@selector(actionOnTouchFreeHandButton)];
	// 3. init notepad button item.
	UIBarButtonItem* notepadButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getTextNotepadButtonIcon]]
																		  style:UIBarButtonItemStylePlain 
																		 target:self 
																		 action:@selector(actionOnTouchNotepadButton)];
	
    // 4. init select button item.
    // delete....
	
    // 5. init flex space button item.
	UIBarButtonItem	*flexSpace = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																			  target:self
																			  action:nil];
    // wangpp 2012.3.28 start
    // 6. init login annotation button item
    UIBarButtonItem *loginAnnButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getLoginButtonIcon]]
																		   style:UIBarButtonItemStylePlain 
																		  target:self 
																		  action:@selector(actionOnTouchLoginAnnButton)];
	loginAnnoCount_ = [DWResistAnnotationManager getResistAnnotationCount];
	if (loginAnnoCount_ == 0)
	{
		loginAnnButtonItem.enabled = NO;
	}
	else
	{
		loginAnnButtonItem.enabled = YES;
	}
    // wangpp 2012.3.28 end
    
    [annotationbarItem_ addObject:editButtonItem];

	[annotationbarItem_ addObject:flexSpace];

	[annotationbarItem_ addObject:freehandButtonItem];

	[annotationbarItem_ addObject:flexSpace];

	[annotationbarItem_ addObject:notepadButtonItem];

	[annotationbarItem_ addObject:flexSpace];
	
    // wangpp 2012.3.28 start
    [annotationbarItem_ addObject:loginAnnButtonItem];
    [annotationbarItem_ addObject:flexSpace];
    [loginAnnButtonItem release];
    // wangpp 2012.3.28 end
    
	[editButtonItem release];
    
	[freehandButtonItem release];
    
	[notepadButtonItem release];
	[flexSpace release];    
}


- (void) initNormalPropertyBarItem
{
    propertybarItemNormal_ = [[NSMutableArray alloc] init];
	
	// 1. init default button
    // 1.1 init flex space.
    UIBarButtonItem	*flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																			   target:self
																			   action:nil];
    
    // 1.2 init back button item.
	UIBarButtonItem* backButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
																					target:self 
																					action:@selector(actionOnTouchBackButton)];
	
	// 1.3 init delete button item.
	UIBarButtonItem* deleteButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]]
																		 style:UIBarButtonItemStylePlain 
																		target:self 
																		action:@selector(actionOnTouchDeleteButton)];
	
	//1.4 init resist button item
	
	// wangpp 2012.4.12 start
	// login 
	UIBarButtonItem* loginAnnButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getRegistLoginButtonIcon]]
																									style:UIBarButtonItemStylePlain 
																								   target:self 
																								   action:@selector(actionOnTouchLoginAnnoationButton)];
	// wangpp 2012.4.12 end
	
	
	// 2.1 init nomal items

	[propertybarItemNormal_ addObject:deleteButtonItem];
	
	[propertybarItemNormal_ addObject:flexSpace];
	
	// wangpp 2012.4.12 start
	// login
	[propertybarItemNormal_ addObject:loginAnnButtonItem];
	
	[propertybarItemNormal_ addObject:flexSpace];
	//// wangpp 2012.4.12 end

	[propertybarItemNormal_ addObject:backButtonItem];

	/*
	[propertybarItemNormal_ addObject:backButtonItem];
	
	[propertybarItemNormal_ addObject:flexSpace];

	[propertybarItemNormal_ addObject:deleteButtonItem];

	[propertybarItemNormal_ addObject:flexSpace];
	 */

	[flexSpace release];
	[backButtonItem release];
	[deleteButtonItem release];
	
	// wangpp 2012.4.12 start
	// login
    [loginAnnButtonItem release];
	// wangpp 2012.4.12 end
}


- (void) initNotepadPropertyBarItem
{

    propertybarItemNotepad_ = [[NSMutableArray alloc] init];
	
	// ツールバー空白ボタン
    UIBarButtonItem	*flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																			   target:self
																			   action:nil];

	// リターンボタン
	UIBarButtonItem* backButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
																					target:self 
																					action:@selector(actionOnTouchBackButton)];

	// アノテーション削除ボタン
	UIBarButtonItem* deleteButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]]
																		 style:UIBarButtonItemStylePlain 
																		target:self 
																		action:@selector(actionOnTouchDeleteButton)];
	
	// アノテーション背景色設定ボタン
	UIBarButtonItem* annBGColorButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getTextNotepadBackgroundColorButtonIcon]]
																			 style:UIBarButtonItemStylePlain
																			target:self
																			action:@selector(actionOnTouchNotepadBGColorButton)];

	// アノテーション文字色設定ボタン
	UIBarButtonItem* fontColorButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getTextNotepadFontColorButtonIcon]]
																			style:UIBarButtonItemStylePlain 
																		   target:self 
																		   action:@selector(actionOnTouchNotepadFontColorButton)];

	// アノテーション文字サイズ設定ボタン
	UIBarButtonItem* fontSizeButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getTextNotepadFontSizeButtonIcon]]
																		   style:UIBarButtonItemStylePlain 
																		  target:self 
																		  action:@selector(actionOnTouchNotepadFontSizeButton)];


	// アノテーション背景色表示ボタン
	DWBorderView* annBGColorView = [[DWBorderView alloc] initWithColor:textNotepadColor_];
	[annBGColorView addAction:@selector(actionOnTouchNotepadBGColorButton)
					   target:self];

	UIBarButtonItem* annBGColorDemoButtonItem = [[UIBarButtonItem alloc] initWithCustomView:annBGColorView];
	[annBGColorView release];


	// アノテーション文字色表示ボタン
	DWBorderView* fontColorView = [[DWBorderView alloc] initWithColor:textNotepadFontColor_];
	[fontColorView addAction:@selector(actionOnTouchNotepadFontColorButton)
					  target:self];
	
	UIBarButtonItem* fontColorDemoButtonItem = [[UIBarButtonItem alloc] initWithCustomView:fontColorView];
	[fontColorView release];

	
	// アノテーション文字サイズ表示ボタン
	DWSizeButton* fontSizeButton = [DWSizeButton buttonWithType:UIButtonTypeCustom];
	[fontSizeButton setTextColor:[pageEditManager_ transformColorRefToUIColor:dwSizeButtonColor]];
	[fontSizeButton setSize:textNotepadFontSize_];
	[fontSizeButton addAction:@selector(actionOnTouchNotepadFontSizeButton)
					   target:self];

	UIBarButtonItem* fontSizeDemoButtonItem = [[UIBarButtonItem alloc] initWithCustomView:fontSizeButton];
	
	
	// wangpp 2012.4.12 start
	// login
	UIBarButtonItem* loginAnnButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getRegistLoginButtonIcon]]
																									style:UIBarButtonItemStylePlain 
																								   target:self 
																								   action:@selector(actionOnTouchLoginAnnoationButton)];
	// wangpp 2012.4.12 end

	
	// ツールバー上にボタン配置
	[propertybarItemNotepad_ addObject:deleteButtonItem];
	
	[propertybarItemNotepad_ addObject:flexSpace];
	
	[propertybarItemNotepad_ addObject:annBGColorButtonItem];
	[propertybarItemNotepad_ addObject:annBGColorDemoButtonItem];
	
	[propertybarItemNotepad_ addObject:flexSpace];
	
	[propertybarItemNotepad_ addObject:fontColorButtonItem];
	[propertybarItemNotepad_ addObject:fontColorDemoButtonItem];
	
	[propertybarItemNotepad_ addObject:flexSpace];
	
	[propertybarItemNotepad_ addObject:fontSizeButtonItem];
	[propertybarItemNotepad_ addObject:fontSizeDemoButtonItem];
	
	// wangpp 2012.4.12 start
	// login
	
	[propertybarItemNotepad_ addObject:flexSpace];
	
	[propertybarItemNotepad_ addObject:loginAnnButtonItem];
	
	// wangpp 2012.4.12 end
    
	[propertybarItemNotepad_ addObject:flexSpace];
	
	[propertybarItemNotepad_ addObject:backButtonItem];
	
	/*
	[propertybarItemNotepad_ addObject:backButtonItem];

	[propertybarItemNotepad_ addObject:flexSpace];

	[propertybarItemNotepad_ addObject:annBGColorButtonItem];
	[propertybarItemNotepad_ addObject:annBGColorDemoButtonItem];

	[propertybarItemNotepad_ addObject:flexSpace];

	[propertybarItemNotepad_ addObject:fontColorButtonItem];
	[propertybarItemNotepad_ addObject:fontColorDemoButtonItem];

	[propertybarItemNotepad_ addObject:flexSpace];

	[propertybarItemNotepad_ addObject:fontSizeButtonItem];
	[propertybarItemNotepad_ addObject:fontSizeDemoButtonItem];
    
	[propertybarItemNotepad_ addObject:flexSpace];

	[propertybarItemNotepad_ addObject:deleteButtonItem];
	
	[propertybarItemNotepad_ addObject:flexSpace];
	 */

	
	// オブジェクト解放
	[annBGColorButtonItem release];	
	[fontColorButtonItem release];
	[fontSizeButtonItem release];	
	
	[flexSpace release];
	[backButtonItem release];
	[deleteButtonItem release];
	
	[annBGColorDemoButtonItem release];
	[fontColorDemoButtonItem release];
	[fontSizeDemoButtonItem release];
	
	// wangpp 2012.4.12 start
	// login
	
	[loginAnnButtonItem release];
	
	// wangpp 2012.4.12 end
	
	[annBGColorView setNeedsLayout];
	[fontColorView setNeedsLayout];
}


- (void) initFreehandPropertyBarItem
{
    propertybarItemFreehand_ = [[NSMutableArray alloc] init];
	
	// ツールバー空白ボタン
    UIBarButtonItem	*flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																			   target:self
																			   action:nil];
    
	// リターンボタン
	UIBarButtonItem* backButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
																					target:self 
																					action:@selector(actionOnTouchBackButton)];
	
	// アノテーション削除ボタン
	UIBarButtonItem* deleteButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]]
																		 style:UIBarButtonItemStylePlain 
																		target:self 
																		action:@selector(actionOnTouchDeleteButton)];

	// フリーハンド線色設定ボタン
	UIBarButtonItem* freehandColorButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFreehandColorButtonIcon]]
																				style:UIBarButtonItemStylePlain 
																			   target:self 
																			   action:@selector(actionOnTouchFreehandColorButton)];

	// フリーハンド線幅設定ボタン
	UIBarButtonItem* freehandLineButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFreehandLineSizeButtonIcon]]
																			   style:UIBarButtonItemStylePlain 
																			  target:self 
																			  action:@selector(actionOnTouchFreehandLineButton)];

	
	// フリーハンド線色表示ボタン
	DWBorderView* freehandColorVeiw = [[DWBorderView alloc] initWithColor:freehandColor_];
	[freehandColorVeiw addAction:@selector(actionOnTouchFreehandColorButton)
						  target:self];

	UIBarButtonItem* freehandColorDemoButtonItem = [[UIBarButtonItem alloc] initWithCustomView:freehandColorVeiw];
	[freehandColorVeiw release];

	
	// フリーハンド線幅表示ボタン
	DWSizeButton* freehandLineButton = [DWSizeButton buttonWithType:UIButtonTypeCustom];
	[freehandLineButton setTextColor:[pageEditManager_ transformColorRefToUIColor:dwSizeButtonColor]];
	[freehandLineButton setSize:freehandLineSize_];
	[freehandLineButton addAction:@selector(actionOnTouchFreehandLineButton)
						   target:self];
	
	UIBarButtonItem* freehandLineDemoButtonItem = [[UIBarButtonItem alloc] initWithCustomView:freehandLineButton];

	// wangpp 2012.2.28 start
    // freehand transparent
	UIBarButtonItem* freehandTransparentButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFreehandTransparentButtonIcon:NO]]
																			   style:UIBarButtonItemStylePlain 
																			  target:self 
																			  action:@selector(actionOnTouchFreeHandTransparentButton)];
    // wangpp 2012.2.28 end
	
	
	// wangpp 2012.4.12 start
	// login
	UIBarButtonItem* loginAnnButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getRegistLoginButtonIcon]]
																									style:UIBarButtonItemStylePlain 
																								   target:self 
																								   action:@selector(actionOnTouchLoginAnnoationButton)];
	// wangpp 2012.4.12 end
	
	// ツールバー上にボタン配置
	[propertybarItemFreehand_ addObject:deleteButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];

	[propertybarItemFreehand_ addObject:freehandColorButtonItem];
	[propertybarItemFreehand_ addObject:freehandColorDemoButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];
	
	[propertybarItemFreehand_ addObject:freehandLineButtonItem];
	[propertybarItemFreehand_ addObject:freehandLineDemoButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];
	
	// wangpp 2012.2.28 start
    // freehand transparent
    [propertybarItemFreehand_ addObject:freehandTransparentButtonItem];
    [propertybarItemFreehand_ addObject:flexSpace];
    // wangpp 2012.2.28 end
	
	// wangpp 2012.4.12 start
	// login
	
	[propertybarItemFreehand_ addObject:loginAnnButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];
	
	// wangpp 2012.4.12 end
	
	[propertybarItemFreehand_ addObject:backButtonItem];

	/*
	[propertybarItemFreehand_ addObject:backButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];
	
	[propertybarItemFreehand_ addObject:freehandColorButtonItem];
	[propertybarItemFreehand_ addObject:freehandColorDemoButtonItem];

	[propertybarItemFreehand_ addObject:flexSpace];

	[propertybarItemFreehand_ addObject:freehandLineButtonItem];
	[propertybarItemFreehand_ addObject:freehandLineDemoButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];

	[propertybarItemFreehand_ addObject:deleteButtonItem];
	
	[propertybarItemFreehand_ addObject:flexSpace];
	 */
	
	// オブジェクト解放
	[freehandColorButtonItem release];
	[freehandLineButtonItem release];	
	
	// wangpp 2012.2.28 start
    // freehand transparent
    [freehandTransparentButtonItem release];
    // wangpp 2012.2.28 end
	
	[flexSpace release];
	[backButtonItem release];
	[deleteButtonItem release];

	[freehandColorDemoButtonItem release];
	[freehandLineDemoButtonItem release];
	
	// wangpp 2012.4.12 start
	// login
	
	[loginAnnButtonItem release];
	
	// wangpp 2012.4.12 end
}

// wangpp 2012.3.28 start
- (void) initLoginAnnotPropertyBarItem
{
    propertybarItemLogin_ = [[NSMutableArray alloc] init];
	
	// ツールバー空白ボタン
    UIBarButtonItem	*flexSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																			   target:self
																			   action:nil] autorelease];
    
	// リターンボタン
	UIBarButtonItem* backButtonItem = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
																					target:self 
																					action:@selector(actionOnTouchBackButton)] autorelease];
	
	// init select button
    UIBarButtonItem *selectButtonItem = [[[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getSelectLoginAnnButtonIcon]]
																		  style:UIBarButtonItemStylePlain 
																		 target:self 
																		 action:@selector(actionOnTouchSelectLoginAnnButton)] autorelease];
	
	// アノテーション削除ボタン
	UIBarButtonItem* deleteButtonItem = [[[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]]
																		 style:UIBarButtonItemStylePlain 
																		target:self 
																		action:@selector(actionOnTouchDeleteButton)] autorelease];
    [propertybarItemLogin_ addObject:deleteButtonItem];
	
	[propertybarItemLogin_ addObject:flexSpace];
    
    [propertybarItemLogin_ addObject:selectButtonItem];
    
    [propertybarItemLogin_ addObject:flexSpace];
    
    [propertybarItemLogin_ addObject:backButtonItem];

}
// wangpp 2012.3.28 end

- (void) inheritPageViewStatus
{
	CGPoint offset = CGPointZero;

	float zoomScale = (float)pageScale / (float)pageView_.minScale;
	[pageView_ setZoomScale:zoomScale animated:NO];

	offset = [self getPageOffset];
	[pageView_ setContentOffset:offset animated:NO];
}


- (CGPoint) getPageOffset
{
	float offsetX = pageOffset.x;
	float offsetY = pageOffset.y;
	
	CGSize screenSize = [pageEditManager_ getScreenRect].size;
	CGSize pageSize = CGSizeMake(pageView_.page.frame.size.width, 
								 pageView_.page.frame.size.height);
	
	float pageWidth = pageSize.width;
	float backgroundWidth = screenSize.width;

	if (offsetX > pageWidth - backgroundWidth)
	{
		offsetX = pageWidth - backgroundWidth;
	}
	
	if (offsetX < 0.0)
	{
		offsetX = 0.0;
	}
	
	float pageHeight = pageSize.height;
	float backgroundHeight = screenSize.height;

	if (offsetY > pageHeight - backgroundHeight)
	{
		offsetY = pageHeight - backgroundHeight;
	}

	if (offsetY < 0.0)
	{
		offsetY = 0.0;
	}
	
	return CGPointMake(offsetX, offsetY);
}


#pragma mark -
#pragma mark button action.

- (void) actionOnTouchDoneButton
{
    if ([pageViewManager_ isEditingFileErrorSaved] == YES)
	{
        UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
                                                           message:NSLocalizedString(@"MSG_ANNOTATIONEDIT_ADD_FAILE", nil)
                                                          delegate:self
                                                 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                 otherButtonTitles:nil];
		alertView.tag = TAG_ALERTVIEW_EDITFAIL;
		[alertView show];
		[alertView release];
    }
	else
	{
        [self returnToDisplayModeWithSucceed:YES];
    }
}


- (void) returnToDisplayModeWithSucceed:(BOOL)succeed
{
	[self.navigationController dismissModalViewControllerAnimated:YES];

	[pageViewManager_ returnToDisplayModeOnEndEditSuccess:succeed];
}


- (void)alertView:(UIAlertView *)alertView
didDismissWithButtonIndex:(NSInteger)buttonIndex
{
	if (alertView.tag == TAG_ALERTVIEW_EDITFAIL)
	{
        // 1. clean temp file
		[pageViewManager_ cleanTempDirectory];
        
        // 2. return to display mode.
        [self returnToDisplayModeWithSucceed:NO];
	}
	
	// wangpp 2012.4.12 start
	// login
	if (alertView.tag == TAG_ALERTVIEW_PERMIT_LOGIN)
	{
		if (buttonIndex == 0) 
		{
			MPCObject* parentObj = [pageEditManager_ getMPCObjectWithPageIndex:pageIndex_];
			if (parentObj == NULL) 
			{
				return;
			}
			
			MPCObject* anoObj = [pageEditManager_ getAnnotationObjectWithParentObject:parentObj annotationIndex:self.dwAnnoInfo.annoIndex];
			if (anoObj == NULL) 
			{
				return;
			}
			
			MPCSession* session_ = [pageEditManager_ getMPCSession];
			if (session_ == NULL) 
			{
				return;
			}
			
			if ([DWResistAnnotationManager addResistAnnotationToLocal:anoObj withSession:session_] == YES)
			{
				loginAnnoCount_ = [DWResistAnnotationManager getResistAnnotationCount];
			}
		}
	}
	// wangpp 2012.4.12 end
}


- (void) actionOnTouchFreeHandButton
{
	self.freehandColor		= applicationDelegate_.freehandSettingColor;
	self.freehandLineSize	= applicationDelegate_.freehandSettingLineSize;
	
	// wangpp 2012.2.13 start
	// freehand transparent
	self.freehandTransparent = applicationDelegate_.freehandSettingTransparent;
    // wangpp 2012.2.13 end

	self.dwAnnoInfo = nil;

    /*
	UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
	if (dwBorderView != nil)
	{
		[dwBorderView removeFromSuperview];
	}

	[self exitSelectStatus];
	 */

	pageEditManager_.isZooming = NO;
	
	pageView_.scrollEnabled = NO;
	pageView_.canCancelContentTouches = NO;

	editMode = kAddFreehand;

	[self enterAddFreehandAnnotationStatus];
	[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];

	// remove gesture
	[self.view removeGestureRecognizer:singleTapGestureRecognizer];
	[self.view removeGestureRecognizer:longPressTapGestureRecognizer];

	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandColor)];
	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandLine)];
	
	// wangpp 2012.3.5 start
	// freehand transparent
	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandTransparent)];
	// wangpp 2012.3.5 end
	
	[self transformMenubar:kPropertyBar];
}


- (void) actionOnTouchNotepadButton
{
	self.textNotepadColor		= applicationDelegate_.textNotepadSettingColor;
	self.textNotepadFontColor	= applicationDelegate_.textNotepadSettingFontColor;
	self.textNotepadFontSize	= applicationDelegate_.textNotepadSettingFontSize;

	self.dwAnnoInfo = nil;

	/*
	UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
	if (dwBorderView != nil)
	{
		[dwBorderView removeFromSuperview];
	}
	
	UIButton *backExitView = (UIButton *)[self.navigationController.view viewWithTag:TAG_HIDDEN_VIEW];
    [backExitView removeFromSuperview];
	
    [self exitSelectStatus];
	 */
    
	pageEditManager_.isZooming = NO;
	
	pageView_.scrollEnabled = NO;
    pageView_.canCancelContentTouches = NO;

	editMode = kAddNotepad;
    
	[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];

	[self.view addGestureRecognizer:panGestureRecognizer];
	
	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kNotepadColor)];
	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontColor)];
	[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontSize)];

	[self transformMenubar:kPropertyBar];
}

// wangpp 2012.3.26 start
- (void) actionOnTouchLoginAnnButton
{
    self.dwAnnoInfo = nil;
    
	pageEditManager_.isZooming = NO;
	pageView_.scrollEnabled = NO;
    pageView_.canCancelContentTouches = NO;
    
    editMode = kAddLogin;
    
    // yangjx 2012.4.18 start
    [self.view addGestureRecognizer:panGestureRecognizer];
    // yangjx 2012.4.18 end
    
    [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_LOGIN];
    
    [self transformMenubar:kPropertyBar];
}
// wangpp 2012.3.26 end

- (void) actionOnTouchBackButton
{
	[dwAnnPropertyPopController dismissPopoverAnimated:YES];
	
	[self removeAllGhostViews];

	if (editMode == kAddFreehand)
	{
		[self.view addGestureRecognizer:singleTapGestureRecognizer];
		[self.view addGestureRecognizer:longPressTapGestureRecognizer];

		if (isDrawFreehandLine == YES)
		{
			[self resizePageView];
		}
		
		isDrawFreehandLine = NO;
	}
	
    // yangjx 2012.4.18 start
    /*old
	if (editMode == kAddNotepad)
     */
    if (editMode == kAddNotepad || editMode == kAddLogin)
    // yangjx 2012.4.18 end    
	{
		[self.view removeGestureRecognizer:panGestureRecognizer];
	}
   

    pageView_.canCancelContentTouches = YES;
	self.dwAnnoInfo = nil;

	editMode = kTopMenu;
	pageEditManager_.isZooming = YES;
    
    pageView_.scrollEnabled = YES;
    
    [self transformMenubar:kAnnotationBar];
}


- (void) actionOnTouchDeleteButton
{
    [dwAnnPropertyPopController dismissPopoverAnimated:YES];
	
    if (dwAnnoInfo_ != nil)
	{
		CGSize oriPageSize = [self getCurrentPageSize];
		
		BOOL res = [pageEditManager_ deleteAnnotationWithAnnotationInfo:dwAnnoInfo_];
		
		CGSize newPageSize = [self getCurrentPageSize];

		if (res == YES)
		{
			[pageEditManager_.annoRectList removeObjectAtIndex:dwAnnoInfo_.annoIndex];
		}

		if (oriPageSize.width  != newPageSize.width ||
			oriPageSize.height != newPageSize.height)
		{
			[self resizePageView];
		}
		else
		{
			[self refreshPageView];
		}

        [self transformMenubar:kAnnotationBar];
		
        self.dwAnnoInfo = nil;

		// 2012.02.01(Ver2.1 New) M.Chikyu
		editMode = kTopMenu;
		pageEditManager_.isZooming = YES;
		// 2012.02.01(Ver2.1 New) M.Chikyu
		
		pageView_.scrollEnabled = YES;
    }
}

// wangpp 2012.4.12 start
// login
- (void) actionOnTouchLoginAnnoationButton
{	
	int loginAnnoCount = loginAnnoCount = [DWResistAnnotationManager getResistAnnotationCount];
	
	if (loginAnnoCount >= LOCAL_RESIST_ANNOTATION_COUNT) 
	{
		UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
															message:NSLocalizedString(@"MSG_WARING_REGIST_ANN_NO", nil) 
														   delegate:nil 
												  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
												  otherButtonTitles:nil, (char*)nil];
		[alertView show];
		[alertView release];
	}
	else
	{
		UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
															message:NSLocalizedString(@"MSG_WARING_LOGIN_ANNOTATION", nil) 
														   delegate:self 
												  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES", nil) 
												  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil), (char*)nil];
		
		alertView.tag = TAG_ALERTVIEW_PERMIT_LOGIN;
		
		[alertView show];
		[alertView release];
	}
}

- (void) actionOnTouchSelectLoginAnnButton
{
	if (popIndex != -1) 
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}
	
	if (popIndex == INDEX_BUTTON_ITEM_LOGIN_SELECT) 
	{
		popIndex = -1;
		return;
	}

	if (isDeviceIsiPad == NO) 
	{
		DWLoginAnnPropertySettingsController *loginAnnViewController = [[DWLoginAnnPropertySettingsController alloc]
																		initWithActionType:kLoginActionRead
																		andOrientation:self.interfaceOrientation];
		loginAnnViewController.loginAnnIndex = applicationDelegate_.loginSetingIndex;
		loginAnnViewController.delegate = self;
		
		self.dwAnnPropertyNavController = [[[UINavigationController alloc] initWithRootViewController:loginAnnViewController] autorelease];
		[self.navigationController presentModalViewController:self.dwAnnPropertyNavController animated:YES];
		
		[loginAnnViewController release];
	}
	else
	{
		DWLoginAnnPropertySettingsController* loginAnnViewController = [[DWLoginAnnPropertySettingsController alloc]
																		initWithActionType:kLoginActionRead
																		andOrientation:self.interfaceOrientation];
		loginAnnViewController.loginAnnIndex = applicationDelegate_.loginSetingIndex;
		loginAnnViewController.delegate = self;

		self.dwAnnPropertyPopController = [[[UIPopoverController alloc] initWithContentViewController:loginAnnViewController] autorelease];
		self.dwAnnPropertyPopController.popoverContentSize = loginAnnViewController.tableView.frame.size;
		self.dwAnnPropertyPopController.delegate = self;
		
	    [loginAnnViewController release];
		
		if ([propertybarItemLogin_ count] > INDEX_BUTTON_ITEM_LOGIN_SELECT) 
		{
			UIBarButtonItem* selectButtonItem = (UIBarButtonItem*)[propertybarItemLogin_ objectAtIndex:INDEX_BUTTON_ITEM_LOGIN_SELECT];
			
			if (selectButtonItem != nil) 
			{
				[self.dwAnnPropertyPopController presentPopoverFromBarButtonItem:selectButtonItem 
														permittedArrowDirections:UIPopoverArrowDirectionDown
																		animated:YES];
			}
			
			popIndex = INDEX_BUTTON_ITEM_LOGIN_SELECT;
		}		
	}
}
// wangpp 2012.4.12 end

- (void) actionOnTouchFreehandColorButton
{
	// 表示中のプロパティがあれば消去
	// (popIndexは現在表示中のメニューの位置。非表示なら-1。)
	if (popIndex != -1)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}

	// 表示中のプロパティのボタンが再度押されたのであればプロパティを消して終了
	if (popIndex == INDEX_BUTTON_ITEM_LINE_COLOR)
	{
        popIndex = -1;
        return;
    }

    // 押されたボタンに対応するプロパティを表示
    [self OpenFreehandAnnotationPropertySettingsView:(Utility::kFreehandColor)];
}


- (void) actionOnTouchFreehandLineButton
{
	// 表示中のプロパティがあれば消去
	// (popIndexは現在表示中のメニューの位置。非表示なら-1。)
	if (popIndex != -1)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}

	// 表示中のプロパティのボタンが再度押されたのであればプロパティを消して終了
	if (popIndex == INDEX_BUTTON_ITEM_LINE_SIZE)
	{
		popIndex = -1;
		return;
	}

    // 押されたボタンに対応するプロパティを表示
    [self OpenFreehandAnnotationPropertySettingsView:(Utility::kFreehandLine)];
}

// wangpp 2012.2.28 start
// freehand transparent
- (void) actionOnTouchFreeHandTransparentButton
{
    if (popIndex != -1) 
	{
        [self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
    }
	
	if (popIndex == INDEX_BUTTON_ITEM_LINE_TRANSPARENT)
	{
		popIndex = -1;
		return;
	}
	
	[self OpenFreehandAnnotationPropertySettingsView:(Utility::kFreehandTransparent)];
}
// wangpp 2012.2.28 end

- (void) actionOnTouchNotepadBGColorButton
{
	// 表示中のプロパティがあれば消去
	// (popIndexは現在表示中のメニューの位置。非表示なら-1。)
	if (popIndex != -1)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}

	// 表示中のプロパティのボタンが再度押されたのであればプロパティを消して終了
	if (popIndex == INDEX_BUTTON_ITEM_NOTE_COLOR)
	{
		popIndex = -1;
		return;
	}

    // 押されたボタンに対応するプロパティを表示
    [self OpenTextNotepadAnnotationPropertySettingsView:(Utility::kNotepadColor)];
}


- (void) actionOnTouchNotepadFontColorButton
{
	// 表示中のプロパティがあれば消去
	// (popIndexは現在表示中のメニューの位置。非表示なら-1。)
	if (popIndex != -1)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}

	// 表示中のプロパティのボタンが再度押されたのであればプロパティを消して終了
	if (popIndex == INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR)
	{
		popIndex = -1;
		return;
	}
      
    // 押されたボタンに対応するプロパティを表示
    [self OpenTextNotepadAnnotationPropertySettingsView:(Utility::kTextFontColor)];
}


- (void) actionOnTouchNotepadFontSizeButton
{
	// 表示中のプロパティがあれば消去
	// (popIndexは現在表示中のメニューの位置。非表示なら-1。)
	if (popIndex != -1)
	{
		[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	}

	// 表示中のプロパティのボタンが再度押されたのであればプロパティを消して終了
	if (popIndex == INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE)
	{
		popIndex = -1;
		return;
	}
     
    // 押されたボタンに対応するプロパティを表示
    [self OpenTextNotepadAnnotationPropertySettingsView:(Utility::kTextFontSize)];
}


- (void) actionOnSingleTapGesture:(UIGestureRecognizer *)gestureRecognizer 
{
    CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];
    [self processEventWithTouchPoint:touchPoint];
}


- (void) actionOnFlipDragGesture:(UIPanGestureRecognizer *)gestureRecognizer 
{
	CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];

	if (editMode == kAddNotepad)
	{
        
        CGRect shadowRect = [self getNewTextNotepadAnnotationRectWithTouchPoint:touchPoint];
        
        if (isKeyboardShowed == NO)
		{
            if (CGRectIntersectsRect(pageView_.page.m_PageInfoA.m_SrcRect, shadowRect) == YES)
			{
                [self enterAddTextNotePadAnnotationWithFrame:shadowRect];
            }
			else
			{
                UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
                if (dwBorderView != nil)
				{
                    [dwBorderView removeFromSuperview];
                }
            }

			if ([gestureRecognizer state] == UIGestureRecognizerStateEnded)
            {
                [self processEventWithTouchPoint:touchPoint];
            }
        }
    }
    // yangjx 2012.4.18 start
    else if (editMode == kAddLogin)
    {
        if ([gestureRecognizer state] == UIGestureRecognizerStateEnded)
        {
            [self processEventWithTouchPoint:touchPoint];
        }
    }
    // yangjx 2012.4.18 end
	else
	{
        [self processEventWithTouchPoint:touchPoint];
    }
}


- (void) actionOnLongPressGesture:(UILongPressGestureRecognizer *)gestureRecognizer 
{
    if (editMode == kSelAnnote ||
		editMode == kTopMenu)
	{
        return;
	}
    
	if ([gestureRecognizer state] == UIGestureRecognizerStateBegan)
	{
		CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];
		[self processEventWithTouchPoint:touchPoint];
	}
}

// 2012.02.01(Ver2.1 New) M.Chikyu
/*
- (void) actionOnDoubleTapGesture:(UIGestureRecognizer *)gestureRecognizer 
{
	[dwAnnPropertyPopController dismissPopoverAnimated:YES];
	
	if (editMode == kAddNotepad)
	{
		CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];
		[self processEventWithTouchPoint:touchPoint];
	}
	
	if (editMode == kEditMode)
	{
		// if touch text notepad annotation, edit text
		CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];
		DWAnnotationInfo* dwInfo = [self isTappedOnAnnotationWithTouchPoint:touchPoint];
		if (dwInfo != nil && dwInfo.annoType == ANTYPE_NOTEPAD)
		{
			if (isDeviceIsiPad == NO)
			{
				[self.view removeGestureRecognizer:panGestureRecognizer];
			}
			
			[pageEditManager_ getAnnotationInfo:dwInfo];
            
			DWTextNotepadAnnotationInfo* textNotepadAnnInfo = (DWTextNotepadAnnotationInfo*)dwInfo;
            
            int textLenght = [self getOutputTextCountWithInputText:textNotepadAnnInfo.textContent];
            if ((textNotepadAnnInfo.textAnnotCount == 0 || 
                 textNotepadAnnInfo.textAnnotCount == 1) &&
                (textLenght <= MAX_ALL_TEXT_COUNT))
			{
                textNotepadAnnInfo.isUpdateText = YES;
				[self enterSelectStatusWithAnnotationInfo:dwInfo];
				
				DWAnnShadowGhostView *dwShadowView = (DWAnnShadowGhostView *)[pageView_.page viewWithTag:TAG_SHADOW_VIEW];
				[dwShadowView removeFromSuperview];
				
				DWTextNotepadAnnotationInfo* textNotepadInfo = (DWTextNotepadAnnotationInfo*)dwInfo;
				if (textNotepadInfo.textContent != nil)
				{
                    NSString* text = [self formatTextAnnotationContentWithTextOutput:textNotepadInfo.textContent];
					if (text == nil)
					{
						dwInputField_.text = @"";
					}
					else
					{
						dwInputField_.text = text;
						if ([dwInputField_.text length] >= MAX_ALL_TEXT_COUNT)
						{
							//dwInputField_.editable = NO;
						}
					}
				}
				else
				{
                    dwInputField_.text = @"";
                }
				
                [self showTextNotepadAnnotationInputView];			
			}
		}
	}
}
 */
// 2012.02.01(Ver2.1 New) M.Chikyu


- (void) actionOnTwoFingerTapGesture:(UIGestureRecognizer *)gestureRecognizer 
{
	if (editMode == kAddNotepad)
	{
		CGPoint oneTouchPoint = [gestureRecognizer locationOfTouch:0 inView:pageView_.page];
		CGPoint twoTouchPoint = [gestureRecognizer locationOfTouch:1 inView:pageView_.page];
		
		CGPoint textNotePadAddPosition = CGPointZero;
		if (oneTouchPoint.x < twoTouchPoint.x)
		{
			textNotePadAddPosition = oneTouchPoint;
		}
		else
		{
			textNotePadAddPosition = twoTouchPoint;
		}
		
		[self processEventWithTouchPoint:textNotePadAddPosition];

		return;
	}
    
	[dwAnnPropertyPopController dismissPopoverAnimated:YES];
	CGPoint touchPoint = [gestureRecognizer locationInView:pageView_.page];
	[pageEditManager_ zoomOutPageWithPoint:touchPoint];
}


- (void) actionOnPinchGesture:(UIPinchGestureRecognizer *)gestureRecognizer
{
    // yangx 2012.4.18 start
    /*old
	if (editMode == kAddNotepad)
     */
    if (editMode == kAddNotepad || editMode == kAddLogin) 
    // yangjx 2012.4.18 end    
	{
		if (gestureRecognizer.state == UIGestureRecognizerStateEnded)
		{
			CGPoint textNotePadAddPosition = [gestureRecognizer locationOfTouch:0
																		 inView:pageView_.page];
			[self processEventWithTouchPoint:textNotePadAddPosition];
		}
	}
}


- (DWAnnotationInfo*) isTappedOnAnnotationWithTouchPoint:(CGPoint)point
{
    self.dwAnnoInfo = nil;
    
	int index = -1;
    CGRect rect;
    CGPoint tapPoint = point;

	int count = pageEditManager_.annoRectList.count;
	
	for (int i = count - 1; i >= 0; i--)
	{
        rect = [[pageEditManager_.annoRectList objectAtIndex:i] CGRectValue];

        if (CGRectContainsPoint(rect, tapPoint))
		{
            index = i;
			
			MP_ObjectType type = [pageEditManager_ getAnnotationTypeWithAnnotationIndex:index];

			if (type == ANTYPE_FREEHAND)
			{
				self.dwAnnoInfo = [[[DWFreehandAnnotationInfo alloc]init] autorelease];

				dwAnnoInfo_.annoType	= type;
				dwAnnoInfo_.pageIndex	= pageIndex_;
				dwAnnoInfo_.annoIndex	= index;
				dwAnnoInfo_.annoRect	= rect;

				[pageEditManager_ getAnnotationInfo:dwAnnoInfo_];
				
				DWFreehandAnnotationInfo *dwAnnotInfo = (DWFreehandAnnotationInfo *)dwAnnoInfo_;

				NSInteger coun = [dwAnnotInfo.linePoints count];

				for (int i = 0 ; i < coun; i++)
				{
					CGPoint pt = [[dwAnnotInfo.linePoints objectAtIndex:i] CGPointValue];
					float distancex = (pt.x - tapPoint.x) * (pt.x - tapPoint.x);
					float distancey = (pt.y - tapPoint.y) * (pt.y - tapPoint.y);

					if (distancex < 100 && distancey < 100)
					{
						return dwAnnoInfo_;
					}
				}
                
                index = -1;
                continue;
			} 
            else 
            {
				break;
			}
		}
    }
    
	if (index != -1)
	{
        MP_ObjectType type = [pageEditManager_ getAnnotationTypeWithAnnotationIndex:index];
		
		switch (type)
		{
			case ANTYPE_TEXT:
				self.dwAnnoInfo = [[[DWTextAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_NOTEPAD:
				self.dwAnnoInfo = [[[DWTextNotepadAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_FREEHAND:
				self.dwAnnoInfo = [[[DWFreehandAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_LINE:
				self.dwAnnoInfo = [[[DWLineAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_RECTANGLE:
				self.dwAnnoInfo = [[[DWRectangleAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_ELLIPSE:
				self.dwAnnoInfo = [[[DWEllipseAnnotationInfo alloc]init] autorelease];
				break;
				
			case ANTYPE_POLYGON:
				self.dwAnnoInfo = [[[DWPolygonAnnotationInfo alloc]init] autorelease];
				break;
				
			default:
				self.dwAnnoInfo = [[[DWAnnotationInfo alloc] init] autorelease];
				break;
		}
        
        dwAnnoInfo_.annoType	= type;
        dwAnnoInfo_.pageIndex	= pageIndex_;
        dwAnnoInfo_.annoIndex	= index;
        dwAnnoInfo_.annoRect	= rect;
		
        return dwAnnoInfo_;
	}
    
    return nil;
}


- (void) OpenFreehandAnnotationPropertySettingsView:(Utility::PROPERTY_TYPE)type;
{
    if (isDeviceIsiPad == NO)
	{
		//
		// iPhone用プロパティを表示
		//

		UIColor* color = [UIColor clearColor];
        int      size = 0;
		
		// wangpp 2012.3.5 start
		// freehand transparent
        BOOL     transparent = YES;
		// wangpp 2012.3.5 end
        
        if (editMode == kSelAnnote || editMode == kTopMenu)
		{
            color = freehandColor_;
            size = freehandLineSize_;
			
			// wangpp 2012.3.5 start
			// freehand transparent
		    transparent = freehandTransparent_;
			// wangpp 2012.3.5 end
        }
		else
		{
            color = applicationDelegate_.freehandSettingColor;
            size = applicationDelegate_.freehandSettingLineSize;
			
			// wangpp 2012.3.5 start
			// freehand transparent
			transparent = applicationDelegate_.freehandSettingTransparent;
			// wangpp 2012.3.5 end
			
        }
        
		// 2012.02.14 M.Chikyu start.
		/*
        DWFreehandAnnPropertySettingsController* controller = 
        [[DWFreehandAnnPropertySettingsController alloc]initWithLineColor:color 
                                                             withLineSize:size];
		 */
		
		// wangpp 2012.2.9 start
		// freehand transparent
		/*
        DWFreehandAnnPropertySettingsController* controller = 
        [[DWFreehandAnnPropertySettingsController alloc]initWithLineColor:color 
                                                             withLineSize:size
														  withOrientation:self.interfaceOrientation];
		// 2012.02.14 M.Chikyu end.
		 */
		DWFreehandAnnPropertySettingsController* controller = 
        [[DWFreehandAnnPropertySettingsController alloc]initWithLineColor:color 
                                                             withLineSize:size
														withIsTransparent:transparent 
														  withOrientation:self.interfaceOrientation];
		// wangpp 2012.2.9 end
		
        controller.delegate = self;

        dwAnnPropertyNavController = [[UINavigationController alloc]initWithRootViewController:controller];

		[self.navigationController presentModalViewController:dwAnnPropertyNavController
													 animated:YES];

        [controller release];
        
    }
	else
	{
		//
		// iPad用プロパティを表示
		//

		UIColor* color  = [UIColor clearColor];
        int      size   = 0;
        int      index  = 0;
		
		// wangpp 2012.3.5 start
		// freehand transparent
        BOOL     transparent = YES;
		// wangpp 2012.3.5 end

		UIPropertyType propertyType = UIPropertyTypeLineColor;

		switch (type)
		{
			case Utility::kFreehandColor:
				propertyType = UIPropertyTypeLineColor;
				index = INDEX_BUTTON_ITEM_LINE_COLOR;
				break;
				
			case Utility::kFreehandLine:
				propertyType = UIPropertyTypeLineSize;
				index = INDEX_BUTTON_ITEM_LINE_SIZE;
				break;
			
				// wangpp 2012.3.5 start
				// freehand transparent 
			case Utility::kFreehandTransparent:
				propertyType = UIPropertyTypeTransparent;
				index = INDEX_BUTTON_ITEM_LINE_TRANSPARENT;
				break;
				// wangpp 2012.3.5 end
				
			default:
				break;
		}

        switch (editMode)
		{
			case kSelAnnote:
				color	= freehandColor_;
				size	= freehandLineSize_;
				
				// wangpp 2012.3.5 start
				// freehand transparent
				transparent = freehandTransparent_;
				// wangpp 2012.3.5 end

				break;
				
			default:
				color	= applicationDelegate_.freehandSettingColor;
				size	= applicationDelegate_.freehandSettingLineSize;

				// wangpp 2012.3.5 start
				// freehand transparent
				transparent = applicationDelegate_.freehandSettingTransparent;
				// wangpp 2012.3.5 end
				
				break;
		}
        
		// wangpp 2012.3.5 start
		// freehand transparent
		/*
		 DWFreehandAnnPropertySettingsController* controller = 
		 [[DWFreehandAnnPropertySettingsController alloc]initForiPadWithPropertyType:propertyType
																	   withLineColor:freehandColor_ 
																		withLineSize:size];
		 */
		
		DWFreehandAnnPropertySettingsController* controller = 
        [[DWFreehandAnnPropertySettingsController alloc]initForiPadWithPropertyType:propertyType
                                                                      withLineColor:freehandColor_ 
                                                                       withLineSize:size
																  withIsTransparent:freehandTransparent_];
		
		// wangpp 2012.3.5 end
		
        controller.delegate = self;

		dwAnnPropertyPopController = [[UIPopoverController alloc]initWithContentViewController:controller];
		dwAnnPropertyPopController.popoverContentSize = controller.view.frame.size;
		dwAnnPropertyPopController.delegate = self;

		[controller release];
        
        propertybar_.items = propertybarItemFreehand_;

		if ([propertybarItemFreehand_ count] > index)
		{
            UIBarButtonItem *item = [propertybarItemFreehand_ objectAtIndex:index];
            if (item != nil)
			{
                [dwAnnPropertyPopController presentPopoverFromBarButtonItem:item 
                                                   permittedArrowDirections:UIPopoverArrowDirectionDown 
                                                                   animated:YES];
			}

            popIndex = index;
        }
    }    
}


- (void) OpenTextNotepadAnnotationPropertySettingsView:(Utility::PROPERTY_TYPE)type;
{
    if (isDeviceIsiPad == NO)
	{
		//
		// iPhone用プロパティを表示
		//
		
        UIColor* bgColor    = [UIColor clearColor];
        UIColor* fontColor  = [UIColor clearColor];
        int      fontSize   = 0;
        int      textConunt = 0;

		if (editMode == kSelAnnote || editMode == kTopMenu)
		{
            bgColor		= textNotepadColor_;
            fontColor	= textNotepadFontColor_;
            fontSize	= textNotepadFontSize_;

			DWTextNotepadAnnotationInfo* annInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo_;
            textConunt = annInfo.textAnnotCount;
        }
		else
		{
            bgColor		= applicationDelegate_.textNotepadSettingColor;
            fontColor	= applicationDelegate_.textNotepadSettingFontColor;
            fontSize	= applicationDelegate_.textNotepadSettingFontSize;

			isCanSetTextProp = YES;
        }
		

		// 2012.02.14 M.Chikyu start.
		/*
		DWTextNotepadAnnPropertySettingsController* controller = 
		[[DWTextNotepadAnnPropertySettingsController alloc] initWithBackgroundColor:bgColor 
																	  withTextColor:fontColor 
																	   withTextSize:fontSize 
																	  withisHasText:isCanSetTextProp
                                                                      withTextCount:textConunt];
		 */

		DWTextNotepadAnnPropertySettingsController* controller = 
		[[DWTextNotepadAnnPropertySettingsController alloc] initWithBackgroundColor:bgColor 
																	  withTextColor:fontColor 
																	   withTextSize:fontSize 
																	  withisHasText:isCanSetTextProp
                                                                      withTextCount:textConunt
																	withOrientation:self.interfaceOrientation];
		// 2012.02.14 M.Chikyu end.

        controller.delegate = self;
        
        dwAnnPropertyNavController = [[UINavigationController alloc]initWithRootViewController:controller];

		[self.navigationController presentModalViewController:dwAnnPropertyNavController
													 animated:YES];

        [controller release];
    }
	else
	{
		//
		// iPad用プロパティを表示
		//
		
        UIColor* bgColor    = [UIColor clearColor];
        UIColor* fontColor  = [UIColor clearColor];
        int      fontSize   = 0;
        int      index      = 0;
        
        UINotepadPropertyType propertyType = UINotepadPropertyTypeBackgroundColor;

		switch (type)
		{
			case Utility::kNotepadColor:
				propertyType = UINotepadPropertyTypeBackgroundColor;
				index = INDEX_BUTTON_ITEM_NOTE_COLOR;
				break;
				
			case Utility::kTextFontColor:
				propertyType = UINotepadPropertyTypeTextColor;
				index = INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR;
				break;
				
			case Utility::kTextFontSize:
				propertyType = UINotepadPropertyTypeTextSize;
				index = INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE;
				break;

			default:
				break;
		}

        switch (editMode)
		{
			case kSelAnnote:
				bgColor		= textNotepadColor_;
				fontColor	= textNotepadFontColor_;
				fontSize	= textNotepadFontSize_;

				break;
				
			default:
				bgColor		= applicationDelegate_.textNotepadSettingColor;
				fontColor	= applicationDelegate_.textNotepadSettingFontColor;
				fontSize	= applicationDelegate_.textNotepadSettingFontSize;
				
				isCanSetTextProp = YES;

				break;
		}
		
		/*
        if (editMode == kSelAnnote)
		{
            bgColor		= textNotepadColor_;
            fontColor	= textNotepadFontColor_;
            fontSize	= textNotepadFontSize_;
        }
		else
		{
            bgColor		= applicationDelegate_.textNotepadSettingColor;
            fontColor	= applicationDelegate_.textNotepadSettingFontColor;
            fontSize	= applicationDelegate_.textNotepadSettingFontSize;

			isCanSetTextProp = YES;
        }
		 */
		
        DWTextNotepadAnnPropertySettingsController* controller = 
        [[DWTextNotepadAnnPropertySettingsController alloc]initForiPadWithPropertyType:propertyType
                                                                   withBackgroundColor:bgColor
                                                                         withTextColor:fontColor 
                                                                          withTextSize:fontSize
																		 withisHasText:isCanSetTextProp];
        controller.delegate = self;
        
        dwAnnPropertyPopController = [[UIPopoverController alloc]initWithContentViewController:controller];
        dwAnnPropertyPopController.popoverContentSize = controller.view.frame.size;
        dwAnnPropertyPopController.delegate = self;
        
        [controller release];
        
        propertybar_.items = propertybarItemNotepad_;

		if ([propertybarItemNotepad_ count] > index)
		{
			UIBarButtonItem *item = [propertybarItemNotepad_ objectAtIndex:index];

			if (item != nil)
			{
				[dwAnnPropertyPopController presentPopoverFromBarButtonItem:item
												   permittedArrowDirections:UIPopoverArrowDirectionDown
																   animated:YES];
			}

            popIndex = index;
        }
    }
}


#pragma mark -
#pragma mark select annotation.

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) selectAnnotation:(DWAnnotationInfo*)dwInfo
{
	annotationIndex = dwInfo.annoIndex;
	
	switch (dwInfo.annoType)
	{
		case ANTYPE_FREEHAND:
		{
			DWFreehandAnnotationInfo* freehandAnnInfo = (DWFreehandAnnotationInfo*)dwInfo;

			self.freehandColor		= [pageEditManager_ transformColorRefToUIColor:freehandAnnInfo.lineColor];
			self.freehandLineSize	= freehandAnnInfo.lineWidth;
			
			// wangpp 2012.3.5 start
			// freehand transparent
			self.freehandTransparent = freehandAnnInfo.transparent;
			// wangpp 2012.3.5 end
			
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandColor)];
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandLine)];
			
			// wangpp 2012.3.5 start
			// freehand transparent
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandTransparent)];
			// wangpp 2012.3.5 end
			
			[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
			
			break;
		}
			
		case ANTYPE_NOTEPAD:
		{
			DWTextNotepadAnnotationInfo* textNotepadAnnInfo = (DWTextNotepadAnnotationInfo*)dwInfo;
			isCanSetTextProp = textNotepadAnnInfo.hasTextAnnotation;

			self.textNotepadColor		= [pageEditManager_ transformColorRefToUIColor:textNotepadAnnInfo.notepadColor];
			self.textNotepadFontColor	= [pageEditManager_ transformColorRefToUIColor:textNotepadAnnInfo.textFontColor];
			self.textNotepadFontSize	= textNotepadAnnInfo.textFontsize;
			
			int  textAnnotCount = textNotepadAnnInfo.textAnnotCount;
			if (textAnnotCount != 1)
			{
				self.textNotepadFontColor    = Utility::DEFAULT_FONTCOLOR_NOTEPAD;
				self.textNotepadFontSize     = Utility::DEFAULT_FONTSIZE_NOTEPAD;
			} 
			
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kNotepadColor)];
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontColor)];
			[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontSize)];
			[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];
			
			break;
		}
			
		default:
			[self udpateDeleteButtonEnabledPropertyWithAnnotationType:0];

			break;
	}
	
	[self transformMenubar:kPropertyBar];
}
// 2012.02.01(Ver2.1 New) M.Chikyu


- (void) enterSelectStatusWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
	[self udpateDeleteButtonEnabledPropertyWithAnnotationType:dwAnnoInfo.annoType];
    
	// 2012.02.01(Ver2.1 New) M.Chikyu
	[self removeAllGhostViews];
	// 2012.02.01(Ver2.1 New) M.Chikyu

	CGRect annoRect = dwAnnoInfo.annoRect;

    
	// border view.
	DWAnnBorderGhostView* dwBorderView;
	dwBorderView = [[DWAnnBorderGhostView alloc] initWithFrame:annoRect
												   borderColor:nil
													 zoomScale:[self getCurrentZoomScale]];

    dwBorderView.tag = TAG_BORDER_VIEW;

	[pageView_.page addSubview:dwBorderView];
	[dwBorderView release];

    
    // shadow view.
	DWAnnShadowGhostView* dwShadowView;
    CGRect pageRect = pageView_.page.m_PageInfoA.m_SrcRect;

	dwShadowView = [[DWAnnShadowGhostView alloc] initWithFrame:annoRect 
                                                 withPageFrame:pageRect
                                                   withIsFixed:dwAnnoInfo.isFixed];
	dwShadowView.tag = TAG_SHADOW_VIEW;
	dwShadowView.delegate = self;
	[dwShadowView setBackgroundColor:[UIColor clearColor]];

	[pageView_.page addSubview:dwShadowView];
	[dwShadowView release];
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	editMode = kSelAnnote;
	pageEditManager_.isZooming = NO;
	// 2012.02.01(Ver2.1 New) M.Chikyu
}


- (void) exitSelectStatus
{
	[self removeAllGhostViews];

	editMode = kTopMenu;
	pageEditManager_.isZooming = YES;
	pageView_.scrollEnabled = YES;
	
    [self transformMenubar:kAnnotationBar];
}


#pragma mark -
#pragma mark edit freehand annotation.

- (void) enterAddFreehandAnnotationStatus
{	
	CGRect ghostRect = [pageEditManager_ getPagePaperRect];

	dwFreehandGhostView = [[[DWFreeHandAnnGhostView alloc] initWithFrame:ghostRect] autorelease];
	dwFreehandGhostView.tag = TAG_FREEHAND_VIEW;

	dwFreehandGhostView.delegate = self;
	
	[self setLineWidthToFreehandGhostView];
    
	dwFreehandGhostView.lineUIColor = self.freehandColor;
	
	// wangpp 2012.3.5 start
	// freehand transparent
	dwFreehandGhostView.transparent  = self.freehandTransparent;
	// wangpp 2012.3.5 end
	
	[pageView_.page addSubview:dwFreehandGhostView];
}


- (void) exitAddFreehandAnnotationStatus
{
    self.dwAnnoInfo = nil;
	
    [pageEditManager_ setAnnotationRectList];
}


- (void) addNewFreehandAnnotationWithPointArray:(NSMutableArray *)points
{
	if (editMode == kAddFreehand)
	{
        DWFreehandAnnotationInfo* dwInfo = [[DWFreehandAnnotationInfo alloc]init];

		dwInfo.annoType		= ANTYPE_FREEHAND;
		dwInfo.pageIndex	= pageIndex_;
		dwInfo.annoIndex	= -1;
		dwInfo.annoRect		= CGRectZero;
		dwInfo.lineWidth	= freehandLineSize_;
		
		// wangpp 2012.2.29 start
		// freehand transparent
		dwInfo.transparent = freehandTransparent_;
		// wangpp 2012.2.29 end
		
		COLORREF colorRef;
		BOOL res = [pageEditManager_ transformUIColorToColorRef:freehandColor_  withColorRef:&colorRef];
        
		if (res == YES)
		{
			dwInfo.lineColor = colorRef;
		}
        
        [dwInfo.linePoints addObjectsFromArray:points];
        
        self.dwAnnoInfo = dwInfo;
		[dwInfo release];

		res = [pageEditManager_ addAnnotationWithAnnotationInfo:dwAnnoInfo_];
		if (res == YES)
		{
			[self exitAddFreehandAnnotationStatus];
        }
		else
		{
			UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
															   message:NSLocalizedString(@"MSG_ANNOTATIONEDIT_ADD_FAILE", nil)
															  delegate:self
													 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													 otherButtonTitles:nil, (char*)nil];
			[alertView show];
			[alertView release];
		}
    }
}


- (void) setLineWidthToFreehandGhostView
{
	long scale = pageView_.page.m_PageInfoA.m_PageFitScale;

	// 2012.01.30 M.Chikyu start.
	/*
	dwFreehandGhostView.lineWidth = Utility::MMToPixelWithScale(freehandLineSize_ * 25.4, scale);
	if (dwFreehandGhostView.lineWidth < 1)
	{
		dwFreehandGhostView.lineWidth = 1;
	}
	 */

	dwFreehandGhostView.lineWidth = Utility::MMToPixelWithScale_F(freehandLineSize_ * 25.4, scale);
	// 2012.01.30 M.Chikyu start.
}


#pragma mark -
#pragma mark edit notpad annotation.
- (void) showTextNotepadAnnotationInputView
{
    [dwInputToolbar_ addSubview:dwInputField_];
	[self.view addSubview:dwInputToolbar_];
    
	if (isDeviceIsiPad == NO)
	{
		[self.navigationController.view addSubview:dwFinishToolbar_];
		
		// 2012.02.01(Ver2.1 New) M.Chikyu
		[self.view bringSubviewToFront:activeIndicator_];
		// 2012.02.01(Ver2.1 New) M.Chikyu
	}

	[dwInputField_ becomeFirstResponder];
}


- (void) closeTextNotepadAnnotationInputView
{
    if (isKeyboardShowed == YES)
	{
		[dwFinishToolbar_ removeFromSuperview];

		[dwInputToolbar_ removeFromSuperview];
		dwInputToolbar_.frame = CGRectZero;

		[dwInputField_ resignFirstResponder];
		dwInputField_.frame = CGRectZero;
        
        isKeyboardShowed = NO;
    }
}


- (void) exitTextNotePadEdit:(id)sender
{
    [dwInputField_ resignFirstResponder];
	
	//remove backExitView
	UIButton *button = (UIButton *)[self.navigationController.view viewWithTag:TAG_HIDDEN_VIEW];
	if (button != nil)
	{
		[button removeFromSuperview];
	}
}


- (CGRect) getNotepadAnnotationRect:(DWAnnotationInfo*)info
{
    CGRect annotationRect = [pageEditManager_ getAnnotationRectWithParentObject:
                             [pageEditManager_ getMPCObjectWithPageIndex:pageIndex_] 
                                                                  withAnnoIndex:info.annoIndex];
    return annotationRect;
}


- (CGRect) getNewTextNotepadAnnotationRectWithTouchPoint:(CGPoint)point
{
	long scale = pageView_.page.m_PageInfoA.m_PageFitScale;

	float originX	= point.x;
	float originY	= point.y;

	float width		= Utility::MMToPixelWithScale(TEXTNOTEPAD_ANNOT_WIDTH,  scale) * 100;
	float height	= Utility::MMToPixelWithScale(TEXTNOTEPAD_ANNOT_HEIGHT, scale) * 100;

	CGRect shadowRect = CGRectMake(originX - width  / 2,
								   originY - height / 2,
								   width,
								   height);
    return shadowRect;
}


- (NSString *) formatTextAnnotationContentWithTextOutput:(NSString *)text
{   
    if (text == nil)
	{
        return nil;
    }
    
	NSArray* content_ = [text componentsSeparatedByString:@"\r\n"]; 
    NSMutableString *textContents = [[NSMutableString alloc] init];
	
	int location = 0;
	
	for (int i = 0 ; i < content_.count ; i++)
	{
		NSMutableString *sub = [content_ objectAtIndex:i];
        
		if ([sub isEqualToString:@""] == NO)
        {
			//
			// １行をMAX_LINE_TEXT_COUNTで複数行に分割する
			//
			
			// 追加する行数を計算
			int count_ = sub.length / MAX_LINE_TEXT_COUNT - (sub.length % MAX_LINE_TEXT_COUNT == 0 ? 1 : 0);
			
			for (int j = 0 ; j < count_; j++)
			{
				// MAX_LINE_TEXT_COUNTで文字列を分割して改行コードを追加
				location = j * MAX_LINE_TEXT_COUNT;
				NSString* line_ = [sub substringWithRange:NSMakeRange(location, MAX_LINE_TEXT_COUNT)];
				
				[textContents appendFormat:@"%@\n", line_];
			}
			
			// 最終文字列を追加
			location = count_ * MAX_LINE_TEXT_COUNT;
			NSString* line_ = [sub substringFromIndex:location];
			
			[textContents appendString:line_];
		}
		
		if (i == content_.count - 1)
		{
			break;
		}
		
		// 最終行以外には改行コードを追加
		[textContents appendString:@"\n"];
	}
	
	return [textContents autorelease];
}


- (NSString*) formatTextAnnotationContentWithTextInput:(NSString *)text
{
    if (text == nil)
	{
		return nil;
	}

	if ([text isEqualToString:@""] == YES)
	{
		return @"";
	}

	NSArray* content_ = [text componentsSeparatedByString:@"\n"]; 
    NSMutableString *textContents = [[NSMutableString alloc] init];
	
	int location = 0;
	
	for (int i = 0 ; i < content_.count ; i++)
	{
		NSMutableString *sub = [content_ objectAtIndex:i];
        
		if ([sub isEqualToString:@""] == NO)
        {
			//
			// １行をMAX_LINE_TEXT_COUNTで複数行に分割する
			//
			
			// 追加する行数を計算
			int count_ = sub.length / MAX_LINE_TEXT_COUNT - (sub.length % MAX_LINE_TEXT_COUNT == 0 ? 1 : 0);
			
			for (int j = 0 ; j < count_; j++)
			{
				// MAX_LINE_TEXT_COUNTで文字列を分割して改行コードを追加
				location = j * MAX_LINE_TEXT_COUNT;
				NSString* line_ = [sub substringWithRange:NSMakeRange(location, MAX_LINE_TEXT_COUNT)];
				
				[textContents appendFormat:@"%@\r\n", line_];
			}
			
			// 最終文字列を追加
			location = count_ * MAX_LINE_TEXT_COUNT;
			NSString* line_ = [sub substringFromIndex:location];
			
			[textContents appendString:line_];
		}
		
		if (i == content_.count - 1)
		{
			break;
		}
        
		// 最終行以外には改行コードを追加
		[textContents appendString:@"\r\n"];
    }
	
	return [textContents autorelease];
}


- (NSString*) formatTextForEditingWithTextInput:(NSString *)text
{
    if (text == nil)
	{
        return nil;
    }
    
	NSArray* content_ = [text componentsSeparatedByString:@"\n"]; 
    NSMutableString *textContents = [[NSMutableString alloc] init];
	
	int location = 0;
	
	for (int i = 0 ; i < content_.count ; i++)
	{
		NSMutableString *sub = [content_ objectAtIndex:i];
        
		if ([sub isEqualToString:@""] == NO)
        {
			//
			// １行をMAX_LINE_TEXT_COUNTで複数行に分割する
			//
			
			// 追加する行数を計算
			int count_ = sub.length / MAX_LINE_TEXT_COUNT - (sub.length % MAX_LINE_TEXT_COUNT == 0 ? 1 : 0);
			
			for (int j = 0 ; j < count_; j++)
			{
				// MAX_LINE_TEXT_COUNTで文字列を分割して改行コードを追加
				location = j * MAX_LINE_TEXT_COUNT;
				NSString* line_ = [sub substringWithRange:NSMakeRange(location, MAX_LINE_TEXT_COUNT)];
				
				[textContents appendFormat:@"%@\n", line_];
			}
			
			// 最終文字列を追加
			location = count_ * MAX_LINE_TEXT_COUNT;
			NSString* line_ = [sub substringFromIndex:location];
			
			[textContents appendString:line_];
		}
        
		if (i == content_.count - 1)
		{
			break;
		}
		
		// 最終行以外には改行コードを追加
		[textContents appendString:@"\n"];
	}
    
    return [textContents autorelease];
}


- (CGSize) getTextAnnotationCustomSize:(DWTextNotepadAnnotationInfo *)info;
{
    CGSize size_ = CGSizeZero;
    if (info == nil)
	{
		return size_;
	}
    
    CGSize tmp = CGSizeZero;
    NSArray* content_ = [info.textContent componentsSeparatedByString:@"\n"]; 

    for (int i = 0; i < content_.count; i++)
	{
        NSString *stringInOneLine = [content_ objectAtIndex:i];
        tmp = [stringInOneLine sizeWithFont:[UIFont systemFontOfSize:info.textFontsize] 
                          constrainedToSize: CGSizeMake(10000, 10000)
                              lineBreakMode:UILineBreakModeWordWrap];

        if (tmp.width > size_.width)
		{
            size_ = tmp;
        }
    }
    
    size_ = [info.textContent sizeWithFont:[UIFont systemFontOfSize:info.textFontsize] 
                               constrainedToSize: CGSizeMake(size_.width, 10000)
                                   lineBreakMode:UILineBreakModeWordWrap];
	return size_;
}


- (int) getLineCountWithInputText:(NSString *)text
{
    if (text == nil)
	{
		return 1;
	}
    
    int lineCount = 1;
    int length = [text length];

    for (int i = 0; i < length; i++)
	{
        NSString *sub = [text substringWithRange:NSMakeRange(i, 1)];
        if ([sub isEqualToString:@"\n"] == YES)
		{
            lineCount++;
        }
    }
    
    return lineCount; 
}


- (int) getTextCountWithInputText:(NSString *)text
{
    if (text == nil)
	{
        return 0;
    }
 
    int textCount = 0;
    NSArray* content_ = [text componentsSeparatedByString:@"\n"];
	
    for (int i = 0; i < content_.count; i++)
	{
        NSString *sub = [content_ objectAtIndex:i];
        if ([sub isEqualToString:@""] == YES)
		{
            continue;
        }
        
        textCount+= [sub length];
    }
    
    return textCount;
}


- (int) getOutputTextCountWithInputText:(NSString *)text
{
    if (text == nil)
	{
        return 0;
    }
    
    int textCount = 0;
    NSArray* content_ = [text componentsSeparatedByString:@"\r\n"];

	for (int i = 0; i < content_.count; i++)
	{
		NSString *sub = [content_ objectAtIndex:i];
		if ([sub isEqualToString:@""] == YES)
		{
			continue;
		}
        
        textCount += [sub length];
    }
    
    return textCount;
}


- (CGSize) getCurrentPageSize
{
    long scale = pageView_.page.m_PageInfoA.m_PageFitScale;
    CGSize pageSize = [pageEditManager_ getPageViewSize:pageIndex_
                                          withPageScale:scale
                                           withPageMode:(PageInfo::kFullMode)];
    return pageSize;
}


- (void) actionOnKeyboardDidShow:(NSNotification *)notification
{
    // 1. get keyboard rect.
    NSDictionary *dic = [notification userInfo];
	keyboardSize = [self getDeviceKeyboardSize:dic];
	
    // 2. get toolbar rect.
    CGSize screenSize = [self getDeviceScreenRect].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;

	float toolbarOriginX = 0.0;
	float toolbarOriginY = 0.0;

	float toolbarWidth  = 0.0;
	float toolbarHeight = 0.0;
    
    if (isDeviceIsiPad == NO)
	{
		toolbarWidth	= backgroundWidth;
		toolbarHeight	= backgroundHeight - keyboardSize.height - TOOLBAR_HEIGHT;
    }
	else
	{
		toolbarWidth	= backgroundWidth;
		toolbarHeight	= TEXTINPUTTOOLBAR_HEIGHT;

		toolbarOriginY	= backgroundHeight - keyboardSize.height - toolbarHeight;
    }
	
	CGRect toolbarRect = CGRectZero;
	
	if (isDeviceIsiPad == NO)
	{
		toolbarRect = CGRectMake(toolbarOriginX,
                                 toolbarOriginY + TOOLBAR_HEIGHT, 
                                 toolbarWidth, 
                                 toolbarHeight);
	}
	else
	{
		toolbarRect = CGRectMake(toolbarOriginX,
								 toolbarOriginY, 
								 toolbarWidth, 
								 toolbarHeight);
	}
    
    dwInputToolbar_.frame = toolbarRect;
    
    // 3. get field rect.
    CGRect fieldRect = CGRectMake(4.0, 
                                  4.0, 
                                  backgroundWidth - 8.0, 
                                  toolbarHeight - 8.0);
    dwInputField_.frame = fieldRect;
	
	CGRect finishToolbarRect = CGRectMake(0, 0, toolbarWidth, TOOLBAR_HEIGHT);
	dwFinishToolbar_.frame = finishToolbarRect;
	
	isKeyboardShowed = YES;
    
	CGRect backButtonRect = CGRectZero;

	backButtonRect.origin.x		= 0;
	backButtonRect.origin.y		= 0;

	backButtonRect.size.width	= dwInputToolbar_.frame.size.width;
	backButtonRect.size.height	= dwInputToolbar_.frame.origin.y + _TAG_STATUSBAR_HEIGHT_;
	
	if (isDeviceIsiPad == YES)
	{
        UIButton *backExitView = (UIButton *)[self.navigationController.view viewWithTag:TAG_HIDDEN_VIEW];

        if (backExitView == nil)
		{
			UIButton *backExitView = [[UIButton alloc] initWithFrame:backButtonRect];

			backExitView.backgroundColor = [UIColor redColor];

			[backExitView addTarget:self
							 action:@selector(exitTextNotePadEdit:) 
				   forControlEvents:UIControlEventTouchUpInside];

			backExitView.tag = TAG_HIDDEN_VIEW;
			[backExitView setBackgroundColor:[UIColor clearColor]];

			[self.navigationController.view addSubview:backExitView];
			[backExitView release];
        }
		else
		{
			backExitView.frame = backButtonRect;
        }
	}
}


#pragma mark -
#pragma mark UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)theTextField
{
    [dwInputField_ resignFirstResponder];
	return YES;
}


- (void)textViewDidEndEditing:(UITextView *)textView
{
	if (isDeviceIsiPad == NO)
	{
		return;
	}

	[self didEndEditingTextNotepadAnnotationWithPoint:notepadPosition];

	UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
	if (dwBorderView != nil)
	{
		[dwBorderView removeFromSuperview];
	}
	
	[dwInputToolbar_ removeFromSuperview];
	dwInputToolbar_.frame = CGRectZero;
	
	[dwInputField_ resignFirstResponder];
	dwInputField_.frame = CGRectZero;
	
	isKeyboardShowed = NO;
	
	
	UIButton *button = (UIButton *)[self.navigationController.view viewWithTag:TAG_HIDDEN_VIEW];
	if (button != nil)
	{
		[button removeFromSuperview];
	}

	pageView_.canCancelContentTouches = YES;
	
	// set toolbar state
	editMode = kTopMenu;
	pageEditManager_.isZooming = YES;
	pageView_.scrollEnabled = YES;
	
	[self transformMenubar:kAnnotationBar];
	
	// remove dash view
	[self removeAllGhostViews];
}


- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    
    NSMutableString* text_ = (NSMutableString* )(textView.text);

    if ([text isEqualToString:@""] == YES)
	{
        [text_ replaceCharactersInRange:range withString:text];
    }
	else
	{
        [text_ insertString:text atIndex:range.location];
    }
    
    NSString* edit_text = [self formatTextForEditingWithTextInput:text_];
    int lineCount = [self getLineCountWithInputText:edit_text];
    
	if (lineCount > MAX_LINE_COUNT)
	{
		return NO;
	}
    
    if ([self getTextCountWithInputText:edit_text] > MAX_ALL_TEXT_COUNT)
	{
        return NO;
    }
    
	return YES;
}


- (void)textViewDidChange:(UITextView *)textView
{
   
}


- (void) didEndEditingTextNotepadAnnotationWithPoint:(CGPoint)point
{
	COLORREF colorRef;
	BOOL res = NO;
	
	// set annotation info
	DWTextNotepadAnnotationInfo* dwInfo = nil;


	if (editMode == kSelAnnote)
	{
		dwInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo_;
	}

	if (editMode == kAddNotepad)
	{
		dwInfo = [[DWTextNotepadAnnotationInfo alloc] init];
		
		dwInfo.annoType = ANTYPE_NOTEPAD;
		dwInfo.pageIndex = pageIndex_;
		dwInfo.annoIndex = -1;
        
		dwInfo.annoRect = CGRectMake(point.x,
									 point.y,
									 TEXTNOTEPAD_ANNOT_WIDTH,
									 TEXTNOTEPAD_ANNOT_HEIGHT);
		
        res = [pageEditManager_ transformUIColorToColorRef:textNotepadColor_
											  withColorRef:&colorRef];
		if (res == YES)
		{
			dwInfo.notepadColor = colorRef;
		}
		
		dwInfo.textFontsize = self.textNotepadFontSize;

		res = [pageEditManager_ transformUIColorToColorRef:textNotepadFontColor_
											  withColorRef:&colorRef];
		if (res == YES)
		{
			dwInfo.textFontColor = colorRef;
		}
		
		dwInfo.isAutoResize = true;
	}


	if (self.dwInputField.text == nil)
	{
		self.dwInputField.text = @"";
	}

	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	dwInfo.textContent = [self formatTextAnnotationContentWithTextInput:self.dwInputField.text];
	dwInfo.textAnnSize = [self getTextAnnotationCustomSize:dwInfo];
	 */
	if (dwInfo.isAutoResize == YES)
	{
		dwInfo.textContent = [self formatTextAnnotationContentWithTextInput:self.dwInputField.text];
		dwInfo.textAnnSize = [self getTextAnnotationCustomSize:dwInfo];
	}
	else
	{
		dwInfo.textContent = self.dwInputField.text;
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu


	//support at ios 4.2 and later version 
	NSString *language = [UITextInputMode currentInputMode].primaryLanguage;


	if ([language isEqualToString:CHARSET_CHINA_SIMPLE]) 
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_GB2312;
		dwInfo.textFontName		= FONTNAME_CHINA_SIMPLE;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_FIXED | AnnotationParameter::TEXT_FONT_FAMILY_ROMAN;
	}
	else if ([language isEqualToString:CHARSET_JAPAN])
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_SHIFTJIS;
		dwInfo.textFontName		= FONTNAME_JAPAN;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_FIXED | AnnotationParameter::TEXT_FONT_FAMILY_MODERN;
	}
	else if ([language isEqualToString:CHARSET_CHINA_TRADITION])
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_BIG5;
		dwInfo.textFontName		= FONTNAME_CHINA_TRADITION;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_FIXED | AnnotationParameter::TEXT_FONT_FAMILY_ROMAN;
	}
	else if ([language isEqualToString:CHARSET_KOR])
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_HANGUL;
		dwInfo.textFontName		= FONTNAME_KOR;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_FIXED | AnnotationParameter::TEXT_FONT_FAMILY_MODERN;
	}
	else if ([language isEqualToString:CHARSET_THAI])
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_THAI;
		dwInfo.textFontName		= FONTNAME_THAI;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_VARIABLE | AnnotationParameter::TEXT_FONT_FAMILY_MODERN;
	}
	else if ([language isEqualToString:CHARSET_ENG] || [language isEqualToString:CHARSET_FR])
	{
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_ANSI;
		dwInfo.textFontName		= FONTNAME_ENG;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_VARIABLE | AnnotationParameter::TEXT_FONT_FAMILY_ROMAN;
	}
	else 
    {
		dwInfo.charSet			= AnnotationParameter::TEXT_FONT_CHARSET_ANSI;
		dwInfo.textFontName		= FONTNAME_ENG;
		dwInfo.pitchAndFamily	= AnnotationParameter::TEXT_FONT_PITCH_VARIABLE | AnnotationParameter::TEXT_FONT_FAMILY_ROMAN;
	}

	// 2012.02.01(Ver2.1 New) M.Chikyu
	self.dwAnnoInfo = dwInfo;

	CGSize oriPageSize = [self getCurrentPageSize];
	// 2012.02.01(Ver2.1 New) M.Chikyu

	switch (editMode)
	{
		case kSelAnnote:
			res = [pageEditManager_ updateAnnotationWithAnnotationInfo:dwAnnoInfo_];

			break;

		case kAddNotepad:
			res = [pageEditManager_ addAnnotationWithAnnotationInfo:dwAnnoInfo_];

			break;

		default:
			res = NO;

			break;
	}

	self.dwAnnoInfo = nil;
	
	if (res == NO)
	{
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
														   message:NSLocalizedString(@"MSG_ANNOTATIONEDIT_ADD_FAILE", nil)
														  delegate:self
												 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												 otherButtonTitles:nil, (char*)nil];
		[alertView show];
		[alertView release];
		
		return;
	}


	CGSize newPageSize = [self getCurrentPageSize];

	if (oriPageSize.width  != newPageSize.width ||
		oriPageSize.height != newPageSize.height)
	{
		[self resizePageView];
	}
	else
	{
		[self refreshPageView];
	}
	
	[pageEditManager_ setAnnotationRectList];
}


- (void) enterAddTextNotePadAnnotationWithFrame:(CGRect)frame
{
	pageView_.scrollEnabled = NO;

    UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
	if (dwBorderView != nil)
	{
		dwBorderView.frame = frame;
	}
	else
	{
		dwBorderView = [[DWAnnBorderGhostView alloc] initWithFrame:frame
														borderColor:nil
														 zoomScale:[self getCurrentZoomScale]];
		dwBorderView.tag = TAG_BORDER_VIEW;

		// 2012.02.13 M.Chikyu start.
		[pageView_.page addSubview:dwBorderView];
		[dwBorderView release];
		// 2012.02.13 M.Chikyu end.
	}

	// 2012.02.13 M.Chikyu start.
	/*
    [pageView_.page addSubview:dwBorderView];
	[dwBorderView release];
	 */
	// 2012.02.13 M.Chikyu end.
}


- (void) exitAddTextNotepadAnnotation:(id)sender
{
	[dwFinishToolbar_ removeFromSuperview];
	UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];

//	[dwInputField_ resignFirstResponder];
	[self didEndEditingTextNotepadAnnotationWithPoint:notepadPosition];

	[dwInputField_ resignFirstResponder];
	dwInputField_.frame = CGRectZero;

	[dwInputToolbar_ removeFromSuperview];
	dwInputToolbar_.frame = CGRectZero;

	[dwFinishToolbar_ removeFromSuperview];
	
	isKeyboardShowed = NO;

	// set toolbar state
	editMode = kTopMenu;
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	pageEditManager_.isZooming = YES;
	pageView_.scrollEnabled = YES;
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	// remove dash view
	[self removeAllGhostViews];
    
	[self.view removeGestureRecognizer:panGestureRecognizer];
	
    self.dwAnnoInfo = nil;

	// reset annotation rect list
	[pageEditManager_ setAnnotationRectList];
	
	// set toolbar to annotation bar
	[self transformMenubar:kAnnotationBar];
}


#pragma mark -
#pragma mark device rotation.

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// AR19008
	// 2012.02.20 M.Chikyu start.
	/*
	if (editMode == kTopMenu)
	{
		if (isDeviceIsiPad == YES)
		{
			if (interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
			{
				return NO;
			}

			return YES;
		}
		else
		{
			return YES;
		}
	}
	else
	{
		if (interfaceOrientation == self.interfaceOrientation)
		{
			return YES;
		}
		else
		{
			return NO;
		}
	}
	 */

	if (interfaceOrientation == orientation_)
	{
		return YES;
	}
	else
	{
		return NO;
	}
	// 2012.02.20 M.Chikyu end.
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
	pageEditManager_.interfaceOrientation = toInterfaceOrientation;
	[self updateMenubarFrameForRotation];
}

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	if (pageEditManager_.interfaceOrientation == fromInterfaceOrientation)
	{
		return;
	}

//	pageEditManager_.interfaceOrientation = self.interfaceOrientation;

	// 2012.02.14 M.Chikyu start.
	/*
	[self resizePageView];
	 */
	[self rotatePageView];
	// 2012.02.14 M.Chikyu end.
}
// 2012.02.01(Ver2.1 New) M.Chikyu


#pragma mark -
#pragma mark method for delegate.

// wangpp 2012.2.29 start
// freehand transparent
/*
 - (void) updateFreehandAnnPropertyWithLineColor:(UIColor*)color 
                                    withLineSize:(int)size
 */
- (void) updateFreehandAnnPropertyWithLineColor:(UIColor*)color 
                                   withLineSize:(int)size
								  withLineTrans:(BOOL)transparent
// wangpp 2012.2.29 end

{
    BOOL isRefresh = YES;
	
	
	// wangpp 2012.2.29 start
	// freehand transparent
	/*
    if (CGColorEqualToColor((self.freehandColor).CGColor, color.CGColor) == true && 
        self.freehandLineSize == size)
	 */
	if (CGColorEqualToColor((self.freehandColor).CGColor, color.CGColor) == true && 
        self.freehandLineSize == size && self.freehandTransparent == transparent)
	// wangpp 2012.2.29 end
		
    {
        isRefresh = NO;
    }
    
    // 1. line color
    self.freehandColor = color;
    
    // 2. line size.
    self.freehandLineSize = size;
	
	// wangpp 2012.2.29 start
	// freehand transparent
	self.freehandTransparent = transparent;
	// wangpp 2012.2.29 end
    
    // 3. update property.
    [self updateAnnotationPropertyWithAnnotationType:ANTYPE_FREEHAND 
                                       withIsRefresh:isRefresh];

	// 4. update Dash Line color
	DWAnnBorderGhostView *dwBorderView
	= (DWAnnBorderGhostView *)[pageView_.page viewWithTag:TAG_BORDER_VIEW];

	/*
	if (dwBorderView != nil)
	{
		dwBorderView.dashLineColor = color;
		[dwBorderView setNeedsDisplay];
	}
	 */

	// 5. refresh ghost view.
	if (editMode == kSelAnnote)
	{
		[self updateBorderViewRectForUpdateAnnotationSize];
	}
}

// wangpp 2012.2.29 start
// freehand transparent
/*
 - (void) updateFreehandAnnPropertyForiPadWithLineColor:(UIColor*)color 
                                           withLineSize:(int)size
 */
- (void) updateFreehandAnnPropertyForiPadWithLineColor:(UIColor*)color 
                                          withLineSize:(int)size
										 withLineTrans:(BOOL)transparent
// wangpp 2012.2.29 end

{
    [self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	popIndex = -1;
    
    // 1. line color
    self.freehandColor = color;
    
    // 2. line size.
    self.freehandLineSize = size;
    
	// wangpp 2012.2.29 start
	// freehand transparent
	self.freehandTransparent = transparent;
	// wangpp 2012.2.29 end
	
    // 3. update property.
    [self updateAnnotationPropertyWithAnnotationType:ANTYPE_FREEHAND 
                                       withIsRefresh:YES];
	
	// 4. update Dash Line color
	DWAnnBorderGhostView *dwBorderView
	= (DWAnnBorderGhostView *)[pageView_.page viewWithTag:TAG_BORDER_VIEW];

	/*
	if (dwBorderView != nil)
	{
		dwBorderView.dashLineColor = color;
		[dwBorderView setNeedsDisplay];
	}
	 */

	// 5. refresh ghost view.
	if (editMode == kSelAnnote)
	{
		[self updateBorderViewRectForUpdateAnnotationSize];
	}
}


- (void) updateTextNotepadAnnPropertyWithNotepadColor:(UIColor*)bgColor 
                                        withFontColor:(UIColor*)fontColor
                                         withFontSize:(int)size
{
    BOOL isRefresh = YES;

    if (CGColorEqualToColor((self.textNotepadColor).CGColor, bgColor.CGColor) == true && 
        CGColorEqualToColor((self.textNotepadFontColor).CGColor, fontColor.CGColor) == true && 
        self.textNotepadFontSize == size)
    {
        isRefresh = NO;
    }
    
    BOOL isResize = NO;

	if (self.textNotepadFontSize != size)
    {
        isResize = YES;
    }
    
    if (isCanSetTextProp == NO)
	{
        if (CGColorEqualToColor((self.textNotepadColor).CGColor, bgColor.CGColor) == true)
        {
            return;
        }
    }
    
    // 1. notepad color.
    self.textNotepadColor = bgColor;
    
    // 2. font color.
    self.textNotepadFontColor = fontColor;
    
    // 3. font size.
    self.textNotepadFontSize = size;
    
    // 4. update property.
    [self updateAnnotationPropertyWithAnnotationType:ANTYPE_NOTEPAD 
                                       withIsRefresh:isRefresh];
    
	// 5. resize ghost view.
	if (editMode == kSelAnnote)
	{
		[self updateBorderViewRectForUpdateAnnotationSize];
	}

    if (isResize == YES &&
		editMode == kSelAnnote)
	{
        [pageEditManager_ setAnnotationRectList];
    }
}


- (void) updateTextNotepadAnnPropertyForiPadWithNotepadColor:(UIColor*)bgColor 
											   withFontColor:(UIColor*)fontColor
												withFontSize:(int)size
{
    [self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	popIndex = -1;
    
    BOOL isResize = NO;
    if (self.textNotepadFontSize != size)
    {
        isResize = YES;
    }
    
    // 1. notepad color.
    self.textNotepadColor = bgColor;
    
    // 2. font color.
    self.textNotepadFontColor = fontColor;
    
    // 3. font size.
    self.textNotepadFontSize = size;
    
    // 4. update property.
    [self updateAnnotationPropertyWithAnnotationType:ANTYPE_NOTEPAD 
                                       withIsRefresh:YES];
    
    // 5. resize ghost view.
	if (editMode == kSelAnnote)
	{
		[self updateBorderViewRectForUpdateAnnotationSize];
	}

    if (isResize == YES && 
		editMode == kSelAnnote)
	{
        [pageEditManager_ setAnnotationRectList];
    }
}

// wangpp 2012.4.13 start
// login
- (void) didSelectLoginAnnotationWithAnnotationIndex:(int)index
{
	applicationDelegate_.loginSetingIndex = index;
	[self.dwAnnPropertyPopController dismissPopoverAnimated:YES];
	popIndex = -1;
}
// wangpp 2012.4.13 end

- (void) didFinishedEditFreehandAnnotationWithPionts:(NSMutableArray *)points;
{
	[self addNewFreehandAnnotationWithPointArray:points];
    isDrawFreehandLine = YES;
}


- (void) didFinishedMoveAnnotationWithMovedOffset:(CGSize)offset
{
    CGRect rect = CGRectMake(dwAnnoInfo_.annoRect.origin.x + offset.width,
                             dwAnnoInfo_.annoRect.origin.y + offset.height, 
                             dwAnnoInfo_.annoRect.size.width, 
                             dwAnnoInfo_.annoRect.size.height);

    CGRect pageRect = pageView_.page.m_PageInfoA.m_SrcRect;

	if  (CGRectIntersectsRect(pageRect, rect) == NO)
	{
		return;
	}

	dwAnnoInfo_.annoRect = rect;
	
	CGSize oriPageSize = [self getCurrentPageSize];
	
	BOOL res = [pageEditManager_ updateAnnotationPositionWithAnnotationInfo:dwAnnoInfo_];
	if (res == NO)
	{
		return;
	}

	CGSize newPageSize = [self getCurrentPageSize];

	if (oriPageSize.width  != newPageSize.width ||
		oriPageSize.height != newPageSize.height)
	{
		[self resizePageView];
	}
	else
	{
		[self refreshPageView];
	}

	[pageEditManager_ setAnnotationRectList];
	
	[pageEditManager_ getAnnotationInfo:dwAnnoInfo_];
	[self enterSelectStatusWithAnnotationInfo:dwAnnoInfo_];
}


- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController
{
	popIndex = -1;
}


#pragma mark -
#pragma mark update toolbar items.

- (void) updateAnnotationPropertyWithAnnotationType:(int)type 
                                      withIsRefresh:(BOOL)refresh
{
    if (type == ANTYPE_FREEHAND)
	{
        if (editMode == kAddFreehand)
        {
            // 1. line color
            applicationDelegate_.freehandSettingColor = freehandColor_;
            
            // 2. line size.
            applicationDelegate_.freehandSettingLineSize = freehandLineSize_;
            
            // 3. update line size
            [self setLineWidthToFreehandGhostView];
			
			// wangpp 2012.2.29 start 
			// freehand transparent 
			applicationDelegate_.freehandSettingTransparent = freehandTransparent_;
			// wangpp 2012.2.29 end
			
        }
            
        // 1. line color
        [self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandColor)];
        
        // 2. line size.
        [self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandLine)];
		
		// wangpp 2012.2.29 start
		// freehand transparent
		[self updateAnnotatinPropertyValueWithPropertyType:(Utility::kFreehandTransparent)];
		// wangpp 2012.2.29 end
        
        // 3. annotation propery.
        [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
    }
	else
	{
        if (editMode == kAddNotepad)
        {
            // 1. notepad color.
            applicationDelegate_.textNotepadSettingColor = textNotepadColor_;
            
            // 2. font color.
            applicationDelegate_.textNotepadSettingFontColor = textNotepadFontColor_;
            
            // 3. font size.
            applicationDelegate_.textNotepadSettingFontSize = textNotepadFontSize_;
        }

        // 1. notepad color.
        [self updateAnnotatinPropertyValueWithPropertyType:(Utility::kNotepadColor)];
        
        // 2. font color.
        [self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontColor)];
        
        // 3. font size.
        [self updateAnnotatinPropertyValueWithPropertyType:(Utility::kTextFontSize)];
        
        // 4. annotation property.
        [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];
    }
    
    if (refresh == YES &&
		editMode == kSelAnnote)
	{
        [self updateAnnotationProperty];
    }
}


- (void) updateBorderViewRectForUpdateAnnotationSize
{
    // get select annotation info.
    [pageEditManager_ getAnnotationInfo:dwAnnoInfo_];
    
    // set annotation select status.
    [self enterSelectStatusWithAnnotationInfo:dwAnnoInfo_];
}


- (void) udpateDeleteButtonEnabledPropertyWithAnnotationType:(int)type
{
    BOOL buttonDeleteEnable = NO;

	if (dwAnnoInfo_ != nil)
	{
        buttonDeleteEnable = YES;
    }
    
    switch (type)
	{
		case ANTYPE_FREEHAND:
        {
			UIBarButtonItem* deleteItem
			= [propertybarItemFreehand_ objectAtIndex:INDEX_BUTTON_ITEM_LINE_DELETE];

            if (deleteItem != nil)
			{
				[deleteItem setEnabled:buttonDeleteEnable];
            }
			
			// wangpp 2012.3.28 start
			// login
			UIBarButtonItem* item_ = [propertybarItemFreehand_ objectAtIndex:INDEX_BUTTON_ITEM_LINE_REGIST];
			if (item_ != nil)
			{
				[item_ setEnabled:buttonDeleteEnable];
            }
			// wangpp 2012.3.28 end
			
            propertybar_.items = propertybarItemFreehand_;
            break;
        }
            
        case ANTYPE_NOTEPAD:
        {
			UIBarButtonItem* item_ = nil;
			
			// tongtx 20120217 start
			// AR009とAR010の対応
			UIBarButtonItem* demo_ = nil;
			// tongtx 20120217 end

			if (editMode == kSelAnnote &&
				dwAnnoInfo_ == nil)
			{
				break;
			}

			// get text property button state
			BOOL textPropertyEnable = YES;
			int  textAnnotCount = 0;
			
			if (editMode == kSelAnnote)
			{
				DWTextNotepadAnnotationInfo* annInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo_;
				textPropertyEnable = annInfo.hasTextAnnotation;
				textAnnotCount = annInfo.textAnnotCount;
			} 
			
			item_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_COLOR];
			
			// tongtx 20120217 start
			// AR009とAR010の対応
			demo_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_COLOR_DEMO];
			// tongtx 20120217 end
			
			if (item_ != nil &&
				isDeviceIsiPad == YES)
			{
				if (textAnnotCount == -1)
				{
					[item_ setEnabled:NO];
					
					// tongtx 20120217 start
					// AR009とAR010の対応
					[demo_ setEnabled:NO];
					// tongtx 20120217 end
				}
				else if (textAnnotCount > 1)
				{
					[item_ setEnabled:NO];
					
					// tongtx 20120217 start
					// AR009とAR010の対応
					[demo_ setEnabled:NO];
					// tongtx 20120217 end
				}
				else
				{
					[item_ setEnabled:YES];
					
					// tongtx 20120217 start
					// AR009とAR010の対応
					[demo_ setEnabled:YES];
					// tongtx 20120217 end
				}
			}
			
			item_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR];
			
			// tongtx 20120217 start
			// AR009とAR010の対応
			demo_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR_DEMO];
			// tongtx 20120217 end
			
			if (item_ != nil && isDeviceIsiPad == YES)
			{
				[item_ setEnabled:textPropertyEnable];
				
				// tongtx 20120217 start
				// AR009とAR010の対応
				[demo_ setEnabled:textPropertyEnable];
				// tongtx 20120217 end
			}
			
			item_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE];
			
			// tongtx 20120217 start
			// AR009とAR010の対応
			demo_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE_DEMO];
			// tongtx 20120217 end
			
			if (item_ != nil && isDeviceIsiPad == YES)
			{
				[item_ setEnabled:textPropertyEnable];
				
				// tongtx 20120217 start
				// AR009とAR010の対応
				[demo_ setEnabled:textPropertyEnable];
				// tongtx 20120217 end
			}
			
			item_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_DELETE];
			if (item_ != nil)
			{
				[item_ setEnabled:buttonDeleteEnable];
			}
			
			// wangpp 2012.3.28 start
			// login
			item_ = [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_REGIST];
			if (item_ != nil)
			{
				[item_ setEnabled:buttonDeleteEnable];
            }
			// wangpp 2012.3.28 end
			
			propertybar_.items = propertybarItemNotepad_;

			break;	
        }   
            
        // wangpp 2012.3.28 start
        case ANTYPE_LOGIN:
        {
			UIBarButtonItem* item_
			= [propertybarItemLogin_ objectAtIndex:INDEX_BUTTON_ITEM_LOGIN_DELETE];
            
            if (item_ != nil)
			{
				[item_ setEnabled:buttonDeleteEnable];
            }
			
			item_ = [propertybarItemLogin_ objectAtIndex:INDEX_BUTTON_ITEM_LOGIN_SELECT];
			if (item_ != nil)
			{
				[item_ setEnabled:YES];
			}
			
            propertybar_.items = propertybarItemLogin_;
            break;
        }
        // wangpp 2012.3.28 end
            
        default:
        {
			UIBarButtonItem* deleteItem
			= [propertybarItemNormal_ objectAtIndex:INDEX_BUTTON_ITEM_SELECT_DELETE];

			if (deleteItem != nil)
			{
				[deleteItem setEnabled:buttonDeleteEnable];
            }
			
			// wangpp 2012.3.28 start
			// login
			UIBarButtonItem* item_ = [propertybarItemNormal_ objectAtIndex:INDEX_BUTTON_ITEM_NORMAL_REGIST];
			if (item_ != nil)
			{
				[item_ setEnabled:buttonDeleteEnable];
            }
			// wangpp 2012.3.28 end
			
            propertybar_.items = propertybarItemNormal_;
            break;
        }
    }
}


- (void) updateAnnotatinPropertyValueWithPropertyType:(Utility::PROPERTY_TYPE)type
{
    switch (type) 
    {
		case Utility::kFreehandColor:
		{
			if ([propertybarItemFreehand_ count] > INDEX_BUTTON_ITEM_LINE_COLOR_DEMO)
			{
				UIBarButtonItem* colorButtonItem
				= [propertybarItemFreehand_ objectAtIndex:INDEX_BUTTON_ITEM_LINE_COLOR_DEMO];

				if (colorButtonItem != nil)
				{
					DWBorderView* border = (DWBorderView*)colorButtonItem.customView;
                    if (border != nil)
					{
						border.contentColor = self.freehandColor;
						[border setNeedsDisplay];
						[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
					}
				}
			}

			if (dwFreehandGhostView != nil)
			{
				dwFreehandGhostView.lineUIColor = self.freehandColor;
			}
			
			if (editMode != kSelAnnote)
			{
				applicationDelegate_.freehandSettingColor = self.freehandColor;
			}
            
            break;
		}
			
		case Utility::kFreehandLine:
		{
			if ([propertybarItemFreehand_ count] > INDEX_BUTTON_ITEM_LINE_SIZE_DEMO)
			{
				UIBarButtonItem* sizeButtonItem
				= [propertybarItemFreehand_ objectAtIndex:INDEX_BUTTON_ITEM_LINE_SIZE_DEMO];

				if (sizeButtonItem != nil)
				{
					/*
					UILabel* label = (UILabel*)sizeButtonItem.customView;

					if (label != nil)
					{
                        label.text = [NSString stringWithFormat:@"%d", freehandLineSize_];
                        [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
                    }
					 */
					UIButton* button = (UIButton*)sizeButtonItem.customView;
					
					if (button != nil)
					{
						[button setTitle:[NSString stringWithFormat:@"%d", freehandLineSize_]
								forState:UIControlStateNormal];
                        [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
					}
				}
			}
            break;
		}
		// wangpp 2012.2.29 start 
		// freehand transparent
		case Utility::kFreehandTransparent:
		{
			if ([propertybarItemFreehand_ count] > INDEX_BUTTON_ITEM_LINE_TRANSPARENT) {
				
				UIBarButtonItem* transparentButton = [propertybarItemFreehand_ objectAtIndex:INDEX_BUTTON_ITEM_LINE_TRANSPARENT];
				
				// transparent button
				if (transparentButton != nil) 
				{
					if (self.freehandTransparent == YES) 
					{
						transparentButton.image = [UIImage imageNamed:[self getFreehandTransparentButtonIcon:YES]];
					} 
					else
					{
						transparentButton.image = [UIImage imageNamed:[self getFreehandTransparentButtonIcon:NO]];
					}
					
					[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_FREEHAND];
				}
				
				if (dwFreehandGhostView != nil)
				{
					dwFreehandGhostView.transparent = self.freehandTransparent;
				}
				
				if (editMode != kSelAnnote)
				{
					applicationDelegate_.freehandSettingTransparent = self.freehandTransparent;
				}
			}
			
			break;
		}
		// wangpp 2012.2.29 end

		case Utility::kNotepadColor:
        {
			if ([propertybarItemNotepad_ count] > INDEX_BUTTON_ITEM_NOTE_COLOR_DEMO)
			{
				UIBarButtonItem* colorButtonItem
				= [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_COLOR_DEMO];

				if (colorButtonItem != nil)
				{
					DWBorderView* border = (DWBorderView*)colorButtonItem.customView;
					
					if (border != nil)
					{
						border.contentColor = self.textNotepadColor;
						[border setNeedsDisplay];
						[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];
					}
				}
				
				if (editMode != kSelAnnote)
				{
					applicationDelegate_.textNotepadSettingColor = self.textNotepadColor;
				}
			}
            break;
        }
			
		case Utility::kTextFontColor:
        {
			if ([propertybarItemNotepad_ count] > INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR_DEMO)
			{
				UIBarButtonItem* textColorButtonItem
				= [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_COLOR_DEMO];	

				if (textColorButtonItem != nil)
				{
					DWBorderView* border = (DWBorderView*)textColorButtonItem.customView;

					if (border != nil)
					{
                        border.contentColor = textNotepadFontColor_;
                        [border setNeedsDisplay];
                        [self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];
                    }
				}
				
				if (editMode != kSelAnnote)
				{
					applicationDelegate_.textNotepadSettingFontColor = self.textNotepadFontColor;
				}
			}
			break;
        }

		case Utility::kTextFontSize:
        {
			if ([propertybarItemNotepad_ count] > INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE_DEMO)
			{
				UIBarButtonItem* colorButtonItem
				= [propertybarItemNotepad_ objectAtIndex:INDEX_BUTTON_ITEM_NOTE_TEXT_SIZE_DEMO];	

				if (colorButtonItem != nil)
				{
					UIButton* button = (UIButton*)colorButtonItem.customView;
					
					if (button != nil)
					{
						[button setTitle:[NSString stringWithFormat:@"%d", textNotepadFontSize_]
								forState:UIControlStateNormal];
						
						if (textNotepadFontSize_ > 99)
						{
							[button setFrame:CGRectMake(button.frame.origin.x,
														button.frame.origin.y,
														fontSizeLabelWidth * 1.6,
														button.frame.size.height)];
						}
						else
						{
							[button setFrame:CGRectMake(button.frame.origin.x,
														button.frame.origin.y,
														fontSizeLabelWidth,
														button.frame.size.height)];
						}
						
						[self udpateDeleteButtonEnabledPropertyWithAnnotationType:ANTYPE_NOTEPAD];
                    }
				}
			}
			break;
        }
            
		default:
			break;
	}
	
	[self transformMenubar:kPropertyBar];
}


- (void) updateMenubarFrameForRotation
{
    // 2. init annotation bar.
    float width = [self getDeviceScreenRect].size.width;
	
	
	// iPadのツールバーの上部に境界線を入れる の対応
	float height = self.navigationController.toolbar.frame.size.height + menubarStartPositionY;

	[annotationbar_ setFrame:CGRectMake(0.0, menubarStartPositionY, width, height - menubarStartPositionY)];
    
    // 3. init property bar.
	[propertybar_ setFrame:CGRectMake(width, menubarStartPositionY, width, height - menubarStartPositionY)];
	
	
    // 4. init menubar bg view.
    float originX = 0.0;
    float originY = [self getDeviceScreenRect].size.height - height;

	width = [self getDeviceScreenRect].size.width;

	[bgViewMenubar_ setFrame:CGRectMake(originX, originY, width, height)];
	[bgViewMenubar_ setContentSize:CGSizeMake(width * 2, height)];

	if (bgViewMenubar_.contentOffset.x != 0)
	{
        width = [self getDeviceScreenRect].size.width;
        [bgViewMenubar_ setContentOffset:CGPointMake(width, 0) animated:NO];
    }
}


- (BOOL) updateAnnotationProperty
{
	COLORREF colorRef;
	BOOL res = NO;

	if (dwAnnoInfo_ == nil)
	{
		return NO;
	}

	int type = dwAnnoInfo_.annoType;
	
	switch (type)
	{
		case ANTYPE_FREEHAND:
		{
			DWFreehandAnnotationInfo* freehandAnnInfo = (DWFreehandAnnotationInfo*)dwAnnoInfo_;
			
			res = [pageEditManager_ transformUIColorToColorRef:freehandColor_  withColorRef:&colorRef];
			if (res == YES)
			{
				freehandAnnInfo.lineColor = colorRef;
			}
			
			freehandAnnInfo.lineWidth = freehandLineSize_;
			
			// wangpp 2012.3.5 start 
			// freehand transparent
			freehandAnnInfo.transparent = freehandTransparent_;
			// wangpp 2012.3.5 end
			
			break;
		}
			
		case ANTYPE_NOTEPAD:
		{
			DWTextNotepadAnnotationInfo* textNotepadAnnInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo_;
			
			res = [pageEditManager_ transformUIColorToColorRef:textNotepadColor_  withColorRef:&colorRef];
			if (res == YES)
			{
				textNotepadAnnInfo.notepadColor = colorRef;
			}
			
			res = [pageEditManager_ transformUIColorToColorRef:textNotepadFontColor_  withColorRef:&colorRef];
			if (res == YES)
			{
				textNotepadAnnInfo.textFontColor = colorRef;
			}
			
			textNotepadAnnInfo.textFontsize = textNotepadFontSize_;
			
			textNotepadAnnInfo.textAnnSize = [self getTextAnnotationCustomSize:textNotepadAnnInfo];
			
			break;
		}
			
		default:
			break;
	}
	
	CGSize oldPageSize = [self getCurrentPageSize];
	
	res = [pageEditManager_ updateAnnotationWithAnnotationInfo:dwAnnoInfo_];
	if (res == NO)
	{
		return NO;
	}

	CGSize newPageSize = [self getCurrentPageSize];

	if (oldPageSize.width  != newPageSize.width ||
		oldPageSize.height != newPageSize.height)
	{
		[self resizePageView];
	}
	else
	{
		[self refreshPageView];
	}
	
	return YES;
}


- (void) processEventWithTouchPoint:(CGPoint)touchPoint
{
    notepadPosition = touchPoint;
    
	if (editMode == kAddFreehand)
	{
		CGRect pageSrcRect = pageView_.page.m_PageInfoA.m_SrcRect;
		if (CGRectContainsPoint(pageSrcRect, touchPoint))
		{
			NSMutableArray *points = [NSMutableArray array];

			CGPoint pt = CGPointZero;

			pt.x = touchPoint.x - pageSrcRect.origin.x;
			pt.y = touchPoint.y - pageSrcRect.origin.y;

			NSValue *pointValue = [NSValue valueWithCGPoint:pt];

			[points addObject:pointValue];
			[points addObject:pointValue];

			[self addNewFreehandAnnotationWithPointArray:points];

			[pageView_.page performSelectorOnMainThread:@selector(setNeedsDisplay)
											 withObject:nil
										  waitUntilDone:NO];
		}
	}
    
    if (editMode == kAddNotepad)
	{
		BOOL isCanPaste = NO;
        CGRect shadowRect = [self getNewTextNotepadAnnotationRectWithTouchPoint:touchPoint];

		if (CGRectIntersectsRect(pageView_.page.m_PageInfoA.m_SrcRect, shadowRect) == YES)
		{
			isCanPaste = YES;
		}
		
		if (isCanPaste == YES)
		{
			self.dwInputField.text = @"";

			// 2012.02.01(Ver2.1 New) M.Chikyu
			[self enterAddTextNotePadAnnotationWithFrame:shadowRect];
			[self showTextNotepadAnnotationInputView];
			/*
			[self didEndEditingTextNotepadAnnotationWithPoint:touchPoint];
			 */

			[self.view removeGestureRecognizer:panGestureRecognizer];
			// 2012.02.01(Ver2.1 New) M.Chikyu
		}
		else
		{
			UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
			if (dwBorderView != nil)
			{
				[dwBorderView removeFromSuperview];
			}
		}

    }

	// 2012.02.01(Ver2.1 New) M.Chikyu
    if (editMode == kSelAnnote ||
		editMode == kTopMenu)
	/*
    if (editMode == kSelAnnote ||
		editMode == kAddNotepad||
		editMode == kTopMenu)
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu
	{
		pageView_.scrollEnabled = NO;

		DWAnnotationInfo* dwInfo = [self isTappedOnAnnotationWithTouchPoint:touchPoint];
		if (dwInfo == nil)
		{
			[self exitSelectStatus];

			return;
        }


		// get select annotation info.
		[pageEditManager_ getAnnotationInfo:dwInfo];

		if (editMode == kSelAnnote &&
			annotationIndex == dwInfo.annoIndex)
		{
			[self actionOnDoubleTap:dwInfo];

			return;
		}


		// set annotation select status.
		[self enterSelectStatusWithAnnotationInfo:dwInfo];
		[self selectAnnotation:dwInfo];

		return;
    }
    
    // yangjx 2012.4.16 start
    if (editMode == kAddLogin) 
    {
        if (CGRectContainsPoint(pageView_.page.m_PageInfoA.m_SrcRect , touchPoint)) 
        {
            DWLoginAnnotationInfo *info_ = [[[DWLoginAnnotationInfo alloc] init] autorelease];
            info_.annoRect = CGRectMake(touchPoint.x, touchPoint.y, 0, 0);
            info_.annoType = ANTYPE_LOGIN;
            info_.pageIndex = pageIndex_;
			info_.loginAnnIndex = applicationDelegate_.loginSetingIndex;
			self.dwAnnoInfo = info_;
            if ([pageEditManager_ addAnnotationWithAnnotationInfo:dwAnnoInfo_]) 
            {
                [self displayIndicator];
                [pageView_.page performSelectorOnMainThread:@selector(setNeedsDisplay)
                                                 withObject:nil
                                              waitUntilDone:NO];
                [self performSelectorOnMainThread:@selector(hideIndicator)
                                                 withObject:nil
                                              waitUntilDone:NO];
                [pageEditManager_ setAnnotationRectList];
            }
            else
            {
                UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
                                                                   message:NSLocalizedString(@"MSG_ANNOTATIONEDIT_ADD_FAILE", nil)
                                                                  delegate:self
                                                         cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                         otherButtonTitles:nil, (char*)nil];
                [alertView show];
                [alertView release];

            }
            
            [self actionOnTouchBackButton];
        }
    }
    // yangjx 2012.4.16 end
}

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) actionOnDoubleTap:(DWAnnotationInfo *)dwInfo 
{
	// if touch text notepad annotation, edit text
	if (dwInfo == nil ||
		dwInfo.annoType != ANTYPE_NOTEPAD)
	{
		return;
	}

	if (isDeviceIsiPad == NO)
	{
		[self.view removeGestureRecognizer:panGestureRecognizer];
	}
	
	[pageEditManager_ getAnnotationInfo:dwInfo];
	
	DWTextNotepadAnnotationInfo* textNotepadAnnInfo = (DWTextNotepadAnnotationInfo*)dwInfo;
	
	if (textNotepadAnnInfo.textAnnotCount != 0 && textNotepadAnnInfo.textAnnotCount != 1)
	{
		return;
	}

	int textLenght = [self getOutputTextCountWithInputText:textNotepadAnnInfo.textContent];
	if (textLenght > MAX_ALL_TEXT_COUNT)
	{
		return;
	}

	textNotepadAnnInfo.isUpdateText = YES;
	[self enterSelectStatusWithAnnotationInfo:dwInfo];
	
	DWAnnShadowGhostView *dwShadowView = (DWAnnShadowGhostView *)[pageView_.page viewWithTag:TAG_SHADOW_VIEW];
	[dwShadowView removeFromSuperview];
	
	
	dwInputField_.text = @"";
	
	DWTextNotepadAnnotationInfo* textNotepadInfo = (DWTextNotepadAnnotationInfo*)dwInfo;
	if (textNotepadInfo.textContent != nil)
	{
		// 2012.02.01(Ver2.1 New) M.Chikyu
		/*
		NSString* text = [self formatTextAnnotationContentWithTextOutput:textNotepadInfo.textContent];
		if (text != nil)
		{
			dwInputField_.text = text;
		}
		 */
		if (textNotepadInfo.isAutoResize == YES)
		{
			NSString* text = [self formatTextAnnotationContentWithTextOutput:textNotepadInfo.textContent];
			if (text != nil)
			{
				dwInputField_.text = text;
			}
		}
		else
		{
			dwInputField_.text = textNotepadInfo.textContent;
		}
		// 2012.02.01(Ver2.1 New) M.Chikyu
	}
	

	[self showTextNotepadAnnotationInputView];			
}
// 2012.02.01(Ver2.1 New) M.Chikyu


- (void) resizePageView
{
	// 表示ページを再描画
	[self displayIndicator];

	if (pageView_ != nil)
	{
		CGSize viewSize = pageView_.frame.size;

		CGPoint oldOffset = pageView_.initContentOffset;

		BOOL isZooming = pageEditManager_.isZooming;
		BOOL scrollEnabled = pageView_.scrollEnabled;

		pageEditManager_.isZooming = YES;

		float zoomScale	= pageView_.zoomScale;
		CGPoint offset	= pageView_.contentOffset;
		
		CGSize preContSize = pageView_.contentSize;

		if (viewSize.width > preContSize.width)
		{
			offset.x -= (viewSize.width - preContSize.width) / 2;
		}
		
		if (viewSize.height > preContSize.height)
		{
			offset.y -= (viewSize.height - preContSize.height) / 2;
		}

		[self removeAllGhostViews];

		[pageView_.page removeFromSuperview];
		[pageView_ removeFromSuperview];
		[pageView_.page release];
		[pageView_ release];

		pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_
														 minViewScale:zoomScale];
		
		[self.view addSubview:pageView_];
		
		CGPoint newOffset = pageView_.initContentOffset;
		
		pageView_.scrollEnabled = NO;

		[pageView_ setZoomScale:zoomScale
					   animated:NO];

		CGSize afterContSize = pageView_.contentSize;

		offset = CGPointMake(offset.x + (newOffset.x - oldOffset.x) * zoomScale,
							 offset.y + (newOffset.y - oldOffset.y) * zoomScale);
		
		if (viewSize.width > afterContSize.width)
		{
			offset.x += (viewSize.width - afterContSize.width) / 2;
		}
		
		if (viewSize.height > afterContSize.height)
		{
			offset.y += (viewSize.height - afterContSize.height) / 2;
		}

		[pageView_ setContentOffset:offset
						   animated:NO];

		pageEditManager_.isZooming = isZooming;
		pageView_.scrollEnabled = scrollEnabled;
	}
	else
	{
		pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_];
		
		[self.view addSubview:pageView_];
	}

	[self hideIndicator];
}


// 2012.02.14 M.Chikyu start.

// 描画データが同じでスケールが変更
- (void) rotatePageView
{
	// 表示ページを回転
	[self displayIndicator];
	
	if (pageView_ != nil)
	{
		CGSize viewSize = pageView_.frame.size;
		
		CGPoint oldOffset = pageView_.initContentOffset;
		
		BOOL isZooming = pageEditManager_.isZooming;
		BOOL scrollEnabled = pageView_.scrollEnabled;
		
		pageEditManager_.isZooming = YES;
		
		float zoomScale	= pageView_.zoomScale;
		CGPoint offset	= pageView_.contentOffset;
		
		float preBaseScale = pageView_.minScale;
		
		[self removeAllGhostViews];
		
		[pageView_.page removeFromSuperview];
		[pageView_ removeFromSuperview];
		[pageView_.page release];
		[pageView_ release];

		pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_];
		
		[self.view addSubview:pageView_];
		
		float afterBaseScale = pageView_.minScale;

		zoomScale = zoomScale * preBaseScale / afterBaseScale;
		
		pageView_.scrollEnabled = NO;
		
		[pageView_ setZoomScale:zoomScale
					   animated:NO];
		
		[pageView_ setContentOffset:offset
						   animated:NO];
		
		pageEditManager_.isZooming = isZooming;
		pageView_.scrollEnabled = scrollEnabled;
	}
	else
	{
		pageView_ = [pageEditManager_ insertEditPageViewWithPageIndex:pageIndex_];
		
		[self.view addSubview:pageView_];
	}
	
	[self hideIndicator];
}
// 2012.02.14 M.Chikyu end.


- (void) refreshPageView
{
	[self displayIndicator];

	[self removeAllGhostViews];
	[pageView_.page performSelectorOnMainThread:@selector(setNeedsDisplay)
									 withObject:nil
								  waitUntilDone:NO];

	[self performSelectorOnMainThread:@selector(hideIndicator)
						   withObject:nil
						waitUntilDone:NO];
}


- (void) removeAllGhostViews
{
    UIView *dwBorderView = [pageView_.page viewWithTag:TAG_BORDER_VIEW];
	if (dwBorderView != nil)
	{
		[dwBorderView removeFromSuperview];
	}
    
	UIView *dwShadowView = [pageView_.page viewWithTag:TAG_SHADOW_VIEW];
	if (dwShadowView != nil)
	{
		[dwShadowView removeFromSuperview];
	}

	if (dwFreehandGhostView != nil)
	{
		[dwFreehandGhostView removeFromSuperview];
		dwFreehandGhostView = nil;
	}
}


- (BOOL) isAnnotationOutPageEdgeWithAnnotationInfo:(DWAnnotationInfo *)info
{
	BOOL isMoved = NO;
	
    MPCObject* obj = [pageEditManager_ getMPCObjectWithPageIndex:pageIndex_];
	CGRect annotationRect = [pageEditManager_ 
							 getAnnotationRectWithParentObject:obj
							 withAnnoIndex:info.annoIndex];
	
    CGRect pageRect = pageView_.page.m_PageInfoA.m_SrcRect;

	if (CGRectIntersectsRect(annotationRect, pageRect) == NO)
	{
		CGPoint newPosition = CGPointZero;
		float newPositionX = 0;
		float newPositionY = 0;
        
		//annotation is outside at left
		float offSetX = pageView_.page.m_PageInfoA.m_SrcRect.origin.x - 
        (annotationRect.origin.x + annotationRect.size.width);
		
		if (offSetX > 0)
		{
			newPositionX =  annotationRect.origin.x - (annotationRect.origin.x + annotationRect.size.width);
			newPositionY = annotationRect.origin.y;
			newPosition = CGPointMake(newPositionX + 1,
									  newPositionY);
		}
		
		//annotation is outside at top
		float offSetY = annotationRect.origin.y + annotationRect.size.height;
 
		if (offSetY < 0)
		{
			newPositionX = annotationRect.origin.x;
			newPositionY = annotationRect.origin.y - (annotationRect.origin.y + annotationRect.size.height);
			newPosition = CGPointMake(annotationRect.origin.x,
									  newPositionY + 1);;
        }
		
		//move annotation inside 
		info.annoRect = CGRectMake(newPosition.x, 
                                   newPosition.y, 
                                   annotationRect.size.width, 
                                   annotationRect.size.height);
        
		isMoved = [pageEditManager_ updateAnnotationPositionWithAnnotationInfo:info];
	}
	
	return isMoved;
}

#pragma mark -
#pragma mark private method.
- (void) transformMenubar:(MENU_BAR_TYPE)type
{
    if (type == kAnnotationBar)
	{
		// wangpp 2012.4.13 start
		// login
		UIBarButtonItem* item_ = [annotationbarItem_ objectAtIndex:INDEX_BUTTON_ITEM_ANNLIST_REGIST];
		if (loginAnnoCount_ == 0)
		{
			item_.enabled = NO;
		}
		else
		{
			item_.enabled = YES;
		}
		// wangpp 2012.4.13 end
		
        [bgViewMenubar_ setContentOffset:CGPointMake(0, 0)
								animated:YES];

		[dwAnnPropertyPopController dismissPopoverAnimated:YES];

		propertybar_.items = propertybarItemNormal_;
		popIndex = -1;
    }
	else
	{
        float width = [self getDeviceScreenRect].size.width;

		[bgViewMenubar_ setContentOffset:CGPointMake(width, 0)
								animated:YES];
    }
}


- (CGRect) getDeviceScreenRect
{
	long pageWidth  = 0;
	long pageHeight = 0;
	CGRect screenFrame = [[UIScreen mainScreen] bounds];

	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
        (self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		pageWidth  = screenFrame.size.width;
		pageHeight = screenFrame.size.height;
	}
	else
	{
		pageWidth  = screenFrame.size.height;
		pageHeight = screenFrame.size.width;
	}
	
	return CGRectMake(0, 0, pageWidth, pageHeight);
}


- (CGSize) getDeviceKeyboardSize:(NSDictionary*)dic
{
    if (dic == nil)
	{
        return CGSizeZero;
    }
    
    NSValue *value_ = [dic objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keyboardRect = [value_ CGRectValue];
    
    float keyboardWidth  = 0.0;
    float keyboardHeight = 0.0;

	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
        (self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		keyboardWidth  = keyboardRect.size.width;
		keyboardHeight = keyboardRect.size.height;
	}
	else
	{
		keyboardWidth  = keyboardRect.size.height;
		keyboardHeight = keyboardRect.size.width;
	}
	
	return CGSizeMake(keyboardWidth, keyboardHeight);
}


- (float) getToolbarHeight
{
    float height_ = 0.0;

	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) ||
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		height_ = TOOLBAR_HEIGHT_H;
	}
	else
	{
		height_ = TOOLBAR_HEIGHT_V;
	}

	return height_;
}


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


#pragma mark -
#pragma mark get icon

- (NSString*) getFreehandButtonIcon
{
	return _ICON_ADDFREEHANDANNOTATION_LOWSCALE_;
}

- (NSString*) getTextNotepadButtonIcon
{
	return _ICON_ADDTEXTNOTEPADANNOTATION_LOWSCALE_;
}

- (NSString*) getFreehandColorButtonIcon
{
	return _ICON_FREEHANDANNOTATION_COLOR_LOWSCALE_;
}

- (NSString*) getFreehandLineSizeButtonIcon
{
	return _ICON_FREEHANDANNOTATION_LINESIZE_LOWSCALE_;
}

// wangpp 2012.2.28 start
// freehand transparent
- (NSString*) getFreehandTransparentButtonIcon:(BOOL)trans
{
	if (trans == YES) 
	{
		return _ICON_FREEHANDANNOTATION_TRANSPARENT_ON_;
	}
	else
	{
		return _ICON_FREEHANDANNOTATION_TRANSPARENT_OFF_;
	}
}
// wangpp 2012.2.28 end

- (NSString*) getTextNotepadBackgroundColorButtonIcon
{
	return _ICON_TEXTNOTEPADANNOTATION_COLOR_LOWSCALE_;
}
- (NSString*) getTextNotepadFontColorButtonIcon
{
	return _ICON_TEXTNOTEPADANNOTATION_FONTCOLOR_LOWSCALE_;
}
- (NSString*) getTextNotepadFontSizeButtonIcon
{
	return _ICON_TEXTNOTEPADANNOTATION_FONTSIZE_LOWSCALE_;
}

- (NSString*) getDeleteButtonIcon
{
	return _ICON_DELETE_LOWSCALE_;
}

// wangpp 2012.4.13 start
// login
- (NSString*) getLoginButtonIcon
{
	return _ICON_LOGIN_ANNO_;
}

- (NSString*) getRegistLoginButtonIcon
{
	return _ICON_REGIST_LOGIN_ANNO_;
}

- (NSString*) getSelectLoginAnnButtonIcon
{
	return _ICON_SELECT_LOGIN_ANNO_;
}
// wangpp 2012.4.13 end

- (NSString*) getFileFullName
{
	return [pageViewManager_ getFileFullName];
}

- (float) getCurrentZoomScale
{
	BOOL isZooming = pageEditManager_.isZooming;

	pageEditManager_.isZooming = YES;
	float zoomScale = pageView_.zoomScale;
	pageEditManager_.isZooming = isZooming;
	
	return zoomScale;
}

#pragma mark -
#pragma mark Memory

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
	[singleTapGestureRecognizer release];
	[longPressTapGestureRecognizer release];
	[panGestureRecognizer release];
	[pinchGestureRecognizer release];
	
    [annotationbar_ release];
    [propertybar_ release];
    [bgViewMenubar_ release];
    [annotationbarItem_ release];
    [propertybarItemNormal_ release];
    [propertybarItemNotepad_ release];
    [propertybarItemFreehand_ release];
	[propertybarItemLogin_ release];
    
	self.dwFinishToolbar = nil;
    
    [dwAnnoInfo_ release];
    
    [dwInputToolbar_ release];
    [dwInputField_ release];
//	[dwFreehandGhostView release];
	
	if (pageEditManager_ != nil)
	{
		[pageEditManager_ release];
	}
    
    [dwAnnPropertyNavController release];
    [dwAnnPropertyPopController release];

    if (pageView_ != nil)
	{
		if (pageView_.page != nil)
		{
			[pageView_.page removeFromSuperview];
			[pageView_.page release];
		}

		[pageView_ removeFromSuperview];
		[pageView_ release];
	}

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

	if (isIndicatorAnimating == YES)
	{
		return;
	}
	
	// 2012.02.13 M.Chikyu start.
	if (pageView_ != nil)
	{
		if (pageView_.page.m_drawTime < 0.5)
		{
			return;
		}
	}
	// 2012.02.13 M.Chikyu end.

	// 2012.02.20 M.Chikyu start.
	/*
	if (isDeviceIsiPad == NO && isKeyboardShowed == YES)
	{
		activeIndicator_.center = CGPointMake(self.view.center.x,
											  self.view.center.y - 100);
	}
	else
	{
		activeIndicator_.center = self.view.center;
	}
	 */

	CGRect scRect = [pageEditManager_ getScreenRect];
	if (isDeviceIsiPad == NO && isKeyboardShowed == YES)
	{
		activeIndicator_.center = CGPointMake(scRect.size.width  / 2,
											  scRect.size.height / 2 - 100);
	}
	else
	{
		activeIndicator_.center = CGPointMake(scRect.size.width  / 2,
											  scRect.size.height / 2);
	}
	// 2012.02.20 M.Chikyu end.

	[activeIndicator_ performSelectorInBackground:@selector(startAnimating)
						   withObject:nil];
	
	isIndicatorAnimating = YES;
}

- (void) hideIndicator
{
	if (activeIndicator_ == nil)
	{
		return;
	}

	if (isIndicatorAnimating == NO)
	{
		return;
	}

	[self.view bringSubviewToFront:activeIndicator_];

	while (activeIndicator_.isAnimating == NO)
	{
		usleep(100000);
	}

	[activeIndicator_ stopAnimating];
	
	isIndicatorAnimating = NO;
}
// 2012.02.01(Ver2.1 New) M.Chikyu

@end

