//
//  PageViewManager.m
//  DWViewer
//
//  Created by FX Neusoft on 10-10-27.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "PageViewManager.h"
#import "DWPageView.h"
#import "DWScrollView.h"
#import "PageInfo.h"
#import "XdwDocumentHandle.h"
#import "PDFDocumentHandle.h"
#import "DocumentRendering.h"
#import "RenderingListener.h"
#import "Utility.h"
#import "DWDrawer.h"
#import "XdwLinkManager.h"
#import "DocumentViewController.h"
#import "DWViewerGUIConst.h"

// xujj 2012.03.22 start
// 選択機能の追加
@implementation DWSearchInfo : NSObject
@synthesize	pageIndex;
@synthesize	annoIndex;
@synthesize startPageIndex;
@synthesize endPageIndex;
@synthesize next;
@synthesize	text;
@synthesize mmSearchRects;
@synthesize pixSearchRects;

- (id)init
{
	self = [super init];
	if (self)
	{
		mmSearchRects = [[NSMutableArray alloc] init];
		pixSearchRects = [[NSMutableArray alloc] init];
	}
	return self;
}

- (void) dealloc
{
	[text release];

	[mmSearchRects release];
	[pixSearchRects release];
	
	[super dealloc];
}
@end
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
@implementation DWSelectInfo : NSObject

@synthesize pageIndex;
@synthesize annoIndex;
@synthesize start;
@synthesize startPixel;
@synthesize end;
@synthesize endPixel;
@synthesize rect;
@synthesize mmRects;
@synthesize pixRects;
@synthesize text;
@synthesize stepX;
@synthesize stepY;
@synthesize isLeftPage;

- (id)init
{
	self = [super init];
	if (self) 
	{
		pageIndex	= 0;
		annoIndex	= -1;
		mmRects		= [[NSMutableArray alloc] init];
		pixRects	= [[NSMutableArray alloc] init];
		text		= nil;
		isLeftPage	= YES;
	}
	return self;
}

- (void)dealloc
{
	[mmRects release];
	[pixRects release];
	[text release];
	
	[super dealloc];
}
@end
// tongtx 2012.03.23 end

@implementation PageViewManager

@synthesize interfaceOrientation;
@synthesize handleDocument;
@synthesize documentType;
@synthesize pageTotalCount;
@synthesize pageIndex;
@synthesize pageScale;
@synthesize pageZoomScale;
@synthesize pageOffset;
@synthesize facingMode;
@synthesize fontOrient;
@synthesize showAnnotation;
@synthesize enableAnnotation;
@synthesize isPageFit;
@synthesize pageStatus;

// lixin 20110626 DW_iPhoneEnhance_12 start
// AR.17872 の対応 
@synthesize isBinderDoc;
// lixin 20110626 DW_iPhoneEnhance_12 end

// liuqw 20110627 start
// AR NO.17779 の対応
@synthesize hasSignature;
// liuqw 20110627 end

// liuqw 20110801 start
// ページ編集機能の追加
@synthesize dwDrawer = drawer;
// liuqw 20110801 end

// xuxinjun 2012.03.23 start
// 保護文書の対応
@synthesize openPassword = openPassword_; 
// xuxinjun 2012.03.23 end

// tongtx 2012.03.23 start
// 選択機能の追加
@synthesize logicAnnMananger = logicAnnMananger_;
// tongtx 2012.03.23 end

#pragma mark -
#pragma mark init manager.

// xuxinjun 2012.03.23 start
// 保護文書の対応
/*
 - (id) initWithDocumentViewController:(DocumentViewController*)controller 
 withDocumentPath:(NSString *)documentPath
 */
- (id) initWithDocumentViewController:(DocumentViewController*)controller 
					 withDocumentPath:(NSString *)documentPath 
					 withOpenPassword:(NSString*)pwd
// xuxinjun 2012.03.23 end

