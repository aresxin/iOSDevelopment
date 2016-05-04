//
//  PageEditManager.m
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//
#import "PageEditManager.h"

#import "PageInfo.h"
#import "DWPageView.h"
#import "DWScrollView.h"
#import "Utility.h"
#import "DWDrawer.h"
#import "XdwLinkManager.h"
#import "DWDocumentEditor.h"
#import "DWAnnotationInfo.h"
#import "AnnotationManager.h"
#import "DWViewerGUIConst.h"
#import "XdwAttributeParser.h"
#include "MXCTextUtl.h"
#define MENU_BAR_HEIGHT_H   44
#define MENU_BAR_HEIGHT_V   32
#define STARCH_ATTRIBUTE	"%ATTR_STARCH"

// yangjx 2012.4.16 start
#include "DWLoginAnnPropertySettingsController.h"
// yangjx 2012.4.16 end

@implementation PageEditManager

@synthesize interfaceOrientation = orientation_;
@synthesize annoRectList = annoRectList_;
@synthesize isZooming;

// 2012.02.01(Ver2.1 New) M.Chikyu
@synthesize pageZoomScale;
// 2012.02.01(Ver2.1 New) M.Chikyu

- (id) initWithDocumentHandle:(DocumentHandle*)handle  
                 withDWDrawer:(DWDrawer*)drawer
{
    if (self = [super init])
	{
		if (handle != nil && drawer != nil)
		{
			documentHandle_	= (XdwDocumentHandle*)handle;
			drawer_			= drawer;
		}
		else
		{
			return nil;
		}

		orientation_	= UIInterfaceOrientationPortrait;

		documentEditor_	= CreateDWDocumentEditor();
		annoRectList_	= [[NSMutableArray alloc] init];
		isZooming		= YES;
	}
    
    return self;
}


#pragma mark -
#pragma mark create new page view.

- (DWEditScrollView *) insertEditPageViewWithPageIndex:(int)index
{
	return [self insertEditPageViewWithPageIndex:index
									minViewScale:1.0];
}


- (DWEditScrollView *) insertEditPageViewWithPageIndex:(int)index
										  minViewScale:(float)minViewScale
{
    // 1. get page view frame.
    CGRect pageViewRect = [self getScreenRectWithToolbar];
	
    // 2. init page vhiew.
	pageView_ = [[DWEditScrollView alloc] initWithFrame:pageViewRect];

	[pageView_ setBackgroundColor:[UIColor grayColor]];

	pageView_.showsHorizontalScrollIndicator	= YES;
	pageView_.showsVerticalScrollIndicator		= YES;
	pageView_.scrollEnabled						= YES;
	pageView_.bounces							= YES;
	pageView_.scrollsToTop						= NO;
	pageView_.directionalLockEnabled			= NO;
    pageView_.index								= index;
    
    // 3. init page.
    [self initPageViewWithPageIndex:(index)
					   minViewScale:minViewScale];

	return pageView_;
}


- (void) initPageViewWithPageIndex:(int)index
					  minViewScale:(float)minViewScale
{
	if (pageView_ != nil)
	{
		// 1. get page fit scale.
		long pageFitCoreScale = [self getPagefitScaleWithIndex:index];

		// 2. get page frame.
		CGRect pageRect = [self getPageRectWithIndex:index 
									   withPageScale:pageFitCoreScale];

		// 3. init page frame.
		DWPageEditView *page = [[DWPageEditView alloc] initWithFrame:pageRect];
		[page setBackgroundColor:[UIColor whiteColor]];

		[self initPage:page
		 withPageIndex:index];

		pageView_.page = page;
		pageView_.contentSize = page.frame.size;

		[pageView_ addSubview:page];
		
		// 4. set link annotation index list.
		[self setAnnotationRectList];
        
		// 5. init page zoom scale.
		// 5.1 min zoom scale.
		float annFitViewScale = (float)[self getAnnfitScaleWithIndex:index] / (float)pageFitCoreScale;

		pageView_.minimumZoomScale = min(annFitViewScale, minViewScale);

		// 5.2 max zoom scale
		float defMaxViewScale = Utility::MAX_SPECIFY_SCALE / (float)pageFitCoreScale;

		pageView_.maximumZoomScale = max(defMaxViewScale, 1.0f);

		// 5.3 page fit scale.
		pageView_.minScale = pageFitCoreScale;

		// 6. set scrollview delegate.
		pageView_.delegate = self;
		
		// 2012.02.01(Ver2.1 New) M.Chikyu
		pageView_.initContentOffset = [self getPageContentOffsetWithIndex:index
															withPageScale:pageFitCoreScale];
		[pageView_ setContentOffset:pageView_.initContentOffset];
		// 2012.02.01(Ver2.1 New) M.Chikyu
	}
}


- (void) initPage:(DWPageEditView*)page
	withPageIndex:(int)index
{
	if (page != nil)
	{
		page.m_PageInfoA = [self getDWPageInfo:index];
		page.m_PageInfoB = [self getDWPageInfo:-1];

		page.backgroundColor = [UIColor whiteColor];

		// Set UIView scalefactor

		// AR19007
		// 2012.02.20 M.Chikyu start.
		/*
		float scaleFactor = Utility::GetScreenScale([self getPagefitScaleWithIndex:index]);
		 */

		CGSize paperSize	= [self getPageViewSize:index 
								   withPageScale:100.0 
									withPageMode:(PageInfo::kPaperMode)];

		CGSize anntSize		= [self getPageViewSize:index 
								   withPageScale:100.0 
									withPageMode:(PageInfo::kFullMode)];

		float ratio = (anntSize.width * anntSize.height) / (paperSize.width * paperSize.height);

		float scaleFactor = Utility::GetScreenScale([self getPagefitScaleWithIndex:index], ratio);

		// 2012.02.20 M.Chikyu end.

		[page setScaleFactor:scaleFactor];
		
		page.drawer = drawer_;
	}
}


