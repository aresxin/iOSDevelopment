//
//  DWViewerAppDelegate.m
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "DWViewerAppDelegate.h"
#import "DirectoryViewController.h"
#import "DocumentViewController.h"
#import "PageViewManager.h"
#import "DWPageView.h"
#import "DocumentSettingsManager.h"
#import "DWViewerGUIConst.h"
// FileSort の対応 start
#import "DWFileInfo.h"
// FileSort の対応 end

// tongtx 20110711 start
// AR17920
#import "FileDetailViewController.h"
#import "Utility.h"
// tongtx 20110711 end


// lixin 20110820 start
// ページ編集機能の追加
#import "DocumentEditController.h"
#define _TAG_ALERTVIEW_EDITINGFILE_             10001
#define _TAG_ALERTVIEW_SAVEANNOTAITONEDIT_      10002
// lixin 20110820 end

// tongtx 2011/08/12 start
// Briefcaseと連携機能の追加
#import "DWAssociationManager.h"
// tongtx 2011/08/12 end

@implementation DWViewerAppDelegate

@synthesize window;
@synthesize navigationController;
@synthesize downloader, url;
@synthesize isDownLoad;


// lixin 20110821 start	
// ページ編集機能の追加
@synthesize freehandSettingColor        = freehandSettingColor_;
@synthesize freehandSettingLineSize     = freehandSettingLineSize_;

//  wangpp 2012.2.28 start
// freehand transparent
@synthesize freehandSettingTransparent	= freehandSettingTransparent_;
//  wangpp 2012.2.28 end

@synthesize textNotepadSettingColor     = textNotepadSettingColor_;
@synthesize textNotepadSettingFontColor = textNotepadSettingFontColor_;
@synthesize textNotepadSettingFontSize  = textNotepadSettingFontSize_; 
// lixin 20110821  end

// wangpp 2012.4.13 start
// login
@synthesize  loginSetingIndex = loginSetingIndex_;
// wangpp 2012.4.13 end


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application 
                    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	// FileSort の対応 start
    documentSettingsManager = [[DocumentSettingsManager alloc]init];
	// FileSort の対応 end
	
	// liuqw 2012.03.26 start
	// アプリ内課金による機能制限
	transObserver_ = [[DWPaymentTransactionObserver alloc]init];
	// liuqw 2012.03.26 end
	
	[self cleanInvalidSettingsFile];
	isRun = NO;
	
	// show statusBar start
	// add by lixin 20110223
	[application setStatusBarHidden:NO withAnimation:UIStatusBarAnimationFade];
	// show statusBar end
	
    [window addSubview:navigationController.view];
	[navigationController setToolbarHidden:NO];
    [window makeKeyAndVisible];
    
    // lixin 20110821 start	
    // ページ編集機能の追加
    self.freehandSettingColor           = Utility::DEFAULT_COLOR_FREEHAND;
	self.freehandSettingLineSize        = Utility::DEFAULT_LINESIZE_FREEHAND;
	
	// wangpp 2012.2.28 start
    // freehand transparent
    self.freehandSettingTransparent     = Utility::DEFAULT_TRANSPARENT_FREEHAND;
    //  wangpp 2012.2.28 end
	
	self.textNotepadSettingColor        = Utility::DEFAULT_COLOR_NOTEPAD;
	self.textNotepadSettingFontColor    = Utility::DEFAULT_FONTCOLOR_NOTEPAD;
	self.textNotepadSettingFontSize     = Utility::DEFAULT_FONTSIZE_NOTEPAD; 
    // lixin 20110821  end
	
	// wangpp 2012.4.13 start
	// login
	self.loginSetingIndex               = Utility::DEFAULT_INDEX_LOGIN;
	// wangpp 2012.4.13 end
	
	
	// for IPad
#if __IPHONE_OS_VERSION_MAX_ALLOWED <= 30200
	NSURL* urlName = [launchOptions objectForKey: @"UIApplicationLaunchOptionsURLKey"];
	if (urlName != nil) {
		if ([urlName.absoluteString hasPrefix: @"xdw"] || [url.absoluteString hasPrefix:@"xbd"])
		{
		    [self application:application handleOpenURL:url];
		}
		else
		{
			NSString *fileName = [urlName.absoluteString lastPathComponent];
			DocumentViewController *controller = nil;
			controller = [[DocumentViewController alloc] initWithPath:urlName.absoluteString];
			controller.title = fileName;
			[self.navigationController pushViewController:controller animated:YES];
		}
	}
