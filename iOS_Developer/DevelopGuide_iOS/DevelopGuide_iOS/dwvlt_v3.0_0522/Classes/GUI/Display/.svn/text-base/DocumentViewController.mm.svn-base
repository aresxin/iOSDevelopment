//
//  DocumentViewController.mbgScrollView
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DocumentViewController.h"
#import "AnnotationListViewController.h"
#import "EnvironmentSettingsViewController.h"  
#import "DWScrollView.h"
#import "DWPageView.h"
#import "XdwLinkManager.h"
#import "LinkAnnotInfo.h"
#import "LinkAnnotationManager.h"
#import "DWViewerGUIConst.h"
#import "Utility.h"
#import "GraphicDrawer.h"
#import "DocumentSettingsManager.h"
#import "XdwFileInfo.h"
#import "Utility.h"
#import "PageInfo.h"
#import "DWAssociationManager.h"
// liuqw 20110801 start
// ページ編集機能の追加
#import "DocumentEditController.h"
// liuqw 20110801 end

#define PAGE_NUMBER_TEXT_TAG 100
#define BACK_GROUND_SCROLLVIEW_TAG 200000
#define DOUBLE_TAP_DELAY 0.35
// lixin 2011/09/20 start 
// NS-AR031 の対応
/*
//#define HIDE_TOOLBAR_DELAY 3.0
#define HIDE_TOOLBAR_DELAY 10.0		// 20110107 M.Chikyu (AR17622)
*/
// 2012.02.01(Ver2.1 New) M.Chikyu
#define HIDE_TOOLBAR_DELAY 1.5
// 2012.02.01(Ver2.1 New) M.Chikyu

// lixin 2011/09/20 end
#define MOVE_PAGE_MINVELOCITY -2000
#define MOVE_PAGE_MAXVELOCITY 2000
// SendEmail の対応 start
#define COOPERATION_MENU_TAG 500
// SendEmail の対応 end

#define LINK_SHADOW_VIEW_TAG 404

// 「拡大率指定ボタンの追加」の対応 start
#define TAG_INPUT_SCALE_ALERT 101
#define TAG_INPUT_SCALE_FIELD 102
#define TAG_INPUT_SCALE_ERROR 103
// 「拡大率指定ボタンの追加」の対応 end

// liuqw 20110801 start
// ページ編集機能の追加
#define TAG_SAVE_UPDATE_ALERT               105
#define TAG_ACTIONSHEET_CHOOSEEDITPAGE      106
// liuqw 20110801 end

// tongtx 2011/08/15 start
// Briefcaseと連携機能の追加
#define TAG_LINK_BRIEFCASE_ALERT 200
#define TAG_BRIEFCASE_EXIST_ALERT 300
// tongtx 2011/08/15 end

// liuqw 2012/03/06 start
// AR NO.19019の対応
#define TAG_LINK_MTA_ALERT 201
// liuqw 2012/03/06 end

// tongtx 20120206 start
// 有償化アナウンス機能の対応
#define TAG_PAYMENT_NOTICE_ALERT 301
// tongtx 20120206 end

// xujj 2012.03.22 start
// 検索機能の追加
#define TAG_SEARCH_GHOST_VIEW 302
#define TAG_SEARCH_FIRST_PAGE_ALERT 305
#define TAG_SEARCH_LAST_PAGE_ALERT 306
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
#define TAG_SELECT_PAGE_VIEW 400
#define TAG_SELECT_ANNOTATION_VIEW 401
// tongtx 2012.03.23 end

@implementation DocumentViewController
@synthesize pageViewMgr;
@synthesize fileName;
@synthesize filePath;
@synthesize pageViewPos;
@synthesize preViewPos;
@synthesize keepDocumentStatus;

// FileSort の対応 start
@synthesize fileSortItemIndex;
@synthesize fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@synthesize fieldInputScale;
@synthesize alertInputScale;
@synthesize labelScalePercent;
// 「拡大率指定の追加」の対応 end

// liuqw 20110628 start
// AR NO.17871 の対応
@synthesize isCanSaveSettings;
// liuqw 20110628

// tongtx 2011/10/21 start
// NS-AR2008 の対応
@synthesize fromBriefCase;
// tongtx 2011/10/21 end

@synthesize delegate;//AR No.17581 by sun.chl 2010.12.17

// liuqw 20110801 start
// ページ編集機能の追加
@synthesize backButtonTitle = backButtonTitle_;
// liuqw 20110801 end

// tongtx 20110916 start
// NS-AR024 の対応
@synthesize displayActionSheet;
// tongtx 20110916 end

// tongtx 20120206 start
// MTA連動機能の対応
@synthesize isFromMTA           = fromMTA;
@synthesize appnameFromMTA      = appnameFromMTA_;
@synthesize folderNameFromMTA   = folderNameFromMTA_;
@synthesize pasteboardFromMTA   = pasteboardFromMTA_;
// tongtx 20120206 end


#pragma mark -
#pragma mark init

// xuxinjun 2012.03.23 start
// 保護文書の対応
//- (id)initWithPath:(NSString *)path
- (id)initWithPath:(NSString *)path andOpenPassword:(NSString*)pwd
// xuxinjun 2012.03.23 end

{
	self = [super init];
	if (self == nil)
	{
		return nil;
	}

	filePath = [path retain];
	
	hideToolbar = NO;
	showAnnotationList = NO;
	showFacingSettings = NO;
	showFontSettings = NO;
	
	// ページ編集機能の追加  
	srcEditFilePath = [[NSString stringWithFormat:@"%@", path]retain];
	showChooseEditPageIndexView = NO;
	
	
	// SendEmail の対応 start
	showCooperationSettings = NO;
	
	
	isRotate = NO;
	needkeepDocumentStatus = YES;//AR No.17581 by sun.chl 2010.12.17
	
	isResetSubviewing = NO;
	
	// liuqw 20110627 start
	// AR NO.17873 の対応
	annoListEnabled = YES;
	binderListEnabled = YES;
	// liuqw 20110627 end
	
	// liuqw 20110628 start
	// AR NO.17871 の対応
	isCanSaveSettings = YES;
	// liuqw 20110628
	
	alertInputScale = nil;
	
	isPortraitBeforePortrait = [self UIDeviceIsPortrait];//Ar No.74

	
	// PageViewManagerの初期化
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	/*
	 pageViewMgr = [[PageViewManager alloc]initWithDocumentViewController:self 
	 withDocumentPath:path];
	 */
	pageViewMgr = [[PageViewManager alloc]initWithDocumentViewController:self 
														withDocumentPath:path 
														withOpenPassword:pwd];
	// xuxinjun 2012.03.23 end
	
	if (pageViewMgr == nil)
	{
		[self autorelease];
		return nil;
	}

	pageViewMgr.interfaceOrientation = self.interfaceOrientation;

	
	docInteractionController = nil;
	
	
	// init document setting manager.
	documentSettingsMgr = [[DocumentSettingsManager alloc]init]; 
	
	
	// FileSort の対応 start
	[documentSettingsMgr readDocumentSettings];
	keepDocumentStatus = documentSettingsMgr.keepStatus;
	
	fileSortItemIndex = documentSettingsMgr.fileSortItemIndex;
	fileSortModeIndex = documentSettingsMgr.fileSortModeIndex;
	
	
	// 「拡大率指定の追加」の対応 start
	specifyScaleModeIndex = documentSettingsMgr.specifyScaleModeIndex;
	specifyScaleValue = documentSettingsMgr.specifyScale;
	
	
	// init navigation controller
	navigateController = nil;
	
	
	// Briefcaseと連携機能の追加
	fromBriefCase = NO;
    
    // tongtx 20120206 start
    // MTA連動機能の対応
    fromMTA = NO;
    // tongtx 20120206 end

	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	//add by yan.get the status bar height
	if ([self UIDeviceIsPortrait])
	{
		CGRect statusRect = [UIApplication sharedApplication].statusBarFrame;
		statusRectHeight = statusRect.size.height;
	}
	else
	{
		statusRectHeight = 20;
	}
	 */
	statusRectHeight = 0;
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// tongtx 2012.03.23 start
	// 選択機能の追加
	selectInfo_ = [[DWSelectInfo alloc] init];
	isSelectGhostShowing = NO;
	// tongtx 2012.03.23 end 
	
	// xujj 2012.04.06 start
	// 検索機能の追加
	searchInfo_ = [[DWSearchInfo alloc] init];
	// xujj 2012.04.06 end
	
	return self;
}