- (DWPageInfo) getDWPageInfo:(int)pageIndex
{
	DWPageInfo dwPageInfo;

	if (pageIndex < 0)
	{
		dwPageInfo.m_PageNum = -1;
		return dwPageInfo;
	}
    
	dwPageInfo.m_PageNum = pageIndex;
	
	long pageFitCoreScale = [self getPagefitScaleWithIndex:pageIndex];
	
	dwPageInfo.m_Scale			= pageFitCoreScale;
	dwPageInfo.m_PageFitScale	= pageFitCoreScale;
	dwPageInfo.m_MaxPageScale	= pageFitCoreScale > Utility::MAX_SPECIFY_SCALE ?
									pageFitCoreScale : Utility::MAX_SPECIFY_SCALE;
	
	float originX = 0.0;
    float originY = 0.0;

	float pageWidth  = 0.0;
	float pageHeight = 0.0;
    
	// 1. set m_SrcRectWithAnno value.
    CGSize pageSize = [self getPageViewSize:pageIndex 
                              withPageScale:pageFitCoreScale 
                               withPageMode:(PageInfo::kFullMode)];
	pageWidth  = pageSize.width;
	pageHeight = pageSize.height;

	dwPageInfo.m_SrcRectWithAnno = CGRectMake(originX, 
                                              originY, 
                                              pageWidth,
                                              pageHeight);
    
	// 2. set m_SrcRect value
    PageInfo* pageInfo = documentHandle_->GetPageInfo(pageIndex);

	if (pageInfo != NULL)
	{
		MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);

		originX = fabs(Utility::MMToPixelWithScale(pos.x, pageFitCoreScale));
		originY = fabs(Utility::MMToPixelWithScale(pos.y, pageFitCoreScale));

		delete pageInfo;
	}
    
    pageSize = [self getPageViewSize:pageIndex 
                       withPageScale:pageFitCoreScale 
                        withPageMode:(PageInfo::kPaperMode)];
	
    pageWidth  = pageSize.width;
	pageHeight = pageSize.height;
    
	dwPageInfo.m_DestRect = CGRectZero;
	dwPageInfo.m_SrcRect  = CGRectMake(originX, 
									   originY, 
									   pageWidth, 
									   pageHeight);
	
	return dwPageInfo;
}


- (void) setAnnotationRectList
{
    [annoRectList_ removeAllObjects];
    
    MPCObject *parentObj = [self getMPCObjectWithPageIndex:pageView_.index];
	if (parentObj == nil)
	{
		return;
	}
    
    count = 0;
    
    HRESULT hres = MP_NOERROR;
    hres = documentEditor_->HowManyAnnotations(parentObj, &count);

	if (hres != MP_NOERROR)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		CGRect rect = [self getAnnotationRectWithParentObject:parentObj
												withAnnoIndex:i];
		NSValue* value_ = [NSValue valueWithCGRect:rect];

		[annoRectList_ addObject:value_];
	}
}


- (long) getPagefitScaleWithIndex:(int)index
{
	float scale = 100.0f;
	
	CGSize paperFullSize = [self getPageViewSize:index 
								   withPageScale:100.0f
									withPageMode:(PageInfo::kPaperMode)];
	
	if (paperFullSize.width  != 0 &&
		paperFullSize.height != 0)
	{
		CGRect screen = [self getScreenRect];

		float scaleX = (float)screen.size.width  / paperFullSize.width  * 100.0f;
		float scaleY = (float)screen.size.height / paperFullSize.height * 100.0f;

		scale = scaleX < scaleY ? scaleX : scaleY;
	}
	
	return (long)scale;
}

// 2012.02.01(Ver2.1 New) M.Chikyu
- (long) getAnnfitScaleWithIndex:(int)index
{
	float scale = 100.0f;
	
	CGSize pageFullSize = [self getPageViewSize:index
								  withPageScale:100.0f
								   withPageMode:(PageInfo::kFullMode)];
	
	if (pageFullSize.width  != 0 &&
		pageFullSize.height != 0)
	{
		// AR19016
		// 2012.02.23 M.Chikyu start.
		/*
		 CGRect screen = [self getScreenRect];
		 */
		CGRect screen = [self getScreenRectWithToolbar];
		// 2012.02.23 M.Chikyu end.
		
		float scaleX = (float)screen.size.width  / pageFullSize.width  * 100.0f;
		float scaleY = (float)screen.size.height / pageFullSize.height * 100.0f;
		
		scale = scaleX < scaleY ? scaleX : scaleY;
	}
	
	return (long)scale;
}
// 2012.02.01(Ver2.1 New) M.Chikyu

- (CGRect) getPageRectWithIndex:(int)index
				  withPageScale:(long)scale
{	
    // 1. background size
	/*
	CGSize screenSize = [self getScreenRect].size;
	 */
	CGSize screenSize = [self getScreenRectWithToolbar].size;

	float backgroundWidth  = screenSize.width;
	float backgroundHeight = screenSize.height;
    
    // 2. page size.
	CGSize pageSize = [self getPageViewSize:index 
                              withPageScale:scale 
                               withPageMode:(PageInfo::kFullMode)];

	float pageWidth  = pageSize.width;
	float pageHeight = pageSize.height;
    
    // 3. origin x.
    float originX = 0.0;
	
    if (pageWidth < backgroundWidth)
	{
		originX = (backgroundWidth - pageWidth) / 2;
	}
    
    // 4. origin y.
	float originY = 0.0;

    if (pageHeight < backgroundHeight)
	{
		originY = (backgroundHeight - pageHeight) / 2;
	}
    
	return CGRectMake((int)originX,
					  (int)originY,
					  (int)pageWidth,
					  (int)pageHeight);
}


- (CGSize) getPageViewSize:(int)index 
             withPageScale:(long)scale
              withPageMode:(PageInfo::PAGE_MODE)mode
{
	CGSize pageSize = CGSizeZero;
	PageInfo* pageInfo = documentHandle_->GetNewPageInfo(index);

	if (pageInfo != nil)
	{
		float pageW = Utility::MMToPixelWithScale(pageInfo->GetWidth(mode),  scale);
		float pageH = Utility::MMToPixelWithScale(pageInfo->GetHeight(mode), scale);

		pageSize = CGSizeMake(pageW, pageH);
	}
    
	return pageSize;
}


- (void) zoomOutPageWithPoint:(CGPoint)point
{
    if (pageView_.zoomScale == pageView_.minimumZoomScale)
	{
		return;
	}
    
    float zoomScale = pageView_.zoomScale / 2;

	if (zoomScale < pageView_.minimumZoomScale)
	{
        zoomScale = pageView_.minimumZoomScale;
    }
    
    CGRect zoomRect = CGRectNull;

	zoomRect.size.width  = pageView_.frame.size.width  / zoomScale;
	zoomRect.size.height = pageView_.frame.size.height / zoomScale;
    
    zoomRect.origin.x = point.x - (zoomRect.size.width  / 2.0);
    zoomRect.origin.y = point.y - (zoomRect.size.height / 2.0);
    
    [pageView_ zoomToRect:zoomRect animated:YES];
}