{
	if (self = [super init])
	{
		documentViewController = controller;
		
		interfaceOrientation = UIInterfaceOrientationPortrait;
		
		handleDocument = NULL;
		drawer = nil;
		documentType = DOC_TYPE_NONE;
		
		pageTotalCount = 0;
		
		// save settings.
		pageIndex = 0;
		pageScale = 100;
		pageOffset = CGPointZero;
		facingMode = MODE_REGULAR;
		fontOrient = YES;
		showAnnotation = YES;
		
		enableAnnotation = YES;
		
		// init page fit statue
		isPageFit = YES;
		
		// init page status
		pageStatus = PAGE_STATUS_FIT;
		
		zoomOutLock = [[NSLock alloc]init];
		pageZoomScale = 1.0;
		
		
		isZoomEnd = NO;
		
		isBinderDoc = NO;
        
        hasSignature = NO;
		
		// load document with file path.
		// xuxinjun 2012.03.23 start
		// 保護文書の対応
		//BOOL ret = [self loadXDWDocument:documentPath];
		
		self.openPassword = pwd;
		BOOL ret = [self loadXDWDocument:documentPath andOpenPassword:pwd];
		// xuxinjun 2012.03.23 end

		if (NULL != handleDocument && ret)
		{
			drawer = [[DWDrawer alloc]initWithDocumentHandle:handleDocument];
		}
        
        documentVersion = handleDocument->GetStorageVersion();
		
		// tongtx 2012.03.23 start
		// 選択機能の追加
		logicAnnMananger_ = new LogicAnnotationManager(handleDocument);
		// tongtx 2012.03.23 end
		
		if (ret)
		{
			return self;	
		}
		else
		{
			// For MemoryLeak;
			if (handleDocument != NULL)
			{
				delete handleDocument;
				handleDocument = NULL;
			}
			if (zoomOutLock != nil)
			{
				[zoomOutLock release];
				zoomOutLock = nil;
			}
			[self autorelease];
			// MemoryLeak end.

			return nil;
		}
	}
	else
	{
		return nil;
	}
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
//- (BOOL) loadXDWDocument:(NSString *)documentPath
- (BOOL) loadXDWDocument:(NSString *)documentPath andOpenPassword:(NSString*)pwd
// xuxinjun 2012.03.23 end

{
	if(documentPath != nil)
	{
		if ([[documentPath pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
			[[documentPath pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
		{
			handleDocument = new XdwDocumentHandle();
			documentType = DOC_TYPE_XDW;
		}
		else if ([[documentPath pathExtension] caseInsensitiveCompare:@"pdf"] == NSOrderedSame)
		{
			handleDocument = new PDFDocumentHandle();
			documentType = DOC_TYPE_PDF;
		}
		else
		{
			//Error 1 Alert
			UIAlertView *errorOne = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
															  message:NSLocalizedString(@"MSG_ERROR_FILETYPEERROR", nil)
															 delegate:nil
													cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													otherButtonTitles:nil];
			[errorOne show];
			[errorOne release];
			return NO;
		}
		
		const char *fileName_const_char = [documentPath UTF8String];
		char fileName_char[1024] = { 0 };
		strcpy(fileName_char, fileName_const_char);
		
		XdwErrorCode ret = XDW_ERRORCODE_SUCCESS;
		
		// xuxinjun 2012.03.23 start
		// 保護文書の対応
		
		//ret = handleDocument->OpenDocument(fileName_char);
		
		if (pwd != nil)
		{
			const char *pwd_const_char = [pwd UTF8String];
			char pwd_char[1024] = { 0 };
			strcpy(pwd_char, pwd_const_char);
			
			ret = handleDocument->OpenDocument(fileName_char, pwd_char);
		} 
		else
		{
			ret = handleDocument->OpenDocument(fileName_char, NULL);
		}
		// xuxinjun 2012.03.23 end

		if (ret != XDW_ERRORCODE_SUCCESS)
		{
			NSString * errorstr;
			if (ret == XDW_ERRORCODE_CRYPT_ERROR        ||
				ret == XDW_ERRORCODE_NEED_PSWD          ||
				ret == XDW_ERRORCODE_FILE_ENCRYPTED_DES)
			{
				/* Open protected file fail(Error 4) */
				errorstr = NSLocalizedString(@"MSG_ERROR_FILEPROTECTEDERROR", nil);
			}
			else if (ret == XDW_ERRORCODE_INSUFFICIENT_MEMORY)
			{
				/* Out of memory(Error 6) */
				errorstr = NSLocalizedString(@"MSG_ERROR_MEMORYOUTERROR", nil);
			}
			else if (ret == XDW_ERRORCODE_BAD_CHECKSUM)
			{
				/* File is not DocWorks file(Error 1) */
				errorstr = NSLocalizedString(@"MSG_ERROR_FILEDEFAULTERROR", nil);
			}
			else if (ret == XDW_ERRORCODE_NOT_SUPPORTED_VERSION)
			{
				errorstr = NSLocalizedString(@"MSG_ERROR_FILEVERSIONERROR", nil);
			}
            else
			{
				/* File can not open.(Error 5) */
				errorstr = NSLocalizedString(@"MSG_ERROR_FILEDEFAULTERROR", nil);
			}
			
			UIAlertView *errorAlert = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
																message:errorstr
															   delegate:nil
													  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													  otherButtonTitles:nil];
			[errorAlert show];
			[errorAlert release];

			return NO;
		}
		
		FileInfo *fileInfo = handleDocument->GetFileInfo();
		if (fileInfo == NULL)
		{
			UIAlertView *errorTwo = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
															  message:NSLocalizedString(@"MSG_ERROR_FILENAMEERROR", nil)
															 delegate:nil
													cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
													otherButtonTitles:nil];
			[errorTwo show];
			[errorTwo release];
			return NO;
		}

		pageTotalCount = fileInfo->GetPageCount();

		if (documentType == DOC_TYPE_XDW)
		{
            if (((XdwFileInfo*)fileInfo)->HasSignature() == true)
			{
				hasSignature = YES;
			}
            
            if(((XdwFileInfo*)fileInfo)->IsBinder() == true)
            {
                isBinderDoc = YES;
            }
		}
		
		bool canEnableAnnot = handleDocument->CanEnableAnnotation();

		if (canEnableAnnot == YES)
		{
			if (kShowAnnot == fileInfo->GetAnnotationDisplayMode())
			{
				showAnnotation = YES;
			}
			else
			{
				showAnnotation = NO;
			}
		}
		else
		{
			showAnnotation = YES;
		}
		
	}
	else
	{
		UIAlertView *errorTwo = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_ERROR", nil) 
														  message:NSLocalizedString(@"MSG_ERROR_FILENAMEERROR", nil)
														 delegate:nil
												cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												otherButtonTitles:nil];
		[errorTwo show];
		[errorTwo release];
		return NO;
	}
	
	return YES;
}

- (int) getPageViewCount
{
	int count = pageTotalCount;

	if ([self UIDeviceIsPortrait] == NO)
	{
		if      (facingMode == MODE_FACE_NO)
		{
			count = count / 2 + count % 2;
		}
		else if (facingMode == MODE_FACE_YES)
		{
			count = (count - 1) / 2 + (count - 1 ) % 2 + 1;
		}
	}
	
	return count;
}

// liuqw 20120203 start
// AR NO.17926の対応
- (int) getPageViewCountAtFacingMode:(FacingMode)mode;
{
    int count = pageTotalCount;
    
	if      (mode == MODE_FACE_NO)
    {
        count = count / 2 + count % 2;
    }
    else if (mode == MODE_FACE_YES)
    {
        count = (count - 1) / 2 + (count - 1 ) % 2 + 1;
    }
	
	return count;
}
// liuqw 20120203 end


#pragma mark -
#pragma mark create new page view.
- (DWScrollView *) insertNewPageViewWithPageIndex:(int)index
{
	DWScrollView *pageView = nil;
	CGRect screen = [self getScreenRect];
	
	pageView = [[DWScrollView alloc]initWithFrame:screen];

	[pageView setBackgroundColor:[UIColor grayColor]];
    
	pageView.showsHorizontalScrollIndicator = YES;
	pageView.showsVerticalScrollIndicator = YES;
	pageView.scrollEnabled = NO;
	pageView.bounces = YES;

	pageView.scrollsToTop = NO;
	
	pageView.directionalLockEnabled = YES;
	
	if (facingMode == MODE_REGULAR)
	{
		[self initPageView:pageView withPageIndex:(index)];
	}
	else
	{
		if ([self UIDeviceIsPortrait] == YES)
		{
			[self initPageView:pageView withPageIndex:(index)];
		}
		else
		{
			[self initFacingPageView:pageView withPageIndex:index];
		}
	}
	return pageView;
}


- (void) setPageViewActive:(DWScrollView*)pageView
{
	if (pageView != nil)
	{
		pageView.isActivePage = YES;
		pageIndex = pageView.index;
	}
}


#pragma mark -
#pragma mark interface for page view zoom.
- (void) zoomOutPageView:(DWScrollView*)pageView withTouchPoint:(CGPoint)point
{
    if (pageScale == pageView.minScale)
	{
        return;
    }
    
    long srcScale = pageScale;
    long dstScale = srcScale / 2;

	if (dstScale < pageView.minScale)
	{
		dstScale = pageView.minScale;
	}

	float zoomScale = (float)dstScale / (float)pageView.baseScale;

	if (zoomScale < pageView.minimumZoomScale)
	{
		zoomScale = pageView.minimumZoomScale;
	}
    
    [self zoomPageView:pageView withTouchPoint:point withZoomScale:zoomScale withInOut:NO];
    
    pageScale = dstScale;
}


- (void) zoomInPageView:(DWScrollView*)pageView withTouchPoint:(CGPoint)point
{
	if (pageScale == pageView.maxScale)
	{
		return;
	}
    
	long srcScale = pageScale;
	long dstScale = srcScale * 2;
	
	if (dstScale > pageView.maxScale)
	{
		dstScale = pageView.maxScale;
	}

	float zoomScale = (float)dstScale / (float)pageView.baseScale;
	
	if (zoomScale > pageView.maximumZoomScale)
	{
		zoomScale = pageView.maximumZoomScale;
	}

	[self zoomPageView:pageView withTouchPoint:point withZoomScale:zoomScale withInOut:YES];

	pageScale = dstScale;
}


//
// 指定ページを紙面フィット表示にする
//
- (void) zoomPageViewToPageFit:(DWScrollView*)pageView
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	pageStatus = PAGE_STATUS_FIT;
	// 2012.02.01(Ver2.1 New) M.Chikyu

	if (pageView.zoomScale != Utility::MIN_SCALE)
	{
		isZoomEnd = YES;
		[pageView setZoomScale:(Utility::MIN_SCALE) animated:NO];
	}
	else
	{
		DWPageView *page =  pageView.page;
		
		if (pageView.isFacingPage == NO)
		{
			long scale = [self getPageScaleWithIndex:pageView.index withPageMode:(PageInfo::kPaperMode)];
			page.frame = [self getPageRectWithIndex:pageView.index withPageScale:scale];
			pageView.contentOffset = pageView.initContentOffset;
		}
		else
		{
			CGRect pageRect = [self getFacingPageViewRectWidthIndex:pageView.index];
			float originY = pageRect.origin.y;
			page.frame = CGRectMake(0.0, originY, page.frame.size.width, page.frame.size.height);
		}
	}

	pageView.scrollEnabled = NO;
}


- (void) zoomPageViewForAnnotationJump:(DWScrollView*)pageView 
					withAnnotationRect:(CGRect)rect
			  withAnnotationInLeftPage:(BOOL)inLeftPage
{
	float zoomScale = 1.0;
	
	// 1. get zoom scale.
	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth	= screenSize.width;
	float backgroundHeight	= screenSize.height;
	
	float pageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
	float pageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
	float pageWidth		= pageView.page.m_PageInfoA.m_SrcRect.size.width;
	float pageHeight	= pageView.page.m_PageInfoA.m_SrcRect.size.height;

	if (pageView.isFacingPage == YES)
	{
		float secondPageWidth = pageView.page.m_PageInfoA.m_SrcRect.size.width;
		
		pageWidth += (secondPageWidth + kFacePageEdgeWidth * 2 +  kFacePageInterval);
	}
	
	float annotWidth	= rect.size.width;
	float annotHeight	= rect.size.height;
	float annotOriginX	= rect.origin.x;
	float annotOriginY	= rect.origin.y;
	
	float scaleX = (backgroundWidth  * 0.8) / annotWidth;
	float scaleY = (backgroundHeight * 0.8) / annotHeight;
	zoomScale = scaleX > scaleY ? scaleY : scaleX;
	
	// min zoom scale
	if (pageView.isFacingPage == YES)
	{
		if (zoomScale < Utility::MIN_SCALE)
		{
			zoomScale = Utility::MIN_SCALE;
		}
	}
	else
	{
        if (zoomScale < pageView.minimumZoomScale)
		{
			zoomScale = pageView.minimumZoomScale;
		}
	}

	// max zoom scale.

	float maxZoomScale = pageView.maximumZoomScale;
	
	if (zoomScale > maxZoomScale)
	{
		zoomScale = maxZoomScale;
	}
    
    pageScale = pageView.baseScale * zoomScale;
	
	if (pageScale < pageView.minScale)
	{
		pageScale = pageView.minScale;
	}
	
	if (pageScale > pageView.maxScale)
	{
		pageScale = pageView.maxScale;
	}
    
	
	// 2. zoom page view 
	[pageView setZoomScale:zoomScale animated:YES];
	[self resetPageViewContentSize:pageView];
	
	CGPoint pageOrigin = pageView.page.frame.origin;
	
	// 3. get offset.
	CGPoint offset = CGPointZero;
	offset.x = annotOriginX * zoomScale + pageOrigin.x - (backgroundWidth  - (annotWidth  * zoomScale)) / 2;
	offset.y = annotOriginY * zoomScale + pageOrigin.y - (backgroundHeight - (annotHeight * zoomScale)) / 2;
	
	float paperRightEdge	= (pageOriginX + pageWidth);
	float annotRightEdge	= (annotOriginX + annotWidth);

	float annotMaxOffsetX	= (annotOriginX + annotWidth) * zoomScale + pageOrigin.x - backgroundWidth;

	if (offset.x > annotMaxOffsetX &&
		annotRightEdge > paperRightEdge)
	{
		offset.x = annotMaxOffsetX;
	}
	
	float paperButtomEdge	= (pageOriginY + pageHeight);
	float annotButtomEdge	= (annotOriginY + annotHeight);

	float annotMaxOffsetY	= (annotOriginY + annotHeight) * zoomScale + pageOrigin.y - backgroundHeight;

	if (offset.y > annotMaxOffsetY &&
		annotButtomEdge > paperButtomEdge)
	{
		offset.y = annotMaxOffsetY;
	}
	
	float paperLeftEdge		= pageOriginX;
	float annotLeftEdge		= annotOriginX;

	float annotMinOffsetX	= annotOriginX * zoomScale + pageOrigin.x;

	if (offset.x < annotMinOffsetX &&
		annotLeftEdge < paperLeftEdge)
	{
		offset.x = annotMinOffsetX;
	}
	
	float paperTopEdge		= pageOriginY;
	float annotTopEdge		= annotOriginY;

	float annotMinOffsetY	= annotOriginY * zoomScale + pageOrigin.y;

	if (offset.y < annotMinOffsetY &&
		annotTopEdge < paperTopEdge)
	{
		offset.y = annotMinOffsetY;
	}
	
	// right
	float pageRightEdge = pageView.contentSize.width;

	float maxOffsetX = pageRightEdge - backgroundWidth;

	if (offset.x > maxOffsetX)
	{
		offset.x = maxOffsetX;
	}
	
	// buttom
	float pageButtomEdge = pageView.contentSize.height;

	float maxOffsetY = pageButtomEdge - backgroundHeight;

	if (offset.y > maxOffsetY)
	{
		offset.y = maxOffsetY;
	}
	
	// left
	float minOffsetX = 0.0;

	if (offset.x < minOffsetX)
	{
		offset.x = minOffsetX;
	}
	
	// top
	float minOffsetY = 0.0;

	if (offset.y < minOffsetY)
	{
		offset.y = minOffsetY;
	}
	
	// 4. reset page view content offset
	[pageView setContentOffset:offset animated:NO];
	pageOffset = offset;
}	


- (void) zoomPageView:(DWScrollView *)pageView 
	   withTouchPoint:(CGPoint)point 
		withZoomScale:(float)scale 
			withInOut:(BOOL)zoomIn
{
	if (pageView == nil)
	{
		return;
	}
	
	isZoomEnd = YES;
	
	float zoomScale = scale;
	
    if (zoomIn == YES)
	{
		// 1. get new origin.
		CGSize screenSize = [self getScreenRect].size;

		float originX = pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x;
		float originY = pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.y;

		float newOriginX = (point.x - originX) * zoomScale;
		float newOriginY = (point.y - originY) * zoomScale;
        
        // 2. get new offset.
		CGSize contentSize = [self getPageViewContentSizeWithPageView:pageView 
														withZoomScale:zoomScale];

		float backgroundWidth = screenSize.width;
		float backgroundHeight = screenSize.height;

		float offsetX = max((newOriginX - backgroundWidth  / 2), 0.0f);
		float offsetY = max((newOriginY - backgroundHeight / 2), 0.0f);

		float maxOffsetX = max(contentSize.width  - backgroundWidth,  0.0f);
		float maxOffsetY = max(contentSize.height - backgroundHeight, 0.0f);

		if (offsetX > maxOffsetX)
		{
			offsetX = maxOffsetX;
		}

		if (offsetY > maxOffsetY)
		{
			offsetY = maxOffsetY;
		}
        
		// 3. zoom in page view.
		[pageView setZoomScale:zoomScale animated:YES];
		[pageView setContentOffset:CGPointMake(offsetX, offsetY) animated:NO];
	}
	else
	{
		if (nil != zoomOutLock)
		{
			[zoomOutLock lock];
		}
		
		[NSThread sleepForTimeInterval:0.25];
        
        // 1. get new origin.
		CGSize screenSize = [self getScreenRect].size;

		float originX = pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x;
		float originY = pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.y;

		float newOriginX = (point.x - originX) * zoomScale;
		float newOriginY = (point.y - originY) * zoomScale;
        
        // 2. get new offset.
		CGSize contentSize = [self getPageViewContentSizeWithPageView:pageView 
														withZoomScale:zoomScale];

		float backgroundWidth  = screenSize.width;
		float backgroundHeight = screenSize.height;

		float offsetX = max((newOriginX - backgroundWidth  / 2), 0.0f);
		float offsetY = max((newOriginY - backgroundHeight / 2), 0.0f);
	
		float maxOffsetX = max(contentSize.width  - backgroundWidth,  0.0f);
		float maxOffsetY = max(contentSize.height - backgroundHeight, 0.0f);

		if (offsetX > maxOffsetX)
		{
			offsetX = maxOffsetX;
		}

		if (offsetY > maxOffsetY)
		{
			offsetY = maxOffsetY;
		}
        
		// 3. zoom in page view.
		[pageView setZoomScale:zoomScale animated:YES];

		if (zoomScale == pageView.minZoomScale)
		{
			offsetX = 0.0f;
			offsetY = 0.0f;
		}

		[pageView setContentOffset:CGPointMake(offsetX, offsetY) animated:NO];
        
		if (nil != zoomOutLock)
		{
			[zoomOutLock unlock];
		}
    }
}


- (void) updatePageViewScaleInfo:(DWScrollView *)pageView
{
	if (pageView != nil)
	{
		if (pageStatus != PAGE_STATUS_FIT)
		{
			if (pageStatus == PAGE_STATUS_FULL)
			{
				isZoomEnd = YES;
				
				[pageView setZoomScale:pageView.minZoomScale animated:NO];
			}
			else
			{
				DWPageInfo pageInfo = pageView.page.m_PageInfoA;

				if (pageScale > pageView.page.m_PageInfoA.m_MaxPageScale)
				{
					pageScale = pageView.page.m_PageInfoA.m_MaxPageScale;
				}
				
				if (pageScale < pageView.page.m_PageInfoA.m_PageFitScale * pageView.minZoomScale)
				{
					pageScale = pageView.page.m_PageInfoA.m_PageFitScale * pageView.minZoomScale;
				}
				
				pageInfo.m_Scale = pageScale;
				pageView.page.m_PageInfoA = pageInfo;
				
				float pageCurScale = pageInfo.m_Scale;
				float pageFitScale = pageView.page.m_PageInfoA.m_PageFitScale;
				pageZoomScale = pageCurScale / pageFitScale;
				
				
				if (pageZoomScale < pageView.minZoomScale)
				{
					pageZoomScale = pageView.minZoomScale;
				}
				
                
                float maxZoomScale = pageView.maximumZoomScale;
				
				if (pageZoomScale > maxZoomScale)
				{
					pageZoomScale = maxZoomScale;
				}
                
				[pageView setZoomScale:pageZoomScale animated:NO];
			}
			
			[self updatePageViewStatusForZoom:pageView 
								withZoomScale:pageZoomScale 
						 withRestoreToPageFit:NO];
		}
	}
}


- (void) updatePageViewScaleToPageFit:(DWScrollView *)pageView
{
	if (pageView != nil)
	{
		[self updatePageViewStatusForZoom:pageView 
							withZoomScale:(Utility::MIN_SCALE) 
					 withRestoreToPageFit:NO];
	}
}


#pragma mark -
#pragma mark method for annotation On / Off.
- (void) setAnnotationDisplay:(BOOL)display
{
	if (display == YES)
	{
		showAnnotation = YES;

		if (handleDocument != NULL)
		{
			handleDocument->SetDocAnnotationDispaly(kShowAnnot);
		}
	}
	else
	{
		showAnnotation = NO;
		
		if (pageStatus == PAGE_STATUS_FULL)
		{
			pageStatus = PAGE_STATUS_FIT;
		}
		
		if (handleDocument != NULL)
		{
			handleDocument->SetDocAnnotationDispaly(kHideAnnot);
		}
	}
	
	if (pageStatus == PAGE_STATUS_ZOOM)
	{
		DWScrollView *pageView = [documentViewController getActivePageView];

		if (pageView != nil && pageView.page != nil)
		{
			// get offset of paper.
			float offsetX = 0.0, offsetY = 0.0;
			PageInfo* pageInfo = handleDocument->GetPageInfo(pageView.index);

			if (pageInfo != nil)
			{
				long scale = pageView.page.m_PageInfoA.m_PageFitScale;
				MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);
				
				offsetX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
				offsetY = fabs(Utility::MMToPixelWithScale(pos.y, scale));
			}

			offsetX = offsetX * pageZoomScale;
			offsetY = offsetY * pageZoomScale;
			
			if (pageView.isFacingPage == YES)
			{
				offsetX = kFacePageEdgeWidth * pageZoomScale;
				offsetY = kFacePageEdgeWidth * pageZoomScale;
			}
			
			if (showAnnotation == YES)
			{
				pageOffset.x += offsetX;
				pageOffset.y += offsetY;
			}
			else
			{
				pageOffset.x -= offsetX;

				if (pageOffset.x < 0.0)
				{
					pageOffset.x = 0.0;
				}
				
				pageOffset.y -= offsetY;

				if (pageOffset.y < 0.0)
				{
					pageOffset.y = 0.0;
				}
			}
		}
	}
}


