//
//  DWPageView.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-19.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef _DWPAGE_VIEW_H_
#define _DWPAGE_VIEW_H_

#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/QuartzCore.h>
#import <vector>

struct DWPageInfo
{
	int    m_PageNum;
	long   m_Scale;
	long   m_PageFitScale;
	long   m_MaxPageScale;
	CGRect m_SrcRect;
	CGRect m_SrcRectWithAnno;
	CGRect m_DestRect;
};


@class PageViewManager;
@class DWLayer;

@interface DWPageView : UIView
{
	BOOL isFacingMode;
	DWPageInfo m_PageInfoA;
	DWPageInfo m_PageInfoB;
	
	std::vector<int> linkAnnotationIndex1;
	std::vector<int> linkAnnotationIndex2;
}
@property BOOL isFacingMode;
@property DWPageInfo m_PageInfoA;
@property DWPageInfo m_PageInfoB;

- (void) addLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage;
- (int)  getLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage;
- (int)  getLinkAnnotationCountWithIsLeftPage:(BOOL)isLeftPage;

- (void)clearLayerContent;
@end



// 2012.02.01(Ver2.1 New) M.Chikyu
@class DWDrawer;

@interface DWPageEditView : UIView
{
	BOOL isFacingMode;
	DWPageInfo m_PageInfoA;
	DWPageInfo m_PageInfoB;
	
	std::vector<int> linkAnnotationIndex1;
	std::vector<int> linkAnnotationIndex2;
	
	float m_bmpScale;
	
	// 2012.02.13 M.Chikyu start.
	NSTimeInterval m_drawTime;
	// 2012.02.13 M.Chikyu end.
}
@property BOOL isFacingMode;
@property DWPageInfo m_PageInfoA;
@property DWPageInfo m_PageInfoB;
@property (nonatomic, retain)DWDrawer* drawer;

//@property float m_bmpScale;

// 2012.02.13 M.Chikyu start.
@property NSTimeInterval m_drawTime;
// 2012.02.13 M.Chikyu end.

- (void) addLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage;
- (int)  getLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage;
- (int)  getLinkAnnotationCountWithIsLeftPage:(BOOL)isLeftPage;

- (void) setScaleFactor:(float)scale;

@end
// 2012.02.01(Ver2.1 New) M.Chikyu

#endif
