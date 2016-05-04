//
//  PageEditManager.h
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XdwDocumentHandle.h"

typedef unsigned long	COLORREF;
@class DWDrawer;
struct DWPageInfo;
@class DWPageEditView;
@class DWEditScrollView;
class DWDocumentEditor;
@class DWAnnotationInfo;

@interface PageEditManager : NSObject<UIScrollViewDelegate>
{
    XdwDocumentHandle*      documentHandle_;
    UIInterfaceOrientation	orientation_;
    DWEditScrollView*       pageView_;
    DWDrawer*               drawer_;
	
    DWDocumentEditor*       documentEditor_;

    NSMutableArray*         annoRectList_;
	
	BOOL                    isZooming;
	int                     count;

	// 2012.02.01(Ver2.1 New) M.Chikyu
	float					pageZoomScale;
	// 2012.02.01(Ver2.1 New) M.Chikyu
}

@property UIInterfaceOrientation interfaceOrientation;
@property (nonatomic, readonly) NSMutableArray* annoRectList;
@property BOOL isZooming;

// 2012.02.01(Ver2.1 New) M.Chikyu
@property float	pageZoomScale;
// 2012.02.01(Ver2.1 New) M.Chikyu

// init
- (id) initWithDocumentHandle:(DocumentHandle*)handle  
                 withDWDrawer:(DWDrawer*)drawer;

// ----------------------------------------------------
// page view about...

// insert new page.
- (DWEditScrollView*) insertEditPageViewWithPageIndex:(int)index;

- (DWEditScrollView*) insertEditPageViewWithPageIndex:(int)index
										 minViewScale:(float)minViewScale;

- (void) initPageViewWithPageIndex:(int)index
					  minViewScale:(float)minViewScale;

- (void) initPage:(DWPageEditView*)page
	withPageIndex:(int)index;

- (DWPageInfo) getDWPageInfo:(int)pageIndex;

// set page property value.
- (void) setAnnotationRectList;


// get page frame and size info.
- (long) getPagefitScaleWithIndex:(int)index;

// 2012.02.01(Ver2.1 New) M.Chikyu
- (long) getAnnfitScaleWithIndex:(int)index;
// 2012.02.01(Ver2.1 New) M.Chikyu

- (CGRect) getPageRectWithIndex:(int)index 
                  withPageScale:(long)scale;

- (CGSize) getPageViewSize:(int)index 
             withPageScale:(long)scale
              withPageMode:(PageInfo::PAGE_MODE)mode;

// zoom page view.
- (void) zoomOutPageWithPoint:(CGPoint)point;

// color transform.
- (UIColor *) transformColorRefToUIColor:(COLORREF)longColor;

- (BOOL) transformUIColorToColorRef:(UIColor *)color 
                       withColorRef:(COLORREF *)colorRef;


// 2012.02.01(Ver2.1 New) M.Chikyu

- (CGPoint) getPageContentOffsetWithIndex:(int)index 
							withPageScale:(long)scale;

// 2012.02.01(Ver2.1 New) M.Chikyu



// private common mehtod.
- (CGRect) getPagePaperRect;
- (CGRect) getScreenRect;
- (CGRect) getScreenRectWithToolbar;
- (BOOL) UIDeviceIsPortrait;


// ----------------------------------------------------
// edit annotation about...
- (BOOL) addAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;

- (BOOL) updateAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;

- (BOOL) updateAnnotationPositionWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;

- (BOOL) deleteAnnotationWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;

- (BOOL) getAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;

// create freehand annotation
- (MPCObject *) createFreehandAnnotation:(DWAnnotationInfo*)dwAnnoInfo 
                            withPosition:(MP_Pos*)pos;

// create text notepad annotation.
- (MPCObject *) createNotepadAnnotation:(DWAnnotationInfo*)dwAnnoInfo;

- (MPCObject *) createTextAnnotation:(DWAnnotationInfo*)dwAnnoInfo;

// common method.
- (MPCSession*) getMPCSession;

- (MPCObject *) getMPCObjectWithPageIndex:(int)index;

- (MPCObject *) getAnnotationObjectWithParentObject:(MPCObject *)parentObject 
									annotationIndex:(NSUInteger)index;

- (MP_ObjectType) getAnnotationTypeWithAnnotationIndex:(int)index;

- (CGRect) getAnnotationRectWithParentObject:(MPCObject*)object 
                               withAnnoIndex:(int)index;

- (void) saveDocumentUpdate;
@end