#pragma mark -
#pragma mark View lifecycle
- (void) viewDidLoad
{
	[super viewDidLoad];
	
	self.wantsFullScreenLayout = YES;
	
	// add gesture recognizers to the image view
	singleTapGestureRecognizer = [[UITapGestureRecognizer alloc] 
								  initWithTarget:self action:@selector(actionSingleTap:)];

	doubleTapGestureRecognizer = [[UITapGestureRecognizer alloc] 
								  initWithTarget:self action:@selector(actionDoubleTap:)];
	
	// add by tongjo
	// detect both sing-tap and double-tap
	[singleTapGestureRecognizer requireGestureRecognizerToFail:doubleTapGestureRecognizer];

	[doubleTapGestureRecognizer setDelaysTouchesBegan:YES];
	[singleTapGestureRecognizer setDelaysTouchesBegan:YES];
	
	[singleTapGestureRecognizer setNumberOfTapsRequired:1];
	[doubleTapGestureRecognizer setNumberOfTapsRequired:2];
	

    twoFingerTapGestureRecognizer = [[UITapGestureRecognizer alloc] 
									 initWithTarget:self action:@selector(actionTwoFingerTap:)];
	
	[twoFingerTapGestureRecognizer setNumberOfTouchesRequired:2];
	
	panGestureRecognizer = [[UIPanGestureRecognizer alloc]initWithTarget:self 
																  action:@selector(actionDragPageView:)];
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	
	longPressTapGestureRecognizer = [[UILongPressGestureRecognizer alloc]
									 initWithTarget:self 
									 action:@selector(actionOnLongPressPageView:)];
	[longPressTapGestureRecognizer requireGestureRecognizerToFail:singleTapGestureRecognizer];
	 
	// tongtx 2012.03.23 end
	
	// init
	[self initToolbarStyle];
	[self initViewControls]; 
	[self initViewControlsRect];
	[self initPageNumberlabelRect];
	[self initMainFrame];
	
	[self initPropertyValueWithKeepStatus:keepDocumentStatus];
    
    // tongtx 20120206 start
    // MTA連動機能の対応
    if (fromMTA == YES) 
    {
        pageViewPos = pageViewMgr.pageIndex;
    }
    // tongtx 20120206 end

	if (pageViewMgr.pageStatus == PAGE_STATUS_FIT)
	{
		[self actionMovePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	else
	{
		[self actionMoveOnePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	
	// AR17558 の対応 start
	[self deleteInboxFile];
	// AR17558 の対応 end
	
	// add tool tip start
    [self addToolTipToSliderBar];
	// add tool tip end
	
	// tongtx 20110926 start
	// NS-AR038 の対応
	isBriefCaseUTIVisible = NO;
	// tongtx 20110926 end
    
    // tongtx 20120206 start
    // MTA連動機能の対応
    isMTAUTIVisible = NO;
    // tongtx 20120206 end
}

- (void)viewWillAppear:(BOOL)animated
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	 // liuqw 20110801 start
	 // ページ編集機能の追加
	 [self initToolbarStyle];
	 [[UIApplication sharedApplication] setStatusBarHidden:NO 
	 withAnimation:UIStatusBarAnimationNone];
	 self.navigationController.navigationBar.hidden = NO;
	 CGRect navigatebarRect = self.navigationController.navigationBar.frame;
	 float originX = 0.0;
	 float originY = 20.0;
	 navigatebarRect = CGRectMake(originX, 
	 originY, 
	 navigatebarRect.size.width,
	 navigatebarRect.size.height);
	 self.navigationController.navigationBar.frame = navigatebarRect;
	 self.navigationController.toolbar.hidden = NO;
	 
	 [self performSelector:@selector(hideAllToolbarItems:) 
	 withObject:[NSNumber numberWithBool:NO] 
	 afterDelay:0];
	 // liuqw 20110801 end
	 */
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
	[self.navigationController setNavigationBarHidden:YES];
	[self.navigationController setNavigationBarHidden:NO];
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// xujj 2012.04.19 start
	[self.navigationController setToolbarHidden:NO];
	// xujj 2012.04.19 end
	
	isPortraitBeforePortrait = [self UIDeviceIsPortrait];//Ar No.74
	
	[super viewWillAppear:animated];
	
	DWScrollView *pageView = [self getActivePageView];
	if (nil != pageView )
	{
		[pageView.page setNeedsLayout];
	}
}

//AR No.17581
- (void)viewWillDisappear:(BOOL)animated
{
	[pageAlertTextField resignFirstResponder];
	
    // tongtx 2011/08/16 start
	// Briefcaseと連携機能の追加
	
    // tongtx 20120206 start
    // MTA連動機能の対応
    //if (fromBriefCase == NO)
    if (fromBriefCase == NO && fromMTA == NO) 
		// tongtx 20120206 end
	{
        if ([pageViewMgr isTempFileEditing] == YES)
		{
			return;
		}
        
		if (needkeepDocumentStatus == YES)
		{
			[delegate saveDocumentStatusWithController:self];
		}
		else
		{
			needkeepDocumentStatus = YES;
		}
	}
	
	[self cancelShowScreen];
	[self removeToolbarPopView];
    
	// tongtx 2011/08/16 end
}

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void)viewDidAppear:(BOOL)animated
{
	DWScrollView *pageView = [self getActivePageView];
	if (nil == pageView )
	{
		return;
	}
	
	// 次ページを取得
	DWScrollView* nextPage = [self getPageViewWithPosition:(pageViewPos + 1)];
	
	// 次ページが存在しなければ追加
	if (nextPage == nil)
	{
		// 最終ページなら何もしない
		if (pageViewPos + 1 <= [pageViewMgr getPageViewCount] - 1)
		{
			[self insertPageViewWithPosition:(pageViewPos + 1)];
			nextPage = [self getPageViewWithPosition:(pageViewPos + 1)];
			
			// 次ページのオフセットを指定
			[nextPage setContentOffset:nextPage.initContentOffset];
		}
	}
	else
	{
		[self shiftNextPage];
	}
	
	
	// 前ページを取得
	DWScrollView* prePage = [self getPageViewWithPosition:(pageViewPos - 1)];
	
	// 前ページが存在しなければ追加
	if (prePage == nil)
	{
		// 先頭ページなら何もしない
		if (pageViewPos - 1 >= 0)
		{
			[self insertPageViewWithPosition:(pageViewPos - 1)];
			prePage = [self getPageViewWithPosition:(pageViewPos - 1)];
			
			// 前ページのオフセットを指定
			[prePage setContentOffset:prePage.initContentOffset];
		}
	}
	else
	{
		[self shiftPrePage];
	}
}
// 2012.02.01(Ver2.1 New) M.Chikyu


#pragma mark -
#pragma mark dealloc
- (void)dealloc
{
	[filePath release];
	//delete []linkAnnotInfo;
	
	[singleTapGestureRecognizer release];
    [doubleTapGestureRecognizer release];
    [twoFingerTapGestureRecognizer release];
    
    // 「リンクアノテーションジャンプ方法」変更の対応 start
	//[longPressTapGestureRecognizer release];
    // 「リンクアノテーションジャンプ方法」変更の対応 end
    
	// Memory Leak の対応 start
	[panGestureRecognizer release];
	// Memory Leak の対応 end
	
	[self removePageViewsFromScrollView];
	[bgScrollView removeFromSuperview];
	[bgScrollView release];
	[pageViewMgr release];
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	if (activeIndicator_ != nil)
	{
		[activeIndicator_ removeFromSuperview];
		[activeIndicator_ release];
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	// page nuber label;
	[pageNumberLabel release];
	
	// slider label.
	[sliderLabel release];
	
	// annotation list view.
	[annotationListView release];
	[annotationListBackgroundView release];
	[annotationListTitle release];
	[annotationListViewController release];
	[separatorView release];
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	[xdwDocListView release];
	[xdwDocListBackgroundView release];
	[xdwDocListTitle release];
	[xdwDocListViewController release];
	[xdwDocSeparatorView release];
	// 3.6 バインダ文書対応 の対応 end
	
	//Toolbar 
    
    // 「環境設定ボタンの削除」の対応 start
	//[environmentSettings release];
    // 「環境設定ボタンの削除」の対応 end
    
	[navigateController release];
	[facingSettings release];
	[fontSettings release];
	// SendEmail の対応 start
	[cooperationSettings release];
	// SendEmail の対応 end
	
    [zoomSettingButtonItem release];
    
	[fontButtonItem release];
	[facingButtonItem release];
	[cooperationButtonItem release];
	[annoButtonItem release];
	
	// tool bar items.
	[buttonCommentsList release];
	[horizontalToolbarItems release];
	[verticalToolbarItems release];
	
	if ( Utility::UIDeviceIsiPad() )
	{
		[fontPopMenu release];
		[facingPopMenu release];
		// SendEmail の対応 start
		[cooperationPopMenu release];
		// SendEmail の対応 end
    }
	
	//  page jump alert
	[pageAlertTextField release];
	[pageAlert release];
	[linkAlert release];
	
	if (docInteractionController != nil)
	{
		[docInteractionController release];
	}
	
	[pageNumBackView release];
    
	// add tool tip start
    [bgToolTip release];
    [labelToolTip release];
	// add tool tip end
    
	if (documentSettingsMgr != nil)
	{
		[documentSettingsMgr release];
		documentSettingsMgr = nil;
	}
    
    // 「拡大率指定の追加」の対応 start
    [alertInputScale release];
    [fieldInputScale release];
    [labelScalePercent release];
    // 「拡大率指定の追加」の対応 end
    
    // liuqw 20110801 start
    // ページ編集機能の追加
    [backButtonTitle_ release];
    [srcEditFilePath release];
    [tmpEditFilePath release];
    [editFacingPageViewPopController release];
    [editFacingPageViewController release];
    // liuqw 20110801 end
	
	// tongtx 20110916 start
	// NS-AR024 の対応
	[displayActionSheet release];
	// tongtx 20110916 end
	
	
    // tongtx 20120206 start
    // MTA連動機能の対応
    [appnameFromMTA_ release];
    [folderNameFromMTA_ release];
    [pasteboardFromMTA_ release];
    // tongtx 20120206 end
    
	// xujj 2012.03.22 start
	// 検索機能の追加
	[searchBar_ release];
	[searchToolbarItems_ release];
	
	[searchInfo_  release];
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	[longPressTapGestureRecognizer release];
	[selectInfo_ release];
	// tongtx 2012.03.23 end
	
	[super dealloc];
}


#pragma mark -
#pragma mark init property value.
- (void) initPropertyValueWithKeepStatus:(BOOL)status
{
	// 1.set facing mode 
	FacingMode mode = pageViewMgr.facingMode;

	if ([self UIDeviceIsPortrait] == YES)
	{
		mode = MODE_REGULAR;
	}
	
	[self updateScrollViewContentSize];
	
	if (status == YES)
	{
		pageViewPos = 0;
		
		// 2.set page view pos.
		int pageCount = [pageViewMgr getPageViewCount];
		
		if (pageViewMgr.fontOrient == YES)
		{
			pageViewPos = pageViewMgr.pageIndex;
		}
		else
		{
			pageViewPos = pageCount - 1 - pageViewMgr.pageIndex;
		}
		
		preViewPos = pageViewPos;
		
		// 3.set page offset.
		pageOffset = pageViewMgr.pageOffset;
		
		// 4.update annotation on /off status
		[pageViewMgr setAnnotationDisplay:pageViewMgr.showAnnotation];
	}
}

// liuqw 20110627 start
// AR NO.17873 の対応
- (void) initRightBarButtonItemEnabledProperty
{
    self.navigationItem.rightBarButtonItem.enabled = YES;
    
    if (pageViewMgr.showAnnotation == YES && 
        [self getAnnotationCountInDocument] > 0)
	{
        annoListEnabled = YES;
    }
	else
	{
        annoListEnabled = NO;
    }
    
    if (pageViewMgr.isBinderDoc == YES)
	{
        XdwFileInfo* xdwFileInfo = (XdwFileInfo*)pageViewMgr.handleDocument->GetFileInfo();

        if (xdwFileInfo->GetBinderCount() > 0)
		{
            binderListEnabled = YES;
        }
		else
		{
            binderListEnabled = NO;
        }
    }
}

- (int) getAnnotationCountInDocument
{
    int count = 0;
    
    LinkAnnotInfoList *linkAnnotInfolist = [pageViewMgr getLinkAnnotationInfoList];

	if (linkAnnotInfolist != NULL)
	{
		for (int i = 0; i < linkAnnotInfolist->Size(); i++)
		{
			LinkAnnotInfo *linkAnnotInfo = linkAnnotInfolist->GetLinkAnnotInfo(i);

			if (linkAnnotInfo != nil &&
				linkAnnotInfo->IsLinkAnnotation() == NO)
			{
				count++;
			}
        }
	}
    
    return count;
}

- (void) setRightBarButtonItenEnabledWithIsBinderDoc:(BOOL)isBinder
{
    if (pageViewMgr.showAnnotation == YES && 
        [self getAnnotationCountInDocument] > 0)
	{
        annoListEnabled = YES;
    }
	else
	{
        annoListEnabled = NO;
    }
    
	// xujj 2012.04.08 start
	// 検索機能の追加
	/*
    if (isBinder == NO)
	{
        self.navigationItem.rightBarButtonItem.enabled = annoListEnabled;
    }
	else
	{
        UISegmentedControl* control = 
        (UISegmentedControl*)self.navigationItem.rightBarButtonItem.customView;

        if (control != nil)
		{
			[control setEnabled:annoListEnabled forSegmentAtIndex:0];
		}
	}*/
	
	UISegmentedControl* control = 
	(UISegmentedControl*)self.navigationItem.rightBarButtonItem.customView;
	
	if (control != nil)
	{
		[control setEnabled:annoListEnabled forSegmentAtIndex:0];
	} 
	// xujj 2012.04.08 end
}
// liuqw 20110627 end


#pragma mark -
#pragma mark init main frame
- (void) initToolbarStyle
{
	// init tool bar's style.
	if (!Utility::UIDeviceIsiPad()) // 201204 tongjo
	{
		[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleBlackTranslucent animated:NO];
	}

	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;	
	self.navigationController.toolbar.barStyle = UIBarStyleBlackTranslucent;
}

- (void) initMainFrame
{
	[self.view addSubview:bgScrollView];
	
	// add page number label to main frame.
	[self.view addSubview:pageNumBackView];
	[pageNumBackView addSubview:pageNumberLabel];
	
	// add slider label to main frame.
	if ([pageViewMgr getPageViewCount] > 1)
	{
		[self updateSliderLabel:pageViewPos];
		[self.view addSubview:sliderLabel];
	}
	
	// add annotation list view to main frame.
	[annotationListView addSubview:annotationListBackgroundView];
	[annotationListView addSubview:annotationListTitle];
	[annotationListView addSubview:separatorView];
	[annotationListView addSubview:annotationListViewController.view];
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	[xdwDocListView addSubview:xdwDocListBackgroundView];
	[xdwDocListView addSubview:xdwDocListTitle];
	[xdwDocListView addSubview:xdwDocSeparatorView];
	[xdwDocListView addSubview:xdwDocListViewController.view];
	// 3.6 バインダ文書対応 の対応 end
}

- (void) initViewControls
{
    // liuqw 20110801 start
    // ページ編集機能の追加
    [self initLeftBarItem];
    // liuqw 20110801 end
    
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	/*
	// create Navigationbar right item.
	if ([[fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame||
		[[fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
	{
        [self initRightBarButtonItemEnabledProperty];

		if (pageViewMgr.isBinderDoc == NO)
		{
			// ボタンイメージ取得
			UIImage *annoBtnImage = [UIImage imageNamed:[self getAnnotationListIcon]];

			// ボタンを登録
			buttonCommentsList = [[UIBarButtonItem alloc] initWithImage:annoBtnImage
																  style:UIBarButtonItemStyleBordered
																 target:self
																 action:@selector(actionTouchAnnotationListButton)];

			self.navigationItem.rightBarButtonItem = buttonCommentsList;
			self.navigationItem.rightBarButtonItem.enabled = annoListEnabled;
		}
		else
		{
			// ボタンイメージ取得
			UIImage *annoBtnImage = [UIImage imageNamed:[self getAnnotationListIcon]];
			UIImage *bindBtnImage = [UIImage imageNamed:[self getBinderListIcon]];

			// カスタムボタン作成
			NSArray *arrayItem = [NSArray arrayWithObjects:annoBtnImage, bindBtnImage, (char *)nil];
			
			UISegmentedControl* segmentCtrl = [[UISegmentedControl alloc] initWithItems:arrayItem];

			segmentCtrl.segmentedControlStyle = UISegmentedControlStyleBar;
			segmentCtrl.momentary = YES;
			
			[segmentCtrl addTarget:self
							action:@selector(actionTouchSegmentControl:) 
				  forControlEvents:UIControlEventValueChanged];

			[segmentCtrl setEnabled:annoListEnabled forSegmentAtIndex:0];
			[segmentCtrl setEnabled:binderListEnabled forSegmentAtIndex:1];

			// ボタンを登録
			buttonCommentsList = [[UIBarButtonItem alloc] initWithCustomView:segmentCtrl];
			
			self.navigationItem.rightBarButtonItem = buttonCommentsList;
			
			[segmentCtrl release];
		}
	}*/
	
	if ([[fileName pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame) 
	{
		// ボタンイメージ取得
		UIImage *searchBtnImage = [UIImage imageNamed:[self getZoomSettingsIcon]];

		// カスタムボタン作成
		NSArray *arrayItem = [NSArray arrayWithObjects:searchBtnImage, (char *)nil];
		UISegmentedControl *segment = [[[UISegmentedControl alloc] initWithItems:arrayItem]autorelease];
		segment.segmentedControlStyle = UISegmentedControlStyleBar;
		segment.momentary = YES;
		
		[segment setEnabled:NO forSegmentAtIndex:0];
		[segment addTarget:self
					action:@selector(actionTouchSegmentControl:) 
		  forControlEvents:UIControlEventValueChanged];
		
		// ボタンを登録
		buttonCommentsList = [[UIBarButtonItem alloc] initWithCustomView:segment];
		self.navigationItem.rightBarButtonItem = buttonCommentsList;
	}
	
	if ([[fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame||
		[[fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
	{
		[self initRightBarButtonItemEnabledProperty];
		
		if (pageViewMgr.isBinderDoc == NO) 
		{
			// ボタンイメージ取得
			UIImage *annoBtnImage	= [UIImage imageNamed:[self getAnnotationListIcon]];
			UIImage *searchBtnImage = [UIImage imageNamed:[self getZoomSettingsIcon]];
			
			// カスタムボタン作成
			NSArray *arrayItem = [NSArray arrayWithObjects:annoBtnImage, searchBtnImage, (char *)nil];
			UISegmentedControl *segment = [[[UISegmentedControl alloc] initWithItems:arrayItem]autorelease];
			segment.segmentedControlStyle = UISegmentedControlStyleBar;
			segment.momentary = YES;
			
			[segment setEnabled:annoListEnabled forSegmentAtIndex:0];
			[segment setEnabled:YES forSegmentAtIndex:1];
			[segment addTarget:self
						action:@selector(actionTouchSegmentControl:) 
			  forControlEvents:UIControlEventValueChanged];
			
			// ボタンを登録
			buttonCommentsList = [[UIBarButtonItem alloc] initWithCustomView:segment];
			self.navigationItem.rightBarButtonItem = buttonCommentsList;
		} 
		else 
		{
			// ボタンイメージ取得
			UIImage *annoBtnImage	= [UIImage imageNamed:[self getAnnotationListIcon]];
			UIImage *bindBtnImage	= [UIImage imageNamed:[self getBinderListIcon]];
			UIImage *searchBtnImage = [UIImage imageNamed:[self getZoomSettingsIcon]];
			
			// カスタムボタン作成
			NSArray *arrayItem = [NSArray arrayWithObjects:annoBtnImage, bindBtnImage, searchBtnImage, (char *)nil];
			UISegmentedControl *segment = [[[UISegmentedControl alloc] initWithItems:arrayItem]autorelease];
			segment.segmentedControlStyle = UISegmentedControlStyleBar;
			segment.momentary = YES;
			
			[segment setEnabled:annoListEnabled forSegmentAtIndex:0];
			[segment setEnabled:binderListEnabled forSegmentAtIndex:1];
			[segment setEnabled:YES forSegmentAtIndex:2];
			[segment addTarget:self
						action:@selector(actionTouchSegmentControl:) 
			  forControlEvents:UIControlEventValueChanged];
			
			// ボタンを登録
			buttonCommentsList = [[UIBarButtonItem alloc] initWithCustomView:segment];
			self.navigationItem.rightBarButtonItem = buttonCommentsList;
		}
	}
	
	activeIndicator_ = [[UIActivityIndicatorView alloc]
						initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	
	if (activeIndicator_ != nil)
	{
		activeIndicator_.frame = CGRectMake(0, 0, 40, 40);

		if ([activeIndicator_ respondsToSelector:@selector(color)])
		{
			activeIndicator_.color = [UIColor blackColor];
		}
		else
		{
			if ([[UIScreen mainScreen] scale] == 2.0)
			{
				activeIndicator_.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
			}
		}
		
		[self.view addSubview:activeIndicator_];
	}
	// xujj 2012.03.22 end
	
	// create page number label.
	pageNumberLabel = [[UIButton buttonWithType:UIButtonTypeCustom]retain];
	[pageNumberLabel setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
	pageNumberLabel.titleLabel.textColor = [UIColor blackColor];
	[pageNumberLabel setAlpha:1];
	[pageNumberLabel addTarget:self action:@selector(actionPageNumberLabelTouchDown) 
			  forControlEvents:UIControlEventTouchDown];
	
	//create pagenumber label's back view,add by yan.1122
	pageNumBackView = [[UIView alloc] init];

	//[pageNumBackView setBackgroundColor:[UIColor grayColor]];
	[pageNumBackView setBackgroundColor:[UIColor blackColor]]; // 20101222 M.Chikyu修正
	//pageNumBackView.alpha = 0.7;
	pageNumBackView.alpha = 0.6; // 20101222 M.Chikyu修正
	pageNumBackView.layer.cornerRadius = 7;
	pageNumBackView.layer.masksToBounds = YES;
	
	// add tool tip start
    
    bgToolTip = [[UIView alloc] init];
    [bgToolTip setBackgroundColor:[UIColor blackColor]];
    bgToolTip.alpha = 0.6;
    bgToolTip.layer.cornerRadius = 7;
    bgToolTip.layer.masksToBounds = YES;
    labelToolTip = [[UILabel alloc] init];
    labelToolTip.textColor = [UIColor whiteColor];
    labelToolTip.backgroundColor = [UIColor clearColor];
    labelToolTip.textAlignment = UITextAlignmentCenter;
    labelToolTip.font = [UIFont systemFontOfSize:25];
    
	// add tool tip end
	
	// create slider label.
	sliderLabel = [[UISlider alloc]init];
	sliderLabel.minimumValue = 0;
	// liuqw 20110323 start
	// スライダーバーの不具合修正
	//sliderLabel.maximumValue = [pageViewMgr getPageViewCount];
	sliderLabel.maximumValue = [pageViewMgr getPageViewCount] - 1;
	// liuqw 20110323 end
	
	sliderLabel.continuous = YES;
	
	[sliderLabel addTarget:self action:@selector(actionSliderLabelDragEnter) 
		  forControlEvents:UIControlEventTouchDown];

	[sliderLabel addTarget:self action:@selector(actionSliderLabelValueChanging) 
		  forControlEvents:UIControlEventValueChanged];

	[sliderLabel addTarget:self action:@selector(actionSliderLabelValueChanged) 
		  forControlEvents:UIControlEventTouchUpInside];

	[sliderLabel addTarget:self action:@selector(actionSliderLabelDragEnd) 
		  forControlEvents:UIControlEventTouchUpInside];
	
	// create toolbar items.
    
    // liuqw 20110801 start
    // ページ編集機能の追加
    // create edit button item.
	UIBarButtonItem* editButtonItem = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemEdit 
                                                                                   target:self 
                                                                                   action:@selector(actionOnTouchEditButton)];
	BOOL editEnable = YES;

	if (pageViewMgr.documentType == DOC_TYPE_PDF)
	{
		editEnable = NO;
	}
	else if (pageViewMgr.pageTotalCount == 0)
	{
		editEnable = NO;
	}
	else
	{
		NSArray* filePathArray = [filePath componentsSeparatedByString:@"/"];
		if ([filePathArray count]>2)
		{
			int tempPathIndex = [filePathArray count]-2;
			NSString* tempPath = [filePathArray objectAtIndex:tempPathIndex];
			NSString* tempString = [NSString stringWithFormat:@"%@", tempPath];

			if ([tempString isEqualToString:@"Inbox"] == YES)
			{
				editEnable = NO;
			}
		}
	}
	
	// xuxinjun 2012.03.23 start
	// パーミッションの対応.
	
	if ([pageViewMgr getPermissionForAnnoEdition] == NO)
	{
		editEnable = NO;
	}
	// xuxinjun 2012.03.23 end
	
	[editButtonItem setEnabled:editEnable];
    // liuqw 20110801 end
	
	// lixin 2011/09/29 start 
	fontButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFontSettingsIcon]]
													  style:UIBarButtonItemStylePlain 
													 target:self
													 action:@selector(actionTouchFontOrientationSettingsButton)];	
	// lixin 2011/09/29 end
	

	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	cooperationButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getActionIcon]]
															 style:UIBarButtonItemStylePlain 
															target:self
															action:@selector(actionTouchCooperationButton)];
	// lixin 2011/09/29 end
    
    
    
    // tongtx 20120206 start
    // MTA連動機能の対応
    
    if (fromBriefCase == YES || fromMTA == YES)
    {
        cooperationButtonItem.enabled = NO;
    }
    
    // tongtx 20120206 end
    
    
	
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	annoButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getAnnotationOnOfIcon:pageViewMgr.showAnnotation]]
													  style:UIBarButtonItemStylePlain 
													 target:self
													 action:@selector(actionTouchAnnotationOnOffButton)];
	// lixin 2011/09/29 end 
	
    // liuqw 20110627 start
    // AR NO.17779 の対応
    if (pageViewMgr.documentType != DOC_TYPE_XDW || 
        pageViewMgr.enableAnnotation == NO || 
        pageViewMgr.hasSignature == YES)
	{
		annoButtonItem.enabled = NO;
	}
	
	// xuxinjun 2012.03.28 start
	// 保護文書の対応
	if ([pageViewMgr getPermissionForAnnoEdition] == NO)
	{
		annoButtonItem.enabled = NO;
	}
	// xuxinjun 2012.03.28 end
    
    // liuqw 20110627 end
	
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	facingButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getFacingSettingsIcon]]
														style:UIBarButtonItemStylePlain 
													   target:self
													   action:@selector(actionTouchFacingSettingsButton)];
	// lixin 2011/09/29 end
    
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	zoomSettingButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getZoomSettingsIcon]]
															 style:UIBarButtonItemStylePlain 
															target:self
															action:@selector(actionTouchZoomSettingsButton)];	
	// lixin 2011/09/29 end
	
	// create flex space 
	UIBarButtonItem	*flexSpace = [[[UIBarButtonItem alloc] 
								   initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
								   target:self action:nil]autorelease];
	
	// set horizontalToolbarItems (3 button total)
	horizontalToolbarItems = [[NSMutableArray alloc]init];
    
    // liuqw 20110801 start
    // ページ編集機能の追加
    [horizontalToolbarItems addObject:editButtonItem];
    // liuqw 20110801 end
	
	[horizontalToolbarItems addObject:flexSpace];
	[horizontalToolbarItems addObject:fontButtonItem];
	[horizontalToolbarItems addObject:flexSpace];
	[horizontalToolbarItems addObject:cooperationButtonItem];
	[horizontalToolbarItems addObject:flexSpace];
	[horizontalToolbarItems addObject:annoButtonItem];
	[horizontalToolbarItems addObject:flexSpace];
    
    // 「拡大率指定ボタンの追加」の対応 start
    [horizontalToolbarItems addObject:zoomSettingButtonItem];
	[horizontalToolbarItems addObject:flexSpace];
    // 「拡大率指定ボタンの追加」の対応 end
	
	// set verticalToolbarItems (4 button total)
	verticalToolbarItems = [[NSMutableArray alloc]init];
    
    // liuqw 20110801 start
    // ページ編集機能の追加
    [verticalToolbarItems addObject:editButtonItem];
    // liuqw 20110801 end
    
	[verticalToolbarItems addObject:flexSpace];
	[verticalToolbarItems addObject:facingButtonItem];
	[verticalToolbarItems addObject:flexSpace];
	[verticalToolbarItems addObject:fontButtonItem];
	[verticalToolbarItems addObject:flexSpace];	
	[verticalToolbarItems addObject:cooperationButtonItem];
	[verticalToolbarItems addObject:flexSpace];
	[verticalToolbarItems addObject:annoButtonItem];
	[verticalToolbarItems addObject:flexSpace];
    
    // 「拡大率指定ボタンの追加」の対応 start
    [verticalToolbarItems addObject:zoomSettingButtonItem];
	[verticalToolbarItems addObject:flexSpace];
    // 「拡大率指定ボタンの追加」の対応 end
    
    // lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	[editButtonItem release];
	// lixin 2011/09/29 end

	// xujj 2012.03.22 start
	// 検索機能の追加
	searchBar_ = [[UISearchBar alloc] init];
	searchBar_.barStyle				= UIBarStyleBlackTranslucent;
	searchBar_.keyboardType			= UIKeyboardTypeDefault;
	searchBar_.showsCancelButton	= YES;
	searchBar_.delegate				= self;
	searchBar_.placeholder			= NSLocalizedString(@"MSG_SEARCH_HOLD_TEXT", nil);
	
	[self setSearchBarCancelButtonEnabled];
	
	searchToolbarItems_ = [[NSMutableArray alloc] init];
	
	UIBarButtonItem *frontButtonItem = [[[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_FRONT", nil)
																		 style:UIBarButtonItemStyleBordered
																		target:self
																		action:@selector(actionTouchFrontSearchButton)] autorelease];
	
	UIBarButtonItem *nextButtonItem = [[[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_NEXT", nil)
																		style:UIBarButtonItemStyleBordered
																	   target:self
																	   action:@selector(actionTouchNextSearchButton)] autorelease];
	[searchToolbarItems_ addObject:flexSpace];
	[searchToolbarItems_ addObject:frontButtonItem];
	[searchToolbarItems_ addObject:flexSpace];
	[searchToolbarItems_ addObject:nextButtonItem];
	[searchToolbarItems_ addObject:flexSpace];
	
	NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
	[notificationCenter addObserver:self 
                           selector:@selector(actionOnKeyboardDidHidden) 
                               name:UIKeyboardDidHideNotification
                             object:nil];
	// xujj 2012.03.22 end
	
	// set toobar items
	if ([self UIDeviceIsPortrait] == YES)
	{
		self.toolbarItems = horizontalToolbarItems;
	}
	else
	{
		self.toolbarItems = verticalToolbarItems;
	}
	
	// create scroll view.
	bgScrollView = [[UIScrollView alloc] init];
	[bgScrollView setBackgroundColor:[UIColor grayColor]];
	// 「先読む」機能の対応 start
	//bgScrollView.scrollEnabled = NO;
	bgScrollView.scrollEnabled = YES;
	bgScrollView.pagingEnabled = YES;
	bgScrollView.delegate = self;
	// 「先読む」機能の対応 end
	bgScrollView.showsHorizontalScrollIndicator = NO;
	bgScrollView.showsVerticalScrollIndicator = NO;
	bgScrollView.scrollsToTop = NO;
	bgScrollView.tag = BACK_GROUND_SCROLLVIEW_TAG;
	
	[bgScrollView addGestureRecognizer:singleTapGestureRecognizer];
	[bgScrollView addGestureRecognizer:doubleTapGestureRecognizer];
	[bgScrollView addGestureRecognizer:twoFingerTapGestureRecognizer];
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	
	if (pageViewMgr.documentType == DOC_TYPE_XDW)
	{
		[bgScrollView addGestureRecognizer:longPressTapGestureRecognizer];
	}
	
	// tongtx 2012.03.23 end
    
	// create annotation list view.
	annotationListView = [[UIView alloc]init];
	[annotationListView setBackgroundColor:[UIColor clearColor]];
	
	// create annotation list background view
	annotationListBackgroundView = [[UIView alloc] init];
	[annotationListBackgroundView setBackgroundColor:[UIColor blackColor]];
	annotationListBackgroundView.alpha = 0.7;
	
	// create annotation list title view.
	annotationListTitle = [[UIView alloc]init];
	kindTitle = [[UILabel alloc] init];
	[kindTitle setBackgroundColor:[UIColor clearColor]];
	kindTitle.textColor = [UIColor whiteColor];
	kindTitle.font = [UIFont systemFontOfSize:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	kindTitle.textAlignment = UITextAlignmentCenter;
		kindTitle.text = NSLocalizedString(@"TITLE_ANNOTATIONLISTVIEW_KIND", nil);
	[annotationListTitle addSubview:kindTitle];
	[kindTitle release];
	
	numberTitle = [[UILabel alloc] init];
	numberTitle.font = [UIFont systemFontOfSize:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	[numberTitle setBackgroundColor:[UIColor clearColor]];
	numberTitle.textColor = [UIColor whiteColor];
	numberTitle.textAlignment = UITextAlignmentCenter;
	numberTitle.text = NSLocalizedString(@"TITLE_ANNOTATIONLISTVIEW_PAGE", nil);
	[annotationListTitle addSubview:numberTitle];
	[numberTitle release];
	
	contentTitle = [[UILabel alloc]init];
	contentTitle.font = [UIFont systemFontOfSize:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	[contentTitle setBackgroundColor:[UIColor clearColor]];
	contentTitle.textColor = [UIColor whiteColor];
	contentTitle.text = NSLocalizedString(@"TITLE_ANNOTATIONLISTVIEW_CONTENT", nil);
	[annotationListTitle addSubview:contentTitle];
	[contentTitle release];
	
	separatorView = [[UIView alloc] init];
	[separatorView setBackgroundColor:[UIColor lightGrayColor]];
	
	// create annotation list table view.
	annotationListViewController = [[AnnotationListViewController alloc]
									initWithPageViewManager:pageViewMgr];
	[annotationListViewController.view setBackgroundColor:[UIColor clearColor]];
	annotationListViewController.delegate = self;
	
	[annotationListView addSubview:annotationListBackgroundView];
	[annotationListView addSubview:annotationListTitle];
	[annotationListView addSubview:separatorView];
	[annotationListView addSubview:annotationListViewController.view];
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	xdwDocListView = [[UIView alloc] init];
	[xdwDocListView setBackgroundColor:[UIColor clearColor]];
	
	// create annotation list background view
	xdwDocListBackgroundView = [[UIView alloc] init];
	[xdwDocListBackgroundView setBackgroundColor:[UIColor blackColor]];
	xdwDocListBackgroundView.alpha = 0.7;
	
	// create annotation list title view.
	xdwDocListTitle = [[UIView alloc]init];
	docNameTitle = [[UILabel alloc] init];
	[docNameTitle setBackgroundColor:[UIColor clearColor]];
	docNameTitle.textColor = [UIColor whiteColor];
	docNameTitle.font = [UIFont systemFontOfSize:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	docNameTitle.textAlignment = UITextAlignmentLeft;
	docNameTitle.text = NSLocalizedString(@"TITLE_XDWDOCLISTVIEW_NAME", nil);
	[xdwDocListTitle addSubview:docNameTitle];
	[docNameTitle release];
	
	docNumberTitle = [[UILabel alloc] init];
	docNumberTitle.font = [UIFont systemFontOfSize:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	[docNumberTitle setBackgroundColor:[UIColor clearColor]];
	docNumberTitle.textColor = [UIColor whiteColor];
	docNumberTitle.textAlignment = UITextAlignmentCenter;
	docNumberTitle.text = NSLocalizedString(@"TITLE_XDWDOCLISTVIEW_PAGE", nil);
	[xdwDocListTitle addSubview:docNumberTitle];
	[docNumberTitle release];

	xdwDocSeparatorView = [[UIView alloc] init];
	[xdwDocSeparatorView setBackgroundColor:[UIColor lightGrayColor]];
	
	// create annotation list table view.
	xdwDocListViewController = [[XdwListinXbdViewController alloc]
									initWithPageViewManager:pageViewMgr];
	[xdwDocListViewController.view setBackgroundColor:[UIColor clearColor]];
	xdwDocListViewController.delegate = self;
	
	[xdwDocListView addSubview:xdwDocListBackgroundView];
	[xdwDocListView addSubview:xdwDocListTitle];
	[xdwDocListView addSubview:xdwDocSeparatorView];
	[xdwDocListView addSubview:xdwDocListViewController.view];
	// 3.6 バインダ文書対応 の対応 end
    
	facingSettings = [[FacingSettingsViewController alloc]init];
	facingSettings.index = pageViewMgr.facingMode;
	facingSettings.delegate = self;
	
	fontSettings = [[FontSettingsViewController alloc]init];
	fontSettings.delegate = self;
	
	// lixin 20110813 start
	// ページ編集機能の追加  DW_iPhoneViewer_20
    editFacingPageViewController = [[DWEditFacingPageViewController alloc] init];
	editFacingPageViewController.delegate = self;
	// lixin 20110813 end

	if (pageViewMgr.fontOrient)
	{
		fontSettings.index = 0;
	}
	else
	{
		fontSettings.index = 1;
	}
	
	// SendEmail の対応 start
	cooperationSettings = [[CooperationSettingsViewController alloc]init];
	cooperationSettings.delegate = self;
	// SendEmail の対応 end
	
	if ( Utility::UIDeviceIsiPad() )
	{
		fontPopMenu = [[UIPopoverController alloc]initWithContentViewController:fontSettings];
		[fontPopMenu setPopoverContentSize:CGSizeMake(320, 88) animated:NO];
	
		facingPopMenu = [[UIPopoverController alloc]initWithContentViewController:facingSettings];
		[facingPopMenu setPopoverContentSize:CGSizeMake(320, 132) animated:NO];
		
		// SendEmail の対応 start
		cooperationPopMenu = [[UIPopoverController alloc]initWithContentViewController:cooperationSettings];
		[cooperationPopMenu setPopoverContentSize:CGSizeMake(240, 88) animated:NO];
		// SendEmail の対応 end
		
		// lixin 20110813 start
		// ページ編集機能の追加  DW_iPhoneViewer_20
		editFacingPageViewPopController = [[UIPopoverController alloc]initWithContentViewController:editFacingPageViewController];
		[editFacingPageViewPopController setPopoverContentSize:CGSizeMake(320, 88) animated:NO];
		// lixin 20110813 end
	}
}

- (void) initViewControlsRect
{
	long screenW = 0;
	long screenH = 0;
	CGRect screenFrame = [[UIScreen mainScreen] bounds];
	CGRect toolbarRect = [self.navigationController toolbar].frame;
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		screenW = screenFrame.size.width;
		screenH = screenFrame.size.height;
		scrollViewRect = CGRectMake(0.0, 0.0, screenW, screenFrame.size.height);
		sliderLabelRect = CGRectMake(20, toolbarRect.origin.y - 40, toolbarRect.size.width - 40, 40);
		annotationListViewRect = CGRectMake(screenW / 2, toolbarRect.size.height + statusRectHeight, 
											screenW / 2, screenH - (toolbarRect.size.height)*2 - statusRectHeight);
		fontSettingsRect = CGRectMake(toolbarRect.size.width *2 / 5, toolbarRect.origin.y - 60, 100, 60);
		
		// lixin 20110813 start
		// ページ編集機能の追加  DW_iPhoneViewer_20
		chooseEditPageIndexViewRect = CGRectMake(toolbarRect.size.width *2 / 5, toolbarRect.origin.y - 60, 100, 60);
		// lixin 20110813 end
	}
	else
	{
		screenW = screenFrame.size.height;
		screenH = screenFrame.size.width;
		scrollViewRect = CGRectMake(0.0, 0.0, screenW, screenH);
		sliderLabelRect = CGRectMake(20, toolbarRect.origin.y - 40, toolbarRect.size.width - 40, 40);
		annotationListViewRect = CGRectMake(screenW / 2, toolbarRect.size.height + statusRectHeight, 
											screenW / 2, screenH - (toolbarRect.size.height)*2 - statusRectHeight);
		facingSettingsRect = CGRectMake(toolbarRect.size.width / 3, toolbarRect.origin.y - 90, 160, 90);
		fontSettingsRect = CGRectMake(toolbarRect.size.width / 2, toolbarRect.origin.y - 60, 100, 60);
		
		// lixin 20110813 start
		// ページ編集機能の追加  DW_iPhoneViewer_20
		chooseEditPageIndexViewRect = CGRectMake(toolbarRect.size.width / 2, toolbarRect.origin.y - 60, 100, 60);
		// lixin 20110813 end
	}
	annotationListBackgroundViewRect = CGRectMake(0.0, 0.0, annotationListViewRect.size.width, 
												  annotationListViewRect.size.height);
	annotationListTitleRect = CGRectMake(0.0, 0.0, annotationListViewRect.size.width, 30);
	kindTitleRect = CGRectMake(5, 10, 35, 15);
	numberTitleRect = CGRectMake(40, 10, 40, 15);
	contentTitleRect = CGRectMake(85, 10, annotationListViewRect.size.width - 92, 15);
	separatorViewRect = CGRectMake(0.0, 25, annotationListViewRect.size.width, 2);
	annotationListViewControllerRect = CGRectMake(0.0, 30, 
												  annotationListViewRect.size.width, 
												  annotationListViewRect.size.height - 30);
	sliderLabel.frame = sliderLabelRect;
	bgScrollView.frame = scrollViewRect;
	annotationListBackgroundView.frame = annotationListBackgroundViewRect;
	annotationListView.frame = annotationListViewRect;
	annotationListTitle.frame = annotationListTitleRect;
	kindTitle.frame = kindTitleRect;
	annotationListViewController.kindLabelRect = CGRectMake(7, 5, 30, _ANNOTATION_LIST_TEXT_FONTSIZE_ * 1.2);
	numberTitle.frame = numberTitleRect;
	separatorView.frame = separatorViewRect;
	annotationListViewController.numberLabelRect =  CGRectMake(40, 5, 20, _ANNOTATION_LIST_TEXT_FONTSIZE_ * 1.2);
	contentTitle.frame = contentTitleRect;
	annotationListViewController.contentLabelRect = CGRectMake(85, 5, 
															   annotationListViewRect.size.width - 92, 
															   _ANNOTATION_LIST_TEXT_FONTSIZE_*2.4);
	annotationListViewController.view.frame = annotationListViewControllerRect;
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	docNameTitleRect = CGRectMake(5, 10, 80, 15);
	docNumberTitleRect = CGRectMake(annotationListViewRect.size.width - 60, 5, 
									60, _ANNOTATION_LIST_TEXT_FONTSIZE_*2.4);
	xdwDocListBackgroundView.frame = annotationListBackgroundViewRect;
	xdwDocListView.frame = annotationListViewRect;
	xdwDocListTitle.frame = annotationListTitleRect;
	docNameTitle.frame = docNameTitleRect;
	docNumberTitle.frame = docNumberTitleRect;
	xdwDocSeparatorView.frame = separatorViewRect;
	xdwDocListViewController.nameLabelRect =  CGRectMake(7, 5, 
														 annotationListViewRect.size.width - 70, 
														 _ANNOTATION_LIST_TEXT_FONTSIZE_*2.4);
	xdwDocListViewController.pageLabelRect = CGRectMake(annotationListViewRect.size.width - 60, 5, 
														60, _ANNOTATION_LIST_TEXT_FONTSIZE_*1.2);
	xdwDocListViewController.view.frame = annotationListViewControllerRect;
	
	// 3.6 バインダ文書対応 の対応 end
}

- (void) initPageNumberlabelRect
{
	long screenW = 0;
	long screenH = 0;
	CGRect screenFrame = [[UIScreen mainScreen] bounds];
	CGRect toolbarRect = [self.navigationController toolbar].frame;

	if ([self UIDeviceIsPortrait] == YES)
	{
		screenW = screenFrame.size.width;
		screenH = screenFrame.size.height;

		if (hideToolbar == NO)
		{
			// 2012.02.01(Ver2.1 New) M.Chikyu
		//	pageNumberLabelRect = CGRectMake(10.0, toolbarRect.size.height + 30, screenW / 3, screenH / 24);
			pageNumberLabelRect = CGRectMake(10.0, toolbarRect.size.height + 10, screenW / 3, screenH / 24);
			// 2012.02.01(Ver2.1 New) M.Chikyu
		}
		else
		{
			pageNumberLabelRect = CGRectMake(10.0, 10.0, screenW / 3, screenH / 24);			
		}
	}
	else
	{
		screenW = screenFrame.size.height;
		screenH = screenFrame.size.width;

		if (hideToolbar == NO)
		{
			// 2012.02.01(Ver2.1 New) M.Chikyu
		//	pageNumberLabelRect = CGRectMake(10.0, toolbarRect.size.height + 30, screenH / 3, screenW / 24);
			pageNumberLabelRect = CGRectMake(10.0, toolbarRect.size.height + 10, screenH / 3, screenW / 24);
			// 2012.02.01(Ver2.1 New) M.Chikyu
		}
		else
		{
			pageNumberLabelRect = CGRectMake(10.0, 10.0, screenH / 3, screenW / 24);
		}
	}

	pageNumberLabel.frame = CGRectMake(3, 
									   0, 
									   pageNumberLabelRect.size.width - 6, 
									   pageNumberLabelRect.size.height);
	
}

- (void) initToolbarButton:(UIButton*)button 
			  withIconName:(NSString*)name 
				withAction:(SEL)action
{
	UIImage *image = [UIImage imageNamed:name];
	[button setImage:image forState:UIControlStateNormal];
	button.frame = CGRectMake(0, 0, 25, 25);
	[button addTarget:self action:action forControlEvents:UIControlEventTouchUpInside];
	//[image release];
}


#pragma mark -
#pragma mark mehtod about pageview
- (DWScrollView*) getActivePageView
{
	return [self getPageViewWithPosition:pageViewPos];
}

- (DWScrollView*) getPageViewWithPosition:(int)pos
{
	int tag = pos;
	
	if (pageViewMgr.fontOrient == NO)
	{
		tag = ([pageViewMgr getPageViewCount] - 1) - pos;
	}
	
	for (UIView* subView in bgScrollView.subviews) 
	{
		if (subView.tag == tag) 
		{
			return (DWScrollView*)subView;
		}
	}

	return nil;
}


#pragma mark -
#pragma mark insert new pageview
- (void) insertPageViewWithPosition:(int)pos
{
	if (bgScrollView.subviews.count >= Utility::INIT_VIEW_COUNT)
	{
		int farPos = -1, interval = 0;

		for (int i = 0; i < bgScrollView.subviews.count; i++) 
		{
			DWScrollView *subView = (DWScrollView*)[bgScrollView.subviews objectAtIndex:i];

			// float subViewOriginX = subView.frame.origin.x + kPageEdgeWidth;
			float subViewOriginX = subView.frame.origin.x;
			float subViewWidth = bgScrollView.frame.size.width;

			int position = subViewOriginX / subViewWidth;

			if (interval < fabs(position - pos))
			{
				farPos = position;
				interval = fabs(position - pos);
			}
		}
		
		DWScrollView *pageView = [self getPageViewWithPosition:farPos];

		if (pageView != nil)
		{
			[pageView removeFromSuperview];
			
			if (pageView.page != nil)
			{
				[pageView.page removeFromSuperview];
				[pageView.page release];
			}
			
			[pageView release];
		}
	}
	
	int index = pos;
	
	if (pageViewMgr.fontOrient == NO)
	{
		index = ([pageViewMgr getPageViewCount] - 1) - pos;
	}
	
	DWScrollView *pageView = [pageViewMgr insertNewPageViewWithPageIndex:index];
	CGRect frame = pageView.frame;

	// frame.origin = CGPointMake(bgScrollView.frame.size.width * pos - kPageEdgeWidth, 0);
	frame.origin = CGPointMake(bgScrollView.frame.size.width * pos, 0);
	pageView.frame = frame;

	// 2012.02.01(Ver2.1 New) M.Chikyu
	[self shiftPage:pageView position:pos];
	// 2012.02.01(Ver2.1 New) M.Chikyu

	[bgScrollView addSubview:pageView];
}

- (void) removePageViewsFromScrollView
{
	NSArray *subviews = [bgScrollView subviews];
	
	for (DWScrollView *pageView in subviews)
	{
		if (pageView != nil)
		{
			[pageView removeFromSuperview];
			
			if (pageView.page != nil)
			{
				[pageView.page removeFromSuperview];
				[pageView.page release];
			}
			[pageView release];
		}
	}
}

- (void) updateScrollViewContentSize
{
	int pageCount = [pageViewMgr getPageViewCount];
	int width = bgScrollView.frame.size.width * pageCount;
	bgScrollView.contentSize = CGSizeMake(width, bgScrollView.frame.size.height);
}

- (void) setPageContentOffset:(CGPoint)offset
{
	DWScrollView *pageView = [self getActivePageView];
	
	if (pageView == nil)
	{
		return;
	}
	
	[pageView setContentOffset:offset animated:NO];
}

- (CGPoint) getPageOffset
{
	pageOffset = pageViewMgr.pageOffset;
	float offsetX = pageOffset.x;
	float offsetY = pageOffset.y;
	
	DWScrollView *pageView = [self getActivePageView];
	
	CGSize screenSize	= [pageViewMgr getScreenRect].size;
	CGSize pageSize		= [pageViewMgr getPageViewCurrentContentSizeWithPageView:pageView];
	
	float pageWidth = pageSize.width;
	
	float backgroundWidth = screenSize.width;

	if (offsetX > pageWidth - backgroundWidth)
	{
		offsetX = pageWidth - backgroundWidth;
	}
	if (offsetX < 0.0)
	{
		offsetX = 0.0;
	}
	
	float pageHeight = pageSize.height;
	float backgroundHeight = screenSize.height;

	if (offsetY > pageHeight - backgroundHeight)
	{
		offsetY = pageHeight - backgroundHeight;
	}
	
	if (offsetY < 0.0)
	{
		offsetY = 0.0;
	}
	
	pageOffset = CGPointMake(offsetX, offsetY);
	pageViewMgr.pageOffset = pageOffset;

	return pageOffset;
}


#pragma mark -
#pragma mark left bar item.
- (void) initLeftBarItem
{
    UIButton* buttonBack = [UIButton buttonWithType:(UIButtonType)101];
    [buttonBack setTitle:backButtonTitle_ forState:UIControlStateNormal];
    [buttonBack addTarget:self action:@selector(actionOnTouchLeftBarItem) forControlEvents:UIControlEventTouchDown];
    UIBarButtonItem* leftButtonItem = [[UIBarButtonItem alloc]initWithCustomView:buttonBack];
    self.navigationItem.leftBarButtonItem = leftButtonItem;
    [leftButtonItem release];
}

- (void) actionOnTouchLeftBarItem
{
	if ([pageViewMgr isTempFileEditing] == YES)
	{
		if (fromBriefCase == YES)
		{
			if ([self isAssociateApplicationCanOpenWithIsUpdated:YES] == NO)
			{
				return;
			}
			
			if ([self isInteracionDocumentUpdated] == NO && 
                documentSettingsMgr.targetFilename != nil)
			{
				[self interacionWithBriefCase];
				return;
			}
		}
        
        // tongtx 20120206 start
        // MTA連動機能の対応
        
        if (fromMTA == YES)
        {
            if ([self isAssociateApplicationCanOpenWithIsUpdated:YES] == NO)
            {
                return;
            }
            
            if ([self isInteracionDocumentUpdated] == NO && 
                documentSettingsMgr.targetFilename != nil)
            {
                [self returnToAssociateApplicationWithUTI];
                return;
            }
        }
        
        // tongtx 20120206 end
		
		
		if ([self isTempFileUpdated] == YES)
		{
            [self cancelShowScreen];
			
			NSString *message = nil;
			NSString* currentFileName = [filePath lastPathComponent];
            
			// tongtx 20110830 start
			// 付箋のUnicode保存
			if ([pageViewMgr isDocumentVersionUpdated] == YES)
			{
                if (fromBriefCase == YES)
				{
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_BRIEFCASE_CHARSET_UNICODE",nil), self.fileName, BRIEFCASE_LINK_NAME];
                }
                
                // tongtx 20120206 start
                // MTA連動機能の対応
                else if (fromMTA == YES)
                {
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_BRIEFCASE_CHARSET_UNICODE",nil), self.fileName, appnameFromMTA_];
                }
                // tongtx 20120206 end
                
				else
				{
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_DOCUWORKS_CHARSET_UNICODE", nil), currentFileName];
                }
			}
			else
			{
				if (fromBriefCase == YES)
				{
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_SAVE",nil), self.fileName, BRIEFCASE_LINK_NAME];
                }
                
                // tongtx 20120206 start
                // MTA連動機能の対応
                else if (fromMTA == YES) 
                {
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_SAVE",nil), self.fileName, appnameFromMTA_];
                }
                // tongtx 20120206 end
                
				else
				{
                    message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ANNOTATIONEDIT_SAVE", nil), currentFileName];
                }
            }
			// tongtx 20110830 end
			
			UIAlertView* alertSaveUpdate = [[UIAlertView alloc] initWithTitle:nil
																	  message:message
																	 delegate:self
															cancelButtonTitle:NSLocalizedString(@"BUTTON_HANLEOPENURL_SAVE", nil)
															otherButtonTitles:NSLocalizedString(@"BUTTON_HANLEOPENURL_NOTSAVE", nil), 
											(char *)nil];
			alertSaveUpdate.tag = TAG_SAVE_UPDATE_ALERT;
			
			[alertSaveUpdate show];
			[alertSaveUpdate release];
			
		}
		else
		{
			// tongtx 2011/08/31 start
			// Briefcaseと連携機能の追加
			/*
			 [pageViewMgr cleanTempDirectory];
			 [self.navigationController popViewControllerAnimated:YES];
			 */
			if (fromBriefCase == YES)
			{
				if ([self isInteracionDocumentUpdated] == NO && 
					documentSettingsMgr.targetFilename != nil)
				{
					[self interacionWithBriefCase];
					return;
				}
				else
				{
					[self returnToAssociateApplicationWithIsUpdated:NO];
				}
			}
            
            // tongtx 20120206 start
            // MTA連動機能の対応
            
            else if (fromMTA == YES)
            {
                if ([self isInteracionDocumentUpdated] == NO && 
                    documentSettingsMgr.targetFilename != nil)
                {
                    [self returnToAssociateApplicationWithUTI];
                    return;
                }
                else
                {
                    [self returnToAssociateApplicationWithIsUpdated:NO];
                }
            }
            
            // tongtx 20120206 end
            
			else
			{
				// lixin 2011/09/24 start 
				// NS-AR007 の対応
				NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
				NSString *documentPath = [paths objectAtIndex:0];
				self.filePath = [NSString stringWithFormat:@"%@/%@", documentPath, fileName];
				// lixin 2011/09/24 end
				[pageViewMgr cleanTempDirectory];
				[self.navigationController popViewControllerAnimated:YES];
			}
			// tongtx 2011/08/31 end
		}
	}
	else
	{
        // tongtx 20120206 start
        // MTA連動機能の対応
        if (fromBriefCase == YES || fromMTA == YES)
        {
            if ([self isAssociateApplicationCanOpenWithIsUpdated:NO])
            {
                [self returnToAssociateApplicationWithIsUpdated:NO];
            }
        }
        // tongtx 20120206 end
		else
		{
			[pageViewMgr cleanTempDirectory];
			[self.navigationController popViewControllerAnimated:YES];
		}
    }
}


#pragma mark -
#pragma mark right bar item.
- (void) actionTouchAnnotationListButton
{	
	[self cancelShowScreen];
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	if (showXdwDocList == YES)
	{
		showXdwDocList = NO;
		[xdwDocListView removeFromSuperview];
	}
	// 3.6 バインダ文書対応 の対応 end
	if (showAnnotationList == YES)
	{
		[self removeToolbarPopView];
	}
	
    // liuqw 20110627 start
    // AR NO.17873 の対応
	//if (showAnnotationList == NO && positionAnnotCount > 0)
    if (showAnnotationList == NO)
		// liuqw 20110627 end
	{
		// if file's name is xbd or xdw,if none of them,do nothing
		if (pageViewMgr.documentType == DOC_TYPE_XDW)
		{
			//AR No.61
			sliderLabel.userInteractionEnabled = NO;
			[self.view addSubview:annotationListView];
			CGRect screenRects = [[UIScreen mainScreen] bounds];
			
			if ([self UIDeviceIsPortrait])
			{
				annotationListView.alpha = 0;
				annotationListView.frame = CGRectMake(screenRects.size.width, 
													  annotationListViewRect.origin.y, 
													  annotationListViewRect.size.width, 
													  annotationListViewRect.size.height);
				
				[UIView beginAnimations:nil context:nil];
				[UIView setAnimationDuration:0.2];
				annotationListView.frame = CGRectMake(screenRects.size.width - annotationListViewRect.size.width, 
													  annotationListViewRect.origin.y, 
													  annotationListViewRect.size.width, 
													  annotationListViewRect.size.height);
				annotationListView.alpha = 1.0;
				[UIView commitAnimations];
			}
			else
			{
				annotationListView.alpha = 0;
				annotationListView.frame = CGRectMake(screenRects.size.height, 
													  annotationListViewRect.origin.y, 
													  annotationListViewRect.size.width, 
													  annotationListViewRect.size.height);
				
				[UIView beginAnimations:nil context:nil];
				[UIView setAnimationDuration:0.2];
				annotationListView.frame = CGRectMake(screenRects.size.height - annotationListViewRect.size.width+5, 
													  annotationListViewRect.origin.y, 
													  annotationListViewRect.size.width, 
													  annotationListViewRect.size.height);
				annotationListView.alpha = 1.0;
				[UIView commitAnimations];
			}
			showAnnotationList = YES;
		}
		else
		{
			showAnnotationList = YES;
		}
		
	}
	else
	{
		//AR No.61
		sliderLabel.userInteractionEnabled = YES;
		[annotationListView removeFromSuperview];
		
		// 3.6 バインダ文書対応 の対応 start
		// change by lixin 20110608 DW_iPhoneEnhance_12
		[xdwDocListView removeFromSuperview];
		// 3.6 バインダ文書対応 の対応 end
		
		showAnnotationList = NO;
		[self performShowScreen];
	}
}

// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
- (void) actionTouchSegmentControl:(id)sender
{
	UISegmentedControl* segmentCtrl = (UISegmentedControl*)sender;
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	/*
	switch (segmentCtrl.selectedSegmentIndex)
	{
		case 0:
			[self actionTouchAnnotationListButton];
			break;
			
		case 1:
			[self actionTouchXdwDocListButton];
			break;
			
		default:
			break;
	}*/
	
	if (pageViewMgr.isBinderDoc == NO) 
	{
		switch (segmentCtrl.selectedSegmentIndex)
		{
			case 0:
				[self actionTouchAnnotationListButton];
				break;
				
			case 1:
				[self actionTouchSearchButton];
				break;
				
			default:
				break;
		}
	} 
	else 
	{
		switch (segmentCtrl.selectedSegmentIndex) 
		{
			case 0:
				[self actionTouchAnnotationListButton];
				break;
				
			case 1:
				[self actionTouchXdwDocListButton];
				break;
				
			case 2:
				[self actionTouchSearchButton];
				break;
				
			default:
				break;
		}
	}
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	[self cancelSelectMode];
	// tongtx 2012.03.23 end
}

- (void) actionTouchXdwDocListButton
{	
	[self cancelShowScreen];
	if (showAnnotationList == YES)
	{
		showAnnotationList = NO;
		[annotationListView removeFromSuperview];
	}
	
	if (showXdwDocList == YES)
	{
		[self removeToolbarPopView];
	}
	
	if (showXdwDocList == NO)
	{
		// if file's name is xbd or xdw,if none of them,do nothing
		XdwFileInfo* xdwFileInfo = (XdwFileInfo*)pageViewMgr.handleDocument->GetFileInfo();
		if (xdwFileInfo->IsBinder() == YES && 
            xdwFileInfo->GetBinderCount() != 0)
		{
            
            // lixin 20110626 DW_iPhoneEnhance_12 start
            // AR.17872 の対応 
            [xdwDocListViewController.tableView reloadData];
            // lixin 20110626 DW_iPhoneEnhance_12 end
            
			sliderLabel.userInteractionEnabled = NO;
			[self.view addSubview:xdwDocListView];
			CGRect screenRects = [[UIScreen mainScreen] bounds];
			
			if ([self UIDeviceIsPortrait])
			{
				xdwDocListView.alpha = 0;
				xdwDocListView.frame = CGRectMake(screenRects.size.width, 
												  annotationListViewRect.origin.y, 
												  annotationListViewRect.size.width, 
												  annotationListViewRect.size.height);
				
				[UIView beginAnimations:nil context:nil];
				[UIView setAnimationDuration:0.2];
				xdwDocListView.frame = CGRectMake(screenRects.size.width - annotationListViewRect.size.width, 
												  annotationListViewRect.origin.y, 
												  annotationListViewRect.size.width, 
												  annotationListViewRect.size.height);
				xdwDocListView.alpha = 1.0;
				[UIView commitAnimations];
			}
			else
			{
				xdwDocListView.alpha = 0;
				xdwDocListView.frame = CGRectMake(screenRects.size.height, 
												  annotationListViewRect.origin.y, 
												  annotationListViewRect.size.width, 
												  annotationListViewRect.size.height);
				
				[UIView beginAnimations:nil context:nil];
				[UIView setAnimationDuration:0.2];
				xdwDocListView.frame = CGRectMake(screenRects.size.height - annotationListViewRect.size.width+5, 
												  annotationListViewRect.origin.y, 
												  annotationListViewRect.size.width, 
												  annotationListViewRect.size.height);
				xdwDocListView.alpha = 1.0;
				[UIView commitAnimations];
			}
			showXdwDocList = YES;
		}
		else
		{
			showXdwDocList = YES;
		}
		
	}
	else
	{
		sliderLabel.userInteractionEnabled = YES;
		[xdwDocListView removeFromSuperview];
		showXdwDocList = NO;
		[self performShowScreen];
	}
}
// 3.6 バインダ文書対応 の対応 end

- (void)didSelectAnnotationInTable:(AnnotationListViewController*)sender
{
	if (sender != nil)
	{
		// AR NO.17557 の対応 start
		BOOL isLeftPage = YES;
		
		// 1. get page index.
		int pageIndex = 0;
		
		if (pageViewMgr.facingMode == MODE_REGULAR)
		{
			pageIndex = sender.pageIndex;
		}
		else if (pageViewMgr.facingMode == MODE_FACE_NO)
		{
			if (pageViewMgr.pageTotalCount == 1) 
			{
				pageIndex = 0;
				isLeftPage = YES;
			} 
			else
			{
				pageIndex = sender.pageIndex / 2;
				
				// set left page flag.
				if (pageViewMgr.fontOrient == YES)
				{
					if (sender.pageIndex % 2 == 0)
					{
						isLeftPage = YES;
					}
					else
					{
						isLeftPage = NO;
					}
				}
				else
				{
					if (sender.pageIndex % 2 == 0)
					{
						isLeftPage = NO;
					}
					else
					{
						isLeftPage = YES;
					}
				}
			}
		}
		else if (pageViewMgr.facingMode == MODE_FACE_YES)
		{
			if (pageViewMgr.pageTotalCount == 1) 
			{
				pageIndex = 0;
				isLeftPage = YES;
			} 
			else
			{
				if (sender.pageIndex == 0)
				{
					pageIndex = sender.pageIndex;
				}
				else
				{
					pageIndex = sender.pageIndex / 2 + sender.pageIndex % 2;
					
					// set left page flag.
					if (pageViewMgr.fontOrient == YES)
					{
						if (sender.pageIndex % 2 == 1)
						{
							isLeftPage = YES;
						}
						else
						{
							isLeftPage = NO;
						}
					}
					else
					{
						if (sender.pageIndex == pageViewMgr.pageTotalCount - 1) 
						{
							isLeftPage = YES;
						} 
						else 
						{
							if (sender.pageIndex % 2 == 1)
							{
								isLeftPage = NO;
							}
							else
							{
								isLeftPage = YES;
							}
						}
					}
				}
			}
		}
		
		// AR NO.17719 の対応 start
		if ([self UIDeviceIsPortrait] == YES)
		{
			pageIndex = sender.pageIndex;
		}
		// AR NO.17719 の対応 end
		
		// 2. move page to target page.
		pageViewPos = pageIndex;
		
		if (pageViewMgr.fontOrient == NO)
		{
			pageViewPos = [pageViewMgr getPageViewCount] - 1 - pageIndex;
		}
		
		[self actionMovePageWithPosition:pageViewPos 
						withMovePageMode:MODE_PAGE_NUMBER];
		[self updatePageNumberLabel:pageViewPos];
		
		// 3. get annotation rect and zoom page view.
		DWScrollView *pageView = [self getActivePageView];
		
		if (pageView != nil)
		{
			// 3.1 get annotation rect.
			long scale = pageView.page.m_PageInfoA.m_PageFitScale;
			float annotLeftTopX = Utility::MMToPixelWithScale(sender.leftTopX, scale);
			float annotLeftTopY = Utility::MMToPixelWithScale(sender.leftTopY, scale);
			float annotRightButtomX = Utility::MMToPixelWithScale(sender.rightButtomX, scale);
			float annotRightButtomY = Utility::MMToPixelWithScale(sender.rightButtomY, scale);
			
			// cut annotation for facing mode.
			if (pageView.isFacingPage == YES)
			{
				// left
				/*
				 if (annotLeftTopX < 0.0)
				 {
				 annotLeftTopX = -kFacePageEdgeWidth;
				 }
				 */
				
				// top
				/*
				 if (annotLeftTopY < 0.0)
				 {
				 annotLeftTopY = -kFacePageEdgeWidth;
				 }
				 */
				
				// right
				float pageRightEdge = 0.0;
				
				if (isLeftPage == YES)
				{
					pageRightEdge = pageView.page.m_PageInfoA.m_SrcRect.size.width;
				}
				else
				{
					pageRightEdge = pageView.page.m_PageInfoB.m_SrcRect.size.width;
				}
				
				if (annotRightButtomX > pageRightEdge)
				{
					//	annotRightButtomX = pageRightEdge + kFacePageEdgeWidth;
					annotRightButtomX = pageRightEdge;
				}
				
				// buttom
				float pageButtomEdge = 0.0;
				
				if (isLeftPage == YES)
				{
					pageButtomEdge = pageView.page.m_PageInfoA.m_SrcRect.size.height;
				}
				else
				{
					pageButtomEdge = pageView.page.m_PageInfoB.m_SrcRect.size.height;
				}
				
				if (annotRightButtomY > pageButtomEdge)
				{
					//	annotRightButtomY = pageButtomEdge + kFacePageEdgeWidth;
					annotRightButtomY = pageButtomEdge;
				}
			}
			
			CGPoint srcOrigin = CGPointZero;
			
			if (pageView.isFacingPage == NO)
			{
				srcOrigin = pageView.page.m_PageInfoA.m_SrcRect.origin;
			}
			else
			{
				if (isLeftPage == YES)
				{
					srcOrigin = pageView.page.m_PageInfoA.m_SrcRect.origin;
				}
				else
				{
					srcOrigin = pageView.page.m_PageInfoB.m_SrcRect.origin;
				}
			}
			
			float originX = srcOrigin.x + annotLeftTopX;
			float originY = srcOrigin.y + annotLeftTopY;
			
			float width = annotRightButtomX - annotLeftTopX;
			float height = annotRightButtomY - annotLeftTopY;
			
			CGRect annotationRect = CGRectMake(originX, originY, width, height);
			
			// 3.2 zoom page view for annotation jump.
			[pageViewMgr zoomPageViewForAnnotationJump:pageView
									withAnnotationRect:annotationRect
							  withAnnotationInLeftPage:isLeftPage];
		}
		
		showAnnotationList = NO;
		[self performSelector:@selector(hideAllToolbarItems:) 
				   withObject:[NSNumber numberWithBool:YES] 
				   afterDelay:0];
		
		// AR NO.17557 の対応 end
		
		// AR NO.17613 の対応 start
		sliderLabel.userInteractionEnabled = YES;
		// AR NO.17613 の対応 end
	}
}

// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
- (void)didSelectXdwDocInTable:(int)xdwPageIndex
{
	BOOL isLeftPage = YES;
	
	// 1. get page index.
	int pageIndex = 0;
	
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		pageIndex = xdwPageIndex;
	}
	else if (pageViewMgr.facingMode == MODE_FACE_NO)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageIndex = 0;
			isLeftPage = YES;
		} 
		else
		{
			pageIndex = xdwPageIndex / 2;
			
			// set left page flag.
			if (pageViewMgr.fontOrient == YES)
			{
				if (xdwPageIndex % 2 == 0)
				{
					isLeftPage = YES;
				}
				else
				{
					isLeftPage = NO;
				}
			}
			else
			{
				if (xdwPageIndex % 2 == 0)
				{
					isLeftPage = NO;
				}
				else
				{
					isLeftPage = YES;
				}
			}
		}
	}
	else if (pageViewMgr.facingMode == MODE_FACE_YES)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageIndex = 0;
			isLeftPage = YES;
		} 
		else
		{
			if (xdwPageIndex == 0)
			{
				pageIndex = xdwPageIndex;
			}
			else
			{
				pageIndex = xdwPageIndex / 2 + xdwPageIndex % 2;
				
				// set left page flag.
				if (pageViewMgr.fontOrient == YES)
				{
					if (xdwPageIndex % 2 == 1)
					{
						isLeftPage = YES;
					}
					else
					{
						isLeftPage = NO;
					}
				}
				else
				{
					if (xdwPageIndex == pageViewMgr.pageTotalCount - 1) 
					{
						isLeftPage = YES;
					} 
					else 
					{
						if (xdwPageIndex % 2 == 1)
						{
							isLeftPage = NO;
						}
						else
						{
							isLeftPage = YES;
						}
					}
				}
			}
		}
		
		// lixin 20110711 start
		// AR NO.17899 の対応
		/*    
		 if ([self UIDeviceIsPortrait] == YES)
		 {
		 pageIndex = xdwPageIndex;
		 }
		 }
		 */
        
	}	
    
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageIndex = xdwPageIndex;
	}
	// lixin 20110711 end
	
	// 2. move page to target page.
	pageViewPos = pageIndex;
	
	if (pageViewMgr.fontOrient == NO)
	{
		pageViewPos = [pageViewMgr getPageViewCount] - 1 - pageIndex;
	}
	
	[self actionMovePageWithPosition:pageViewPos 
					withMovePageMode:MODE_PAGE_NUMBER];
	[self updatePageNumberLabel:pageViewPos];	
	
	showAnnotationList = NO;
	showXdwDocList = NO;
	[self performSelector:@selector(hideAllToolbarItems:) 
			   withObject:[NSNumber numberWithBool:YES] 
			   afterDelay:0];
	
	sliderLabel.userInteractionEnabled = YES;
	
}
// 3.6 バインダ文書対応 の対応 end


