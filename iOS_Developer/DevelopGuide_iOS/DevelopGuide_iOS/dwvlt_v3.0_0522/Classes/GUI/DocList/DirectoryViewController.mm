//
//  DirectoryViewController.m
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "DirectoryViewController.h"
#import "DocumentViewController.h"
#import "PageViewManager.h"
#import "DocumentSettingsManager.h"
#import "Utility.h"
#import "DWViewerGUIConst.h"
#import "FileDetailViewController.h"

//「文書情報ボタン」の動作 start
#import "DocumentSummaryManager.h"
//「文書情報ボタン」の動作 end

// FileSort の対応 start
#import "DWFileInfo.h"
// FileSort の対応 end

// yangjx 20110622 start
// AR17848 の対応
#import "FileSortSettingsViewController.h"
// yangjx 20110622 end

#define MAX_DOCUMENT_NUM 500

// FileSort の対応 start
#define FILE_SIZE_LABEL_TAG 1001
// FileSort の対応 end

//File Multiple Del by Yangjx 0607 start
#define ALERT_DELONEFILE_TAG 0
#define ALERT_SENDEMAIL_TAG 1
#define ALERT_MULTIDEL_TAG 2
#define ALERT_CANCELDEL_TAG 3
#define FILE_SIZE_LABEL_OFFSET 35
#define FILE_SIZE_LABEL_HOFFSET 2
//File Multiple Del by Yangjx 0607 end

// liuqw 20110628 start
// AR NO.17871 の対応
#define TAG_SETTINGS_NAME_ERROR 101
// liuqw 20110628 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
#define TAG_ALERT_INPUT_PWD 5001
#define TAG_FIELD_INPUT_PWD 5002
// xuxinjun 2012.03.23 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
@implementation DWMTAAssociationInfo
@synthesize backButtonTitle;
@synthesize pasteboard;
@synthesize folderName;
@synthesize appName;
@synthesize pageIndex;

- (void)dealloc{
	[backButtonTitle release];
	[pasteboard release];
	[folderName release];
	[appName release];
}

@end
// xuxinjun 2012.03.23 end

@implementation DirectoryViewController
// FileSort の対応 start
//@synthesize fileNames;
@synthesize fileInfos;
@synthesize fileSortItemIndex;
@synthesize fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@synthesize specifyScaleModeIndex;
@synthesize specifyScaleValue;
// 「拡大率指定の追加」の対応 end

@synthesize keepDocumentStatus;

// 20110322 M.Chikyu start
// QuartzBridge高速化対応
//File Multiple Del by Yangjx 0603 start
@synthesize selectFileInfos;
@synthesize isBecomeActiveFromBackground;
//File Multiple Del by Yangjx 0603 end

// yangjx 20110706 start 
// AR 17898 の対応
@synthesize isEditMode;
// yangjx 20110706 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
@synthesize authenticationManager	= authManager_;
@synthesize authFullPath			= authFullPath_;
@synthesize authFileName			= authFileName_;
@synthesize otherInfo				= otherInfo_;
@synthesize alertViewInputPassword	= alertViewInputPassword_;
@synthesize fieldTextInputPassword  = fieldTextInputPassword_;
// xuxinjun 2012.03.23 end

void InitFontSupportCache();

// 20110322 M.Chikyu end


#pragma mark -
#pragma mark View lifecycle
- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = NSLocalizedString(@"MENU_FILELIST_TITLE", nil);
	
	
	// 1. common manager
	documentSettingsMgr		= [[DocumentSettingsManager alloc]init];
    documentSummaryMgr		= [[DocumentSummaryManager alloc]init];
	//activeViewController	= nil;
	
	
	// 2. doucment list about.
	// FileSort の対応 start
	fileInfos = [[NSMutableArray alloc] init];
	// FileSort の対応 end
	
	// tongtx 20110920 start
	// NS-AR029 の対応
	isUpdateFileNameFromDetailView = NO;
	// tongtx 20110920 end
	
	
	// 3. about delete file
	deleteFilePath = nil;
	
	
	// 4. toolbar items about. 
	// 4.1. init environment settings controller.
	environmentSettingsController = [[EnvironmentSettingsViewController alloc]init];
	environmentSettingsController.delegate = self;	
	navigateController = [[UINavigationController alloc]
						  initWithRootViewController:environmentSettingsController];
	navigateController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	keepDocumentStatus	= NO;
	
	// liuqw 20110628 start
    // AR NO.17871 の対応
	selectCellIndex		= -1;
	// liuqw 20110628 end
	
	// FileSort の対応 start
	fileSortItemIndex	= 0;
	fileSortModeIndex	= 0;
	// FileSort の対応 end
	
	[self addEnvironmentSettingsButtonToToolbar];
	
	// 4.2. app info controller.
	// アプリ情報機能の追加 の対応 start
	aboutDocuworksController = [[AboutDocuworksViewController alloc] init];	
	aboutNavigateController = [[UINavigationController alloc]
							   initWithRootViewController:aboutDocuworksController];
	aboutNavigateController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	// アプリ情報機能の追加 の対応 end
	
	
	// 4.3 edit button item about.
	// File Multiple Del by Yangjx 0603 start
    UIBarButtonItem* editItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_EDIT", @"")
														 action:@selector(actionTouchEditButton:)];
	self.navigationItem.rightBarButtonItem = editItem;	
	
	// yangjx 20110622 start
	// AR17848 の対応
	UIBarButtonItem *sortItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_SORT", @"") 
														 action:@selector(actionTouchSortButton:)];
	self.navigationItem.leftBarButtonItem = sortItem;
	// yangjx 20110622 end
	self.tableView.allowsSelectionDuringEditing = YES;
	isEditMode = NO;
    isBecomeActiveFromBackground = NO;
	// File Multiple Del by Yangjx 0603 end
	
	
	// 20110107 M.Chikyu (AR17679)
	// リリースノートの保存を確認
	[self checkInitialize];
	
	// 20110322 M.Chikyu start
	// QuartzBridge高速化対応
	
	InitFontSupportCache();
	
	// 20110322 M.Chikyu end
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	self.authenticationManager = [[[DWAuthenticationManager alloc]init]autorelease];
	// xuxinjun 2012.03.23 end
	
}

- (void)viewWillAppear:(BOOL)animated {
    
    // liuqw 2011/09/28 start
    // NS-AR034 の対応
    
    /*
    // liuqw 2011/09/02 start
    CGRect navigatebarRect = self.navigationController.navigationBar.frame;
    float originX = 0.0;
    float originY = 20.0;
    navigatebarRect = CGRectMake(originX, 
                                 originY, 
                                 navigatebarRect.size.width,
                                 navigatebarRect.size.height);
    self.navigationController.navigationBar.frame = navigatebarRect;
    // liuqw 2011/09/02 end
    */
    
	//AR17720 modify by yangjx 0620 start
	
	// xuxinjun 2012.04.12 start
	// 保護文書の対応
	
	/*
	CGFloat top = self.navigationController.navigationBar.frame.size.height;
	CGFloat bottom = self.navigationController.toolbar.frame.size.height;
	self.tableView.contentInset = UIEdgeInsetsMake(top, 0, bottom, 0);
	self.tableView.scrollIndicatorInsets = UIEdgeInsetsMake(top, 0, bottom, 0);
	 */
	
	// xuxinjun 2012.04.12 end
	
	//AR17720 modify by yangjx 0620 end
	
    /*
	[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleBlackOpaque];
	// 20110822 modify by yangjx start
	[[UIApplication sharedApplication] setStatusBarHidden:NO];
	// 20110822 modify by yangjx end
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;	
	self.navigationController.toolbar.barStyle = UIBarStyleBlackTranslucent;
	
	// 20110622 tongtx start
	// AR17861 の対応
	self.navigationController.toolbar.hidden = NO;
	// 20110622 tongtx end
    */
    
    if (isBecomeActiveFromBackground == NO) {
        CGRect navigatebarRect = self.navigationController.navigationBar.frame;
        float originX = 0.0;
        float originY = 20.0;
        navigatebarRect = CGRectMake(originX, 
                                     originY, 
                                     navigatebarRect.size.width,
                                     navigatebarRect.size.height);
        self.navigationController.navigationBar.frame = navigatebarRect;
        
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleBlackOpaque];
        [[UIApplication sharedApplication] setStatusBarHidden:NO];
        self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;	
        self.navigationController.toolbar.barStyle = UIBarStyleBlackTranslucent;
        self.navigationController.toolbar.hidden = NO;
    }
    
    self.navigationController.navigationBar.hidden = NO;
    
    // liuqw 2011/09/28 end
    
	// FileSort の対応 start
	// set keep document status.
	//keepDocumentStatus = [documentSettingsMgr readKeepDocumentStatus];
	if (YES == [documentSettingsMgr readDocumentSettings]) {
		keepDocumentStatus = documentSettingsMgr.keepStatus;
		fileSortItemIndex = documentSettingsMgr.fileSortItemIndex;
		fileSortModeIndex = documentSettingsMgr.fileSortModeIndex;
        
        // 「拡大率指定の追加」の対応 start
        specifyScaleModeIndex = documentSettingsMgr.specifyScaleModeIndex;
        specifyScaleValue = documentSettingsMgr.specifyScale;
        // 「拡大率指定の追加」の対応 end
	}
	// FileSort の対応 end
	
	//AR No.17581 delete by sun.chl 2010.12.17
	/*
	 // save settings.
	 if (activeViewController != nil) {
	 [self saveDocumentStatusWithController:(DocumentViewController*)activeViewController];
	 }
	 */
	
    //modify by yangjx 0618 start
    
	// 文書入出力リスト更新 2010/12/01
    //[self loadAllFileNamesInDocumentDirectory];
    
	if (isBecomeActiveFromBackground == YES && isEditMode == YES) {
        isBecomeActiveFromBackground = NO;
	} else {
        isBecomeActiveFromBackground = NO;
        [self loadAllFileNamesInDocumentDirectory];
    }

	//modify by yangjx 0618 end
    
	[self.tableView reloadData];
	
    [super viewWillAppear:animated];
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}


#pragma mark -
#pragma mark Memory management
- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc that aren't in use.
}


