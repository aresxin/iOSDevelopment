//
//  PageViewManager.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-27.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DocumentHandle.h"
#import "LinkAnnotInfo.h"

// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
#import "XdwFileInfo.h"
// 3.6 バインダ文書対応 の対応 end


enum FacingMode {
	MODE_REGULAR = 0,
	MODE_FACE_NO,
	MODE_FACE_YES
};

enum DocumentType {
	DOC_TYPE_XDW = 0,
	DOC_TYPE_PDF,
	DOC_TYPE_NONE
};

enum PageStatus {
	PAGE_STATUS_FIT		= 0,
	PAGE_STATUS_FULL	= 1,
	PAGE_STATUS_ZOOM	= 2
};

/*
static const int kPageViewEdgeWidth = 5;
// 「先読む」機能の対応 start
static const float kPageEdgeWidth = 1;
static const float kShadowEdgeWidth = 2;
// 「先読む」機能の対応 end
static const int kFacePageEdgeWidth = 2;
// AR NO.17571 の対応 start
static const int kFacePageInterval = 2;
// AR NO.17571 の対応 end
// AR NO.17607の対応 start
static const float kPageFitMinScale = 0.95;
static const float kPageFitMaxScale = 1.05;
// AR NO.17607の対応 end
*/
//static const float kShadowEdgeWidth = 2;
static const int kFacePageEdgeWidth = 2;
static const int kFacePageInterval = 2;

// xujj 2012.03.22 start
// 検索機能の追加
@interface DWSearchInfo : NSObject
@property int	pageIndex;
@property int   annoIndex;
@property int	startPageIndex;
@property int	endPageIndex;
@property BOOL	next;
@property (nonatomic, retain) NSString* text; 
@property (nonatomic, assign) NSMutableArray* mmSearchRects;
@property (nonatomic, assign) NSMutableArray* pixSearchRects;
@end
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
@interface DWSelectInfo : NSObject

@property int	 pageIndex;
@property int    annoIndex;
@property CGPoint start;
@property CGPoint startPixel;
@property CGPoint end;
@property CGPoint endPixel;
@property CGRect rect;
@property (nonatomic, assign) NSMutableArray* mmRects;
@property (nonatomic, assign) NSMutableArray* pixRects;
@property (nonatomic, retain) NSString* text;
@property float stepX;
@property float stepY;
@property BOOL isLeftPage;

@end
// tongtx 2012.03.23 end

struct DWPageInfo;
@class DWPageView;
@class DWScrollView;
@class DocumentViewController;
@class DWDrawer;

@interface PageViewManager : NSObject<UIScrollViewDelegate>
{
	DocumentViewController	*documentViewController;
	UIInterfaceOrientation	interfaceOrientation;
	NSString				*filePath;
	
	DocumentHandle			*handleDocument;
	DocumentType			documentType;
	int						pageTotalCount;
	
	// save document settings.
	int			pageIndex;
	long		pageScale;
	CGPoint		pageOffset;
	FacingMode	facingMode;
	BOOL		fontOrient;
	BOOL		showAnnotation;
	BOOL		isPageFit;
	
	BOOL		enableAnnotation;
	float		pageZoomScale;
	PageStatus	pageStatus;
	
	// for tiled layer's back ground.
	UIColor			*bgColor;

	// Graphic Drawer
	DWDrawer        *drawer;
	NSLock			*zoomOutLock;
	
	// for flick move page.
	// ページ移動仕様の変更の対応 start
	/*
	CGPoint			dragStartOffset;
	CGPoint			dragEndOffset;
	NSTimeInterval	dragStart;
	NSTimeInterval	dragEnd; 
	*/ 
	// ページ移動仕様の変更の対応 end
	
	// AR NO.17526 の対応 start
	//BOOL isZooming;
	// AR NO.17526 の対応 end
	
	// AR NO.17607 の対応 start
	BOOL isZoomEnd;
	// AR NO.17607 の対応 end
	
	// lixin 20110626 DW_iPhoneEnhance_12 start
	// AR.17872 の対応 
	BOOL isBinderDoc;
	// lixin 20110626 DW_iPhoneEnhance_12 end
    
    // liuqw 20110627 start
    // AR NO.17779 の対応
    BOOL hasSignature;
    // liuqw 20110627 end
    