- (UIColor *) transformColorRefToUIColor:(COLORREF)colorRef
{
	return [UIColor colorWithRed:( colorRef & 0xFF)             / 255.0f 
						   green:((colorRef & 0xFF00) >> 8)     / 255.0f 
							blue:((colorRef & 0xFF0000) >> 16)  / 255.0f  
						   alpha:1.0f];
}


- (BOOL) transformUIColorToColorRef:(UIColor *)color withColorRef:(COLORREF *)colorRef
{
	if (color != nil)
	{
		NSString *RGBValue = [NSString stringWithFormat:@"%@",color];
		NSArray  *RGBArr = [RGBValue componentsSeparatedByString:@" "];
        
		if ([RGBArr count] < 4)
		{
			*colorRef = RGB(0, 0, 0);
			return YES;
		}
		
		int colorR = [[RGBArr objectAtIndex:1] floatValue] * 255;
		int colorG = [[RGBArr objectAtIndex:2] floatValue] * 255;
		int colorB = [[RGBArr objectAtIndex:3] floatValue] * 255;
		
		*colorRef = RGB(colorR, colorG, colorB);

		return YES;
	}

	return NO;
}


#pragma mark -
#pragma mark private method.
- (CGRect) getScreenRect
{
	long pageWidth  = 0;
	long pageHeight = 0;
	
	CGRect screenFrame = [[UIScreen mainScreen] bounds];

	// 2012.02.14 M.Chikyu start.
	/*
	pageWidth = screenFrame.size.width;
	pageHeight = screenFrame.size.height;
	 */

	// 2012.02.20 M.Chikyu start.
	/*
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageWidth = screenFrame.size.width;
		pageHeight = screenFrame.size.height - MENU_BAR_HEIGHT_H;
	}
	else
	{
		pageWidth = screenFrame.size.height;
		pageHeight = screenFrame.size.width - MENU_BAR_HEIGHT_V;
	}
	 */

	if ([self UIDeviceIsPortrait] == YES)
	{
		pageWidth	= screenFrame.size.width;
		pageHeight	= screenFrame.size.height;
	}
	else
	{
		pageWidth	= screenFrame.size.height;
		pageHeight	= screenFrame.size.width;
	}
	// 2012.02.20 M.Chikyu end.

	// 2012.02.14 M.Chikyu end.
    
	return CGRectMake(0, 0, pageWidth, pageHeight);
}


- (CGRect) getScreenRectWithToolbar
{
	long pageWidth  = 0;
	long pageHeight = 0;
	
	CGRect screenFrame = [[UIScreen mainScreen] bounds];
	
	if ([self UIDeviceIsPortrait] == YES)
	{
		pageWidth = screenFrame.size.width;
		pageHeight = screenFrame.size.height - MENU_BAR_HEIGHT_H;
	}
	else
	{
		pageWidth = screenFrame.size.height;
		pageHeight = screenFrame.size.width - MENU_BAR_HEIGHT_V;
		
		if (Utility::UIDeviceIsiPad() == YES)
		{
			pageHeight = screenFrame.size.width - MENU_BAR_HEIGHT_H;
		}
	}
    
	return CGRectMake(0, 0, pageWidth, pageHeight);
}


- (CGRect) getPagePaperRect
{
    float originX = pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
    float originY = pageView_.page.m_PageInfoA.m_SrcRect.origin.y;

    float width  = pageView_.page.m_PageInfoA.m_SrcRect.size.width;
    float height = pageView_.page.m_PageInfoA.m_SrcRect.size.height;

	return CGRectMake(originX, originY, width, height);
}


- (BOOL) UIDeviceIsPortrait
{
	if ((orientation_ == UIInterfaceOrientationPortrait) || 
		(orientation_ == UIInterfaceOrientationPortraitUpsideDown))
	{
		return YES;
	}
	else
	{
		return NO;
	}
}



- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
	if (isZooming)
	{
		return pageView_.page;
	}
	else
	{
		return nil;
	}
}

- (void)scrollViewDidZoom:(UIScrollView *)scrollView __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2)
{
    if (pageView_ != nil && pageView_.page != nil)
	{
        DWPageEditView* page = pageView_.page;
        
        // 1. background size
		CGSize screenSize = [self getScreenRectWithToolbar].size;
        
        // 2. get origin.
        float originX = 0.0f;
        if (page.frame.size.width <= screenSize.width)
		{
			originX = (screenSize.width - page.frame.size.width) / 2.0;
		}
        
        float originY = 0.0f;
        if (page.frame.size.height <= screenSize.height)
		{
			originY = (screenSize.height - page.frame.size.height) / 2.0;
		}

        // 3. set page frame and pageview content size.
        page.frame = CGRectMake(originX,
								originY,
								page.frame.size.width,
								page.frame.size.height);

        pageView_.contentSize = page.frame.size;
    }
}

#pragma mark -
#pragma mark edit annotation.
// ----------------------------------------------------
// edit annotation about...