#pragma mark -
#pragma mark dealloc
- (void)dealloc {
	if (documentSettingsMgr != nil) {
		[documentSettingsMgr release];
		documentSettingsMgr = nil;
	}
    
    //「文書情報ボタン」の動作 start
    if (documentSummaryMgr != nil) {
		[documentSummaryMgr release];
		documentSummaryMgr = nil;
	}
    //「文書情報ボタン」の動作 end
	
	if (activeViewController != nil) {
		[activeViewController release];
		activeViewController = nil;
	}
	
	if (deleteIndexPath != nil) {
		[deleteIndexPath release];
		deleteIndexPath = nil;
	}
	
	if (deleteFilePath != nil) {
		[deleteFilePath release];
		deleteFilePath = nil;
	}
	
	if (environmentSettingsController != nil) {
		[environmentSettingsController release];
		environmentSettingsController = nil;
	}
	
	if (navigateController != nil) {
		[navigateController release];
		navigateController = nil;
	}
	
	
	// 3.5アプリ情報機能の追加 の対応 start 
	// change by lixin 20110613 DW_iPhoneEnhance_12
	if (aboutNavigateController != nil) {
		[aboutNavigateController release];
		aboutNavigateController = nil;
	}
	// 3.5アプリ情報機能の追加 の対応 end
	
	// FileSort の対応 start
	//[fileNames release];
	[fileInfos release];
	// FileSort の対応 end
	
	//File Multiple Del by Yangjx 0603 start
	[selectFileInfos release];
	//File Multiple Del by Yangjx 0603 end
    
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	self.authenticationManager = nil;
	self.authFullPath = nil;
	self.authFileName = nil;
	self.otherInfo = nil;
	[fieldTextInputPassword_ release];
	[alertViewInputPassword_ release];
	// xuxinjun 2012.03.23 end
	
    [super dealloc];
}


#pragma mark -
#pragma mark checkInitialize
//
// 20110107 M.Chikyu (AR17679)
//
- (void) checkInitialize
{
	NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
	
	// ユーザー設定に保存したアプリケーションのバージョンを取得
	NSString* defVersion = [defaults stringForKey:@"APP_VERSION"];
	
	// アプリケーションのバージョンをinfo.plistから取得
	NSString* appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];;
	
	// ユーザー設定が存在しないかバージョン番号が異なる場合に実行
	if ( defVersion == nil ||
		[defVersion compare:appVersion] != NSOrderedSame)
	{
		// 20111031 M.Chikyu(AR18920) start
		/*
		 // リリースノートをコピー
		 [self copyReleaseNote];
		 */
		// 20111031 M.Chikyu(AR18920) end
		
        // liuqw 2011/10/28 start
        // マニュアルの追加 の対応
        [self copyManualBook];
        // liuqw 2011/10/28 end
		
		// 3.7 初回起動時に更新内容の表示 start
		// change by lixin 20110608 DW_iPhoneEnhance_12
		[self showUpdateContent];
		// 3.7 初回起動時に更新内容の表示 end
		
		// アプリケーションのバージョンをユーザー設定に保存
		[defaults setObject:appVersion forKey:@"APP_VERSION"];
		
		// liuqw 20110323 start
		// バージョンアップ時に、表示画面の変更の対応
		environmentSettingsController.keepDocumentStatus = YES;
		environmentSettingsController.fileSortItemIndex = 0;
		environmentSettingsController.fileSortModeIndex = 0;
		[self presentModalViewController:navigateController animated:NO];
		// liuqw 20110323 end
	}
}

// 20111031 M.Chikyu(AR18920) start
/*
 
//Copy ReadMe の対応 start

//
// 20110107 M.Chikyu (AR17679)
//
-(void) copyReleaseNote
{
	// releasenoteのファイル名を取得
	//	NSString *fileName_JPN = NSLocalizedString(@"RELEASENOTE", nil);
	//	NSString *fileName_ENG = NSLocalizedString(@"RELEASENOTE", nil);
	NSString *fileName = NSLocalizedString(@"RELEASENOTE", nil);
	
	// リソース上のreleasenoteのパスを取得
	NSString *srcPath = [[NSBundle mainBundle] resourcePath];
	//	NSString *srcPath_JPN = [srcPath stringByAppendingPathComponent:fileName_JPN];
	//	NSString *srcPath_ENG = [srcPath stringByAppendingPathComponent:fileName_ENG];
	
	NSString *srcPath_bundle = [srcPath stringByAppendingPathComponent:fileName];
	
	// ドキュメントフォルダ上のreleasenoteのパスを取得
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *dstPath = [paths objectAtIndex:0];
	//	NSString *dstPath_JPN = [dstPath stringByAppendingPathComponent:fileName_JPN];  
	//	NSString *dstPath_ENG = [dstPath stringByAppendingPathComponent:fileName_ENG];  
	
	// liuqw 20110330 start
	// 全言語でReadme.xdwの対応
	
	// liuqw 20110623 start
	//NSString* dstFileName = @"Readme.xdw"; 
	NSString* dstFileName = @"HowToUse(1.2).xdw";
	// liuqw 20110623 end
	
	NSString *dstPath_bundle = [dstPath stringByAppendingPathComponent:dstFileName]; 
	// liuqw 20110330 end
	
	// ドキュメントフォルダにコピー
	[self copyFileAutoRenAtPath:srcPath_bundle toPath:dstPath_bundle];
}
 
 //Copy ReadMe の対応 end
 
 */ 
// 20111031 M.Chikyu(AR18920) end

// liuqw 2011/10/28 start
// マニュアルの追加 の対応
- (void) copyManualBook
{
	NSString *fileName = NSLocalizedString(@"HANDBOOK", nil);
	NSString *srcPath = [[NSBundle mainBundle] resourcePath];
	NSString *srcPath_bundle = [srcPath stringByAppendingPathComponent:fileName];
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *dstPath = [paths objectAtIndex:0];  
    NSString* dstFileName = @"DocuWorks Viewer Light Handbook.xdw";
    
    NSString *dstPath_bundle = [dstPath stringByAppendingPathComponent:dstFileName]; 
	[self copyFileAutoRenAtPath:srcPath_bundle toPath:dstPath_bundle];
}
// liuqw 2011/10/28 end

//
// 20110107 M.Chikyu (AR17679)
//
- (void) copyFileAutoRenAtPath:(NSString*)srcPath toPath:(NSString*)dstPath
{
	// ドキュメントフォルダにコピー
	NSFileManager *fileman = [NSFileManager defaultManager];
	NSError *error;
	BOOL res;
	int count;
	
	// オリジナルのファイル名でコピー
	res = [fileman copyItemAtPath:srcPath toPath:dstPath error:&error];
	if (res == NO)
	{
		// 失敗した場合はファイル名に番号をつけて再実行
		NSString *dstPathPre = [dstPath stringByDeletingPathExtension];
		NSString *dstPathExt = [dstPath pathExtension];
		for (count = 1; count <= 500; count++)
		{
			NSString *dstPathNum = [NSString stringWithFormat:@"%@-%d.%@", dstPathPre, count, dstPathExt];
			res = [fileman copyItemAtPath:srcPath toPath:dstPathNum error:&error];
			if (res == YES) break;
		}
	}
}

// 初回起動時に更新内容の表示 start
- (void) showUpdateContent
{
	NSString* updateMsg = NSLocalizedString(@"MSG_UPDATECONTENT_CONTENT", nil);
    // liuqw 2011/07/11 start
    // AR NO.17915 の対応 
	//UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_UPDATECONTENT_ALERT", nil) 
    UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil
							  // liuqw 2011/07/11 end                          
													   message:updateMsg
													  delegate:nil
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:nil];
	[alertView show];
	[alertView release];
}
// 初回起動時に更新内容の表示 end


#pragma mark -
#pragma mark Rotation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation 
{
	//return YES;
	// AR NO.17539 の対応 start
	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
	// AR NO.17539 の対応 end
}

// FileSort の対応 start
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
	// xuxinjun 2012.04.06 start
	// 保護文書の対応
	if([self.alertViewInputPassword isVisible])
	{
		[self setInputPasswordViewPositionWithOrientation:toInterfaceOrientation];
	}
	// xuxinjun 2012.04.06 end
	
	[self.tableView reloadData];
}
// FileSort の対応 end


#pragma mark -
#pragma mark action for document list.
// Load files in directory.
- (void) loadAllFileNamesInDocumentDirectory
{
	// tongtx 20110920 start
	// NS-AR029 の対応
	if (isUpdateFileNameFromDetailView == YES) {
		isUpdateFileNameFromDetailView = NO;
		return;
	}
	// tongtx 20110920 end
	
	// FileSort の対応 start
	//NSMutableArray *tempFileNames = [[NSMutableArray alloc]init];
	NSMutableArray *tempFileInfos = [[NSMutableArray alloc]init];
	// FileSort の対応 end
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
    NSString *dir = [paths objectAtIndex:0];
	NSFileManager *filemanager = [NSFileManager defaultManager];
	NSArray *files = [filemanager contentsOfDirectoryAtPath:dir error:nil];
	NSString *hiddenFilePrefix = @".";
	
	//check item style
	BOOL bIsDirectory = NO;
	NSString *fullPath;
	
	for (NSString* item in files) {
		if ([item characterAtIndex:0] == [hiddenFilePrefix characterAtIndex:0]) {
			continue;
		}
		if ([[item pathExtension] caseInsensitiveCompare:@"plist"] == NSOrderedSame) {
			continue;
		}
		
		//check item is a directory or a file name
		fullPath = [dir stringByAppendingPathComponent:item];
		[filemanager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		if ( bIsDirectory ) {
			continue;
		}
		
		// FileSort の対応 start
		//[tempFileNames addObject:item];
		DWFileInfo* dwFileInfo = [DWFileInfo new];
		dwFileInfo.fileName = item;
		NSDictionary *fileAttrs = [filemanager attributesOfItemAtPath:fullPath error:nil];
		dwFileInfo.fileSize = [fileAttrs objectForKey:NSFileSize];
		dwFileInfo.fileUpdateDate = [fileAttrs objectForKey:NSFileModificationDate];
		
		// xuxinjun 2012.03.27 start
		// 保護文書の対応
		dwFileInfo.fileProtected = [self.authenticationManager isDocumentProtected:fullPath];
		// xuxinjun 2012.03.27 end
		
		//File Multiple Del by Yangjx 0603 start
		dwFileInfo.isCheck = NO;
		//File Multiple Del by Yangjx 0603 end
        
		[tempFileInfos addObject:dwFileInfo];
		// FileSort の対応 end
		
		// Memory Leak の対応 by yangjx 0627 start
		[dwFileInfo release];
		// Memory Leak の対応 by yangjx 0627 end
	}
	
	// FileSort の対応 start
	/*
	 // sorts the arrays according to the lexical ordering.
	 NSSortDescriptor *desc = [[NSSortDescriptor alloc] initWithKey:nil
	 ascending:YES
	 selector:@selector(localizedCompare:)]; 
	 
	 NSArray *sortedFileNames = [tempFileNames sortedArrayUsingDescriptors:[NSArray arrayWithObject:desc]];
	 [tempFileNames release];
	 [desc release];
	 
	 if ([fileNames count] > 0) {
	 [fileNames removeAllObjects];
	 }
	 [fileNames addObjectsFromArray:sortedFileNames];
	 */
	
	NSString *keyName = @"fileName";
	if (fileSortItemIndex == 0) 
	{
		keyName = @"fileName";
	} 
	else if (fileSortItemIndex == 1) 
	{
		keyName = @"fileUpdateDate";
	} 
	else 
	{
		keyName = @"fileSize";
	}
	NSSortDescriptor *desc = nil;
	
	// liuqw 20110329 start
	// ソート機能の不具合の対応
	
	/*
	 if (fileSortModeIndex == 0) {
	 desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:YES];
	 } 
	 else
	 {
	 desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:NO];
	 }
	 */
	
	if (fileSortModeIndex == 0) {
		if (fileSortItemIndex == 0) {
			// liuqw 20110406 start
			// ファイル名ソートのロジック確認の対応
			/*
			 desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:YES 
			 selector:@selector(caseInsensitiveCompare:)];
			 */
			desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:YES 
												selector:@selector(localizedCaseInsensitiveCompare:)];
			// liuqw 20110406 end
		} else {
			desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:YES];
		}
	} 
	else
	{
		if (fileSortItemIndex == 0) {
			// liuqw 20110406 start
			// ファイル名ソートのロジック確認の対応
			/*
			 desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:NO
			 selector:@selector(caseInsensitiveCompare:)];
			 */
			desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:NO
												selector:@selector(localizedCaseInsensitiveCompare:)];
			// liuqw 20110406 end
		} else {
			desc = [[NSSortDescriptor alloc] initWithKey:keyName ascending:NO];
		}
	}
	
	// liuqw 20110329 end
	
	NSArray *sortedFileInfos = [tempFileInfos sortedArrayUsingDescriptors:[NSArray arrayWithObject:desc]];
	[tempFileInfos release];
	[desc release];
	
	if ([fileInfos count] > 0) {
		[fileInfos removeAllObjects];
	}
	[fileInfos addObjectsFromArray:sortedFileInfos];
	// FileSort の対応 end
}