#pragma mark -
#pragma mark method for get annotation list.
- (LinkAnnotInfoList*) getLinkAnnotationInfoList
{
	return handleDocument->GetLinkAnnotationList();
}


- (XdwFileInfo*) getBinderFileInfo
{
	XdwFileInfo* xdwFileInfo = (XdwFileInfo*)handleDocument->GetFileInfo();
	
	return xdwFileInfo;//handleDocument->GetLinkAnnotationList();
}


#pragma mark -
#pragma mark init new page view with regular.
- (void) initPageView:(DWScrollView*)pageView withPageIndex:(int)index
{
	if (pageView != nil)
	{
		pageView.index = index;
		pageView.tag = index;
		
		long scale = [self getPageScaleWithIndex:index withPageMode:(PageInfo::kPaperMode)];

		DWPageView *page = [[DWPageView alloc]initWithFrame:[self getPageRectWithIndex:index 
																		 withPageScale:scale]];
		[page setBackgroundColor:[UIColor whiteColor]];

		[self initPage:page withPageIndex:index];

		pageView.page = page;
		pageView.contentSize = page.frame.size;
		
		CGPoint contentOffset = [self getPageContentOffsetWithIndex:index withPageScale:scale];

		pageView.initContentOffset = contentOffset;
		pageView.contentOffset = pageView.initContentOffset;
		
		[pageView addSubview:page];
		
		pageView.isFacingPage = NO;
		
		// set link annotation index list.
		[self setLinkAnnotationIndexList:pageView];
		
		//Set ScrollView's ZoomScale
		float minZoomScale = Utility::MIN_SCALE;

		if (showAnnotation == YES)
		{
			minZoomScale = [self getPageFullZoomScale:pageView];
		}
        // 20110714 M.Chikyu(AR17924) start
        else
        {
            long scale = [self getPageScaleWithIndex:pageView.index
                                        withPageMode:(PageInfo::kPaperMode)];
            if (scale > 100) 
            {
               minZoomScale = 100.0 / (float)scale;
            }
        }
        // 20110714 M.Chikyu(AR17924) end
		
		pageView.minimumZoomScale = minZoomScale;
		
		pageView.minZoomScale = minZoomScale;
        
        pageView.maximumZoomScale = [self getPageMaxZoomScale:pageView];
        
        if (showAnnotation == YES)
		{
			pageView.minScale = [self getPageScaleWithIndex:pageView.index
											   withPageMode:(PageInfo::kFullMode)];   
        }
		else
		{
			pageView.minScale = [self getPageScaleWithIndex:pageView.index
											   withPageMode:(PageInfo::kPaperMode)];
        }

		if (pageView.minScale > 100)
		{
			pageView.minScale = 100;
		}

		pageView.baseScale = [self getPageScaleWithIndex:pageView.index
											withPageMode:(PageInfo::kPaperMode)];
		pageView.maxScale = Utility::MAX_SPECIFY_SCALE;
        
		if (pageView.baseScale > Utility::MAX_SPECIFY_SCALE)
		{
			pageView.maxScale = pageView.baseScale;
		}

		pageView.delegate = self;
	}
}

- (void) initPage:(DWPageView*)page withPageIndex:(int)index
{
	if (page != nil)
	{
		page.m_PageInfoA = [self getDWPageInfo:index];
		page.m_PageInfoB = [self getDWPageInfo:-1];

		page.tag = 100000;
		page.backgroundColor = [UIColor whiteColor];

		[self setLayerPropertyWithPageView:page];
	}
}


- (DWPageInfo) getDWPageInfo:(int)pageNum
{
	DWPageInfo pageInfo;

	if (pageNum >= [self getPageViewCount] || pageNum < 0)
	{
		pageInfo.m_PageNum = -1;
		return pageInfo;
	}

	pageInfo.m_PageNum = pageNum;
	
	long scale = [self getPageScaleWithIndex:pageNum withPageMode:(PageInfo::kPaperMode)];
	pageInfo.m_Scale = scale;
	pageInfo.m_PageFitScale = scale;
    
    pageInfo.m_MaxPageScale = Utility::MAX_SPECIFY_SCALE;

    if (scale > Utility::MAX_SPECIFY_SCALE)
	{
		pageInfo.m_MaxPageScale = scale;
	}
	
	// 次ページの一部が表示されるの対応
	float originX = 0.0;
	float originY = 0.0;

	float pageWidth = 0.0;
	float pageHeight = 0.0;
	
	// 1. set m_SrcRectWithAnno value.
	CGSize pageSize = CGSizeZero;
	if (showAnnotation == YES)
	{
		pageSize = [self getPageSize:pageNum 
					   withPageScale:scale 
						withPageMode:(PageInfo::kFullMode)];
		
		float offsetX = 0.0;
		PageInfo* dwPageInfo = handleDocument->GetPageInfo(pageNum);

		if (dwPageInfo != nil)
		{
			MP_Pos pos = dwPageInfo->GetPagePos(PageInfo::kFullMode);

			offsetX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
		}
	}
	else
	{
		pageSize = [self getPageSize:pageNum 
					   withPageScale:scale 
						withPageMode:(PageInfo::kPaperMode)];
	}
	
	pageWidth = pageSize.width;
	pageHeight = pageSize.height;
	
	originX = [self getPageMinIntervalWithIndex:pageNum withPageScale:scale];

	pageInfo.m_SrcRectWithAnno = CGRectMake(originX, 
											originY, 
											pageWidth,
											pageHeight);

	// 2. set m_SrcRect value
	CGRect frameInner = [self getPageInnerRectWithIndex:pageNum withPageScale:scale];
	pageInfo.m_SrcRect = CGRectMake(originX + frameInner.origin.x, 
									originY + frameInner.origin.y, 
									frameInner.size.width, 
									frameInner.size.height);
	pageInfo.m_DestRect = CGRectZero;
	
	return pageInfo;
}


- (void) setLinkAnnotationIndexList:(DWScrollView*)pageView
{
	if (pageView != nil)
	{
		LinkAnnotInfoList* list = [self getLinkAnnotationInfoList];

		if (list != NULL)
		{
			XdwLinkManager linkManager(list);
			std::vector<int> linkIndexVector;
			
			if (pageView.isFacingPage == NO)
			{
				int count = linkManager.GetLinkAnnotationIndexForPageIndex(pageView.index, linkIndexVector);

				if (count > 0)
				{
					for (int i = 0; i < count; i++)
					{
						[pageView.page addLinkAnnotationIndex:linkIndexVector[i] withIsLeftPage:YES];
					}
				}
			}
			else
			{
				// if facing mode.
				int firstIndex = pageView.page.m_PageInfoA.m_PageNum;
				int secondIndex = pageView.page.m_PageInfoB.m_PageNum;
								
				// first page 
				linkIndexVector.clear();
				if (firstIndex != -1)
				{
					int count = linkManager.GetLinkAnnotationIndexForPageIndex(firstIndex, linkIndexVector);

					if (count > 0)
					{
						for (int i = 0; i < count; i++)
						{
							[pageView.page addLinkAnnotationIndex:linkIndexVector[i] withIsLeftPage:YES];
						}
					}
				}

				// second page
				linkIndexVector.clear();

				if (secondIndex != -1)
				{
					int count = linkManager.GetLinkAnnotationIndexForPageIndex(secondIndex, linkIndexVector);

					if (count > 0)
					{
						for (int i = 0; i < count; i++)
						{
							[pageView.page addLinkAnnotationIndex:linkIndexVector[i] withIsLeftPage:NO];
						}
					}
				}
			}
		}
	}
}

- (void)setLayerPropertyWithPageView:(DWPageView*)page
{
	if (nil == page)
	{
		return;
	}
	
	if (nil != [self getBackGround])
	{
		[page.layer setBackgroundColor:bgColor.CGColor];
	}

	CATiledLayer* tiledLayer = (CATiledLayer*)page.layer;	

	CGFloat scaleFactor = page.contentScaleFactor;
	
	CGRect screenRect = [self getScreenRect];

	float tileSize;

	// AR190xx
	// 2012.02.23 M.Chikyu start.
	/*
	if (Utility::UIDeviceIsiPad() == YES)
	{
		tileSize = 1024;
	}
	else if (scaleFactor > 1.0)
	{
		tileSize = 960;
	}
	else
	{
		tileSize = 480;
	}
	 */
	
	if (Utility::UIDeviceIsiPad() == YES)
	{
		tileSize = 2048;
	}
	else if (scaleFactor > 1.0)
	{
		tileSize = 2048;
	}
	else
	{
		tileSize = 1024;
	}
	// 2012.02.23 M.Chikyu end.
	
	tiledLayer.tileSize = CGSizeMake(tileSize, tileSize);

	// init drawer
	// all page use same drawer.
	((DWLayer*)page.layer).drawer = drawer;
}

#pragma mark -
#pragma mark init new page view with facing mode.
- (void) initFacingPageView:(DWScrollView*)pageView withPageIndex:(int)index;
{
	if (pageView != nil)
	{
		pageView.index = index;
		pageView.tag = index;
		
		CGRect frame = [self getFacingPageViewRectWidthIndex:index];

		// add page to back ground view.
		DWPageView *page = [[DWPageView alloc]initWithFrame:frame];
		[page setBackgroundColor:[UIColor whiteColor]];
		[self initFacingPage:page withPageIndex:index];
		pageView.page = page;
		pageView.contentSize = page.frame.size;
		[pageView addSubview:page];
		
		pageView.minScale = [self getFacingPageScalewithIndex:pageView.index];

		if (pageView.minScale > 100)
		{
			pageView.minScale = 100;
		}
		
        pageView.baseScale = [self getFacingPageScalewithIndex:pageView.index];
        pageView.maxScale = Utility::MAX_SPECIFY_SCALE;

		if (pageView.minScale > Utility::MAX_SPECIFY_SCALE)
		{
			pageView.maxScale = pageView.minScale;
		}
		
        pageView.minimumZoomScale = (float)pageView.minScale / (float)pageView.baseScale;
        pageView.maximumZoomScale = (float)pageView.maxScale / (float)pageView.baseScale;
        
		pageView.delegate = self;
		
		pageView.isFacingPage = YES;
		
		// set link annotation index list.
		[self setLinkAnnotationIndexList:pageView];
	}
}


