//
//  DWFreehandAnnPropertySettingsController.h
//  DWViewer
//
//  Created by liuqw on 11-8-25.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "Utility.h"
typedef unsigned long COLORREF;

typedef enum
{
	UIPropertyTypeAll,
	UIPropertyTypeLineColor,
	UIPropertyTypeLineSize,
	
	// wangpp 2012.2.29 start
	// freehand transparent
	UIPropertyTypeTransparent
	// wangpp 2012.2.29 end
	
} UIPropertyType;


// DWLineSizeButton
// -------------------------------
@interface DWLineSizeButton : UIButton
{
	int lineSize_;
}
@property  (nonatomic, assign) int lineSize;

- (id)initWithLineSize:(int)lineSize;
@end


// DWFreehandAnnPropertySettingsController
// -------------------------------
@protocol DWFreeHandAnnPropertySettingsDelegate <NSObject>
@optional

// wangpp 2012.2.29 start
// freehand transparent
/*
 - (void) updateFreehandAnnPropertyWithLineColor:(UIColor*)color withLineSize:(int)size;
 - (void) updateFreehandAnnPropertyForiPadWithLineColor:(UIColor*)color withLineSize:(int)size;
 */
- (void) updateFreehandAnnPropertyWithLineColor:(UIColor*)color withLineSize:(int)size withLineTrans:(BOOL)transparent;
- (void) updateFreehandAnnPropertyForiPadWithLineColor:(UIColor*)color withLineSize:(int)size withLineTrans:(BOOL)transparent;
// wangpp 2012.2.29 end

@end

@interface DWFreehandAnnPropertySettingsController : UIViewController <UITableViewDelegate, UITableViewDataSource> 
{
    id <DWFreeHandAnnPropertySettingsDelegate> delegate;
    
	NSArray*        lineColorArray_;
	NSArray*        lineSizeArray_;
	NSArray*        lineSizeButtonImageArray_;
	
	UIColor*        freehandLineColor_;
	int             freehandLineSize_;
	
	// wangpp 2012.2.29 start
	// freehand transparent
	BOOL			freehandTransparent_;
	// wangpp 2012.2.29 end
	
	BOOL            deviceIsiPad_;
	UIPropertyType  propertyType_;
    
    // 選択枠の追加 の対応
    UIImageView*    selectGhostView_;
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	UIActivityIndicatorView*	activeIndicator_;
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// 2012.02.14 M.Chikyu start.
	UIInterfaceOrientation orientation_;
	// 2012.02.14 M.Chikyu end.
}
@property (nonatomic, assign) id <DWFreeHandAnnPropertySettingsDelegate> delegate;
@property (nonatomic, retain) UIColor* freehandLineColor;
@property (nonatomic, assign) int      freehandLineSize;

// wangpp 2012.2.29 start
// freehand transparent
@property (nonatomic,assign) BOOL freehandTransparent;
// wangpp 2012.2.29 end

// 2012.02.14 M.Chikyu start.
/*
- (id) initWithLineColor:(UIColor*)lineColor 
            withLineSize:(int)lineSize;
 */

// wangpp 2012.2.29 start
// freehand transparent
/*
- (id) initWithLineColor:(UIColor*)lineColor 
            withLineSize:(int)lineSize
		 withOrientation:(UIInterfaceOrientation)orientation;
 */
// 2012.02.14 M.Chikyu end.
- (id) initWithLineColor:(UIColor*)lineColor 
            withLineSize:(int)lineSize
	   withIsTransparent:(BOOL)transparent
		 withOrientation:(UIInterfaceOrientation)orientation;
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

- (void) initNavigationController;
- (void) initPropertySettingView;
- (void) initColorPropertySettingView;
- (void) initSizePropertySettingView;

// wangpp 2012.2.29 start
// freehand transparent
- (void) initTransparentSettingView;
// wangpp 2012.2.29 end

- (void) resetPropertySettingViewFrame;

- (int) getViewWidth;
- (int) getViewHeight;
- (int) getPropertyDistance;
- (int) getTopDistance;

// wangpp 2012.3.9 start
// freehand transparent 
- (int) getTableViewHeight;
// wangpp 2012.3.9 end

// 選択枠の追加 の対応
- (void) selectColorButtonWithButtonFrame:(CGRect)rect;
- (NSString*) getSelectColorImageName;

- (BOOL) UIDeviceIsPortrait;

- (void) transformUIColorToColorRef:(UIColor *)color 
					   withColorRef:(COLORREF *)colorRef;

- (IBAction) actionTouchBackButton:(id)sender;
- (IBAction) actionTouchLineColorButton:(id)sender;	
- (IBAction) actionTouchLineSizeButton:(id)sender;

// wangpp 2012.2.29 start 
// freehand tranparent
- (IBAction) actionTouchLineTransButton:(id)sender;
// wangpp 2012.2.29 end

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) displayIndicator;
- (void) hideIndicator;
// 2012.02.01(Ver2.1 New) M.Chikyu


@end