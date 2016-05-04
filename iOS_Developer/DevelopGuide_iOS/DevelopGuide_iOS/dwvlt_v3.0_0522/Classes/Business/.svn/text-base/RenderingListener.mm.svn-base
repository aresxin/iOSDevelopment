/*
 *  RenderingListener.mm
 *  DWViewer
 *
 *  Created by tongjo on 10-11-1.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "RenderingListener.h"
#import "Canvas.h"
#import "DWPageView.h"
#import "Utility.h"
void DrawingListener::FinishedDrawing(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx)
{
	// paste a part of page on the offscreen
	if (!CGRectIsEmpty(ctx.m_SrcRect)) {
		FinishedOffscreen(nPageNum, canvas, ctx);
	} else {
		// paste one page on the target view.
		if (CGRectIsEmpty(ctx.m_DestRect)) {
			FinishedOnePage(nPageNum, canvas, ctx);
		} else {
			FinishedRect(nPageNum, canvas, ctx);
		}	
	}
}

void DrawingListener::FinishedOnePage(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx)
{
    if (NULL == canvas) {
		return;
	}
	
	DWPageView* page = canvas->GetPage();
	if (nil == page) {
		return;
	}
	
	page.canvas = canvas;
	//page.transform = CGAffineTransformMakeScale(1.0, 1.0);
	[page performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
}

void DrawingListener::FinishedRect(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx)
{
    if (NULL == canvas) {
		return;
	}
	
	DWPageView* page = canvas->GetPage();
	if (nil == page) {
		return;
	}
	
	page.canvas = canvas;
	//page.transform = CGAffineTransformMakeScale(1.0, 1.0);
	
	CGRect rect = ctx.m_DestRect;
	NSValue* rectValue = [NSValue valueWithCGRect:rect];
	[page performSelectorOnMainThread:@selector(setNeedsDisplayInRectAsValue:) withObject:rectValue waitUntilDone:NO];
}

void DrawingListener::FinishedOffscreen(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx)
{
	if (NULL == canvas) {
		return;
	}
	
	DWPageView* page = canvas->GetPage();
	if (nil == page) {
		return;
	}
	
	DWPageView* offscreenView = page.offscreenView;
	if (nil == offscreenView) {
		return;
	}
	if (page.isZooming) {
		return;
	}
	offscreenView.canvas = canvas;	
	offscreenView.hidden = NO;
	[offscreenView performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:NO];
}