- (BOOL) isFacingPageContainTowPages:(int)index
{
	BOOL isTwoPage = NO;

	if (facingMode == MODE_FACE_NO)
	{
		if ((index * 2) >= 0 && (index * 2)<= (pageTotalCount - 1))
		{
			isTwoPage = NO;
		}
		
		if ((index * 2 + 1) >= 0 && (index * 2 + 1) <= (pageTotalCount - 1))
		{
			isTwoPage = YES;
		}
		else
		{
			isTwoPage = NO;
		}
	}
	else if (facingMode == MODE_FACE_YES)
	{
		if (index == 0)
		{
			isTwoPage = NO;
		}
		else
		{
			if ((index * 2 - 1) >= 0 && (index * 2 - 1) <= (pageTotalCount - 1))
			{
				isTwoPage = NO;
			}
			
			if ((index * 2) >= 0 &&(index * 2) <= (pageTotalCount - 1))
			{
				isTwoPage = YES;
			}
			else
			{
				isTwoPage = NO;
			}
		}
	}
	
	return isTwoPage;
}


- (void) initFacingPage:(DWPageView*)page withPageIndex:(int)index
{
	if (page != nil)
	{
		page.isFacingMode = YES;

		if (facingMode == MODE_FACE_NO)
		{
			if (fontOrient == YES)
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					[self setOneFacingPageInfo:page withPageIndex:(index * 2)];
				}
				else
				{
					[self setTwoFacingPageInfo:page 
							withFirstPageIndex:(index * 2) withSecondPageIndex:(index * 2 + 1)];
				}
			}
			else
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					[self setOneFacingPageInfo:page withPageIndex:(index * 2)];
				}
				else
				{
					[self setTwoFacingPageInfo:page 
							withFirstPageIndex:(index * 2 + 1) withSecondPageIndex:(index * 2)];
				}
			}
		}
		else if (facingMode == MODE_FACE_YES)
		{
			if (index == 0)
			{
				[self setOneFacingPageInfo:page withPageIndex:index];
			}
			else
			{
				if (fontOrient == YES)
				{
					if ([self isFacingPageContainTowPages:index] == NO)
					{
						[self setOneFacingPageInfo:page withPageIndex:(index * 2 - 1)];
					}
					else
					{
						[self setTwoFacingPageInfo:page 
								withFirstPageIndex:(index * 2 - 1) withSecondPageIndex:(index * 2)];
					}
				}
				else
				{
					if ([self isFacingPageContainTowPages:index] == NO)
					{
						[self setOneFacingPageInfo:page withPageIndex:(index * 2 - 1)];
					}
					else
					{
						[self setTwoFacingPageInfo:page 
								withFirstPageIndex:(index * 2) withSecondPageIndex:(index * 2 - 1)];
					}
				}
			}
		}
		
		page.tag = 100000;
		[self setLayerPropertyWithPageView:page];
	}
}


- (void) setOneFacingPageInfo:(DWPageView*)page 
				withPageIndex:(int)index
{
	// AR NO.17527 の対応 start
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;
	CGPoint offset = CGPointZero;
	
	if (showAnnotation == YES && documentType == DOC_TYPE_XDW)
	{
		offset = CGPointMake(kFacePageEdgeWidth, kFacePageEdgeWidth);
	}
	long scale = [self getFacingPageScaleWithFirstIndex:index 
									withSecondPageIndex:0
										  withIsOnePage:YES];

	CGSize pageSize = [self getPageSize:index 
						  withPageScale:scale 
						   withPageMode:mode];
	
	float originX = 0;
	float originY = 0;

	float screenW = [self getScreenRect].size.width;

	// 2012.02.14 M.Chikyu start.
	/*
	originX = (screenW - offset.x * 2) / 2;
	 */

	originX = (screenW - pageSize.width - offset.x * 2) / 2;
	// 2012.02.14 M.Chikyu end.
	
	// set m_PageInfoA.
	DWPageInfo pageInfoA;
	pageInfoA.m_PageNum = index;
	pageInfoA.m_Scale = scale;
	pageInfoA.m_PageFitScale = scale;
    
    pageInfoA.m_MaxPageScale = Utility::MAX_SPECIFY_SCALE;
	
	if (scale > Utility::MAX_SPECIFY_SCALE)
	{
		pageInfoA.m_MaxPageScale = scale;
	}
    
	pageInfoA.m_SrcRectWithAnno = CGRectMake(originX, 
											 originY, 
											 pageSize.width + offset.x * 2, 
											 pageSize.height + offset.y * 2);
	
	pageInfoA.m_SrcRect = CGRectMake(originX + offset.x, 
									 originY + offset.y, 
									 pageSize.width, 
									 pageSize.height);

	pageInfoA.m_DestRect = CGRectZero;
	page.m_PageInfoA = pageInfoA;
	
	// set m_PageInfoB.
	DWPageInfo pageInfoB;
	pageInfoB.m_PageNum = -1;
	pageInfoB.m_SrcRectWithAnno = CGRectZero;
	pageInfoB.m_SrcRect = CGRectZero;
	pageInfoB.m_DestRect = CGRectZero;
	page.m_PageInfoB = pageInfoB;
	// AR NO.17527 の対応 end
}


- (void) setTwoFacingPageInfo:(DWPageView*)page 
		   withFirstPageIndex:(int)firstIndex 
		  withSecondPageIndex:(int)secondIndex
{
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;
	
	CGPoint offset = CGPointZero;
	
	if (showAnnotation == YES && documentType == DOC_TYPE_XDW)
	{
		offset = CGPointMake(kFacePageEdgeWidth, kFacePageEdgeWidth);
	}
	
	// first page *************************************************************
	// origin y.
	float originX = 0.0;
	float originY = 0.0;
	
	long scale = [self getFacingPageScaleWithFirstIndex:firstIndex 
									withSecondPageIndex:secondIndex
										  withIsOnePage:NO];
	
	CGSize firstPageSize = [self getPageSize:firstIndex withPageScale:scale withPageMode:mode];

	float firstPageWidth  = firstPageSize.width;
	float firstPageHeight = firstPageSize.height;
	
	CGSize secondPageSize = [self getPageSize:secondIndex withPageScale:scale withPageMode:mode];

	float secondPageWidth  = secondPageSize.width;
	float secondPageHeight = secondPageSize.height;
	
	float pageViewWidth = firstPageWidth + secondPageWidth + offset.x * 4 + kFacePageInterval;

	float screenW = [self getScreenRect].size.width;

	originX = (screenW - pageViewWidth) / 2;
	
	// set m_PageInfoA.
	DWPageInfo pageInfoA;
	pageInfoA.m_PageNum = firstIndex;
	pageInfoA.m_Scale = scale;
	pageInfoA.m_PageFitScale = scale;

    pageInfoA.m_MaxPageScale = Utility::MAX_SPECIFY_SCALE;
	
	if (scale > Utility::MAX_SPECIFY_SCALE)
	{
		pageInfoA.m_MaxPageScale = scale;
	}
	
	pageInfoA.m_SrcRectWithAnno = CGRectMake(originX, 
											 originY, 
											 firstPageWidth  + offset.x * 2, 
											 firstPageHeight + offset.y * 2);
	
	pageInfoA.m_SrcRect = CGRectMake(originX + offset.x, 
									 originY + offset.y, 
									 firstPageWidth, 
									 firstPageHeight);
	
	pageInfoA.m_DestRect = CGRectZero;
	page.m_PageInfoA = pageInfoA;
	
	// second page *************************************************************
	originX += pageInfoA.m_SrcRectWithAnno.size.width + kFacePageInterval;
	
	DWPageInfo pageInfoB;

	pageInfoB.m_PageNum		 = secondIndex;
	pageInfoB.m_Scale		 = scale;
	pageInfoB.m_PageFitScale = scale;

    pageInfoB.m_MaxPageScale = Utility::MAX_SPECIFY_SCALE;
	
	if (scale > Utility::MAX_SPECIFY_SCALE)
	{
		pageInfoB.m_MaxPageScale = scale;
	}
    
	pageInfoB.m_SrcRectWithAnno	= CGRectMake(originX, 
											 originY, 
											 secondPageWidth  + offset.x * 2, 
											 secondPageHeight + offset.y * 2);
	
	pageInfoB.m_SrcRect			= CGRectMake(originX + offset.x, 
											 originY + offset.y, 
											 secondPageWidth, 
											 secondPageHeight);
	
	pageInfoB.m_DestRect		= CGRectZero;

	page.m_PageInfoB = pageInfoB;
}


#pragma mark -
#pragma mark get page size with scale.
- (CGSize) getPageSize:(int)index 
		 withPageScale:(long)scale
		  withPageMode:(PageInfo::PAGE_MODE)mode
{
	CGSize pageSize = CGSizeZero;
	PageInfo* pageInfo = handleDocument->GetPageInfo(index);

	if (pageInfo != nil)
	{
		float pageW = Utility::MMToPixelWithScale(pageInfo->GetWidth(mode), scale);
		float pageH = Utility::MMToPixelWithScale(pageInfo->GetHeight(mode), scale);
		pageSize = CGSizeMake(pageW, pageH);
	}
	
	return pageSize;
}


#pragma mark -
#pragma mark method for get page info with regular.
- (CGRect) getPageRectWithIndex:(int)index withPageScale:(long)scale
{	
	CGSize screenSize = [self getScreenRect].size;
	
	float backgroundWidth	= screenSize.width;
	float backgroundHeight	= screenSize.height;
	
	CGSize pageMinSize = [self getPageMinSizeWithIndex:index withPageScale:scale];

	float pageWidth		= pageMinSize.width;
	float pageHeight	= pageMinSize.height;
	
	if (pageWidth < backgroundWidth)
	{
		pageWidth = backgroundWidth;
	}

	// liuqw 20110324 start
	// イメージ部分に水平の線の不具合を修正
	float originX = 0.0;
	float originY = 0.0;

	if (pageHeight < backgroundHeight)
	{
		originY = (backgroundHeight - pageHeight) / 2;
	}
	// liuqw 20110324 end
	
	return CGRectMake((int)originX, (int)originY, (int)pageWidth, (int)pageHeight);
}


- (CGSize) getPageMinSizeWithIndex:(int)index  
					 withPageScale:(long)scale
{
	CGSize screenSize = [self getScreenRect].size;
	float backgroundWidth = screenSize.width;
	
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;

	if (showAnnotation == YES)
	{
		mode = PageInfo::kFullMode;
	}
	
	CGSize outerPageSize = [self getPageSize:index withPageScale:scale withPageMode:mode];
	float pageWidth = outerPageSize.width;
	float pageHeight = outerPageSize.height;
	
	if (showAnnotation == YES)
	{
		float offsetX = 0.0;
		PageInfo* pageInfo = handleDocument->GetPageInfo(index);

		if (pageInfo != nil)
		{
			MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);
			offsetX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
		}
		
		CGSize innerPageSize = [self getPageSize:index 
								   withPageScale:scale 
									withPageMode:(PageInfo::kPaperMode)];

		float innerPageWidth = innerPageSize.width;
		
		float interval = (backgroundWidth - innerPageWidth) / 2;

		if (offsetX < interval)
		{
			pageWidth += (interval - offsetX);
		}
	}

	return CGSizeMake(pageWidth, pageHeight);
}


- (CGFloat) getPageMinIntervalWithIndex:(int)index  
						  withPageScale:(long)scale
{
    float interval = 0.0;
	
	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth = screenSize.width;

	CGSize innerPageSize = [self getPageSize:index 
							   withPageScale:scale 
								withPageMode:(PageInfo::kPaperMode)];

	float innerPageWidth = innerPageSize.width;

	if (showAnnotation == YES)
	{
		float offsetX = 0.0;

		PageInfo* pageInfo = handleDocument->GetPageInfo(index);

		if (pageInfo != nil)
		{
			MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);

			offsetX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
		}
		
		float temp = (backgroundWidth - innerPageWidth) / 2;

		if (offsetX < temp)
		{
			interval = (temp - offsetX);
		}
	}
	else
	{
		interval = (backgroundWidth - innerPageWidth) / 2;
	}
    
	return (float)interval;
}
// liuqw 20110323 end