#pragma mark -
#pragma mark toolbar item(edit button).
- (void) actionOnTouchEditButton
{
	// tongtx 20120206 start
	// 有償化アナウンス機能の対応
	if ([self showPaymentNotice] == YES)
	 {
		return;
	 }
	// tongtx 20120206 end
	 
	// xuxinjun 2012.03.23 start
	// パーミッションの対応.
	if ([self hasMakePayment] == NO)
	{
		UIAlertView *alertView_ = [[UIAlertView alloc] initWithTitle:nil 
															 message:NSLocalizedString(@"MSG_PAYM_ALERT_LIMIT_MESSAGE", nil) 
															delegate:nil 
												   cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
												   otherButtonTitles:nil];
		[alertView_ show];
		[alertView_ release];
		
		return;
	}
	// xuxinjun 2012.03.23 end
    
	[self cancelShowScreen];
	[self removeToolbarPopView];
	
	if ([pageViewMgr isTempFileEditing] == NO)
	{
        [pageViewMgr copyEditFileToTempDirectory];
        [pageViewMgr reloadXDWDocument:filePath];
		
		if (xdwDocListViewController != nil)
		{
			[xdwDocListViewController reloadDataWithPageViewManager:pageViewMgr];
		}
        
        tmpEditFilePath = [[NSString stringWithFormat:@"%@", filePath]retain];
	}
	else
	{
        [pageViewMgr reloadXDWDocument:filePath];
    }
	
	// lixin 2011/09/28 start
	// NS-AR1019 の対応
	[pageViewMgr setAnnotationDisplay:YES];
	// lixin 2011/09/28 end
	showAnnotationList = NO;
	
	if (showChooseEditPageIndexView == NO)
	{
		showChooseEditPageIndexView = YES;
	}
	else
	{
		showChooseEditPageIndexView = NO;
	}
	
	if (pageViewMgr.facingMode != MODE_REGULAR )
	{
		// get active DWScrollView
		DWScrollView* dwScrollView = [self getActivePageView];
		if (dwScrollView == nil) return;
		
		// get active DWPageView
		DWPageView* pageView = dwScrollView.page;
		if (pageView == nil) return;
		
		// if showing double page, choose one
		if (pageView.m_PageInfoB.m_PageNum != -1)
		{
			if (Utility::UIDeviceIsiPad())
			{
				if ([self.toolbarItems count] > 0)
				{
					UIBarButtonItem* editBarButtonItem = [self.toolbarItems objectAtIndex:0];
					if (editBarButtonItem != nil)
					{
						[editFacingPageViewPopController presentPopoverFromBarButtonItem:editBarButtonItem 
                                                                permittedArrowDirections:UIPopoverArrowDirectionDown 
                                                                                animated:YES];
					}
				}
			}
			else
			{
				UIActionSheet *sheet = [[UIActionSheet alloc] initWithTitle:nil
                                                                   delegate:self 
                                                          cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil) 
                                                     destructiveButtonTitle:nil
                                                          otherButtonTitles:NSLocalizedString(@"TOOLBAR_BUTTON_LEFTPAGE", nil),
                                        NSLocalizedString(@"TOOLBAR_BUTTON_RIGHTPAGE", nil),
                                        (char*)nil];
				sheet.actionSheetStyle = UIActionSheetStyleAutomatic;
				
				// tongtx 20110916 start
				// NS-AR024 の対応
				self.displayActionSheet = sheet;
				// tongtx 20110916 end
				
				sheet.tag = TAG_ACTIONSHEET_CHOOSEEDITPAGE;
				[sheet showInView:self.view];
				[sheet release];
			}
		}
		else
		{
			int pageIndex = [self getPageNumberWithPageViewPosition:pageViewPos] - 1;
			[self pushEditControllerWithPageIndex:pageIndex];
		}
	}
	else
	{
		[self pushEditControllerWithPageIndex:pageViewMgr.pageIndex];
	}
}

// tongtx 20120206 start
// MTA連動機能の対応
- (BOOL) showPaymentNotice
{
    NSString *defVersion = [[NSUserDefaults standardUserDefaults] valueForKey:@"APP_VERSION_EDIT"];
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleVersion"];
    
    if (defVersion == nil || [defVersion compare:appVersion] != NSOrderedSame) 
    {
        const unichar first_char  = [appVersion characterAtIndex:0];
        const unichar second_char = [appVersion characterAtIndex:2];
        if (first_char - '0' == 2 && second_char - '0' > 0)
        {
            NSString *message_ = NSLocalizedString(@"MSG_EDIT_PAYMENT_NOTICE", nil);
            UIAlertView *alertView_ = [[UIAlertView alloc] initWithTitle:nil 
                                                                 message:message_ 
                                                                delegate:self 
                                                       cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
                                                       otherButtonTitles:nil];
            alertView_.tag = TAG_PAYMENT_NOTICE_ALERT;
            [alertView_ show];
            [alertView_ release];
            
            [[NSUserDefaults standardUserDefaults] setValue:appVersion forKey:@"APP_VERSION_EDIT"];
            
            return YES;
        }
        
        [[NSUserDefaults standardUserDefaults] setValue:appVersion forKey:@"APP_VERSION_EDIT"];
    }
    
    return NO;
}
// tongtx 20120206 end

- (void) editPageViewWithButtonIndex:(int)buttonIndex
{
	// get page index to edit
	int pageIndex = pageViewMgr.pageIndex;
	
	DWScrollView* pageView = [self getActivePageView];
	if (pageView == nil) return;
	
	if (pageView.isFacingPage == YES)
	{
		if (buttonIndex == 0)
		{
			if (pageViewMgr.fontOrient == YES)
			{
				pageIndex = [self getPageNumberWithPageViewPosition:pageViewPos] - 1;
			}
			else
			{
				pageIndex = [self getPageNumberWithPageViewPosition:pageViewPos];
			}
		}
		else
		{
			if (pageViewMgr.fontOrient == YES)
			{
				pageIndex = [self getPageNumberWithPageViewPosition:pageViewPos];
			}
			else
			{
				pageIndex = [self getPageNumberWithPageViewPosition:pageViewPos] - 1;
			}
            
		}
	}
	
	[self pushEditControllerWithPageIndex:pageIndex];
}

// lixin 2011/09/28 start
// NS-AR1019 の対応
- (void) resetAnnnotationButtonStatus
{
	if (annoButtonItem.enabled == YES)
	{
		annoButtonItem.image = [UIImage imageNamed:[self getAnnotationOnOfIcon:pageViewMgr.showAnnotation]];
	}
}
//  lixin 2011/09/28 end

