//
//  DWPageView.m
//  DWViewer
//
//  Created by FX Neusoft on 10-10-19.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DWPageView.h"
#import "PageViewManager.h"
#import "DocumentViewController.h"
#import "DWViewerAppDelegate.h"
#import "GraphicDrawer.h"
#import "DWDrawer.h"

// 2012.02.01(Ver2.1 New) M.Chikyu
#import "DWScrollView.h"
// 2012.02.01(Ver2.1 New) M.Chikyu

@implementation DWPageView
@synthesize isFacingMode;
@synthesize m_PageInfoA;
@synthesize m_PageInfoB;

- (id)initWithFrame:(CGRect)frame
{
	// in drawLayer method, layer's ClipBoundingBox will be round by core.
	// so we ajust frame layer's ClipBoundingBox rect.
	
	// liuqw 20110328 start
	// 表示品質が低下を対応
	/*
	CGRect viewFrame = CGRectMake((float)frame.origin.x,
								  (float)frame.origin.y,
								  (float)frame.size.width,
								  (float)frame.size.height);
	*/
	CGRect viewFrame = CGRectMake((int)frame.origin.x,
								  (int)frame.origin.y,
								  (int)frame.size.width,
								  (int)frame.size.height);
	// liuqw 20110328 end

	self = [super initWithFrame:viewFrame];
	if (self == nil)
	{
		return nil;
	}

	self.multipleTouchEnabled = YES;
	self.clearsContextBeforeDrawing = YES;
	// V4 
	// contentMode's default value is UIViewContentModeScaleToFill. 
	// And, if layer's tile size < frame's size, CATiledLayer's scale(transform.a) will be double.
	
	// Be careful... 
	// Frame's size is a float. If set tilesize as same value, the float value will be rounded. 
	// For excample:
	// Frame's width = 10.8, and set tilesize's width as same value,
	// Then, in method drawLayer, ClipBounding' width be changed to 10.0.
	// who change it? why changed it?
	// 10.0 < 10.8, transform.a changed to double.
	// We do not want that!
	self.contentMode = UIViewContentModeScaleToFill;
	isFacingMode = NO;
	
	// V4 
	// Init tiled layer's property.
	// Tiled layer's tile size is frame * 2.
	// If contentScaleFactor is 2 for Retain Diaplay,
	// we set tile size as double frame * 2.
	/* delete for display large annotation
	 CGFloat scaleFactor = self.contentScaleFactor;
	 myTiledLayer.tileSize = CGSizeMake(viewFrame.size.width * scaleFactor * 2, 
	 viewFrame.size.height * scaleFactor * 2);
	 */
	// tongjo 20101204
	// zoomScale = 1  : draw with pageFitScale * 2
	// zoomScale = 2  : no redraw
	// zommScale > 2  : redraw with pageFitScale * 4
	// if drawde as pageFitScale * 4 once, never redraw again.
	
	// When zoomOut, do not need redraw.
	CATiledLayer* myTiledLayer = (CATiledLayer*)self.layer;	
	
	// liuqw 20110622 start
	// AR NO.17847 の対応
	
	/*
	 myTiledLayer.levelsOfDetail = 3; 
	 myTiledLayer.levelsOfDetailBias = 3;
	 */
	myTiledLayer.levelsOfDetail = 4; 
	myTiledLayer.levelsOfDetailBias = 5;
	
	// liuqw 20110622 end
	
	linkAnnotationIndex1.clear();
	linkAnnotationIndex2.clear();
	
    return self;
}

// tongtx 2012.03.23 start
// 選択機能の追加
- (BOOL)canBecomeFirstResponder 
{
	return YES;
}
// tongtx 2012.03.23 end

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
	// For V4, use tiled layer.
	// Do drawing in drawLayer method.
}