- (CGPoint) getPageContentOffsetWithIndex:(int)index 
						   withPageScale:(long)scale
{
	float contentOffsetX = 0.0;
	float contentOffsetY = 0.0;
	
	if (showAnnotation == YES)
	{
		CGSize screenSize = [self getScreenRect].size;
		CGSize backgroundSize = CGSizeMake(screenSize.width, screenSize.height);
		
		// get paper page size.
		CGSize innerPageSize = [self getPageSize:index withPageScale:scale withPageMode:(PageInfo::kPaperMode)];
		
		// get offset between full page and paper page.
		float offsetX = 0.0, offsetY = 0.0;

		PageInfo* pageInfo = handleDocument->GetPageInfo(index);
		
		if (pageInfo != nil)
		{
			MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);
			offsetX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
			offsetY = fabs(Utility::MMToPixelWithScale(pos.y, scale));
		}
		
		// liuqw 20110323 start
		// 次ページの一部が表示されるの対応
		float innerPageWidth = innerPageSize.width;
		float interval = (backgroundSize.width - innerPageWidth) / 2;

		if (offsetX > interval)
		{
			contentOffsetX = offsetX - interval;
		}
		// liuqw 20110323 end
		
		CGRect frameOuter = [self getPageOuterRectWithIndex:index withPageScale:scale];

		if (frameOuter.size.height > backgroundSize.height)
		{
			contentOffsetY = offsetY - (backgroundSize.height - innerPageSize.height) / 2;
		}
		else
		{
			float originY = 0.0;

			if (backgroundSize.height > frameOuter.size.height)
			{
				originY = (backgroundSize.height - frameOuter.size.height) / 2;
			}
			
			contentOffsetY = (originY + offsetY) - (backgroundSize.height - innerPageSize.height) / 2;
		}
	}

	return CGPointMake(contentOffsetX, contentOffsetY);
}


- (CGRect) getPageOuterRectWithIndex:(int)index withPageScale:(long)scale
{
	PageInfo::PAGE_MODE mode;
	
	if (showAnnotation == YES)
	{
		mode = PageInfo::kFullMode;
	}
	else
	{
		mode = PageInfo::kPaperMode;
	}
	
	CGSize pageSize = [self getPageSize:index withPageScale:scale withPageMode:mode];
	
	return CGRectMake(0, 0, pageSize.width, pageSize.height);
}

- (CGRect) getPageInnerRectWithIndex:(int)index withPageScale:(long)scale
{
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;
	CGSize pageSize = [self getPageSize:index withPageScale:scale withPageMode:mode];
	
	float pointX = 0.0;
	float pointY = 0.0;
	
	if (showAnnotation == YES)
	{
		PageInfo* pageInfo = handleDocument->GetPageInfo(index);

		if (pageInfo != nil)
		{
			MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);

			pointX = fabs(Utility::MMToPixelWithScale(pos.x, scale));
			pointY = fabs(Utility::MMToPixelWithScale(pos.y, scale));
		}
	}

	return CGRectMake(pointX, pointY, pageSize.width, pageSize.height);
}

#pragma mark -
#pragma mark method for get page info with facing mode.
- (long) getFacingPageScaleWithFirstIndex:(int)firstIndex 
					  withSecondPageIndex:(int)secondIndex
							withIsOnePage:(BOOL)onePage
{
	float scale = 100;
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;
	
	CGSize pageSize = CGSizeZero;
	if (onePage == YES)
	{
		pageSize = [self getPageSize:firstIndex withPageScale:scale withPageMode:mode];
	}
	else
	{
		CGSize firstPageSize	= [self getPageSize:firstIndex  withPageScale:scale withPageMode:mode];
		CGSize secondPageSize	= [self getPageSize:secondIndex withPageScale:scale withPageMode:mode];

		float pageWidth		= firstPageSize.width + secondPageSize.width + kFacePageInterval;
		float pageHeight	= max(firstPageSize.height, secondPageSize.height);

		pageSize = CGSizeMake(pageWidth, pageHeight);
	}

	CGRect screen = [self getScreenRect];

	float width  = (screen.size.width);
	float height = (screen.size.height);

	if (showAnnotation == YES &&
		documentType == DOC_TYPE_XDW)
	{
		width  =  screen.size.width - (kFacePageEdgeWidth * 2);
		height = (screen.size.height - kFacePageEdgeWidth * 2);
	}
	
	float scaleX = width  / pageSize.width  * scale;
	float scaleY = height / pageSize.height * scale;
	
	scale = scaleX > scaleY ? scaleY : scaleX;
	
	return (long)scale;
}


- (CGRect) getFacingPageViewRectWidthIndex:(int)index
{
	int firstIndex = 0;
	int secondIndex = 0;
	
	if (facingMode == MODE_FACE_NO)
	{
		if (fontOrient == YES)
		{
			if ([self isFacingPageContainTowPages:index] == NO)
			{
				firstIndex = index * 2;
			}
			else
			{
				firstIndex  = index * 2;
				secondIndex = index * 2 + 1;
			}
		}
		else
		{
			if ([self isFacingPageContainTowPages:index] == NO)
			{
				firstIndex = index * 2;
			}
			else
			{
				firstIndex  = index * 2 + 1;
				secondIndex = index * 2;
			}
		}
	}
	else if (facingMode == MODE_FACE_YES)
	{
		if (index == 0)
		{
			firstIndex = 0;
		}
		else
		{
			if (fontOrient == YES)
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					firstIndex = index * 2 - 1;
				}
				else
				{
					firstIndex  = index * 2 - 1;
					secondIndex = index * 2;
				}
			}
			else
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					firstIndex = index * 2 - 1;
				}
				else
				{
					firstIndex  = index * 2;
					secondIndex = index * 2 - 1;
				}
			}
		}
	}
	
	PageInfo::PAGE_MODE mode = PageInfo::kPaperMode;
	CGPoint offset = CGPointZero;

	if (showAnnotation == YES &&
		documentType == DOC_TYPE_XDW)
	{
		offset = CGPointMake(kFacePageEdgeWidth, kFacePageEdgeWidth);
	}
	
	
	if ([self isFacingPageContainTowPages:index] == NO)
	{
		long scale = [self getFacingPageScaleWithFirstIndex:firstIndex 
										withSecondPageIndex:secondIndex
											  withIsOnePage:YES];

		CGSize pageSize = [self getPageSize:firstIndex 
							  withPageScale:scale 
							   withPageMode:mode];
		
		float originX = 0;
		float screenW = [self getScreenRect].size.width;

		originX = (screenW - pageSize.width) / 2;
		originX -= offset.x;
		
		float originY = 0;
		float screenH = [self getScreenRect].size.height;

		originY = (screenH - pageSize.height) / 2;
		originY -= offset.y;
		
		originX = 0.0;
		originY = 0.0;

		float pageViewWidth = pageSize.width + offset.x * 2;

		if (pageViewWidth < screenW)
		{
			pageViewWidth = screenW;
		}
		
		float pageViewHeight = pageSize.height + offset.y * 2;

		if (pageViewHeight < screenH)
		{
			originY = (screenH - pageViewHeight) / 2;
		}
		
		return CGRectMake(originX, 
						  originY, 
						  pageViewWidth, 
						  pageViewHeight);
	}
	else
	{
		long scale = [self getFacingPageScaleWithFirstIndex:firstIndex 
										withSecondPageIndex:secondIndex
											  withIsOnePage:NO];

		CGSize firstPageSize	= [self getPageSize:firstIndex withPageScale:scale withPageMode:mode];
		CGSize secondPageSize	= [self getPageSize:secondIndex withPageScale:scale withPageMode:mode];

		CGSize pageSize			= CGSizeMake(firstPageSize.width + secondPageSize.width + kFacePageInterval,
											 max(firstPageSize.height, secondPageSize.height));
		
		float originX = 0;
		float originY = 0;
		float screenH = [self getScreenRect].size.height;
		originY = (screenH - pageSize.height) / 2;
		originY -= offset.y;
		
		float firstPageWidth = firstPageSize.width + offset.x * 2 + kFacePageInterval / 2;
		float secondPageWidth = secondPageSize.width + offset.x * 2 + kFacePageInterval / 2;
		float pageViewWidth = firstPageWidth + secondPageWidth;
		float pageViewHeight = pageSize.height + offset.y * 2;
		
		originX = 0.0;
		float screenW = [self getScreenRect].size.width;

		if (pageViewWidth < screenW)
		{
			pageViewWidth = screenW;
		}
		
		if (pageViewHeight < screenH)
		{
			originY = (screenH - pageViewHeight) / 2;
		}
		
		return CGRectMake(originX, originY, pageViewWidth, pageViewHeight); 
	}
}


#pragma mark -
#pragma mark method for zoom page view.
// update page view status for zoom.
- (void) updatePageViewStatusForZoom:(DWScrollView*)pageView 
					   withZoomScale:(float)scale 
				withRestoreToPageFit:(BOOL)restore
{
	if (pageView != nil)
	{
		// 1.get new zoom scale
		float zoomScale = scale;
		
		
		/*
		// 2. update page status
        if (zoomScale == Utility::MIN_SCALE)
		{
			pageStatus = PAGE_STATUS_FIT;
		}
		else
		{
			pageStatus = PAGE_STATUS_ZOOM;
		}
		 */

		
		// 3. update pagefit status
		if (pageStatus == PAGE_STATUS_ZOOM)
		{
			isPageFit = NO;
		}
		else
		{
			isPageFit = YES;
		}
		
		
		// 4. update page info.
		[self updatePageInfo:pageView.page withZoomScale:zoomScale];
		
		
		// 5. update new zoom scale
		pageZoomScale = zoomScale;
		
		// 6. update page offset
		
		// 7. update page view scroll enabled
        if (pageStatus != PAGE_STATUS_FIT)
		{
			pageView.scrollEnabled = YES;
		}

		
		// 8. update pagescale
        pageScale = pageView.baseScale * scale;
        
        if (pageView.zoomScale == pageView.maximumZoomScale)
		{
            pageScale = pageView.maxScale;
        }
        
        if (pageView.zoomScale == pageView.minimumZoomScale)
		{
			pageScale = pageView.minScale;
		}
		
		isZoomEnd = NO;
	}
}

- (void) updatePageInfo:(DWPageView*)page withZoomScale:(float)scale
{
	if (page == nil)
	{
		return;
	}
	
	// update pageInfoA
	DWPageInfo pageInfoA = page.m_PageInfoA;

	if (pageInfoA.m_PageNum != -1)
	{
		long currScale = pageInfoA.m_PageFitScale * scale;

		if (currScale <= pageInfoA.m_PageFitScale)
		{
			currScale =  pageInfoA.m_PageFitScale;
		}
		
		pageInfoA.m_Scale = currScale;
		page.m_PageInfoA = pageInfoA;
	}
	
	// update pageInfoB
	DWPageInfo pageInfoB = page.m_PageInfoB;
	if (pageInfoB.m_PageNum != -1)
	{
		long currScaleB = pageInfoB.m_PageFitScale * scale;

		if (currScaleB <= pageInfoB.m_PageFitScale)
		{
			currScaleB =  pageInfoB.m_PageFitScale;
		}
		
		pageInfoB.m_Scale = currScaleB;
		page.m_PageInfoB = pageInfoB;
	}
}


- (long) getPageScaleWithIndex:(int)index withPageMode:(PageInfo::PAGE_MODE)mode
{
	float scale = 100;
	CGSize pageSize = [self getPageSize:index 
						  withPageScale:scale 
						   withPageMode:mode];
	
	if (pageSize.width != 0 && pageSize.height != 0)
	{
		CGRect screen = [self getScreenRect];

		float scaleX = (float)screen.size.width  / pageSize.width  * scale;
		float scaleY = (float)screen.size.height / pageSize.height * scale;

		scale = scaleX > scaleY ? scaleY : scaleX;
	}
	
	return (long)scale;
}


- (float) getPageFullZoomScale:(DWScrollView*)pageView
{
	long paperScale = [self getPageScaleWithIndex:pageView.index 
									 withPageMode:(PageInfo::kPaperMode)];
	long fullScale = [self getPageScaleWithIndex:pageView.index 
									withPageMode:(PageInfo::kFullMode)];
    if (fullScale > 100)
	{
        fullScale = 100;
    }

	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
    // AR17879 2011/06/29 M.Chikyu start
	if (fullScale == paperScale)
	{
		// ページフィットと付箋フィットの倍率同じ場合に両方の倍率に差をつける
		return 0.999;
	}
	// AR17879 2011/06/29 M.Chikyu end
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	return ((float)fullScale / (float)paperScale);
}


- (float) getPageMaxZoomScale:(DWScrollView*)pageView
{
    long paperScale = [self getPageScaleWithIndex:pageView.index 
									 withPageMode:(PageInfo::kPaperMode)];
	long maxScale = Utility::MAX_SPECIFY_SCALE;
	
	if (paperScale > Utility::MAX_SPECIFY_SCALE)
	{
        maxScale = paperScale;
    }
	
	return ((float)maxScale / (float)paperScale);
}


