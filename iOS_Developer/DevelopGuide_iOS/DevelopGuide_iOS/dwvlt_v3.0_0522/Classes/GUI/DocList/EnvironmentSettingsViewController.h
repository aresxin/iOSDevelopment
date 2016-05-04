//
//  EnvironmentSettingsViewController.h
//  DWViewer
//
//  Created by sun on 10-10-22.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
// FileSort の対応 start
#import "FileSortSettingsViewController.h"
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
#import "ScaleSpecifyViewController.h" 
// 「拡大率指定の追加」の対応 end

//add by yangjx 0613 start
#import "DocumentSettingsManager.h"
//add by yangjx 0613 end

// wangpp 2012.3.29 start
// login
#import "DWViewerAppDelegate.h"
#import "DWLoginAnnPropertySettingsController.h"
// wangpp 2012.3.29 end

@protocol EnvironmentSettingsViewDelegate;
// FileSort の対応 start
//@interface EnvironmentSettingsViewController : UITableViewController{

//Trash file Del add by yangjx 0613 start
@class DocumentSettingsManager;
//Trash file Del add by yangjx 0613 end

// 「拡大率指定の追加」の対応 start
//@interface EnvironmentSettingsViewController : UITableViewController<FileSortSettingsViewDelegate>{
@interface EnvironmentSettingsViewController : UITableViewController
											 <
											  FileSortSettingsViewDelegate,
											  ScaleSpecifyViewDelegate,
											  // wangpp 2012.4.13 start
											  // login
											  DWLoginAnnotationPropertySettingsDelegate
											  // wangpp 2012.4.13 end
											  >
{    
// 「拡大率指定の追加」の対応 end
    
// FileSort の対応 end	
	id <EnvironmentSettingsViewDelegate> delegate;
	UISwitch *buttonSwitch;
	BOOL keepDocumentStatus;
	
	// FileSort の対応 start
	int fileSortItemIndex;
	int fileSortModeIndex;
	// FileSort の対応 end
    
    // 「拡大率指定の追加」の対応 start
    int specifyScaleModeIndex;
    int specifyScaleValue;
    // 「拡大率指定の追加」の対応 end
	
	//Trash file Del add by yangjx 0613 start
	DocumentSettingsManager *documentSettingsMgr;
	//Trash file Del add by yangjx 0613 end
}
@property (nonatomic, assign) id <EnvironmentSettingsViewDelegate> delegate;
@property BOOL keepDocumentStatus;
// FileSort の対応 start
@property int fileSortItemIndex;
@property int fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@property int specifyScaleModeIndex;
@property int specifyScaleValue;
// 「拡大率指定の追加」の対応 end

- (void) actionSwitchButtonValueChanged;
- (void) actionBackToMenu;

// liuqw 20110623 start
// AR NO.17869 の対応
- (BOOL) isTrashEmpty;
// liuqw 20110623 end

@end

@protocol EnvironmentSettingsViewDelegate <NSObject>
@optional
- (void)didSwitchButtonValueChanged:(EnvironmentSettingsViewController *)sender;
@end