- (void) setTabelViewCellInfo:(UITableViewCell*)cell withCellIndex:(int)index
{
	// FileSort の対応 start
	//NSString *cellText = [[fileNames objectAtIndex:index] retain];
	DWFileInfo *dwFileInfo = [fileInfos objectAtIndex:index];
	NSString *cellText = dwFileInfo.fileName;
	NSString* fileSize = Utility::formatFileSize(dwFileInfo.fileSize);
	cell.textLabel.text = cellText;
	cell.detailTextLabel.text = Utility::formatFileUpdateDate(dwFileInfo.fileUpdateDate, DATE_FILE_FORMAT);
	if (Utility::UIDeviceIsiPad()) 
	{
		cell.textLabel.font = [UIFont systemFontOfSize: Utility::IPAD_LIMIT_UI_FONT_SIZE];
		cell.detailTextLabel.font = [UIFont systemFontOfSize:Utility::IPAD_LIMIT_UI_FONT_ATTRIBUTESIZE];
	}
	else 
	{
		cell.textLabel.font = [UIFont systemFontOfSize: Utility::IPHONE_LIMIT_UI_FONT_SIZE];
		cell.detailTextLabel.font = [UIFont systemFontOfSize:Utility::IPHONE_LIMIT_UI_FONT_ATTRIBUTESIZE];
	}
	[cell.textLabel sizeToFit];
	[cell.detailTextLabel sizeToFit];
	
	// get file size label frame.
	float rowHeight = self.tableView.rowHeight;
	float textlabelHeight = cell.textLabel.frame.size.height;
	float detailTextlabelHeight = cell.detailTextLabel.frame.size.height;
	float screenWidth = [[UIScreen mainScreen] bounds].size.width;
	if ((self.interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || 
		(self.interfaceOrientation == UIInterfaceOrientationLandscapeRight))
	{
		screenWidth = [[UIScreen mainScreen] bounds].size.height;
	}
	float fileSizeLabelWidth = _FILE_SIZE_LABEL_WIDTH_;
	float fileSizeLabelHeight = detailTextlabelHeight;
	float fileSizeLabelOriginX = screenWidth - fileSizeLabelWidth - FILE_SIZE_LABEL_OFFSET;
	float fileSizeLabelOrininY = (int)((rowHeight - textlabelHeight - detailTextlabelHeight) / 2) + textlabelHeight + FILE_SIZE_LABEL_HOFFSET;
	CGRect fileSizeRect = CGRectMake(fileSizeLabelOriginX, fileSizeLabelOrininY, fileSizeLabelWidth, fileSizeLabelHeight);
	
	// add file size label to cell.
	UILabel *fileSizeLabel = (UILabel*)[cell.contentView viewWithTag:FILE_SIZE_LABEL_TAG];
	if (fileSizeLabel == nil) 
	{
		UILabel *fileSizeLabel = [[UILabel alloc] initWithFrame:fileSizeRect];
		fileSizeLabel.backgroundColor = [UIColor clearColor];
		fileSizeLabel.textColor = [UIColor grayColor];
		fileSizeLabel.text = fileSize;
		fileSizeLabel.textAlignment = UITextAlignmentRight;
		fileSizeLabel.tag = FILE_SIZE_LABEL_TAG;
		// yangjx 20110622 start
		// AR17854 の対応
		// Set Hightlighted Text Color 2011/06/21 M.Chikyu
		fileSizeLabel.highlightedTextColor = [UIColor whiteColor];
		// yangjx 20110622 end
		if (Utility::UIDeviceIsiPad()) {
			fileSizeLabel.font = [UIFont systemFontOfSize:(Utility::IPAD_LIMIT_UI_FONT_ATTRIBUTESIZE)];
		} else {
			fileSizeLabel.font = [UIFont systemFontOfSize:(Utility::IPHONE_LIMIT_UI_FONT_ATTRIBUTESIZE)];
		}
		[cell.contentView addSubview:fileSizeLabel];
		[fileSizeLabel release];
	} 
	else 
	{
		//update the text of file size label
		fileSizeLabel.frame = fileSizeRect;
		fileSizeLabel.text = fileSize;
		//fileSizeLabel.backgroundColor = [UIColor clearColor];
		//fileSizeLabel.textAlignment = UITextAlignmentRight;
	}
	// FileSort の対応 end
	
	//「文書情報ボタン」の追加 start
	
	/*
	if ([[cellText pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame)
	{ // XDW item.
		cell.accessoryType = UITableViewCellAccessoryNone;
		cell.imageView.image = [UIImage imageNamed:[self getXdwDocumentIcon]];
	} 
	else if ([[cellText pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
	{ // XBD item.
		cell.accessoryType = UITableViewCellAccessoryNone;
		cell.imageView.image = [UIImage imageNamed:[self getXbdDocumentIcon]];
	}
	else if ([[cellText pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame)
	{ // PDF item.
		cell.accessoryType = UITableViewCellAccessoryNone;
		cell.imageView.image = [UIImage imageNamed:[self getPDFDocumentIcon]];
	}
	else
	{ // unknown item.
		cell.accessoryType = UITableViewCellAccessoryNone;
		cell.imageView.image = [UIImage imageNamed:@"unknown.png"];
	}
	*/
	
	// xuxinjun 2012.03.27 start
	// 保護文書の対応
	/*
	if ([[cellText pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame)
	{
		cell.imageView.image = [UIImage imageNamed:[self getXdwDocumentIcon]];
	} 
	else if ([[cellText pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
	{ 
		cell.imageView.image = [UIImage imageNamed:[self getXbdDocumentIcon]];
	}
	 */
	if ([[cellText pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame)
	{
		if (dwFileInfo.fileProtected == YES)
		{
			cell.imageView.image = [UIImage imageNamed:[self getXdwProtectedDocumentIcon]];
		}
		else
		{
			cell.imageView.image = [UIImage imageNamed:[self getXdwDocumentIcon]];
		}
	} 
	else if ([[cellText pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
	{ 
		if (dwFileInfo.fileProtected == YES)
		{
			cell.imageView.image = [UIImage imageNamed:[self getXbdProtectedDocumentIcon]];
		}
		else
		{
			cell.imageView.image = [UIImage imageNamed:[self getXbdDocumentIcon]];
		}
	}
	// xuxinjun 2012.03.27 end
	
	else if ([[cellText pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame)
	{ 
		cell.imageView.image = [UIImage imageNamed:[self getPDFDocumentIcon]];
	}
	else
	{ 
		cell.imageView.image = [UIImage imageNamed:@"unknown.png"];
	}
	cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
	
	// yangjx 20110623 start
	// AR17859 の対応
	cell.selectionStyle = UITableViewCellSelectionStyleBlue;
	// yangjx 20110623 end
	
	//「文書情報ボタン」の追加 end
	//[cellText release];
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
/*
 - (XdwAttributeParser *) createXdwAttrubuteParse:(NSString *)filePath
 {
 XdwAttributeParser *attributeParse = new XdwAttributeParser();
 if (attributeParse != XdwNull) {
 const char *cFilePath = [filePath UTF8String];
 XdwErrorCode retCode = attributeParse->SetFile(cFilePath);
 if (retCode == XDW_ERRORCODE_SUCCESS) {
 return attributeParse;
 }
 } else {
 if (attributeParse) {
 delete attributeParse;
 attributeParse = XdwNull;
 }
 }
 return XdwNull;
 }
 */
// xuxinjun 2012.03.23 end

//「文書情報ボタン」の動作 end

- (void) didSelectRowInTableViewWithIndex:(int)index
{
	// release old controller.
	if (activeViewController != nil) {
		[activeViewController release];
		activeViewController = nil;
	}
	
	// get delete file path with document directory and delete file name.
	NSString *filePath = [[self getDocumentFilePathWithIndex:index] retain];
	
	// get current select file name.
	NSString* fileName = [[self getDocumentFileNameWithIndex:index] retain];
	
	// get file manager.
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	// find document file with file path.
	BOOL bSuccess = [fileManager fileExistsAtPath:filePath];
	if (bSuccess == NO) {
		UIAlertView *errorTwo = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
														  message:NSLocalizedString(@"MSG_ERROR_FILENAMEERROR", nil)
														 delegate:nil
												cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												otherButtonTitles:nil];
		[errorTwo show];
		[errorTwo release];
	} else {
        
        // liuqw 20110628 start
        // AR NO.17871 の対応
        
        /*
		 // create document view controller.
		 DocumentViewController* controller = [self createViewControllerWithFileName:fileName 
		 withFilePath:filePath]; 
		 if (controller != nil) {
		 activeViewController = controller;
		 [self.navigationController pushViewController:activeViewController animated:YES];
		 }
		 */
        
        if ([documentSettingsMgr isDocumentCanSaveSettings:fileName] == YES) {
            
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
			/*
			 // create document view controller.
			 DocumentViewController* controller = [self createViewControllerWithFileName:fileName 
			 withFilePath:filePath]; 
			 if (controller != nil) {
			 activeViewController = controller;
			 [self.navigationController pushViewController:activeViewController animated:YES];
			 }
			 */
					
			enum CHECK_PROTECTED_TYPE type = kCheckSelectRowInTableView;
			DW_PROTECTED_TYPE result = [self checkProtectedTypeWithActionType:type
																  andFilePath:filePath 
																  andFileName:fileName
																  andOtherInf:nil];
			if (result != kProtectTypePwd)
			{
				if (result == kProtectTypeNoPwd)
				{
					[self pushControllerWithActionType:type 
										   andFilePath:filePath 
										   andFileName:fileName 
										   andPassword:@""
										   andOtherInf:nil];
				}
				else
				{
					[self pushControllerWithActionType:type 
										   andFilePath:filePath 
										   andFileName:fileName 
										   andPassword:nil
										   andOtherInf:nil];
				}
			}
			// xuxinjun 2012.03.23 end 
			
        } else {
            
            selectCellIndex = index;
            
            UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
															   message:NSLocalizedString(@"MSG_FILE_NAME_OVERLENGTH", nil)
															  delegate:self
													 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
			alertView.tag = TAG_SETTINGS_NAME_ERROR;
			[alertView show];
			[alertView release];
        }
        // liuqw 20110628 end
	}
	
	[filePath release];
	[fileName release];
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
/*
 - (DocumentViewController*) createViewControllerWithFileName:(NSString*)name 
 withFilePath:(NSString*)path
 */
- (DocumentViewController*) createViewControllerWithFileName:(NSString*)name 
												withFilePath:(NSString*)path
												withPassword:(NSString*)pwd
// xuxinjun 2012.03.23 end

{
	DocumentViewController *documentViewController = nil;
	if (name == nil || path == nil) {
		return nil;
	}
	
	NSString* fileName = [name retain];
	NSString* filePath = [path retain];
	
	if ([[fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
		[[fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame ||
		[[fileName pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame) {
		
		// Load and display the xdw Document.
		// xuxinjun 2012.03.23 start
		// 保護文書の対応
		documentViewController = [[DocumentViewController alloc]initWithPath:filePath andOpenPassword:pwd];
		// xuxinjun 2012.03.23end
		
		if (documentViewController == nil) {
			// Memory Leak の対応 start
			[fileName release];
			[filePath release];
			// Memory Leak の対応 end
			return nil;
		}
        
        // liuqw 20110801 start
        // ページ編集機能の追加
        documentViewController.backButtonTitle = NSLocalizedString(@"MENU_FILELIST_TITLE", nil);
        // liuqw 20110801 end
		// set file name to controller
		documentViewController.title = fileName;
		documentViewController.fileName = fileName;
		documentViewController.delegate = self;//AR No.17581 by sun.chl 2010.12.17
		// get file manager.
		NSFileManager *fileManager = [NSFileManager defaultManager];
		// get file attributes
		NSDictionary *fileAtribute = [fileManager attributesOfItemAtPath:filePath error:nil];
		// get file creation date.
		NSString *fileCreateDate = [[fileAtribute objectForKey:NSFileCreationDate] description];
		// get file size.
		NSString *fileSize = [[fileAtribute objectForKey:NSFileSize] stringValue];
		// load document setting.
		[self loadDocumentStatusWithController:documentViewController 
								  withFileName:fileName 
							  withCreationDate:fileCreateDate 
							  withDocumentSize:fileSize];
	}
	//add for AR No44
	else if([[fileName pathExtension] caseInsensitiveCompare:@""] == NSOrderedSame){ 
		UIAlertView *errorOne = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
														 // message:NSLocalizedString(@"MSG_ERROR_FILEDEFAULTERROR", nil)
														  message:NSLocalizedString(@"MSG_ERROR_FILETYPEERROR", nil) // 20101222 M.Chikyu修正
														 delegate:nil
												cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												otherButtonTitles:nil];
		[errorOne show];
		[errorOne release];	
	}
	else { 
		// change message when open a file without extension failed. change by lixin AR17576	
		UIAlertView *errorOne = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
														  message:NSLocalizedString(@"MSG_ERROR_FILETYPEERROR", nil)
														 delegate:nil
												cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												otherButtonTitles:nil];
		[errorOne show];
		[errorOne release];	
	}
	
	// release
	[fileName release];
	[filePath release];
	
	return documentViewController;
}

- (void) loadDocumentStatusWithController:(DocumentViewController*)controller 
							 withFileName:(NSString*)name 
						 withCreationDate:(NSString*)date 
						 withDocumentSize:(NSString*)size;
{
	if (controller == nil || name == nil || date == nil || size == nil) {
		return;
	}
	
	if (keepDocumentStatus == NO) {
		return;
	}
	
	DocumentViewController* documentViewController = [controller retain];
	NSString* fileName = [name retain];
	NSString* fileDate = [date retain];
	NSString* fileSize = [size retain];
	
	if (documentSettingsMgr != nil) {
		if ([documentSettingsMgr readDocumentStatusWithFileName:fileName
											   withCreationDate:fileDate 
											   withDocumentSize:fileSize] == YES) {
			
			int pageIndex = documentSettingsMgr.pageIndex;
			
			// liuqw 20110412 start
			// 「確認7」の対応
			if ([documentViewController UIDeviceIsPortrait] == YES) {
				// do nothing.
			} else {
				FacingMode toMode = (FacingMode)(documentSettingsMgr.facingMode);
				if (toMode == MODE_REGULAR) {
					// do nothing.
				} else {
					pageIndex = [documentViewController convertPageViewPosition:pageIndex
																   withFromMode:MODE_REGULAR
																	 withToMode:toMode];
				}
			}
			
			/*
			if ([documentViewController UIDeviceIsPortrait] == YES && 
				documentViewController.pageViewMgr.facingMode != MODE_REGULAR) {
				pageIndex = [documentViewController convertPageViewPosition:pageIndex
															   withFromMode:documentViewController.pageViewMgr.facingMode
																 withToMode:MODE_REGULAR];
			}
			*/
			// liuqw 20110412 end
			
			documentViewController.pageViewMgr.pageIndex = pageIndex;
			documentViewController.pageViewMgr.pageScale = documentSettingsMgr.pageScale;
			CGPoint offset = CGPointMake(documentSettingsMgr.pagePointX, documentSettingsMgr.pagePointY);
			documentViewController.pageViewMgr.pageOffset = offset;
			documentViewController.pageViewMgr.facingMode = (FacingMode)(documentSettingsMgr.facingMode);
			documentViewController.pageViewMgr.fontOrient = documentSettingsMgr.fontOrientationH;
			documentViewController.pageViewMgr.showAnnotation = documentSettingsMgr.showAnnotation;
			documentViewController.pageViewMgr.pageStatus = (PageStatus)documentSettingsMgr.pageStatus;
		} else {
			documentViewController.pageViewMgr.pageIndex = 0;
			documentViewController.pageViewMgr.isPageFit = YES;
			documentViewController.pageViewMgr.pageOffset = CGPointZero;
		}
	}
	
	// release
	[documentViewController release];
	[fileName release];
	[fileDate release];
	[fileSize release];
}

- (void) saveDocumentStatusWithController:(DocumentViewController*)controller
{
	if (controller == nil) {
		return;
	}
	DocumentViewController* documentViewController = [controller retain];
    
    // liuqw 20110628 start
    // AR NO.17871 の対応
    if (documentViewController.isCanSaveSettings == NO) {
        return;
    }
    // liuqw 20110628 end
	
	// FileSort の対応 start
	[documentSettingsMgr readDocumentSettings];
	keepDocumentStatus = documentSettingsMgr.keepStatus;
	// FileSort の対応 end
	
	if (keepDocumentStatus == NO) {
		documentViewController.fileName = nil;
		return;
	}
	
	NSString* filePath = [documentViewController.filePath retain];
	if (documentViewController.fileName == nil) {
		return;
	}
	
	NSString* selectFileName = [documentViewController.fileName retain];
	
	if (filePath != nil) {
		NSFileManager *fileManager = [NSFileManager defaultManager];
		NSDictionary *fileAtribute = [fileManager attributesOfItemAtPath:filePath error:nil];
		NSString *fileCreateDate = [[fileAtribute objectForKey:NSFileCreationDate] description];
		NSString *fileSize = [[fileAtribute objectForKey:NSFileSize] stringValue];
		
		int pageIndex = documentViewController.pageViewMgr.pageIndex;
		
		// liuqw 20110412 start
		// 「確認7」の対応
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
		
		[documentSettingsMgr writeDocumentStatusWithFileName:selectFileName
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
	}
	
	// release
	[documentViewController release];
	[filePath release];
	[selectFileName release];
}

- (BOOL) deleteDocumentWithFilePath:(NSString*)path
{
	if (path == nil)
		return NO;
	
	NSString* filePath = [path retain];
	
	UIAlertView *alertView = nil;
	NSFileManager *fileManager = [NSFileManager defaultManager];
	BOOL bSuccess = [fileManager fileExistsAtPath:filePath];
	if (bSuccess == NO) {
		alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
											  message:NSLocalizedString(@"MSG_FINDFILE_FAIL", nil)
											 delegate:nil
									cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									otherButtonTitles:nil];
		[alertView show];
		[alertView release];
		
	} else {
		//AR17495
		//display the message when delete failed.
		bSuccess = [fileManager removeItemAtPath:filePath error:nil];
		if (bSuccess != YES) {
			alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
												  message:NSLocalizedString(@"MSG_DELETEFILE_FAIL", nil)
												 delegate:nil
										cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
										otherButtonTitles:nil];
			[alertView show];
			[alertView release];
		}
	}
	//AR17495 end;
	// release
	[filePath release];
	
	return bSuccess;
}


// xuxinjun 2012.04.06 start
// 保護文書の対応
#pragma mark -
#pragma mark security file about.
- (DW_PROTECTED_TYPE) checkProtectedTypeWithActionType:(int)type
										   andFilePath:(NSString*)path 
										   andFileName:(NSString*)name 
										   andOtherInf:(void*)other
{
	DW_PROTECTED_TYPE result = kProtectTypeNull;
	
	if (name == nil || path == nil) return kProtectTypeNull;
	
	if ([[name pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
		[[name pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame) 
	{
		result = [self.authenticationManager checkDocumentProtectedType:path];
		if (result == kProtectTypePwd) 
		{
			actionType_			= type;
			self.authFullPath	= path;
			self.authFileName	= name;
			self.otherInfo		= (DWMTAAssociationInfo*)other;
			[self showAlertViewForInputPassword];
		}
	}
	
	return result;
}

- (void) pushControllerWithActionType:(int)type 
						  andFilePath:(NSString*)path
						  andFileName:(NSString*)name 
						  andPassword:(NSString*)pwd
						  andOtherInf:(void*)other
{
	if (path == nil || name == nil) 
		return;
	
	DocumentViewController* controller = [self createViewControllerWithFileName:name 
																   withFilePath:path
																   withPassword:pwd];
	if (controller == nil) 
		return;
	
	switch (type) {
		case (int)kCheckSelectRowInTableView:
		{
			break;
		}
			
		case (int)kCheckSettingsNameError:
		{
			controller.isCanSaveSettings = NO;
			break;
		}
			
		case (int)kCheckEditingFile:
		case (int)kCheckUTIAssociate:
		{
			[controller performSelector:@selector(hideAllToolbarItems:) 
							 withObject:[NSNumber numberWithBool:NO] 
							 afterDelay:0];
			break;
		}
			
		case (int)kCheckDownloadFinish:
			break;
			
		case (int)kCheckBrifecase:
		{
			controller.fromBriefCase	= YES;
			controller.backButtonTitle	= MENU_BRIEFCASE_TITLE;
			controller.title			= name;
			controller.fileName			= name;
			controller.delegate			= self;
			
			break;
		}
			
		case (int)kCheckOpenAssociatedFile:
		{
			if (other != nil)
			{
				DWMTAAssociationInfo* info_ = [(DWMTAAssociationInfo*)other retain];
				int index = info_.pageIndex;
				int pageCount = controller.pageViewMgr.pageTotalCount;
				if (index < 0 || index > pageCount - 1) index = 0;
				controller.isFromMTA                = YES;
				controller.backButtonTitle          = info_.backButtonTitle;
				controller.title                    = name;
				controller.fileName                 = name;
				controller.pasteboardFromMTA        = info_.pasteboard;
				controller.folderNameFromMTA        = info_.folderName;
				controller.pageViewMgr.pageIndex    = index;
				controller.appnameFromMTA           = info_.appName;
				
				[info_ release];
			}
			controller.delegate						= self;
			
			[controller performSelector:@selector(hideAllToolbarItems:) 
							 withObject:[NSNumber numberWithBool:NO] 
							 afterDelay:0];
			
			break;
		}
			
		default:
			break;
	}
	
	[self.navigationController pushViewController:controller animated:YES];
	[controller release];
}

- (void) showAlertViewForInputPassword
{
	NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
	[notificationCenter addObserver:self 
                           selector:@selector(actionOnKeyboardDidShow) 
                               name:UIKeyboardDidShowNotification
                             object:nil];
	
	self.alertViewInputPassword = [[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"MSG_AUTH_ALERT_PASSWORD_TITLE",nil)
															  message:@"   "
															 delegate:self
													cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), 
									(char *)nil] autorelease];
	
	self.alertViewInputPassword.delegate					= self;
	self.alertViewInputPassword.tag							= TAG_ALERT_INPUT_PWD;
	
	self.fieldTextInputPassword = [[[UITextField alloc] init]autorelease];
	self.fieldTextInputPassword.adjustsFontSizeToFitWidth	= YES;
	self.fieldTextInputPassword.autocorrectionType			= UITextAutocorrectionTypeNo;
	self.fieldTextInputPassword.clearButtonMode				= UITextFieldViewModeWhileEditing;
	self.fieldTextInputPassword.minimumFontSize				= 2.0;
	self.fieldTextInputPassword.secureTextEntry				= YES;
	self.fieldTextInputPassword.keyboardType				= UIKeyboardTypeNumbersAndPunctuation;
	self.fieldTextInputPassword.borderStyle					= UITextBorderStyleRoundedRect;
	self.fieldTextInputPassword.placeholder					= NSLocalizedString(@"MSG_AUTH_ALERT_VIEW_PLACEHOLDER", nil);
	self.fieldTextInputPassword.returnKeyType				= UIReturnKeyDone;
	self.fieldTextInputPassword.frame						= CGRectZero;
	self.fieldTextInputPassword.font						= [UIFont systemFontOfSize:18.0];
	self.fieldTextInputPassword.tag							= TAG_FIELD_INPUT_PWD;
	self.fieldTextInputPassword.text						= nil;
	self.fieldTextInputPassword.delegate					= self;
	
	[self.alertViewInputPassword addSubview:self.fieldTextInputPassword];
	[self.alertViewInputPassword show];
	[self.fieldTextInputPassword becomeFirstResponder];
}

- (void) setInputPasswordViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    if (Utility::UIDeviceIsiPad() == NO)
	{
		float originX, originY, width, height;
		
		if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation))
		{
			originX = fieldTextInputPassword_.frame.origin.x;
			originY = fieldTextInputPassword_.frame.origin.y - 9;    
			width = 200;
			height = 22;
		}
		else
		{
			originX = fieldTextInputPassword_.frame.origin.x;
			originY = fieldTextInputPassword_.frame.origin.y + 10;    
			width = 200;
			height = 30;
		}
		fieldTextInputPassword_.frame = CGRectMake(originX, originY, width, height);
    }
	else
	{
        float originX, originY, width, height;
		
        if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation))
		{
            originX = fieldTextInputPassword_.frame.origin.x;
            originY = fieldTextInputPassword_.frame.origin.y - 8;
            width = 200;
            height = 27;
        }
		else
		{
            originX = fieldTextInputPassword_.frame.origin.x;
            originY = fieldTextInputPassword_.frame.origin.y + 8;
            width = 200;
            height = 30;
        }
        fieldTextInputPassword_.frame = CGRectMake(originX, originY, width, height);
    }
}

- (void) actionOnKeyboardDidShow
{
	UILabel* labelTitle =  ((UILabel*)[[self.alertViewInputPassword subviews] objectAtIndex:1]);
	
    if (labelTitle != nil)
	{
        float originX = 45;
        float originY = labelTitle.frame.origin.y + labelTitle.frame.size.height; 
        float width = 200;
        float height = 0;
        float offset = 0;
		
		if (Utility::UIDeviceIsiPad() == NO)
		{
            if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
			{
                height = 30;
                offset = 4;
            }
			else
			{
                height = 22;
                offset = 2;
            }
        }
		else
		{
            if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
			{
                height = 30;
                offset = 4;
            }
			else
			{
                height = 27;
                offset = 4;
            }
        }
        fieldTextInputPassword_.frame = CGRectMake(originX, originY + offset, width, height);
	}
	
	NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
	[[NSNotificationCenter defaultCenter] removeObserver:self 
													name:UIKeyboardDidShowNotification 
												  object:nil];
}
// xuxinjun 2012.04.06 end


#pragma mark -
#pragma mark Sort Toolbar button.
// yangjx 20110622 start
// AR17848 の対応
- (void) actionTouchSortButton:(UIBarButtonItem *)buttonItem
{
	FileSortSettingsViewController *filesortController = [[FileSortSettingsViewController alloc] initWithStyle:UITableViewStyleGrouped];
	filesortController.sortItemIndex = fileSortItemIndex;
	filesortController.sortModeIndex = fileSortModeIndex;
	[self.navigationController pushViewController:filesortController animated:YES];
	[filesortController release];
}
// yangjx 20110622 end


#pragma mark -
#pragma mark Edit Toolbar button.
- (void) actionTouchEditButton:(UIBarButtonItem*)buttonItem
{
	UIBarButtonItem* doneItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_DONE", @"")
														 action:@selector(actionTouchDoneButton:)];
	doneItem.style = UIBarButtonItemStyleDone;
	self.navigationItem.rightBarButtonItem = doneItem;
	isEditMode = YES;
	[self setEditing:isEditMode];
	[self setEditModeToolbar];
}

- (void) actionOnTouchCheckAllButton:(UIBarButtonItem *)buttonItem
{   
	//del button status changed by yangjx 0617 start
	[self.tableView setEditing:NO];
	//del button status changer by yangjx 0617 end
	//edit modify by yangjx 0616
	
	// yangjx 20110623 start
	// AR17850 の対応
	if ([selectFileInfos count] == [fileInfos count]) {
		[self uncheckAllFilesInList];
	} else {
		[self checkAllFilesInList];
	}
    // yangjx 20110623 end
	[self setToolbarItemsStatus];
}

- (void) actionOnTouchSendEmailButton:(UIBarButtonItem *)buttonItem
{
	
	NSString *errorMessage = nil;
	BOOL isValid = YES;
    
    if ([selectFileInfos count] > EMAIL_MAX_FILE_COUNT) {
        isValid = NO;
        errorMessage = NSLocalizedString(@"MSG_WARING_FILECOUNT_OUT", nil); 
    } else {
        float size = 0.0;
        for(DWFileInfo *dwFileInfo in selectFileInfos) {
			if (dwFileInfo.fileSize != nil) {
				size = size + [dwFileInfo.fileSize floatValue];
			}
		}
        
        if ((size / pow(1024, 2)) > EMAIL_MAX_FILE_SIZE) {
			isValid = NO;
			errorMessage = NSLocalizedString(@"MSG_WARING_FILESIZE_OUT", nil);
		}
    }
	
	if (isValid == YES) {
		NSInteger fileCount = [selectFileInfos count];
		NSString *message = [NSString stringWithFormat:NSLocalizedString(@"MSG_WARING_SENDEMAIL", nil) ,fileCount];
		
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
														   message:message
														  delegate:self
												 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
		alertView.tag = ALERT_SENDEMAIL_TAG;
		[alertView show];
		[alertView release];
	} else {
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
														   message:errorMessage
														  delegate:self
												 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												 otherButtonTitles:nil, (char*)nil];
		[alertView show];
		[alertView release];
	}
}

- (void) actionOnTouchDeleteButton:(UIBarButtonItem *)buttonItem
{
	NSInteger fileCount = [selectFileInfos count];
	NSString *message = [NSString stringWithFormat:NSLocalizedString(@"MSG_WARING_DELETE_FILE", nil) ,fileCount];
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
													   message:message
													  delegate:self
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
	alertView.tag = ALERT_MULTIDEL_TAG;
	[alertView show];
	[alertView release];
}

- (void) actionOnTouchRestoreButton:(UIBarButtonItem *)buttonItem
{
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
													   message:NSLocalizedString(@"MSG_WARING_RESTORE_FILE", nil) 
													  delegate:self
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
	alertView.tag = ALERT_CANCELDEL_TAG;
	[alertView show];
	[alertView release];
}

- (void) actionTouchDoneButton:(UIBarButtonItem*)buttonItem
{
	UIBarButtonItem* editItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_EDIT", @"")
														 action:@selector(actionTouchEditButton:)];
	self.navigationItem.rightBarButtonItem = editItem;
	// yangjx 20110622 start
	// AR17848 の対応
	UIBarButtonItem *sortItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_SORT", @"") 
														 action:@selector(actionTouchSortButton:)];
	self.navigationItem.leftBarButtonItem = sortItem;
	// yangjx 20110622 end
	
	[self addEnvironmentSettingsButtonToToolbar];
	isEditMode = NO;
	[self setEditing:isEditMode];
}

- (UIBarButtonItem*) createButtonItemWithTitle:(NSString*)title action:(SEL)action
{
	UIBarButtonItem* buttonItem = [[UIBarButtonItem alloc] initWithTitle:title
																   style:UIBarButtonItemStyleBordered
																  target:self
																  action:action];
	return [buttonItem autorelease];
}

- (void) setEditModeToolbar
{
	NSMutableArray *editToolBarItems = [[NSMutableArray alloc] init];
	
	// create flex space 
	UIBarButtonItem	*flexSpace = [[[UIBarButtonItem alloc] 
								   initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
								   target:self action:nil]autorelease];
	
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	/*
	// modify by yangjx 20110624 start
	//create sendemail button
	UIButton *sendEmailButton = [self getToolbarButton:[self getSendEmailButtonIcon]];
	[sendEmailButton addTarget:self 
						  action:@selector(actionOnTouchSendEmailButton:)
				forControlEvents:UIControlEventTouchUpInside];
	UIBarButtonItem *sendEmailItem = [[[UIBarButtonItem alloc] initWithCustomView:sendEmailButton] autorelease];
	sendEmailItem.style = UIBarButtonItemStylePlain;
	// modify by yangjx 20110624 end
	*/
	//create sendemail button
	UIBarButtonItem *sendEmailItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getSendEmailButtonIcon]]
																	  style:UIBarButtonItemStylePlain 
																	 target:self
																	 action:@selector(actionOnTouchSendEmailButton:)];
	// lixin 2011/09/29 end
	
	//create del button
	// lixin 2011/09/15 start 
	// NS-AR012 の対応
	/*
	 UIBarButtonItem *delFileItem = [[[UIBarButtonItem alloc] 
	 initWithBarButtonSystemItem:UIBarButtonSystemItemTrash 
	 target:self action:@selector(actionOnTouchDeleteButton:)]autorelease];
	 */
	
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	/*
	UIButton* deleteButton = [self getToolbarButton:[self getDeleteButtonIcon]];
	[deleteButton addTarget:self 
					 action:@selector(actionOnTouchDeleteButton:)
		   forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem *delFileItem = [[[UIBarButtonItem alloc] initWithCustomView:deleteButton] autorelease];
	delFileItem.style = UIBarButtonItemStylePlain;
	// lixin 2011/09/15 end
	*/
	UIBarButtonItem *delFileItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]]
																	style:UIBarButtonItemStylePlain 
																   target:self
																   action:@selector(actionOnTouchDeleteButton:)];
	// lixin 2011/09/29 end
	
	//create undo button
	UIBarButtonItem *cancelDelFileItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_CANCELDELETE", @"") 
																  action:@selector(actionOnTouchRestoreButton:)];
	
	
	//edit modify by yangjx 0616
	[editToolBarItems addObject:flexSpace];
	[editToolBarItems addObject:delFileItem];
	[editToolBarItems addObject:cancelDelFileItem];
	[editToolBarItems addObject:flexSpace];
	[editToolBarItems addObject:sendEmailItem];
	[editToolBarItems addObject:flexSpace];

	self.toolbarItems = editToolBarItems;
	[self setToolbarItemsStatus];
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	[delFileItem release];
	[sendEmailItem release];
	// lixin 2011/09/29 end
	[editToolBarItems release];
}

