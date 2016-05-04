//
//  DWViewerAppDelegate.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DocumentDownloader.h"

// liuqw 2012.03.26 start
// アプリ内課金による機能制限
#import "DWRemoveLimitViewController.h"
// liuqw 2012.03.26 end

@class DocumentSettingsManager;
@class DocumentViewController;
@interface DWViewerAppDelegate : NSObject <UIApplicationDelegate,
										   DocumentDownloaderDeleagte,
                                           UIAlertViewDelegate> 
{
    UIWindow *window;
    UINavigationController *navigationController;
	DocumentDownloader *downloader;
	NSURL *url;
	BOOL isDownLoad;
											   
    DocumentSettingsManager *documentSettingsManager;
	BOOL isRun;
	
	// lixin 20110821 start	
	// ページ編集機能の追加
	UIColor*                freehandSettingColor_;
	int                     freehandSettingLineSize_;
	
	// wangpp 2012.2.28 start
    // freehand transparent
    BOOL                freehandSettingTransparent_;
    // wangpp 2012.2.28 end
	
	UIColor*                textNotepadSettingColor_;
	UIColor*                textNotepadSettingFontColor_;
	int                     textNotepadSettingFontSize_;
	
	// wangpp 2012.4.13 start
	// login
	int                      loginSetingIndex_;
	// wangpp 2012.4.13 end

	NSString*               tempFileName_;
	/// lixin 20110821 end
	
	// liuqw 2012.03.26 start
	// アプリ内課金による機能制限
	DWPaymentTransactionObserver* transObserver_;
	// liuqw 2012.03.26 end
	
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;
@property (nonatomic, retain) DocumentDownloader *downloader;
@property (nonatomic, retain) NSURL *url;
@property BOOL isDownLoad;

// lixin 20110821 start	
// ページ編集機能の追加
@property (nonatomic, retain) UIColor* freehandSettingColor;
@property (nonatomic, assign) int      freehandSettingLineSize;

// wangpp 2012.2.28 start
// freehand transparent
@property  BOOL	freehandSettingTransparent;
// wangpp 2012.2.28 end

@property (nonatomic, retain) UIColor* textNotepadSettingColor;
@property (nonatomic, retain) UIColor* textNotepadSettingFontColor;
@property (nonatomic, assign) int      textNotepadSettingFontSize;
// lixin 20110821 end

// wangpp 2012.4.13 start
// login
@property int loginSetingIndex;
// wangpp 2012.4.13 end

// clean invalid settings file.
- (void) cleanInvalidSettingsFile;

// get document files and settings files.
- (void) getAllDocumentFiles:(NSMutableArray*)documents 
			   settingsFiles:(NSMutableArray*)settings;

// find valid settings file from all settings files.
- (int)  findValidSettingsFileFromSettingsFileList:(NSMutableArray*)fileList 
									  withFileName:(NSString*)name;

// save document status.
- (void) saveDocumentStatusWithController:(DocumentViewController*)controller;

// delete all file in inbox directory. add by lixin 20101207
- (void)deleteInboxFile;

// yanliang 20110706 start
// AR.NO 17896 対応
- (void) deleteKeyBoardAndAlertView;
// yanliang 20110706 end

// lixin 20110820 start
// ページ編集機能の追加 
- (NSString*) getEditTempFileName;

// tongtx 2012.04.17 start
// NS-AR001 の対応
/*
 - (BOOL) saveDocumentAndDeleteTempFile:(NSString*)fileName;
 */
- (BOOL) saveDocumentAndDeleteTempFile:(NSString*)fileName 
						targetFileName:(NSString**)targetName;
// tongtx 2012.04.17 end

- (void) deleteAllInTempDirectory;
- (void) popToDirectroyViewController;
- (BOOL) isEditingFileWithFileName:(NSString*)filePath;
// lixin 201108200 end

// tongtx 2011/08/13 start
// Briefcaseと連携機能の追加
- (void) lauchingFromBrifecaseWithFilepath:(NSString *)filePath
                              withFileName:(NSString *)filename;
- (void) handleOpenURL;
- (void) popToRootViewController:(UIViewController *)topViewController;
// tongtx 2011/08/13 end

// tongtx 20120206 start
// MTA連動機能の対応
- (void) handleOpenURLFromMTA:(NSURL*)url;
- (NSArray*)getParamtersFromURLString:(NSString*)string;
- (NSString*) downloadFileDataWithFilename:(NSString *)name
                            withPasteboard:(NSString *)pasteboard;
- (void) openAssociatedFileWithPath:(NSString*)path 
                         pasteboard:(NSString*)pasteboard
                         foldername:(NSString*)folder
                           filename:(NSString*)fname 
                        buttonTitle:(NSString*)title
                          pageIndex:(int)index
                            appname:(NSString*)appname;
// tongtx 20120206 end
@end


