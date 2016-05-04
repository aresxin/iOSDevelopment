//
//  FileDetailViewController.h
//  DWViewer
//
//  Created by tongtiexin on 11-6-3.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MFMailComposeViewController.h>
#import "DocumentSettingsManager.h"

// zhaijie 2012.03.30 start
#include "DWAuthenticationManager.h"
// zhaijie 2012.03.30 end

@class DWFileInfo;
@interface FileDetailViewController : UITableViewController <MFMailComposeViewControllerDelegate,
															UIDocumentInteractionControllerDelegate,
															UITextFieldDelegate>
{
    UIDocumentInteractionController *interactionController;
	DocumentSettingsManager *documentSettingsMgr;
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応
	UIInterfaceOrientation orientation_;
	// zhaijie 2012.03.30 end
    
	NSMutableArray *titles;
	NSMutableArray *contents;
    
	DWFileInfo *fileInfo;
    
	UIAlertView *fileUpdateAlert;
	float       maxWidth;
}

- (id)initWithStyle:(UITableViewStyle)style andFileInfo:(DWFileInfo *)fInfo;

- (void) initTitlesAndContents;
- (void) configUITableViewCell:(UITableViewCell *)cell 
         cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (BOOL) UIDeviceIsPortrait;
- (void) didUpdateFileNameFinish:(FileUpdateErrorCode)errorCode;
- (void) resetTextFieldFrame:(UITextField *)textField;
- (void) resetTextFieldFrameForRotation:(UITextField *)textField 
                        withOrientation:(UIInterfaceOrientation)toInterfaceOrientation;
- (void) sendEmailWithAttachment;
- (void) openFileWithOthers:(UIView *)inView;

// tongtx 20110711 start
// AR17920 (20110712 M.Chikyu)
- (void)removeModalView;
// tongtx 20110711 end

@end