- (long) getFacingPageScalewithIndex:(int)index
{
    long scale = 100;
    int firstIndex = 0;
	int secondIndex = 0;
	
	if (facingMode == MODE_FACE_NO)
	{
		if (fontOrient == YES)
		{
			if ([self isFacingPageContainTowPages:index] == NO)
			{
				firstIndex = index * 2;
			}
			else
			{
				firstIndex = index * 2;
				secondIndex = index * 2 + 1;
			}
		}
		else
		{
			if ([self isFacingPageContainTowPages:index] == NO)
			{
				firstIndex = index * 2;
			}
			else
			{
				firstIndex = index * 2 + 1;
				secondIndex = index * 2;
			}
		}
	}
	else if (facingMode == MODE_FACE_YES)
	{
		if (index == 0)
		{
			firstIndex = 0;
		}
		else
		{
			if (fontOrient == YES)
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					firstIndex = index * 2 - 1;
				}
				else
				{
					firstIndex = index * 2 - 1;
					secondIndex = index * 2;
				}
			}
			else
			{
				if ([self isFacingPageContainTowPages:index] == NO)
				{
					firstIndex = index * 2 - 1;
				}
				else
				{
					firstIndex = index * 2;
					secondIndex = index * 2 - 1;
				}
			}
		}
	}
	
	if ([self isFacingPageContainTowPages:index] == NO)
	{
		scale = [self getFacingPageScaleWithFirstIndex:firstIndex 
                                   withSecondPageIndex:secondIndex
                                         withIsOnePage:YES];
	}
	else
	{
		scale = [self getFacingPageScaleWithFirstIndex:firstIndex 
                                   withSecondPageIndex:secondIndex
                                         withIsOnePage:NO];
	}
	
    return scale;
}


- (CGPoint) getPageCurrentOriginWithPageView:(DWScrollView*)pageView
{
	if (pageView == nil)
	{
		return CGPointZero;
	}
	
	float zoomScale = pageView.zoomScale;

	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;
	
	// 1. get page origin.
	float pageFullWidth = pageView.page.frame.size.width;

	float originX = (backgroundWidth - pageFullWidth) / 2;

	float minOriginX = -(pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x * zoomScale);

	if (originX < minOriginX)
	{
		originX = minOriginX;
	}
    
    if (pageView.isFacingPage == NO)
	{
		float pageFullWidth = pageView.page.m_PageInfoA.m_SrcRectWithAnno.size.width;
		pageFullWidth = pageFullWidth * zoomScale;

		originX = (backgroundWidth - pageFullWidth) / 2;
		float minOriginX = -(pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x * zoomScale);

		if (originX <= 0)
		{
			originX = minOriginX;
		}
		else
		{
			originX = minOriginX + originX;
		}
	}
    
	float pageFullHeight = pageView.page.frame.size.height;
	float originY = (backgroundHeight - pageFullHeight) / 2;
	float minOriginY = -(pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.y * zoomScale);

	if (originY < minOriginY)
	{
		originY = minOriginY;
	}
	
	return CGPointMake(originX, originY);
}


- (CGSize) getPageViewCurrentContentSizeWithPageView:(DWScrollView*)pageView
{
	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;
	
	if (pageView == nil)
	{
		return CGSizeMake(backgroundWidth, backgroundHeight);
	}
	
	// 1. get page origin.
	CGPoint pageOrigin = [self getPageCurrentOriginWithPageView:pageView];
		
	// 2. get page size.
	float pageWidth = pageView.page.frame.size.width;

	if (showAnnotation == YES)
	{
		float offsetX = 0.0;

		if (pageView.isFacingPage == NO)
		{
			long scale = pageView.page.m_PageInfoA.m_PageFitScale;
			CGSize pageMinSize = [self getPageMinSizeWithIndex:pageView.index withPageScale:scale];
			float pageMinWidth = pageMinSize.width;
			
			if (pageMinWidth < backgroundWidth)
			{
				offsetX = backgroundWidth - pageMinWidth;
			}
		}
		
		if (pageWidth < backgroundWidth)
		{
			pageWidth = backgroundWidth;
		}
		else
		{
			if (pageView.isFacingPage == NO)
			{
				pageWidth += pageOrigin.x;
				pageWidth -= offsetX * pageView.zoomScale;
			}
			else
			{
				pageWidth += pageOrigin.x * 2;
			}
		}
	}
	else
	{
		if (pageWidth < backgroundWidth)
		{
			pageWidth = backgroundWidth;
		}
		else
		{
			pageWidth += pageOrigin.x * 2;
		}
	}
	
	float pageHeight = pageView.page.frame.size.height;
	
	// liuqw 20110324 start
	// イメージ部分に水平の線の不具合を修正
	/*
	if (pageHeight < backgroundHeight) {
		pageHeight = backgroundHeight;
	} else {
		pageHeight += pageOrigin.y * 2;
	}
	*/ 
	pageHeight += pageOrigin.y * 2;
	// liuqw 20110324 end
    
    if (pageView.isFacingPage == NO)
	{
		float pageWidth_ = (pageView.page.m_PageInfoA.m_SrcRectWithAnno.size.width);
        pageWidth_ = pageWidth_ * pageView.zoomScale;

        float minOriginX = (pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x * pageView.zoomScale);
        pageWidth = (minOriginX - fabs(pageOrigin.x)) + pageWidth_;
    }
	
	return CGSizeMake(pageWidth, pageHeight);
}


- (void) resetPageViewContentSize:(DWScrollView*)pageView
{
	CGSize pageContentSize = [self getPageViewCurrentContentSizeWithPageView:pageView];
	pageView.contentSize = CGSizeMake(pageContentSize.width, pageContentSize.height);
}


- (CGPoint) getPageOriginWithPageView:(DWScrollView*)pageView 
                        withZoomScale:(float)zoomScale
{
    if (pageView == nil) {
		return CGPointZero;
	}
	
	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;
	
	// 1. get page origin.
    CGRect frame = [self getPageRectWithIndex:pageView.index 
                                withPageScale:pageView.baseScale];

	float pageFullWidth	= frame.size.width * zoomScale;
	float originX		= (backgroundWidth - pageFullWidth) / 2;
	float minOriginX	= -(pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.x * zoomScale);

	if (originX < minOriginX)
	{
		originX = minOriginX;
	}
	
	float pageFullHeight= frame.size.height * zoomScale;
	float originY		= (backgroundHeight - pageFullHeight) / 2;
	float minOriginY	= -(pageView.page.m_PageInfoA.m_SrcRectWithAnno.origin.y * zoomScale);

	if (originY < minOriginY)
	{
		originY = minOriginY;
	}
	
	return CGPointMake(originX, originY);
}


- (CGSize) getPageViewContentSizeWithPageView:(DWScrollView*)pageView
                                withZoomScale:(float)zoomScale

{
	CGSize screenSize = [self getScreenRect].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;
	
	if (pageView == nil)
	{
		return CGSizeMake(backgroundWidth, backgroundHeight);
	}
	
	// 1. get page origin.
	CGPoint pageOrigin = [self getPageOriginWithPageView:pageView withZoomScale:zoomScale];
    
	// 2. get page size.
    CGRect frame = [self getPageRectWithIndex:pageView.index 
                                withPageScale:pageView.baseScale];
	float pageWidth = frame.size.width * zoomScale;

	if (showAnnotation == YES)
	{
		float offsetX = 0.0;

		if (pageView.isFacingPage == NO)
		{
			long scale = pageView.page.m_PageInfoA.m_PageFitScale;

			CGSize pageMinSize = [self getPageMinSizeWithIndex:pageView.index withPageScale:scale];

			float pageMinWidth = pageMinSize.width;
			
			if (pageMinWidth < backgroundWidth)
			{
				offsetX = backgroundWidth - pageMinWidth;
			}
		}
		
		if (pageWidth < backgroundWidth)
		{
			pageWidth = backgroundWidth;
		}
		else {
			if (pageView.isFacingPage == NO)
			{
				pageWidth += pageOrigin.x;
				pageWidth -= offsetX * zoomScale;
			}
			else
			{
				pageWidth += pageOrigin.x * 2;
			}
		}
	}
	else
	{
		if (pageWidth < backgroundWidth) {
			pageWidth = backgroundWidth;
		}
		else
		{
			pageWidth += pageOrigin.x * 2;
		}
	}
	
    float pageHeight = frame.size.height * zoomScale;
	pageHeight += pageOrigin.y * 2;
	
	return CGSizeMake(pageWidth, pageHeight);
}


#pragma mark -
#pragma mark UIScrollView delegate methods
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
	
	DWScrollView* pageView = (DWScrollView*)scrollView;
    
    if (pageView.isActivePage == YES)
	{
		pageOffset = scrollView.contentOffset;
	}
	
	// tongtx 2012.03.29 start
	// 選択機能の追加
	if (scrollView.isZooming == NO) 
	{
		[documentViewController restoreCopyMenu];
	}
	// tongtx 2012.03.29 end
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
	DWScrollView* pageView = (DWScrollView*)scrollView;

	return pageView.page;
}


- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView 
						  withView:(UIView *)view __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2)
{
    scrollView.scrollEnabled = YES;
}

- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView 
					   withView:(UIView *)view 
						atScale:(float)scale
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	pageStatus = PAGE_STATUS_ZOOM;
	// 2012.02.01(Ver2.1 New) M.Chikyu
	
	DWScrollView* pageView = (DWScrollView*)scrollView;
	if (pageView == nil)
	{
		return;
	}
	
	if (pageView.isActivePage == YES)
	{
		pageOffset = scrollView.contentOffset;
	}

	[self updatePageViewStatusForZoom:pageView 
						withZoomScale:scale 
				 withRestoreToPageFit:YES];
}


- (void)scrollViewDidZoom:(UIScrollView *)scrollView 
{
	DWScrollView* pageView = (DWScrollView*)scrollView;

	if (nil == pageView || nil == pageView.page)
	{
		return;
	}
	
	// get page.
	DWPageView *page =  pageView.page;
	
	if (isZoomEnd == NO)
	{
		if (pageView.zoomScale == Utility::MIN_SCALE)
		{
			if (pageView.isFacingPage == NO)
			{
				long scale = [self getPageScaleWithIndex:pageView.index withPageMode:(PageInfo::kPaperMode)];
				page.frame = [self getPageRectWithIndex:pageView.index withPageScale:scale];
				pageView.contentOffset = pageView.initContentOffset;
			}
			else
			{
				CGRect pageRect = [self getFacingPageViewRectWidthIndex:pageView.index];
				float originY = pageRect.origin.y;
				page.frame = CGRectMake(0.0, originY, page.frame.size.width, page.frame.size.height);
			}
		}
		else
		{
			// 1. reset page origin for zoom.
			CGPoint pageOrigin = [self getPageCurrentOriginWithPageView:pageView];
			page.frame = CGRectMake(pageOrigin.x, pageOrigin.y, page.frame.size.width, page.frame.size.height);
			
			// 2. reset pageview contentsize for zoom.
			CGSize pageContentSize = [self getPageViewCurrentContentSizeWithPageView:pageView];
			pageView.contentSize = CGSizeMake(pageContentSize.width, pageContentSize.height);
		}
	}
	else
	{
		if (pageView.zoomScale == Utility::MIN_SCALE && self.isPageFit == YES)
		{
			if (pageView.isFacingPage == NO)
			{
				long scale = [self getPageScaleWithIndex:pageView.index withPageMode:(PageInfo::kPaperMode)];
				page.frame = [self getPageRectWithIndex:pageView.index withPageScale:scale];
				pageView.contentOffset = pageView.initContentOffset;
			}
			else
			{
				CGRect pageRect = [self getFacingPageViewRectWidthIndex:pageView.index];
				float originY = pageRect.origin.y;
				page.frame = CGRectMake(0.0, originY, page.frame.size.width, page.frame.size.height);
			}
		}
        else
		{
			// 1. reset page origin for zoom.
			CGPoint pageOrigin = [self getPageCurrentOriginWithPageView:pageView];
			page.frame = CGRectMake(pageOrigin.x, pageOrigin.y, page.frame.size.width, page.frame.size.height);
			
			// 2. reset pageview contentsize for zoom.
			CGSize pageContentSize = [self getPageViewCurrentContentSizeWithPageView:pageView];
			pageView.contentSize = CGSizeMake(pageContentSize.width, pageContentSize.height);
		}
	}
	
	// tongtx 2012.04.01 start
	// 選択機能の追加
	[documentViewController restoreCopyMenu];
	// tongtx 2012.04.01 end
}


- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate
{
	DWScrollView* pageView = (DWScrollView*)scrollView;
	if (pageView.isActivePage == YES)
	{
		pageOffset = scrollView.contentOffset;
	}
}


// called when scroll view grinds to a halt
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView     
{
	DWScrollView* pageView = (DWScrollView*)scrollView;

	if (pageView.isActivePage == YES)
	{
		pageOffset = scrollView.contentOffset;
	}
}


#pragma mark -
#pragma mark private method.
- (CGRect) getScreenRect
{
	long pageWidth = 0;
	long pageHeight = 0;
	CGRect screenFrame = [[UIScreen mainScreen] bounds];

	if ([self UIDeviceIsPortrait] == YES)
	{
		pageWidth = screenFrame.size.width;
		pageHeight = screenFrame.size.height;
	}
	else
	{
		pageWidth = screenFrame.size.height;
		pageHeight = screenFrame.size.width;
	}
	
	return CGRectMake(0, 0, pageWidth, pageHeight);
}


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


- (UIColor*) getBackGround
{
	
	if (nil != bgColor)
	{
		return bgColor;
	}
	
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	if (nil == colorSpace)
	{
		return nil;
	}
	
	// メッシュサイズ
	size_t width = 24;
	size_t height = 24;
	
	size_t bitsPerComponent = 8;
	size_t bytesPerRow = ((((unsigned int)width * 4) +15) / 16) *16;
	
	CGContextRef bgCtx = CGBitmapContextCreate(NULL, 
											   width,
											   height,
											   bitsPerComponent,
											   bytesPerRow,
											   colorSpace,
											   kCGImageAlphaPremultipliedLast 
											   | kCGBitmapByteOrder32Big);
	
	CGColorSpaceRelease(colorSpace);
	
	if (nil == bgCtx)
	{
		return nil;
	}
	
	CGContextSaveGState(bgCtx);
	
	CGRect bgRect = CGRectNull;

	// メッシュサイズ
	int nRectSize = 12;
	
	//compute background draw rect count
	int nHRectCount = width / nRectSize;
	int nVRectCount = height / nRectSize;
	
	CGContextBeginPath(bgCtx);

	//start draw default background  
	int i, j;

	for ( i=0; i <= nVRectCount; i++ )
	{
		for ( j=0; j <= nHRectCount; j++ )
		{
			bgRect = CGRectMake((i*nRectSize*2+j%2*nRectSize), 
								(j*nRectSize), nRectSize, nRectSize);
			
			// メッシュカラー
			CGContextSetRGBFillColor(bgCtx, 
									 Utility::BACK_GROUND_WHITE_COLOR,
									 Utility::BACK_GROUND_WHITE_COLOR,
									 Utility::BACK_GROUND_WHITE_COLOR, 1);
			
			CGContextAddRect(bgCtx, bgRect);
		}
	}

	CGContextDrawPath(bgCtx, kCGPathFill);

	for ( i=0; i <= nVRectCount; i++ )
	{
		for ( j=0; j <= nHRectCount; j++ )
		{
			bgRect = CGRectMake((i*nRectSize*2+(j+1)%2*nRectSize), 
								(j*nRectSize), nRectSize, nRectSize);
			
			// メッシュカラー
			CGContextSetRGBFillColor(bgCtx, 
									 Utility::BACK_GROUND_WHITE_COLOR - 0.05,
									 Utility::BACK_GROUND_WHITE_COLOR - 0.05,
									 Utility::BACK_GROUND_WHITE_COLOR - 0.05, 1);
			
			CGContextAddRect(bgCtx, bgRect);
		}
	}
	
	CGContextDrawPath(bgCtx, kCGPathFill);
	CGContextRestoreGState(bgCtx);
	
	CGImageRef cgImage = CGBitmapContextCreateImage(bgCtx);
	CGContextRelease(bgCtx);

	if (nil == cgImage)
	{
		return nil;
	}
	
	UIImage* image  = [[UIImage alloc] initWithCGImage:cgImage];
	CGImageRelease(cgImage);

	if (nil == image)
	{
		return nil;
	}
	
	bgColor = [[UIColor alloc] initWithPatternImage:image];
	
	return bgColor;
}