- (BOOL) addAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
    if (dwAnnoInfo == nil)
	{
        return NO;
    }
    
	[drawer_ breakDrawing];
	[drawer_ resetDrawing];
	
    MPCObject *parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex];
    if (parentObj == nil)
	{
        return NO;
    }
    
    HRESULT hres = MP_NOERROR;
    MP_Pos position = MP_NULL_POS;
    MPCObject *annoObj = NULL;
	float scale = 0;
	
    if (dwAnnoInfo.annoType == ANTYPE_FREEHAND)
	{
        annoObj = [self createFreehandAnnotation:dwAnnoInfo
									withPosition:&position];
        if (annoObj == nil)
		{
            return NO;
        }
    }
    
    if (dwAnnoInfo.annoType == ANTYPE_NOTEPAD)
	{
		scale = pageView_.page.m_PageInfoA.m_PageFitScale;
        annoObj = [self createNotepadAnnotation:dwAnnoInfo];

		position.x = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.x, scale);
        position.y = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.y, scale);
        
        MPCObject *textObj = [self createTextAnnotation:dwAnnoInfo];
        
        if (annoObj != NULL && textObj != NULL)
		{
			MP_Pos pos = MP_NULL_POS;

			pos.x = Utility::PixelToMMWithScale_F(10, scale);
			pos.y = Utility::PixelToMMWithScale_F(10, scale);

			hres = documentEditor_->AddAnnotation(annoObj, textObj, pos);

			if (hres != MP_NOERROR)
			{
				return NO;
			}
		}
	}
   
    // yangjx 2012.4.16 start
    if (dwAnnoInfo.annoType == ANTYPE_LOGIN)
    {
		DWLoginAnnotationInfo* info_ = (DWLoginAnnotationInfo*)dwAnnoInfo;
        scale = pageView_.page.m_PageInfoA.m_PageFitScale;
        position.x = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.x, scale);
        position.y = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.y, scale);
        if([DWResistAnnotationManager getResistAnnotationWithIndex:info_.loginAnnIndex 
                                                    withSession:[self getMPCSession]
												withAnnObjectRef:&annoObj] == NO)
		{
			return NO;
		}
	}
    // yangjx 2012.4.16 end

    hres = documentEditor_->AddAnnotation(parentObj, annoObj, position);
	if (hres != MP_NOERROR)
	{
		return NO;
	}
	
    // yangjx 2012.4.16 start
    /*old
    if (dwAnnoInfo.annoType == ANTYPE_NOTEPAD)
     */
    if (dwAnnoInfo.annoType == ANTYPE_NOTEPAD || dwAnnoInfo.annoType == ANTYPE_LOGIN)
    // yangjx 2012.4.16 end    
	{
		int annoCount = 0;

		hres = documentEditor_->HowManyAnnotations(parentObj, &annoCount);

		if (annoCount > 0)
		{
            int annoIndex = annoCount - 1;
            CGRect rect = [self getAnnotationRectWithParentObject:parentObj
                                                    withAnnoIndex:annoIndex];
            
            // x.
			float originX = dwAnnoInfo.annoRect.origin.x
							- rect.size.width / 2
							- pageView_.page.m_PageInfoA.m_SrcRect.origin.x;

			float minOriginX = -rect.size.width;
			
            if (originX < minOriginX)
			{
                originX = minOriginX;
            }
			
            float maxOriginX = pageView_.page.m_PageInfoA.m_SrcRect.size.width;
			
            if (originX > maxOriginX)
			{
                originX = maxOriginX;
            }
			
            position.x = Utility::PixelToMMWithScale_F(originX, scale);
            
            // y.
			float originY = dwAnnoInfo.annoRect.origin.y
							- rect.size.height / 2
							- pageView_.page.m_PageInfoA.m_SrcRect.origin.y;

			float minOriginY = -rect.size.height;

			if (originY < minOriginY)
			{
                originY = minOriginY;
            }
			
            float maxOriginY = pageView_.page.m_PageInfoA.m_SrcRect.size.height;

            if (originY > maxOriginY)
			{
                originY = maxOriginY;
            }

            position.y = Utility::PixelToMMWithScale_F(originY, scale);
            
            parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex];
 
			documentEditor_->SetAnnotationPosition(parentObj,
												   annoObj,
												   position);
        }
	}
    
	[self saveDocumentUpdate];
    
    // yangjx 2012.4.16 start
    if (annoObj != NULL) 
    {
        annoObj->Destroy();

    }
    // yangjx 2012.4.16 end
    
    return YES;
}


