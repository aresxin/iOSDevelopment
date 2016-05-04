//
//  DocumentViewController.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-18.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <MessageUI/MFMailComposeViewController.h>
#import "EnvironmentSettingsViewController.h"
#import "FacingSettingsViewController.h"
#import "FontSettingsViewController.h"
// SendEmail の対応 start
#import "CooperationSettingsViewController.h"
// SendEmail の対応 end
#import "AnnotationListViewController.h"
#import "PageViewManager.h"

// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
#import "XdwListinXbdViewController.h"
// 3.6 バインダ文書対応 の対応 end

// lixin 20110813 start
// ページ編集機能の追加  DW_iPhoneViewer_20
#import "DWEditFacingPageViewController.h"
// lixin 20110813 end

// tongtx 2012.03.23 start
// 選択機能の追加
#import "DWSelectGhostView.h"
// tongtx 2012.03.23 end

@protocol DocumentViewDelegate;//AR No.17581 by sun.chl 2010.12.17

enum MOVE_PAGE_MODE
{
	MODE_PAGE_SCROLL = 0,
	MODE_PAGE_NUMBER,
	MODE_PAGE_SLIDER,
	MODE_PAGE_OTHER
};

@class AnnotationListViewController;

// 「環境設定ボタンの削除」の対応 start
//@class EnvironmentSettingsViewController;
// 「環境設定ボタンの削除」の対応 end

