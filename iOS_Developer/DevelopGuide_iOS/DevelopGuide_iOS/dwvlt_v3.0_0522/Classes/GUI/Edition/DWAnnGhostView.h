//
//  DWAnnGhostView.h
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "DWViewerGUIConst.h"
typedef unsigned long	COLORREF;



// delegate
// ----------------------------

@protocol DWAnnotationEditDelegate <NSObject>
@optional
- (void) didFinishedMoveAnnotationWithMovedOffset:(CGSize)offset;
@end


@protocol DWFreeHandAnnotationEditDelegate <NSObject>
@optional
- (void) didFinishedEditFreehandAnnotationWithPionts:(NSMutableArray *)points;
@end



// DWAnnShadowGhostView
// ---------------------------------
@interface DWAnnShadowGhostView : UIView
{
    id <DWAnnotationEditDelegate> delegate;
    
    COLORREF            lineColor;
    long                lineWidth;
    
    CGRect              annoSrcRect;
    CGPoint             srcPosition;
    CGPoint             dstPosition;
	CGRect              pageViewRect;
	BOOL                isNeedMove;
    
    BOOL                isFixed;
}
@property (nonatomic, assign) id <DWAnnotationEditDelegate> delegate;
@property COLORREF lineColor;
@property long lineWidth;

- (id) initWithFrame:(CGRect)frame 
       withPageFrame:(CGRect)pageRect 
         withIsFixed:(BOOL)fixed;
@end



// DWAnnBorderGhostView
// ---------------------------------
@interface DWAnnBorderGhostView : UIView
{
	CGRect  annotationFrame;
	CGPoint startLocation;
	UIColor *dashLineColor;

	float	m_bmpScale;
	CGFloat	m_zoomScale;
}
@property (nonatomic, retain) UIColor *dashLineColor;

- (id)initWithFrame:(CGRect)frame
		borderColor:(UIColor *)bcolor
		  zoomScale:(CGFloat)zoomScale;

@end



// DWFreeHandAnnGhostView
// ---------------------------------
#define _KEY_COLOR_   @"lineColor"
#define _KEY_WIDTH_   @"lineWidth"
#define _KEY_POINTS_  @"points"

// wangpp 2012.2.29 start
// freehand transparent
#define _KEY_TRANS_ @"transparent"
// wangpp 2012.2.29 end

@interface DWFreeHandAnnGhostView : UIView
{
	// 2012.01.30 M.Chikyu start.
//	long                lineWidth;
	float				lineWidth;
	// 2012.01.30 M.Chikyu end.

	UIColor             *lineUIColor;
	
	// wangpp 2012.2.29 start
	// freehand transparent
	BOOL               transparent;
	// wangpp 2012.2.29 end
	
	NSMutableArray      *arrayStrokes;
	BOOL                isTouchBegin;
	id <DWFreeHandAnnotationEditDelegate> delegate;
}

// 2012.01.30 M.Chikyu start.
//@property long lineWidth;
@property float lineWidth;
// 2012.01.30 M.Chikyu end.

@property (nonatomic, retain) UIColor *lineUIColor;

// wangpp 2012.2.29 start
// freehand transparent
@property BOOL transparent;
// wangpp 2012/2.29 end

@property (nonatomic, assign) id <DWFreeHandAnnotationEditDelegate> delegate;
@property (nonatomic, retain) NSMutableArray *arrayStrokes;
@end