- (BOOL) updateAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
	if (dwAnnoInfo == nil)
	{
		return NO;
	}


	[drawer_ breakDrawing];
	[drawer_ resetDrawing];
	
    
	MPCObject* parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex]; 
	if (parentObj == NULL)
	{
		return NO;
	}

	MPCObject* annObject = [self getAnnotationObjectWithParentObject:parentObj 
													 annotationIndex:dwAnnoInfo.annoIndex];
	
	if (annObject == NULL)
	{
		return NO;
	}

	HRESULT hres = MP_NOERROR;

	if (dwAnnoInfo.annoType == ANTYPE_FREEHAND)
	{
        FreehandAnnotationParameter para;
		para.tag = AnnotationParameter::TAG_FREEHAND;

		hres = documentEditor_->GetAnnotationParameter(annObject, &para);
        if (hres != MP_NOERROR)
		{
			return NO;
		}
        
        DWFreehandAnnotationInfo* dwInfo = (DWFreehandAnnotationInfo*)dwAnnoInfo;
        para.tag = AnnotationParameter::TAG_FREEHAND;
        para.border.width = dwInfo.lineWidth;
        para.border.color = dwInfo.lineColor;
        
		// wangpp 2012.3.5 start
		// freehand transparent
		
		/*
		 if (para.border.transparent == true)
		 {
		    const long whiteColorRef = 16777215;
		 
		    if (para.border.color == whiteColorRef)
		    {
		        para.border.transparent = false;
			}
		    else
		    {
		         para.border.transparent = true;
			}
		 }
		 */
		
		if (dwInfo.transparent == YES) 
		{
			para.border.transparent = true;
		}
		else
		{
			para.border.transparent = false;
		}
		
		// wangpp 2012.3.5  end
        
        hres = documentEditor_->SetAnnotationParameter(annObject, &para);
        if (hres != MP_NOERROR)
		{
			return NO;
		}
	}
	else if (dwAnnoInfo.annoType == ANTYPE_NOTEPAD)
	{
        CGRect oldRect = [self getAnnotationRectWithParentObject:parentObj
                                                   withAnnoIndex:dwAnnoInfo.annoIndex];
        
        NotepadAnnotationParameter para;
        para.tag = AnnotationParameter::TAG_NOTEPAD;

		hres = documentEditor_->GetAnnotationParameter(annObject, &para);
		if (hres != MP_NOERROR)
		{
            return NO;
        }
        
        DWTextNotepadAnnotationInfo* dwInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo;
        
        // get text object.
        MPCObject* textObj = [self getAnnotationObjectWithParentObject:annObject 
                                                       annotationIndex:0];
        if (textObj == NULL && [dwInfo.textContent length] != 0)
		{
			MP_Pos position = MP_NULL_POS;
			float scale = pageView_.page.m_PageInfoA.m_PageFitScale;

			position.x = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.x, scale);
			position.y = Utility::PixelToMMWithScale_F(dwAnnoInfo.annoRect.origin.y, scale);
            
            MPCObject *textObj = [self createTextAnnotation:dwInfo];
          
            if (annObject != NULL && textObj != NULL)
			{
                MP_Pos pos = MP_NULL_POS;

                pos.x = Utility::PixelToMMWithScale_F(10, scale);
                pos.y = Utility::PixelToMMWithScale_F(10, scale);

				hres = documentEditor_->AddAnnotation(annObject, textObj, pos);
				if (hres != MP_NOERROR)
				{
					return NO;
				}
			}
		}

		if (textObj != NULL)
		{
			TextAnnotationParameter parameter;
			parameter.tag = AnnotationParameter::TAG_TEXT;

			hres = documentEditor_->GetAnnotationParameter(textObj, &parameter);
			if (hres != MP_NOERROR)
			{
                return NO;
            }

			if (dwInfo.isUpdateText == NO)
			{
				parameter.font.size = dwInfo.textFontsize;
				parameter.font.color = dwInfo.textFontColor;
            }
			else
			{
                int count_ = [dwInfo.textContent length];
                unsigned short *src = (unsigned short*)[dwInfo.textContent cStringUsingEncoding:NSUTF16StringEncoding];
                unsigned short *dst = new unsigned short[count_ + 1];

                for (int i = 0; i < count_; i++)
				{
					dst[i] = src[i];
				}
                
				dst[count_] = 0;
				parameter.text = UTF16Text(dst);
				delete dst;
            }
            
            hres = documentEditor_->SetAnnotationParameter(textObj, &parameter);
            if (hres != MP_NOERROR)
			{
				return NO;
			}
		}
		
		para.tag = AnnotationParameter::TAG_NOTEPAD;
		para.autoResize = dwInfo.isAutoResize;
        para.color = dwInfo.notepadColor;
        
        hres = documentEditor_->SetAnnotationParameter(annObject, &para);
        if (hres != MP_NOERROR)
		{
            return NO;
        }
        
        
        MP_Pos position = MP_NULL_POS;
        float scale = pageView_.page.m_PageInfoA.m_PageFitScale;

		CGRect newRect = [self getAnnotationRectWithParentObject:parentObj
												   withAnnoIndex:dwAnnoInfo.annoIndex];
        
        // x.
        float originX = newRect.origin.x - pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
        float minOriginX = -newRect.size.width;

		if (originX < minOriginX)
		{

			originX = oldRect.origin.x
					+ oldRect.size.width
					- newRect.size.width
					- pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
		}

        float maxOriginX = pageView_.page.m_PageInfoA.m_SrcRect.size.width;

		if (originX > maxOriginX)
		{
            originX = maxOriginX;
        }
		
        position.x = Utility::PixelToMMWithScale_F(originX, scale);
        
        // y.
        float originY = newRect.origin.y - pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
        float minOriginY = -newRect.size.height;

		if (originY < minOriginY)
		{
			originY = minOriginY;

			originY = oldRect.origin.y
					+ oldRect.size.height
					- newRect.size.height
					- pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
        }
		
        float maxOriginY = pageView_.page.m_PageInfoA.m_SrcRect.size.height;

		if (originY > maxOriginY)
		{
            originY = maxOriginY;
        }
		
        position.y = Utility::PixelToMMWithScale_F(originY, scale);
        
        parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex];

        documentEditor_->SetAnnotationPosition(parentObj,
											   annObject,
											   position);
    }

    [self saveDocumentUpdate];
    
    return YES;
}


- (BOOL) updateAnnotationPositionWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
	if (dwAnnoInfo == nil)
	{
        return NO;
	}
    
	[drawer_ breakDrawing];
	[drawer_ resetDrawing];

    
    MPCObject* parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex]; 
	if (parentObj == NULL)
	{
		return NO;
	}

	MPCObject* annObject = [self getAnnotationObjectWithParentObject:parentObj
													 annotationIndex:dwAnnoInfo.annoIndex];

	MP_Pos position = MP_NULL_POS;
	float scale = pageView_.page.m_PageInfoA.m_PageFitScale;

	float originX = dwAnnoInfo.annoRect.origin.x - pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
	position.x = Utility::PixelToMMWithScale_F(originX, scale);

	float originY = dwAnnoInfo.annoRect.origin.y - pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
	position.y = Utility::PixelToMMWithScale_F(originY, scale);
    
	HRESULT hres = MP_NOERROR;

	hres = documentEditor_->SetAnnotationPosition(parentObj,
												  annObject,
												  position);
	if (hres != MP_NOERROR)
	{
		return NO;
	}

	// zhaijie 2012.03.30 start
	int nth = parentObj->GetChildPosition(annObject);
	hres = parentObj->ChangeChildOrder(nth);
	if (hres != MP_NOERROR)
	{
		return NO;
	}
	
	nth = parentObj->GetChildPosition(annObject);
	dwAnnoInfo.annoIndex = nth;
	
	int count_ = 0;
	hres = documentEditor_->HowManyAnnotations(parentObj, &count_);
	if (hres == MP_NOERROR && nth > count_ - 1)
	{
		dwAnnoInfo.annoIndex = count_ - 1;
	}
	
	// zhaijie 2012.03.30 end

	[self saveDocumentUpdate];
    
	return YES;
}


- (BOOL) deleteAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
    if (dwAnnoInfo == nil)
	{
        return NO;
    }
    
	[drawer_ breakDrawing];
	[drawer_ resetDrawing];
    
	MPCObject* parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex]; 
	if (parentObj == NULL)
	{
		return NO;
	}
	
	MPCObject* annObject = [self getAnnotationObjectWithParentObject:parentObj 
													 annotationIndex:dwAnnoInfo.annoIndex];
	
	if (annObject == NULL)
	{
		return NO;
	}
	
	// remove annotation from parent
    HRESULT hres = MP_NOERROR;
	hres = documentEditor_->RemoveAnnotation(parentObj, annObject);
	
	// destroy annotation object
	if (hres == MP_NOERROR)
	{
		hres = documentEditor_->DestroyAnnotation(annObject);
	}
	
	if ( hres != MP_NOERROR )
	{
		return NO;
	}
	
	[self saveDocumentUpdate];
    
	return YES;
}