    int documentVersion;
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	NSString	*openPassword_; 
	// xuxinjun 2012.03.23 end
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	MP_TextInfo	*textInfoInput;
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	LogicAnnotationManager* logicAnnMananger_;
	// tongtx 2012.03.23 end
}
@property UIInterfaceOrientation interfaceOrientation;
@property DocumentHandle *handleDocument;
@property DocumentType    documentType;
@property int		pageTotalCount;
@property int		pageIndex;
@property long		pageScale;
@property float		pageZoomScale;
@property CGPoint	pageOffset;
@property FacingMode facingMode;
@property BOOL		fontOrient;
@property BOOL		showAnnotation;
@property BOOL		enableAnnotation;
@property BOOL		isPageFit;
@property PageStatus pageStatus;
@property BOOL isBinderDoc;
@property BOOL hasSignature;
@property (nonatomic, assign) DWDrawer* dwDrawer;

// xuxinjun 2012.03.23 start
// 保護文書の対応
@property (nonatomic, retain) NSString *openPassword;
// xuxinjun 2012.03.23 end

// tongtx 2012.03.23 start
// 選択機能の追加
@property LogicAnnotationManager* logicAnnMananger;
// tongtx 2012.03.23 end

#pragma mark -
#pragma mark init manager.

// xuxinjun 2012.03.23 start
// 保護文書の対応
/*
 - (id) initWithDocumentViewController:(DocumentViewController*)controller 
 withDocumentPath:(NSString *)documentPath;
 */
- (id) initWithDocumentViewController:(DocumentViewController*)controller 
					 withDocumentPath:(NSString *)documentPath 
					 withOpenPassword:(NSString*)pwd;

/*
 - (BOOL) loadXDWDocument:(NSString *)documentPath;
 */
- (BOOL) loadXDWDocument:(NSString *)documentPath andOpenPassword:(NSString*)pwd;
// xuxinjun 2012.03.23 end

// get page view count.
- (int) getPageViewCount;

// liuqw 20120203 start
// AR NO.17926の対応
- (int) getPageViewCountAtFacingMode:(FacingMode)mode;
// liuqw 20120203 end

#pragma mark -
#pragma mark create new page view.
// create a new page views with index.
- (DWScrollView*) insertNewPageViewWithPageIndex:(int)index;

//  active current page view.
- (void) setPageViewActive:(DWScrollView*)pageView;

#pragma mark -
#pragma mark interface for page view zoom.
// zoom out page view with touch point.
- (void) zoomOutPageView:(DWScrollView*)pageView 
		  withTouchPoint:(CGPoint)point;

// zoom in page view with touch point.
- (void) zoomInPageView:(DWScrollView*)pageView 
		 withTouchPoint:(CGPoint)point;

// zoom pageview to pagefit status 
- (void) zoomPageViewToPageFit:(DWScrollView*)pageView;

// zoom page view for anntation jump.
- (void) zoomPageViewForAnnotationJump:(DWScrollView*)pageView 
					withAnnotationRect:(CGRect)rect 
			  withAnnotationInLeftPage:(BOOL)inLeftPage;

// zoom in or out page view.
- (void) zoomPageView:(DWScrollView *)pageView 
	   withTouchPoint:(CGPoint)point 
		withZoomScale:(float)scale 
			withInOut:(BOOL)zoomIn;

- (void) updatePageViewScaleToPageFit:(DWScrollView *)pageView;

// update page view with new scale.
- (void) updatePageViewScaleInfo:(DWScrollView *)pageView;

#pragma mark -
#pragma mark method for annotation On / Off.
// set annotation dispaly on / off.
- (void) setAnnotationDisplay:(BOOL)display;

#pragma mark -
#pragma mark method for get annotation list.
// get annotation info of all pages.
- (LinkAnnotInfoList*) getLinkAnnotationInfoList;

#pragma mark -
#pragma mark init new page view with regular.
// init page view with page index.
- (void) initPageView:(DWScrollView*)pageView 
		withPageIndex:(int)index; 

// init page with index and scale.
- (void) initPage:(DWPageView*)page 
	withPageIndex:(int)index;

// get DocuWorks page info.
- (DWPageInfo) getDWPageInfo:(int)pageNum;

// set link annotation index list to page view.
- (void) setLinkAnnotationIndexList:(DWScrollView*)pageView;

// set page layer property.
- (void)setLayerPropertyWithPageView:(DWPageView*)page;

#pragma mark -
#pragma mark init new page view with facing mode.
// init facing page view with page index.
- (void) initFacingPageView:(DWScrollView*)pageView 
			  withPageIndex:(int)index;

// get if facing page contain two pages.
- (BOOL) isFacingPageContainTowPages:(int)index;

// init facing page with page index. 
- (void) initFacingPage:(DWPageView*)page 
		  withPageIndex:(int)index;

// set one page info when facing page include one page.
- (void) setOneFacingPageInfo:(DWPageView*)page 
				withPageIndex:(int)index;

// set two page info when facing page include two pages.
- (void) setTwoFacingPageInfo:(DWPageView*)page 
		   withFirstPageIndex:(int)firstIndex 
		  withSecondPageIndex:(int)secondIndex;