#endif
	
	// AR17558 の対応 start.
	// change by lixin 20110222. 
	NSURL* urlLauch = [launchOptions objectForKey: @"UIApplicationLaunchOptionsURLKey"];
	if (urlLauch != nil) {
		self.url = urlLauch;
	} 
    
	// lixin 20110820 start
	// ページ編集機能の追加
	else
	{
		NSString* tempFileName = [self getEditTempFileName];
		if (tempFileName != nil)
		{
			// lixin 2011/09/23 start 
			// NS-AR1017 の対応
			/*
			UIAlertView *alert = [[UIAlertView alloc]initWithTitle:tempFileName
                                                           message:NSLocalizedString(@"MSG_OPENEDITINGFILE", nil)
                                                          delegate:self
                                                 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                 otherButtonTitles:nil]; 
			*/
			UIAlertView *alert = [[UIAlertView alloc]initWithTitle:tempFileName
                                                           message:NSLocalizedString(@"MSG_OPENEDITINGFILE", nil)
                                                          delegate:self
                                                 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES", nil)
                                                 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil), 
								  (char*)nil]; 
			// lixin 2011/09/23 end
			alert.tag = _TAG_ALERTVIEW_EDITINGFILE_;
			[alert show];
			[alert release];
		}
	}
	// lixin 20110820 end
    
	// delete files in Inbox folder.
	[self deleteInboxFile];
	// AR17558 の対応 end.
	
    return YES;
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)urlname
{
	// Add the navigation controller's view to the window and display.	
	if (urlname == nil)
	{
		return NO;
	}
	
	self.url = urlname;
    
    // yanliang 20110706 start
	// AR.NO 17896 対応
	[self deleteKeyBoardAndAlertView];
	// yanliang 20110706 end
    
    // lixin 20110813  start
    // ページ編集機能の追加
    
    
    /*
    // For AR41
	if (isRun == YES) {
		[self.navigationController popToRootViewControllerAnimated:NO];
        
        // yangjx 20110706 start
		// AR 17898 の対応
		DirectoryViewController *dirViewController = (DirectoryViewController *)self.navigationController.topViewController;
		if (dirViewController != nil) {
			if (dirViewController.isEditMode) {
				[dirViewController actionTouchDoneButton:nil];
			}
		}
		// yangjx 20110706 end
	}
	
	UIAlertView *alert = 
    [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_SAVETEMPFILE_ALERT", nil)
                              message:NSLocalizedString(@"MSG_SAVETOLOCAL", nil)
                             delegate:self
     //					  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
     //					  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil),
                    cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES", nil) // 20101222 M.Chikyu修正
                    otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil), // 20101222 M.Chikyu修正
     (char*)nil];
	
	[alert show];
	[alert release];
    */
    

	if (isRun == YES) {
		// dismiss modal view
		UIViewController *subController = [self.navigationController topViewController];
		
		// AR19025
		// 2012.02.29 M.Chikyu start.
		
		if ([subController isKindOfClass:[DocumentViewController class]] == YES)
		{
			UIViewController *modalController = self.navigationController.modalViewController;
			if (modalController != nil &&
				[modalController isKindOfClass:[UINavigationController class]] == YES)
			{
				UINavigationController *subNavigation = (UINavigationController *)modalController;
				subController = [subNavigation topViewController];
			}
		}
		
		// 2012.02.29 M.Chikyu end.
		
		if ([subController isKindOfClass:[DocumentViewController class]] ||
			[subController isKindOfClass:[DocumentEditController class]]) {
			NSString* filePath = nil;
			if ([subController isKindOfClass:[DocumentViewController class]])
			{
				DocumentViewController* viewController = (DocumentViewController*)subController;
				filePath = viewController.filePath;
                
				// tongtx 20110916 start
				// NS-AR024 の対応
				[viewController removeTopViews];
				// tongtx 20110916 end
				
                // lixin 2011/09/14 start 
				// NS-AR009 の対応	
				[viewController cancelShowScreen];
				[viewController performSelector:@selector(hideAllToolbarItems:) 
									 withObject:[NSNumber numberWithBool:NO] 
									 afterDelay:0];
				// lixin 2011/09/14 end
			}
			else
			{
				DocumentEditController* viewController = (DocumentEditController*)subController;
				filePath = [viewController getFileFullName];
                
                // liuqw 2011/09/22 start
                // NS-AR1010 の対応
                if (viewController.modalViewController != nil) {
                    [viewController dismissModalViewControllerAnimated:NO];
                }
                // liuqw 2011/09/22 end
                
                // liuqw 2011/09/22 start
                // NS-AR1011 の対応
                [viewController closeTextNotepadAnnotationInputView];
                // liuqw 2011/09/22 end
				
				// AR19025
				// 2012.02.29 M.Chikyu start.
				
				[self.navigationController dismissModalViewControllerAnimated:NO];
				
				// 2012.02.29 M.Chikyu end.
			}
            
			if ([self isEditingFileWithFileName:filePath] == YES)
			{
                // lixin 2011/09/14 start
				// NS-AR019 の対応
                /*
				UIView* scrollToolbarView = [self.navigationController.view viewWithTag:_TAG_TOOLBAR_SCROLLVIEW_];
				if (scrollToolbarView != nil)
				{
					[scrollToolbarView removeFromSuperview];
				}
				
				tempFileName_ = [[filePath lastPathComponent] copy];
				if (tempFileName_ != nil)
				{
					NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_HANLEOPENURL_SAVEEIDT", nil), tempFileName_];
					UIAlertView *alert = 
					[[UIAlertView alloc]initWithTitle:nil
											  message:message
											 delegate:self
									cancelButtonTitle:NSLocalizedString(@"BUTTON_HANLEOPENURL_SAVE", nil)
									otherButtonTitles:NSLocalizedString(@"BUTTON_HANLEOPENURL_NOTSAVE", nil), 
					 (char*)nil];
					alert.tag = _TAG_ALERTVIEW_SAVEANNOTAITONEDIT_;
					[alert show];
					[alert release];
					
					return YES;
				}
                */
				
				// get src file path name
				NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
				NSString *documentPath = [paths objectAtIndex:0];
				NSString* srcEditFilePath = [documentPath stringByAppendingFormat:@"/%@", [filePath lastPathComponent]];
				
				// compare temp file and src file
				if ([documentSettingsManager compareDataWithSrcPath:srcEditFilePath 
														withDstPath:filePath] == NO)
				{
					UIView* scrollToolbarView = [self.navigationController.view viewWithTag:_TAG_TOOLBAR_SCROLLVIEW_];
					if (scrollToolbarView != nil)
					{
						[scrollToolbarView removeFromSuperview];
					}
					
					tempFileName_ = [[filePath lastPathComponent] copy];
					if (tempFileName_ != nil)
					{
						NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_HANLEOPENURL_SAVEEIDT", nil), tempFileName_];
						UIAlertView *alert = 
						[[UIAlertView alloc]initWithTitle:nil
												  message:message
												 delegate:self
										cancelButtonTitle:NSLocalizedString(@"BUTTON_HANLEOPENURL_SAVE", nil)
										otherButtonTitles:NSLocalizedString(@"BUTTON_HANLEOPENURL_NOTSAVE", nil), 
						 (char*)nil];
						alert.tag = _TAG_ALERTVIEW_SAVEANNOTAITONEDIT_;
						[alert show];
						[alert release];
						//[tempFileName_ release];
						
						return YES;
					}
				}
				else
				{
					[self deleteAllInTempDirectory];
				}
				// lixin 2011/09/14 end
			}
		}
		
		[self popToDirectroyViewController];
	}
	else
	{
		NSString* tempFilePathName = [self getEditTempFileName];
		if (tempFilePathName != nil)
		{
			tempFileName_ = [[tempFilePathName lastPathComponent] copy];
			NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_HANLEOPENURL_SAVEEIDT", nil), tempFileName_];
			UIAlertView *alert = 
			[[UIAlertView alloc]initWithTitle:nil
									  message:message
									 delegate:self
							cancelButtonTitle:NSLocalizedString(@"BUTTON_HANLEOPENURL_SAVE", nil)
							otherButtonTitles:NSLocalizedString(@"BUTTON_HANLEOPENURL_NOTSAVE", nil), 
			 (char*)nil];
			alert.tag = _TAG_ALERTVIEW_SAVEANNOTAITONEDIT_;
			[alert show];
			[alert release];
			
			return YES;
		}
	}
	
	// if showing scroll toolbar, remove 
	UIView* scrollToolbarView = [self.navigationController.view viewWithTag:_TAG_TOOLBAR_SCROLLVIEW_];
	if (scrollToolbarView != nil)
	{
		[scrollToolbarView removeFromSuperview];
	}
    // lixin 20110813  end
	
	// tongtx 2011/08/24 start
    // Briefcaseと連携機能の追加
	[self handleOpenURL];
	// tongtx 2011/08/24 end
    
	return YES;
}

// yanliang 20110706 start
// AR.NO 17896 対応
- (void) deleteKeyBoardAndAlertView
{
    // tongtx 20110711 start
	// AR17920 (20110712 M.Chikyu)
	UIViewController *subController = [self.navigationController topViewController];
	if ([subController isKindOfClass:[FileDetailViewController class]]) {
		[(FileDetailViewController *)subController removeModalView];
	}
	// tongtx 20110711 end
    
	NSArray *windowsView = [[UIApplication sharedApplication] windows];
	for(UIView *winSubView in windowsView)
	{
		NSArray *subView = [winSubView subviews];
		for(UIView *alertView in subView)
		{
			if([[NSString stringWithUTF8String:object_getClassName(alertView)] isEqualToString:@"UIAlertView"])
			{
				for (UIView *textView in alertView.subviews) {
					if ([[NSString stringWithUTF8String:object_getClassName(textView)] isEqualToString:@"UITextField"]) {
						if (textView != nil)
						{
							[textView resignFirstResponder];
						}
					}
				}
				[(UIAlertView *)alertView dismissWithClickedButtonIndex:((UIAlertView *)alertView).cancelButtonIndex animated:NO];
			}
		}
	}
}
// yanliang 20110706 end