- (void) setEditing:(BOOL)edit
{
	//del button status changed by yangjx 0617 start
	[self.tableView setEditing:NO];
	//del button status changer by yangjx 0617 end
	
	NSArray *indexPaths = [self.tableView indexPathsForVisibleRows];
	[self.tableView reloadRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationNone];	
	
	[self checkAllFiles:NO];
	
	if (selectFileInfos != nil) {
		[selectFileInfos removeAllObjects];
		self.selectFileInfos = nil;
	}
	
	if (edit == YES) {
	// Memory Leak の対応 by yangjx 0627 start
	   selectFileInfos = [[NSMutableArray alloc] init];
	// Memory Leak の対応 by yangjx 0627 end
	} 
}

//  set allfiles status
- (void) checkAllFiles:(BOOL)check
{
	for (DWFileInfo *fileInfo in fileInfos) {
		fileInfo.isCheck = check;
	}
}

// set toolbar Items status
- (void) setToolbarItemsStatus
{
	UIBarButtonItem *sendEmailItem = nil;
	UIBarButtonItem *delFileItem = nil;
	UIBarButtonItem *cancelDelFileItem = nil;
	
	//modify by yangjx 0616
	//get selectAllButton status
	
	// yangjx 20110623 start
	// AR17850 の対応
	if ([selectFileInfos count] == [fileInfos count] && [fileInfos count] != 0) {
		UIBarButtonItem *unSelectItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_UNSLECTALL", @"") 
																 action:@selector(actionOnTouchCheckAllButton:)];
		self.navigationItem.leftBarButtonItem = unSelectItem;
		unSelectItem.style = UIBarButtonItemStyleDone;		
	} else {
		UIBarButtonItem *selectAllItem = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_SLECTALL", @"") 
																  action:@selector(actionOnTouchCheckAllButton:)];
		self.navigationItem.leftBarButtonItem = selectAllItem;
	}
    // yangjx 20110623 end
	
	sendEmailItem = (UIBarButtonItem *)[self.toolbarItems objectAtIndex:4];
	delFileItem = (UIBarButtonItem *)[self.toolbarItems objectAtIndex:1];
	cancelDelFileItem = (UIBarButtonItem *)[self.toolbarItems objectAtIndex:2];
	
	if ([selectFileInfos count] == 0) {
		sendEmailItem.enabled = NO;
		delFileItem.enabled = NO;
	} else {
		sendEmailItem.enabled = YES;
		delFileItem.enabled = YES;
	}
    
	//set canceldel buttoitem status
	NSArray *rootPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, 
															 YES); 
	NSString *documentsPath = [rootPaths objectAtIndex:0];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *trashDirectoryPath = [documentsPath stringByAppendingString:_TRASH_DIR_];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:trashDirectoryPath];
	if (isDirectoryExist) {
		NSArray *fileItemList = [fileManager contentsOfDirectoryAtPath:trashDirectoryPath error:nil];
		[fileItemList count] == 0 ? cancelDelFileItem.enabled = NO : cancelDelFileItem.enabled = YES;
	} else {
		cancelDelFileItem.enabled = NO;
	}
}