@class FacingSettingsViewController;
@class FontSettingsViewController;
// SendEmail の対応 start
@class CooperationSettingsViewController;
// SendEmail の対応 end
@class PageViewManager;
@class DWScrollView;
@class DWPageView;
@class DocumentSettingsManager;
@class LinkAnnotationManager;
@interface DocumentViewController : UIViewController<UIScrollViewDelegate, 
													 UITableViewDelegate, 
													 UIAlertViewDelegate,
                                                     UIActionSheetDelegate,
													 AnnotatinListViewDelegate,
                                                     // 「環境設定ボタンの削除」の対応 start
                                                     //EnvironmentSettingsViewDelegate,
                                                     // 「環境設定ボタンの削除」の対応 end
													 FacingSettingsViewDelegate,
													 FontSettingsViewDelegate,
													 // SendEmail の対応 start
													 CooperationSettingsViewDelegate,
													 // SendEmail の対応 end
													 UIDocumentInteractionControllerDelegate,
													 MFMailComposeViewControllerDelegate,
                                                     UITextFieldDelegate,  //AR No17624
                                                     DWEditFacingPageViewDelegate, // ページ編集機能の追加
                                                     XdwListViewDelegate,

													 // xujj 2012.03.22 start
													 // 検索機能の追加
													 UISearchBarDelegate,
													 // xujj 2012.03.22 end

													 // tongtx 2012.03.23 start
													 // 選択機能の追加
													 DWSelectGhostViewDelegate
													 // tongtx 2012.03.23 end
													 >
{
	//AR No.17581 by sun.chl 2010.12.17
	id <DocumentViewDelegate> delegate;
	BOOL					needkeepDocumentStatus;
	
	// 1. self property.
	DocumentSettingsManager *documentSettingsMgr;
	UINavigationController	*navigateController;
	PageViewManager			*pageViewMgr;
	
	NSString				*filePath;
	NSString				*fileName;
	BOOL					keepDocumentStatus;
	
	// liuqw 20110628 start
    // AR NO.17871 の対応
	BOOL					isCanSaveSettings;
	// liuqw 20110628 end
	CGPoint					pageViewOffset;
	int						pageViewPos;
	int						preViewPos;
	int						pageNumber;
	CGPoint					pageOffset;
	// FileSort の対応 start
	int						fileSortItemIndex;
	int						fileSortModeIndex;
	// FileSort の対応 end
	
	// 2. navigation bar item.
	// liuqw 20110801 start
    // ページ編集機能の追加
	NSString				*backButtonTitle_;
	UIBarButtonItem			*buttonCommentsList;
	NSString				*srcEditFilePath;
    NSString				*tmpEditFilePath;
	UIPopoverController		*editFacingPageViewPopController;
	DWEditFacingPageViewController* editFacingPageViewController;
	CGRect					chooseEditPageIndexViewRect;
	BOOL					showChooseEditPageIndexView;
	// liuqw 20110801 end
	
	// liuqw 20110627 start
    // AR NO.17873 の対応
	BOOL					annoListEnabled;
	// liuqw 20110627 end
	AnnotationListViewController *annotationListViewController;
	CGRect					annotationListViewControllerRect;
	BOOL					showAnnotationList;
	
	UIView					*annotationListView;
	CGRect					annotationListViewRect;
	
	// add by lixin 20101205 AR.65
	UIView					*annotationListBackgroundView;
	CGRect					annotationListBackgroundViewRect;
	
	UIView					*annotationListTitle;
	CGRect					annotationListTitleRect;
	
	UILabel					*kindTitle;
	CGRect					kindTitleRect;
	
	UILabel					*numberTitle;
	CGRect					numberTitleRect;
	
	UILabel					*contentTitle;
	CGRect					contentTitleRect;
	
	UIView					*separatorView;
	CGRect					separatorViewRect;
	
	// バインダ文書対応 の対応 start
	// change by lixin 20110608
	BOOL					binderListEnabled;
	XdwListinXbdViewController* xdwDocListViewController;
	BOOL					showXdwDocList;
	
	UIView					*xdwDocListTitle;
	UIView					*xdwDocListView;
	UIView					*xdwDocListBackgroundView;
	
	UILabel					*docNameTitle;
	CGRect					docNameTitleRect;
	
	UILabel					*docNumberTitle;
	CGRect					docNumberTitleRect;
	
	UIView					*xdwDocSeparatorView;
	// バインダ文書対応 の対応 end
	
	
	// 3. tool bar item.
	NSMutableArray			*horizontalToolbarItems;
	NSMutableArray			*verticalToolbarItems;
	BOOL					hideToolbar;

	FacingSettingsViewController *facingSettings;
	CGRect					facingSettingsRect;
	BOOL					showFacingSettings;
	UIBarButtonItem			*facingButtonItem;
	UIPopoverController		*facingPopMenu;
	
	FontSettingsViewController *fontSettings;
	CGRect					fontSettingsRect;
	BOOL					showFontSettings;
	UIBarButtonItem			*fontButtonItem;
	UIPopoverController		*fontPopMenu;
	
	CooperationSettingsViewController *cooperationSettings;
	UIDocumentInteractionController   *docInteractionController;
	BOOL					showCooperationSettings;
	UIBarButtonItem			*cooperationButtonItem;
	UIPopoverController		*cooperationPopMenu;
	
	UIBarButtonItem			*annoButtonItem;
	
	// 「拡大率指定ボタンの追加」の対応 start
    UIBarButtonItem			*zoomSettingButtonItem;
	UIAlertView				*alertInputScale;
    UITextField				*fieldInputScale;
    UILabel					*labelScalePercent;
    int						specifyScaleModeIndex;
    int						specifyScaleValue;
	// 「拡大率指定ボタンの追加」の対応 end
	
	// 4. page number label.
	UIButton				*pageNumberLabel;
	UIView					*pageNumBackView;
	CGRect					pageNumberLabelRect;
	
	// 5. slider label.
	UISlider				*sliderLabel;
	CGRect					sliderLabelRect;
	UIView*					bgToolTip; 
	UILabel*				labelToolTip;
	
	// 6. background scrollview.
	UIScrollView			*bgScrollView;
	CGRect					scrollViewRect;
	
    // 7. link annotation.
	LinkAnnotationManager	*linkAnnotationManager;
	UIAlertView				*pageAlert;
	UITextField				*pageAlertTextField;
	UIAlertView				*linkAlert;
	UIView					*linkShadowView;
	CGPoint					centerPoint;
	CGFloat					statusRectHeight;
	
	
	// 8. page view settings.
	// 2012.02.01(Ver2.1 New) M.Chikyu
	UIActivityIndicatorView	*activeIndicator_;
	// 2012.02.01(Ver2.1 New) M.Chikyu
	UITapGestureRecognizer	*singleTapGestureRecognizer;
	UITapGestureRecognizer	*doubleTapGestureRecognizer;
	UITapGestureRecognizer	*twoFingerTapGestureRecognizer;
	// 「リンクアノテーションジャンプ方法」変更の対応 start
	//UILongPressGestureRecognizer	*longPressTapGestureRecognizer;
    // 「リンクアノテーションジャンプ方法」変更の対応 end
	UIPanGestureRecognizer	*panGestureRecognizer;
	BOOL					isRotate;
	BOOL					isPortraitBeforePortrait;
	BOOL					isResetSubviewing;
    
    // 9. link from other application.
	// tongtx 2011/08/16 start
	// Briefcaseと連携機能の追加
	BOOL					fromBriefCase;
	UIActionSheet			*displayActionSheet;
	// tongtx 2011/08/16 end
	
	// tongtx 20110926 start
	// NS-AR038 start
	BOOL					isBriefCaseUTIVisible;
	// tongtx 20110926 end
	
    // tongtx 20120206 start
    // MTA連動機能の対応
    BOOL					fromMTA;
    NSString*				appnameFromMTA_;
    BOOL					isMTAUTIVisible;
    NSString*				folderNameFromMTA_;
    NSString*				pasteboardFromMTA_;
    // tongtx 20120206 end
	
	// 「環境設定ボタンの削除」の対応 start
	//EnvironmentSettingsViewController *environmentSettings;
	//UIButton	*envSettingButton;
	//UIBarButtonItem *envSettingButtonItem;
    // 「環境設定ボタンの削除」の対応 end
	
	// lixin 2011/09/29 start 
	// 単色アイコンボタンの実装変更 の対応
	/*
	 UIButton	*fontButton;
	 UIButton	*annoButton;
	 UIButton	*facingButton;
	 
	 // 「拡大率指定ボタンの追加」の対応 start
	 UIButton	*zoomSettingButton;
	 // 「拡大率指定ボタンの追加」の対応 end
	 */
	// lixin 2011/09/29 end

    // liuqw 20110627 start
    // AR NO.17873 の対応
	//int positionAnnotCount;
    // liuqw 20110627 end
	
	
	// 20110407 M.Chikyu start
	// Viewの変更により削除
	
	/*
	 // M.Chikyu 20110311 start
	 // スクロールが不適切な位置で止まる不具合を修正
	 BOOL isSCRPage;
	 // M.Chikyu 20110311 end
	 */
	
	// 20110407 M.Chikyu end
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	UISearchBar		*searchBar_;
	
	BOOL			isSearchBarShowing;
	BOOL			isSearchOrientation;
	
	NSMutableArray	*searchToolbarItems_;
	
	int				searchStartPageIndex;
	int				searchStartAnnoIndex;
	int				ghostViewPageIndex;
	
	CGRect			searchGhostViewRect;
	
	DWSearchInfo	*searchInfo_;
	
	BOOL			isIndicatorAnimating;
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	UILongPressGestureRecognizer	*longPressTapGestureRecognizer;
	DWSelectInfo	*selectInfo_;
	BOOL			isSelectGhostShowing;
	// tongtx 2012.03.23 end
	
}
@property (nonatomic, readonly) PageViewManager* pageViewMgr;
@property (nonatomic, retain) NSString *filePath;
@property (nonatomic, retain) NSString *fileName;
@property (nonatomic, assign) int pageViewPos;
@property (nonatomic, assign) int preViewPos;
@property BOOL keepDocumentStatus;