- (void) didChoosePageToEditWithButtonIndex:(int)index
{
	[self removeToolbarPopView];
	[self editPageViewWithButtonIndex:index];
}

// lixin 20110830 DW_iPhoneViewer_20の追加 start
- (void) pushEditControllerWithPageIndex:(int)pageIndex
{
    DWScrollView* pageView = [self getActivePageView];
    long scale = pageView.baseScale * pageView.zoomScale;
    CGPoint offset = pageView.contentOffset;
	
	// AR19008
	// 2012.02.20 M.Chikyu start.
	/*
	 DocumentEditController* controller = 
	 [[DocumentEditController alloc] initWithPageViewManager:pageViewMgr 
	 withPageIndex:pageIndex
	 withPageScale:scale
	 withPageOffset:offset];
	 */
	DocumentEditController* controller = 
	[[DocumentEditController alloc] initWithPageViewManager:pageViewMgr 
											  withPageIndex:pageIndex
                                              withPageScale:scale
											 withPageOffset:offset
											withOrientation:self.interfaceOrientation];
	// 2012.02.20 M.Chikyu end.
	
	if (controller != nil)
	{
		UINavigationController* navigation = [[UINavigationController alloc] initWithRootViewController:controller];
		navigation.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
		//	navigation.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
		[self.navigationController presentModalViewController:navigation animated:YES];
		
		[navigation release];
		[controller release];
	}
}
// lixin 20110830 end


#pragma mark -
#pragma mark action for finish editing.
// lixin 2011/09/19 start 
// NS-AR1006 の対応
- (void) resetLeftBarItem
{
	UIButton* leftButton = (UIButton*)self.navigationItem.leftBarButtonItem.customView;
	
	if (leftButton != nil)
	{
		if ([self isTempFileUpdated] == YES)
		{
			// lixin 2011/09/28 start 
			// NS-AR1006 の対応
			//[leftButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
			[leftButton setTitleColor:[UIColor colorWithRed:106.0/255.0 green:146.0/255.0 blue:232.0/255.0
													  alpha:1] 
							 forState:UIControlStateNormal];
			// lixin 2011/09/28 end
		}
		else
		{
			[leftButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
		}
	}
}
// lixin 2011/09/19 end

- (void) reloadAnnotationList
{
	[annotationListViewController reloadLinkAnnotationList];
	[annotationListViewController.tableView reloadData];
	
	// reload annotation button item state
	if (pageViewMgr.showAnnotation == YES && 
        [self getAnnotationCountInDocument] > 0)
	{
        annoListEnabled = YES;
    }
	else
	{
        annoListEnabled = NO;
    }
	
	if (pageViewMgr.isBinderDoc == NO)
	{
		// xujj 2012.04.18 start
		// 検索機能の追加
		//self.navigationItem.rightBarButtonItem.enabled = annoListEnabled;
		if (self.navigationItem.rightBarButtonItem.customView != nil)
		{
			UISegmentedControl* segmentCtrl = (UISegmentedControl*)self.navigationItem.rightBarButtonItem.customView;
			
			if (segmentCtrl.numberOfSegments > 0)
			{
				[segmentCtrl setEnabled:annoListEnabled forSegmentAtIndex:0];
			}
		}
		// xujj 2012.04.18 end
	}
	else
	{
		if (self.navigationItem.rightBarButtonItem.customView != nil)
		{
			UISegmentedControl* segmentCtrl = (UISegmentedControl*)self.navigationItem.rightBarButtonItem.customView;
			
			if (segmentCtrl.numberOfSegments > 0)
			{
				[segmentCtrl setEnabled:annoListEnabled forSegmentAtIndex:0];
			}
		}
		
		// lixin 2011/09/23 start 
		// NS-AR1017 の対応
		if (xdwDocListViewController != nil)
		{
			[xdwDocListViewController reloadDataWithPageViewManager:pageViewMgr];
		}
		// lixin 2011/09/23 end
	}
}

- (BOOL) isTempFileUpdated
{
	// lixin 2011/09/29 start 
	// NS-AR1006 の対応
	if (srcEditFilePath == nil)
	{
		return NO;
	}
	if (tmpEditFilePath == nil)
	{
		return NO;
	}
	
	NSFileManager* fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:tmpEditFilePath] == NO)
	{
		return NO;
	}
	
	// lixin 2011/09/29 end
	return ([documentSettingsMgr compareDataWithSrcPath:srcEditFilePath 
                                            withDstPath:tmpEditFilePath] == NO);
}
// liuqw 20110801 end

- (void) updateControlStatusForRotation
{
	isResetSubviewing = YES;
	[self actionDeviceRotationWithOrientation:self.interfaceOrientation];
	isResetSubviewing = NO;
}


#pragma mark -
#pragma mark toolbar item(facing button).
- (void) actionTouchFacingSettingsButton
{
	[self cancelShowScreen];
	
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	
	if (showFacingSettings == NO)
	{
		showFacingSettings = YES;
	}
	else
	{
		showFacingSettings = NO;
	}
	
	UIActionSheet *FacingSettingMenu = [[UIActionSheet alloc] initWithTitle:nil
																   delegate:self 
														  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil) 
													 destructiveButtonTitle:nil
														  otherButtonTitles:NSLocalizedString(@"TOOLBAR_BUTTON_SINGLEPAGE", nil),
										NSLocalizedString(@"TOOLBAR_BUTTON_FACING_WITHOUTHEADPAGE", nil), 
										NSLocalizedString(@"TOOLBAR_BUTTON_FACING_WITHHEADPAGE", nil),
										(char*)nil];
	FacingSettingMenu.actionSheetStyle = UIActionSheetStyleAutomatic;
	
	FacingSettingMenu.tag = 1;
	
	if (Utility::UIDeviceIsiPad())
	{
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
		// change by lixin 20110607 DW_iPhoneEnhance_12
		if (pageViewMgr.facingMode == MODE_REGULAR)
		{
			facingSettings.index = 0;
		}
		else if (pageViewMgr.facingMode == MODE_FACE_NO)
		{
			facingSettings.index = 1;
		}
		else
		{
			facingSettings.index = 2;
		}
		
		[facingSettings.tableView reloadData];
		
		// zhaijie 2011/09/21 begin
		// NS-AR025
		[facingPopMenu presentPopoverFromBarButtonItem:facingButtonItem
							  permittedArrowDirections:UIPopoverArrowDirectionDown 
											  animated:YES];
		
		// zhaijie 2011/09/21 end
	}
	else
	{
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
		// change by lixin 20110607 DW_iPhoneEnhance_12
		if (pageViewMgr.facingMode == MODE_REGULAR)
		{
			FacingSettingMenu.destructiveButtonIndex = 0;
		}
		else if (pageViewMgr.facingMode == MODE_FACE_NO)
		{
			FacingSettingMenu.destructiveButtonIndex = 1;
		}
		else
		{
			FacingSettingMenu.destructiveButtonIndex = 2;
		}
		
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 end
		
		// tongtx 20110916 start
		// NS-AR024 の対応
		self.displayActionSheet = FacingSettingMenu;
		// tongtx 20110916 end
		
		[FacingSettingMenu showInView:self.view];	
		[FacingSettingMenu release];
	}
}

- (void)didFacingSettingsChanged:(int)index
{
	isResetSubviewing = YES;
	[self actionFacingSettingsChanged:index];
	isResetSubviewing = NO;
}

- (void) actionFacingSettingsChanged:(int)index
{
	[self removeToolbarPopView];
	
	FacingMode fromMode = MODE_REGULAR;
	FacingMode toMode = MODE_REGULAR;
	
	if (index == 0 && pageViewMgr.facingMode != MODE_REGULAR)
	{
		fromMode = pageViewMgr.facingMode;
		pageViewMgr.facingMode = MODE_REGULAR;
		toMode = MODE_REGULAR;
	}
	else if (index == 1 && pageViewMgr.facingMode != MODE_FACE_NO)
	{
		fromMode = pageViewMgr.facingMode;
		pageViewMgr.facingMode = MODE_FACE_NO;
		toMode = MODE_FACE_NO;
	}
	else if (index == 2 && pageViewMgr.facingMode != MODE_FACE_YES)
	{
		fromMode = pageViewMgr.facingMode;
		pageViewMgr.facingMode = MODE_FACE_YES;
		toMode = MODE_FACE_YES;
	}
	else
	{
		return;
	}
	
	//*******************************************************************
	pageViewPos = [self convertPageViewPosition:pageViewPos 
								   withFromMode:fromMode 
									 withToMode:toMode];
	preViewPos = pageViewPos;
	//*******************************************************************
	
	// reset slider maxinumValue.
	// liuqw 20110323 start
	// スライダーバーの不具合修正
	//sliderLabel.maximumValue = [pageViewMgr getPageViewCount];
	sliderLabel.maximumValue = [pageViewMgr getPageViewCount] - 1;
	// liuqw 20110323 end
	
	[self removePageViewsFromScrollView];
	[self updateScrollViewContentSize];
	pageViewMgr.isPageFit = YES;
	pageViewMgr.pageStatus = PAGE_STATUS_FIT;
	
	if (pageViewMgr.pageStatus == PAGE_STATUS_FIT)
	{
		[self actionMovePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	else
	{
		[self actionMoveOnePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	
	facingButtonItem.image = [UIImage imageNamed:[self getFacingSettingsIcon]];
	
	
	
	if ([pageViewMgr getPageViewCount] == 1) 
	{
		[sliderLabel removeFromSuperview];
	} 
	else 
	{
		[self.view addSubview:sliderLabel];
	}
	
	[self performShowScreen];
}


#pragma mark -
#pragma mark toolbar item(font button).
- (void) actionTouchFontOrientationSettingsButton
{
	[self cancelShowScreen];
	
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	
	if (showFontSettings == NO)
	{
		showFontSettings = YES;
	}
	else
	{
		showFontSettings = NO;
	}
	
	UIActionSheet *FontSettingMenu = [[UIActionSheet alloc] initWithTitle:nil
																 delegate:self 
														cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil) 
												   destructiveButtonTitle:nil
														otherButtonTitles:NSLocalizedString(@"TOOLBAR_BUTTON_CROSSBOOKS", nil),
									  NSLocalizedString(@"TOOLBAR_BUTTON_VERTICALBOOKS", nil),
									  (char*)nil];
	FontSettingMenu.actionSheetStyle = UIActionSheetStyleAutomatic;
	
	FontSettingMenu.tag = 2;
	
	if (Utility::UIDeviceIsiPad())
	{
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
		// change by lixin 20110607 DW_iPhoneEnhance_12
		if (pageViewMgr.fontOrient == YES)
		{
			fontSettings.index = 0;
		}
		else
		{
			fontSettings.index = 1;
		}
		
		[fontSettings.tableView reloadData];
		
		// zhaijie 2011/09/21 begin
		// NS-AR025
		[fontPopMenu presentPopoverFromBarButtonItem:fontButtonItem
							permittedArrowDirections:UIPopoverArrowDirectionDown 
											animated:YES];
		
		// zhaijie 2011/09/21 end
	}
	else
	{
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
		// change by lixin 20110607 DW_iPhoneEnhance_12
		if (pageViewMgr.fontOrient == YES)
		{
			FontSettingMenu.destructiveButtonIndex = 0;
		}
		else
		{
			FontSettingMenu.destructiveButtonIndex = 1;
		}
		// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 end
		
		// tongtx 20110916 start
		// NS-AR024 の対応
		self.displayActionSheet = FontSettingMenu;
		// tongtx 20110916 end
		
		[FontSettingMenu showInView:self.view];
		[FontSettingMenu release];
	}
}

- (void)didFontSettingsChanged:(int)index
{
	isResetSubviewing = YES;
	[self actionFontSettingsChanged:index];
	isResetSubviewing = NO;
}

- (void) actionFontSettingsChanged:(int)index
{	
	[self removeToolbarPopView];
	
	if (index == 0 && pageViewMgr.fontOrient == NO)
	{
		pageViewMgr.fontOrient = YES;
	}
	else if (index == 1 && pageViewMgr.fontOrient == YES)
	{
		pageViewMgr.fontOrient = NO;
	}
	else
	{
		return;
	}
	
	// transform new position
	int pageCount = [pageViewMgr getPageViewCount];
	pageViewPos = pageCount - 1 - pageViewPos;
	preViewPos = pageViewPos;
	
	[self removePageViewsFromScrollView];
	
	if (pageViewMgr.pageStatus == PAGE_STATUS_FIT)
	{
		[self actionMovePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	else
	{
		[self actionMoveOnePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	
	fontButtonItem.image = [UIImage imageNamed:[self getFontSettingsIcon]];
	
	[self performShowScreen];
}


#pragma mark -
#pragma mark toolbar item(cooperation button).
// SendEmail の対応 start
- (void) actionTouchCooperationButton
{
	[self cancelShowScreen];
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	
	if (showCooperationSettings == NO)
	{
		showCooperationSettings = YES;
	}
	else
	{
		showCooperationSettings = NO;
	}
	
	UIActionSheet *cooperationSettingsMenu = [[UIActionSheet alloc] initWithTitle:nil
																		 delegate:self 
																cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil) 
														   destructiveButtonTitle:nil
																otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_SENDMAIL", nil),
											  NSLocalizedString(@"BUTTON_TITLE_OPENMODE", nil),
											  (char*)nil];
	cooperationSettingsMenu.actionSheetStyle = UIActionSheetStyleAutomatic;
	cooperationSettingsMenu.tag = COOPERATION_MENU_TAG;
	
	if (Utility::UIDeviceIsiPad())
	{
		//OnSite AR No21
		[cooperationPopMenu presentPopoverFromBarButtonItem:cooperationButtonItem
								   permittedArrowDirections:UIPopoverArrowDirectionDown 
												   animated:YES];
		// Memory Leak の対応 by yangjx 0627 start
		[cooperationSettingsMenu release];
		// Memory Leak の対応 by yangjx 0627 end
	}
	else
	{
		// tongtx 20110916 start
		// NS-AR024 の対応
		self.displayActionSheet = cooperationSettingsMenu;
		// tongtx 20110916 end
		
		[cooperationSettingsMenu showInView:self.view];
		[cooperationSettingsMenu release];
	}
}

- (void) actionTouchSendMailButton
{
	[self cancelShowScreen];
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	// Memory Leak の対応 by yangjx 0627 start
	//NSFileManager *fileManager = [[NSFileManager alloc] init];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	// Memory Leak の対応 by yangjx 0627 end
	NSDictionary *fileAttributes = [fileManager attributesOfItemAtPath:filePath error:NULL];
	
	long fileSize = [[fileAttributes valueForKey:NSFileSize] floatValue];
	if (fileSize / pow(1024, 2) > EMAIL_MAX_FILE_SIZE)
	{
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
															message:NSLocalizedString(@"MSG_WARING_FILESIZE_OUT",nil) 
														   delegate:nil
												  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK",nil) 
												  otherButtonTitles:nil];
		[alertView show];
		[alertView release];
	}
	else 
    {
		Class mailClass = NSClassFromString(@"MFMailComposeViewController");
		if (mailClass != nil && [MFMailComposeViewController canSendMail]) 
		{
			// lixin 20110705 start
			// AR NO.17893 の対応 
			//NSString* mailFileName = [self.title retain];
			NSString* mailFileName = [fileName copy];
			// lixin 20110705 end
            
			NSString* mailFilePath = [filePath retain]; 
			MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
			picker.mailComposeDelegate = self;
			// tongtx 20110627 start
			// AR17880
			//NSString *mimeType = Utility::getAttachmentMIMEType([mailFileName pathExtension]);
			NSString *mimeType = Utility::getAttachmentMIMEType(mailFilePath);
			// tongtx 20110627 end
			NSData *attachmentData = [NSData dataWithContentsOfFile:mailFilePath];
			
			if (mimeType != nil && [attachmentData length] > 0)
			{
				[picker addAttachmentData:attachmentData 
								 mimeType:mimeType 
								 fileName:mailFileName];
				[self presentModalViewController:picker animated:YES];
			}
			
			[mailFilePath release];
			[mailFileName release];
			[picker release];
		}
	}
}

- (UIDocumentInteractionController*)docControllerForFile:(NSURL*)fileURL
{
	UIDocumentInteractionController *docController
	= [UIDocumentInteractionController interactionControllerWithURL:fileURL];
	
	docController.delegate = self;
	
	return docController;
}

- (void) actionTouchOpenModeButton
{
	[self cancelShowScreen];
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	
	if (docInteractionController != nil)
	{
		[docInteractionController release];
		docInteractionController = nil;
	}
	
	NSURL *fileURL = [NSURL fileURLWithPath:filePath];
	docInteractionController = [[self docControllerForFile:fileURL] retain];
	
	//modify Toolbar subMenu by sun.chl 101127
	if( Utility::UIDeviceIsiPad() )
	{
		//OnSite AR No21
		CGRect MenuDisplayPos;
		if ([self UIDeviceIsPortrait] == YES)
		{
			MenuDisplayPos = CGRectMake(-530, -12, self.view.frame.size.width, self.view.frame.size.height);
		}
		else
		{
			MenuDisplayPos = CGRectMake(-680, -12, self.view.frame.size.width, self.view.frame.size.height);
		}
		
        if ([docInteractionController presentOpenInMenuFromBarButtonItem:cooperationButtonItem 
                                                                animated:YES]== NO)
		{
			return ;
		}
	}
	else
	{
		if ([docInteractionController presentOpenInMenuFromRect:self.view.frame 
														 inView:self.view animated:YES] == NO)
		{
			return ;
		}	
	}
	
}

- (void)didClickedCooperationMenuButtonIndex:(int)index
{
	if (index == 0) 
	{
		[self actionTouchSendMailButton];
	} else 
	{
		[self actionTouchOpenModeButton];
	}
}
// SendEmail の対応 end

// Dismisses the email composition interface when users tap Cancel or Send. 
// Proceeds to update the message field with the result of the operation.
- (void)mailComposeController:(MFMailComposeViewController *)controller 
		  didFinishWithResult:(MFMailComposeResult)result 
						error:(NSError *)error

{
	[self becomeFirstResponder];
	[self dismissModalViewControllerAnimated:YES];
}


#pragma mark -
#pragma mark toolbar item(annotation on/off button).
- (void) actionTouchAnnotationOnOffButton
{
	[self cancelShowScreen];
	[self removeToolbarPopView];
	
	showAnnotationList = NO;
	
    // liuqw 20110627 start
    // AR NO.17873 の対応
    
    if (pageViewMgr.showAnnotation == YES)
	{
		[pageViewMgr setAnnotationDisplay:NO];
	}
	else
	{
		[pageViewMgr setAnnotationDisplay:YES];	
	}
    
    [self setRightBarButtonItenEnabledWithIsBinderDoc:pageViewMgr.isBinderDoc];
    // liuqw 20110627 end
	
	
	isResetSubviewing = YES;
	
	[self removePageViewsFromScrollView];
	
	if (pageViewMgr.pageStatus == PAGE_STATUS_FIT)
	{
		[self actionMovePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	else
	{
		[self actionMoveOnePageWithPosition:pageViewPos withMovePageMode:MODE_PAGE_OTHER];
	}
	
	isResetSubviewing = NO;
	
	annoButtonItem.image = [UIImage imageNamed:[self getAnnotationOnOfIcon:pageViewMgr.showAnnotation]];
	
	[self performShowScreen];
}


#pragma mark -
#pragma mark toolbar item(zoom settings button).
// 「拡大率指定ボタンの追加」の対応 start
- (void) actionTouchZoomSettingsButton
{
	// yangjx 2011/09/15 start
    // NS-AR026 の対応
    [self cancelShowScreen];
	[self removeToolbarPopView];
    // yangjx 2011/09/15 end
	
    if (specifyScaleModeIndex == 0)
	{
        [self showZoomScaleInputView];
    }
	else
	{
		DWScrollView* pageView = [self getActivePageView];
		if (pageView == nil)
		{
			return;
		}
        
        int scale = specifyScaleValue;
		
        if (scale > pageView.maxScale)
		{
            scale = pageView.maxScale;
        }
		
		if (scale < pageView.minScale)
		{
            scale = pageView.minScale;
        }
        
        [self zoomPageViewToScale:scale];
    }
}

- (void) showZoomScaleInputView
{
    // 1. init alert view.
    DWScrollView* pageView = [self getActivePageView];
    if (pageView == nil)
	{
        return;
    }
    
    if (alertInputScale == nil)
	{
        int minScale = pageView.minScale;
        int maxScale = pageView.maxScale;
        
        NSString* tilte = [NSString stringWithFormat:NSLocalizedString(@"TITLE_ALERT_ZOOMSCALE_INPUT", nil), minScale, maxScale];
        self.alertInputScale = [[UIAlertView alloc] initWithTitle:tilte
                                                          message:@"             "
                                                         delegate:self
                                                cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), 
                                (char *)nil];
        alertInputScale.tag = TAG_INPUT_SCALE_ALERT;
        
        // 2.1 init field text view.
        self.fieldInputScale = [[UITextField alloc] init];
        fieldInputScale.clearButtonMode = UITextFieldViewModeWhileEditing;
        fieldInputScale.autocorrectionType = UITextAutocorrectionTypeNo;
        fieldInputScale.borderStyle = UITextBorderStyleRoundedRect;
        fieldInputScale.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
        fieldInputScale.font = [UIFont systemFontOfSize:22.0];
        fieldInputScale.adjustsFontSizeToFitWidth = YES;
        fieldInputScale.returnKeyType = UIReturnKeyDone;
        fieldInputScale.minimumFontSize = 2.0;
        fieldInputScale.tag = TAG_INPUT_SCALE_FIELD;
        fieldInputScale.delegate = self;
        
        // liuqw 2011/07/13 start
        // AR NO.17925 の対応
        pageViewMgr.pageScale = pageView.baseScale * pageView.zoomScale;
        // liuqw 2011/07/13 end
        
        // tongtx 2011/09/14 start
        // NS-AR010 の対応
        if (pageViewMgr.pageScale < pageView.minScale)
		{
            pageViewMgr.pageScale = pageView.minScale;
        }
        // tongtx 2011/09/14 end
        
        fieldInputScale.text = [NSString stringWithFormat:@"%d", pageViewMgr.pageScale];
        [alertInputScale addSubview:fieldInputScale];
        alertInputScale.delegate = self;
        [alertInputScale show];
        
        // 2.2 init unit
        self.labelScalePercent = [[UILabel alloc]init];
        labelScalePercent.backgroundColor = [UIColor clearColor];
        labelScalePercent.textColor = [UIColor whiteColor];
        labelScalePercent.text = @"%";
        [alertInputScale addSubview:labelScalePercent];
        
    }
	else
	{
        int minScale = pageView.minScale;
        int maxScale = pageView.maxScale;
        NSString* tilte = [NSString stringWithFormat:NSLocalizedString(@"TITLE_ALERT_ZOOMSCALE_INPUT", nil), minScale, maxScale];
        alertInputScale.title = tilte;
        
        // liuqw 2011/07/13 start
        // AR NO.17925 の対応
        pageViewMgr.pageScale = pageView.baseScale * pageView.zoomScale;
        // liuqw 2011/07/13 end
        
        // tongtx 2011/09/14 start
        // NS-AR010 の対応
        if (pageViewMgr.pageScale < pageView.minScale)
		{
            pageViewMgr.pageScale = pageView.minScale;
        }
        // tongtx 2011/09/14 end
        
        fieldInputScale.text = [NSString stringWithFormat:@"%d", pageViewMgr.pageScale];
        [alertInputScale show];
    }
	
    [self setInputScaleFieldViewPosition];
	
    [fieldInputScale becomeFirstResponder];
}

- (void) updateAlertInputScaleTitle
{
    DWScrollView* pageView = [self getActivePageView];
	
	if (pageView == nil)
	{
        return;
    }
    
    int minScale = pageView.minScale;
    int maxScale = pageView.maxScale;
    NSString* tilte = [NSString stringWithFormat:NSLocalizedString(@"TITLE_ALERT_ZOOMSCALE_INPUT", nil), minScale, maxScale];
    alertInputScale.title = tilte;
    fieldInputScale.text = [NSString stringWithFormat:@"%d", pageViewMgr.pageScale];    
}

- (void) setInputScaleFieldViewPosition
{
    UILabel* labelTitle =  ((UILabel*)[[alertInputScale subviews]objectAtIndex:1]);
	
    if (labelTitle != nil)
	{
        float originX = 45;
        float originY = labelTitle.frame.origin.y + labelTitle.frame.size.height;   
        float width = 170;
        float height = 30;
        float offset = 3;
        float percentWidth = 30;
        
        if (Utility::UIDeviceIsiPad() == NO)
		{
            if ([self UIDeviceIsPortrait] == YES)
			{
                height = 30;
                offset = 4;
                percentWidth = 30;
            }
			else
			{
                height = 27;
                offset = 2;
                percentWidth = 27;
            }
        }
		else
		{
            if ([self UIDeviceIsPortrait] == YES)
			{
                height = 30;
                offset = 4;
                percentWidth = 30;
            }
			else
			{
                height = 27;
                offset = 4;
                percentWidth = 27;
            }
        }
        
        fieldInputScale.frame = CGRectMake(originX, originY + offset, width, height);
        labelScalePercent.frame = CGRectMake(originX + width + 6, originY + offset, percentWidth, percentWidth);
    }
}

- (void) setInputScaleFieldViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    if (Utility::UIDeviceIsiPad() == NO)
	{
        if (toInterfaceOrientation != pageViewMgr.interfaceOrientation)
		{
            float originX, originY, width, height;
			
            if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation))
			{
                originX = fieldInputScale.frame.origin.x;
                originY = fieldInputScale.frame.origin.y - 8;    
                width = 170;
                height = 27;
            }
			else
			{
                originX = fieldInputScale.frame.origin.x;
                originY = fieldInputScale.frame.origin.y + 8;    
                width = 170;
                height = 30;
            }
			
            fieldInputScale.frame = CGRectMake(originX, originY, width, height);
            labelScalePercent.frame = CGRectMake(originX + width + 6, originY, height, height);
        }
    }
	else
	{
        float originX, originY, width, height;
		
        if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation))
		{
            originX = fieldInputScale.frame.origin.x;
            originY = fieldInputScale.frame.origin.y - 8;
            width = 170;
            height = 27;
        }
		else
		{
            originX = fieldInputScale.frame.origin.x;
            originY = fieldInputScale.frame.origin.y + 8;
            width = 170;
            height = 30;
        }
		
        fieldInputScale.frame = CGRectMake(originX, originY, width, height);
        labelScalePercent.frame = CGRectMake(originX + width + 6, originY, height, height);
    }
}

- (void) inputZoomScaleWithAlertView:(UIAlertView*)alertView
{
    if (alertView != nil)
	{
        UITextField* fieldInput = (UITextField*)[alertView viewWithTag:TAG_INPUT_SCALE_FIELD];
        if (fieldInput == nil)
		{
            return;
		}
        
        NSString *stringValue = [fieldInput text];
        int inputValue = 0;
        NSScanner *scanner = [NSScanner scannerWithString:stringValue];
		
        BOOL isInt = [scanner scanInt:&inputValue]&&[scanner isAtEnd];
        if (isInt == NO)
        {
            NSString* errorMessage = NSLocalizedString(@"MSG_ERROR_INPUT_NO_NUMBER", nil);
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
                                                            message:errorMessage 
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
                                                  otherButtonTitles:nil];
            alert.tag = TAG_INPUT_SCALE_ERROR;
            [alert show];
            [alert release];
            return;
        }
        
        int scale = inputValue;
        
        DWScrollView* pageView = [self getActivePageView];
        if (pageView == nil)
		{
            return;
        }
        
        int minScale = pageView.minScale;
        int maxScale = pageView.maxScale;
        
        if (scale < minScale || scale > maxScale)
        {
            NSString* errorMessage = NSLocalizedString(@"MSG_ERROR_INPUT_OUT_RANGE", nil);
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
                                                            message:errorMessage 
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
                                                  otherButtonTitles:nil];
            alert.tag = TAG_INPUT_SCALE_ERROR;
            [alert show];
            [alert release];
        }
        else
        {
            [self zoomPageViewToScale:scale];
        }
    }
}