#pragma mark -
#pragma mark document edtion method.
// ページ編集機能の追加
- (BOOL) loadXDWDocumentForUpdate:(NSString *)documentPath
{
    if(documentPath != nil)
	{
		if ([[documentPath pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
			[[documentPath pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
		{
			handleDocument = new XdwDocumentHandle();
			documentType = DOC_TYPE_XDW;
		}
		else
		{
            return NO;
		}
		
		const char *fileName_const_char = [documentPath UTF8String];
		char fileName_char[1024] = { 0 };
		strcpy(fileName_char, fileName_const_char);
		
		// xuxinjun 2012.03.23 start
		// 保護文書の対応
		XdwErrorCode ret = XDW_ERRORCODE_SUCCESS;
		
		/*
		ret = handleDocument->OpenDocumentForUpdate(fileName_char);
		 */
		
		if (openPassword_ != nil)
		{
			const char *pwd_const_char = [openPassword_ UTF8String];
			char pwd_char[1024] = { 0 };
			strcpy(pwd_char, pwd_const_char);
			
			ret = handleDocument->OpenDocumentForUpdate(fileName_char, pwd_char);
		} 
		else
		{
			ret = handleDocument->OpenDocumentForUpdate(fileName_char, NULL);
		}
		// xuxinjun 2012.03.23 end
		
		if (ret != XDW_ERRORCODE_SUCCESS)
		{
			return NO;
		}
    }
    return YES; 
}


- (BOOL) reloadXDWDocument:(NSString *)documentPath
{
    if (nil != drawer)
	{
		[drawer breakDrawing];
		[drawer release];
	}

	if (handleDocument != NULL)
	{
		handleDocument->Destroy();
		delete handleDocument;	
		handleDocument = NULL;
	}

	BOOL ret = [self loadXDWDocumentForUpdate:documentPath];

	if (NULL != handleDocument && ret)
	{
		drawer = [[DWDrawer alloc]initWithDocumentHandle:handleDocument];
	}

    return YES;
}


- (BOOL) isDocumentVersionUpdated
{
	int version = handleDocument->GetStorageVersion();
    
	if (documentVersion < version)
	{
		return YES;
	}
    
    return NO;
}


- (BOOL) saveDocumentUpdateContent
{
	if ([self isTempFileEditing] == YES)
	{
		// get application directory
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentPath = [paths objectAtIndex:0];

		if (documentViewController.filePath == nil)
		{
			return NO;
		}
		
		NSString* fileName = [[documentViewController.filePath lastPathComponent] copy];
		NSString* dstFilePathName = [[documentPath stringByAppendingFormat:@"/%@", fileName] copy];
		
		NSString* tempPlistFileName = [documentViewController.filePath stringByDeletingPathExtension];
		tempPlistFileName = [tempPlistFileName stringByAppendingFormat:@".plist"];
		
		NSFileManager* fileManager = [NSFileManager defaultManager];
		
		NSError* fileError = nil;

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
		
		[fileManager moveItemAtPath:documentViewController.filePath 
							 toPath:dstFilePathName 
							  error:&fileError];
		
		documentViewController.filePath = dstFilePathName;
		
		[fileManager removeItemAtPath:tempPlistFileName error:nil];
		
		[dstFilePathName release];
		[fileName release];

		if (fileError == nil)
		{
			return YES;
		}
		else
		{
			return NO;
		}
	}
	
	return NO;
}


- (void) returnToDisplayModeOnEndEditSuccess:(BOOL)succeed
{
    int index = pageIndex;
    
    if (succeed == YES)
	{
		// save annotation edit content
		handleDocument->SaveDocumentModified();
	}
	else
	{
		// update src file path to file path. 
		NSString* fileName_ = [documentViewController.filePath lastPathComponent];
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentPath = [paths objectAtIndex:0];
		NSString* filePath_= [documentPath stringByAppendingPathComponent:fileName_];
        documentViewController.filePath = filePath_;
    }
    
    // reload document handle.
    if (nil != drawer)
	{
		[drawer breakDrawing];
		[drawer release];
	}
	
	if (handleDocument != NULL)
	{
        handleDocument->Destroy();
		delete handleDocument;	
		handleDocument = NULL;
	}
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	if (logicAnnMananger_ != NULL)
	{
		delete logicAnnMananger_;
		logicAnnMananger_ = NULL;
	}
	// tongtx 2012.03.23 end
    
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//[self loadXDWDocument:(documentViewController.filePath)];
	BOOL ret = [self loadXDWDocument:(documentViewController.filePath) andOpenPassword:self.openPassword];
	// xuxinjun 2012.03.23 end

	if (NULL != handleDocument)
	{
        drawer = [[DWDrawer alloc]initWithDocumentHandle:handleDocument];
		
		// tongtx 2012.03.23 start
		// 選択機能の追加
		logicAnnMananger_ = new LogicAnnotationManager(handleDocument);
		// tongtx 2012.03.23 end
    }
    
	
	[self setAnnotationDisplay:YES];
	[documentViewController resetAnnnotationButtonStatus];
	
    // update annotation list.
    handleDocument->UpdateLinkAnnotationList();
    [documentViewController reloadAnnotationList];
    
    [documentViewController removePageViewsFromScrollView];

	if (self.fontOrient == NO)
    {
        index = [self getPageViewCount] - 1 - index;
    }
    [documentViewController insertPageViewWithPosition:index];
	
	// reset document rotation state
	[documentViewController updateControlStatusForRotation];
	interfaceOrientation = documentViewController.interfaceOrientation;
	
	[documentViewController resetLeftBarItem];

	self.isPageFit = YES;

    [[documentViewController getActivePageView].page setNeedsDisplay];
}

- (BOOL) isEditingFileErrorSaved
{
    if (nil != drawer)
	{
		[drawer breakDrawing];
		[drawer release];
        drawer = nil;
	}
	
	if (handleDocument != NULL)
	{
		handleDocument->Destroy();
		delete handleDocument;	
		handleDocument = NULL;
	}
    
    // xuxinjun 2012.03.23 start
	// 保護文書の対応
	/*
	 if ([self loadXDWDocument:(documentViewController.filePath)] == YES)
	 {
	 return NO;
	 }
	 */
	if ([self loadXDWDocument:(documentViewController.filePath) andOpenPassword:self.openPassword] == YES)
    {
        return NO;
    }
	// xuxinjun 2012.03.23 end
	
    {
        return NO;
    }
	
    return YES;
}


- (BOOL) copyEditFileToTempDirectory
{
    // 1. delete temp file in temp directory
	[self cleanTempDirectory];
	
	// 2. create temp file directory
	NSFileManager* tempFileManager =[NSFileManager defaultManager];

	if (tempFileManager == nil)
	{
		return NO;
	}
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *tempPath = [paths objectAtIndex:0];
	
	NSString *tempDirectoryPath = [tempPath stringByAppendingString:TEMP_DIRECTORY_NAME];
	
	BOOL isDirectoryExist = [tempFileManager fileExistsAtPath:tempDirectoryPath];
	
	if (!isDirectoryExist)
	{
		[tempFileManager createDirectoryAtPath:tempDirectoryPath 
				   withIntermediateDirectories:YES 
									attributes:nil 
										 error:nil];
        
	}
	
	// 3. get file name from filePath
	NSString* tempFileName = nil;
	NSString* tempFilePathName = nil;
	if (documentViewController.filePath == nil)
	{
		return NO;
	}
	else
	{
		tempFileName = [documentViewController.filePath lastPathComponent];
		tempFilePathName = [tempDirectoryPath stringByAppendingString:tempFileName];
	}
    
	// 4. save src file date and size
	NSString* tempPlistFileName = [tempFilePathName stringByDeletingPathExtension];
	tempPlistFileName = [tempPlistFileName stringByAppendingFormat:@".plist"];
	
	NSDictionary* fileAttrs = [tempFileManager attributesOfItemAtPath:documentViewController.filePath error:nil];
	[fileAttrs writeToFile:tempPlistFileName atomically:YES];
    
    NSError* error = nil;
    [tempFileManager copyItemAtPath:documentViewController.filePath 
                             toPath:tempFilePathName 
                              error:&error];
    if (error == nil)
    {
        documentViewController.filePath = tempFilePathName;
        return YES;
    }
	
    return NO;
}


- (BOOL) isTempFileEditing
{
    if (documentViewController.filePath == nil)
	{
		return NO;
	}
	
	NSArray* filePathArray = [documentViewController.filePath componentsSeparatedByString:@"/"];

	if ([filePathArray count] > 2)
	{
		int tempPathIndex = [filePathArray count]-2;
		NSString* tempPath = [filePathArray objectAtIndex:tempPathIndex];
		NSString* tempString = [NSString stringWithFormat:@"/%@/", tempPath];

		if ([tempString isEqualToString:TEMP_DIRECTORY_NAME] == NO)
		{
			return NO;
		}
    }
    
    return YES;
}


- (void) cleanTempDirectory
{
	[drawer breakDrawing];
    
	if ([self isTempFileEditing] == YES)
	{
		if (handleDocument != nil)
		{
			handleDocument->CloseCurrentFile();
		}
	}
	
	NSFileManager* tempFileManager =[NSFileManager defaultManager];
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString* tempPath = [paths objectAtIndex:0];
	NSString* tempDirectoryPath = [tempPath stringByAppendingString:TEMP_DIRECTORY_NAME];
	NSArray *files = [tempFileManager contentsOfDirectoryAtPath:tempDirectoryPath error:nil];
	NSString *fullPath;
    
	BOOL bIsDirectory = NO;

	for (NSString* item in files)
    {
		fullPath = [tempDirectoryPath stringByAppendingPathComponent:item];
		[tempFileManager fileExistsAtPath:fullPath isDirectory:&bIsDirectory];
		
		if ( bIsDirectory )
		{
			continue;
		}
		
		[tempFileManager removeItemAtPath:fullPath error:nil];
	}
}


- (NSString*) getFileFullName
{
	return documentViewController.filePath;
}


- (void) dealloc
{
	if (nil != drawer)
	{
		[drawer breakDrawing];
		[drawer release];
	}
	
	if (handleDocument != NULL)
	{
		delete handleDocument;	
		handleDocument = NULL;
	}
	
	if (nil != bgColor)
	{
		[bgColor release];
		bgColor = nil;
	}
	
	if (nil != zoomOutLock)
	{
		[zoomOutLock release];
		zoomOutLock = nil;
	}
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	if (logicAnnMananger_ != NULL)
	{
		delete logicAnnMananger_;	
		logicAnnMananger_ = NULL;
	}
	// tongtx 2012.03.23 end
	
    [super dealloc];
}

// xuxinjun 2012.03.23 start
// パーミッションの対応.
#pragma mark -
#pragma mark mehtod Get Doc Permission.
- (BOOL) getPermissionForAnnoEdition
{
	MP_Permission perm = handleDocument->GetPermission();
	
	if ((perm & MP_PERM_ANNO_EDIT) == MP_PERM_ANNO_EDIT) 
	{
		return YES;
	}

	return NO;
}

- (BOOL) getPermissionForCopy
{
	MP_Permission perm = handleDocument->GetPermission();
	
	if ((perm & MP_PERM_COPY) == MP_PERM_COPY) 
	{
		return YES;
	}
	
	return NO;
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
#pragma mark -
#pragma mark mehtod search text.
- (void) beginSearchText
{
	if (textInfoInput != NULL)
	{
		textInfoInput->Destroy();
	}
	textInfoInput = NULL;
}

- (BOOL) searchText:(DWSearchInfo*)info
{
	if (info == nil) return NO;
	
	// 1. search page index.
	int pageIndex_ = 0;
	int startPageIndex = info.startPageIndex;
	int endPageIndex = info.endPageIndex;
	
	// 2. search text
	int count_ = [info.text length];
    unsigned short *src = (unsigned short*)[info.text cStringUsingEncoding:NSUTF16StringEncoding];
    unsigned short *dst = new unsigned short[count_ + 1];
    for (int i = 0; i < count_; i++)
	{
		dst[i] = src[i];
	}
    dst[count_] = 0;
    
	// 3. is next search.
	bool next = true;
	if (info.next == NO) next = false;
	
	// 4. anno show on/off.
	bool display = true;
	if (showAnnotation == NO) display = false;
	
	// 5. MP_SearchTextInfo index.
	MP_AnnoInfo *annoInfo_ = new MP_AnnoInfo;
	annoInfo_->annoIndex = info.annoIndex;
	
	MP_TextInfo *textInfoResult = NULL;
	
	BOOL result = NO;
	HRESULT hres = handleDocument->SearchText(pageIndex_, startPageIndex, endPageIndex, dst, next, display, textInfoInput, &textInfoResult, annoInfo_);
	if (hres != MP_S_NO_RES) 
	{
		[info.mmSearchRects removeAllObjects];
		
		info.pageIndex = pageIndex_;
		
		if (hres == MP_S_IN_PAGE) 
		{
			info.annoIndex = annoInfo_->annoIndex;
			
			if (textInfoResult != NULL && textInfoResult->nRecordCount > 0)
			{
				if (textInfoInput != NULL)
				{
					textInfoInput->Destroy();
				}
				textInfoInput = textInfoResult;
				
				for (int i = 0; i < textInfoResult->nRecordCount; i++) {
					MP_TextRect textRect = textInfoResult->pTextRects[i];
					MP_Pos *point = textRect.point;
					CGRect rect = CGRectMake(point[0].x, point[0].y, point[2].x - point[0].x, point[2].y - point[0].y);
					[info.mmSearchRects addObject:[NSValue valueWithCGRect:rect]];
				}
			}
		}
		
		if (hres == MP_S_IN_ANNO) 
		{
			info.annoIndex = annoInfo_->annoIndex;
			
			if (textInfoInput != NULL)
			{
				textInfoInput->Destroy();
				textInfoInput = NULL;
			}
			
			CGRect rect = CGRectMake(annoInfo_->annoRect.pos.x, 
									 annoInfo_->annoRect.pos.y, 
									 annoInfo_->annoRect.dim.cx, 
									 annoInfo_->annoRect.dim.cy);
			
			[info.mmSearchRects addObject:[NSValue valueWithCGRect:rect]];
		}
		
		result = YES;
	}
	
	delete dst;
	delete annoInfo_;
	
	return result;
}

- (void) endSearchText
{
	if (textInfoInput != NULL)
	{
		textInfoInput->Destroy();
		textInfoInput = NULL;
	}

	int pageIndex_ = -1;
	handleDocument->SearchText(pageIndex_, 0, 0, NULL);
}

- (void) displaySearchTargetInPageView:(DWScrollView *)pageView withMoveRect:(CGRect)rect withLeft:(BOOL)left
{
	// 1. get zoom scale.
	float zoomScale = pageView.zoomScale;
	
	CGSize screenSize = [self getScreenRect].size;
	
	float backgroundWidth	= screenSize.width;
	float backgroundHeight	= screenSize.height;
	
	float pageOriginX	= pageView.page.m_PageInfoA.m_SrcRect.origin.x;
	float pageOriginY	= pageView.page.m_PageInfoA.m_SrcRect.origin.y;
	float pageWidth		= pageView.page.m_PageInfoA.m_SrcRect.size.width;
	float pageHeight	= pageView.page.m_PageInfoA.m_SrcRect.size.height;
	
	if (pageView.isFacingPage == YES)
	{
		float secondPageWidth = pageView.page.m_PageInfoA.m_SrcRect.size.width;
		
		pageWidth += (secondPageWidth + kFacePageEdgeWidth * 2 +  kFacePageInterval);
	}
	
	float annotWidth	= rect.size.width;
	float annotHeight	= rect.size.height;
	float annotOriginX	= rect.origin.x;
	float annotOriginY	= rect.origin.y;

	// 2. zoom page view 
	CGPoint pageOrigin = pageView.page.frame.origin;
	
	// 3. get offset.
	CGPoint offset = CGPointZero;
	offset.x = annotOriginX * zoomScale + pageOrigin.x - (backgroundWidth  - (annotWidth  * zoomScale)) / 2;
	offset.y = annotOriginY * zoomScale + pageOrigin.y - (backgroundHeight - (annotHeight * zoomScale)) / 2;
	
	float paperRightEdge	= (pageOriginX + pageWidth);
	float annotRightEdge	= (annotOriginX + annotWidth);
	
	float annotMaxOffsetX	= (annotOriginX + annotWidth) * zoomScale + pageOrigin.x - backgroundWidth;
	
	if (offset.x > annotMaxOffsetX &&
		annotRightEdge > paperRightEdge)
	{
		offset.x = annotMaxOffsetX;
	}
	
	float paperButtomEdge	= (pageOriginY + pageHeight);
	float annotButtomEdge	= (annotOriginY + annotHeight);
	
	float annotMaxOffsetY	= (annotOriginY + annotHeight) * zoomScale + pageOrigin.y - backgroundHeight;
	
	if (offset.y > annotMaxOffsetY &&
		annotButtomEdge > paperButtomEdge)
	{
		offset.y = annotMaxOffsetY;
	}
	
	float paperLeftEdge		= pageOriginX;
	float annotLeftEdge		= annotOriginX;
	
	float annotMinOffsetX	= annotOriginX * zoomScale + pageOrigin.x;
	
	if (offset.x < annotMinOffsetX &&
		annotLeftEdge < paperLeftEdge)
	{
		offset.x = annotMinOffsetX;
	}
	
	float paperTopEdge		= pageOriginY;
	float annotTopEdge		= annotOriginY;
	
	float annotMinOffsetY	= annotOriginY * zoomScale + pageOrigin.y;
	
	if (offset.y < annotMinOffsetY &&
		annotTopEdge < paperTopEdge)
	{
		offset.y = annotMinOffsetY;
	}
	
	// right
	float pageRightEdge = pageView.contentSize.width;
	
	float maxOffsetX = pageRightEdge - backgroundWidth;
	
	if (offset.x > maxOffsetX)
	{
		offset.x = maxOffsetX;
	}
	
	// buttom
	float pageButtomEdge = pageView.contentSize.height;
	
	float maxOffsetY = pageButtomEdge - backgroundHeight;
	
	if (offset.y > maxOffsetY)
	{
		offset.y = maxOffsetY;
	}
	
	// left
	float minOffsetX = 0.0;
	
	if (offset.x < minOffsetX)
	{
		offset.x = minOffsetX;
	}
	
	// top
	float minOffsetY = 0.0;
	
	if (offset.y < minOffsetY)
	{
		offset.y = minOffsetY;
	}
	
	// 4. reset page view content offset
	[pageView setContentOffset:offset animated:NO];
}
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
- (BOOL) selectTextInPage:(DWSelectInfo*)info
{
	if (info == nil) return NO;
	
	int pageIndex_ = info.pageIndex;
	int annoIndex_ = info.annoIndex;
	
	MP_Pos start;
	start.x	= info.start.x;
	start.y	= info.start.y;
	
	MP_Pos end;
	end.x	= info.end.x;
	end.y	= info.end.y;
	
	MP_TextInfo* textInfo_ = NULL;
	BOOL result = NO;
	
	BOOL res = handleDocument->SelectText(pageIndex_, annoIndex_, start, end, &textInfo_);
	
	if (res == true) 
	{
		// press in page
		if (annoIndex_ < 0)
		{
			if (textInfo_ != NULL && textInfo_->nRecordCount > 0) {
				[info.mmRects removeAllObjects];
				
				for (int i = 0; i < textInfo_->nRecordCount; i++) {
					MP_TextRect textRect = textInfo_->pTextRects[i];
					MP_Pos *point = textRect.point;
					CGRect rect = CGRectMake(point[0].x, point[0].y, point[1].x - point[0].x, point[2].y - point[0].y);
					[info.mmRects addObject:[NSValue valueWithCGRect:rect]];
				}
				
				int length = textInfo_->nCharLengthWithLF + 1;
				MP_Text* text = new MP_Text[length];
				res = handleDocument->GetText(pageIndex_, annoIndex_, &text, length, textInfo_);
				if (res == true)
				{
					info.text = [NSString stringWithCharacters:(unichar*)text length:length];
				}
				if (text != NULL) 
				{
					delete [] text;
				}
			}
		}
		// press in annotation
		else
		{
			MP_Text* text = NULL;
			int length = 0;
			res = handleDocument->GetText(pageIndex_, annoIndex_, &text, length, textInfo_);
			if (res == true && text != NULL)
			{
				int l = 0;
				while (text[l] != 0) { ++l; }
				length = l;
				
				info.text = [NSString stringWithCharacters:(unichar*)text length:length];
			}
			if (text != NULL) 
			{
				delete [] text;
			}
		}
		
		result = YES;
	}
	
	if (textInfo_ != NULL) 
	{
		textInfo_->Destroy();
	}
	return result;
}
// tongtx 2012.03.23 end
@end