// FileSort の対応 start
@property int fileSortItemIndex;
@property int fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@property (nonatomic, retain) UIAlertView *alertInputScale;
@property (nonatomic, retain) UITextField *fieldInputScale;
@property (nonatomic, retain) UILabel     *labelScalePercent;
// 「拡大率指定の追加」の対応 end

// liuqw 20110628 start
// AR NO.17871 の対応
@property BOOL isCanSaveSettings;
// liuqw 20110628

// tongtx 2011/10/21 start
// NS-AR2008 の対応
@property BOOL fromBriefCase;
// tongtx 2011/10/21 end

// tongtx 20120206 start
// MTA連動機能の対応
@property BOOL isFromMTA;
@property (nonatomic, retain) NSString *appnameFromMTA;
@property (nonatomic, retain) NSString *folderNameFromMTA;
@property (nonatomic, retain) NSString *pasteboardFromMTA;
// tongtx 20120206 end

// 20110407 M.Chikyu start
// Viewの変更により削除

/*
 // M.Chikyu 20110311 start
 // スクロールが不適切な位置で止まる不具合を修正
 @property (nonatomic, readonly) UIScrollView *bgScrollView;
 @property BOOL isSCRPage;
 // M.Chikyu 20110311 end
 */

// 20110407 M.Chikyu end

