//
//  DWIphoneTextnotepadPropertyController.mm
//  DWViewer
//
//  Created by zhaijie on 11-8-24.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DWTextNotepadAnnPropertySettingsController.h"
#import "Utility.h"
// lixin 2011/09/30 start 
// 選択枠の追加 の対応
#import "DWViewerGUIConst.h"
// lixin 2011/09/30 end

#define TAG_BACKGROUNDCOLOR_TITLE_LABEL   1001
#define TAG_FONTCOLOR_TITLE_LABEL         1002
#define TAG_FONTSIZE_TITLE_LABEL          1003

#define TAG_FONTSIZE_DEMO_LABEL           1004
#define TAG_FONTSIZE_MINA_LABEL           1005
#define TAG_FONTSIZE_MAXA_LABEL           1006
#define TAG_FONTSIZE_SLIDER               1007

#define TAG_BACKGROUNDCOLOR_BUTTON_MIN    1099
#define TAG_FONTCOLOR_BUTTON_MIN          1199

#define RGB(r,g,b)  ((b << 16) | (g << 8) | r)

const int      screenDistance = 10;
const int      colorButtonHeight = 25;
const int      portraitTopDistance = 70;
const int      landscapeTopDistance = 40;
const int      portraitDistance = 50;
const int      landscapeDistance = 20;
const int      titleLabelHeight = 30;

const int      ipadButtonDistance = 10;
const int      ipadButtonSize = 40;
const int      buttonCornerRadius = 4;
const CGFloat  buttonBorderWidth = 2.5;
const CGFloat  buttonSelectTransform = 1.1;

const int      minFontSize = 8;
const int      maxFontSize = 36;

@implementation DWTextNotepadAnnPropertySettingsController
@synthesize delegate;

@synthesize textNotepadBGColor;
@synthesize textNotepadFontColor;
@synthesize textNotepadFontSize;
// yangjx 2011/09/06 start
// NS-AR(011/1003/1004) の対応
@synthesize hasTextAnnotation;
// yangjx 2011/09/06 end
#pragma mark -
#pragma mark init

// yangjx 2011/09/06 start
// NS-AR(011/1003/1004) の対応
/*old
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
*/ 

// 2012.02.14 M.Chikyu start.
/*
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
				 withisHasText:(BOOL)isHasText
                 withTextCount:(int)textCount_
 */

- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
				 withisHasText:(BOOL)isHasText
                 withTextCount:(int)textCount_
			   withOrientation:(UIInterfaceOrientation)orientation
// 2012.02.14 M.Chikyu end.