// set file isSelect status 
- (void) setUITableViewCellAccessoryType:(UITableViewCell *)cell withCheckStatus:(BOOL)check
{
    if (cell != nil) {
        if (isEditMode) {
            if (check == YES) {
                // yangjx 20110623 start
                // AR17859 の対応
                cell.selectionStyle = UITableViewCellSelectionStyleBlue;
                // yangjx 20110623 end
                
                cell.accessoryType = UITableViewCellAccessoryCheckmark;
                [cell setSelected:YES animated:NO];
                [cell setHighlighted:YES animated:NO];
            } else {
                // yangjx 20110623 start
                // AR17859 の対応
                cell.selectionStyle = UITableViewCellSelectionStyleNone;
                // yangjx 20110623 end
                
                cell.accessoryType = UITableViewCellAccessoryNone;
                [cell setSelected:NO animated:NO];
                [cell setHighlighted:NO animated:NO];
            }
        }
    }
}

// select all file
- (void) checkAllFilesInList
{
	[self checkAllFiles:YES]; 	
	NSArray *indexPaths = [self.tableView indexPathsForVisibleRows];
	[self.tableView reloadRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationNone];
	
	if (selectFileInfos != nil) {
		[selectFileInfos removeAllObjects];
		self.selectFileInfos = nil;
	}
	
	// Memory Leak の対応 by yangjx 0627 start
	selectFileInfos = [[NSMutableArray alloc] initWithArray:fileInfos];
	// Memory Leak の対応 by yangjx 0627 start
}