#pragma mark -
#pragma mark get page size with scale.
// get page size with page mode.
- (CGSize) getPageSize:(int)index 
		 withPageScale:(long)scale 
		  withPageMode:(PageInfo::PAGE_MODE)mode;

#pragma mark -
#pragma mark method for get page info with regular.
// get page rect with scale.
- (CGRect) getPageRectWithIndex:(int)index 
				  withPageScale:(long)scale;

// 次ページの一部が表示されるの対応
- (CGSize) getPageMinSizeWithIndex:(int)index  
					 withPageScale:(long)scale;

- (CGFloat) getPageMinIntervalWithIndex:(int)index  
						  withPageScale:(long)scale;

// get page init content offset for pagefit(page) mode.
- (CGPoint) getPageContentOffsetWithIndex:(int)index 
						   withPageScale:(long)scale;

// get page out rect.
- (CGRect) getPageOuterRectWithIndex:(int)index 
					   withPageScale:(long)scale;

// get page rect at annotation show.
- (CGRect) getPageInnerRectWithIndex:(int)index 
					   withPageScale:(long)scale;

#pragma mark -
#pragma mark method for get page info with facing mode.
// get facing page scale with index.
- (long) getFacingPageScaleWithFirstIndex:(int)firstIndex 
					  withSecondPageIndex:(int)secondIndex
							withIsOnePage:(BOOL)onePage;

// get facing page view rect.
- (CGRect) getFacingPageViewRectWidthIndex:(int)index;

#pragma mark -
#pragma mark method for zoom page view.
- (void) updatePageViewStatusForZoom:(DWScrollView*)pageView 
					   withZoomScale:(float)scale 
				withRestoreToPageFit:(BOOL)restore;

// update page info while zoom page end.
- (void) updatePageInfo:(DWPageView*)page withZoomScale:(float)scale;

// get page fit status'scale.
- (long) getPageScaleWithIndex:(int)index withPageMode:(PageInfo::PAGE_MODE)mode;

// get page full mode zoom scale.
- (float) getPageFullZoomScale:(DWScrollView*)pageView;

- (float) getPageMaxZoomScale:(DWScrollView*)pageView;
- (long) getFacingPageScalewithIndex:(int)index;

// 拡大縮小操作時の不具合を修正
- (CGPoint) getPageCurrentOriginWithPageView:(DWScrollView*)pageView;
- (CGSize) getPageViewCurrentContentSizeWithPageView:(DWScrollView*)pageView;
- (void) resetPageViewContentSize:(DWScrollView*)pageView;

- (CGPoint) getPageOriginWithPageView:(DWScrollView*)pageView 
                        withZoomScale:(float)zoomScale;
- (CGSize) getPageViewContentSizeWithPageView:(DWScrollView*)pageView
                                withZoomScale:(float)zoomScale;


#pragma mark -
#pragma mark private method.
// get current screen rect.
- (CGRect) getScreenRect;

// if device is portrait.
- (BOOL) UIDeviceIsPortrait;

// get back ground image.
- (UIColor*) getBackGround;

// 3.6 バインダ文書対応 の対応 start
// change by lixin 20110608 DW_iPhoneEnhance_12
- (XdwFileInfo*) getBinderFileInfo;
// 3.6 バインダ文書対応 の対応 end

// ページ編集機能の追加
- (BOOL) loadXDWDocumentForUpdate:(NSString *)documentPath;
- (BOOL) reloadXDWDocument:(NSString *)documentPath;

- (BOOL) isDocumentVersionUpdated;
- (BOOL) saveDocumentUpdateContent;

- (void) returnToDisplayModeOnEndEditSuccess:(BOOL)succeed;
- (BOOL) isEditingFileErrorSaved;

- (BOOL) copyEditFileToTempDirectory;
- (BOOL) isTempFileEditing;
- (void) cleanTempDirectory;

- (NSString*) getFileFullName;

- (void) dealloc;


// xuxinjun 2012.03.23 start
// パーミッションの対応.
#pragma mark -
#pragma mark mehtod Get Doc Permission.
- (BOOL) getPermissionForAnnoEdition;
- (BOOL) getPermissionForCopy;
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
#pragma mark -
#pragma mark mehtod search text.
- (void) beginSearchText;
- (BOOL) searchText:(DWSearchInfo*)info;
- (void) endSearchText;
- (void) displaySearchTargetInPageView:(DWScrollView *)pageView 
						  withMoveRect:(CGRect)rect 
							  withLeft:(BOOL)left;
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
#pragma mark -
#pragma mark mehtod select text.
- (BOOL) selectTextInPage:(DWSelectInfo*)info;
// tongtx 2012.03.23 end
@end