// lixin 20110820 start
// ページ編集機能の追加 
- (NSString*) getEditTempFileName
{
	// create temp file manager
	NSFileManager* tempFileManager =[NSFileManager defaultManager];
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *tempPath = [paths objectAtIndex:0];
	NSString *tempDirectoryPath = [tempPath stringByAppendingString:TEMP_DIRECTORY_NAME];
	
	BOOL isDirectoryExist = [tempFileManager fileExistsAtPath:tempDirectoryPath];
	if (isDirectoryExist == NO)
	{
		return nil;
	}
	
	NSArray *files = [tempFileManager contentsOfDirectoryAtPath:tempDirectoryPath error:nil];
	NSString *fullPath = nil;
	
	BOOL bIsDirectory = NO;
	NSString* tempFileName = nil;
	for (NSString* item in files) {
		fullPath = [tempDirectoryPath stringByAppendingPathComponent:item];
		[tempFileManager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		
		if ( bIsDirectory ) {
			continue;
		} else if ([item hasPrefix:@"."] == YES) {
			continue;
		} else if ([item hasSuffix:@".plist"] == YES) {
			continue;
		} else {
			tempFileName = item;
			break;
		}
	}

	return tempFileName;
}

// tongtx 2012.04.17 start
// NS-AR001 の対応
/*
 - (BOOL) saveDocumentAndDeleteTempFile:(NSString*)fileName
 */
- (BOOL) saveDocumentAndDeleteTempFile:(NSString*)fileName 
						targetFileName:(NSString**)targetName
// tongtx 2012.04.17 end
{
	// move temp file to document directory
	// get application document directory
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentPath = [paths objectAtIndex:0];
	
	NSString* dstFilePathName = [[documentPath stringByAppendingFormat:@"/%@", fileName] copy];	
	
	NSString* tempDirectoryPath = [documentPath stringByAppendingString:TEMP_DIRECTORY_NAME];
	
	NSString* tempFileName = [tempDirectoryPath  stringByAppendingFormat:@"/%@", fileName];
	NSString* tempPlistFileName = [tempDirectoryPath stringByAppendingFormat:@"/%@", fileName];	
	tempPlistFileName = [tempPlistFileName stringByDeletingPathExtension];
	tempPlistFileName = [tempPlistFileName stringByAppendingFormat:@".plist"];	
    
	NSFileManager* fileManager = [NSFileManager defaultManager];	
	NSError* fileError = nil;	
    
	// if dst file exist, compare to src file
	if ([fileManager fileExistsAtPath:dstFilePathName] == YES)
	{
		// compare file state
		BOOL isSrcFile = YES;
		
		// get file attributes
		NSString* srcFileSize = nil;
		NSString* srcFileDate = nil;
		NSString* fileSize = nil;
		NSString* fileDate = nil;
		
		// get src file attributes
		NSDictionary* srcFileAttrs = [NSDictionary dictionaryWithContentsOfFile:tempPlistFileName];
		
		// if has plist file, check state
		if (srcFileAttrs != nil)
		{
			srcFileSize = [srcFileAttrs objectForKey:NSFileSize];
			srcFileDate = [srcFileAttrs objectForKey:NSFileModificationDate];
			
			if (srcFileSize == nil || srcFileDate == nil)
			{
				return NO;
			}
			
			// get temp file attributes
			NSDictionary* fileAttrs = [fileManager attributesOfItemAtPath:dstFilePathName error:nil];
			if (fileAttrs != nil)
			{
				fileSize = [fileAttrs objectForKey:NSFileSize];
				fileDate = [fileAttrs objectForKey:NSFileModificationDate];
			}
			
			if (fileSize == nil || fileDate == nil)
			{
				return NO;
			}
			
			if ([fileSize compare:srcFileSize] != NSOrderedSame)
			{
				isSrcFile = NO;
			}
			
			if ([fileDate compare:srcFileDate] != NSOrderedSame)
			{
				isSrcFile = NO;
			}
		}
		else
		{
			isSrcFile = NO;
		}
		
		// if dst file is not src file
		if (isSrcFile == NO)
		{
			NSString* externName = [[dstFilePathName pathExtension] copy];
			
			NSString* dstFileNameWithoutExtension = [dstFilePathName stringByDeletingPathExtension];
			
			int i=1;
			NSString* dstFileName = [dstFileNameWithoutExtension stringByAppendingFormat:@"-%d.%@", i, externName];
			
			while ([fileManager fileExistsAtPath:dstFileName] == YES) {
				i++;
				dstFileName = [dstFileNameWithoutExtension stringByAppendingFormat:@"-%d.%@", i, externName];
			}
			
			if (dstFilePathName != nil)
			{
				[dstFilePathName release];
			}
			
			dstFilePathName = [dstFileName copy];
			
			[externName release];
		}
		else
		{
			[fileManager removeItemAtPath:dstFilePathName error:&fileError];
			
			if (fileError != nil)
			{
				[dstFilePathName release];
				[fileName release];
				return NO;
			}
		}
	}	
	
	[fileManager moveItemAtPath:tempFileName 
						 toPath:dstFilePathName 
						  error:&fileError];	
    
	// tongtx 2012.04.17 start
	// NS-AR001 の対応
    if (targetName != NULL) 
	{
		*targetName = [[dstFilePathName pathComponents] lastObject];
	}
	// tongtx 2012.04.17 end
	
	// delete all file in temp directory
	[self deleteAllInTempDirectory];
	
	return YES;
}

- (void) deleteAllInTempDirectory
{
	NSFileManager* fileManager = [NSFileManager defaultManager];	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentPath = [paths objectAtIndex:0];
	NSString* tempDirectoryPath = [documentPath stringByAppendingString:TEMP_DIRECTORY_NAME];
	NSArray *files = [fileManager contentsOfDirectoryAtPath:tempDirectoryPath error:nil];
	NSString *fullPath;
	
	BOOL bIsDirectory = NO;
	for (NSString* item in files)
    {
		fullPath = [tempDirectoryPath stringByAppendingPathComponent:item];
		[fileManager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		
		if ( bIsDirectory ) {
			continue;
		}
		
		[fileManager removeItemAtPath:fullPath error:nil];
	}
}

- (void) popToDirectroyViewController
{    
    // liuqw 2011/09/28 start
    // NS-AR034 の対応
    /*
	[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleBlackOpaque];
	[[UIApplication sharedApplication] setStatusBarHidden:NO];
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;	
	self.navigationController.toolbar.barStyle = UIBarStyleBlackTranslucent;
	*/
    // liuqw 2011/09/28 end
    
	[self.navigationController popToRootViewControllerAnimated:NO];
	
	DirectoryViewController *dirViewController = (DirectoryViewController *)self.navigationController.topViewController;
	if (dirViewController != nil) {
		if (dirViewController.isEditMode) {
			[dirViewController actionTouchDoneButton:nil];
		}
	}
}

- (BOOL) isEditingFileWithFileName:(NSString*)filePath
{
	if (filePath == nil)
	{
		return NO;
	}
	
	NSArray* filePathArray = [filePath componentsSeparatedByString:@"/"];
	if ([filePathArray count]>2)
	{
		int tempPathIndex = [filePathArray count]-2;
		NSString* tempPath = [filePathArray objectAtIndex:tempPathIndex];
		NSString* tempString = [NSString stringWithFormat:@"/%@/", tempPath];
		if ([tempString isEqualToString:TEMP_DIRECTORY_NAME] == NO)
		{
			return NO;
		}
		else 
		{
			return YES;
		}
	}
	
	return NO;
}
// lixin 201108200 end

// tongtx 2011/08/13 start
// Briefcaseと連携機能の追加
- (void) lauchingFromBrifecaseWithFilepath:(NSString *)filePath withFileName:(NSString *)filename;
{
	if (filePath != nil && filename != nil) {
		if ([[filename pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
			[[filename pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame ||
			[[filename pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame) {
			
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
			/*
			 DocumentViewController *documentViewController = [[DocumentViewController alloc] initWithPath:filePath];
			 if (documentViewController != nil) {
			 documentViewController.fromBriefCase = YES;
			 documentViewController.backButtonTitle = MENU_BRIEFCASE_TITLE;
			 documentViewController.title = filename;
			 documentViewController.fileName = filename;
			 DirectoryViewController *dirViewController = (DirectoryViewController *)self.navigationController.topViewController;
			 documentViewController.delegate = dirViewController;
			 [self.navigationController pushViewController:documentViewController animated:NO];
			 }
			 [documentViewController release];
			 */
			
			enum CHECK_PROTECTED_TYPE type = kCheckBrifecase;
			DirectoryViewController *controller = 
			(DirectoryViewController *)self.navigationController.topViewController;
			DW_PROTECTED_TYPE result = [controller checkProtectedTypeWithActionType:type
																		andFilePath:filePath 
																		andFileName:filename
																		andOtherInf:nil];
			if (result != kProtectTypePwd)
			{
				if (result == kProtectTypeNoPwd)
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:filePath 
												 andFileName:filename 
												 andPassword:@"" 
												 andOtherInf:nil];
				}
				else
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:filePath 
												 andFileName:filename 
												 andPassword:nil
												 andOtherInf:nil];
				}
			}
			// xuxinjun 2012.03.23 end
			
		}
	}
}

- (void) handleOpenURL
{
	if ([[self.url scheme] caseInsensitiveCompare:@"xdwbc"] == NSOrderedSame) {
		[self popToRootViewController:self.navigationController];
		NSString *urlString = [self.url absoluteString];
		NSRange range = [urlString rangeOfString:URL_BRIEFCASE_TO_VLT20];
		if (range.length > 0) {
			NSString *srcFilename = [urlString substringFromIndex:range.length];
			srcFilename = [srcFilename stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
			if ([srcFilename length] > 0) {
                NSString *directorPath = [[documentSettingsManager getDocumentFilePathWithFileName:nil] 
                                          stringByAppendingPathComponent:BRIEFCASE_LINK_DIRECTORY];
                BOOL canRead = [DWAssociationManager readDataFromPasteBoard:directorPath file:srcFilename];
                if (canRead) {
                    NSString *filePath = [directorPath stringByAppendingPathComponent:srcFilename];
                    [self lauchingFromBrifecaseWithFilepath:filePath withFileName:srcFilename];
                }
				
				// liuqw 2012.03.08 start
				// AR NO.19043の対応
				
				else
				{
					UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil
																   message:NSLocalizedString(@"MSG_READ_DATA_FAIL", nil)
																  delegate:nil
														 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
														 otherButtonTitles:nil];
					
					
					[alert show];
					[alert release];
				}
				
				// liuqw 2012.03.08 end
			}
		}
	} else if ([[self.url scheme] caseInsensitiveCompare:MTA_TO_VLT_URLSCHEMA] == NSOrderedSame) {
        [self popToRootViewController:self.navigationController];
        [self handleOpenURLFromMTA:self.url];
    } else {
		UIAlertView *alert = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_SAVETEMPFILE_ALERT", nil)
                                                       message:NSLocalizedString(@"MSG_SAVETOLOCAL", nil)
                                                      delegate:self
                                             cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES", nil)
                                             otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil), 
                              (char*)nil];
		
		
		[alert show];
		[alert release];
	}
}

- (void)popToRootViewController:(UIViewController *)topViewController
{
	if (topViewController.modalViewController != nil) {
		[self popToRootViewController:topViewController.modalViewController];
	} else {
		if ([topViewController isKindOfClass:[UINavigationController class]]) {
			[(UINavigationController *)topViewController popToRootViewControllerAnimated:NO];
		}
		[topViewController dismissModalViewControllerAnimated:NO];
	}
}
// tongtx 2011/08/13 end 

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    // lixin 20110820 start
    // ページ編集機能の追加 
    
	if (alertView.tag == _TAG_ALERTVIEW_EDITINGFILE_)
	{
		// lixin 2011/09/23 start 
		// NS-AR1017 の対応
		/*
		if (alertView.title != nil)
		{
			// get temp file name
			NSString* fileName = [alertView.title copy];
			NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			
			// move temp file to Document directory
			NSString* documentFileName = nil;
			NSFileManager* fileManager = [NSFileManager defaultManager];
			if (fileManager != nil && paths != nil)
			{
				BOOL saveFileSuccess = [self saveDocumentAndDeleteTempFile:fileName];

				if (saveFileSuccess == YES)
				{
					documentFileName = [paths objectAtIndex:0];
					documentFileName = [documentFileName stringByAppendingFormat:@"/%@", fileName];
				}
			}
			
			if (documentFileName != nil)
			{
				// create document view controller. 
				DocumentViewController* controller = 
				[(DirectoryViewController *)self.navigationController.topViewController
				 createViewControllerWithFileName:fileName 
				 withFilePath:documentFileName];
								
				if (controller != nil) {					
					[controller performSelector:@selector(hideAllToolbarItems:) 
									 withObject:[NSNumber numberWithBool:NO] 
									 afterDelay:0];
					[self.navigationController pushViewController:controller animated:YES];
				}
			}
		}
		*/
		if (buttonIndex == alertView.cancelButtonIndex)
		{
			if (alertView.title != nil)
			{
				// get temp file name
				NSString* fileName = [alertView.title copy];
				NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
				
				// move temp file to Document directory
				NSString* documentFileName = nil;
				NSFileManager* fileManager = [NSFileManager defaultManager];
				if (fileManager != nil && paths != nil)
				{
					// tongtx 2012.04.17 start
					// NS-AR001 の対応
					/*
					 BOOL saveFileSuccess = [self saveDocumentAndDeleteTempFile:fileName];
					 */
					BOOL saveFileSuccess = [self saveDocumentAndDeleteTempFile:fileName targetFileName:&fileName];
					// tongtx 2012.04.17 end
					
					if (saveFileSuccess == YES)
					{
						documentFileName = [paths objectAtIndex:0];
						documentFileName = [documentFileName stringByAppendingFormat:@"/%@", fileName];
					}
				}
				
				if (documentFileName != nil)
				{
					
					// xuxinjun 2012.03.23 start
					// 保護文書の対応
					/*
					 // create document view controller. 
					 DocumentViewController* controller = 
					 [(DirectoryViewController *)self.navigationController.topViewController
					 createViewControllerWithFileName:fileName 
					 withFilePath:documentFileName];
					 
					 if (controller != nil) {					
					 [controller performSelector:@selector(hideAllToolbarItems:) 
					 withObject:[NSNumber numberWithBool:NO] 
					 afterDelay:0];
					 [self.navigationController pushViewController:controller animated:YES];
					 }
					 */
					
					enum CHECK_PROTECTED_TYPE type = kCheckEditingFile;
					DirectoryViewController *controller = (DirectoryViewController *)self.navigationController.topViewController;
					DW_PROTECTED_TYPE result = [controller checkProtectedTypeWithActionType:type
																				andFilePath:documentFileName 
																				andFileName:fileName
																				andOtherInf:nil];
					if (result != kProtectTypePwd)
					{
						if (result == kProtectTypeNoPwd)
						{
							[controller pushControllerWithActionType:type 
														 andFilePath:documentFileName 
														 andFileName:fileName 
														 andPassword:@"" 
														 andOtherInf:nil];
						}
						else
						{
							[controller pushControllerWithActionType:type 
													     andFilePath:documentFileName 
														 andFileName:fileName 
														 andPassword:nil 
														 andOtherInf:nil];
						}
					}
					// xuxinjun 2012.03.23 end
					
				}
			}
		}
		else
		{
			[self deleteAllInTempDirectory];
		}
		// lixin 2011/09/23 end
	}
	// add for save annnotation edit when handleOpenURL
	else if (alertView.tag == _TAG_ALERTVIEW_SAVEANNOTAITONEDIT_)
	{
		[[UIApplication sharedApplication] setStatusBarHidden:NO
												withAnimation:UIStatusBarAnimationNone];
		if ([UIApplication sharedApplication].statusBarHidden == NO)
		{
			self.navigationController.navigationBar.hidden = NO;
			self.navigationController.toolbar.hidden = NO;
		}
		
		UIViewController* subController = [self.navigationController topViewController];
		if (subController.modalViewController != nil)
		{
			[subController dismissModalViewControllerAnimated:NO];
		}
		
		if ([subController isKindOfClass:[DocumentEditController class]]) {
			DocumentEditController* viewController = (DocumentEditController*)subController;
			
			// if add text notepad, check showing keyboard				
			if (viewController.editMode == kAddNotepad)
			{
				[viewController exitAddTextNotepadAnnotation:nil];
			}	
		}
		
		[self.navigationController popToRootViewControllerAnimated:NO];
		
		if (buttonIndex == alertView.cancelButtonIndex)
		{
			// save edit
			if (tempFileName_ != nil)
			{
				// tongtx 2012.04.17 start
				// NS-AR001 の対応
				/*
				 [self saveDocumentAndDeleteTempFile:tempFileName_];
				 */
				[self saveDocumentAndDeleteTempFile:tempFileName_ targetFileName:NULL];
				// tongtx 2012.04.17 end
			}
		}
		else
		{
			[self deleteAllInTempDirectory];
		}
		[self handleOpenURL];
	}
    // lixin 20110820 end
    
	else
	{
		// display main interface.
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsPath = [paths objectAtIndex:0];
		
		// 2010/12/09 zhongchao modified this for AR17520 begin
		/*
		 if ([url.absoluteString hasPrefix: @"xdw"] || [url.absoluteString hasPrefix:@"xbd"]
		 || [url.absoluteString hasPrefix:@"pdf"]) {
		 */
		if ([[url scheme] caseInsensitiveCompare:@"xdw"] == NSOrderedSame || 
			[[url scheme] caseInsensitiveCompare:@"xdws"] == NSOrderedSame) {
			// 2010/12/09 zhongchao modified this for AR17520 end
			// get the request URL specified by url scheme.
			NSRange range;
			range.location = 0;
			range.length = [url.scheme length];
			// 2010/12/09 zhongchao modified this for AR17520 begin
			/*
			 NSString *stringURL = [url.absoluteString stringByReplacingOccurrencesOfString:url.scheme 
			 withString:@"http"
			 options:0
			 range:range];
			 */
			NSString *stringURL = nil;
			
			if ([[url scheme] caseInsensitiveCompare:@"xdw"] == NSOrderedSame) {
				stringURL = [url.absoluteString stringByReplacingOccurrencesOfString:url.scheme 
																		  withString:@"http"
																			 options:0
																			   range:range];
			}
			else if ([[url scheme] caseInsensitiveCompare:@"xdws"] == NSOrderedSame) {
				stringURL = [url.absoluteString stringByReplacingOccurrencesOfString:url.scheme 
																		  withString:@"https"
																			 options:0
																			   range:range];
			}
			// 2010/12/09 zhongchao modified this for AR17520 end
			
			NSURL *requestURL = [[NSURL alloc] initWithString:stringURL];
			NSURLRequest *req = [NSURLRequest requestWithURL:requestURL];
			[requestURL release];
			NSString *tempDir = NSTemporaryDirectory();
			// download the file specified by url.
			if (downloader != nil) {
				[downloader release];
				downloader = nil;
			}
			if (buttonIndex == 0) 
			{
				downloader = [[DocumentDownloader alloc]initWithRequest:req 
															  directory:documentsPath 
															   delegate:self];
				self.isDownLoad = YES;	
			}
			else if(buttonIndex == 1)
			{
				self.isDownLoad = NO;
				downloader = [[DocumentDownloader alloc]initWithRequest:req 
															  directory:tempDir 
															   delegate:self];
			}
		} 
		else 
		{
			// change function to get file name from url. add by lixin 20101209 AR17536
			NSString *file  = nil;
			NSString *fileURLPath = nil;
			if ([url isFileURL]) {
				fileURLPath = [url path];
			}
			
			// liuqw 20110329 start
			// DWセキュリティ文書を、他のアプリケーションから連携の不具合の対応
			
			//file = [fileURLPath lastPathComponent];
			file = [[fileURLPath lastPathComponent] retain];
			
			// liuqw 20110329 end
			
			// AR17536 change end
			
			NSString *inboxPath = [documentsPath stringByAppendingString:@"/Inbox/"];
			NSString *filePath =[inboxPath stringByAppendingPathComponent:file];
			
			// tongtx 20110711 start
			// AR NO.17914 の対応
			NSString *newFile = nil;
			if ([file hasPrefix:@"."]) {
				newFile = [@"_" stringByAppendingString:[file substringFromIndex:1]];
				
				[file release];
				file = [newFile retain];
			}
			// tongtx 20110711 end
			
			NSString *dstPath = [documentsPath stringByAppendingPathComponent:file];
			NSError *error;
			
			// 20110107 M.Chikyu (AR17678)
			if ([[NSFileManager defaultManager] fileExistsAtPath:filePath] == NO) return;
			
			if (buttonIndex == 0) {
				self.isDownLoad = YES;
				DirectoryViewController *topController = 
				(DirectoryViewController *)self.navigationController.topViewController;
				
                
                // liuqw 20120203 start
                // AR NO.17904の対応
                /*
                
				// FileSort の対応 start
				//[topController.fileNames addObject:file];
				DWFileInfo* dwFileInfo = [DWFileInfo new];
				dwFileInfo.fileName = file;
				NSFileManager *filemanager = [NSFileManager defaultManager];
				NSDictionary *fileAttrs = [filemanager attributesOfItemAtPath:dstPath error:nil];
				dwFileInfo.fileSize = [fileAttrs objectForKey:NSFileSize];
				dwFileInfo.fileUpdateDate = [fileAttrs objectForKey:NSFileModificationDate];
				[topController.fileInfos addObject:dwFileInfo];
				// FileSort の対応 end
				
				[topController.tableView reloadData];
				[topController.tableView setNeedsDisplay];	
                 
                */ 
                // liuqw 20120203 end
                 
				NSFileManager *fm = [NSFileManager defaultManager];		
				
				if ([fm fileExistsAtPath:filePath] && ![fm fileExistsAtPath:dstPath]) {
					[fm copyItemAtPath: filePath toPath:dstPath error:&error];
				}
				else {
					// when dst file exist, change the dst file to save. add by lixin 20101207 AR.83
					if ( [fm fileExistsAtPath:dstPath] ) {
						// get extension name
						NSString* fileExtName = [dstPath substringFromIndex:(dstPath.length-4)];
						
						//get file name except extension name
						NSString* fileCopyName = [dstPath substringToIndex:(dstPath.length-4)];
						
						// AR17558の対応 start.
						// change by lixin 20110215.
						/*
						 //get file add index ( filename-1, filename-2, ... )
						 int nAddIndex = 1;
						 NSString* fileAddName = [NSString stringWithFormat:@"-%d", nAddIndex];
						 
						 // put file name together
						 dstPath = [fileCopyName stringByAppendingString:fileAddName];
						 dstPath = [dstPath stringByAppendingString:fileExtName];
						 
						 // get index until the file name not exist in directory
						 while ([fm fileExistsAtPath:dstPath]) {
						 nAddIndex++;
						 fileAddName = [NSString stringWithFormat:@"-%d", nAddIndex];
						 dstPath = [fileCopyName stringByAppendingString:fileAddName];
						 dstPath = [dstPath stringByAppendingString:fileExtName];
						 }
						 
						 // copy file 
						 [fm copyItemAtPath: filePath toPath:dstPath error:&error];
						 
						 //copy file end
						 */
						
						// find "-" in file name.
						int nFileNumberLocation = [file rangeOfString:@"-" options:NSBackwardsSearch].location;
						if ( nFileNumberLocation >= file.length-1 ) {
							nFileNumberLocation = 0;
						} else {
							int nFirstNumber = [file characterAtIndex:nFileNumberLocation+1];
							if ( nFirstNumber < '1' || nFirstNumber > '9' ) {
								nFileNumberLocation = 0;
							}
						}
						// end for find "-" 
						
						// if "-" exsit, check whether a file number behind it
						NSString* fileNumber = nil;
						int nAddIndex = 0;
						if ( nFileNumberLocation != 0 ) {
							fileNumber = [file substringFromIndex:nFileNumberLocation+1];
							nAddIndex = [fileNumber intValue];
							if ( nAddIndex < 100 ) {
								nAddIndex += 1;
								int nCopyFileNumberLocation = fileCopyName.length - file.length + fileExtName.length + nFileNumberLocation;
								//nFileNumberLocation = fileCopyName.length-file.length+nFileNumberLocation;
								fileCopyName = [fileCopyName substringToIndex:nCopyFileNumberLocation];
							} else {
								nAddIndex = 1;
							}
						} else {
							nAddIndex = 1;
						}
						
						//get file add index ( filename-1, filename-2, ... )
						NSString* fileAddName = [NSString stringWithFormat:@"-%d", nAddIndex];
						
						// put file name together
						dstPath = [fileCopyName stringByAppendingString:fileAddName];
						dstPath = [dstPath stringByAppendingString:fileExtName];
						
						// get index until the file name not exist in directory
						while ([fm fileExistsAtPath:dstPath]) {
							nAddIndex++;
							fileAddName = [NSString stringWithFormat:@"-%d", nAddIndex];
							dstPath = [fileCopyName stringByAppendingString:fileAddName];
							dstPath = [dstPath stringByAppendingString:fileExtName];
						}
						
						// copy file 
						[fm copyItemAtPath: filePath toPath:dstPath error:&error];
						//copy file end.
						//AR17558の対応 end.
					}
				}
				// AR17558の対応 start
				// start add by lixin.
				// when choose save file to local, open the save file.
				filePath = dstPath;
				
				// liuqw 20110329 start
				// DWセキュリティ文書を、他のアプリケーションから連携の不具合の対応
				
				[file release];
				//file  = [dstPath lastPathComponent];
				file  = [[dstPath lastPathComponent]retain];
				
				// liuqw 20110329 end
				
				self.url = nil;
				// AR17558の対応 end.
                
                // liuqw 20120203 start
                // AR NO.17904の対応
                
                [topController loadAllFileNamesInDocumentDirectory];
                [topController.tableView reloadData];
                [topController.tableView setNeedsDisplay];
                
                // liuqw 20120203 end
			}
			else 
			{
				self.isDownLoad = NO;
			}
			
			// add by liuqw 2011/04/13 start
			// AR NO.17775の対応
			UIViewController *modalViewController = self.navigationController.modalViewController;
			if (modalViewController != nil) {
				if ([modalViewController isKindOfClass:[MFMailComposeViewController class]]) {
					[modalViewController dismissModalViewControllerAnimated:YES];
				}
			}
			// add by liuqw 2011/04/13 end
			
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
			/*
			// create document view controller. // For AR41
			DocumentViewController* controller = 
			[(DirectoryViewController *)self.navigationController.topViewController
			 createViewControllerWithFileName:file withFilePath:filePath];
			
			// liuqw 20110329 start
			// DWセキュリティ文書を、他のアプリケーションから連携の不具合の対応
			
			if (controller != nil) {
				[controller performSelector:@selector(hideAllToolbarItems:) 
								 withObject:[NSNumber numberWithBool:NO] 
								 afterDelay:0];
				[self.navigationController pushViewController:controller animated:YES];
			}
			
			// liuqw 20110329 end
			*/
			
			enum CHECK_PROTECTED_TYPE type = kCheckUTIAssociate;
			DirectoryViewController *controller = (DirectoryViewController *)self.navigationController.topViewController;
			DW_PROTECTED_TYPE result = [controller checkProtectedTypeWithActionType:type
																		andFilePath:filePath 
																		andFileName:file
																		andOtherInf:nil];
			if (result != kProtectTypePwd)
			{
				if (result == kProtectTypeNoPwd)
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:filePath 
												 andFileName:file 
												 andPassword:@"" 
												 andOtherInf:nil];
				}
				else
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:filePath 
												 andFileName:file 
												 andPassword:nil 
												 andOtherInf:nil];
				}
			}
			
			// xuxinjun 2012.03.23 end
			
			// delete files in Inbox folder. add lixin 20101209 AR17563
			[self deleteInboxFile];
			
			// dealloc NSString *file. add by lixin 20101209 AR17536
			[file release];
		}	
	}
	
}