// usSelect all file
- (void) uncheckAllFilesInList
{
	[self checkAllFiles:NO];
	NSArray *indexPaths = [self.tableView indexPathsForVisibleRows];
	[self.tableView reloadRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationNone];
	if (selectFileInfos != nil) {
		[selectFileInfos removeAllObjects];
		self.selectFileInfos = nil;
	}
	// Memory Leak の対応 by yangjx 0627 start
	selectFileInfos = [[NSMutableArray alloc] init];
	// Memory Leak の対応 by yangjx 0627 start
}

// get mail attachment data
- (void) getAttachmentDataWithFilePath:(NSString *)filePath 
					   forMFMailPicker:(MFMailComposeViewController *)mailPicker
{
	if (filePath == nil || mailPicker == nil) {
		return;
	}
    
	NSString *fileName = [filePath lastPathComponent];
	// tongtx 20110627 start
	// AR17880
	//NSString *mimeType = Utility::getAttachmentMIMEType([fileName pathExtension]);
	NSString *mimeType = Utility::getAttachmentMIMEType(filePath);
	// tongtx 20110627 end
	NSData *attachmentData = [NSData dataWithContentsOfFile:filePath];
	
	if (mimeType != nil && [attachmentData length] > 0)
	{
		[mailPicker addAttachmentData:attachmentData 
							 mimeType:mimeType 
							 fileName:fileName];
	}
}

// send Email with data
- (void) sendEmailInDirectoryView
{
		Class mailClass = NSClassFromString(@"MFMailComposeViewController");
		if (mailClass != nil && [MFMailComposeViewController canSendMail]) 
		{
			MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
			picker.mailComposeDelegate = self;
			
			for (int i = 0; i < [selectFileInfos count]; i++) {
				NSString *filePath = nil;
				DWFileInfo *dwFileInfo = [selectFileInfos objectAtIndex:i];
				filePath = [[documentSettingsMgr getDocumentFilePathWithFileName:dwFileInfo.fileName] retain];
				[self getAttachmentDataWithFilePath:filePath 
									forMFMailPicker:picker];
				[filePath release];
			}
			
			[self presentModalViewController:picker animated:YES];
			[picker release];
		}
}

//#pragma mark -
//#pragma mark mailComposeDelegate
- (void)mailComposeController:(MFMailComposeViewController *)controller 
		  didFinishWithResult:(MFMailComposeResult)result 
						error:(NSError *)error

{
	[self becomeFirstResponder];
	[self dismissModalViewControllerAnimated:YES];
	
	if (Utility::UIDeviceIsiPad()){
		[self checkAllFiles:NO]; 
		[self.tableView reloadData];
	}
	
	//muti select add by yangjx 0613 start
	if (selectFileInfos != nil) {
		[selectFileInfos removeAllObjects];
		self.selectFileInfos = nil;
	}
	// Memory Leak の対応 by yangjx 0627 start
	selectFileInfos = [[NSMutableArray alloc] init];
	// Memory Leak の対応 by yangjx 0627 start
	//muti select add by yangjx 0613 end
	
	[self setToolbarItemsStatus];
}


#pragma mark -
#pragma mark environment Toolbar button.
// add environment settings button to toolbar.
- (void) addEnvironmentSettingsButtonToToolbar
{
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	/*
	 // init environment settings button.
	 UIButton *envSettingsButton = [self getToolbarButton:[self getEnvironmentSettingsIcon] ];
	 [envSettingsButton addTarget:self 
	 action:@selector(actionTouchEnvironmentSettingsButton) 
	 forControlEvents:UIControlEventTouchUpInside];
	 
	 // init toolbar button item.
	 UIBarButtonItem *buttonItem = [[[UIBarButtonItem alloc] initWithCustomView:envSettingsButton] autorelease];
	 buttonItem.style = UIBarButtonItemStylePlain;
	 
	 // add environment settings button to toolbar button items.
	 NSMutableArray *toolbarButtonItems = [[NSMutableArray alloc]init];
	 [toolbarButtonItems addObject:buttonItem];
	 */
	// init toolbar button item.
	UIBarButtonItem* envSettingButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getEnvironmentSettingsIcon]]
																			 style:UIBarButtonItemStylePlain 
																			target:self 
																			action:@selector(actionTouchEnvironmentSettingsButton)];
	
	// add environment settings button to toolbar button items.
	NSMutableArray *toolbarButtonItems = [[NSMutableArray alloc]init];
	[toolbarButtonItems addObject:envSettingButtonItem];
	[envSettingButtonItem release];
	// lixin 2011/09/29 end
	
	// 3.5アプリ情報機能の追加 の対応 start 
	// change by lixin 20110607 DW_iPhoneEnhance_12
	
	// create flex space 
	UIBarButtonItem	*flexSpace = [[[UIBarButtonItem alloc] 
								   initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
								   target:self action:nil]autorelease];
	
	// create about Docuworks button
	UIButton *aboutButton = [UIButton buttonWithType:UIButtonTypeInfoLight];
	[aboutButton addTarget:self 
					action:@selector(actionTouchAboutDocuworksButton)
		  forControlEvents:UIControlEventTouchUpInside];
	
	// create about Docuworks button item	
	UIBarButtonItem *aboutButtonItem = [[[UIBarButtonItem alloc] initWithCustomView:aboutButton] autorelease];
	aboutButtonItem.style = UIBarButtonItemStylePlain;
	
	[toolbarButtonItems addObject:flexSpace];
	[toolbarButtonItems addObject:aboutButtonItem];
	
	// 3.5アプリ情報機能の追加 の対応 end
	
	self.toolbarItems = toolbarButtonItems;
	[toolbarButtonItems release];
}