//AR No.17581 
@property (nonatomic, assign) id <DocumentViewDelegate> delegate;

// liuqw 20110801 start
// ページ編集機能の追加
@property (nonatomic, retain) NSString* backButtonTitle;
// liuqw 20110801 end

// tongtx 20110916 start
// NS-AR024 の対応
@property (nonatomic, retain) UIActionSheet *displayActionSheet;
// tongtx 20110916 end


#pragma mark -
#pragma mark init

// xuxinjun 2012.03.23 start
// 保護文書の対応
//- (id)initWithPath:(NSString *)documentPath;
- (id)initWithPath:(NSString *)path andOpenPassword:(NSString*)pwd;
// xuxinjun 2012.03.23 end


#pragma mark -
#pragma mark init property value.
- (void) initPropertyValueWithKeepStatus:(BOOL)status;
// liuqw 20110627 start
// AR NO.17873 の対応
- (void) initRightBarButtonItemEnabledProperty;
- (int)  getAnnotationCountInDocument;
- (void) setRightBarButtonItenEnabledWithIsBinderDoc:(BOOL)isBinder;
// liuqw 20110627 end


#pragma mark -
#pragma mark init gui.
- (void) initToolbarStyle;
- (void) initMainFrame;
- (void) initViewControls;
- (void) initViewControlsRect;
- (void) initPageNumberlabelRect;
- (void) initToolbarButton:(UIButton*)button 
			  withIconName:(NSString*)name 
				withAction:(SEL)action;


#pragma mark -
#pragma mark mehtod about pageview
- (DWScrollView*) getActivePageView;
- (DWScrollView*) getPageViewWithPosition:(int)pos;
- (void) insertPageViewWithPosition:(int)pos;
- (void) removePageViewsFromScrollView;
// ページ移動仕様の変更の対応 start
//- (void) removeOtherPageViews;
// ページ移動仕様の変更の対応 end
- (void) updateScrollViewContentSize;
- (void) setPageContentOffset:(CGPoint)offset;
- (CGPoint) getPageOffset;


#pragma mark -
#pragma mark left bar item.
// liuqw 20110801 start
// ページ編集機能の追加
- (void) initLeftBarItem;
- (void) actionOnTouchLeftBarItem;
// liuqw 20110801 end