#pragma mark -
#pragma mark Memory management
- (void)dealloc
{
	self.url = nil;
	[self deleteInboxFile];
	[documentSettingsManager release];
	
	// liuqw 2012.03.26 start
	// アプリ内課金による機能制限
	[transObserver_ release];
	// liuqw 2012.03.26 end
	
	[navigationController release];
	[window release];
	if (downloader != nil) {
		[downloader release];
	}
	
	// lixin 20110821 start	
	// ページ編集機能の追加
	self.freehandSettingColor = nil;
	self.freehandSettingLineSize = nil;
	self.textNotepadSettingColor = nil;
	self.textNotepadSettingFontColor = nil;
	self.textNotepadSettingFontSize = nil; 
	
	if (tempFileName_ != nil)
	{
		tempFileName_ = nil;
	}
	// lixin 20110821 end
	
	[super dealloc];
}

#pragma mark -
#pragma mark DownloadDocument delegate method
- (void)downloadDidFinish:(DocumentDownloader *)download
{
	NSString *filePath = [download.filePath lastPathComponent];
	if (self.isDownLoad == YES) 
	{
		if ([self.navigationController.topViewController isKindOfClass:[DirectoryViewController class]]) { //AR17536
			DirectoryViewController *topController =  
			(DirectoryViewController *)self.navigationController.topViewController;
			
			// FileSort の対応 start
			//[topController.fileNames addObject:filePath];
			DWFileInfo* dwFileInfo = [DWFileInfo new];
			dwFileInfo.fileName = filePath;
			NSFileManager *filemanager = [NSFileManager defaultManager];
			NSDictionary *fileAttrs = [filemanager attributesOfItemAtPath:download.filePath error:nil];
			dwFileInfo.fileSize = [fileAttrs objectForKey:NSFileSize];
			dwFileInfo.fileUpdateDate = [fileAttrs objectForKey:NSFileModificationDate];
			[topController.fileInfos addObject:dwFileInfo];
			// FileSort の対応 end
			
			[topController.tableView reloadData];
			[topController.tableView setNeedsDisplay];
		}
	}
	
	DocumentViewController *controller = nil;
	
	if (([[filePath pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame) ||
	    ([[filePath pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame) ||
		([[filePath pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame))
	{
		// Load and display the xdw Document.
		// repair For AR41
		if ([self.navigationController.topViewController isKindOfClass:[DirectoryViewController class]]) {//AR17536
			
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
			
			/*
			 DirectoryViewController *directoryViewController =  
			 (DirectoryViewController *)self.navigationController.topViewController;
			 
			 controller = [directoryViewController createViewControllerWithFileName:filePath 
			 withFilePath:download.filePath];
			 [self.navigationController pushViewController:controller animated:YES];
			 */
			
			enum CHECK_PROTECTED_TYPE type = kCheckDownloadFinish;
			DirectoryViewController *controller = (DirectoryViewController *)self.navigationController.topViewController;
			DW_PROTECTED_TYPE result = [controller checkProtectedTypeWithActionType:type
																		andFilePath:download.filePath 
																		andFileName:filePath
																		andOtherInf:nil];
			if (result != kProtectTypePwd)
			{
				if (result == kProtectTypeNoPwd)
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:download.filePath 
												 andFileName:filePath 
												 andPassword:@"" 
												 andOtherInf:nil];
				}
				else
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:download.filePath 
												 andFileName:filePath 
												 andPassword:nil 
												 andOtherInf:nil];
				}
			}
			// xuxinjun 2012.03.23 end
			
		}
		/*
		controller = [(DirectoryViewController *)self.navigationController.topViewController
					  createViewControllerWithFileName:filePath withFilePath:download.filePath];
		[self.navigationController pushViewController:controller animated:YES];
		 */
	}	
	else
	{ // unsuported file format.
		UIAlertView *alert = 
		  [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
									message:NSLocalizedString(@"MSG_FILE_DISPLAYERROR", nil)
								   delegate:nil
						  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
						  otherButtonTitles:nil];	
		[alert show];
		[alert release];
		return;		
	}
}

- (void)download:(DocumentDownloader *)download didCancelBecauseOf:(NSException *)exception
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString( @"TITLE_ALERT_ERROR", nil)
													 message:[exception reason]
													delegate:nil
										   cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
										   otherButtonTitles:nil];
	
	[alert show];
	[alert release];
}