- (void) zoomPageViewToScale:(int)scale
{
    DWScrollView* pageView = [self getActivePageView];
    if (pageView != nil)
	{
        // liuqw 20110627 start
        // AR NO.17875 の対応
        
        //CGPoint point = pageView.contentOffset;
        
        CGPoint offset = pageView.contentOffset;
        CGPoint origin = [pageViewMgr getPageCurrentOriginWithPageView:pageView];
		
        CGSize screenSize = [pageViewMgr getScreenRect].size;
		
		//	float backgroundWidth = screenSize.width + kPageEdgeWidth * 2;
		float backgroundWidth  = screenSize.width;
		float backgroundHeight = screenSize.height;
		
		float offsetX = fabs(origin.x) + offset.x + backgroundWidth / 2;
		float offsetY = offset.y + min(backgroundHeight / 2, pageView.page.frame.size.height / 2);
        
        float currentZoomScale = pageView.zoomScale;
        if (currentZoomScale < 1.0f)
		{
            currentZoomScale = 1.0f;
        }
        offsetX = offsetX / currentZoomScale;
        offsetY = offsetY / currentZoomScale;
        
        CGPoint point = CGPointMake(offsetX, offsetY);
        float zoomScale = (float)scale / (float)pageView.baseScale;
		
		if (zoomScale > pageView.zoomScale)
		{
			[pageViewMgr zoomPageView:pageView 
					   withTouchPoint:point 
						withZoomScale:zoomScale 
							withInOut:YES];
        }
        else if (zoomScale < pageView.zoomScale)
        {
            [pageViewMgr zoomPageView:pageView 
                       withTouchPoint:point 
                        withZoomScale:zoomScale
                            withInOut:YES];
        }
        
        // liuqw 20110627 end
    }
}
// 「拡大率指定ボタンの追加」の対応 end


#pragma mark -
#pragma mark page number label.
- (void) actionPageNumberLabelTouchDown
{
	// tongtx 2012.03.23 start
	// 選択機能の追加
	[self cancelSelectMode];
	// tongtx 2012.03.23 end
	
	[self cancelShowScreen];
	
	NSString* AlertTitle = NSLocalizedString(@"MSG_INPUT_PAGENUMBER", nil);
	
	if (pageAlert == nil)
	{
		pageAlert = [[UIAlertView alloc] initWithTitle:AlertTitle
											   message:@"             "
											  delegate:self
									 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), 
					 (char *)nil];
		pageAlert.tag = 0;
		
		pageAlertTextField = [[UITextField alloc] init];
		pageAlertTextField.clearButtonMode = UITextFieldViewModeWhileEditing;
		pageAlertTextField.autocorrectionType = UITextAutocorrectionTypeNo;
		pageAlertTextField.borderStyle = UITextBorderStyleRoundedRect;
		pageAlertTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;//AR No.77
		pageAlertTextField.font = [UIFont systemFontOfSize:22.0];
		pageAlertTextField.adjustsFontSizeToFitWidth = YES;
		pageAlertTextField.returnKeyType = UIReturnKeyDone;
		pageAlertTextField.minimumFontSize = 2.0;
		pageAlertTextField.tag = PAGE_NUMBER_TEXT_TAG;
		pageAlertTextField.delegate = self; //AR No17624 add
		[pageAlert addSubview:pageAlertTextField];
		pageAlert.delegate = self;
		[pageAlert show];
		CGRect frame;
		
		if ([self UIDeviceIsPortrait] == YES)
		{
			if ( Utility::UIDeviceIsiPad() )
			{
				frame = CGRectMake(45, (pageAlert.frame.size.height -115), 200, 30);
			}
			else
			{
				frame = CGRectMake(45, (pageAlert.frame.size.height -115), 200, 30);
			}
		}
		else
		{
			if ( Utility::UIDeviceIsiPad() )
			{
				frame = CGRectMake(45, (pageAlert.frame.size.height -100), 200, 27);
			}
			else
			{
				frame = CGRectMake(45, (pageAlert.frame.size.height -103), 200, 27);
			}
		}
		pageAlertTextField.frame = frame;
	}
	else
	{
		[pageAlert show];
		pageAlertTextField.text = nil;
	}
	
	//AR No.74
	[pageAlertTextField becomeFirstResponder];
}

- (void) updatePageNumberLabel:(int)position
{
	int pageNum = [self getPageNumberWithPageViewPosition:position];
	[pageNumberLabel setTitle:[NSString stringWithFormat:@"%d / %d", 
							   pageNum, pageViewMgr.pageTotalCount] 
					 forState:UIControlStateNormal];
	
	// add tool tip start
    
	[labelToolTip setText:[NSString stringWithFormat:@"%d / %d", 
						   pageNum, pageViewMgr.pageTotalCount]];
    
	// add tool tip end
    
	[self updatePageNumberBackGroundViewRect];
}

- (void) updatePageNumberBackGroundViewRect;
{
	[pageNumberLabel sizeToFit];
	pageNumberLabelRect.size.width = pageNumberLabel.frame.size.width + 6;
	pageNumberLabelRect.size.height = pageNumberLabel.frame.size.height;
	pageNumBackView.frame = pageNumberLabelRect;
}

- (int)  getPageNumberWithPageViewPosition:(int)pos
{
	int pageNum = 0;
	int position = 0;
	
	if (pageViewMgr.pageTotalCount == 0)
	{
		return 0;
	}
	
	// 1.set facing mode 
	FacingMode mode = pageViewMgr.facingMode;
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		mode = MODE_REGULAR;
	}
	
	if (pageViewMgr.fontOrient == YES)
	{
		position = pos;
	}
	else
	{
		position = [pageViewMgr getPageViewCount] - pos - 1;
	}
	
	// 2. set page number.
	if (mode == MODE_REGULAR)
	{
		pageNum = position + 1;
	}
	else
	{
		if (mode == MODE_FACE_NO)
		{
			pageNum = position * 2 + 1;
		}
		else
		{
			if (position == 0)
			{
				pageNum = 1;
			}
			else
			{
				pageNum = position * 2;
			}
		}
	}
	
	return pageNum;
}

- (void)hidePageNumberLable:(BOOL)hidden
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	if ((hideToolbar == NO) && (hidden != NO))
	{
		return;	
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	pageNumBackView.hidden = hidden;
	[self updatePageNumberBackGroundViewRect];
}


#pragma mark -
#pragma mark slider bar.
- (void) actionSliderLabelDragEnter
{
	[self cancelShowScreen];
	[self hidePageNumberLable:NO];
}

- (void) actionSliderLabelDragEnd
{
	[self performShowScreen];
}

- (void) actionSliderLabelValueChanging
{
	// liuqw 20110323 start
	// スライダーバーの不具合修正
	if (sliderLabel.currentMaximumTrackImage != sliderLabel.currentMinimumTrackImage) 
	{
		[sliderLabel setMinimumTrackImage:sliderLabel.currentMaximumTrackImage 
								 forState:UIControlStateNormal];
	}
	
	//position = sliderLabel.value;
	int position = 0;
	
	if (pageViewMgr.fontOrient == YES)
	{
		position = floor(sliderLabel.value);
	} 
	else 
	{
		position = ceil(sliderLabel.value);
	}
	// liuqw 20110323 end
	
	int pageCount = [pageViewMgr getPageViewCount];
	
	if (position > pageCount - 1)
	{
		position = pageCount - 1;
	}
	
	[self updatePageNumberLabel:position];
	
	// add tool tip start
	if ( Utility::UIDeviceIsiPad() )
	{
		[self moveToolTipViewWithSliderBar];
	}
	// add tool tip end
}

- (void) actionSliderLabelValueChanged
{
	// liuqw 20110323 start
	// スライダーバーの不具合修正
	//position = sliderLabel.value;
	int position = 0;
	
	if (pageViewMgr.fontOrient == YES)
	{
		position = floor(sliderLabel.value);
	}
	else
	{
		position = ceil(sliderLabel.value);
	}
	// liuqw 20110323 end
	
	int pageCount = [pageViewMgr getPageViewCount];
	
	if (position > pageCount - 1)
	{
		position = pageCount - 1;
	}
	
	// ページ移動仕様の変更の対応 start
	[self actionMovePageWithPosition:position 
					withMovePageMode:MODE_PAGE_SLIDER];
	
	// add tool tip start
	[self removeToolTipToSliderBar];
}

// liuqw 20110323 start
// スライダーバーの不具合修正
- (void) updateSliderLabel:(float)position
{
	sliderLabel.value = position;
	if (sliderLabel.currentMaximumTrackImage != sliderLabel.currentMinimumTrackImage) 
	{
		[sliderLabel setMinimumTrackImage:sliderLabel.currentMaximumTrackImage 
								 forState:UIControlStateNormal];
	}
}
// liuqw 20110323 end

// add tool tip start
- (void) initToolTipRect
{
	bgToolTip.hidden = YES;
    
    bgToolTip.frame = [self getToolTipViewPositon];
	labelToolTip.frame = CGRectMake(0,
                                    0, 
                                    bgToolTip.frame.size.width, 
                                    bgToolTip.frame.size.height);
}

- (void) addToolTipToSliderBar
{
	if (Utility::UIDeviceIsiPad())
    {
		[self initToolTipRect];
		[self.view addSubview:bgToolTip];
        [bgToolTip addSubview:labelToolTip];
	}
}

- (void) moveToolTipViewWithSliderBar
{
	bgToolTip.hidden = NO;
    [labelToolTip sizeToFit];
    
	float bgOriginX = [self getToolTipViewPositon].origin.x - bgToolTip.frame.size.width / 2;
    float bgOriginY = bgToolTip.frame.origin.y;
    float width = labelToolTip.frame.size.width + 6;
    float height = labelToolTip.frame.size.height;
	
	if (bgOriginX >= sliderLabel.frame.origin.x + sliderLabel.frame.size.width)
	{
        bgOriginX -= 35;
	}
    
    bgToolTip.frame = CGRectMake(bgOriginX, bgOriginY, width, height);
}

- (void) removeToolTipToSliderBar
{
    if (Utility::UIDeviceIsiPad())
    {
		bgToolTip.hidden = YES;
	}
}

- (CGRect) getToolTipViewPositon
{   
    CGRect rect = CGRectZero;
    
    float originX = 0.0;
	
	int count = [pageViewMgr getPageViewCount] - 1;
    if (count != 0)
	{
        float section = (float)sliderLabel.frame.size.width / (float)count;
        originX = (float)sliderLabel.frame.origin.x + 
		(sliderLabel.value * section) + 
		(sliderLabel.currentThumbImage.size.width / 2);
    }
	
    float originY = sliderLabelRect.origin.y - 40;
    
    CGRect screenFrame = [[UIScreen mainScreen] bounds];
	long screenW = screenFrame.size.width;
	long screenH = screenFrame.size.height;
    float width = screenW / 10;
    float height = screenH / 30;
    
    rect = CGRectMake(originX, originY, width, height);
    
    return rect;
}
// add tool tip end


#pragma mark -
#pragma mark navigation bar and tool bar.
- (void) removeToolbarPopView
{
	if ( Utility::UIDeviceIsiPad() )
	{
		[fontPopMenu dismissPopoverAnimated:YES];
		[facingPopMenu dismissPopoverAnimated:YES];
		
		// lixin 20110813 start
		// ページ編集機能の追加  DW_iPhoneViewer_20
		[editFacingPageViewPopController dismissPopoverAnimated:YES];
		// lixin 20110813 end
        
		// SendEmail の対応 start
		[cooperationPopMenu dismissPopoverAnimated:YES];
		// SendEmail の対応 end
		
		if (docInteractionController != nil)
		{
			[docInteractionController dismissMenuAnimated:YES];
		}
	}
	
	[annotationListView removeFromSuperview];
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	[xdwDocListView removeFromSuperview];
	// 3.6 バインダ文書対応 の対応 end
	
	//AR No.61
	sliderLabel.userInteractionEnabled = YES;
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	[self cancelSelectMode];
	// tongtx 2012.03.23 end
	
}

- (void) performShowScreen
{
	// lixin 2011/09/20 start 
	// NS-AR031 の対応
	/*
	 if ([UIApplication sharedApplication].statusBarHidden == NO)
	 {
	 [self performSelector:@selector(hideAllToolbarItems:) 
	 withObject:[NSNumber numberWithBool:YES] 
	 afterDelay:HIDE_TOOLBAR_DELAY];
	 }
	 */
	// lixin 2011/09/20 end
}

- (void) cancelShowScreen
{
	[NSObject cancelPreviousPerformRequestsWithTarget:self];
}

- (void) hideAllToolbarItems:(NSNumber*)status
{
	BOOL hidden = [status boolValue];
	hideToolbar = hidden;
	
	// lixin 20110815 start
	// ページ編集機能の追加  DW_iPhoneViewer_20
	if (self.navigationController.topViewController == nil)
	{
		return;
	}
	// lixin 20110815 end
    
	if ([self.navigationController.topViewController isKindOfClass:[DocumentViewController class]])
	{
		/*
		 [[UIApplication sharedApplication] setStatusBarHidden:hidden 
		 withAnimation:UIStatusBarAnimationNone];
		 */
		[self.navigationController setNavigationBarHidden:hidden animated:NO];
		[self.navigationController setToolbarHidden:hidden animated:NO];
		
		if (hidden == YES)
		{
			[self hidePageNumberLable:YES];
			[sliderLabel removeFromSuperview];
			[annotationListView removeFromSuperview];
			
			// 3.6 バインダ文書対応 の対応 start
			// change by lixin 20110608 DW_iPhoneEnhance_12
			[xdwDocListView removeFromSuperview];
			// 3.6 バインダ文書対応 の対応 end
			
			if ( Utility::UIDeviceIsiPad() )
			{
				[fontPopMenu dismissPopoverAnimated:YES];
				[facingPopMenu dismissPopoverAnimated:YES];
				
				// SendEmail の対応 start
				[cooperationPopMenu dismissPopoverAnimated:YES];
				// SendEmail の対応 end
				
				// zhaijie 2011/09/20 begin
				// NS-AR023
				[editFacingPageViewPopController dismissPopoverAnimated:YES];
				// zhaijie 2011/09/20 end
				
				if (docInteractionController != nil)
				{
					[docInteractionController dismissMenuAnimated:YES];
				}
			}
            
            // lixin 2011/09/20 start 
            // NS-AR031 の対応
            [self removeToolTipToSliderBar];
            // lixin 2011/09/20 end
		}
		else
		{
			[self initPageNumberlabelRect];
			[self hidePageNumberLable:NO];
			[self initViewControlsRect];
			
			if ([pageViewMgr getPageViewCount] > 1)
			{
				[self.view addSubview:sliderLabel];
                
				// add tool tip start
                [self initToolTipRect];
				// add tool tip end
			}
			
			if (showAnnotationList == YES)
			{
				[self.view addSubview:annotationListView];
			}
			
			// 3.6 バインダ文書対応 の対応 start
			// change by lixin 20110608 DW_iPhoneEnhance_12
			if (showXdwDocList == YES)
			{
				[self.view addSubview:xdwDocListView];
			}
			// 3.6 バインダ文書対応 の対応 end
		}
	}
}


#pragma mark -
#pragma mark action for move page.
- (void) actionMovePageWithPosition:(int)position 
				   withMovePageMode:(MOVE_PAGE_MODE)mode
{
	preViewPos = pageViewPos;
	pageViewPos = position;
	
	
	// 表示ページの取得
	DWScrollView* pageView = [self getActivePageView];
	
	// 表次ページが存在しなければ追加
	if (pageView == nil)
	{
		[self insertPageViewWithPosition:position];
		pageView = [self getActivePageView];
	}
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	[self restoreSearchTextGhostViewForMovePage:position];
	// xujj 2012.03.22 end
	
	// 表示ページをページフィットへ拡大
	[pageViewMgr zoomPageViewToPageFit:pageView];
	// 表示ページのオフセットを指定
	//	[pageView setContentOffset:pageView.initContentOffset];
	// 表示ページの表示を更新
	//	[pageViewMgr updatePageViewScaleToPageFit:pageView];
	// 表示ページの拡大率を取得
    pageViewMgr.pageScale = pageView.baseScale;
	
	
	// 前ページを取得
	DWScrollView* prePage = [self getPageViewWithPosition:(position - 1)];
	
	// 前ページが存在しなければ追加
	if (prePage == nil)
	{
		// 先頭ページなら何もしない
		if (position - 1 >= 0)
		{
			[self insertPageViewWithPosition:(position - 1)];
			prePage = [self getPageViewWithPosition:(position - 1)];
		}
	}
	
	
	// 前ページのオフセットを指定
	if (prePage != nil) 
	{
		[prePage setContentOffset:prePage.initContentOffset];
	}
	
	
	// 次ページを取得
	DWScrollView* nextPage = [self getPageViewWithPosition:(position + 1)];
	
	// 次ページが存在しなければ追加
	if (nextPage == nil)
	{
		// 最終ページなら何もしない
		if (position + 1 <= [pageViewMgr getPageViewCount] - 1)
		{
			[self insertPageViewWithPosition:(position + 1)];
			nextPage = [self getPageViewWithPosition:(position + 1)];
		}
	}
	
	
	// 次ページのオフセットを指定
	if (nextPage != nil) 
	{
		[nextPage setContentOffset:nextPage.initContentOffset];
	}
	
	
	// アクティブフラグをセット
	[pageViewMgr setPageViewActive:pageView];
	
	
	// ページ番号が指定されていない場合、ページ番号表示を更新
	if (mode != MODE_PAGE_NUMBER)
	{
		[self updatePageNumberLabel:position];
	}
	
	// スライダーでページ位置が指定されていない場合、スライダー表示を更新
	if (mode != MODE_PAGE_SLIDER)
	{
		[self updateSliderLabel:position];
	}
	
	// スクロールインジケータの表示を更新
	if (mode == MODE_PAGE_NUMBER ||
		mode == MODE_PAGE_SLIDER || 
		mode == MODE_PAGE_OTHER)
	{
		[self updateScrollIndicatorPos:position animated:NO];
	}
	
	// 前ページのページフィット処理
	if (prePage != nil)
	{
		[pageViewMgr zoomPageViewToPageFit:prePage];
		[bgScrollView bringSubviewToFront:prePage];
	}
	
	// 次ページのページフィット処理
	if (nextPage != nil)
	{
		[pageViewMgr zoomPageViewToPageFit:nextPage];
		[bgScrollView bringSubviewToFront:nextPage];
	}
	
    if (pageViewMgr.isBinderDoc == YES) 
    {
        self.title = [self getBinderTitleWithPageIndex:pageViewPos];
    }
}

- (void) actionMoveOnePageWithPosition:(int)position 
					  withMovePageMode:(MOVE_PAGE_MODE)mode
{
	preViewPos = pageViewPos;
	pageViewPos = position;
	
	// スクロールインジケータの表示を更新
	if (mode == MODE_PAGE_NUMBER ||
		mode == MODE_PAGE_SLIDER || 
		mode == MODE_PAGE_OTHER)
	{
		[self updateScrollIndicatorPos:position animated:NO];
	}
	
	// 表示ページの取得
	DWScrollView* activePage = [self getActivePageView];
	
	// 表示ページが存在しなければ追加
	if (activePage == nil)
	{
		[self insertPageViewWithPosition:position];
		activePage = [self getActivePageView];
	}
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	[self restoreSearchTextGhostViewForMovePage:position];
	// xujj 2012.03.22 end
	
	// 表示ページの表示を更新
	[pageViewMgr updatePageViewScaleInfo:activePage];
	
	// set page offset.
	// AR NO.17527 の対応 start
	if (pageViewMgr.pageStatus == PAGE_STATUS_ZOOM)
	{
		[self setPageContentOffset:[self getPageOffset]];
	}
	// AR NO.17527 の対応 end
	
	// 全ページのアクティブフラグをリセット
	NSArray *subviews = [bgScrollView subviews];
	for (DWScrollView *pageView in subviews)
	{
		pageView.isActivePage = NO;
	}
	
	
	// アクティブフラグをセット
	[pageViewMgr setPageViewActive:activePage];
	
	
	// ページ番号が指定されていない場合、ページ番号表示を更新
	if (mode != MODE_PAGE_NUMBER)
	{
		[self updatePageNumberLabel:position];
	}
	
	// スライダーでページ位置が指定されていない場合、スライダー表示を更新
	if (mode != MODE_PAGE_SLIDER)
	{
		[self updateSliderLabel:position];
	}
	
	if (pageViewMgr.isBinderDoc == YES) 
    {
        self.title = [self getBinderTitleWithPageIndex:pageViewPos];
    }
}

- (void) actionMoveToNextPage:(BOOL)toNext
{
	int position = pageViewPos;
	
	if (toNext == YES)
	{
		if (position >= [pageViewMgr getPageViewCount] - 1)
		{
			return;
		}
		
		position++;
	}
	else
	{
		if (position <= 0)
		{
			return;
		}
		
		position--;
	}
	
	[self updateScrollIndicatorPos:position animated:YES];
	
	[NSObject cancelPreviousPerformRequestsWithTarget:self];
	
	// xujj 2012.04.17 start
	// 検索機能の追加
	if (isSearchBarShowing == YES)
	{
		return;
	}
	// xujj 2012.04.17 end
	
	[self initPageNumberlabelRect];
	[self hidePageNumberLable:NO];
}

- (BOOL) touchInPageCenterArea:(CGPoint)point
{
	float frameWidth = self.view.frame.size.width;
	float minOriginX = frameWidth * 3 / 20;
	float maxOriginX = frameWidth - frameWidth * 3 / 20;
	
	if (point.x < minOriginX ||
		point.x > maxOriginX)
	{
		return NO;
	}
	
	return YES;
}

- (void) actionTouchPageEdge:(CGPoint)point
{
	float frameWidth = self.view.frame.size.width;
	float minOriginX = frameWidth * 3 / 20;
	float maxOriginX = frameWidth - frameWidth * 3 / 20;
	
	DWScrollView *pageView = [self getActivePageView];
	
	if (point.x < minOriginX)
	{
		if (pageView.contentOffset.x > 20 && pageViewMgr.isPageFit == NO)
		{
			CGPoint offset = CGPointMake(0, pageView.contentOffset.y);
			[pageView setContentOffset:offset animated:YES];
		}
		else
		{
			[self actionMoveToNextPage:NO];
		}
	}
	
	if (point.x > maxOriginX)
	{
		if (pageViewMgr.isPageFit == NO && 
			(pageView.contentSize.width - pageView.contentOffset.x > frameWidth + 20))
		{
			CGPoint offset = CGPointMake(pageView.contentSize.width - frameWidth, 
										 pageView.contentOffset.y);
			[pageView setContentOffset:offset animated:YES];
		}
		else
		{
			[self actionMoveToNextPage:YES];
		}
	}
}

- (void) updateScrollIndicatorPos:(int)position animated:(BOOL)animated
{
	CGFloat localX = bgScrollView.frame.size.width * position;
	[bgScrollView setContentOffset:CGPointMake(localX, 0) animated:animated];
}

// lixin 20110626 DW_iPhoneEnhance_12 start
// AR.17872 の対応 
- (NSString*) getBinderTitleWithPageIndex:(int)pageIndex
{
	NSString* name = @"";
	if (pageViewMgr.isBinderDoc == YES) 
	{
        // lixin 20110705 start
		// AR NO.17899 の対応 
		pageIndex = [self getPageNumberWithPageViewPosition:pageIndex] - 1;
        if (pageIndex < 0)
		{
            pageIndex = 0;
        }
		// lixin 20110705 end
        
		XdwFileInfo* xdwFileInfo = (XdwFileInfo*)pageViewMgr.handleDocument->GetFileInfo();
		if (xdwFileInfo->GetBinderCount() != 0)
        {
            int i = 0;
            int prePageCount = xdwFileInfo->GetPageCntOfBinderDoc(i);
            while (pageIndex > prePageCount - 1)
            {
                i++;
                
                // 20110701 M.Chikyu (AR17887,AR17889) start
				// ページ数0の内部文書対策
				
				// 配列のインデックスが配列サイズを超えないように確認
				if (i >= xdwFileInfo->GetBinderCount())
				{
					// 配列の最後の文書を表示文書とする
					i = xdwFileInfo->GetBinderCount() - 1 ;
					break;
				}
				
				// 20110701 M.Chikyu (AR17887,AR17889) end
                
                prePageCount += xdwFileInfo->GetPageCntOfBinderDoc(i);
            }
            
            if (i < xdwFileInfo->GetBinderCount())
            {
                name = [fileName stringByAppendingFormat:@"(%@)", 
						[NSString stringWithCString:xdwFileInfo->GetNameOfBinderDoc(i)
										   encoding:NSUTF8StringEncoding]];
                xdwDocListViewController.selectDocIndex = i;
				
				[xdwDocListViewController.tableView reloadData];
            }
        }
		// lixin 2011/09/05 start 
		// NS-AR001 の対応
		else
		{
			name = [NSString stringWithFormat:@"%@", fileName];
		}
		// lixin 2011/09/05 end
	}
	
	return name;
}
// lixin 20110626 DW_iPhoneEnhance_12 end

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void)shiftNextPage
{
	// 次ページを取得
	DWScrollView* nextPage = [self getPageViewWithPosition:(pageViewPos + 1)];
	
	[self shiftPage:nextPage position:(pageViewPos + 1)];
}

- (void)shiftPrePage
{
	// 前ページを取得
	DWScrollView* prePage = [self getPageViewWithPosition:(pageViewPos - 1)];
	
	[self shiftPage:prePage position:(pageViewPos - 1)];
}

- (void)shiftPage:(DWScrollView*)pageView position:(int)pos
{
	if (pageView == nil ||
		pos == pageViewPos ||
		pageView.isPreDraw == YES)
	{
		return;
	}
	
	CGRect frame = pageView.frame;
	pageView.afterFrame = frame;
	pageView.isPreDraw = YES;
	
	if (pos > pageViewPos)
	{
		frame.origin.x -= 1;
	}
	else
	{
		frame.origin.x += 1;
	}
	
	pageView.frame = frame;
}

// 2012.02.01(Ver2.1 New) M.Chikyu


#pragma mark -
#pragma mark action for zoom page.
- (void) actionDoubleTap:(UIGestureRecognizer *)gestureRecognizer 
{
	[self cancelShowScreen];
	DWScrollView* dwPage = [self getActivePageView]; 
	CGPoint touchPoint = [gestureRecognizer locationInView:dwPage.page];
	[self actionZoomInOutPageView:YES withTouchPoint:touchPoint];
	[self performShowScreen];
}

- (void) actionTwoFingerTap:(UIGestureRecognizer *)gestureRecognizer 
{
	[self cancelShowScreen];
	
	DWScrollView *pageView = [self getActivePageView];
	CGPoint touchPoint = [gestureRecognizer locationInView:pageView.page];
	[self actionZoomInOutPageView:NO withTouchPoint:touchPoint];
	
	[self performShowScreen];
}

- (void) actionZoomInOutPageView:(BOOL)zoomIn withTouchPoint:(CGPoint)point
{
	DWScrollView* dwPage = [self getActivePageView]; 
	
	if (zoomIn == YES)
	{
		[pageViewMgr zoomInPageView:dwPage withTouchPoint:point];
	}
	else
	{
		[pageViewMgr zoomOutPageView:dwPage withTouchPoint:point];
	}
}


#pragma mark -
#pragma mark action for single touch.
- (void) actionSingleTap:(UIGestureRecognizer *)gestureRecognizer 
{
	// tongtx 2012.03.23 start
	// 選択機能の追加
	if (isSelectGhostShowing == YES)
	{
		[self cancelSelectModeWithGesture:gestureRecognizer];
		return;
	}
	// tongtx 2012.03.23 end
	
    // 「リンクアノテーションジャンプ方法」変更の対応 start
    BOOL isTapped = [self isTappedInLinkAnnotation:gestureRecognizer];
    if (isTapped == NO)
	{
        [self actionOnTappedInPage:gestureRecognizer];
    }
    // 「リンクアノテーションジャンプ方法」変更の対応 end
}

// 「リンクアノテーションジャンプ方法」変更の対応 start
- (void) actionOnTappedInPage:(UIGestureRecognizer *)gestureRecognizer
{
    [self cleanLinkAnnotationShadow];
    
	if (showAnnotationList == YES ||
		showFacingSettings == YES ||
		showFontSettings == YES   ||
		showCooperationSettings == YES ||
        showXdwDocList == YES)
	{
		showAnnotationList = NO;
		showFacingSettings = NO;
		showFontSettings = NO;
		showCooperationSettings = NO;
        showXdwDocList = NO;
		[self removeToolbarPopView];
	}
	else
	{
		CGPoint point = [gestureRecognizer locationInView:self.view];
        
		if ([self touchInPageCenterArea:point] == YES)
		{
			// xujj 2012.03.22 start
			// 検索機能の追加
			if (isSearchBarShowing == YES) {
				return;
			}
			// xujj 2012.03.22 end
			
			[self cancelShowScreen];
            
			//	if ([UIApplication sharedApplication].statusBarHidden == NO)
			if (self.navigationController.navigationBarHidden == NO)
			{
				
				[self performSelector:@selector(hideAllToolbarItems:) 
						   withObject:[NSNumber numberWithBool:YES] 
						   afterDelay:0];
			}
			else
			{
				
				[self performSelector:@selector(hideAllToolbarItems:) 
						   withObject:[NSNumber numberWithBool:NO] 
						   afterDelay:0];
			}
		}
		else
		{
			[self actionTouchPageEdge:point];
		}
	}    
}