#pragma mark -
#pragma mark right bar item.
- (void) actionTouchAnnotationListButton;
// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
- (void) actionTouchSegmentControl:(id)sender;
- (void) actionTouchXdwDocListButton;
// 3.6 バインダ文書対応 の対応 end
// 「環境設定ボタンの削除」の対応 start
//- (void) actionTouchEnvironmentSettingsButton;
// 「環境設定ボタンの削除」の対応 end


#pragma mark -
#pragma mark toolbar item(edit button).
// liuqw 20110801 start
// ページ編集機能の追加
- (void) actionOnTouchEditButton;

// tongtx 20120206 start
// MTA連動機能の対応
- (BOOL) showPaymentNotice;
// tongtx 20120206 end

- (void) editPageViewWithButtonIndex:(int)buttonIndex;
// liuqw 20110801 end

// lixin 2011/09/28 start
// NS-AR1019 の対応
- (void) resetAnnnotationButtonStatus;
// lixin 2011/09/28 end

// liuqw 20110801 start
// ページ編集機能の追加
- (void) pushEditControllerWithPageIndex:(int)pageIndex;
// liuqw 20110801 end

#pragma mark -
#pragma mark action for finish editing.
// lixin 2011/09/19 start 
// NS-AR1006 の対応
- (void) resetLeftBarItem;
// lixin 2011/09/19 end

// liuqw 20110801 start
// ページ編集機能の追加
- (void) reloadAnnotationList;
- (BOOL) isTempFileUpdated;
- (void) updateControlStatusForRotation;
// liuqw 20110801 end


#pragma mark -
#pragma mark toolbar item(facing button).
- (void) actionTouchFacingSettingsButton;
- (void) actionFacingSettingsChanged:(int)index;


#pragma mark -
#pragma mark toolbar item(font button).
- (void) actionTouchFontOrientationSettingsButton;
- (void) actionFontSettingsChanged:(int)index;


#pragma mark -
#pragma mark toolbar item(cooperation button).
- (void) actionTouchCooperationButton;
// SendEmail の対応 start
- (void) actionTouchSendMailButton;
- (void) actionTouchOpenModeButton;
// SendEmail の対応 end


#pragma mark -
#pragma mark toolbar item(annotation on/off button).
- (void) actionTouchAnnotationOnOffButton;


#pragma mark -
#pragma mark toolbar item(zoom settings button).
// 「拡大率指定ボタンの追加」の対応 start
- (void) actionTouchZoomSettingsButton;
- (void) showZoomScaleInputView;
- (void) updateAlertInputScaleTitle;
- (void) setInputScaleFieldViewPosition;
- (void) setInputScaleFieldViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation;
- (void) inputZoomScaleWithAlertView:(UIAlertView*)alertView;
- (void) zoomPageViewToScale:(int)scale;
// 「拡大率指定ボタンの追加」の対応 end


#pragma mark -
#pragma mark page number label.
- (void) actionPageNumberLabelTouchDown;
- (void) updatePageNumberLabel:(int)position;
- (void) updatePageNumberBackGroundViewRect;
- (int)  getPageNumberWithPageViewPosition:(int)pos;
- (void)hidePageNumberLable:(BOOL)hidden;


#pragma mark -
#pragma mark slider bar.
- (void) actionSliderLabelDragEnter;
- (void) actionSliderLabelDragEnd;
- (void) actionSliderLabelValueChanging;
- (void) actionSliderLabelValueChanged;
// liuqw 20110323 start
// スライダーバーの不具合修正
//- (void) updateSliderLabel:(int)position;
- (void) updateSliderLabel:(float)position;
// liuqw 20110323 end
- (void) initToolTipRect;
- (void) addToolTipToSliderBar;
- (void) moveToolTipViewWithSliderBar;
- (void) removeToolTipToSliderBar;
- (CGRect) getToolTipViewPositon;


#pragma mark -
#pragma mark navigation bar and tool bar.
- (void) removeToolbarPopView;
- (void) performShowScreen;
- (void) cancelShowScreen;
- (void) hideAllToolbarItems:(NSNumber*)status;


