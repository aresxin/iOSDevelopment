//
//  DirectoryViewController.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EnvironmentSettingsViewController.h"
// アプリ情報機能の追加 の対応 start 
#import "AboutDocuworksViewController.h" 
// アプリ情報機能の追加 の対応 end 
#import "DocumentViewController.h"
#import "XdwAttributeParser.h"

// xuxinjun 2012.03.23 start
// 保護文書の対応
#import "DWAuthenticationManager.h"
#import "DWFileInfo.h"
// xuxinjun 2012.03.23 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
@interface DWMTAAssociationInfo : NSObject
@property (nonatomic, retain) NSString* backButtonTitle;
@property (nonatomic, retain) NSString* pasteboard;
@property (nonatomic, retain) NSString* folderName;
@property (nonatomic, retain) NSString* appName;
@property int pageIndex;
@end
// xuxinjun 2012.03.23 end

@class DocumentViewController;
@class EnvironmentSettingsViewController;
@class DocumentSettingsManager;
//「文書情報ボタン」の動作 start
@class DocumentSummaryManager;
//「文書情報ボタン」の動作 end
@interface DirectoryViewController : UITableViewController<UIAlertViewDelegate,
														   EnvironmentSettingsViewDelegate,
                                                           DocumentViewDelegate,
														   UITextFieldDelegate,
                                                           MFMailComposeViewControllerDelegate>
{
	// 1. common.
	DocumentSettingsManager				*documentSettingsMgr;
	//「文書情報ボタン」の動作 start
    DocumentSummaryManager				*documentSummaryMgr;
	//「文書情報ボタン」の動作 end
	UIViewController					*activeViewController;
	UINavigationController				*navigateController;
    
	
	// 2. document list about.
	// FileSort の対応 start
	NSMutableArray						*fileInfos;
	// FileSort の対応 end
	
	// tongtx 20110920 start
	// NS-AR029 の対応
	BOOL								isUpdateFileNameFromDetailView;
	// tongtx 20110920 end
	
	// 3. about delete file
	NSIndexPath							*deleteIndexPath;
	NSString							*deleteFilePath;
	
	
	// 4. toolbar items about. 
	// 4.1 for environment settings.
	EnvironmentSettingsViewController	*environmentSettingsController;
	
	// 4.1.1 keep status
	BOOL								keepDocumentStatus;
	// liuqw 20110628 start
    // AR NO.17871 の対応
	int									selectCellIndex;
	// liuqw 20110628 end
	
	// 4.2.2 sort about.
	// FileSort の対応 start
	int									fileSortItemIndex;
	int									fileSortModeIndex;
	// FileSort の対応 end
	
	// 4.3.3 scale about.
	// 「拡大率指定の追加」の対応 start
	int									specifyScaleModeIndex;
    int									specifyScaleValue;
	// 「拡大率指定の追加」の対応 end
	
	// 4.2 for Docuworks info view .
	// アプリ情報機能の追加 の対応 start 
    AboutDocuworksViewController		*aboutDocuworksController;
	UINavigationController				*aboutNavigateController;
	// アプリ情報機能の追加 の対応 end
	
	// 4.3 edit button item about.
	// File Multiple Del by Yangjx 0603 start
	BOOL								isEditMode;
	NSMutableArray						*selectFileInfos;
    BOOL								isBecomeActiveFromBackground;
	// File Multiple Del by Yangjx 0603 end

	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	DWAuthenticationManager	*authManager_;
	NSString				*authFullPath_;
	NSString				*authFileName_;
	int						actionType_;
	UINavigationController	*navController_;
	DWMTAAssociationInfo	*otherInfo_;
	UITextField				*fieldTextInputPassword_;
	UIAlertView				*alertViewInputPassword_;
	// xuxinjun 2012.03.23 end

}
@property BOOL keepDocumentStatus;
// FileSort の対応 start
@property int fileSortItemIndex;
@property int fileSortModeIndex;
//@property (nonatomic, retain) NSMutableArray *fileNames;
@property (nonatomic, retain) NSMutableArray *fileInfos;
// FileSort の対応 end
// 「拡大率指定の追加」の対応 start
@property int specifyScaleModeIndex;
@property int specifyScaleValue;
// 「拡大率指定の追加」の対応 end
//File Multiple Del by Yangjx 0603 start
@property (nonatomic, retain) NSMutableArray *selectFileInfos;
@property BOOL isBecomeActiveFromBackground;
//File Multiple Del by Yangjx 0603 end
// yangjx 20110706 start
// AR 17898 の対応
@property BOOL isEditMode;
// yangjx 20110706 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
@property (nonatomic, retain) DWAuthenticationManager *authenticationManager;
@property (nonatomic, retain) NSString *authFullPath;
@property (nonatomic, retain) NSString *authFileName;
@property (nonatomic, retain) DWMTAAssociationInfo *otherInfo;
@property (nonatomic, retain) UIAlertView *alertViewInputPassword;
@property (nonatomic, retain) UITextField *fieldTextInputPassword;
// xuxinjun 2012.03.23 end

#pragma mark -
#pragma mark checkInitialize
//
// 20110107 M.Chikyu (AR17679)
//
- (void) checkInitialize;

// 20111031 M.Chikyu(AR18920) start
/*
 - (void) copyReleaseNote;
 */
// 20111031 M.Chikyu(AR18920) end