#pragma mark -
#pragma mark action for link annotation.
// 「リンクアノテーションジャンプ方法」変更の対応 start
- (BOOL) isTappedInLinkAnnotation:(UIGestureRecognizer *)gestureRecognizer
{
    BOOL isTapped = NO;
    
    // liuqw 2012/02/03 start
    // AR NO.17834の対応
    if (pageViewMgr.showAnnotation == NO) 
    {
        return isTapped;
    }
    // liuqw 2012/02/03 end
    
	DWScrollView* pageView = [self getActivePageView];
	if (pageView == nil)
	{
		return isTapped;
	}
	
	// 1. get touch point.
	CGPoint point = [gestureRecognizer locationInView:pageView.page];
	
	// 2. set left page flag.
	BOOL isLeftPage = YES;
    
	if (pageView.isFacingPage == YES)
	{
		float firstPageOriginX = pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		//	float firstPageWidth =  firstPageOriginX + pageView.page.m_PageInfoA.m_SrcRect.size.width + kFacePageEdgeWidth;
		float firstPageWidth =  firstPageOriginX + pageView.page.m_PageInfoA.m_SrcRect.size.width;
		
		if (point.x < firstPageWidth)
		{
			isLeftPage = YES;
		}
		else
		{
			isLeftPage = NO;
		}
	}
    
	// 3. find if touch in link annotation or not.
	BOOL bFind = NO;
	int index = 0;
	CGRect rect = CGRectNull;
	int count = [pageView.page getLinkAnnotationCountWithIsLeftPage:isLeftPage];
    
	for (int i = count - 1; i >= 0; --i)
	{
		index = [pageView.page getLinkAnnotationIndex:i withIsLeftPage:isLeftPage];
		rect = [self getLinkAnnotationRectWithAnnotationIndex:index
									 withAnnotationInLeftPage:isLeftPage];
		
		if (CGRectContainsPoint(rect, point))
		{
			bFind = YES;
			break;
		}
	}
	
	if (bFind == YES)
	{
        isTapped = YES;
        
        LinkAnnotationManager *linkAnnotMgr = [self getLinkAnnotManager:index];
        if (linkAnnotMgr != nil)
        {
            [self addShadowToLinkAnnotation:rect];
            [self showLinkAnnotationAlert:linkAnnotMgr];
        }
	}
    return isTapped;
}
// 「リンクアノテーションジャンプ方法」変更の対応 end

// AR NO.17516 の対応 start
- (CGRect) getLinkAnnotationRectWithAnnotationIndex:(int)index 
						   withAnnotationInLeftPage:(BOOL)inLeftPage
{
	DWScrollView *pageView = [self getActivePageView];
	
	if (pageView == nil)
	{
		return CGRectZero;
	}
	
	LinkAnnotInfoList *linkAnnotInfolist = [pageViewMgr getLinkAnnotationInfoList];
	LinkAnnotInfo* linkAnnotInfo = linkAnnotInfolist->GetLinkAnnotInfo(index);
	XdwRectangle xdwRect = linkAnnotInfo->GetRectangle();
	
	long scale = pageView.page.m_PageInfoA.m_PageFitScale;
	float annotLeftTopX = Utility::MMToPixelWithScale(xdwRect.LeftTopF.xF, scale);
	float annotLeftTopY = Utility::MMToPixelWithScale(xdwRect.LeftTopF.yF, scale);
	float annotRightButtomX = Utility::MMToPixelWithScale(xdwRect.RightBottomF.xF, scale);
	float annotRightButtomY = Utility::MMToPixelWithScale(xdwRect.RightBottomF.yF, scale);
	
	// cut annotation for facing mode.
	
	// left
	if (annotLeftTopX < 0.0)
	{
		annotLeftTopX = 0.0;
	}
	
	// top
	if (annotLeftTopY < 0.0)
	{
		annotLeftTopY = 0.0;
	}
	
	// right
	float pageRightEdge = 0.0;
	
	if (inLeftPage == YES)
	{
		pageRightEdge = pageView.page.m_PageInfoA.m_SrcRect.size.width;
	}
	else
	{
		pageRightEdge = pageView.page.m_PageInfoB.m_SrcRect.size.width;
	}
	
	if (annotRightButtomX > pageRightEdge)
	{
		annotRightButtomX = pageRightEdge;
	}
	
	// buttom
	float pageButtomEdge = 0.0;
	
	if (inLeftPage == YES)
	{
		pageButtomEdge = pageView.page.m_PageInfoA.m_SrcRect.size.height;
	}
	else
	{
		pageButtomEdge = pageView.page.m_PageInfoB.m_SrcRect.size.height;
	}
	
	if (annotRightButtomY > pageButtomEdge)
	{
		annotRightButtomY = pageButtomEdge;
	}
	
	CGPoint srcOrigin = CGPointZero;
	
	if (pageView.isFacingPage == NO)
	{
		srcOrigin = pageView.page.m_PageInfoA.m_SrcRect.origin;
	}
	else
	{
		if (inLeftPage == YES)
		{
			srcOrigin = pageView.page.m_PageInfoA.m_SrcRect.origin;
		}
		else
		{
			srcOrigin = pageView.page.m_PageInfoB.m_SrcRect.origin;
		}
	}
	
	float originX = srcOrigin.x + annotLeftTopX;
	float originY = srcOrigin.y + annotLeftTopY;
	float width = annotRightButtomX - annotLeftTopX;
	float height = annotRightButtomY - annotLeftTopY;
	
	CGRect annotationRect = CGRectMake(originX, originY, width, height);
	
	return annotationRect;
}

- (LinkAnnotationManager*) getLinkAnnotManager:(int)linkAnnotationIndex
{
	LinkAnnotationManager *mgr = nil;
	LinkAnnotInfoList *linkAnnotInfolist = [pageViewMgr getLinkAnnotationInfoList];
	
	if (linkAnnotInfolist == NULL)
	{
		return mgr;
	}
	
	LinkAnnotInfo *linkAnnotInfo = linkAnnotInfolist->GetLinkAnnotInfo(linkAnnotationIndex);
	
	if (linkAnnotInfo == nil)
	{
		return mgr;
	}
	
	XdwFileInfo *dwFileInfo = (XdwFileInfo *)pageViewMgr.handleDocument->GetFileInfo();
	
	if (nil == dwFileInfo)
	{
		return mgr;
	}
	
	mgr = [[LinkAnnotationManager alloc] 
		   initWithDocumentViewController:self 
		   XdwFileInfo:dwFileInfo
		   LinkAnnotInfo:linkAnnotInfo];
	
	return mgr;
}
// AR NO.17516 の対応 end

- (void) addShadowToLinkAnnotation:(CGRect)rect
{
	isRotate = NO;
	DWScrollView* activePageView = [self getActivePageView];
	linkShadowView = [[UIView alloc] initWithFrame:rect];
	[linkShadowView setBackgroundColor:[UIColor blackColor]];
	linkShadowView.alpha = 0.2;
	linkShadowView.tag = LINK_SHADOW_VIEW_TAG;
	
	[activePageView.page addSubview:linkShadowView];
}

- (void) showLinkAnnotationAlert:(LinkAnnotationManager *)linkManager
{
	if (linkManager == nil)
	{
		return;
	}
	
	linkAnnotationManager = linkManager;
	
	NSString * linkContent = [linkManager getLinkToContent];
	
	if (linkContent == nil)
	{
		linkContent = @"     ";
	}
	
	if (linkAlert != nil)
	{
		[linkAlert release];
	}
	
	linkAlert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_LINKANNOTATION_ALERT", nil)
										   message:linkContent
										  delegate:self
								 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
								 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), 
				 (char *)nil];
	
	linkAlert.tag = 1;
	linkAlert.delegate = self;
	[linkAlert show];	
	
}

- (void) cleanLinkAnnotationShadow
{
	DWPageView* page = [self getActivePageView].page;
	if (page != nil) 
	{
		int tag = linkShadowView.tag;
		for (UIView* subView in page.subviews) 
		{
			if (subView.tag == tag) 
			{
				[linkShadowView removeFromSuperview];
			}
		}
	}
}

- (void) actionlinkToDestPostion
{
	if (isRotate == NO)
	{
		[self cleanLinkAnnotationShadow];
	}
	
	if (nil != linkAnnotationManager)
	{
		[linkAnnotationManager doJump];
		[linkAnnotationManager release];
		linkAnnotationManager = nil;
	}
}


#pragma mark -
#pragma mark action for page rotation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	//return YES;
	// AR NO.17539 の対応 start
	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (toInterfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
	// AR NO.17539 の対応 end
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
    if ([alertInputScale isVisible])
	{
        [self setInputScaleFieldViewPositionWithOrientation:toInterfaceOrientation];
	}
    
	isResetSubviewing = YES;
	[self actionDeviceRotationWithOrientation:toInterfaceOrientation];
	isResetSubviewing = NO;
}

- (void) actionDeviceRotationWithOrientation:(UIInterfaceOrientation)orientation
{
	isRotate = YES;
	
	if (Utility::UIDeviceIsiPad())
	{
		[fontPopMenu dismissPopoverAnimated:YES];
		[facingPopMenu dismissPopoverAnimated:YES];
		// SendEmail の対応 start
		[cooperationPopMenu dismissPopoverAnimated:YES];
		// SendEmail の対応 end
		// zhaijie 2011/09/20 begin
		// NS-AR023
		[editFacingPageViewPopController dismissPopoverAnimated:YES];
		// zhaijie 2011/09/20 end
	}
	
	BOOL fromIsPortrait = UIInterfaceOrientationIsPortrait(pageViewMgr.interfaceOrientation);
	BOOL toIsPortrait = UIInterfaceOrientationIsPortrait(orientation);
	
	if (fromIsPortrait == toIsPortrait)
	{
		return;
	}
	
	pageViewMgr.interfaceOrientation = orientation;
	[self initViewControlsRect];
	[self initPageNumberlabelRect];
	[annotationListViewController.tableView reloadData];
	
	// 3.6 バインダ文書対応 の対応 start
	// change by lixin 20110608 DW_iPhoneEnhance_12
	if (pageViewMgr.documentType == DOC_TYPE_XDW)
	{
		[xdwDocListViewController.tableView reloadData];
	}
	// 3.6 バインダ文書対応 の対応 end
    
    // add tool tip start
	[self initToolTipRect];
	// add tool tip end
	
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	/*
	// update toolbar buttons.
	if ([self UIDeviceIsPortrait] == YES)
	{
		self.toolbarItems = horizontalToolbarItems;
		
		if ( Utility::UIDeviceIsiPad() )
		{
			// Ar No.74
            // 20110707 M.Chikyu (AR17905)
            // 20110707 M.Chikyu (AR17905)
		}
		else
		{
			// Ar No.74
			if (isPortraitBeforePortrait != [self UIDeviceIsPortrait])
			{
				pageAlertTextField.frame = CGRectMake(45, (pageAlert.frame.size.height -80), 200, 30);
			}	
		}
	}
	else
	{
		self.toolbarItems = verticalToolbarItems;
		
		if ( Utility::UIDeviceIsiPad() )
		{
			// Ar No.74
            // 20110707 M.Chikyu (AR17905)
            // 20110707 M.Chikyu (AR17905)
		}
		else
		{
			// Ar No.74
			if (isPortraitBeforePortrait != [self UIDeviceIsPortrait])
			{
				pageAlertTextField.frame = CGRectMake(45, (pageAlert.frame.size.height -110), 200, 27);
			}
		}
	}*/
	
	if (isSearchBarShowing == YES)
	{
		float searchBarW_ = self.navigationController.navigationBar.frame.size.width;
		float searchBarH_ = self.navigationController.navigationBar.frame.size.height;
		[searchBar_ setFrame:CGRectMake(0, 0, searchBarW_, searchBarH_)];
		
		[sliderLabel removeFromSuperview];
	}
	else
	{
		if ([self UIDeviceIsPortrait] == YES)
		{
			self.toolbarItems = horizontalToolbarItems;
			
			if ( Utility::UIDeviceIsiPad() == NO)
			{
				if (isPortraitBeforePortrait != [self UIDeviceIsPortrait])
				{
					pageAlertTextField.frame = CGRectMake(45, (pageAlert.frame.size.height -80), 200, 30);
				}
			}
		}
		else
		{
			self.toolbarItems = verticalToolbarItems;
			
			if ( Utility::UIDeviceIsiPad() == NO)
			{
				if (isPortraitBeforePortrait != [self UIDeviceIsPortrait])
				{
					pageAlertTextField.frame = CGRectMake(45, (pageAlert.frame.size.height -110), 200, 27);
				}
			}
		}
	}
	// xujj 2012.03.22 end
	
	int position = pageViewPos;
	
	FacingMode mode = MODE_REGULAR;
	
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		mode = MODE_REGULAR;
	}
	else
	{
		pageViewMgr.isPageFit = YES;
		pageViewMgr.pageStatus = PAGE_STATUS_FIT;
		
		FacingMode fromMode = MODE_REGULAR;
		FacingMode toMode = MODE_REGULAR;
		
		if ([self UIDeviceIsPortrait] == YES)
		{
			fromMode = pageViewMgr.facingMode;
			toMode = MODE_REGULAR;
		}
		else
		{
			fromMode = MODE_REGULAR;
			toMode = pageViewMgr.facingMode;
		}
		
        // liuqw 20120203 start
        // AR NO.17926の対応
        
        //*******************************************************************
        /*
		 position = [self convertPageViewPosition:pageViewPos 
		 withFromMode:fromMode 
		 withToMode:toMode];
		 */
		//*******************************************************************
        
        if (pageViewMgr.fontOrient == YES) 
        {
            position = [self convertPageViewPosition:pageViewPos 
                                        withFromMode:fromMode 
                                          withToMode:toMode];
        }
        else
        {
            int pos = ([pageViewMgr getPageViewCountAtFacingMode:fromMode] - 1) - pageViewPos;
            position = [self convertPageViewPosition:pos 
                                        withFromMode:fromMode 
                                          withToMode:toMode];
            position = ([pageViewMgr getPageViewCountAtFacingMode:toMode] - 1) - position;
        }
        
        // liuqw 20120203 end
        
		mode = toMode;
		
		// reset slider maxinumValue.
		// liuqw 20110323 start
		// スライダーバーの不具合修正
		//sliderLabel.maximumValue = [pageViewMgr getPageViewCount];
		sliderLabel.maximumValue = [pageViewMgr getPageViewCount] - 1;
		// liuqw 20110323 end
	}
	
	[self updateScrollViewContentSize];
	[self removePageViewsFromScrollView];
	
	if (pageViewMgr.pageStatus == PAGE_STATUS_FIT)
	{
		[self actionMovePageWithPosition:position withMovePageMode:MODE_PAGE_OTHER];
	}
	else
	{
		[self actionMoveOnePageWithPosition:position withMovePageMode:MODE_PAGE_OTHER];
	}
	
	if ([pageViewMgr getPageViewCount] == 1) 
	{
		[sliderLabel removeFromSuperview];
	} 
	else if (hideToolbar == NO) 
	{
		[self.view addSubview:sliderLabel];
	}
	
	// xujj 2012.04.08 start
	// 検索機能の追加
	if (isSearchBarShowing == YES)
	{
		pageNumBackView.hidden = YES;
		[sliderLabel removeFromSuperview];
	}
	// xujj 2012.04.08 end
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	if ( Utility::UIDeviceIsiPad() )
	{
		pageAlert.frame = CGRectMake(pageAlert.frame.origin.x, 150, 
									 pageAlert.frame.size.width, 
									 pageAlert.frame.size.height);
	}
	
	// Ar No.74
	isPortraitBeforePortrait = [self UIDeviceIsPortrait];
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	[self restoreSelectTextGhostViewForRotation];
	// tongtx 2012.03.23 end
}


#pragma mark -
#pragma mark common method.
- (int) convertPageViewPosition:(int)fromPos 
				   withFromMode:(FacingMode)fromMode 
					 withToMode:(FacingMode)toMode
{
	Utility::PageMode from = Utility::PAGE_MODE_NONE;
	
	switch (fromMode)
	{
		case MODE_REGULAR:
			from = Utility::PAGE_MODE_NORMAL;
			break;
		case MODE_FACE_NO:
			from = Utility::PAGE_MODE_FACE_NO;
			break;
		case MODE_FACE_YES:
			from = Utility::PAGE_MODE_FACE_YES;
			break;
		default:
			break;
	}
	
	Utility::PageMode to = Utility::PAGE_MODE_NONE;
	
	switch (toMode)
	{
		case MODE_REGULAR:
			to = Utility::PAGE_MODE_NORMAL;
			break;
		case MODE_FACE_NO:
			to = Utility::PAGE_MODE_FACE_NO;
			break;
		case MODE_FACE_YES:
			to = Utility::PAGE_MODE_FACE_YES;
			break;
		default:
			break;
	}
	
	int toPos = Utility::TransformPageMode(fromPos, from, to);
	
	if (toPos < 0)
	{
		toPos = 0;
	}
	
	return toPos;
}

// AR17558 の対応 start
// delete files in inbox directory except openning file. add by lixin 20110221
- (void)deleteInboxFile 
{
	// delete files in inbox directory
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);	
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *inboxPath = [documentsDirectory stringByAppendingString:@"/Inbox/"];
	
	NSFileManager *filemanager = [NSFileManager defaultManager];
	NSArray *files = [filemanager contentsOfDirectoryAtPath:inboxPath error:nil];
	NSString *fullPath;
	
	BOOL bIsDirectory = NO;
	
	for (NSString* item in files)
	{
		//check item is a directory or a file name
		fullPath = [inboxPath stringByAppendingPathComponent:item];
		[filemanager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		
		if ( bIsDirectory )
		{
			continue;
		}
		
		// if item is not the showing file, delete it.   
		if ( [item compare:fileName] )
		{
			[fileManager removeItemAtPath:fullPath error:nil];
		}
	}
}
// AR17558 の対応 end

- (BOOL) UIDeviceIsPortrait
{
	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		return YES;
	}
	else
	{
		return NO;
	}
}

- (void)removeTopViews
{
	[pageAlertTextField resignFirstResponder];
	[fieldInputScale resignFirstResponder];
	
	// xuxinjun 2012.04.17 start
	// AR005 の対応 start
	[searchBar_ resignFirstResponder];
	// AR005 の対応 end
	// xuxinjun 2012.04.17 end
	
	[alertInputScale dismissWithClickedButtonIndex:alertInputScale.cancelButtonIndex animated:NO];
	[pageAlert dismissWithClickedButtonIndex:pageAlert.cancelButtonIndex animated:NO];
	[linkAlert dismissWithClickedButtonIndex:linkAlert.cancelButtonIndex animated:NO];
	[self.displayActionSheet dismissWithClickedButtonIndex:self.displayActionSheet.cancelButtonIndex animated:NO];
	
	if (docInteractionController != nil)
	{
		[docInteractionController dismissMenuAnimated:NO];
	}
	
	[self removeToolbarPopView];
}

- (UIImage*) getToolbarButtonImageWithName:(NSString*)name
{
	// change by lixin 20101203 AR No.49	
	UIImage *image = [UIImage imageNamed:name];
	return image;
}

- (NSString*) getFacingSettingsIcon
{
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		return _LOWSCALE_FACINGSETTING_BUTTON_ICON_SINGLE_;
	}
	else
	{
		if (pageViewMgr.facingMode == MODE_FACE_NO)
		{
			return _LOWSCALE_FACINGSETTING_BUTTON_ICON_DOUBLE_;
		}
		else
		{
			if (pageViewMgr.facingMode == MODE_FACE_YES)
			{
				return _LOWSCALE_FACINGSETTING_BUTTON_ICON_FRONTCOVER_;
			}
		}
	}
	
	return @"";
}

- (NSString*) getFontSettingsIcon
{
	if (pageViewMgr.fontOrient)
	{
		return _LOWSCALE_FONTSETTING_BUTTON_ICON_HORIZONTAL_;	
	}
	else
	{
		return _LOWSCALE_FONTSETTING_BUTTON_ICON_VERTICAL_;
	}
}

- (NSString*) getAnnotationOnOfIcon:(BOOL)on
{
	if (on)
	{
		return _LOWSCALE_ANNOTATIONSETTING_BUTTON_ICON_ON_;
	}
	else
	{
		return _LOWSCALE_ANNOTATIONSETTING_BUTTON_ICON_OFF_;
	}	
}

- (NSString*) getZoomSettingsIcon
{
	return _LOWSCALE_SPECIFYSCALE_BUTTON_ICON_;
}

- (NSString*) getAnnotationListIcon
{
	return _LOWSCALE_ANNOTATIONLISTVIEW_BUTTON_ICON_;
}

- (NSString*) getBinderListIcon
{
	return _LOWSCALE_BINDERLISTVIEW_BUTTON_ICON_;
}

- (NSString*) getActionIcon
{
	return _LOWSCALE_ACTION_BUTTON_ICON_;
}


#pragma mark -
#pragma mark link from other application.
// liuqw 2012/03/06 start
// AR NO.19019の対応

/*
// tongtx 2011/08/15 start
// Briefcaseと連携機能の追加
- (BOOL) saveFileFromBriefcase 
{
	BOOL saveResult = NO;
	
	NSData *data = [documentSettingsMgr fileContentsAtPath:self.filePath];
	if ([data length] == 0)
	{
		return saveResult;
	}
	
	NSString *documentsDirectory = [documentSettingsMgr getDocumentFilePathWithFileName:nil];
	if (documentSettingsMgr.targetFilename == nil)
	{
		saveResult = [documentSettingsMgr createFileAtDirectoryPath:documentsDirectory 
															   file:self.fileName 
														   contents:data 
														overwritten:NO];
	}
	else
	{
		saveResult = [documentSettingsMgr createFileAtDirectoryPath:documentsDirectory 
															   file:documentSettingsMgr.targetFilename 
														   contents:data 
														overwritten:YES];
	}
	if (saveResult == YES)
	{
		NSString *fileNameRecord = [self.fileName copy];
		NSString *filePathRecord = [self.filePath copy];
		self.fileName = documentSettingsMgr.targetFilename;
		self.filePath = [documentsDirectory stringByAppendingPathComponent:documentSettingsMgr.targetFilename];
		
		
		fromBriefCase = NO;
		
		// tongtx 20120206 start
		// MTA連動機能の対応
		fromMTA = NO;
		// tongtx 20120206 end
		
		self.fileName = fileNameRecord;
		self.filePath = filePathRecord;
		[fileNameRecord release];
		[filePathRecord release];
	}
	return saveResult;
}
*/

- (BOOL) saveEditedFileToLocalDocument
{
	BOOL result = NO;
	if (documentSettingsMgr.targetFilename == nil)
	{
		result = [documentSettingsMgr copyEditedFileToDocuments:self.filePath 
												   destFileName:self.fileName
													overwritten:NO];
	}
	else
	{
		result = [documentSettingsMgr copyEditedFileToDocuments:self.filePath 
												   destFileName:documentSettingsMgr.targetFilename
													overwritten:YES];
	}
	
	return result;
}
// liuqw 2012/03/06 end

- (void) documentInteractionController:(UIDocumentInteractionController *)controller
            didEndSendingToApplication:(NSString *)application
{
	// liuqw 2012/03/06 start
	// AR NO.19019の対応
	//if (fromBriefCase == YES)
	if (fromBriefCase == YES || fromMTA == YES)
		// liuqw 2012/03/06 end		
	{
		[self.navigationController popViewControllerAnimated:NO];
		
		if ([pageViewMgr isTempFileEditing] == YES)
		{
			[pageViewMgr cleanTempDirectory];
		}
	}
}

// tongtx 20110926 start
// NS-AR038 の対応
- (void)documentInteractionControllerDidDismissOpenInMenu:(UIDocumentInteractionController *)controller
{
	isBriefCaseUTIVisible = NO;
    
    // tongtx 20120206 start
    // MTA連動機能の対応
    isMTAUTIVisible = NO;
    // tongtx 20120206 end
}
// tongtx 20110926 end

- (void) interacionWithBriefCase
{
	NSURL *fileURL = [NSURL fileURLWithPath:self.filePath];
	
	if (isBriefCaseUTIVisible == YES)
	{
		isBriefCaseUTIVisible = NO;
		[docInteractionController dismissMenuAnimated:YES];
		[docInteractionController release];
		docInteractionController = nil;
		return;
	}
	
	docInteractionController = [[self docControllerForFile:fileURL] retain];
	
	if( Utility::UIDeviceIsiPad() )
	{
		[docInteractionController presentOpenInMenuFromBarButtonItem:self.navigationItem.leftBarButtonItem
                                                            animated:YES];
		
		// tongtx 20110926 start
		// NS-AR038 の対応
		isBriefCaseUTIVisible = YES;
		// tongtx 20110926 end
		
	}
	else
	{
		[docInteractionController presentOpenInMenuFromRect:self.view.frame 
													 inView:self.view animated:YES];
	}
}

- (BOOL) isInteracionDocumentUpdated
{
	NSString *srcPath = [documentSettingsMgr getDocumentFilePathWithFileName:documentSettingsMgr.targetFilename];
	NSString *dstPath = self.filePath;
	return ([documentSettingsMgr compareDataWithSrcPath:srcPath withDstPath:dstPath] == NO);
}

// tongtx 20120206 start
// MTA連動機能の対応

- (void) returnToAssociateApplicationWithUTI
{
    NSURL *fileURL = [NSURL fileURLWithPath:self.filePath];
    
    if (isMTAUTIVisible == YES)
    {
        isMTAUTIVisible = NO;
        [docInteractionController dismissMenuAnimated:YES];
        [docInteractionController release];
        docInteractionController = nil;
        return;
    }
    
    docInteractionController = [[self docControllerForFile:fileURL] retain];
    
    if( Utility::UIDeviceIsiPad() )
    {
        [docInteractionController presentOpenInMenuFromBarButtonItem:self.navigationItem.leftBarButtonItem
                                                            animated:YES];
        
        isMTAUTIVisible = YES;
    }
    else
    {
        [docInteractionController presentOpenInMenuFromRect:self.view.frame 
                                                     inView:self.view animated:YES];
    }
}

/*
 - (void) returnToBriefCaseWithIsUpdated:(BOOL)updated
 */