#pragma mark -
#pragma mark action for move page.
- (void) actionMovePageWithPosition:(int)position
				   withMovePageMode:(MOVE_PAGE_MODE)mode;
- (void) actionMoveOnePageWithPosition:(int)position 
					  withMovePageMode:(MOVE_PAGE_MODE)mode;
- (void) actionMoveToNextPage:(BOOL)toNext;
- (BOOL) touchInPageCenterArea:(CGPoint)point;
- (void) actionTouchPageEdge:(CGPoint)point;
- (void) updateScrollIndicatorPos:(int)position animated:(BOOL)animated;

// lixin 20110626 DW_iPhoneEnhance_12 start
// AR.17872 の対応 
- (NSString*) getBinderTitleWithPageIndex:(int)pageIndex;
// lixin 20110626 DW_iPhoneEnhance_12 end

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void)shiftNextPage;
- (void)shiftPrePage;
- (void)shiftPage:(DWScrollView*)pageView position:(int)pos;
// 2012.02.01(Ver2.1 New) M.Chikyu


#pragma mark -
#pragma mark action for zoom page.
- (void) actionDoubleTap:(UIGestureRecognizer *)gestureRecognizer;
- (void) actionTwoFingerTap:(UIGestureRecognizer *)gestureRecognizer; 
- (void) actionZoomInOutPageView:(BOOL)zoomIn withTouchPoint:(CGPoint)point;


#pragma mark -
#pragma mark action for single touch
- (void) actionSingleTap:(UIGestureRecognizer *)gestureRecognizer;
// 「リンクアノテーションジャンプ方法」変更の対応 start
- (void) actionOnTappedInPage:(UIGestureRecognizer *)gestureRecognizer;
// 「リンクアノテーションジャンプ方法」変更の対応 end


#pragma mark -
#pragma mark action for link annotation.
// 「リンクアノテーションジャンプ方法」変更の対応 start
- (BOOL) isTappedInLinkAnnotation:(UIGestureRecognizer *)gestureRecognizer;
// 「リンクアノテーションジャンプ方法」変更の対応 end

// AR NO.17516 の対応 start
- (CGRect) getLinkAnnotationRectWithAnnotationIndex:(int)index 
						   withAnnotationInLeftPage:(BOOL)inLeftPage;
- (LinkAnnotationManager*) getLinkAnnotManager:(int)linkAnnotationIndex;
// AR NO.17516 の対応 end

- (void) addShadowToLinkAnnotation:(CGRect)rect;
- (void) showLinkAnnotationAlert:(LinkAnnotationManager *)linkManager;
- (void) cleanLinkAnnotationShadow;
- (void) actionlinkToDestPostion;


#pragma mark -
#pragma mark action for page rotation.
- (void) actionDeviceRotationWithOrientation:(UIInterfaceOrientation)orientation;


#pragma mark -
#pragma mark common method.
- (int) convertPageViewPosition:(int)fromPos 
				   withFromMode:(FacingMode)fromMode 
					 withToMode:(FacingMode)toMode;
// AR17558 の対応 start
// delete files in inbox directory except showing file. add by lixin 20110221
- (void)deleteInboxFile;
// AR17558 の対応 end
- (BOOL) UIDeviceIsPortrait;

// tongtx 20110916 start
// NS-AR024 の対応
- (void)removeTopViews;
// tongtx 20110916 end

- (UIImage*) getToolbarButtonImageWithName:(NSString*)name;
// 「環境設定ボタンの削除」の対応 start
//- (NSString*) getEnvironmentSettingsIcon;
// 「環境設定ボタンの削除」の対応 end
- (NSString*) getFacingSettingsIcon;
- (NSString*) getFontSettingsIcon;
- (NSString*) getAnnotationOnOfIcon:(BOOL)on;
// 「拡大率指定ボタンの追加」の対応 start
- (NSString*) getZoomSettingsIcon;
// 「拡大率指定ボタンの追加」の対応 end
- (NSString*) getAnnotationListIcon;
- (NSString*) getBinderListIcon;
// lixin 2011/09/09 start 
// NS-AR012 の対応
- (NSString*) getActionIcon;
// lixin 2011/09/09 end