- (void)download:(DocumentDownloader *)download didFailWithError:(NSError *)error
{
	// AR17536
	if (download.needAuthen) {
		download.needAuthen = NO;
		UIAlertView *alert = 
		[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil)
								   message:NSLocalizedString(@"MSG_ERROR_OPENURL_AUTHENTICATION", nil)
								  delegate:nil 
						 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
						 otherButtonTitles:nil];
		
		[alert show];
		[alert release];
		
	} else {
		
		UIAlertView *alert = 
		[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil)
								   message:NSLocalizedString(@"MSG_DOWNLOADFILE_FAIL", nil)
								  delegate:nil 
						 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
						 otherButtonTitles:nil];
		
		[alert show];
		[alert release];
		
	}
}

- (void) cleanInvalidSettingsFile
{
	NSMutableArray *documentFiles = [[NSMutableArray alloc]init];
	NSMutableArray *settingsFiles = [[NSMutableArray alloc]init];
	
	// get all documents and settings files.
	[self getAllDocumentFiles:documentFiles settingsFiles:settingsFiles];
	
	// remove all valid settings files.
	for (int i = 0; i < documentFiles.count; i++) {
		NSString *fileName = [documentFiles objectAtIndex:i];
		int index = [self findValidSettingsFileFromSettingsFileList:settingsFiles 
													   withFileName:fileName];
		if (index != -1) {
			[settingsFiles removeObjectAtIndex:index];
		}
	}
	
	// delete invalid settings file.
	for (int i = 0; i < settingsFiles.count; i++) {
		NSString *fileName = [settingsFiles objectAtIndex:i];
		[documentSettingsManager deleteSettingsFileWithFileName:fileName];
	}
	
	// release
	[documentFiles release];
	[settingsFiles release];
}