- (void) returnToAssociateApplicationWithIsUpdated:(BOOL)updated
{
    NSString *param_     = updated ? @"true":@"false";
    
    NSString *filename_  = [self.fileName stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSString *url_string = nil;
    
    if (fromBriefCase == YES) 
    {
        url_string = [NSString stringWithFormat:URL_VLT20_TO_BRIEFCASE, filename_, param_];
    }
    
    if (fromMTA == YES)
    {
		// tongtx 2012.02.22 start
		
		// コードの対応
		/*
		 url_string = [NSString stringWithFormat:URL_VLT21_TO_MTA, pasteboardFromMTA_, folderNameFromMTA_, filename_, param_];
		 */
		
		NSString *pasteboard = [pasteboardFromMTA_ stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		url_string = [NSString stringWithFormat:URL_VLT21_TO_MTA, pasteboard, folderNameFromMTA_, filename_, param_];
		
		// tongtx 2012.02.22 end
    }
    
    NSURL *url_ = [NSURL URLWithString:url_string];
    
    if ([[UIApplication sharedApplication] canOpenURL:url_])
    {
        [[UIApplication sharedApplication] openURL:url_];
        [self.navigationController popViewControllerAnimated:NO];
        
        if ([pageViewMgr isTempFileEditing] == YES)
        {
            [pageViewMgr cleanTempDirectory];
        }
    }
}

/*
 - (BOOL) isBriefcaseCanOpenWithIsUpdated:(BOOL)updated
 */ 
- (BOOL) isAssociateApplicationCanOpenWithIsUpdated:(BOOL)updated
{
    NSString *url_string = nil;
    
    if (fromMTA == YES) 
    {
        url_string = [URL_VLT21_TO_MTA stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    }
    
    if (fromBriefCase == YES) 
    {
        url_string = [URL_VLT20_TO_BRIEFCASE stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        
    }
    
    NSURL *url_ = [NSURL URLWithString:url_string];
    
    if (([[UIApplication sharedApplication] canOpenURL:url_]) == NO)
    {
        NSString *message_ = nil;
        
        if (fromBriefCase == YES) 
        {
            message_ = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_NOEXISTED",nil), BRIEFCASE_LINK_NAME];
        }
        
        if (fromMTA == YES) 
        {
            message_ = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_NOEXISTED",nil), appnameFromMTA_];
        }
        
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
                                                            message:message_ 
                                                           delegate:self
                                                  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK",nil)
                                                  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL",nil),
                                  (char *)nil];
        
        alertView.tag = TAG_BRIEFCASE_EXIST_ALERT;
        [alertView show];
        [alertView release];
        
        return NO;
    }
    
    return YES;
}
// tongtx 20120206 end


#pragma mark -
#pragma mark ActionSheet delegate method.
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	// SendEmail の対応 start
	if (actionSheet.tag == COOPERATION_MENU_TAG) 
	{
		switch (buttonIndex)
		{
			case 0:
				[self actionTouchSendMailButton];
				break;
			case 1:
				[self actionTouchOpenModeButton];
				break;
			default:
				return;
		}
	} 
    
	// lixin 20110813 start
	// ページ編集機能の追加 
	else if (actionSheet.tag == TAG_ACTIONSHEET_CHOOSEEDITPAGE)
	{
		if (buttonIndex != actionSheet.cancelButtonIndex)
		{
			[self editPageViewWithButtonIndex:buttonIndex];
		}
	}
	// lixin 20110813 end
    
	else 
	{
		// AR NO.17770 の対応 start
		isResetSubviewing = YES;
		if(actionSheet.tag == 1)
		{
			[self actionFacingSettingsChanged:buttonIndex];
		}
		else
		{
			[self actionFontSettingsChanged:buttonIndex];
		}
		isResetSubviewing = NO;
		// AR NO.17770 の対応 end
	}
	// SendEmail の対応 end
}


#pragma mark -
#pragma mark alertView delegate method.
- (void) willPresentAlertView:(UIAlertView *)alertView
{
    if (alertView.tag == TAG_INPUT_SCALE_ALERT)
	{
        [self setInputScaleFieldViewPosition];
        return;
    }
    
	if ( Utility::UIDeviceIsiPad() )
	{
		alertView.frame = CGRectMake(alertView.frame.origin.x, 150, 
									 alertView.frame.size.width, 
									 alertView.frame.size.height);
	}
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	
	// xujj 2012.04.01 start
	// 検索機能の追加
	if (alertView.tag == TAG_SEARCH_FIRST_PAGE_ALERT) 
	{
		if (buttonIndex == 0) 
		{
			[pageViewMgr beginSearchText];

			searchInfo_.startPageIndex = -1;
			searchInfo_.endPageIndex = searchStartPageIndex;

			[self searchDestTextFromAllPages:NO withIsEnd:YES];
		} 
		else 
		{
			return;
		}
	}
	
	if (alertView.tag == TAG_SEARCH_LAST_PAGE_ALERT)
	{
		if (buttonIndex == 0)
		{
			[pageViewMgr beginSearchText];

			searchInfo_.startPageIndex = -1;
			searchInfo_.endPageIndex = searchStartPageIndex;
			
			[self searchDestTextFromAllPages:YES withIsEnd:YES];
		} 
		else 
		{
			return;
		}
	}
	// xujj 2012.04.01 end
	
    // tongtx 20120206 start
    // 有償化アナウンス機能の対応
    if (alertView.tag == TAG_PAYMENT_NOTICE_ALERT)
    {
        [self actionOnTouchEditButton];
        
        return;
    }
    // tongtx 20120206 end
    
	// tongtx 2011/08/16 start
	// Briefcaseと連携機能の追加
	if (alertView.tag == TAG_BRIEFCASE_EXIST_ALERT)
	{
		//[alertView dismissWithClickedButtonIndex:alertView.cancelButtonIndex animated:NO];
		if (buttonIndex == 0)
		{
			// liuqw 2012/03/06 start
			// AR NO.19019の対応
			
			/*
			[self saveFileFromBriefcase];
			*/
			
			[self saveEditedFileToLocalDocument];
			
			// liuqw 2012/03/06 end
		}

		if ([pageViewMgr isTempFileEditing] == YES)
		{
			[pageViewMgr cleanTempDirectory];
		}

		[self.navigationController popViewControllerAnimated:YES];
	}
	
	if (alertView.tag == TAG_LINK_BRIEFCASE_ALERT)
	{
		[alertView dismissWithClickedButtonIndex:alertView.cancelButtonIndex animated:YES];
		
		// liuqw 2012/03/06 start
		// AR NO.19019の対応
		
		/*
		 [self saveFileFromBriefcase];
		 */
		
		[self saveEditedFileToLocalDocument];
		
		// liuqw 2012/03/06 end
		
		[self interacionWithBriefCase];

		return;
	}
	// tongtx 2011/08/16 end
	
	
	// liuqw 2012/03/06 start
	// AR NO.19019の対応
	
	if (alertView.tag == TAG_LINK_MTA_ALERT)
	{
		[alertView dismissWithClickedButtonIndex:alertView.cancelButtonIndex animated:YES];
		[self saveEditedFileToLocalDocument];
		[self returnToAssociateApplicationWithUTI];
		
		return;
	}
	
	// liuqw 2012/03/06 end
	
	
    // liuqw 20110801 start
    // ページ編集機能の追加
	if (alertView.tag == TAG_SAVE_UPDATE_ALERT)
	{
        if (buttonIndex == 0)
		{
			if (fromBriefCase == YES)
			{
				[alertView dismissWithClickedButtonIndex:0 animated:YES];

				if ([DWAssociationManager writeDataToPasteBoard:self.filePath] == YES)
				{
					[self returnToAssociateApplicationWithIsUpdated:YES];
				}
				else
				{
					NSString *message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_SAVEFAILE", nil),
																					BRIEFCASE_LINK_NAME,
																					BRIEFCASE_LINK_NAME];
					
					UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
																	message:message
																   delegate:self
														  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
														  otherButtonTitles:nil];
					alert.tag = TAG_LINK_BRIEFCASE_ALERT;

					[alert show];
					[alert release];
					
				}
				
				return;
			} 
            
            // tongtx 20120206 start
            // MTA連動機能の対応
            else if (fromMTA == YES)
            {
                [alertView dismissWithClickedButtonIndex:0 animated:YES];
                
                if ([DWAssociationManager writeFileDataToPasteBoard:pasteboardFromMTA_ 
                                                               type:MTA_PASTEBOARD_TYPE 
                                                           filepath:self.filePath] == YES)
                {
                    [self returnToAssociateApplicationWithIsUpdated:YES];
                }
                else
                {
                    NSString *message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ASSOCIATION_SAVEFAILE", nil),
                                         appnameFromMTA_,
                                         appnameFromMTA_];
                    
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                                    message:message
                                                                   delegate:self
                                                          cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                          otherButtonTitles:nil];
					
					// liuqw 2012/03/06 start
					// AR NO.19019の対応
					
					//alert.tag = TAG_LINK_BRIEFCASE_ALERT;
					alert.tag = TAG_LINK_MTA_ALERT;
					
					// liuqw 2012/03/06 end
                    
                    [alert show];
                    [alert release];
                }
                
                return;
            }
            // tongtx 20120206 end
            
			else 
			{
				BOOL saveSuccess = [pageViewMgr saveDocumentUpdateContent];
				if (saveSuccess == NO)
				{
					[alertView dismissWithClickedButtonIndex:0 animated:YES];
					
					NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_ANNOTATIONEDIT_SAVEFAILE", nil),
																					self.fileName];
					
					UIAlertView* alertSaveUpdate = [[UIAlertView alloc] initWithTitle:nil
																			  message:message
																			 delegate:self
																	cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil)
																	otherButtonTitles:nil];				
					[alertSaveUpdate show];
					[alertSaveUpdate release];
					
					return;
				}
				else 
				{
					[self.navigationController popViewControllerAnimated:YES];
				}
			}
        }
		else 
        {
            // tongtx 20120206 start
            // MTA連動機能の対応
            if (fromBriefCase == YES || fromMTA == YES)
            {
                [self returnToAssociateApplicationWithIsUpdated:NO];
            }
            // tongtx 20120206 end
			else
			{
				[self.navigationController popViewControllerAnimated:YES];
			}
            
			if ([pageViewMgr isTempFileEditing] == YES)
			{
				[pageViewMgr cleanTempDirectory];
			}
		}
		
		return;
        
    }
    // liuqw 20110801 end
    

    // 「拡大率指定ボタンの追加」の対応 start
    
    // liuqw 2011/10/10 start
    // NS-AR2002 の対応
    
	if (alertView.tag == TAG_INPUT_SCALE_ALERT)
	{
		if (buttonIndex == 0)
		{
			[self inputZoomScaleWithAlertView:alertView];
		}

		return;
	}
	else if (alertView.tag == TAG_INPUT_SCALE_ERROR)
	{
		if (buttonIndex == 0)
		{
			[self showZoomScaleInputView];
		}

		return;
    }
    // liuqw 2011/10/10 end
    

    // 「拡大率指定ボタンの追加」の対応 end
    
	if (alertView.tag == 0)
	{
		if (buttonIndex == 0)
		{
			UITextField* pageText = (UITextField*)[alertView viewWithTag:PAGE_NUMBER_TEXT_TAG];
	
			if (pageText == nil)
			{
				return;
			}
			
			// AR.78 start
			//int pageCount = [pageViewMgr getPageViewCount];
			int pageCount = pageViewMgr.pageTotalCount;
			// AR.78 end
			
			NSString *stringValue = [pageText text];
			
			// FX Ar No.17574 start
			// check input string is int string 
			BOOL InputIsInt = NO;
			int InputVal = 0;
			NSScanner *scan = [NSScanner scannerWithString:stringValue];
			InputIsInt = [scan scanInt:&InputVal]&&[scan isAtEnd];
			// FX Ar No.17574 end 
			
			int pageValue = [stringValue intValue];

			if (pageValue < 1 ||
				pageValue > pageCount ||
				InputIsInt == NO)
			{
				NSString *messageString = [NSString stringWithFormat:NSLocalizedString(@"MSG_WARNING_PAGENUMBERWARNING", nil),
																						pageCount ];
	
				UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
																message:messageString 
															   delegate:nil 
													  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
													  otherButtonTitles:nil];
				[alert show];
				[alert release];
			}
			else
			{
				int pos = pageValue - 1;
				
				// AR.78 start
				// change page pos compute
				// when facing enable, compute page pos in new way.
				// font with Vertical Books books
				if (pageViewMgr.fontOrient == NO)
				{
					if ([self UIDeviceIsPortrait] == NO) 
					{
						// AR17772 M.Chikyu start
						
						switch (pageViewMgr.facingMode)
						{
							case MODE_REGULAR:
								pos = pageCount - pageValue;
								break;

							case MODE_FACE_NO:
								pos = (pageCount + 1)/2 - (pageValue + 1)/2;
								break;

							case MODE_FACE_YES:
								pos = (pageCount + 2)/2 - (pageValue + 2)/2;
								break;

							default:
								break;
						}
						
						// AR17772 M.Chikyu end
					}
					else
					{
						// AR17772 M.Chikyu start

						/*
						pos = pageCount - 1 - pos;
						 */
						pos = pageCount - pageValue;

						// AR17772 M.Chikyu end
					}
				}
				else
				{ 
					if ([self UIDeviceIsPortrait] == NO) 
					{
						// AR17772 M.Chikyu start
						
						// font with cross books
						switch (pageViewMgr.facingMode)
						{
							case MODE_REGULAR:
								pos = pageValue - 1;
								break;

							case MODE_FACE_NO:
								pos = (pageValue + 1)/2 - 1;
								break;
	
							case MODE_FACE_YES:
								pos = (pageValue + 2)/2 - 1;
								break;

							default:
								break;
						}
						
						// AR17772 M.Chikyu end
					}
					else
					{
						pos = pageValue - 1;
					}
				}
				// AR.78 end
				
				// ページ移動仕様の変更の対応 start
				[self actionMovePageWithPosition:pos withMovePageMode:MODE_PAGE_OTHER];
				// ページ移動仕様の変更の対応 end
			}
		}
		
		[self performShowScreen];
		
	}
	else
	{
		if (buttonIndex == 0)
		{
			// AR NO.42
			if ([linkAnnotationManager isSupportLinkTo] == NO)
			{
				if (isRotate == NO)
				{
					[self cleanLinkAnnotationShadow];
				}
				return;
				
			}
			else if([linkAnnotationManager isConfilictLinkTo] == YES)
			{
				if (isRotate == NO)
				{
					[self cleanLinkAnnotationShadow];
				}
				
				[linkAnnotationManager jumpToTarget:1];
				return;
			}
			
			[self actionlinkToDestPostion];		
		}
		else
		{
			if (isRotate == NO)
			{
				[self cleanLinkAnnotationShadow];
			}
            
            // 「リンクアノテーションジャンプ方法」変更の対応 start
			// 3.6 バインダ文書対応 の対応 start
			// change by lixin 20110608 DW_iPhoneEnhance_12
			
            // lixin 20110813 start
			// ページ編集機能の追加
			
			// 3.6 バインダ文書対応 の対応 end
			if (showAnnotationList == YES ||
				showXdwDocList == YES     ||
                showFacingSettings == YES ||
                showFontSettings == YES   ||
                showCooperationSettings == YES ||
				showChooseEditPageIndexView == YES)
            {
                showAnnotationList = NO;
				showXdwDocList = NO;
                showFacingSettings = NO;
                showFontSettings = NO;
                showCooperationSettings = NO;
				showChooseEditPageIndexView = NO;
                [self removeToolbarPopView];
            }
			// lixin 20110813 end
            
            else
            {
                [self cancelShowScreen];
			//	if ([UIApplication sharedApplication].statusBarHidden == NO)
				if (self.navigationController.navigationBarHidden == NO)
                {
                    
                    [self performSelector:@selector(hideAllToolbarItems:) 
                               withObject:[NSNumber numberWithBool:YES] 
                               afterDelay:0];
                }
                else
                {
                    [self performSelector:@selector(hideAllToolbarItems:) 
                               withObject:[NSNumber numberWithBool:NO] 
                               afterDelay:0];
                }
            }
            // 「リンクアノテーションジャンプ方法」変更の対応 end
            
		}
	}
}


#pragma mark -
#pragma mark UITextField delegate method.
//AR No17624 add
- (BOOL)textFieldShouldReturn:(UITextField *)theTextField
{
    // 「拡大率指定ボタンの追加」の対応 start
    
    if (theTextField.tag == TAG_INPUT_SCALE_FIELD)
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
        [pageAlertTextField resignFirstResponder];
        [self alertView:pageAlert clickedButtonAtIndex:0];
        [pageAlert dismissWithClickedButtonIndex:0 animated:YES];
    }
    
    // 「拡大率指定ボタンの追加」の対応 end
    
	return YES;
}


#pragma mark -
#pragma mark scrollView delegate method.
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
	// tongtx 2012.04.01 start
	// 選択機能の追加
	[self restoreCopyMenu];
	// tongtx 2012.04.01 end
	
	if (isResetSubviewing == YES)
	{
		return;
	}
	
	BOOL isDWSC = [scrollView isMemberOfClass:[DWScrollView class]];
	
	if (isDWSC == YES)
	{
		return;
	}
	
	int prePos		= pageViewPos;
	int pageWidth	= bgScrollView.frame.size.width;
	int offsetX		= bgScrollView.contentOffset.x;
	
	int position = (offsetX + pageWidth / 2 ) / pageWidth;	
	
	if (prePos == position)
	{
		return;
	}
	
	if (position >= 0 && position <= [pageViewMgr getPageViewCount] - 1)
	{
		// tongtx 2012.04.23 start
		// 選択機能の追加
		[self cancelSelectMode];
		// tongtx 2012.03.23 end
		
		[self actionMovePageWithPosition:position withMovePageMode:MODE_PAGE_SCROLL];
		
		[NSObject cancelPreviousPerformRequestsWithTarget:self];
		[self initPageNumberlabelRect];
		[self hidePageNumberLable:NO];
		
		[self performSelector:@selector(hidePageNumberLable:)
				   withObject:[NSNumber numberWithBool:YES]
				   afterDelay:HIDE_TOOLBAR_DELAY];
		
		
		// xujj 2012.04.08 start
		// 検索機能の追加
		if (isSearchBarShowing == YES)
		{
			pageNumBackView.hidden = YES;
		}
		// xujj 2012.04.08 end
		
		return;
	}
}

#pragma mark -
#pragma mark some method not used.
- (void) actionDragPageView:(UIPanGestureRecognizer *)gestureRecognizer
{
	CGPoint velocity = [gestureRecognizer velocityInView:bgScrollView];
	int pageCount = [pageViewMgr getPageViewCount];
	
	BOOL movedPage = NO;
	float frameWidth = bgScrollView.frame.size.width;

	if (velocity.x <= MOVE_PAGE_MAXVELOCITY && velocity.x >= MOVE_PAGE_MINVELOCITY)
	{
		// AR NO.17526 の対応 start
		if ([gestureRecognizer state] == UIGestureRecognizerStateChanged)
		{	
			if (fabs(velocity.x) < fabs(velocity.y))
			{
				[gestureRecognizer setTranslation:CGPointZero inView:bgScrollView];
				return;
			}
			
			CGPoint translation = [gestureRecognizer translationInView:bgScrollView];
			float offsetX = [bgScrollView contentOffset].x - translation.x;
			float offsetY = [bgScrollView contentOffset].y;
			[bgScrollView setContentOffset:CGPointMake(offsetX, offsetY)];
			[gestureRecognizer setTranslation:CGPointZero inView:bgScrollView];
		}
		// AR NO.17526 の対応 end
	}
	
	if ([gestureRecognizer state] == UIGestureRecognizerStateEnded)
	{
		int position = pageViewPos;

		if (velocity.x > MOVE_PAGE_MAXVELOCITY)
		{
			if (position > 0)
			{
				movedPage = YES;
			}
			else
			{
				[self updateScrollIndicatorPos:position animated:YES];
				return;
			}

		}
		else if (velocity.x < MOVE_PAGE_MINVELOCITY)
		{
			if (position < pageCount - 1)
			{
				[self actionMovePageWithPosition:(++position) 
								withMovePageMode:MODE_PAGE_SCROLL];
				
				movedPage = YES;
			}
			else
			{
				[self updateScrollIndicatorPos:position animated:YES];
				return;
			}
			
		}
		else
		{
			float offsetX = [bgScrollView contentOffset].x;

			if (offsetX < 0)
			{
				offsetX = 0;
			}
			
			if (offsetX > bgScrollView.contentSize.width - frameWidth)
			{
				offsetX = bgScrollView.contentSize.width - frameWidth;
			}
			
			if (offsetX > frameWidth * position + frameWidth / 5)
			{
				position++;
			}
			else if (offsetX < frameWidth * position - frameWidth / 5)
			{
				position--;
			}
			
			if (position == pageViewPos)
			{
				[self updateScrollIndicatorPos:position animated:YES];
				return;
			}
			
			[self actionMovePageWithPosition:position
							withMovePageMode:MODE_PAGE_SCROLL];
			
			movedPage = YES;
		}
	}
	
	if (movedPage == YES)
	{
		[NSObject cancelPreviousPerformRequestsWithTarget:self];
		[self initPageNumberlabelRect];
		[self hidePageNumberLable:NO];
	}
	
}

- (void) didSwitchButtonValueChanged:(EnvironmentSettingsViewController *)sender
{
	keepDocumentStatus = sender.keepDocumentStatus;
}

// xuxinjun 2012.03.23 start
// パーミッションの対応.
#pragma mark -
#pragma mark Payment.
- (BOOL) hasMakePayment
{
	if ([[NSUserDefaults standardUserDefaults] boolForKey:TRANSACTION_STATE] == YES)
    {
        return YES;
    }
	
    return NO;
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
#pragma mark - 
#pragma mark search text
- (void) actionTouchSearchButton
{	
	if (showAnnotationList == YES)
	{
		showAnnotationList = NO;
		[annotationListView removeFromSuperview];
	}
	
	if (showXdwDocList == YES)
	{
		showXdwDocList = NO;
		[xdwDocListView removeFromSuperview];
	}
	
	pageNumBackView.hidden = YES;
	[sliderLabel removeFromSuperview];
	
    self.navigationController.navigationBar.hidden = YES;
	
	float searchBarW_ = self.navigationController.navigationBar.frame.size.width;
    float searchBarH_ = self.navigationController.navigationBar.frame.size.height;
	[searchBar_ setFrame:CGRectMake(0, 0, searchBarW_, searchBarH_)];
	
	[self.view addSubview:searchBar_];
	self.toolbarItems = searchToolbarItems_;
    [searchBar_ becomeFirstResponder];
	
	[pageViewMgr beginSearchText];
	isSearchBarShowing = YES;

	ghostViewPageIndex = -1;
	searchStartAnnoIndex = -1;
}

- (void) actionTouchFrontSearchButton
{
	[self cancelSelectMode];
	
	if (ghostViewPageIndex != -1) 
	{
		searchInfo_.startPageIndex = ghostViewPageIndex;
	}
	else
	{
		searchStartPageIndex = [self transformPageViewIndexToPageIndex:pageViewMgr.pageIndex];
		searchInfo_.startPageIndex = searchStartPageIndex;
	}
	
	searchInfo_.endPageIndex = -1;
	
	isSearchOrientation = NO;
	[self searchDestTextFromAllPages:isSearchOrientation withIsEnd:NO];
}

- (void) actionTouchNextSearchButton
{
	[self cancelSelectMode];
	
	if (ghostViewPageIndex != -1) 
	{
		searchInfo_.startPageIndex = ghostViewPageIndex;
	}
	else
	{
		searchStartPageIndex = [self transformPageViewIndexToPageIndex:pageViewMgr.pageIndex];
		searchInfo_.startPageIndex = searchStartPageIndex;
	}
	
	searchInfo_.endPageIndex = -1;
	
	isSearchOrientation = YES;
	[self searchDestTextFromAllPages:isSearchOrientation withIsEnd:NO];
}

- (void) searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
	[searchBar resignFirstResponder];
	
	searchStartPageIndex = [self transformPageViewIndexToPageIndex:pageViewMgr.pageIndex];
	
	if (ghostViewPageIndex != -1) 
	{
		searchInfo_.startPageIndex = ghostViewPageIndex;
	}
	else
	{
		searchInfo_.startPageIndex = searchStartPageIndex;
	}

	searchInfo_.endPageIndex = -1;

	isSearchOrientation = YES;
	[self searchDestTextFromAllPages:isSearchOrientation withIsEnd:NO];
	
	[self setSearchBarCancelButtonEnabled];
}

- (void) searchDestTextFromAllPages:(BOOL)toNext withIsEnd:(BOOL)end;
{	
	NSString *searchText_ = [searchBar_ text];
	if (searchText_ != nil && searchText_.length > 0) 
	{	
		[self displayIndicator];
		
		searchInfo_.annoIndex = searchStartAnnoIndex;
		searchInfo_.next = toNext;
		searchInfo_.text = searchText_;
		
		BOOL result = [pageViewMgr searchText:searchInfo_];
		
		[self hideIndicator];
		
		if (result == YES) 
		{
			// 1. record page index.
			searchStartPageIndex = searchInfo_.pageIndex;
			searchStartAnnoIndex = searchInfo_.annoIndex;
			ghostViewPageIndex	 = searchInfo_.pageIndex;
			
			// 2. if current page not found, move page.
			int pageViewIndex = [self transformPageIndexToPageViewIndex:searchStartPageIndex];
			if (pageViewMgr.pageIndex != pageViewIndex )
			{			
				int pos = pageViewIndex;
				if (pageViewMgr.fontOrient == NO)
				{
					pos = [pageViewMgr getPageViewCount] - 1 - pos;
				}
				
				[self actionMovePageWithPosition:pos 
								withMovePageMode:MODE_PAGE_OTHER];
			}
			
			[self hideSearchTextGhostView];
			
			// 3. remove 
			[searchInfo_.pixSearchRects removeAllObjects];
			
			BOOL left = [self isPageInPageViewLeft:searchStartPageIndex];

			// 4. get ghost view rect in dest page.
			for (int i = 0; i < searchInfo_.mmSearchRects.count; i++) 
			{
				CGRect mmrect = [[searchInfo_.mmSearchRects objectAtIndex:i] CGRectValue];
				CGRect pixrect = CGRectZero;

				if (searchInfo_.annoIndex < 0)
				{
					pixrect = [self transformRectFromMMToPixel:mmrect];
				}
				else
				{
					pixrect = [self transformRectFromMMToPixel:mmrect andLeftPage:left];
				}
				[searchInfo_.pixSearchRects addObject:[NSValue valueWithCGRect:pixrect]];
			}
		
			// 5. add ghost view
			DWScrollView* pageView_ = [self getActivePageView];
			selectInfo_.isLeftPage = left;
			[self showSearchTextGhostView:pageView_  andLeft:left];
		}
		else
		{	
			if (end == NO)
			{
				if (isSearchOrientation == YES) 
				{
					NSString* message_ = NSLocalizedString(@"MSG_SEARCH_LAST_PAGE", nil);
					UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
																		message:message_ 
																	   delegate:self
															  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES",nil)
															  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil) ,(char*)nil];
					
					alertView.tag = TAG_SEARCH_LAST_PAGE_ALERT;
					[alertView show];
					[alertView release];
				}
				else if(isSearchOrientation == NO)
				{
					NSString* message_ = NSLocalizedString(@"MSG_SEARCH_FIRST_PAGE", nil);
					UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
																		message:message_ 
																	   delegate:self
															  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES",nil)
															  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil) ,(char*)nil];
					
					alertView.tag = TAG_SEARCH_FIRST_PAGE_ALERT;
					[alertView show];
					[alertView release];
				}
			}
			else
			{
				[self hideSearchTextGhostView];
				
				NSString* message_ = NSLocalizedString(@"MSG_SEARCH_NO_RESULT_ALL", nil);
				UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
																	message:message_ 
																   delegate:nil
														  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK",nil)
														  otherButtonTitles:nil];
				[alertView show];
				[alertView release];
				
				ghostViewPageIndex = -1;
			}
		}
	}
	
	[self setSearchBarCancelButtonEnabled];
}

- (void) setSearchBarCancelButtonEnabled
{
	for(id view in [searchBar_ subviews])
    {
        if([view isKindOfClass:[UIButton class]])
        {
            [((UIButton *)view) setEnabled:YES];
        }
    }
}

- (void) showSearchTextGhostView:(DWScrollView*)pageView andLeft:(BOOL)left
{
	if (pageView.page != nil)
	{
		UIView *searchGhostView_ = nil; 
		
		CGRect pageRect = CGRectZero;
		if (left == YES) 
		{
			pageRect = pageView.page.m_PageInfoA.m_SrcRect;
		}
		else
		{
			pageRect = pageView.page.m_PageInfoB.m_SrcRect;
		}
		
		if (searchStartAnnoIndex == -1) 
		{
			searchGhostView_ = [[[DWSearchGhostView alloc] initWithFrame:pageRect 
															 searchInfo:searchInfo_]autorelease];
		}
		else
		{
			CGRect pixRect = [[searchInfo_.pixSearchRects objectAtIndex:0] CGRectValue];
			
			if ([self UIDeviceIsPortrait] == NO && 
				pageView.isFacingPage == YES && 
				CGRectContainsRect(pageRect, pixRect) == false) 
			{
				pixRect = CGRectIntersection(pageRect, pixRect);
				
				float MAXPageWidth	= pageRect.origin.x + pageRect.size.width;
				float MAXPageHeight	= pageRect.origin.y + pageRect.size.height;

				if (pixRect.origin.x <= pageRect.origin.x) 
				{
					pixRect.origin.x = pageRect.origin.x - kFacePageEdgeWidth;
					pixRect.size.width += kFacePageEdgeWidth;
				}
				
				if (pixRect.origin.y <= pageRect.origin.y) 
				{
					pixRect.origin.y = pageRect.origin.y - kFacePageEdgeWidth;
					pixRect.size.height += kFacePageEdgeWidth;
				}
				
				if (pixRect.origin.x + pixRect.size.width >= MAXPageWidth) 
				{
					pixRect.size.width = MAXPageWidth - pixRect.origin.x + kFacePageInterval;
				}
				
				if (pixRect.origin.y + pixRect.size.height >= MAXPageHeight)
				{
					pixRect.size.height = MAXPageHeight - pixRect.origin.y + kFacePageEdgeWidth;
				}
			}
			
			searchGhostView_ = [[[DWAnnBorderGhostView alloc] initWithFrame:pixRect 
																borderColor:nil 
																  zoomScale:pageView.zoomScale]autorelease];
		}
		
		searchGhostView_.tag = TAG_SEARCH_GHOST_VIEW;
		[pageView.page addSubview:searchGhostView_];
		
		if (pageView.zoomScale != 1)
		{
			CGRect pixRect = CGRectZero;
			if (searchInfo_.annoIndex < 0) 
			{
				pixRect = [self transformRectFromMMToPixel:[[searchInfo_.mmSearchRects objectAtIndex:0] CGRectValue] 
											   andLeftPage:left];
			}
			else
			{
				pixRect = [[searchInfo_.pixSearchRects objectAtIndex:0] CGRectValue];
			}
			
			[pageViewMgr displaySearchTargetInPageView:pageView withMoveRect:pixRect withLeft:left];
		}
	} 
}