#pragma mark -
#pragma mark link from other application.
// liuqw 2012/03/06 start
// AR NO.19019の対応
//- (BOOL) saveFileFromBriefcase;
- (BOOL) saveEditedFileToLocalDocument;
// liuqw 2012/03/06 end

- (void) interacionWithBriefCase;
- (BOOL) isInteracionDocumentUpdated;

// tongtx 20120206 start
// MTA連動機能の対応
- (void) returnToAssociateApplicationWithUTI;
//- (void) returnToBriefCaseWithIsUpdated:(BOOL)updated;
- (void) returnToAssociateApplicationWithIsUpdated:(BOOL)updated;
//- (BOOL) isBriefcaseCanOpenWithIsUpdated:(BOOL)updated ;
- (BOOL) isAssociateApplicationCanOpenWithIsUpdated:(BOOL)updated;
// tongtx 20120206 end


// xuxinjun 2012.03.23 start
// パーミッションの対応.
#pragma mark -
#pragma mark Payment.
- (BOOL) hasMakePayment;
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
#pragma mark - 
#pragma mark search text
- (void) actionTouchSearchButton;
- (void) actionTouchFrontSearchButton;
- (void) actionTouchNextSearchButton;

- (void) searchDestTextFromAllPages:(BOOL)toNext withIsEnd:(BOOL)end;
- (void) setSearchBarCancelButtonEnabled;

- (void) showSearchTextGhostView:(DWScrollView*)pageView andLeft:(BOOL)left;
- (void) hideSearchTextGhostView;

- (void) restoreSearchTextGhostViewForMovePage:(int)position;

- (void) actionOnKeyboardDidHidden;
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
#pragma mark - 
#pragma mark select text
- (CGRect) getAnnotationRectWithPageIndex:(int)index 
							andTouchPoint:(CGPoint)point 
							 andAnnoIndex:(int&)annIndex;

- (void) showSelectTextGhostView;
- (void) hideSelectTextGhostView;

- (void) showCopyMenuWithTargetRect:(CGRect)targetRect inView:(UIView*)targetView;
- (void) hideCopyMenu;

- (void) restoreSelectTextGhostViewForRotation;
- (void) restoreCopyMenu;

- (void) cancelSelectModeWithGesture:(UIGestureRecognizer*)gestureRecognizer;
- (void) cancelSelectMode;
// tongtx 2012.03.23 end

// liuqw 2012.03.23 start
#pragma mark - 
#pragma mark common method.
- (BOOL) isTouchInLeftPage:(CGPoint)point;
- (BOOL) isPageInPageViewLeft:(int)pageIndex;
- (int) transformPageViewIndexToPageIndex:(int)pageViewIndex;
- (int) transformPageIndexToPageViewIndex:(int)pageIndex;
- (CGRect) transformRectFromMMToPixel:(CGRect)rect;
- (CGRect) transformRectFromPixelToMM:(CGRect)rect;
- (CGRect) transformRectFromPixelToMM:(CGRect)rect andLeftPage:(BOOL)left;
- (CGRect) transformRectFromMMToPixel:(CGRect)rect andLeftPage:(BOOL)left;
- (int) getPageIndexWithPageViewIndex:(int)pageViewIndex andLeftPage:(BOOL)left;


#pragma mark - 
#pragma mark Indicator.
- (void) displayIndicator;
- (void) hideIndicator;

// liuqw 2012.03.23 end
@end

//AR No.17581
@protocol DocumentViewDelegate <NSObject>
@optional
- (void) saveDocumentStatusWithController:(DocumentViewController*)controller;
@end