- (void) getAllDocumentFiles:(NSMutableArray*)documents settingsFiles:(NSMutableArray*)settings;
{
	if (documents != nil && settings != nil) {
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
		NSString *dir = [paths objectAtIndex:0];
		NSFileManager *filemanager = [NSFileManager defaultManager];
		NSArray *files = [filemanager contentsOfDirectoryAtPath:dir error:nil];
		NSString *hiddenFilePrefix = @".";
		
		BOOL isDirectory = NO;
		for (NSString* item in files) {
			if ([item characterAtIndex:0] == [hiddenFilePrefix characterAtIndex:0]) {
				continue;
			}
			
			NSString* path = [dir stringByAppendingPathComponent:item];
			[filemanager fileExistsAtPath:path isDirectory:&isDirectory];
			if ( isDirectory ) {
				continue;
			}
			
			// FileSort の対応 start
			/*
			if ([[item pathExtension] caseInsensitiveCompare:@"plist"] == NSOrderedSame) {
				[settings addObject:item];
			} else {
				[documents addObject:item];
			}
			*/
			
			[documents addObject:item];
			// FileSort の対応 end
		}
		
		// FileSort の対応 start
		dir = [documentSettingsManager getSettingsSubDirectoryPath];
		NSArray *settingsfiles = [filemanager contentsOfDirectoryAtPath:dir error:nil];
		for (NSString* item in settingsfiles) {
			NSString* path = [dir stringByAppendingPathComponent:item];
			[filemanager fileExistsAtPath:path isDirectory:&isDirectory];
			if ( isDirectory ) {
				continue;
			}
			
			[settings addObject:item];
		}
		// FileSort の対応 end
	}
}