- (void) hideSearchTextGhostView;
{
	for (int i = 0; i < bgScrollView.subviews.count; i++) 
	{
		DWScrollView *pageView_ = (DWScrollView*)[bgScrollView.subviews objectAtIndex:i];
		
		if (pageView_.page != nil)
		{
			UIView *ghostView_ = [pageView_.page viewWithTag:TAG_SEARCH_GHOST_VIEW];
			
			if (ghostView_ != nil)
			{
				[ghostView_ removeFromSuperview];
			}
		}
	}
}

- (void) restoreSearchTextGhostViewForMovePage:(int)position
{
	if (isSearchBarShowing == YES) 
	{
		if (ghostViewPageIndex == -1) 
			return;
		
		if (searchInfo_.pixSearchRects != NULL) 
		{
			[searchInfo_.pixSearchRects removeAllObjects];
		}		
		
		// 1. is same page.
		int movePageIndex = position;
		if (pageViewMgr.fontOrient == NO)
		{
			movePageIndex = ([pageViewMgr getPageViewCount] - 1) - position;
		}
		
		int pageViewIndex = [self transformPageIndexToPageViewIndex:ghostViewPageIndex];
		if (pageViewIndex != movePageIndex) 
		{
			return;
		}
		
		BOOL left = [self isPageInPageViewLeft:searchStartPageIndex];
		
		// 2. get ghost view rect in dest page.
		for (int i = 0; i < [searchInfo_.mmSearchRects count]; i++) 
		{
			CGRect mmrect = [[searchInfo_.mmSearchRects objectAtIndex:i] CGRectValue];
			CGRect pixrect = CGRectZero;
			
			if (searchInfo_.annoIndex < 0)
			{
				pixrect = [self transformRectFromMMToPixel:mmrect];
			}
			else
			{
				pixrect = [self transformRectFromMMToPixel:mmrect andLeftPage:left];
			}
			
			[searchInfo_.pixSearchRects addObject:[NSValue valueWithCGRect:pixrect]];
		}
		
		
		// 3. restore ghost view.
		DWScrollView *pageView_ = [self getActivePageView];
		UIView *ghostView_ = [pageView_.page viewWithTag:TAG_SEARCH_GHOST_VIEW];
		if (ghostView_ == nil) 
		{
			[self showSearchTextGhostView:pageView_ andLeft:(BOOL)left];
		}
	}
}

- (void) actionOnKeyboardDidHidden
{
	if (isSearchBarShowing == YES)
	{
		[self setSearchBarCancelButtonEnabled];
	}
}

- (void) searchBarTextDidBeginEditing:(UISearchBar *)searchBar
{
	[self cancelSelectMode];
}

- (void) searchBarCancelButtonClicked:(UISearchBar *)searchBar
{
    [searchBar resignFirstResponder];
    [searchBar removeFromSuperview];
    self.navigationController.navigationBar.hidden = NO;
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		self.toolbarItems = horizontalToolbarItems;
	}
	else
	{
		self.toolbarItems = verticalToolbarItems;
	}
	
	[self hideSearchTextGhostView];
	
	isSearchBarShowing = NO;
	searchGhostViewRect = CGRectNull;
	searchStartPageIndex = -1;
	searchStartAnnoIndex = -1;
	ghostViewPageIndex = -1;
	
	[pageViewMgr endSearchText];

	[self cancelSelectMode];
	
	[self.view addSubview:sliderLabel];
	
	pageNumBackView.hidden = NO;
	[self updatePageNumberBackGroundViewRect];
}
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
#pragma mark - 
#pragma mark select text
- (void) actionOnLongPressPageView:(UILongPressGestureRecognizer *)gestureRecognizer
{
	if (gestureRecognizer.state != UIGestureRecognizerStateBegan) return;
	
	DWScrollView* pageView = [self getActivePageView];
	
	// get touch point.(pixel)
	CGPoint touchPoint = [gestureRecognizer locationInView:pageView.page];
	
	// get page index.
	selectInfo_.isLeftPage = [self isTouchInLeftPage:touchPoint];
	int pageIndex_  = [self getPageIndexWithPageViewIndex:pageViewMgr.pageIndex
											  andLeftPage:selectInfo_.isLeftPage];
	
	int annoIndex = -1;
	
	// get touch point.(mm)
	CGRect rect = CGRectMake(touchPoint.x, touchPoint.y, 0, 0);
	rect = [self transformRectFromPixelToMM:rect andLeftPage:selectInfo_.isLeftPage];
	
	// get annotation rect. (mm)
	CGRect annotationRect = [self getAnnotationRectWithPageIndex:pageIndex_ 
												   andTouchPoint:rect.origin 
													andAnnoIndex:annoIndex];
	
	// press in page.
	BOOL result = NO;
	if (CGRectEqualToRect(annotationRect, CGRectNull) == YES)
	{
		selectInfo_.pageIndex	= pageIndex_;
		selectInfo_.annoIndex	= -1;
		selectInfo_.start		= rect.origin;
		selectInfo_.end			= selectInfo_.start;
		
		result = [pageViewMgr selectTextInPage:selectInfo_];
		if (result == YES) 
		{
			[self showSelectTextGhostView];
		}
	}
	// press in annotation.
	else 
	{
		selectInfo_.pageIndex	= pageIndex_;
		selectInfo_.annoIndex	= annoIndex;
		
		result = [pageViewMgr selectTextInPage:selectInfo_];
		if (result == YES) 
		{
			// set ann rect.
			selectInfo_.rect = annotationRect;
			
			// add ghost view to page.
			[self showSelectTextGhostView];
		}
	}
	
	if (result == NO) 
	{
		[self cancelSelectMode];
	}
}

- (BOOL) isPressInLeftPage:(CGPoint)point
{
	DWScrollView* pageView = [self getActivePageView];
	if (pageView == nil) return YES;
	
	BOOL isLeftPage = YES;
	if (pageView.isFacingPage == YES)
	{
		float firstPageOriginX = pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageWidth   = firstPageOriginX + pageView.page.m_PageInfoA.m_SrcRect.size.width;
		
		if (point.x < firstPageWidth)
		{
			isLeftPage = YES;
		}
		else
		{
			isLeftPage = NO;
		}
	}
	
	return isLeftPage;
}

- (CGRect) getAnnotationRectWithPageIndex:(int)index andTouchPoint:(CGPoint)point andAnnoIndex:(int&)annIndex
{
	if (pageViewMgr.showAnnotation == NO) return CGRectNull;
	
	DWScrollView *pageView_ = [self getActivePageView];
	long scale = pageView_.page.m_PageInfoA.m_PageFitScale;
	
	CGRect annoRect = CGRectNull;
	pageViewMgr.logicAnnMananger->GetLogicAnnotationList(index);
	int count = pageViewMgr.logicAnnMananger->GetLogicAnnotationCount();
	for (int i = count - 1; i >= 0; i--) 
	{
		LogicAnnoInfo* annInfo_ = pageViewMgr.logicAnnMananger->GetLogicAnnoInfo(i);
		if (annInfo_ == NULL || 
			(annInfo_->IsNotepadAnnotation() == false && 
			 annInfo_->IsTextAnnotation() == false)) 
		{
			continue;
		}
		
		CGRect rect = pageViewMgr.logicAnnMananger->GetLogicAnnotationRect(i);
		if (CGRectContainsPoint(rect, point))
		{
			annIndex = pageViewMgr.logicAnnMananger->GetLogicAnnotationIndex(i);
			annoRect = rect;
			break;
		}
	}
	
	return annoRect;
}

- (void) showSelectTextGhostView
{
	[self hideSelectTextGhostView];
	
	DWScrollView* pageView = [self getActivePageView];
	CGRect pageRect = CGRectZero;
	if (selectInfo_.isLeftPage == YES) 
	{
		pageRect = pageView.page.m_PageInfoA.m_SrcRect;
	}
	else
	{
		pageRect = pageView.page.m_PageInfoB.m_SrcRect;
	}
	
	CGRect targetRect = CGRectZero;
	if (selectInfo_.annoIndex < 0)
	{
		CGRect rect = CGRectMake(selectInfo_.start.x, selectInfo_.start.y, 0, 0);
		rect = [self transformRectFromMMToPixel:rect];
		selectInfo_.startPixel = rect.origin;
		
		rect = CGRectMake(selectInfo_.end.x, selectInfo_.end.y, 0, 0);
		rect = [self transformRectFromMMToPixel:rect];
		selectInfo_.endPixel = rect.origin;
		
		[selectInfo_.pixRects removeAllObjects];
		for (int i = 0; i < selectInfo_.mmRects.count; i++) 
		{
			CGRect mmRect = [[selectInfo_.mmRects objectAtIndex:i] CGRectValue];
			CGRect pixRect = [self transformRectFromMMToPixel:mmRect];
			[selectInfo_.pixRects addObject:[NSValue valueWithCGRect:pixRect]];
			
			if (i == 0) 
			{
				targetRect = pixRect;
			}
		}
		
		DWSelectGhostView *ghostView = [[DWSelectGhostView alloc] initWithFrame:pageRect 
																	 selectInfo:selectInfo_];
		ghostView.delegate = self;
		ghostView.backgroundColor = [UIColor clearColor];
		ghostView.tag = TAG_SELECT_PAGE_VIEW;
		[pageView.page addSubview:ghostView];
		[ghostView release];
		
		[self showCopyMenuWithTargetRect:targetRect inView:ghostView];
	}
	else
	{
		CGRect ghostRect = [self transformRectFromMMToPixel:selectInfo_.rect 
												andLeftPage:selectInfo_.isLeftPage];
		if ([self UIDeviceIsPortrait] == NO && pageView.isFacingPage == YES) 
		{
			float MAXPageWidth	= pageRect.origin.x + pageRect.size.width;
			float MAXPageHeight	= pageRect.origin.y + pageRect.size.height;
			
			if (ghostRect.origin.x <= pageRect.origin.x) 
			{
				ghostRect.size.width -= abs(pageRect.origin.x - kFacePageEdgeWidth - ghostRect.origin.x);
				ghostRect.origin.x = pageRect.origin.x - kFacePageEdgeWidth;
			}
			
			if (ghostRect.origin.y <= pageRect.origin.y) 
			{
				ghostRect.size.height -= abs(pageRect.origin.y - kFacePageEdgeWidth - ghostRect.origin.y);
				ghostRect.origin.y = pageRect.origin.y - kFacePageEdgeWidth;
			}
			
			if (ghostRect.origin.x + ghostRect.size.width >= MAXPageWidth) 
			{
				ghostRect.size.width = MAXPageWidth - ghostRect.origin.x + kFacePageInterval;
			}
			
			if (ghostRect.origin.y + ghostRect.size.height >= MAXPageHeight) 
			{
				ghostRect.size.height = MAXPageHeight - ghostRect.origin.y + kFacePageEdgeWidth;
			}
		}
		
		DWAnnBorderGhostView * borderGhostView = [[DWAnnBorderGhostView alloc] initWithFrame:ghostRect 
																				 borderColor:nil 
																				   zoomScale:pageView.zoomScale];
		borderGhostView.tag = TAG_SELECT_ANNOTATION_VIEW;
		[pageView.page addSubview:borderGhostView];
		[borderGhostView release];
		
		[self showCopyMenuWithTargetRect:ghostRect inView:pageView.page];
	}
	
	isSelectGhostShowing = YES;
}

- (void) restoreCopyMenu
{
	if (isSelectGhostShowing == YES) 
	{
		DWScrollView* pageView = [self getActivePageView];
		UIView *ghostView_ = [pageView.page viewWithTag:TAG_SELECT_ANNOTATION_VIEW];
		if (ghostView_ != nil) 
		{
			[self showCopyMenuWithTargetRect:ghostView_.frame inView:pageView.page];
		}
		else
		{
			ghostView_ = [pageView.page viewWithTag:TAG_SELECT_PAGE_VIEW];
			if (ghostView_ != nil) 
			{
				CGRect rect = [[selectInfo_.mmRects objectAtIndex:0] CGRectValue];
				rect = [self transformRectFromMMToPixel:rect];
				[self showCopyMenuWithTargetRect:rect inView:ghostView_];
			}
		}
	}
}

- (void) cancelSelectModeWithGesture:(UIGestureRecognizer *)gestureRecognizer
{
	if (isSelectGhostShowing)
	{
		DWScrollView* pageView = [self getActivePageView]; 
		CGPoint touchPoint = [gestureRecognizer locationInView:pageView.page];
		
		BOOL cancelSelectMode = YES;
		
		if (selectInfo_.annoIndex < 0)
		{
			for (int i = 0; i < [selectInfo_.mmRects count]; i++) 
			{
				CGRect rect = [[selectInfo_.mmRects objectAtIndex:i] CGRectValue];
				rect = [self transformRectFromMMToPixel:rect andLeftPage:selectInfo_.isLeftPage];
				
				if (CGRectContainsPoint(rect, touchPoint)) 
				{
					cancelSelectMode = NO;
					break;
				}
			}
		}
		else
		{
			CGRect rect = CGRectMake(touchPoint.x, touchPoint.y, 0, 0);
			rect = [self transformRectFromPixelToMM:rect andLeftPage:selectInfo_.isLeftPage];
			if (CGRectContainsRect(selectInfo_.rect, rect))
			{
				cancelSelectMode = NO;
			}
		}
		if (cancelSelectMode == YES) {
			[self cancelSelectMode];
		}
		else
		{
			UIMenuController *menu = [UIMenuController sharedMenuController];
			[menu setMenuVisible:YES animated:NO];
		}
	}
}

- (void) cancelSelectMode
{
	[self hideSelectTextGhostView];
	[self hideCopyMenu];
	isSelectGhostShowing = NO;
}

- (void) hideSelectTextGhostView
{
	if (isSelectGhostShowing == NO) 
		return;
	
	DWScrollView* pageView = [self getActivePageView];
	UIView *ghostView = [pageView.page viewWithTag:TAG_SELECT_PAGE_VIEW];
	if (ghostView != nil) 
	{
		[ghostView removeFromSuperview];
	}
	
	ghostView = [pageView.page viewWithTag:TAG_SELECT_ANNOTATION_VIEW];
	if (ghostView != nil) 
	{
		[ghostView removeFromSuperview];
	}
}

- (void) showCopyMenuWithTargetRect:(CGRect)targetRect 
							 inView:(UIView*)targetView
{
	if (targetView != nil && [targetView becomeFirstResponder])
	{
		UIMenuController *menu = [UIMenuController sharedMenuController];
		[menu setTargetRect:targetRect inView:targetView];
		[menu setMenuVisible:YES animated:YES];
	}
}

- (void) hideCopyMenu
{
	UIMenuController *menu = [UIMenuController sharedMenuController];
	[menu setMenuVisible:NO animated:YES];
}

// tongtx 2012.04.01 start
// 選択機能の追加
- (void) restoreSelectTextGhostViewForRotation
{
	if (isSelectGhostShowing == YES) 
	{
		int pageIndex = [self transformPageViewIndexToPageIndex:pageViewMgr.pageIndex];
		if (pageIndex != selectInfo_.pageIndex) 
		{
			isSelectGhostShowing = NO;
			return;
		}
		else
		{
			if (pageViewMgr.fontOrient == YES)
			{
				selectInfo_.isLeftPage = YES;
			}
			else
			{
				selectInfo_.isLeftPage = NO;
			}
		}
				
		if ([self UIDeviceIsPortrait] == YES)
		{
			selectInfo_.isLeftPage = YES;
		}
		
		[self showSelectTextGhostView];
	}
}
// tongtx 2012.04.01 end

#pragma mark - 
#pragma mark select ghostview delegate.
- (void)ghostViewWillBeginDragging:(DWSelectGhostView*)ghostView
{
	bgScrollView.scrollEnabled = NO;
	DWScrollView* pageView_ = [self getActivePageView];
	if (pageView_.zoomScale != 1.0) 
	{
		pageView_.scrollEnabled = NO;
	}
}

- (void)ghostViewWillEndedDragging:(DWSelectGhostView*)ghostView;
{
	bgScrollView.scrollEnabled = YES;
	DWScrollView* pageView_ = [self getActivePageView];
	if (pageView_.zoomScale != 1.0) 
	{
		pageView_.scrollEnabled = YES;
	}
}

- (void)ghostView:(DWSelectGhostView*)ghostView changeSelectionWithDragPoint:(DRAG_POINT)point
{
	// 1. transform pos from pix to mm.
	if (point == kDragPointLeft)
	{
		CGRect rect = CGRectMake(selectInfo_.startPixel.x, selectInfo_.startPixel.y, 0, 0);
		rect = [self transformRectFromPixelToMM:rect];
		selectInfo_.start = rect.origin;
	}
	
	if (point == kDragPointRight)
	{
		CGRect rect = CGRectMake(selectInfo_.endPixel.x, selectInfo_.endPixel.y, 0, 0);
		rect = [self transformRectFromPixelToMM:rect];
		selectInfo_.end = rect.origin;
	}
	
	BOOL result = [pageViewMgr selectTextInPage:selectInfo_];
	if (result == YES) 
	{
		// 3. update pix rect.
		[selectInfo_.pixRects removeAllObjects];
		for (int i = 0; i < selectInfo_.mmRects.count; i++) 
		{
			CGRect mmRect = [[selectInfo_.mmRects objectAtIndex:i] CGRectValue];
			CGRect pixRect = [self transformRectFromMMToPixel:mmRect];
			[selectInfo_.pixRects addObject:[NSValue valueWithCGRect:pixRect]];
		}
		
		// 4. update drag point pos.
		[ghostView setLeftDragPointPos];
		[ghostView setRightDragPointPos];

		// 5. refresh ghost view.
		[ghostView setNeedsDisplay];
	}
}

#pragma mark - 
#pragma mark copy menu delegate.
- (void) copy:(id)sender
{
	if ([pageViewMgr getPermissionForCopy] == YES) 
	{
		UIPasteboard *pasteBoard = [UIPasteboard generalPasteboard];
		pasteBoard.string = selectInfo_.text;
	}
	else
	{
		UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
															message:NSLocalizedString(@"MSG_FORBID_TO_COPY_TEXT", nil) 
														   delegate:nil
												  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK",nil)
												  otherButtonTitles:nil];
		[alertView show];
		[alertView release];
	}
	
	[self cancelSelectMode];
}
// tongtx 2012.03.23 end

#pragma mark - 
#pragma mark common method.
- (BOOL) isTouchInLeftPage:(CGPoint)point
{
	DWScrollView* pageView = [self getActivePageView];
	if (pageView == nil) return YES;
	
	BOOL isLeftPage = YES;
	if (pageView.isFacingPage == YES)
	{
		float firstPageOriginX = pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageWidth   = firstPageOriginX + pageView.page.m_PageInfoA.m_SrcRect.size.width;
		
		if (point.x < firstPageWidth)
		{
			isLeftPage = YES;
		}
		else
		{
			isLeftPage = NO;
		}
	}
	
	return isLeftPage;
}

- (BOOL) isPageInPageViewLeft:(int)pageIndex
{
	BOOL isLeftPage = YES;
	
	int index = pageIndex;
	if (pageViewMgr.facingMode == MODE_FACE_NO)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			isLeftPage = YES;
		} 
		else
		{
			if (pageViewMgr.fontOrient == YES)
			{
				if (index % 2 == 0)
				{
					isLeftPage = YES;
				}
				else
				{
					isLeftPage = NO;
				}
			}
			else
			{
				if (index % 2 == 0)
				{
					isLeftPage = NO;
				}
				else
				{
					isLeftPage = YES;
				}
			}
		}
	}
	else if (pageViewMgr.facingMode == MODE_FACE_YES)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			isLeftPage = YES;
		} 
		else
		{
			if (pageViewMgr.fontOrient == YES)
			{
				if (index == 0)
				{
					isLeftPage = YES;
				} 
				else
				{
					if (index % 2 == 1)
					{
						isLeftPage = YES;
					}
					else
					{
						isLeftPage = NO;
					}
				}
			}
			else
			{
				if (index == pageViewMgr.pageTotalCount - 1) 
				{
					isLeftPage = YES;
				} 
				else 
				{
					if (index % 2 == 1)
					{
						isLeftPage = NO;
					}
					else
					{
						isLeftPage = YES;
					}
				}
			}
		}
	}
	
	DWScrollView* pageView_ = [self getActivePageView];
	if (pageView_.isFacingPage == NO)
	{
		isLeftPage = YES;
	}
	
	return isLeftPage;
}

- (int) transformPageViewIndexToPageIndex:(int)pageViewIndex
{
	int pageIndex = 0;
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		pageIndex = pageViewIndex;
	}
	else if (pageViewMgr.facingMode == MODE_FACE_NO)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageIndex = 0;
		} 
		else
		{
			pageIndex = pageViewIndex * 2;
		}
	}
	else if (pageViewMgr.facingMode == MODE_FACE_YES)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageIndex = 0;
		} 
		else
		{
			if (pageViewIndex == 0)
			{
				pageIndex = pageViewIndex;
			}
			else
			{
				pageIndex = pageViewIndex * 2 - pageViewIndex % 2;
			}
		}
	}
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageIndex = pageViewIndex;
	}
	
	return pageIndex;
}

- (int) transformPageIndexToPageViewIndex:(int)pageIndex
{
	int pageViewIndex = pageIndex;
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		pageViewIndex = pageIndex;
	}
	else if (pageViewMgr.facingMode == MODE_FACE_NO)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageViewIndex = 0;
		} 
		else
		{
			pageViewIndex = pageIndex / 2;
		}
	}
	else if (pageViewMgr.facingMode == MODE_FACE_YES)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageViewIndex = 0;
		} 
		else
		{
			if (pageIndex == 0)
			{
				pageViewIndex = pageIndex;
			}
			else
			{
				pageViewIndex = pageIndex / 2 + pageIndex % 2;
			}
		}
	}
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageViewIndex = pageIndex;
	}
	
	return pageViewIndex;
}

- (CGRect) transformRectFromMMToPixel:(CGRect)rect
{
	CGRect result = CGRectZero;
	
	DWScrollView* pageView = [self getActivePageView];
	
	long scale			= pageView.page.m_PageInfoA.m_PageFitScale;
	result.origin.x		= Utility::MMToPixelWithScale(rect.origin.x, scale);
	result.origin.y		= Utility::MMToPixelWithScale(rect.origin.y, scale); 
	result.size.width	= Utility::MMToPixelWithScale(rect.size.width, scale);
	result.size.height	= Utility::MMToPixelWithScale(rect.size.height, scale);
	
	return result;
}

- (CGRect) transformRectFromPixelToMM:(CGRect)rect
{
	CGRect result = CGRectZero;
	
	DWScrollView* pageView = [self getActivePageView];
	
	long scale			= pageView.page.m_PageInfoA.m_PageFitScale;
	result.origin.x		= Utility::PixelToMMWithScale(rect.origin.x, scale);
	result.origin.y		= Utility::PixelToMMWithScale(rect.origin.y, scale); 
	result.size.width	= Utility::PixelToMMWithScale(rect.size.width, scale);
	result.size.height	= Utility::PixelToMMWithScale(rect.size.height, scale);
	
	return result;
}

- (CGRect) transformRectFromPixelToMM:(CGRect)rect andLeftPage:(BOOL)left
{
	CGRect result = CGRectZero;
	
	DWScrollView* pageView = [self getActivePageView];
	
	if (pageView.isFacingPage == NO)
	{
		float firstPageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
		result.origin.x			= rect.origin.x - firstPageOriginX;
		result.origin.y			= rect.origin.y - firstPageOriginY;
	}
	else if (left == YES) 
	{
		float firstPageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
		result.origin.x			= rect.origin.x - firstPageOriginX;
		result.origin.y			= rect.origin.y - firstPageOriginY;
	}
	else
	{
		float secondPageOriginX = pageView.page.m_PageInfoB.m_SrcRect.origin.x;
		float secondPageOriginY = pageView.page.m_PageInfoB.m_SrcRect.origin.y;
		result.origin.x			= rect.origin.x - secondPageOriginX;
		result.origin.y			= rect.origin.y - secondPageOriginY;
	}
	
	result = [self transformRectFromPixelToMM:result];
	
	return result;
}

- (CGRect) transformRectFromMMToPixel:(CGRect)rect andLeftPage:(BOOL)left
{
	CGRect result = CGRectZero;
	
	DWScrollView* pageView = [self getActivePageView];
	
	result = [self transformRectFromMMToPixel:rect];
	
	if (pageView.isFacingPage == NO)
	{
		float firstPageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
		result.origin.x			= result.origin.x + firstPageOriginX;
		result.origin.y			= result.origin.y + firstPageOriginY;
	}
	else if (left == YES)
	{
		float firstPageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
		float firstPageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
		result.origin.x			= result.origin.x + firstPageOriginX;
		result.origin.y			= result.origin.y + firstPageOriginY;
	}
	else
	{
		float secondPageOriginX = pageView.page.m_PageInfoB.m_SrcRect.origin.x;
		float secondPageOriginY = pageView.page.m_PageInfoB.m_SrcRect.origin.y;
		result.origin.x			= result.origin.x + secondPageOriginX;
		result.origin.y			= result.origin.y + secondPageOriginY;
	}
	
	return result;
}

- (int) getPageIndexWithPageViewIndex:(int)pageViewIndex andLeftPage:(BOOL)left
{
	int pageIndex = 0;
	if (pageViewMgr.facingMode == MODE_REGULAR)
	{
		pageIndex = pageViewIndex;
	}
	else if (pageViewMgr.facingMode == MODE_FACE_NO)
	{
		if (pageViewMgr.fontOrient == YES) 
		{
			if (pageViewMgr.pageTotalCount == 1) 
			{
				pageIndex = 0;
			} 
			else
			{
				if (left == YES)
				{
					pageIndex = pageViewIndex * 2;
				}
				else if ((pageViewIndex * 2 + 1) <= (pageViewMgr.pageTotalCount - 1))
				{
					pageIndex = pageViewIndex * 2 + 1;
				}
			}
		}
		else
		{
			if (pageViewMgr.pageTotalCount == 1) 
			{
				pageIndex = 0;
			} 
			else
			{
				if (left == YES)
				{
					if ((pageViewIndex * 2 + 1) <= (pageViewMgr.pageTotalCount - 1))
					{
						pageIndex = pageViewIndex * 2 + 1;
					}
					else
					{
						pageIndex = (pageViewMgr.pageTotalCount - 1);
					}
				}
				else
				{
					pageIndex = pageViewIndex * 2;
					
				}
			}
		}
	}
	else if (pageViewMgr.facingMode == MODE_FACE_YES)
	{
		if (pageViewMgr.pageTotalCount == 1) 
		{
			pageIndex = 0;
		} 
		else
		{
			if (pageViewMgr.fontOrient == YES) 
			{
				if (pageViewIndex == 0)
				{
					pageIndex = pageViewIndex;
				}
				else
				{
					if (left == YES)
					{
						pageIndex = pageViewIndex * 2 - pageViewIndex % 2;
					}
					else if ((pageViewIndex * 2 - pageViewIndex % 2 + 1) <= (pageViewMgr.pageTotalCount - 1))
					{
						pageIndex = pageViewIndex * 2 - pageViewIndex % 2 + 1;
					}
				}
			}
			else
			{
				if (pageViewIndex == 0)
				{
					pageIndex = pageViewIndex;
				}
				else
				{
					if (left == YES)
					{
						if ((pageViewIndex * 2 - pageViewIndex % 2 + 1) <= (pageViewMgr.pageTotalCount - 1))
						{
							pageIndex = pageViewIndex * 2 - pageViewIndex % 2 + 1;
						}
						else
						{
							pageIndex = (pageViewMgr.pageTotalCount - 1);
						}
					}
					else
					{
						pageIndex = pageViewIndex * 2 - pageViewIndex % 2;
						
					}
				}
			}
		}
	}
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageIndex = pageViewIndex;
	}
	
	return pageIndex;
}

// xujj 2012.04.01 start
// 検索機能の追加
#pragma mark - 
#pragma mark Indicator.
- (void) displayIndicator
{
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	if (isIndicatorAnimating == YES)
	{
		return;
	}
	
	activeIndicator_.center = self.view.center;
	
	[activeIndicator_ performSelectorInBackground:@selector(startAnimating)
									   withObject:nil];
	
	isIndicatorAnimating = YES;
}

- (void) hideIndicator
{
	
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	if (isIndicatorAnimating == NO)
	{
		return;
	}
	
	[self.view bringSubviewToFront:activeIndicator_];

	while (activeIndicator_.isAnimating == NO)
	{
		usleep(100000);
	}
	
	[activeIndicator_ stopAnimating];
	
	isIndicatorAnimating = NO;
}
// xujj 2012.04.01 end

@end