// yangjx 2011/09/06 end
{
	if ((self = [super init]))
	{
		// yangjx 2011/09/06 start
		// NS-AR(011/1003/1004) の対応
		hasTextAnnotation = isHasText;
		// yangjx 2011/09/06 end
        
        // yangjx 2011/09/16 start
        // NS-AR(011/1003/1004) の対応
        textCount = textCount_;
        // yangjx 2011/09/16 end
		
		// 2012.02.01(Ver2.1 New) M.Chikyu
		/*
		[[UIApplication sharedApplication] setStatusBarHidden:NO 
												withAnimation:UIStatusBarAnimationNone];
		 */
		// 2012.02.01(Ver2.1 New) M.Chikyu
		
		self.textNotepadBGColor = backgroundColor;
		self.textNotepadFontColor = textColor;
		self.textNotepadFontSize = textSize;

		propertyType_ = UINotepadPropertyTypeAll;
		deviceIsiPad_ = NO;
		
		// Array For Save Color
		arrayListBackgroundColor = [[NSArray alloc] initWithObjects:
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(194.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(157.0 / 255.0) green:(191.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(100.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(157.0 / 255.0) green:(255.0 / 255.0) blue:(194.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(215.0 / 255.0) blue:(225.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(200.0 / 255.0) green:(225.0 / 255.0) blue:(250.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(250.0 / 255.0) blue:(195.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(205.0 / 255.0) green:(250.0 / 255.0) blue:(210.0 / 255.0) alpha:1],
                                    (UIColor*)nil];
		
		arrayListFontColor = [[NSArray alloc] initWithObjects:
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

		// 2012.02.14 M.Chikyu start.
		orientation_ = orientation;
		// 2012.02.14 M.Chikyu end.
	}
    
	return self;
}
// yangjx 2011/09/06 start
// NS-AR(011/1003/1004) の対応
/*
- (id) initForiPadWithPropertyType:(UINotepadPropertyType)type
			   withBackgroundColor:(UIColor*)backgroundColor 
					 withTextColor:(UIColor*)textColor 
					  withTextSize:(int)textSize
*/ 
- (id) initForiPadWithPropertyType:(UINotepadPropertyType)type
			   withBackgroundColor:(UIColor*)backgroundColor 
					 withTextColor:(UIColor*)textColor 
					  withTextSize:(int)textSize
					 withisHasText:(BOOL)isHasText
{
	if ((self = [super init]))
	{
		// yangjx 2011/09/06 start
		// NS-AR(011/1003/1004) の対応
		hasTextAnnotation = isHasText;
		// yangjx 2011/09/06 end
		
		self.textNotepadBGColor = backgroundColor;
		self.textNotepadFontColor = textColor;
		self.textNotepadFontSize = textSize;
		
		propertyType_ = type;
		deviceIsiPad_ = YES;
		
		// Array For Save Color
		// Array For Save Color
		arrayListBackgroundColor = [[NSArray alloc] initWithObjects:
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(194.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(157.0 / 255.0) green:(191.0 / 255.0) blue:(255.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(255.0 / 255.0) blue:(100.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(157.0 / 255.0) green:(255.0 / 255.0) blue:(194.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(215.0 / 255.0) blue:(225.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(200.0 / 255.0) green:(225.0 / 255.0) blue:(250.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(255.0 / 255.0) green:(250.0 / 255.0) blue:(195.0 / 255.0) alpha:1],
                                    [UIColor colorWithRed:(205.0 / 255.0) green:(250.0 / 255.0) blue:(210.0 / 255.0) alpha:1],
                                    (UIColor*)nil];
		
		arrayListFontColor = [[NSArray alloc] initWithObjects:
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
	}
	
	return self;
}
// yangjx 2011/09/06 end
#pragma mark -
#pragma mark draw
- (void)viewDidLoad {
    [super viewDidLoad];
    
    // lixin 2011/09/30 start 
    // 選択枠の追加 の対応
    noteColorGhostView_ = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[self getSelectColorImageName]]];
    noteColorGhostView_.backgroundColor = [UIColor clearColor];
    
    fontColorGhostView_ = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[self getSelectColorImageName]]];
    fontColorGhostView_.backgroundColor = [UIColor clearColor];
    // lixin 2011/09/30 end
	
	switch (propertyType_) {
		case UINotepadPropertyTypeAll:
			[self drawViewItems];
			break;
		case UINotepadPropertyTypeBackgroundColor:
			[self drawBackgroundColorSettingView];
			break;
		case UINotepadPropertyTypeTextColor:
			[self drawTextColorSettingView];
			break;
		case UINotepadPropertyTypeTextSize:
			[self drawTextSizeSettingView];
			break;
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

- (void) drawViewItems
{
	COLORREF colorRefSrcColor = 0;
	COLORREF colorRefDstColor = 0;

	// Back Button On NavigationBar
	[self initBackButtonOnNavigationBar];
	
	// start draw view
	int viewTopHeight = [self getTopDistance];
	int viewWidth = [self getViewWidth];
	int propertyDistance = [self getPropertyDistance];
	CGFloat buttonWidth = (viewWidth-screenDistance*2)/8.0;
	
	// 1. draw background color property setting view
	// 1.1 draw title
	CGRect bgColorTitleLabelRect = CGRectMake(screenDistance, viewTopHeight, viewWidth, titleLabelHeight);
	UILabel* bgColorTitleLabel = [[UILabel alloc] initWithFrame:bgColorTitleLabelRect];
	bgColorTitleLabel.tag = TAG_BACKGROUNDCOLOR_TITLE_LABEL;
	bgColorTitleLabel.backgroundColor = [UIColor clearColor];
	bgColorTitleLabel.textColor = [UIColor whiteColor];
	bgColorTitleLabel.text = NSLocalizedString(@"TITLE_TEXTNOTEPAD_NOTEPADCOLOR", nil);
	[self.view addSubview:bgColorTitleLabel];
	[bgColorTitleLabel release];
	
	// 1.2 draw background color button
	[self transformUIColorToColorRef:self.textNotepadBGColor 
						withColorRef:&colorRefSrcColor];
	
	int bgColorCount = [arrayListBackgroundColor count];
	for(int i = 0; i < bgColorCount; i ++)
	{
		CGRect buttonRect = CGRectMake(screenDistance+buttonWidth*i, 
									   bgColorTitleLabelRect.origin.y+titleLabelHeight+5, 
									   buttonWidth, 
									   colorButtonHeight);
		
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		colorButton.tag = TAG_BACKGROUNDCOLOR_BUTTON_MIN+i;
		colorButton.frame = buttonRect;
		colorButton.backgroundColor = [arrayListBackgroundColor objectAtIndex:i];

		// check select
        UIColor* bgColor = (UIColor*)[arrayListBackgroundColor objectAtIndex:i];
		[self transformUIColorToColorRef:bgColor  withColorRef:&colorRefDstColor];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		/*
		if (colorRefSrcColor == colorRefDstColor)
		{
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor whiteColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		*/
		// lixin 2011/09/30 end

		[colorButton addTarget:self 
						action:@selector(actionOnTouchBgColorSettingsButton:)
			  forControlEvents:UIControlEventTouchUpInside];
        
        // yangjx 2011/09/16 start
        // NS-AR(011/1003/1004) の対応
        if (textCount > 1 || textCount == -1) {
            [colorButton setEnabled:NO];
        }else {
            [colorButton setEnabled:YES];
        }
        // yangjx 2011/09/16 end
		[self.view addSubview:colorButton];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:NO];
		}
		// lixin 2011/09/30 end
	}
	
	// 2. draw font color property setting view
	// 2.1 draw title
	CGRect fontColorTitleLabelRect = CGRectMake(screenDistance, 
												viewTopHeight+titleLabelHeight+5+colorButtonHeight+propertyDistance, 
												viewWidth, 
												titleLabelHeight);
	UILabel* fontColorTitleLabel = [[UILabel alloc] initWithFrame:fontColorTitleLabelRect];
	fontColorTitleLabel.tag = TAG_FONTCOLOR_TITLE_LABEL;
	fontColorTitleLabel.backgroundColor = [UIColor clearColor];
	fontColorTitleLabel.textColor = [UIColor whiteColor];
	fontColorTitleLabel.text = NSLocalizedString(@"TITLE_TEXTNOTEPAD_TEXTCOLOR", nil);
	[self.view addSubview:fontColorTitleLabel];
	[fontColorTitleLabel release];
	
	// 2.2 draw font color button
	[self transformUIColorToColorRef:self.textNotepadFontColor  
						withColorRef:&colorRefSrcColor];
	
	int fontColorCount = [arrayListFontColor count];
	for(int i = 0; i < fontColorCount; i ++)
	{
		CGRect buttonRect = CGRectMake(screenDistance+buttonWidth*(i%(fontColorCount/2)), 
									   viewTopHeight+(titleLabelHeight+5)*2+colorButtonHeight+propertyDistance
									   +colorButtonHeight*(i/(fontColorCount/2)), 
									   buttonWidth, 
									   colorButtonHeight);
		
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		colorButton.frame = buttonRect;
		colorButton.tag = TAG_FONTCOLOR_BUTTON_MIN+i;
		colorButton.backgroundColor = [arrayListFontColor objectAtIndex:i];
		
		// check select
		UIColor* fontColor = (UIColor*)[arrayListFontColor objectAtIndex:i];
		[self transformUIColorToColorRef:fontColor  withColorRef:&colorRefDstColor];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		/*
		if (colorRefSrcColor == colorRefDstColor)
		{
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor whiteColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		*/
		// lixin 2011/09/30 end
		
		[colorButton addTarget:self 
						action:@selector(actionOnTouchFontColorSettingsButton:)
			  forControlEvents:UIControlEventTouchUpInside];
		
		// yangjx 2011/09/06 start
		// NS-AR(011/1003/1004) の対応
		[colorButton setEnabled:hasTextAnnotation];
		// yangjx 2011/09/06 end
		
		[self.view addSubview:colorButton];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:YES];
		}
		// lixin 2011/09/30 end
	}
	
	// 3. draw font size property setting
	// 3.1 draw title
	CGRect fontSizeTitleLabelRect = CGRectMake(screenDistance, 
											   viewTopHeight+(titleLabelHeight+5)*2+colorButtonHeight*3+propertyDistance*2,
											   150, 
											   titleLabelHeight);
	UILabel* fontSizeTitleLabel = [[UILabel alloc] initWithFrame:fontSizeTitleLabelRect];
	fontSizeTitleLabel.tag = TAG_FONTSIZE_TITLE_LABEL;
	fontSizeTitleLabel.backgroundColor = [UIColor clearColor];
	fontSizeTitleLabel.textColor = [UIColor whiteColor];
	fontSizeTitleLabel.text = NSLocalizedString(@"TITLE_TEXTNOTEPAD_FONTSIZE", nil);
	[self.view addSubview:fontSizeTitleLabel];
	[fontSizeTitleLabel release];
	
	// 3.2 draw demo label
	CGRect fontSizeDemoLabelRect = CGRectMake(screenDistance+150, 
											   fontSizeTitleLabelRect.origin.y,
											   100, 
											   titleLabelHeight);
	UILabel* fontSizeDemoLabel = [[UILabel alloc] initWithFrame:fontSizeDemoLabelRect];
	fontSizeDemoLabel.tag = TAG_FONTSIZE_DEMO_LABEL;
	fontSizeDemoLabel.backgroundColor = [UIColor clearColor];
	fontSizeDemoLabel.textColor = [UIColor whiteColor];
	fontSizeDemoLabel.text = [NSString stringWithFormat:@"%2dpt", self.textNotepadFontSize];
	[self.view addSubview:fontSizeDemoLabel];
	[fontSizeDemoLabel release];
	
	// 3.3 draw min label
	CGRect minLabelRect = CGRectMake(screenDistance,
									 viewTopHeight+(titleLabelHeight+5)*3+colorButtonHeight*3+propertyDistance*2,
									 40,
									 titleLabelHeight);
	UILabel* minLabel = [[UILabel alloc] initWithFrame:minLabelRect];
	minLabel.tag = TAG_FONTSIZE_MINA_LABEL;
	minLabel.backgroundColor = [UIColor clearColor];
	minLabel.textColor = [UIColor whiteColor];
	minLabel.font = [UIFont systemFontOfSize:minFontSize];
	minLabel.textAlignment = UITextAlignmentCenter;
	minLabel.text = NSLocalizedString(@"TITLE_ANNOTATIONPROPERTYSET_TEXTDEMO", nil);
	[self.view addSubview:minLabel];
	[minLabel release];
	
	// 3.4 draw max label
	CGRect maxLabelRect = CGRectMake(viewWidth-screenDistance*2-30,
									 minLabelRect.origin.y,
									 40,
									 titleLabelHeight);
	UILabel* maxLabel = [[UILabel alloc] initWithFrame:maxLabelRect];
	maxLabel.tag = TAG_FONTSIZE_MAXA_LABEL;
	maxLabel.backgroundColor = [UIColor clearColor];
	maxLabel.textColor = [UIColor whiteColor];
	maxLabel.font = [UIFont systemFontOfSize:maxFontSize];
	maxLabel.textAlignment = UITextAlignmentCenter;
	maxLabel.text = NSLocalizedString(@"TITLE_ANNOTATIONPROPERTYSET_TEXTDEMO", nil);
	[self.view addSubview:maxLabel];
	[maxLabel release];
	
	// 3.5 draw slider 
	CGRect sliderRect = CGRectMake(screenDistance+40,
								   viewTopHeight+(titleLabelHeight+5)*3+colorButtonHeight*3+propertyDistance*2,
								   viewWidth-(screenDistance+40)*2,
								   titleLabelHeight);
	UISlider* slider = [[UISlider alloc] initWithFrame:sliderRect];
	slider.tag = TAG_FONTSIZE_SLIDER;
	slider.maximumValue = maxFontSize;
	slider.minimumValue = minFontSize;
	
	// lixin 2011/09/14 start
	// NS-AR1005 の対応
	//	slider.value = self.textNotepadFontSize;
	// set slider color
	slider.value = maxFontSize;
	CGRect trackRect = [slider trackRectForBounds:slider.frame];
	
	slider.value = self.textNotepadFontSize;
	
	if (self.textNotepadFontSize > maxFontSize)
	{
		[slider setMinimumTrackImage:[self getSliderRedImageWithSize:trackRect.size]
							forState:UIControlStateNormal];
	}
	
	if (self.textNotepadFontSize < minFontSize)
	{
		[slider setMaximumTrackImage:[self getSliderRedImageWithSize:trackRect.size]
							forState:UIControlStateNormal];
	}
	// lixin 2011/09/14 end
	
	[slider addTarget:self
			   action:@selector(actionOnDragSlider:) 
	 forControlEvents:UIControlEventValueChanged];
	
	// yangjx 2011/09/06 start
	// NS-AR(011/1003/1004) の対応
	[slider setEnabled:hasTextAnnotation];
	// yangjx 2011/09/06 end

	[self.view addSubview:slider];
	[slider release];
}

/* draw for ipad */
- (void) drawBackgroundColorSettingView
{
	COLORREF colorRefSrcColor = 0;
	COLORREF colorRefDstColor = 0;
	
	self.view.backgroundColor = [UIColor lightGrayColor];

	[self transformUIColorToColorRef:self.textNotepadBGColor  
						withColorRef:&colorRefSrcColor];
	
	// draw background color button
	int bgColorCount = [arrayListBackgroundColor count];
	for(int i = 0; i < bgColorCount; i ++)
	{
		CGRect buttonRect = CGRectMake(screenDistance+(screenDistance+ipadButtonSize)*i, 
									   screenDistance, 
									   ipadButtonSize, 
									   ipadButtonSize);
		
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		colorButton.tag = TAG_BACKGROUNDCOLOR_BUTTON_MIN+i;
		colorButton.frame = buttonRect;
		colorButton.backgroundColor = [arrayListBackgroundColor objectAtIndex:i];
		
		// check select
		UIColor* bgColor = (UIColor*)[arrayListBackgroundColor objectAtIndex:i];
		[self transformUIColorToColorRef:bgColor  withColorRef:&colorRefDstColor];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		/*
		if (colorRefSrcColor == colorRefDstColor)
		{
			colorButton.transform = CGAffineTransformMakeScale(buttonSelectTransform, buttonSelectTransform);
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor whiteColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		else
		{
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		*/
		colorButton.layer.cornerRadius = buttonCornerRadius;
		colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
		colorButton.layer.borderWidth = buttonBorderWidth;
		// lixin 2011/09/30 end
        
		[colorButton addTarget:self 
						action:@selector(actionOnTouchBgColorSettingsButton:)
			  forControlEvents:UIControlEventTouchUpInside];
		[self.view addSubview:colorButton];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:NO];
		}
		// lixin 2011/09/30 end
		 
	}
	
	[self.view setFrame:CGRectMake(0, 
								   0, 
								   screenDistance*(bgColorCount+1)
								   +ipadButtonSize*bgColorCount, 
								   screenDistance*2+ipadButtonSize)];
}

- (void) drawTextColorSettingView
{
	COLORREF colorRefSrcColor = 0;
	COLORREF colorRefDstColor = 0;
	
	self.view.backgroundColor = [UIColor lightGrayColor];

	[self transformUIColorToColorRef:self.textNotepadFontColor  
						withColorRef:&colorRefSrcColor];

	// draw font color button
	int fontColorCount = [arrayListFontColor count];
	for(int i = 0; i < fontColorCount; i ++)
	{
		CGRect buttonRect = CGRectMake(screenDistance+(screenDistance+ipadButtonSize)*(i%(fontColorCount/2)), 
									   screenDistance+(ipadButtonSize+screenDistance)*(i/(fontColorCount/2)), 
									   ipadButtonSize, 
									   ipadButtonSize);
		
		UIButton* colorButton = [UIButton buttonWithType:UIButtonTypeCustom];
		colorButton.frame = buttonRect;
		colorButton.tag = TAG_FONTCOLOR_BUTTON_MIN+i;
		colorButton.backgroundColor = [arrayListFontColor objectAtIndex:i];
		
		UIColor* fontColor = (UIColor*)[arrayListFontColor objectAtIndex:i];
		[self transformUIColorToColorRef:fontColor  withColorRef:&colorRefDstColor];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		/*
		if (colorRefSrcColor == colorRefDstColor)
		{
			colorButton.transform = CGAffineTransformMakeScale(buttonSelectTransform, buttonSelectTransform);
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor whiteColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		else
		{
			colorButton.layer.cornerRadius = buttonCornerRadius;
			colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
			colorButton.layer.borderWidth = buttonBorderWidth;
		}
		*/
		colorButton.layer.cornerRadius = buttonCornerRadius;
		colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
		colorButton.layer.borderWidth = buttonBorderWidth;
		// lixin 2011/09/30 end
        
		[colorButton addTarget:self 
						action:@selector(actionOnTouchFontColorSettingsButton:)
			  forControlEvents:UIControlEventTouchUpInside];
		// yangjx 2011/09/06 start
		// NS-AR(011/1003/1004) の対応
		[colorButton setEnabled:hasTextAnnotation];
		// yangjx 2011/09/06 end
		
		[self.view addSubview:colorButton];
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		if (colorRefSrcColor == colorRefDstColor)
		{
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:YES];
		}
		// lixin 2011/09/30 end
	}
	[self.view setFrame:CGRectMake(0, 
								   0, 
								   screenDistance*(fontColorCount/2+1)
								   +ipadButtonSize*fontColorCount/2, 
								   screenDistance*3+ipadButtonSize*2)];
}

- (void) drawTextSizeSettingView
{
	self.view.backgroundColor = [UIColor whiteColor];
	
	int viewWidth = 400;
	// 3.1 draw title
	CGRect fontSizeTitleLabelRect = CGRectMake(screenDistance, 
											   screenDistance,
											   150, 
											   titleLabelHeight);
	UILabel* fontSizeTitleLabel = [[UILabel alloc] initWithFrame:fontSizeTitleLabelRect];
	fontSizeTitleLabel.tag = TAG_FONTSIZE_TITLE_LABEL;
	fontSizeTitleLabel.backgroundColor = [UIColor clearColor];
	fontSizeTitleLabel.text = NSLocalizedString(@"TITLE_TEXTNOTEPAD_FONTSIZE", nil);
	[self.view addSubview:fontSizeTitleLabel];
	[fontSizeTitleLabel release];
	
	// 3.2 draw demo label
	CGRect fontSizeDemoLabelRect = CGRectMake(screenDistance+150, 
											  screenDistance,
											  100, 
											  titleLabelHeight);
	UILabel* fontSizeDemoLabel = [[UILabel alloc] initWithFrame:fontSizeDemoLabelRect];
	fontSizeDemoLabel.tag = TAG_FONTSIZE_DEMO_LABEL;
	fontSizeDemoLabel.backgroundColor = [UIColor clearColor];
	fontSizeDemoLabel.text = [NSString stringWithFormat:@"%2dpt", self.textNotepadFontSize];
	[self.view addSubview:fontSizeDemoLabel];
	[fontSizeDemoLabel release];
	
	// 3.3 draw min label
	CGRect minLabelRect = CGRectMake(screenDistance,
									 screenDistance*2+titleLabelHeight,
									 40,
									 titleLabelHeight);
	UILabel* minLabel = [[UILabel alloc] initWithFrame:minLabelRect];
	minLabel.tag = TAG_FONTSIZE_MINA_LABEL;
	minLabel.backgroundColor = [UIColor clearColor];
	minLabel.font = [UIFont systemFontOfSize:minFontSize];
	minLabel.textAlignment = UITextAlignmentCenter;
	minLabel.text = NSLocalizedString(@"TITLE_ANNOTATIONPROPERTYSET_TEXTDEMO", nil);
	[self.view addSubview:minLabel];
	[minLabel release];
	
	// 3.4 draw max label
	CGRect maxLabelRect = CGRectMake(viewWidth-screenDistance*2-30,
									 screenDistance*2+titleLabelHeight,
									 40,
									 titleLabelHeight);
	UILabel* maxLabel = [[UILabel alloc] initWithFrame:maxLabelRect];
	maxLabel.tag = TAG_FONTSIZE_MAXA_LABEL;
	maxLabel.backgroundColor = [UIColor clearColor];
	maxLabel.font = [UIFont systemFontOfSize:maxFontSize];
	maxLabel.textAlignment = UITextAlignmentCenter;
	maxLabel.text = NSLocalizedString(@"TITLE_ANNOTATIONPROPERTYSET_TEXTDEMO", nil);
	[self.view addSubview:maxLabel];
	[maxLabel release];
	
	// 3.5 draw slider 
	CGRect sliderRect = CGRectMake(screenDistance+40,
								   screenDistance*2+titleLabelHeight,
								   viewWidth-(screenDistance+40)*2,
								   titleLabelHeight);
	UISlider* slider = [[UISlider alloc] initWithFrame:sliderRect];
	slider.tag = TAG_FONTSIZE_SLIDER;
	slider.maximumValue = maxFontSize;
	slider.minimumValue = minFontSize;
	// lixin 2011/09/14 start
	// NS-AR1005 の対応
	//	slider.value = self.textNotepadFontSize;
	// set slider color
	slider.value = maxFontSize;
	CGRect trackRect = [slider trackRectForBounds:slider.frame];
	
	slider.value = self.textNotepadFontSize;
	
	if (self.textNotepadFontSize > maxFontSize)
	{
		[slider setMinimumTrackImage:[self getSliderRedImageWithSize:trackRect.size]
							forState:UIControlStateNormal];
	}
	
	if (self.textNotepadFontSize < minFontSize)
	{
		[slider setMaximumTrackImage:[self getSliderRedImageWithSize:trackRect.size]
							forState:UIControlStateNormal];
	}
	// lixin 2011/09/14 end

	[slider addTarget:self
			   action:@selector(actionOnDragSlider:) 
	 forControlEvents:UIControlEventValueChanged];
	
	[slider addTarget:self
			   action:@selector(actionOnExitDragSlider:)
	 forControlEvents:UIControlEventTouchUpInside];
	
	[slider addTarget:self
			   action:@selector(actionOnExitDragSlider:)
	 forControlEvents:UIControlEventTouchUpOutside];
	
	// yangjx 2011/09/06 start
	// NS-AR(011/1003/1004) の対応
	[slider setEnabled:hasTextAnnotation];
	// yangjx 2011/09/06 end
	
	[self.view addSubview:slider];
	[slider release];
	
	[self.view setFrame:CGRectMake(0, 0, viewWidth, 110)];
	
}

- (void) initBackButtonOnNavigationBar
{
	self.title = NSLocalizedString(@"TITLE_TEXTNOTEPAD_PROPERTYTITLE", nil);
	self.view.backgroundColor = [UIColor darkGrayColor];

	// init back button.
	UIButton* backButton = [UIButton buttonWithType:(UIButtonType)101];
    [backButton setTitle:NSLocalizedString(@"BUTTON_TITLE_BACK", nil) 
				forState:UIControlStateNormal];
    [backButton addTarget:self 
				   action:@selector(actionTouchBackButtonOnNavigationBar) 
		 forControlEvents:UIControlEventTouchDown];
    UIBarButtonItem* backButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backButton];
    self.navigationItem.leftBarButtonItem = backButtonItem;
    [backButtonItem release];
		
	// init navigation controller
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	self.navigationController.navigationBarHidden = NO;
}

- (void) resetViewFrame
{
	// start
	int viewTopHeight = [self getTopDistance];
	int viewWidth = [self getViewWidth];
	int propertyDistance = [self getPropertyDistance];
	CGFloat buttonWidth = (viewWidth-screenDistance*2)/8.0;
	
	// 1. draw background color property setting view
	// 1.1 draw title
	CGRect bgColorTitleLabelRect = CGRectZero;
	UIView* bgColorTitleLabel = [self.view viewWithTag:TAG_BACKGROUNDCOLOR_TITLE_LABEL];
	if (bgColorTitleLabel != nil)
	{
		bgColorTitleLabelRect = bgColorTitleLabel.frame;
		bgColorTitleLabelRect.origin.y = viewTopHeight;
		[bgColorTitleLabel setFrame:bgColorTitleLabelRect];
	}
	
	// 1.2 draw background color button
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	COLORREF colorRefSrcColor = 0;
    COLORREF colorRefDstColor = 0;
    
	[self transformUIColorToColorRef:self.textNotepadBGColor  
						withColorRef:&colorRefSrcColor];
	// lixin 2011/09/30 end
    
	int bgColorCount = [arrayListBackgroundColor count];
	for(int i = 0; i < bgColorCount; i ++)
	{
		UIView* colorButton = [self.view viewWithTag:TAG_BACKGROUNDCOLOR_BUTTON_MIN+i];
		if (colorButton != nil)
		{
			CGRect buttonRect = colorButton.frame;
			buttonRect.origin.x = screenDistance+buttonWidth*i;
			buttonRect.origin.y = bgColorTitleLabelRect.origin.y+titleLabelHeight+5;
			buttonRect.size.width = buttonWidth;
			[colorButton setFrame:buttonRect];
		}
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		UIColor* color_ = (UIColor*)[arrayListBackgroundColor objectAtIndex:i];
		[self transformUIColorToColorRef:color_  withColorRef:&colorRefDstColor];
		if (colorRefSrcColor == colorRefDstColor) {
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:NO];
		}
		// lixin 2011/09/30 end
	}
	
	// 2. draw font color property setting view
	// 2.1 draw title
	UIView* fontColorTitleLabel = [self.view viewWithTag:TAG_FONTCOLOR_TITLE_LABEL];
	if (fontColorTitleLabel != nil)
	{
		CGRect fontColorTitleLabelRect = fontColorTitleLabel.frame;
		fontColorTitleLabelRect.origin.y = viewTopHeight+titleLabelHeight+5+colorButtonHeight+propertyDistance;
		[fontColorTitleLabel setFrame:fontColorTitleLabelRect];
	}
	
	// 2.2 draw font color button
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	[self transformUIColorToColorRef:self.textNotepadFontColor 
						withColorRef:&colorRefSrcColor];
	// lixin 2011/09/30 end
	
	int fontColorCount = [arrayListFontColor count];
	for(int i = 0; i < fontColorCount; i ++)
	{
		UIView* colorButton = [self.view viewWithTag:TAG_FONTCOLOR_BUTTON_MIN+i];
		if (colorButton != nil)
		{
			CGRect buttonRect = colorButton.frame;
			buttonRect.origin.x = screenDistance+buttonWidth*(i%(fontColorCount/2));
			buttonRect.origin.y = viewTopHeight+(titleLabelHeight+5)*2+colorButtonHeight+propertyDistance
			                      +colorButtonHeight*(i/(fontColorCount/2));
			buttonRect.size.width = buttonWidth;
			[colorButton setFrame:buttonRect];
			
		}
		
		// lixin 2011/09/30 start 
		// 選択枠の追加 の対応
		// check select
		UIColor* fontColor = (UIColor*)[arrayListFontColor objectAtIndex:i];
		[self transformUIColorToColorRef:fontColor  withColorRef:&colorRefDstColor];
        if (colorRefSrcColor == colorRefDstColor) {
            [self selectColorButtonWithButtonFrame:colorButton.frame withIsFont:YES];
		}
		// lixin 2011/09/30 end
	}
	
	// 3. draw font size property setting
	// 3.1 draw title
	CGRect fontSizeTitleLabelRect = CGRectZero;
	UIView* fontSizeTitleLabel = [self.view viewWithTag:TAG_FONTSIZE_TITLE_LABEL];
	if (fontSizeTitleLabel != nil)
	{
		fontSizeTitleLabelRect = fontSizeTitleLabel.frame;
		fontSizeTitleLabelRect.origin.y = viewTopHeight+(titleLabelHeight+5)*2+colorButtonHeight*3+propertyDistance*2;
		[fontSizeTitleLabel setFrame:fontSizeTitleLabelRect];
	}
	
	// 3.2 draw demo label
	UIView* fontSizeDemoLabel = [self.view viewWithTag:TAG_FONTSIZE_DEMO_LABEL];
	if (fontSizeDemoLabel != nil)
	{
		CGRect fontSizeDemoLabelRect = fontSizeDemoLabel.frame;
		fontSizeDemoLabelRect.origin.y = fontSizeTitleLabelRect.origin.y;
		[fontSizeDemoLabel setFrame:fontSizeDemoLabelRect];
	}
	
	// 3.3 draw min label
	CGRect minLabelRect = CGRectZero;
	UIView* minLabel = [self.view viewWithTag:TAG_FONTSIZE_MINA_LABEL];
	if (minLabel != nil)
	{
		minLabelRect = minLabel.frame;
		minLabelRect.origin.y = viewTopHeight+(titleLabelHeight+5)*3+colorButtonHeight*3+propertyDistance*2;
		[minLabel setFrame:minLabelRect];
	}
	
	// 3.4 draw max label
	UIView* maxLabel = [self.view viewWithTag:TAG_FONTSIZE_MAXA_LABEL];
	if (maxLabel != nil)
	{
		CGRect maxLabelRect = maxLabel.frame;
		maxLabelRect.origin.x = viewWidth-screenDistance*2-30;
		maxLabelRect.origin.y = minLabelRect.origin.y;
		[maxLabel setFrame:maxLabelRect];
	}
	
	// 3.5 draw slider 
	UIView* slider = [self.view viewWithTag:TAG_FONTSIZE_SLIDER];
	if (slider != nil)
	{
		CGRect sliderRect = slider.frame;
		sliderRect.origin.y =  viewTopHeight+(titleLabelHeight+5)*3
		                       +colorButtonHeight*3
		                       +propertyDistance*2;
		sliderRect.size.width = viewWidth-(screenDistance+40)*2;
		[slider setFrame:sliderRect];
	}
	
	[self.view setNeedsDisplay];
}

#pragma mark -
#pragma mark action

- (void) actionTouchBackButtonOnNavigationBar
{
	[delegate updateTextNotepadAnnPropertyWithNotepadColor:self.textNotepadBGColor  
                                             withFontColor:self.textNotepadFontColor 
                                              withFontSize:self.textNotepadFontSize];

	[self.parentViewController dismissModalViewControllerAnimated:YES];
}

- (void) actionOnTouchBgColorSettingsButton:(id) sender
{
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	/*
	// set Background color border width = 0
	int bgColorButtonCount = [arrayListBackgroundColor count];
	for (int i = 0; i < bgColorButtonCount; i++)
	{
		UIButton* colorButton = (UIButton*)[self.view viewWithTag:TAG_BACKGROUNDCOLOR_BUTTON_MIN+i];
		if (colorButton != nil)
		{
			colorButton.transform = CGAffineTransformMakeScale(1.0, 1.0);
			if (deviceIsiPad_ == YES)
			{
				colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
			}
			else
			{
				colorButton.layer.borderWidth = 0;
				colorButton.layer.cornerRadius = 0;
			}
		}
	}
	
	// set select line color border with = buttonBorderWidth
	UIButton* selectColorButton = (UIButton*)sender;
	//selectColorButton.transform = CGAffineTransformMakeScale(buttonSelectTransform, buttonSelectTransform);
	selectColorButton.layer.cornerRadius = buttonCornerRadius;
	selectColorButton.layer.borderColor = [UIColor whiteColor].CGColor;
	selectColorButton.layer.borderWidth = buttonBorderWidth;
	*/
    
	UIButton* selectColorButton = (UIButton*)sender;
    [self selectColorButtonWithButtonFrame:selectColorButton.frame withIsFont:NO];
	// lixin 2011/09/30 end
    
	self.textNotepadBGColor = selectColorButton.backgroundColor;
    
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	//[self.view bringSubviewToFront:selectColorButton];
	// lixin 2011/09/30 end
    
	[self.view setNeedsDisplay];
	
	if (deviceIsiPad_ == YES)
	{
		[delegate updateTextNotepadAnnPropertyForiPadWithNotepadColor:self.textNotepadBGColor
														withFontColor:self.textNotepadFontColor
														 withFontSize:self.textNotepadFontSize];
	}
}

- (void) actionOnTouchFontColorSettingsButton:(id) sender
{
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	/*
	int fontColorButtonCount = [arrayListFontColor count];
	for (int i = 0; i < fontColorButtonCount; i++)
	{
		UIButton* colorButton = (UIButton*)[self.view viewWithTag:TAG_FONTCOLOR_BUTTON_MIN+i];
		if (colorButton != nil)
		{
			colorButton.transform = CGAffineTransformMakeScale(1.0, 1.0);
			if (deviceIsiPad_ == YES)
			{
				colorButton.layer.borderColor = [UIColor darkGrayColor].CGColor;
			}
			else
			{
				colorButton.layer.borderWidth = 0;
				colorButton.layer.cornerRadius = 0;
			}
		}
	}
	
	// set select line color border with = buttonBorderWidth
	UIButton* selectColorButton = (UIButton*)sender;
	selectColorButton.layer.cornerRadius = buttonCornerRadius;
	selectColorButton.layer.borderColor = [UIColor whiteColor].CGColor;
	selectColorButton.layer.borderWidth = buttonBorderWidth;
	 */
	UIButton* selectColorButton = (UIButton*)sender;
     [self selectColorButtonWithButtonFrame:selectColorButton.frame withIsFont:YES];
	// lixin 2011/09/30 end
    
	self.textNotepadFontColor = selectColorButton.backgroundColor;
    
	// lixin 2011/09/30 start 
	// 選択枠の追加 の対応
	//[self.view bringSubviewToFront:selectColorButton];
	// lixin 2011/09/30 end
    
	[self.view setNeedsDisplay];
	
	if (deviceIsiPad_ == YES)
	{
		[delegate updateTextNotepadAnnPropertyForiPadWithNotepadColor:self.textNotepadBGColor
														withFontColor:self.textNotepadFontColor
														 withFontSize:self.textNotepadFontSize];
	}
}

- (IBAction) actionOnDragSlider:(id)sender
{
	UISlider* slider = (UISlider*)sender;
	self.textNotepadFontSize = slider.value;
	
	// change slider frame label
	UILabel* demoLabel = (UILabel*)[self.view viewWithTag:TAG_FONTSIZE_DEMO_LABEL];
	if (demoLabel != nil)
	{
		demoLabel.text = [NSString stringWithFormat:@"%2dpt", self.textNotepadFontSize];
	}
	
	// lixin 2011/09/14 start
	// NS-AR1005 の対応
	[slider setMinimumTrackImage:nil
						forState:UIControlStateNormal];
	[slider setMaximumTrackImage:nil
						forState:UIControlStateNormal];
	// lixin 2011/09/14 end
}

- (IBAction) actionOnExitDragSlider:(id)sender
{
	if (deviceIsiPad_ == YES)
	{
		[delegate updateTextNotepadAnnPropertyForiPadWithNotepadColor:self.textNotepadBGColor
														withFontColor:self.textNotepadFontColor
														 withFontSize:self.textNotepadFontSize];
	}
}

#pragma mark -
#pragma mark function
- (BOOL) UIDeviceIsPortrait
{
	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)) {
		return YES;
	} else {
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

// lixin 2011/09/30 start 
// 選択枠の追加 の対応
- (void) selectColorButtonWithButtonFrame:(CGRect)rect withIsFont:(BOOL)isFont;
{
    CGRect ghostViewRect = CGRectZero;
    if (deviceIsiPad_ == YES) {
		ghostViewRect = rect;
	} else {
		ghostViewRect = CGRectMake(rect.origin.x - 0.5, 
                                   rect.origin.y, 
                                   rect.size.width + 1, 
                                   rect.size.height);
	}
    
    if (isFont == YES) {
        fontColorGhostView_.frame = ghostViewRect;
        [self.view addSubview:fontColorGhostView_];
        [self.view bringSubviewToFront:fontColorGhostView_];
    } else {
        noteColorGhostView_.frame = ghostViewRect;
        [self.view addSubview:noteColorGhostView_];
        [self.view bringSubviewToFront:noteColorGhostView_];
    }
}

- (NSString*) getSelectColorImageName
{
	if (deviceIsiPad_ == YES) {
		return SELECTCOLOR_IMAGE_IPAD;
	} else if ([self UIDeviceIsPortrait] == YES) {
		return SELECTCOLOR_IMAGE_PORTRAIT;
	} else {
		return SELECTCOLOR_IMAGE_LANDSCAPE;
	}
}
// lixin 2011/09/30 end

// lixin 2011/09/14 start
// NS-AR1005 の対応
- (UIImage*) getSliderRedImageWithSize:(CGSize)size
{	
	CGRect imageRect = CGRectMake(0, 0, size.width, size.height);
	
	UIGraphicsBeginImageContext(imageRect.size);
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	CGContextSaveGState(context);
	CGContextClipToRect(context, imageRect);
	
	CGColorSpaceRef rgb = CGColorSpaceCreateDeviceRGB();
	
	CGFloat colors[16];
	
	int lineCount = 16/4;
	
	for (int i=0; i<lineCount; i++)
	{
		colors[i*4]   = 1;
		colors[i*4+1] = (i*50)/255.0;
		colors[i*4+2] = (i*50)/255.0;
		colors[i*4+3] = 1.00;
	}
	
	CGGradientRef fillGradient = CGGradientCreateWithColorComponents(rgb, colors, NULL, 3);
	
	CGColorSpaceRelease(rgb);
	CGContextDrawLinearGradient(context, 
								fillGradient, 
								CGPointMake(imageRect.origin.x, imageRect.origin.y), 
								CGPointMake(imageRect.origin.x, imageRect.origin.y + imageRect.size.height), 
								kCGGradientDrawsAfterEndLocation);
	
	CGContextRestoreGState(context);
	
	UIImage* image = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	
	CGGradientRelease(fillGradient);
	
	return image;
}
// lixin 2011/09/14 end

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
#pragma mark view delegate
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// TSET
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
	if (!Utility::UIDeviceIsiPad())
	{
		[self resetViewFrame];
	}
}

#pragma mark -
#pragma mark Memory 
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)dealloc {
	if (arrayListBackgroundColor != nil)
	{
		[arrayListBackgroundColor release];
	}
	
	if (arrayListFontColor != nil)
	{
		[arrayListFontColor release];
	}
	
	self.textNotepadBGColor = nil;
	self.textNotepadFontColor = nil;
    
    // lixin 2011/09/30 start 
    // 選択枠の追加 の対応
    [noteColorGhostView_ release];
    [fontColorGhostView_ release];
    // lixin 2011/09/30 end
	
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

