/*
 *  Canvas.mm
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "Canvas.h"

Canvas::Canvas()
:	m_FacingMode(kOnePage)
,   m_IsNeedRedraw(false)
,	m_Page(nil)
{
	// init ctx A
	m_CtxA = MakeEmptyCtx();
	m_CtxB = MakeEmptyCtx();
	
	m_StatusLock = [[NSLock alloc]init];
};

Canvas::~Canvas(){
	
	CleanCtxA();
	CleanCtxB();
	if (nil != m_StatusLock) {
		[m_StatusLock dealloc];
		m_StatusLock = nil;
	}
}

void Canvas::DoLock(){
#ifdef THREAD_DEBUG
	NSLog(@"Canvas::DoLock() Start...");
#endif
	if (nil != m_StatusLock) {
		[m_StatusLock lock];
	}
}

void Canvas::DoUnlock(){
#ifdef THREAD_DEBUG
	NSLog(@"Canvas::DoUnlock() Start...");
#endif
	if (nil != m_StatusLock) {
		[m_StatusLock unlock];
	}
}

bool Canvas::ReverseNeedRedrawFlag()
{
	bool bRet = m_IsNeedRedraw;
	if (m_IsNeedRedraw) {
		m_IsNeedRedraw = false;
	}
	return bRet;
}

void Canvas::SetNeedRedrawStatus()
{
#ifdef THREAD_DEBUG
	NSLog(@"Canvas::SetNeedRedrawStatus() Start...");
#endif
	m_IsNeedRedraw = true;
}

void Canvas::SetCtxA(const CANVAS_CTX& ctx){ 
	CleanCtxA();
	m_CtxA = ctx;	
	if (nil != m_CtxA.m_Context) {
		m_CtxA.m_Image = CGBitmapContextCreateImage(m_CtxA.m_Context);
	} 
}

void Canvas::SetCtxB(const CANVAS_CTX& ctx){ 
	CleanCtxB();
	m_CtxB = ctx;	
	if (nil != m_CtxB.m_Context) {
		m_CtxB.m_Image = CGBitmapContextCreateImage(m_CtxB.m_Context);
	} 
}

void Canvas::CleanCtxA()
{
	CleanCtx(m_CtxA);
}

void Canvas::CleanCtxB()
{
	CleanCtx(m_CtxB);
}

void Canvas::CleanCtx(CANVAS_CTX& ctx)
{
#ifdef THREAD_DEBUG
	NSLog(@"Canvas::DeleteCtx() Start...");
#endif
	if (nil != ctx.m_Image) {
		CGImageRelease(ctx.m_Image);
		ctx.m_Image = nil;
	}
	if (nil != ctx.m_Context) {	
		CGContextRelease(ctx.m_Context);
		ctx.m_Context = nil;
	}
}

bool Canvas::CtxEqualToCtx(const CANVAS_CTX& ctx1, const CANVAS_CTX& ctx2)
{
	bool bRet = true;
	
	//bRet &= (ctx1.m_Context == ctx2.m_Context);
	//bRet &= (ctx1.m_Image   == ctx2.m_Image);
	bRet &= (ctx1.m_Scale   == ctx2.m_Scale);
	bRet &= (ctx1.m_PageFitScale == ctx2.m_PageFitScale);
	bRet &= (CGRectEqualToRect(ctx1.m_SrcRect, ctx2.m_SrcRect));
	bRet &= (CGRectEqualToRect(ctx1.m_DestRect, ctx2.m_DestRect));
	bRet &= (ctx1.m_PageNum      == ctx2.m_PageNum);
	//bRet &= (ctx1.m_DrawStatus   == ctx2.m_DrawStatus);
	
	return bRet;
}

Canvas::CANVAS_CTX Canvas::MakeEmptyCtx()
{
	CANVAS_CTX ctx;
	ctx.m_Context = nil;
	ctx.m_Image = nil;
	ctx.m_Scale = 0;
	ctx.m_PageFitScale = 0;
	ctx.m_SrcRect = CGRectMake(0, 0, 0, 0);
	ctx.m_DestRect = CGRectMake(0, 0, 0, 0);
	ctx.m_PageNum = -1;
	ctx.m_DrawStatus = kNoDraw;
	
	return ctx;
}