- (int)  findValidSettingsFileFromSettingsFileList:(NSMutableArray*)fileList 
									  withFileName:(NSString*)name
{
	int index = -1;
	
	if (fileList == nil || name == nil) {
		return index;
	}
	
	NSString* fileName = [name retain];
	NSMutableArray* files  = [fileList retain];
	
	// get plist file name.
	NSMutableString* plistName = [[NSMutableString alloc]initWithString:fileName];
	[plistName appendString:@".plist"];
	
	NSString* item = nil;
	for (int i = 0; i < files.count; i++) {
		item = [files objectAtIndex:i];
		if ([item isEqualToString:plistName] || 
			[item isEqualToString:DW_GLOBAL_SETTINGS_FILE]) {
			index = i;
			break;	
		}
	}
	
	// release
	[fileName release];
	[files release];
	[plistName release];
	
	return index;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

//20101201,modify by yan.if the app enter the background ,save doc settings.
- (void)applicationDidEnterBackground:(UIApplication *)application {
    isRun = YES;

	if ([self.navigationController.topViewController isKindOfClass:[DocumentViewController class]]) {
		DocumentViewController *docViewController = (DocumentViewController*)self.navigationController.topViewController;
		[self saveDocumentStatusWithController:docViewController];
	}
	
	// delete by lixin 20101209 AR17563
	//[self deleteInboxFile];
}

- (void) saveDocumentStatusWithController:(DocumentViewController*)controller
{
	if (controller == nil) {
		return;
	}
	
	if (controller.keepDocumentStatus == NO) {
		return;
	}
    
    // liuqw 20110628 start
    // AR NO.17871 の対応
    if (controller.isCanSaveSettings == NO) {
        return;
    }
    // liuqw 20110628 end
	
	DocumentViewController* documentViewController = [controller retain];
	
	NSString* filePath = [documentViewController.filePath retain];
	NSString* fileName = [documentViewController.fileName retain];
	
	if (filePath != nil) {
		NSFileManager *fileManager = [NSFileManager defaultManager];
		NSDictionary *fileAtribute = [fileManager attributesOfItemAtPath:filePath error:nil];
		NSString *fileCreateDate = [[fileAtribute objectForKey:NSFileCreationDate] description];
		NSString *fileSize = [[fileAtribute objectForKey:NSFileSize] stringValue];
		
		int pageIndex = documentViewController.pageViewMgr.pageIndex;
		
		// liuqw 20110412 start
		// 「AR17778」の対応
		if (documentViewController.pageViewMgr.facingMode == MODE_REGULAR) {
			// do nothing.
		} else {
			if ([documentViewController UIDeviceIsPortrait] == YES) {
				// do nothing.
			} else {
				pageIndex = [documentViewController convertPageViewPosition:pageIndex
															   withFromMode:documentViewController.pageViewMgr.facingMode
																 withToMode:MODE_REGULAR];
			}
		}
		
		/*
		if ([documentViewController UIDeviceIsPortrait] == YES && 
			documentViewController.pageViewMgr.facingMode != MODE_REGULAR) {
			pageIndex = [documentViewController convertPageViewPosition:pageIndex
														   withFromMode:MODE_REGULAR
															 withToMode:documentViewController.pageViewMgr.facingMode];
		}
		*/
		
		// liuqw 20110412 end
	
		DocumentSettingsManager *documentSettingsMgr = [[DocumentSettingsManager alloc]init]; 
		[documentSettingsMgr writeDocumentStatusWithFileName:fileName
											   //withPageIndex:documentViewController.pageViewMgr.pageIndex
											   withPageIndex:pageIndex
											   withPageScale:documentViewController.pageViewMgr.pageScale
											  withPagePointX:documentViewController.pageViewMgr.pageOffset.x
											  withPagePointY:documentViewController.pageViewMgr.pageOffset.y
											  withFacingMode:documentViewController.pageViewMgr.facingMode
										 withFontOrientation:documentViewController.pageViewMgr.fontOrient 
										  withShowAnnotation:documentViewController.pageViewMgr.showAnnotation
											   withPageStatus:documentViewController.pageViewMgr.pageStatus
										 withFileCreatedDate:fileCreateDate
												withFileSize:fileSize];
		[documentSettingsMgr release];
	}
	
	// release
	[documentViewController release];
	[filePath release];
	[fileName release];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
	/*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
	// 文書入出力リスト更新 2010/12/01
	if ([self.navigationController.topViewController isKindOfClass:[DirectoryViewController class]])
	{
		DirectoryViewController *dirViewController = (DirectoryViewController*)self.navigationController.topViewController;
        
        //modify by yangjx 0618 start
        
        dirViewController.isBecomeActiveFromBackground = YES;
        //[dirViewController viewWillAppear:NO];
        
        //modify by yangjx 0618 end
	}
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	if ([self.navigationController.topViewController isKindOfClass:[DocumentViewController class]])
	{
		DocumentViewController *docViewController = (DocumentViewController*)self.navigationController.topViewController;
		[docViewController shiftNextPage];
		[docViewController shiftPrePage];
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
	// 文書入出力リスト更新 2010/12/03
	if ([self.navigationController.topViewController isKindOfClass:[DirectoryViewController class]])
	{
		DirectoryViewController *dirViewController = (DirectoryViewController*)self.navigationController.topViewController;
		// select all modify by yangjx 20110623 start
		dirViewController.isBecomeActiveFromBackground = YES;
		// select all modify by yangjx 20110623 end
		[dirViewController viewWillAppear:YES];
	}
}

/*
- (void)applicationWillTerminate:(UIApplication *)application {
    
     //Called when the application is about to terminate.
     //See also applicationDidEnterBackground:.
}*/


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}

// delete all file in inbox directory
- (void)deleteInboxFile {
	// delete all file in inbox directory
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);	
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *inboxPath = [documentsDirectory stringByAppendingString:@"/Inbox/"];
	
	NSFileManager *filemanager = [NSFileManager defaultManager];
	NSArray *files = [filemanager contentsOfDirectoryAtPath:inboxPath error:nil];
	NSString *fullPath;
	
	BOOL bIsDirectory = NO;
	
	// AR17558の対応 start.
	// add by lixin.
	// get the url file name. 
	NSString *file  = nil;
	NSString *fileURLPath = nil;
	if ( url != nil ) {
		if ([url isFileURL]) {
			fileURLPath = [url path];
		}
		file = [fileURLPath lastPathComponent];
	}
	else {
		file = @"";
	}
	// get url file name end.
	// AR17558の対応 end.
	
	for (NSString* item in files) {
		
		//check item is a directory or a file name
		fullPath = [inboxPath stringByAppendingPathComponent:item];
		[filemanager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		
		if ( bIsDirectory ) {
			continue;
		}
		
		// AR17558の対応 start.
		// change by lixin.
		
		// if item is not the showing file, delete it.   
		//[fileManager removeItemAtPath:fullPath error:nil];
		if ( [item compare:file] ) {
			[fileManager removeItemAtPath:fullPath error:nil];
		}
		// AR17558の対応 end.
	}
}

#pragma mark -
#pragma mark MTA連動機能の対応
// tongtx 20120206 start
// MTA連動機能の対応

- (void) handleOpenURLFromMTA:(NSURL*)url_
{
    if (url_ == nil) {
        return;
    }
    
	// tongtx 2012.02.22 start
	// コードの対応
    
	/*
	 NSString *url_string = [[url_ absoluteString] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	 */
	
	NSString *url_string = [url_ absoluteString];
	
	// tongtx 2012.02.22 end
	
    NSArray *parameters  = [self getParamtersFromURLString:url_string];
    
    if (parameters != nil && [parameters count] == 6) 
    {
        NSString *pasteboard_   = [parameters objectAtIndex:0];
        NSString *filename_     = [parameters objectAtIndex:2];
        NSString *filepath_     = [self downloadFileDataWithFilename:filename_ 
                                                      withPasteboard:pasteboard_];
        if (filepath_ != nil) 
        {
            [self openAssociatedFileWithPath:filepath_ 
                                  pasteboard:pasteboard_
                                  foldername:[parameters objectAtIndex:1] 
                                    filename:[parameters objectAtIndex:2] 
                                 buttonTitle:[parameters objectAtIndex:4] 
                                   pageIndex:[[parameters objectAtIndex:3] intValue] - 1
                                     appname:[parameters objectAtIndex:5]];
        }
		
		// liuqw 2012.03.08 start
		// AR NO.19043の対応
		
		else
		{
			UIAlertView *alert = [[UIAlertView alloc]initWithTitle:nil
														   message:NSLocalizedString(@"MSG_READ_DATA_FAIL", nil)
														  delegate:nil
												 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												 otherButtonTitles:nil];
			
			
			[alert show];
			[alert release];
		}
		
		// liuqw 2012.03.08 end
    }
}

- (NSArray*)getParamtersFromURLString:(NSString*)string
{
    if (string == nil) {
        return nil;
    }
    
    NSArray* items = [string componentsSeparatedByString:@"&"];
    
    NSString*   pasteboard_    = nil;
    NSString*   foldername_    = nil;
    NSString*   filename_      = nil;
    NSString*   pageIndex_     = nil;
    NSString*   buttonTitle_   = nil;
    NSString*   appname_       = nil;
    NSRange     range;
    if ([items count] == 7) {
        NSCharacterSet *whitespace = [NSCharacterSet whitespaceAndNewlineCharacterSet];
        
		// tongtx 2012.02.22 start
		// コードの対応
		/*
        range           = [[items objectAtIndex:1] rangeOfString:@"pasteboard="];
        pasteboard_     = [[items objectAtIndex:1] substringFromIndex:range.length];
        
        range           = [[items objectAtIndex:2] rangeOfString:@"folder="];
        foldername_     = [[items objectAtIndex:2] substringFromIndex:range.length];
        
        range           = [[items objectAtIndex:3] rangeOfString:@"filename="];
        filename_       = [[items objectAtIndex:3] substringFromIndex:range.length];
        
        range           = [[items objectAtIndex:4] rangeOfString:@"page="];
        pageIndex_      = [[items objectAtIndex:4] substringFromIndex:range.length];
        pageIndex_      = [pageIndex_ stringByTrimmingCharactersInSet:whitespace];
        
        range           = [[items objectAtIndex:5] rangeOfString:@"returnbutton="];
        buttonTitle_    = [[items objectAtIndex:5] substringFromIndex:range.length];
        buttonTitle_    = [buttonTitle_ stringByTrimmingCharactersInSet:whitespace];
        
        range           = [[items objectAtIndex:6] rangeOfString:@"appname="];
        appname_        = [[items objectAtIndex:6] substringFromIndex:range.length];
        appname_        = [appname_ stringByTrimmingCharactersInSet:whitespace];
		*/
		
        range           = [[items objectAtIndex:1] rangeOfString:@"pasteboard="];
        pasteboard_     = [[[items objectAtIndex:1] substringFromIndex:range.length] 
						   stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		
        range           = [[items objectAtIndex:2] rangeOfString:@"folder="];
        foldername_     = [[items objectAtIndex:2] substringFromIndex:range.length];
        
        range           = [[items objectAtIndex:3] rangeOfString:@"filename="];
        filename_       = [[[items objectAtIndex:3] substringFromIndex:range.length] 
						   stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        
        range           = [[items objectAtIndex:4] rangeOfString:@"page="];
        pageIndex_      = [[[items objectAtIndex:4] substringFromIndex:range.length] 
						   stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        pageIndex_      = [pageIndex_ stringByTrimmingCharactersInSet:whitespace];
        
        range           = [[items objectAtIndex:5] rangeOfString:@"returnbutton="];
        buttonTitle_    = [[[items objectAtIndex:5] substringFromIndex:range.length] 
						   stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        buttonTitle_    = [buttonTitle_ stringByTrimmingCharactersInSet:whitespace];
        
        range           = [[items objectAtIndex:6] rangeOfString:@"appname="];
        appname_        = [[[items objectAtIndex:6] substringFromIndex:range.length] 
						   stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        appname_        = [appname_ stringByTrimmingCharactersInSet:whitespace];
		
        // tongtx 2012.02.22 end
        
        if (pageIndex_ == nil || 
            [pageIndex_ isEqualToString:@""] || 
            [pageIndex_ intValue] == 0) 
        {
            pageIndex_ = [NSString stringWithFormat:@"%d", 0];
        }
        
        if (buttonTitle_ == nil || [buttonTitle_ isEqualToString:@""]) 
        {
            buttonTitle_ = NSLocalizedString(@"BUTTON_TITLE_BACK", nil);
        }
        
        if (appname_ == nil || [appname_ isEqualToString:@""]) 
        {
            appname_ = NSLocalizedString(@"ASSOCIATION_DEFAULT_APPNAME", nil);
        }
        
        return [NSArray arrayWithObjects:pasteboard_, 
                foldername_, 
                filename_, 
                pageIndex_,
                buttonTitle_, 
                appname_, 
                (char *)nil];
    }
    
    return nil;
}

- (NSString*) downloadFileDataWithFilename:(NSString *)name
                            withPasteboard:(NSString *)pasteboard
{
    NSData *data = [DWAssociationManager readFileDataFromPasteBoard:pasteboard 
                                                               type:MTA_PASTEBOARD_TYPE];
    if (data != nil && [data length] > 0) 
    {
        NSString *directoryPath = [[documentSettingsManager getDocumentFilePathWithFileName:nil] 
                                   stringByAppendingPathComponent:MTA_ASSOCIATION_DIRECTORY];
        [documentSettingsManager removeFilesAtPath:directoryPath];
        
        BOOL isCreated = [documentSettingsManager createDirectoryAtPath:directoryPath];
        if (isCreated == YES) 
        {
            [documentSettingsManager createFileAtDirectoryPath:directoryPath 
                                                          file:name
                                                      contents:data 
                                                   overwritten:YES];
        }
        
        return [directoryPath stringByAppendingPathComponent:name];
    }
    
    return nil;
}

- (void) openAssociatedFileWithPath:(NSString*)path 
                         pasteboard:(NSString*)pasteboard
                         foldername:(NSString*)folder
                           filename:(NSString*)fname 
                        buttonTitle:(NSString*)title
                          pageIndex:(int)index
                            appname:(NSString*)appname
{
    if (path != nil && fname != nil)
    {
        if ([[fname pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
            [[fname pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame ||
            [[fname pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame) 
        {
            // xuxinjun 2012.03.23 start
			// 保護文書の対応
			/*
			 DocumentViewController *documentViewController = [[DocumentViewController alloc] initWithPath:path];
			 if (documentViewController != nil) 
			 {
			 int pageCount = documentViewController.pageViewMgr.pageTotalCount;
			 if (index < 0 || index > pageCount - 1) index = 0;
			 documentViewController.isFromMTA                = YES;
			 documentViewController.backButtonTitle          = title;
			 documentViewController.title                    = fname;
			 documentViewController.fileName                 = fname;
			 documentViewController.pasteboardFromMTA        = pasteboard;
			 documentViewController.folderNameFromMTA        = folder;
			 documentViewController.pageViewMgr.pageIndex    = index;
			 documentViewController.appnameFromMTA           = appname;
			 
			 DirectoryViewController *dirViewController = (DirectoryViewController *)self.navigationController.topViewController;
			 documentViewController.delegate = dirViewController;
			 
			 [self.navigationController pushViewController:documentViewController animated:NO];
			 }
			 [documentViewController release];
			 */ 
			DWMTAAssociationInfo* info_ = [[[DWMTAAssociationInfo alloc]init]autorelease];
			info_.backButtonTitle		= title;
			info_.pasteboard			= pasteboard;
			info_.folderName			= folder;
			info_.pageIndex				= index;
			info_.appName				= appname;
			
			enum CHECK_PROTECTED_TYPE type = kCheckOpenAssociatedFile;
			DirectoryViewController *controller = 
			(DirectoryViewController *)self.navigationController.topViewController;
			DW_PROTECTED_TYPE result = [controller checkProtectedTypeWithActionType:type
																		andFilePath:path 
																		andFileName:fname
																		andOtherInf:info_];
			if (result != kProtectTypePwd)
			{
				if (result == kProtectTypeNoPwd)
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:path 
												 andFileName:fname 
												 andPassword:@"" 
												 andOtherInf:info_];
				}
				else
				{
					[controller pushControllerWithActionType:type 
												 andFilePath:path 
												 andFileName:fname 
												 andPassword:nil 
												 andOtherInf:info_];
				}
			}
			// xuxinjun 2012.03.23 end
        }
    }
}

// tongtx 20120206 end
@end