- (void) actionTouchEnvironmentSettingsButton
{
	environmentSettingsController.keepDocumentStatus = keepDocumentStatus;
	
	// FileSort の対応 start
	environmentSettingsController.fileSortItemIndex = fileSortItemIndex;
	environmentSettingsController.fileSortModeIndex = fileSortModeIndex;
	// FileSort の対応 end
    
    // 「拡大率指定の追加」の対応 start
    environmentSettingsController.specifyScaleModeIndex = specifyScaleModeIndex;
    environmentSettingsController.specifyScaleValue = specifyScaleValue;
    // 「拡大率指定の追加」の対応 end
	
	[self presentModalViewController:navigateController animated:YES];	
}

- (void) didSwitchButtonValueChanged:(EnvironmentSettingsViewController *)sender
{
	keepDocumentStatus = sender.keepDocumentStatus;
}


#pragma mark -
#pragma mark application about Toolbar button.
// 3.5アプリ情報機能の追加 の対応 start 
// change by lixin 20110607 DW_iPhoneEnhance_12
- (void) actionTouchAboutDocuworksButton
{
	aboutNavigateController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	
	[self presentModalViewController:aboutNavigateController animated:YES];
}
// 3.5アプリ情報機能の追加 の対応 end


#pragma mark -
#pragma mark Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    //max document number limit by sun.chl 20101129
	// FileSort の対応 start
    //max document number limit by sun.chl 20101129
	/*
	 if ([fileNames count] > MAX_DOCUMENT_NUM) {
	 //cell 501 display a message
	 return (MAX_DOCUMENT_NUM + 1);
	 } else {
	 return [fileNames count];
	 }
	 */
	
	if ([fileInfos count] > MAX_DOCUMENT_NUM) {
		return (MAX_DOCUMENT_NUM + 1);
	} else {
		return [fileInfos count];
	}
	// FileSort の対応 end
}

// FileSort の対応 start
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	if (Utility::UIDeviceIsiPad()) 
	{
		return _IPAD_FILE_LIST_ROW_HEIGHT_;
	}
	else 
	{
		return _IPHONE_FILE_LIST_ROW_HEIGHT_;
	}
}
// FileSort の対応 end

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
	UITableViewCell *cell = nil;
	static NSString *ID_Limit = @"CellLimit";
	static NSString *ID_Other = @"CellOther";
	if ([indexPath row] == MAX_DOCUMENT_NUM) {
		cell = [tableView dequeueReusableCellWithIdentifier:ID_Limit];
		if (nil == cell) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:ID_Limit] autorelease];
		}
	} else {
		cell = [tableView dequeueReusableCellWithIdentifier:ID_Other];
		if (nil == cell) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:ID_Other] autorelease];
		}
	}
	// max document number limit by sun.chl 20101129
	if ([indexPath row] == MAX_DOCUMENT_NUM) {
		cell.textLabel.text = NSLocalizedString(@"MSG_FILELIST_FILECOUNTERROR", nil);
		
		// FileSort の対応 start
		// set cell label font size to show all notice message add by lixin 20101129 
		if ( !Utility::UIDeviceIsiPad() ) {
			cell.textLabel.font = [UIFont systemFontOfSize: Utility::IPHONE_LIMIT_UI_FONT_SIZE];
		}				
		else {
			cell.textLabel.font = [UIFont systemFontOfSize: Utility::IPAD_LIMIT_UI_FONT_SIZE];				
		}
		cell.textLabel.numberOfLines = 2;
		// set font size end
		cell.accessoryType = UITableViewCellAccessoryNone;
		// FileSort の対応 end
		
		cell.imageView.image = nil;
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
		cell.selected = NO;
	} else {
		[self setTabelViewCellInfo:cell withCellIndex:[indexPath row]];	
	}
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
	//File Multiple Del by Yangjx 0603 start
	/*old
	//max document number limit by sun.chl 20101129
	if ([indexPath row] == MAX_DOCUMENT_NUM) {
		return NO;
	} else {
		return YES;
	}
	*/
	if ([indexPath row] == MAX_DOCUMENT_NUM) {
		return NO;
	} else if (isEditMode == YES) {
		UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
		DWFileInfo *fileInfo = [fileInfos objectAtIndex:indexPath.row];
		if (fileInfo.isCheck && cell.accessoryType == UITableViewCellAccessoryCheckmark) {
			return NO;
		}
	    return YES;
	} else {
		// liuqw 2011/06/18 start 
        
        // liuqw 20110623 start
        // AR NO.17852 の対応
		return YES;
        //return NO;
        // liuqw 20110623 end
        
		// liuqw 2011/06/18 end        
	}
	//File Multiple Del by Yangjx 0603 end
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle 
										    forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
		//max document number limit by sun.chl 20101129
		if ([indexPath row] == MAX_DOCUMENT_NUM) {
			// do nothing
		} else {
			// Delete the row from the data source.
			deleteIndexPath = [indexPath retain];
			
			// get delete file path with document directory and delete file name.
			deleteFilePath = [[self getDocumentFilePathWithIndex:[deleteIndexPath row]] retain];
			
			// show alert view to receive user operation.
			UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
															   message:NSLocalizedString(@"MSG_DELETEFILE", nil)
															  delegate:self
													 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
			alertView.tag = ALERT_DELONEFILE_TAG;
			[alertView show];
			[alertView release];
		}
    }
}

//File Multiple Del by Yangjx 0603 start
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (cell != nil) {
        int index = [indexPath row];
		// yangjx 20110622 start
		// AR 17862
        if (index < fileInfos.count && index != MAX_DOCUMENT_NUM) {
            DWFileInfo *dwFileInfo = [fileInfos objectAtIndex:index];
            [self setUITableViewCellAccessoryType:cell withCheckStatus:dwFileInfo.isCheck];
        }
		// yangjx 20110622 end
    }
}
//File Multiple Del by Yangjx 0603 end

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	//File Multiple Del by Yangjx 0603 start
	/*old
	 //max document number limit by sun.chl 20101129
	 if ([indexPath row] == MAX_DOCUMENT_NUM) {
	 // do nothing
	 } else {
	 [self didSelectRowInTableViewWithIndex:[indexPath row]];	
	 }
	 */
	// yangjx 20110622 start
	// AR 17862
	if ([indexPath row] == MAX_DOCUMENT_NUM) {
		// do nothing
	}else {
		if (isEditMode == YES) {
			UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
			DWFileInfo *dwFileInfo = [fileInfos objectAtIndex:indexPath.row];
			if (dwFileInfo.isCheck == NO) {
				[selectFileInfos addObject:dwFileInfo];
				dwFileInfo.isCheck = YES;
				[self setUITableViewCellAccessoryType:cell withCheckStatus:YES];
			} else if (dwFileInfo.isCheck == YES){
				[selectFileInfos removeObject:dwFileInfo];
				dwFileInfo.isCheck = NO;
				[self setUITableViewCellAccessoryType:cell withCheckStatus:NO];
			}
			
			[self setToolbarItemsStatus];
		} else {
			[self didSelectRowInTableViewWithIndex:[indexPath row]];	
		}
		
	}
    // yangjx 20110622 end
	//File Multiple Del by Yangjx 0603 end
}