- (BOOL) getAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo
{
    if (dwAnnoInfo == nil)
	{
		return NO;
	}
    
	MPCObject* parentObj = [self getMPCObjectWithPageIndex:dwAnnoInfo.pageIndex]; 
	if (parentObj == NULL)
	{
		return NO;
	}
	
	MPCObject* annObject = [self getAnnotationObjectWithParentObject:parentObj 
													 annotationIndex:dwAnnoInfo.annoIndex];
	
	if (annObject == NULL)
	{
		return NO;
	}

	HRESULT hres = MP_NOERROR;

	bool isFixed = false;
    MP_AValue avalue = { sizeof(int), MP_A_INT, (void*)&isFixed };

	hres = annObject->GetAttribute(STARCH_ATTRIBUTE, &avalue);
	if (hres == MP_E_INVALIDARG)
	{
		dwAnnoInfo.isFixed = NO;
	}
	else if (isFixed == true)
	{
		dwAnnoInfo.isFixed = YES;
	}
	else
	{
		dwAnnoInfo.isFixed = NO;
	}

	if (dwAnnoInfo.annoType == ANTYPE_FREEHAND)
	{
		FreehandAnnotationParameter para;
		para.tag = AnnotationParameter::TAG_FREEHAND;

		hres = documentEditor_->GetAnnotationParameter(annObject, &para);
		if (hres != MP_NOERROR)
		{
			return NO;
		}

		DWFreehandAnnotationInfo* dwInfo = (DWFreehandAnnotationInfo*)dwAnnoInfo;
 
		// 1. set rect value.
		long scale = pageView_.page.m_PageInfoA.m_PageFitScale;
		float originX = Utility::MMToPixelWithScale(para.position.x, scale);
		originX = originX + pageView_.page.m_PageInfoA.m_SrcRect.origin.x; 
		float originY = Utility::MMToPixelWithScale(para.position.y, scale);
		originY = originY + pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
		float width = Utility::MMToPixelWithScale(para.width, scale);
		float height = Utility::MMToPixelWithScale(para.height, scale);
		dwInfo.annoRect = CGRectMake(originX, originY, width, height);

		// 2. set line value.
		dwInfo.lineWidth = para.border.width;
		dwInfo.lineColor = para.border.color;
		
		// wangpp 2012.3.5  start
		// freehand transparent
		dwInfo.transparent = para.border.transparent;
		// wangpp 2012.3.5 end
		
		// 3. dwInfo points
		int pointCount = (para.points).size();

		for (int j = 0; j < pointCount; j++)
		{
            CGPoint point;
            float originX = Utility::MMToPixelWithScale(para.points[j].x, scale);
			point.x = originX + pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
            float originY = Utility::MMToPixelWithScale(para.points[j].y, scale);
			point.y = originY + pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
			[dwInfo.linePoints addObject:[NSValue valueWithCGPoint:point]];
		}
	}
	else if (dwAnnoInfo.annoType == ANTYPE_NOTEPAD)
	{

        NotepadAnnotationParameter para;
        para.tag = AnnotationParameter::TAG_NOTEPAD;

        hres = documentEditor_->GetAnnotationParameter(annObject, &para);
		if (hres != MP_NOERROR)
		{
			return NO;
		}

        DWTextNotepadAnnotationInfo* dwInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo;
        dwInfo.isUpdateText = NO;
        
		// 1. set nodepad value.
		long scale = pageView_.page.m_PageInfoA.m_PageFitScale;
		float originX = Utility::MMToPixelWithScale(para.position.x, scale);
		originX = originX + pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
		float originY = Utility::MMToPixelWithScale(para.position.y, scale);
		originY = originY + pageView_.page.m_PageInfoA.m_SrcRect.origin.y;
		float width = Utility::MMToPixelWithScale(para.width, scale);
		float height = Utility::MMToPixelWithScale(para.height, scale);
		dwInfo.annoRect = CGRectMake(originX, originY, width, height);
		dwInfo.notepadColor = para.color;
		dwInfo.isAutoResize = para.autoResize;

		int annotationCount = 0;

		hres = documentEditor_->HowManyAnnotations(annObject, &annotationCount);
		if (hres != MP_NOERROR || annotationCount != 1)
		{
			dwInfo.hasTextAnnotation = NO;
		}
        
        // get text object.
		MPCObject* textObj = [self getAnnotationObjectWithParentObject:annObject
													   annotationIndex:0];
		if (textObj != NULL)
		{
            dwInfo.hasTextAnnotation = YES;
			
			TextAnnotationParameter textPara;
            textPara.tag = AnnotationParameter::TAG_TEXT;
            
            hres = documentEditor_->GetAnnotationParameter(textObj, &textPara);
            if (hres != MP_NOERROR)
			{
				dwInfo.hasTextAnnotation = NO;
				dwInfo.textAnnotCount = -1;

				return NO;
			}

			dwInfo.textFontsize  = textPara.font.size;
			dwInfo.textFontColor = textPara.font.color;
           
			if (textPara.text != NULL)
			{
				dwInfo.textContent = [NSString stringWithCharacters:(unichar*)(textPara.text.data())
															 length:(textPara.text.GetLength())];
			}
			else
			{
				dwInfo.hasTextAnnotation = NO;
			}
			
			if (annotationCount > 1)
			{
				dwInfo.hasTextAnnotation = NO;
			}
		}
		else
		{
			dwInfo.hasTextAnnotation = NO;
            COLORREF color_;
            [self transformUIColorToColorRef:(Utility::DEFAULT_FONTCOLOR_NOTEPAD)
                                withColorRef:&color_];
            dwInfo.textFontColor = color_;
            dwInfo.textFontsize = Utility::DEFAULT_FONTSIZE_NOTEPAD;
		}
        
        if (annotationCount == 0)
        {
        	dwInfo.textAnnotCount = 0;
        } 
        else if (annotationCount == 1)
        {
        	if (dwInfo.hasTextAnnotation == YES) 
        	{
        		dwInfo.textAnnotCount = 1;
        	}
        	else
        	{
        		dwInfo.textAnnotCount = -1;
        	}
        }
        else 
        {
        	dwInfo.textAnnotCount = annotationCount;
        }
    }
	else
	{
        
        CGRect rect = [self getAnnotationRectWithParentObject:parentObj 
                                                withAnnoIndex:dwAnnoInfo.annoIndex];
        dwAnnoInfo.annoRect = rect;
    }
	
	return YES;
}