// liuqw 2011/10/28 start
// マニュアルの追加 の対応
- (void) copyManualBook;
// liuqw 2011/10/28 end

- (void) copyFileAutoRenAtPath:(NSString*)srcPath toPath:(NSString*)dstPath;

// 初回起動時に更新内容の表示 start
- (void) showUpdateContent;
// 初回起動時に更新内容の表示 end



#pragma mark -
#pragma mark action for document list.
// load all file name in document dir.
- (void) loadAllFileNamesInDocumentDirectory;

// set table view cell info with cell index.
- (void) setTabelViewCellInfo:(UITableViewCell*)cell 
				withCellIndex:(int)index;

// action for select row in table view.
- (void) didSelectRowInTableViewWithIndex:(int)index;

// xuxinjun 2012.03.23 start
// 保護文書の対応
//「文書情報ボタン」の動作 start
/*
 - (XdwAttributeParser *)createXdwAttrubuteParse:(NSString *)filePath;
 */
//「文書情報ボタン」の動作 end
// xuxinjun 2012.03.23 end

// create document view controller with file name and path.

// xuxinjun 2012.03.23 start
// 保護文書の対応
/*
 - (DocumentViewController*) createViewControllerWithFileName:(NSString*)name 
 withFilePath:(NSString*)path;
 */ 
- (DocumentViewController*) createViewControllerWithFileName:(NSString*)name 
												withFilePath:(NSString*)path
												withPassword:(NSString*)pwd;
// xuxinjun 2012.03.23 end

// load document saved status. 
- (void) loadDocumentStatusWithController:(DocumentViewController*)controller 
							 withFileName:(NSString*)name 
						 withCreationDate:(NSString*)date 
						 withDocumentSize:(NSString*)size;

// save document current status.
- (void) saveDocumentStatusWithController:(DocumentViewController*)controller; 

// delete document file with file path.
- (BOOL) deleteDocumentWithFilePath:(NSString*)path;


// xuxinjun 2012.04.06 start
// 保護文書の対応
#pragma mark -
#pragma mark security file about.
- (DW_PROTECTED_TYPE) checkProtectedTypeWithActionType:(int)type
										   andFilePath:(NSString*)path 
										   andFileName:(NSString*)name 
										   andOtherInf:(void*)other;

- (void) pushControllerWithActionType:(int)type 
						  andFilePath:(NSString*)path
						  andFileName:(NSString*)name 
						  andPassword:(NSString*)pwd 
						  andOtherInf:(void*)other;

- (void) showAlertViewForInputPassword;
- (void) setInputPasswordViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation;
- (void) actionOnKeyboardDidShow;
// xuxinjun 2012.04.06 end


#pragma mark -
#pragma mark Edit Toolbar button.
// yangjx 20110706 start
// AR 17898の対応
- (void) actionTouchDoneButton:(UIBarButtonItem*)buttonItem;
// yangjx 20110706 end

//File Multiple Del by Yangjx 0603 start
- (UIBarButtonItem*) createButtonItemWithTitle:(NSString*)title action:(SEL)action;

- (void) setEditModeToolbar;

- (void) setEditing:(BOOL)edit;

// set allfiles status
- (void) checkAllFiles:(BOOL)check;

// set toolbar Items status
- (void) setToolbarItemsStatus;

// set file isSelect status 
- (void) setUITableViewCellAccessoryType:(UITableViewCell *)cell withCheckStatus:(BOOL)check;

// select all file
- (void) checkAllFilesInList;

// usSelect all file
- (void) uncheckAllFilesInList;

// get mail attachment data
- (void) getAttachmentDataWithFilePath:(NSString *)filePath 
					   forMFMailPicker:(MFMailComposeViewController *)mailPicker;

// send Email with data
- (void) sendEmailInDirectoryView;
//File Multiple Del by Yangjx 0603 end



#pragma mark -
#pragma mark environment Toolbar button.
// add environment settings button to toolbar.
- (void) addEnvironmentSettingsButtonToToolbar;

- (void) actionTouchEnvironmentSettingsButton;



#pragma mark -
#pragma mark application about Toolbar button.
// アプリ情報機能の追加 の対応 start 
- (void) actionTouchAboutDocuworksButton;
// アプリ情報機能の追加 の対応 end



#pragma mark -
#pragma mark common method.
// get document file name with index.
- (NSString*) getDocumentFileNameWithIndex:(int)index;

// get document file path with index.
- (NSString*) getDocumentFilePathWithIndex:(int)index;

// get icon name.
- (NSString*) getEnvironmentSettingsIcon;

// modify by yangjx 20110624 start
- (NSString*) getSendEmailButtonIcon;
// modify by yangjx 20110624 end

- (NSString*) getXdwDocumentIcon;
- (NSString*) getXbdDocumentIcon;
- (NSString*) getPDFDocumentIcon;

// xuxinjun 2012.03.27 start
// 保護文書の対応
- (NSString*) getXdwProtectedDocumentIcon;
- (NSString*) getXbdProtectedDocumentIcon;
// xuxinjun 2012.03.27 end

// lixin 2011/09/15 start 
// NS-AR012 の対応
- (NSString*) getDeleteButtonIcon;
// lixin 2011/09/15 end

// get toolbar button.
- (UIButton*) getToolbarButton:(NSString*)iconName;

@end