//「文書情報ボタン」の動作 start
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath: (NSIndexPath *) indexPath{
	if ([fileInfos count] > indexPath.row) {
		DWFileInfo *fileInfo = (DWFileInfo *)[fileInfos objectAtIndex:indexPath.row];
		if ([[fileInfo.fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame || 
			[[fileInfo.fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame) {
			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			NSString *directoryPath = [paths objectAtIndex:0];
			NSString *filePath = [directoryPath stringByAppendingPathComponent:fileInfo.fileName];

            fileInfo.fileTitle = @"";
            fileInfo.fileSubtitle = @"";
            fileInfo.fileAuthor = @"";
            fileInfo.fileKeyword = @"";
            fileInfo.fileRemark = @"";
            
            BOOL res = [documentSummaryMgr getDocumentSummaryDataWithFilePath:filePath];

            if (res == YES) {
                if (documentSummaryMgr.fileTitle != nil) {
                    fileInfo.fileTitle = documentSummaryMgr.fileTitle;
                }
                
                if (documentSummaryMgr.fileSubtitle != nil) {
                    fileInfo.fileSubtitle = documentSummaryMgr.fileSubtitle;
                }
                
                if (documentSummaryMgr.fileAuthor != nil) {
                    fileInfo.fileAuthor = documentSummaryMgr.fileAuthor;    
                }
                
                if (documentSummaryMgr.fileKeyword != nil) {
                    fileInfo.fileKeyword = documentSummaryMgr.fileKeyword;
                }
                
                if (documentSummaryMgr.fileComment != nil) {
                    fileInfo.fileRemark = documentSummaryMgr.fileComment;    
                }
            }
			
			// zhaijie 2012.03.30 start
			// 『セキュリティ』の情報の対応
			fileInfo.filePermission = [documentSummaryMgr getFilePermission:filePath];
			// zhaijie 2012.03.30 end
		}
		// 20110622 tongtx start
		// AR17861 の対応
		self.navigationController.toolbar.hidden = YES;
		// 20110622 tongtx end

		FileDetailViewController *fileDetail = [[FileDetailViewController alloc] initWithStyle:UITableViewStyleGrouped 
																				   andFileInfo:[fileInfos objectAtIndex:indexPath.row]];
		
		[self.navigationController pushViewController:fileDetail animated:YES];
		[fileDetail release];
		
		// tongtx 20110920 start
		// NS-AR029 の対応
		isUpdateFileNameFromDetailView = YES;
		// tongtx 20110920 end
	}
}

// 20110705 M.Chikyu (AR17895,AR17900) start
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView
		   editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
	// 編集モードではスワイプによるファイルの削除を禁止する
	return isEditMode ? UITableViewCellEditingStyleNone : UITableViewCellEditingStyleDelete;
}
// 20110705 M.Chikyu (AR17895,AR17900) end


#pragma mark -
#pragma mark alertView delegate
// Called when a button is clicked. The view will be automatically dismissed after this call returns
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	//File Multiple Del by Yangjx 0603 start
	switch (alertView.tag) {
		case 0:
			if (buttonIndex == 0) {
				
				if ([self deleteDocumentWithFilePath:deleteFilePath] == YES) {
					
					NSString* fileName = [self getDocumentFileNameWithIndex:[deleteIndexPath row]];
					if (fileName != nil) {
						// get plist name with file name.
						NSMutableString* plistFileName = [[NSMutableString alloc]initWithString:fileName];
						[plistFileName appendString:@".plist"];
						[documentSettingsMgr deleteSettingsFileWithFileName:plistFileName];
						// Memory Leak の対応 start
						[plistFileName release];
						// Memory Leak の対応 end
					}
					
					// delete file name from table view.
					//delete for max document number limit by sun.chl 20101129
					/*
					 [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:deleteIndexPath] 
					 withRowAnimation:UITableViewRowAnimationFade];
					 */
					
					// delete file name from file name list.
					NSUInteger index = [deleteIndexPath row];
					
					// FileSort の対応 start
					//[fileNames removeObjectAtIndex:index];
					[fileInfos removeObjectAtIndex:index];
					// FileSort の対応 end
					
					//max document number limit by sun.chl 20101129
					[self.tableView reloadData];
				}
			}
			
			// release deleteIndexPath.
			if (deleteIndexPath != nil) {
				[deleteIndexPath release];
				deleteIndexPath = nil;
			}
			
			// release deleteFilePath.
			if (deleteFilePath != nil) {
				[deleteFilePath release];
				deleteFilePath = nil;
			}
			
			break;
		case 1:
			if (buttonIndex == 0) {
				[self sendEmailInDirectoryView];
			}
			break;
		case 2:
			if (buttonIndex == 0) {
				[documentSettingsMgr deleteAllFilesFromTrashDirectory];
                
                NSString *trashDir = [[documentSettingsMgr createTrashDirectory] retain];
				for (int i = 0; i < [selectFileInfos count]; i++) {
					NSString *srcFilePath = nil;
					DWFileInfo *dwFileInfo = [selectFileInfos objectAtIndex:i];
					srcFilePath = [[documentSettingsMgr getDocumentFilePathWithFileName:dwFileInfo.fileName] retain];
					[documentSettingsMgr moveDocumentFromSrcPath:srcFilePath toDestPath:trashDir];
					[srcFilePath release];
				}
				[trashDir release];
				
				//delete from fileInfos
				[fileInfos removeObjectsInArray:selectFileInfos];
				if (selectFileInfos != nil) {
					[selectFileInfos removeAllObjects];
					self.selectFileInfos = nil;
				}
				// Memory Leak の対応 by yangjx 0627 start
				selectFileInfos = [[NSMutableArray alloc] init];
				// Memory Leak の対応 by yangjx 0627 start
				[self setToolbarItemsStatus];
				[self.tableView reloadData];
			}
			break;
		case 3:
			if (buttonIndex == 0) {
				[documentSettingsMgr moveFileFromTrashToDocument];
				[self loadAllFileNamesInDocumentDirectory];
				
				// modify by yangjx 0629 start
				if (selectFileInfos != nil) {
					[selectFileInfos removeAllObjects];
					self.selectFileInfos = nil;
				}
				selectFileInfos = [[NSMutableArray alloc] init];
				// modify by yangjx 0629 end
				
				[self.tableView reloadData];
				[self setToolbarItemsStatus];
			}
			break;
            
            // liuqw 20110628 start
            // AR NO.17871 の対応
        case TAG_SETTINGS_NAME_ERROR:    
            if (buttonIndex == 0) {
                NSString *filePath = [[self getDocumentFilePathWithIndex:selectCellIndex] retain];
                NSString* fileName = [[self getDocumentFileNameWithIndex:selectCellIndex] retain];
                
				// xuxinjun 2012.03.23 start
				// 保護文書の対応
				/*
				 // create document view controller.
				 DocumentViewController* controller = [self createViewControllerWithFileName:fileName 
				 withFilePath:filePath]; 
				 controller.isCanSaveSettings = NO;
				 if (controller != nil) {
				 activeViewController = controller;
				 [self.navigationController pushViewController:activeViewController animated:YES];
				 }
				 */ 
				
				enum CHECK_PROTECTED_TYPE type = kCheckSettingsNameError;
				DW_PROTECTED_TYPE result = [self checkProtectedTypeWithActionType:type
																	  andFilePath:filePath 
																	  andFileName:fileName
																	  andOtherInf:nil];
				if (result != kProtectTypePwd)
				{
					if (result == kProtectTypeNoPwd)
					{
						[self pushControllerWithActionType:type 
											   andFilePath:filePath 
											   andFileName:fileName 
											   andPassword:@""
											   andOtherInf:nil];
					}
					else
					{
						[self pushControllerWithActionType:type 
											   andFilePath:filePath 
											   andFileName:fileName 
											   andPassword:nil
											   andOtherInf:nil];
					}
				}
				// xuxinjun 2012.03.23 end
				
                [filePath release];
                [fileName release];
            }   
            break;
            // liuqw 20110628 end
            
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
		case TAG_ALERT_INPUT_PWD:
			if (buttonIndex == 0)
			{
				[alertView dismissWithClickedButtonIndex:buttonIndex animated:NO];
				UITextField *fieldInputPassword_ = (UITextField *)[alertView viewWithTag:TAG_FIELD_INPUT_PWD];
				if (fieldInputPassword_ != nil)
				{
					NSString* password_ = fieldInputPassword_.text;
					BOOL canOpen =  [self.authenticationManager canOpenProtectedDocument:self.authFullPath 
																			withPassword:password_];
					if (canOpen == YES)
					{
						[self pushControllerWithActionType:actionType_ 
											   andFilePath:self.authFullPath 
											   andFileName:self.authFileName
											   andPassword:password_
											   andOtherInf:otherInfo_];
					}
					else
					{						
						UIAlertView* alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil)   
																		   message:NSLocalizedString(@"MSG_AUTH_ALERT_PASSWORD_ERROR_MESSAGE", nil)
																		  delegate:self
																 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
																 otherButtonTitles:nil,	(char *)nil];
						[alertView show];
						[alertView release];
					}
				}
			} 
			else	
			{
				[alertView dismissWithClickedButtonIndex:buttonIndex animated:NO];
			}
			
			break;
			// xuxinjun 2012.03.23 end
			
		default:
			break;
	}
	//File Multiple Del by Yangjx 0603 end
}

// xuxinjun 2012.04.12 start
// 保護文書の対応
#pragma mark -
#pragma mark UITextField delegate method.
- (BOOL)textFieldShouldReturn:(UITextField *)theTextField
{
    if (theTextField.tag == TAG_ALERT_INPUT_PWD)
	{
        [theTextField resignFirstResponder];
        UIAlertView* superView = (UIAlertView*)[theTextField superview];
		
		if (superView != nil)
		{
            [self alertView:superView clickedButtonAtIndex:0];
            [superView dismissWithClickedButtonIndex:0 animated:YES];
        }
    }
	else
	{
        [fieldTextInputPassword_ resignFirstResponder];
        [self alertView:alertViewInputPassword_ clickedButtonAtIndex:0];
        [alertViewInputPassword_ dismissWithClickedButtonIndex:0 animated:YES];
    }
	return YES;
}
// xuxinjun 2012.04.12 end


#pragma mark -
#pragma mark common method.
- (NSString*) getDocumentFileNameWithIndex:(int)index
{
	// FileSort の対応 start
	//[fileNames objectAtIndex:index];
	NSString* fileName = ((DWFileInfo*)[fileInfos objectAtIndex:index]).fileName;
	// FileSort の対応 end
	return fileName;
}

- (NSString*) getDocumentFilePathWithIndex:(int)index
{
	NSString* documentFilePath = nil;
	
	// get document directory.
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentDirectory = [[paths objectAtIndex:0] retain];
	
	// get file name from file name list.
	// FileSort の対応 start
	//NSString* fileName = [[fileNames objectAtIndex:index] retain];
	NSString* fileName = [((DWFileInfo*)[fileInfos objectAtIndex:index]).fileName retain];
	// FileSort の対応 end
	
	// get file path with document directory and delete file name.
	documentFilePath = [documentDirectory stringByAppendingPathComponent:fileName];
	
	// release
	[documentDirectory release];
	[fileName release];
	
	return documentFilePath;
}

- (NSString*) getEnvironmentSettingsIcon
{
	/*
	if  ( Utility::UIDeviceScreenIsHighScale() )
	{
		return _HIGHSCALE_ENVIRONMENTSETTING_BUTTON_ICON_;
	}
	else
	{
		return _LOWSCALE_ENVIRONMENTSETTING_BUTTON_ICON_;
	}
	 */

	return _LOWSCALE_ENVIRONMENTSETTING_BUTTON_ICON_;
}

// modify by yangjx 20110624 start
- (NSString*) getSendEmailButtonIcon
{
	/*
	if  ( Utility::UIDeviceScreenIsHighScale() )
	{
		return _HIGHSCALE_SENDEMAIL_BUTTON_ICON_;
	}
	else
	{
		return _LOWSCALE_SENDEMAIL_BUTTON_ICON_;
	}
	 */

	return _LOWSCALE_SENDEMAIL_BUTTON_ICON_;
}
// modify by yangjx 20110624 end

- (NSString*) getXdwDocumentIcon
{
	return _XDWDOCUMENT_ICON_;
}

- (NSString*) getXbdDocumentIcon
{
	return _XBDDOCUMENT_ICON_;	
}

- (NSString*) getPDFDocumentIcon
{
	return _PDFDOCUMENT_ICON_;
}

// xuxinjun 2012.03.27 start
// 保護文書の対応
- (NSString*) getXdwProtectedDocumentIcon
{
	return _XDWDOCUMENT_PROTECTED_ICON_;
}

- (NSString*) getXbdProtectedDocumentIcon
{
	return _XBDDOCUMENT_PROTECTED_ICON_;
}
// xuxinjun 2012.03.27 end

// lixin 2011/09/15 start 
// NS-AR012 の対応
- (NSString*) getDeleteButtonIcon
{
	/*
	if ( Utility::UIDeviceScreenIsHighScale() )
	{
		return _ICON_DELETE_HEIGHTSCALE_;
	}
	else
	{
		return _ICON_DELETE_LOWSCALE_;
	}
	 */

	return _ICON_DELETE_LOWSCALE_;
}
// lixin 2011/09/15 end

- (UIButton*) getToolbarButton:(NSString*)iconName
{
	UIImage *image = [UIImage imageNamed:iconName];
	UIButton *button = [UIButton buttonWithType:UIButtonTypeInfoLight];
	[button setImage:image forState:UIControlStateNormal];
	button.frame = CGRectMake(0, 0, 25, 25);
	//modify by yangjx start 0616
	//[image release];
	//modify by yangjx end 0616
	return button;
}
@end