#pragma mark -
#pragma mark create annotation.
- (MPCObject *) createFreehandAnnotation:(DWAnnotationInfo*)dwAnnoInfo 
                            withPosition:(MP_Pos*)pos
{
    if (dwAnnoInfo == nil)
	{
		return NULL;
	}
  
    MPCObject *annoObj = NULL;
    
    DWFreehandAnnotationInfo* dwInfo = (DWFreehandAnnotationInfo*)dwAnnoInfo;
    
    FreehandAnnotationParameter para;
    para.tag = AnnotationParameter::TAG_FREEHAND;
    
	para.width  = 0;
	para.height = 0;
	
	para.border.color = dwInfo.lineColor;
	para.border.width = dwInfo.lineWidth;
	
	
	// wangpp 2012.2.29 start 
	// freehand transparent
	/*
    const long whiteColorRef = 16777215;

	if (para.border.color == whiteColorRef)
	{
		para.border.transparent = false;
	}
	else
	{
		para.border.transparent = true;
	}
	 */
	
	if (dwInfo.transparent == YES) 
	{
		para.border.transparent = true;
	} 
	else
	{
		para.border.transparent = false;
	}
	
	// wangpp 2012.2.29 end
	
	float scale = pageView_.page.m_PageInfoA.m_PageFitScale;
    
    int pointCount  = [dwInfo.linePoints count];
    POINT *pt = new POINT[pointCount];
    
	for (int i = 0; i < pointCount; i++)
	{
		CGPoint point = [[dwInfo.linePoints objectAtIndex:i] CGPointValue];

		pt[i].x = Utility::PixelToMMWithScale_F(point.x, scale);
		pt[i].y = Utility::PixelToMMWithScale_F(point.y, scale);
	}
    
    para.points.set(pt, pointCount);
    
	delete[] pt;
	
    HRESULT hres = MP_NOERROR;
    MPCSession* session_ = [self getMPCSession];

	hres = documentEditor_->CreateAnnotation(session_, &para, &annoObj);
	if (hres != MP_NOERROR)
	{
		return NULL;
	}
    
    pos->x = para.position.x;
    pos->y = para.position.y;
    
    return annoObj;
}


- (MPCObject *) createNotepadAnnotation:(DWAnnotationInfo*)dwAnnoInfo
{
	if (dwAnnoInfo == nil)
	{
		return NULL;
	}

	MPCObject *annoObj = NULL;

	DWTextNotepadAnnotationInfo* dwInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo;
	NotepadAnnotationParameter para;
	para.tag = AnnotationParameter::TAG_NOTEPAD;

	float scale = pageView_.page.m_PageInfoA.m_PageFitScale;

    para.position.x = Utility::PixelToMMWithScale_F(dwInfo.annoRect.origin.x, scale);
    para.position.y = Utility::PixelToMMWithScale_F(dwInfo.annoRect.origin.y, scale);
    
	para.width  = TEXTNOTEPAD_ANNOT_WIDTH  * 100;
    para.height = TEXTNOTEPAD_ANNOT_HEIGHT * 100;

    para.rect.left = Utility::PixelToMMWithScale_F(dwInfo.annoRect.origin.x, scale);
    para.rect.top  = Utility::PixelToMMWithScale_F(dwInfo.annoRect.origin.y, scale);
	
	para.rect.right  = para.rect.left + TEXTNOTEPAD_ANNOT_WIDTH  * 100;
	para.rect.bottom = para.rect.top  + TEXTNOTEPAD_ANNOT_HEIGHT * 100;
	
    para.color		= dwInfo.notepadColor;
    para.autoResize	= dwInfo.isAutoResize;

	HRESULT hres = MP_NOERROR;

    MPCSession* session_ = [self getMPCSession];

	hres = documentEditor_->CreateAnnotation(session_, &para, &annoObj);
    if (hres != MP_NOERROR)
	{
        return NULL;
    }
	
	return annoObj;
}


- (MPCObject *) createTextAnnotation:(DWAnnotationInfo*)dwAnnoInfo
{
    if (dwAnnoInfo == nil)
	{
		return NULL;
	}

	MPCObject *annoObj = NULL;

	DWTextNotepadAnnotationInfo* dwInfo = (DWTextNotepadAnnotationInfo*)dwAnnoInfo;
	
	NSCharacterSet *whitespace = [NSCharacterSet whitespaceAndNewlineCharacterSet];
	NSString *leftString = [dwInfo.textContent stringByTrimmingCharactersInSet:whitespace];

	int strLength = [leftString length];
	if (strLength == 0)
	{
		return NULL;
	}
	
    TextAnnotationParameter *para = new TextAnnotationParameter();

    para->tag = AnnotationParameter::TAG_TEXT;
    
    para->textbox.left = 1000;
    para->textbox.top = 1000;
    
    float scale = 100;
    long textRight =  Utility::PixelToMMWithScale(dwInfo.textAnnSize.width, scale) * 2.5;

	para->textbox.right = textRight + para->textbox.left;
    
    long textBottom  = Utility::PixelToMM(dwInfo.textAnnSize.height) * 100 + 1000;

	if ((textBottom + para->textbox.top) < TEXTNOTEPAD_ANNOT_HEIGHT * 100)
	{
		para->textbox.bottom = TEXTNOTEPAD_ANNOT_HEIGHT * 100;
	}
	else
	{
		para->textbox.bottom = textBottom;
	}
    
    UTF16Text fontName = (unsigned short *)[dwInfo.textFontName cStringUsingEncoding:NSUTF16StringEncoding];

	para->font.name				= fontName;
	para->font.color			= dwInfo.textFontColor;
	para->font.size				= dwInfo.textFontsize;
	para->font.angle			= 0.0f;
	para->font.vertical			= false;
	para->font.style			= 0; 
	para->font.pitchAndFamily	= dwInfo.pitchAndFamily;
	para->font.charSet			= dwInfo.charSet;
    
    para->fill.has		= false;
    para->fill.color	= 0;
    
    para->margin.left   = 1.70f;
    para->margin.top    = 1.70f;
    para->margin.right  = 1.70f;
    para->margin.bottom = 1.70f;
    
    para->spacing.line		= 1.0f;
    para->spacing.character	= 0.0f;

	para->wrapStyle = AnnotationParameter::TEXT_WRAP_STYLE_NOWRAP;
    

    int count_ = [dwInfo.textContent length];
    unsigned short *src = (unsigned short*)[dwInfo.textContent cStringUsingEncoding:NSUTF16StringEncoding];
    unsigned short *dst = new unsigned short[count_ + 1];

    for (int i = 0; i < count_; i++)
	{
		dst[i] = src[i];
	}
	
    dst[count_] = 0;
    para->text = UTF16Text(dst);
    delete dst;
    
    HRESULT hres = MP_NOERROR;
    MPCSession* session_ = [self getMPCSession];
	hres = documentEditor_->CreateAnnotation(session_, para, &annoObj);
    delete para;

	if (hres != MP_NOERROR)
	{
		return NULL;
	}
    
    return annoObj;
}


