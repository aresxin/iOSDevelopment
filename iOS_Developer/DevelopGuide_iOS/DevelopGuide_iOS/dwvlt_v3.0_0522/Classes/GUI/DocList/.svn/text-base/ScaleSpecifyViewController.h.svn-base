//
//  ScaleSpecifyViewController.h
//  DWViewer
//
//  Created by liuqw on 11-6-9.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ScaleSpecifyViewDelegate;

@interface ScaleSpecifyViewController : UITableViewController<UIAlertViewDelegate, UITextFieldDelegate> {
    int specifyScaleMode;
    int fixedScale;
    
    UIAlertView *alertInputScale;
    UITextField *fieldInputScale;
    UILabel     *labelScalePercent;
}
@property (nonatomic, assign) id <ScaleSpecifyViewDelegate> delegate;
@property int specifyScaleMode;
@property int fixedScale;

@property (nonatomic, retain) UIAlertView *alertInputScale;
@property (nonatomic, retain) UITextField *fieldInputScale;
@property (nonatomic, retain) UILabel     *labelScalePercent;

- (id)initWithStyle:(UITableViewStyle)style withSpecifyMode:(int)mode withFixedScale:(int)scale;

- (void) showZoomScaleInputView;
- (void) setInputScaleFieldViewPosition;
- (void) setInputScaleFieldViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation;
- (void) inputZoomScaleWithAlertView:(UIAlertView*)alertView;
- (BOOL) UIDeviceIsPortrait;

@end

@protocol ScaleSpecifyViewDelegate <NSObject>
@optional
- (void)didSpecifyScaleModeChanged:(ScaleSpecifyViewController *)sender;
@end