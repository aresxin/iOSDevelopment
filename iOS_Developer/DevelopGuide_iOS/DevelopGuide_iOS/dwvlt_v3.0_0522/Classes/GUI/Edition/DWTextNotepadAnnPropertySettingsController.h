//
//  DWIphoneTextnotepadPropertyController.h
//  DWViewer
//
//  Created by zhaijie on 11-8-24.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

typedef unsigned long COLORREF;
typedef enum  {
	UINotepadPropertyTypeAll,
	UINotepadPropertyTypeBackgroundColor,
	UINotepadPropertyTypeTextColor,
	UINotepadPropertyTypeTextSize
} UINotepadPropertyType;

@protocol DWTextNotepadAnnPropertySettingsDelegate <NSObject>

@optional
- (void) updateTextNotepadAnnPropertyWithNotepadColor:(UIColor*)bgColor 
                                        withFontColor:(UIColor*)fontColor
                                             withFontSize:(int)size;
- (void) updateTextNotepadAnnPropertyForiPadWithNotepadColor:(UIColor*)bgColor 
											   withFontColor:(UIColor*)fontColor
												withFontSize:(int)size;
                                        
@end


@interface DWTextNotepadAnnPropertySettingsController : UIViewController {
	id <DWTextNotepadAnnPropertySettingsDelegate> delegate;
	
	BOOL            deviceIsiPad_;
	UINotepadPropertyType propertyType_;
	
	NSArray *arrayListBackgroundColor;
	NSArray *arrayListFontColor;
	
	// yangjx 2011/09/06 start
	// NS-AR(011/1003/1004) の対応
	BOOL            hasTextAnnotation;
	// yangjx 2011/09/06 end
    
    // yangjx 2011/09/16 start
    // NS-AR(011/1003/1004) の対応
    int             textCount;
    // yangjx 2011/09/16 end
    
    // lixin 2011/09/30 start 
    // 選択枠の追加 の対応
    UIImageView*    noteColorGhostView_;
    UIImageView*    fontColorGhostView_;
    // lixin 2011/09/30 end
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	UIActivityIndicatorView*	activeIndicator_;
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// 2012.02.14 M.Chikyu start.
	UIInterfaceOrientation orientation_;
	// 2012.02.14 M.Chikyu end.
}
@property (nonatomic, assign) id <DWTextNotepadAnnPropertySettingsDelegate> delegate;
@property (nonatomic, retain) UIColor *textNotepadBGColor;
@property (nonatomic, retain) UIColor *textNotepadFontColor;
@property (nonatomic, assign) int textNotepadFontSize;
// yangjx 2011/09/06 start
// NS-AR(011/1003/1004) の対応
@property BOOL    hasTextAnnotation;
// yangjx 2011/09/06 end

// yangjx 2011/09/06 start
// NS-AR(011/1003/1004) の対応
/*
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize;
*/
/*
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
				 withisHasText:(BOOL)isHasText;
*/ 

// 2012.02.14 M.Chikyu start.
/*
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
				 withisHasText:(BOOL)isHasText
                 withTextCount:(int)textCount_;
 */
- (id) initWithBackgroundColor:(UIColor*)backgroundColor 
				 withTextColor:(UIColor*)textColor 
				  withTextSize:(int)textSize
				 withisHasText:(BOOL)isHasText
                 withTextCount:(int)textCount_
			   withOrientation:(UIInterfaceOrientation)orientation;
// 2012.02.14 M.Chikyu end.

/*old
- (id) initForiPadWithPropertyType:(UINotepadPropertyType)type
			   withBackgroundColor:(UIColor*)backgroundColor 
					 withTextColor:(UIColor*)textColor 
					  withTextSize:(int)textSize;
*/
- (id) initForiPadWithPropertyType:(UINotepadPropertyType)type
			   withBackgroundColor:(UIColor*)backgroundColor 
					 withTextColor:(UIColor*)textColor 
					  withTextSize:(int)textSize
					 withisHasText:(BOOL)isHasText;
// yangjx 2011/09/06 end
- (void) drawViewItems;
- (void) initBackButtonOnNavigationBar;

/* draw for ipad */
- (void) drawBackgroundColorSettingView;
- (void) drawTextColorSettingView;
- (void) drawTextSizeSettingView;

/* action */
- (void) actionTouchBackButtonOnNavigationBar;
- (void) actionOnTouchBgColorSettingsButton:(id) sender;
- (void) actionOnTouchFontColorSettingsButton:(id) sender;
- (IBAction) actionOnDragSlider:(id)sender;
- (IBAction) actionOnExitDragSlider:(id)sender;

- (void) resetViewFrame;

- (BOOL) UIDeviceIsPortrait;

- (void) transformUIColorToColorRef:(UIColor *)color 
					   withColorRef:(COLORREF *)colorRef;

- (int) getViewWidth;
- (int) getPropertyDistance;
- (int) getTopDistance;

// lixin 2011/09/30 start 
// 選択枠の追加 の対応
- (void) selectColorButtonWithButtonFrame:(CGRect)rect withIsFont:(BOOL)isFont;
- (NSString*) getSelectColorImageName;
// lixin 2011/09/30 end

// lixin 2011/09/14 start
// NS-AR1005 の対応
- (UIImage*)getSliderRedImageWithSize:(CGSize)size;
// lixin 2011/09/14 end


// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) displayIndicator;
- (void) hideIndicator;
// 2012.02.01(Ver2.1 New) M.Chikyu

@end