#pragma mark -
#pragma mark get MPCObject.
- (MPCSession *) getMPCSession
{
    MPCSession* object = NULL;
    
    AttributeParser* parser_ = documentHandle_->GetAttributePaser();
    if (parser_ != NULL)
	{
		object = (MPCSession*)parser_->GetDocSession();
	}
    
    return object;
}


- (MPCObject *) getMPCObjectWithPageIndex:(int)index
{
    MPCObject* object = NULL;
    
    AttributeParser* parser_ = documentHandle_->GetAttributePaser();
	if (parser_ != NULL)
	{
		XdwPageInfo* pageInfo = (XdwPageInfo*)parser_->GetPageInfo(index);
		object = (MPCObject*)pageInfo->GetPageObject();
	}
    
    return object;
}


- (MPCObject *) getAnnotationObjectWithParentObject:(MPCObject *)parentObject 
									annotationIndex:(NSUInteger)index
{
    MPCObject *annotObject = NULL;
    
	HRESULT hres = MP_NOERROR;
	hres = documentEditor_->GetAnnotation(parentObject, index, &annotObject);

	if (hres == MP_NOERROR)
	{
		return annotObject;
	}
    
    return NULL;
}


- (MP_ObjectType) getAnnotationTypeWithAnnotationIndex:(int)index
{
    MP_ObjectType type = 0;
    MPCObject *parentObj = [self getMPCObjectWithPageIndex:pageView_.index];

	if (parentObj == nil)
	{
		return type;
	}
    
    MP_Rect mpRect = MP_NULL_RECT;
    HRESULT hres = MP_NOERROR;
    hres = documentEditor_->GetAnnotationInformation(parentObj, index, &type, &mpRect);
    
    return type;
}


- (CGRect) getAnnotationRectWithParentObject:(MPCObject*)object 
                               withAnnoIndex:(int)index
{
    CGRect rect = CGRectZero;
    
    HRESULT hres = MP_NOERROR;
    MP_ObjectType type = 0;
    MP_Rect mpRect = MP_NULL_RECT;

	hres = documentEditor_->GetAnnotationInformation(object,
													 index,
													 &type,
													 &mpRect);
	
	MPCObject *antobj = NULL;
	hres = documentEditor_->GetAnnotation(object,
										  0,
										  &antobj);

	if (hres == MP_NOERROR)
	{
		float scale = pageView_.page.m_PageInfoA.m_PageFitScale;

		float originX = Utility::MMToPixelWithScale_F(mpRect.pos.x, scale);
		float originY = Utility::MMToPixelWithScale_F(mpRect.pos.y, scale);

		originX = originX + pageView_.page.m_PageInfoA.m_SrcRect.origin.x;
		originY = originY + pageView_.page.m_PageInfoA.m_SrcRect.origin.y;

		float width  = Utility::MMToPixelWithScale_F(mpRect.dim.cx, scale);
		float height = Utility::MMToPixelWithScale_F(mpRect.dim.cy, scale);
        
		rect = CGRectMake(originX,
						  originY,
						  width,
						  height);
	}
	
    return rect;
}


//
// 2012.02.01(Ver2.1 New) M.Chikyu
//

// ページフィットに必要な関数を定義


- (CGPoint) getPageContentOffsetWithIndex:(int)index 
							withPageScale:(long)scale
{
	float contentOffsetX = 0.0;
	float contentOffsetY = 0.0;
	
	CGSize screenSize = [self getScreenRect].size;
	
	// get paper page size.
	CGSize paperSize = [self getPageViewSize:index
							   withPageScale:scale
								withPageMode:(PageInfo::kPaperMode)];
	
	// get offset between full page and paper page.
	float paperOffsetX = 0.0;
	float paperOffsetY = 0.0;
	
	PageInfo* pageInfo = documentHandle_->GetPageInfo(index);
	
	if (pageInfo != nil)
	{
		MP_Pos pos = pageInfo->GetPagePos(PageInfo::kFullMode);

		paperOffsetX = fabs(Utility::MMToPixelWithScale_F(pos.x, scale));
		paperOffsetY = fabs(Utility::MMToPixelWithScale_F(pos.y, scale));
	}

	contentOffsetX = paperOffsetX - (screenSize.width  - paperSize.width)  / 2;
	contentOffsetY = paperOffsetY - (screenSize.height - paperSize.height) / 2;
	
	return CGPointMake((int)contentOffsetX,
					   (int)contentOffsetY);
}

//
// 2012.02.01(Ver2.1 New) M.Chikyu
//


#pragma mark -
#pragma mark save update.
- (void) saveDocumentUpdate
{
	//documentHandle_->SaveDocumentModified();
	bool saveStatus = documentHandle_->SaveDocumentModified();
	
	if (saveStatus == false)
	{
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
														   message:NSLocalizedString(@"MSG_ANNOTATIONEDIT_ADD_FAILE", nil)
														  delegate:self
												 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
												 otherButtonTitles:nil];
		[alertView show];
		[alertView release];
	}
}


- (void) dealloc
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	if (nil != bgColor)
	{
		[bgColor release];
		bgColor = nil;
	}
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu

	if (documentEditor_ != NULL)
	{
		DestroyDWDocumentEditor(documentEditor_);
		documentEditor_ = NULL;
	}
	
	// liuqw 2012.04.20 start
	// memory leak 
	
	[annoRectList_ release];
	
	// liuqw 2012.04.20 end

	[super dealloc];
}
@end