#pragma mark -
#pragma mark Draw Tiled Layer
- (void) drawLayer:(CALayer*)layer inContext:(CGContextRef)context
{
	// 2012.02.01(Ver2.1 New) M.Chikyu
	DWScrollView *dwsView = (DWScrollView*)[self superview];
	if (dwsView.isPreDraw == YES)
	{
		dwsView.frame = dwsView.afterFrame;
		dwsView.isPreDraw = NO;
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// Current tiled layer's scale. It's not PageScale.
	// For Retain Display, CTM's a will be double.
	float currScale = CGContextGetCTM(context).a;

#ifdef _DEBUG
	NSLog(@"drawLayer currScale = %f", currScale);
	NSLog(@"drawLayer zoomScale = %f", ((UIScrollView*)self.superview).zoomScale);
#endif	

    // get drawing target rect.
	CGRect rect = CGContextGetClipBoundingBox(context);

	// begin drawing....
	CGContextSaveGState(context);
	
	// 1. draw gray back ground on the whole area
	CGContextAddRect(context, rect);
	CGContextSetFillColorWithColor(context,[UIColor grayColor].CGColor);
	CGContextDrawPath(context, kCGPathFill);
	
	// Only one page
	if (isFacingMode == NO)
	{
		// 2. draw white back ground for page area
		CGRect pageRect = CGRectIntersection(rect, m_PageInfoA.m_SrcRect);	

		if (CGRectIsEmpty(pageRect) == false)
		{
			CGContextAddRect(context, pageRect);
			CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
			CGContextDrawPath(context, kCGPathFill);
		}
		
		// 3. clip with annotation
		CGRect pageRectWithAnno = CGRectIntersection(rect, m_PageInfoA.m_SrcRectWithAnno);
		CGContextAddRect(context, pageRectWithAnno);
		CGContextClip(context);

		// 4. move origin
		CGFloat moveOffsetX = m_PageInfoA.m_SrcRect.origin.x; 
		CGFloat moveOffsetY = m_PageInfoA.m_SrcRect.origin.y;
		CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
		
		// 5. scale for draw a part of DW page.
		CGContextScaleCTM(context, 1/currScale, 1/currScale);
		
		GraphicDrawer::CavansCtx ctx = GraphicDrawer::MakeEmptyCtx();
		ctx.m_Scale                  = m_PageInfoA.m_PageFitScale * currScale;
		ctx.m_Context                = context;
		ctx.m_PageNum                = m_PageInfoA.m_PageNum;

		// 7. drawing
		DWDrawer* drawer = ((DWLayer*)layer).drawer;
		if (drawer != nil)
		{
			// do drawing
			[drawer drawWithCtx:ctx];
		}
		
	// tow page	
	}
	else
	{
		// 2. draw white back ground for page area
		CGRect pageRectA = CGRectIntersection(rect, m_PageInfoA.m_SrcRect);
		CGRect pageRectB = CGRectIntersection(rect, m_PageInfoB.m_SrcRect);
		
		if (CGRectIsEmpty(pageRectA) == false &&
			m_PageInfoA.m_PageNum != -1)
		{
			CGContextAddRect(context, pageRectA);
		}
		
		if (CGRectIsEmpty(pageRectB) == false &&
			m_PageInfoB.m_PageNum != -1)
		{
			CGContextAddRect(context, pageRectB);
		}
		
		CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
		CGContextDrawPath(context, kCGPathFill);

		// 3.clip with annotation	

		// for tow page, never display intact annotation.
		CGRect pageRectAWithAnno = CGRectIntersection(rect, m_PageInfoA.m_SrcRectWithAnno);
		CGRect pageRectBWithAnno = CGRectIntersection(rect, m_PageInfoB.m_SrcRectWithAnno);

		// 4. Draw first page
		if (CGRectIsEmpty(pageRectA) == false &&
			m_PageInfoA.m_PageNum != -1)
		{
			CGContextSaveGState(context);
			
			if (CGRectIsEmpty(pageRectAWithAnno) == false &&
				m_PageInfoA.m_PageNum != -1)
			{
				CGContextAddRect(context, pageRectAWithAnno);
			}
			
			CGContextClip(context);
			
			// 4.1 move origin
			CGFloat moveOffsetX = m_PageInfoA.m_SrcRect.origin.x; 
			CGFloat moveOffsetY = m_PageInfoA.m_SrcRect.origin.y;
			CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
			
			// 4.2 scale for draw page.
			CGContextScaleCTM(context, 1/currScale, 1/currScale);
			
			// 4.3 draw
			GraphicDrawer::CavansCtx ctxA = GraphicDrawer::MakeEmptyCtx();
			ctxA.m_Scale                  = m_PageInfoA.m_PageFitScale * currScale;
			ctxA.m_Context                = context;
			ctxA.m_PageNum                = m_PageInfoA.m_PageNum;
			// drawing
			DWDrawer* drawer = ((DWLayer*)layer).drawer;
			
			if (drawer != nil)
			{
				[drawer drawWithCtx:ctxA];
			}
			
			CGContextRestoreGState(context);
		}
		
		CGContextFlush(context);

		// 5. Draw sec page
		if (CGRectIsEmpty(pageRectB) == false &&
			m_PageInfoB.m_PageNum != -1)
		{
			CGContextSaveGState(context);
			
			if (CGRectIsEmpty(pageRectBWithAnno) == false &&
				m_PageInfoB.m_PageNum != -1)
			{
				CGContextAddRect(context, pageRectBWithAnno);
			}
			
			CGContextClip(context);
			
			// 5.1 move origin.
			CGFloat moveOffsetX = m_PageInfoB.m_SrcRect.origin.x; 
			CGFloat moveOffsetY = m_PageInfoB.m_SrcRect.origin.y;
			CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
			
			// 5.2 scale for draw page.
			CGContextScaleCTM(context, 1/currScale, 1/currScale);
			
			// 5.3 draw
			GraphicDrawer::CavansCtx ctxB = GraphicDrawer::MakeEmptyCtx();
			ctxB.m_Scale                  = m_PageInfoB.m_PageFitScale * currScale;
			ctxB.m_Context                = context;
			ctxB.m_PageNum                = m_PageInfoB.m_PageNum;

			// drawing
			DWDrawer* drawer = ((DWLayer*)layer).drawer;
			if (drawer != nil)
			{
				[drawer drawWithCtx:ctxB];
			}
			
			CGContextRestoreGState(context);
		}
	}
	
	// end drawing.
	CGContextRestoreGState(context);

}

- (void) addLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage
{
	if (isLeftPage == YES)
	{
		linkAnnotationIndex1.push_back(index);
	}
	else
	{
		linkAnnotationIndex2.push_back(index);
	}
}

- (int)  getLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage
{
	int annotationIndex = -1;
	
	if (isLeftPage == YES)
	{
		int size = linkAnnotationIndex1.size();

		if (index >= size || index < 0)
		{
			return -1;
		}
		
		annotationIndex = linkAnnotationIndex1[index];
	}
	else
	{
		int size = linkAnnotationIndex2.size();

		if (index >= size || index < 0)
		{
			return -1;
		}
		
		annotationIndex = linkAnnotationIndex2[index];
	}

	return annotationIndex;
}

- (int)  getLinkAnnotationCountWithIsLeftPage:(BOOL)isLeftPage
{
	int count = 0;
	
	if (isLeftPage == YES)
	{
		count = linkAnnotationIndex1.size();
	}
	else
	{
		count = linkAnnotationIndex2.size();
	}
	
	return count;
}

- (void)dealloc
{
	[self clearLayerContent];
    [super dealloc];
}


// V4
+ (Class)layerClass
{  
    return [DWLayer class];  
}

// V4
// clear layer's content
- (void) clearLayerContent;
{
	if (self.layer != nil)
	{
		self.layer.delegate = nil;
		[self.layer removeFromSuperlayer];
	}
}

// V4 for Retain Display
- (void)layoutSubviews
{
	// it's a workground from google.
	// For Retain Display, contentScaleFactor is 2.0f.
	// When use tiled layer, layer's transform.a be changed to double as 4.0f.
	if ([self respondsToSelector:@selector(contentScaleFactor)])
	{
		self.contentScaleFactor = 1.0f;
	}
}

@end


// 2012.02.01(Ver2.1 New) M.Chikyu

@implementation DWPageEditView
@synthesize isFacingMode;
@synthesize m_PageInfoA;
@synthesize m_PageInfoB;
@synthesize drawer;

// 2012.02.13 M.Chikyu start.
@synthesize m_drawTime;
// 2012.02.13 M.Chikyu end.

//@synthesize m_bmpScale;

- (id)initWithFrame:(CGRect)frame
{
	// in drawLayer method, layer's ClipBoundingBox will be round by core.
	// so we ajust frame layer's ClipBoundingBox rect.

	CGRect viewFrame = CGRectMake((int)frame.origin.x,
								  (int)frame.origin.y,
								  (int)frame.size.width,
								  (int)frame.size.height);
	self = [super initWithFrame:viewFrame];
	if (self == nil)
	{
		return nil;
	}
	
	self.multipleTouchEnabled = YES;
	self.clearsContextBeforeDrawing = YES;
	self.contentMode = UIViewContentModeScaleToFill;
	isFacingMode = NO;

	m_bmpScale = 2.0;

	linkAnnotationIndex1.clear();
	linkAnnotationIndex2.clear();

	// 2012.02.13 M.Chikyu start.
	m_drawTime = 0.0;
	// 2012.02.13 M.Chikyu end.

    return self;
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
	// 2012.02.13 M.Chikyu start.
	NSDate *startTime = [NSDate date];
	// 2012.02.13 M.Chikyu end.

	CGContextRef context = UIGraphicsGetCurrentContext();
	
	float currScale = CGContextGetCTM(context).a;
	
	// begin drawing....
	CGContextSaveGState(context);
	
	// 1. draw gray back ground on the whole area
	CGContextAddRect(context, rect);
	CGContextSetFillColorWithColor(context,[UIColor grayColor].CGColor);
	CGContextDrawPath(context, kCGPathFill);
	
	// Only one page
	if (isFacingMode == NO)
	{
		// 2. draw white back ground for page area
		CGRect pageRect = CGRectIntersection(rect, m_PageInfoA.m_SrcRect);	
		
		if (CGRectIsEmpty(pageRect) == false)
		{
			CGContextAddRect(context, pageRect);
			CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
			CGContextDrawPath(context, kCGPathFill);
		}
		
		// 3. clip with annotation
		CGRect pageRectWithAnno = CGRectIntersection(rect, m_PageInfoA.m_SrcRectWithAnno);
		CGContextAddRect(context, pageRectWithAnno);
		CGContextClip(context);
		
		// 4. move origin
		CGFloat moveOffsetX = m_PageInfoA.m_SrcRect.origin.x; 
		CGFloat moveOffsetY = m_PageInfoA.m_SrcRect.origin.y;
		CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
		
		// 5. scale for draw a part of DW page.
		CGContextScaleCTM(context, 1/currScale, 1/currScale);
		
		GraphicDrawer::CavansCtx ctx = GraphicDrawer::MakeEmptyCtx();
		ctx.m_Scale                  = m_PageInfoA.m_PageFitScale * currScale;
		ctx.m_Context                = context;
		ctx.m_PageNum                = m_PageInfoA.m_PageNum;
		
		// 7. drawing
		if (drawer != nil)
		{
			// do drawing
			[drawer drawWithCtx:ctx];
		}
		
		// two page	
	}
	else
	{
		// 2. draw white back ground for page area
		CGRect pageRectA = CGRectIntersection(rect, m_PageInfoA.m_SrcRect);
		CGRect pageRectB = CGRectIntersection(rect, m_PageInfoB.m_SrcRect);
		
		if (CGRectIsEmpty(pageRectA) == false &&
			m_PageInfoA.m_PageNum != -1)
		{
			CGContextAddRect(context, pageRectA);
		}
		
		if (CGRectIsEmpty(pageRectB) == false &&
			m_PageInfoB.m_PageNum != -1)
		{
			CGContextAddRect(context, pageRectB);
		}
		
		CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
		CGContextDrawPath(context, kCGPathFill);
		
		// 3.clip with annotation	
		
		// for tow page, never display intact annotation.
		CGRect pageRectAWithAnno = CGRectIntersection(rect, m_PageInfoA.m_SrcRectWithAnno);
		CGRect pageRectBWithAnno = CGRectIntersection(rect, m_PageInfoB.m_SrcRectWithAnno);
		
		// 4. Draw first page
		if (CGRectIsEmpty(pageRectA) == false &&
			m_PageInfoA.m_PageNum != -1)
		{
			CGContextSaveGState(context);
			
			if (CGRectIsEmpty(pageRectAWithAnno) == false &&
				m_PageInfoA.m_PageNum != -1)
			{
				CGContextAddRect(context, pageRectAWithAnno);
			}
			
			CGContextClip(context);
			
			// 4.1 move origin
			CGFloat moveOffsetX = m_PageInfoA.m_SrcRect.origin.x; 
			CGFloat moveOffsetY = m_PageInfoA.m_SrcRect.origin.y;
			CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
			
			// 4.2 scale for draw page.
			CGContextScaleCTM(context, 1/currScale, 1/currScale);
			
			// 4.3 draw
			GraphicDrawer::CavansCtx ctxA = GraphicDrawer::MakeEmptyCtx();
			ctxA.m_Scale                  = m_PageInfoA.m_PageFitScale * currScale;
			ctxA.m_Context                = context;
			ctxA.m_PageNum                = m_PageInfoA.m_PageNum;

			// drawing
			if (drawer != nil)
			{
				[drawer drawWithCtx:ctxA];
			}
			
			CGContextRestoreGState(context);
		}
		
		CGContextFlush(context);
		
		// 5. Draw sec page
		if (CGRectIsEmpty(pageRectB) == false &&
			m_PageInfoB.m_PageNum != -1)
		{
			CGContextSaveGState(context);
			
			if (CGRectIsEmpty(pageRectBWithAnno) == false &&
				m_PageInfoB.m_PageNum != -1)
			{
				CGContextAddRect(context, pageRectBWithAnno);
			}
			
			CGContextClip(context);
			
			// 5.1 move origin.
			CGFloat moveOffsetX = m_PageInfoB.m_SrcRect.origin.x; 
			CGFloat moveOffsetY = m_PageInfoB.m_SrcRect.origin.y;
			CGContextTranslateCTM(context, moveOffsetX, moveOffsetY);
			
			// 5.2 scale for draw page.
			CGContextScaleCTM(context, 1/currScale, 1/currScale);
			
			// 5.3 draw
			GraphicDrawer::CavansCtx ctxB = GraphicDrawer::MakeEmptyCtx();
			ctxB.m_Scale                  = m_PageInfoB.m_PageFitScale * currScale;
			ctxB.m_Context                = context;
			ctxB.m_PageNum                = m_PageInfoB.m_PageNum;
			
			// drawing
			if (drawer != nil)
			{
				[drawer drawWithCtx:ctxB];
			}
			
			CGContextRestoreGState(context);
		}
	}
	
	// end drawing.
	CGContextRestoreGState(context);
	
	// 2012.02.13 M.Chikyu start.
	m_drawTime = [startTime timeIntervalSinceNow] * -1.0;
	// 2012.02.13 M.Chikyu end.
}


#pragma mark -
#pragma mark Draw Tiled Layer

- (void) addLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage
{
	if (isLeftPage == YES)
	{
		linkAnnotationIndex1.push_back(index);
	}
	else
	{
		linkAnnotationIndex2.push_back(index);
	}
}

- (int)  getLinkAnnotationIndex:(int)index withIsLeftPage:(BOOL)isLeftPage
{
	int annotationIndex = -1;
	
	if (isLeftPage == YES)
	{
		int size = linkAnnotationIndex1.size();
		
		if (index >= size || index < 0)
		{
			return -1;
		}
		
		annotationIndex = linkAnnotationIndex1[index];
	}
	else
	{
		int size = linkAnnotationIndex2.size();
		
		if (index >= size || index < 0)
		{
			return -1;
		}
		
		annotationIndex = linkAnnotationIndex2[index];
	}
	
	return annotationIndex;
}

- (int)  getLinkAnnotationCountWithIsLeftPage:(BOOL)isLeftPage
{
	int count = 0;
	
	if (isLeftPage == YES)
	{
		count = linkAnnotationIndex1.size();
	}
	else
	{
		count = linkAnnotationIndex2.size();
	}
	
	return count;
}

- (void) setScaleFactor:(float)scale
{
	if ([self respondsToSelector:@selector(contentScaleFactor)])
	{
		m_bmpScale = self.contentScaleFactor * scale;
	}
}

- (void)layoutSubviews
{
	if ([self respondsToSelector:@selector(contentScaleFactor)])
	{
		self.contentScaleFactor = m_bmpScale;
	}
}

- (void)dealloc
{
    [super dealloc];
}

@end
// 2012.02.01(Ver2.1 New) M.Chikyu
