/*
 *  GraphicDrawer.mm
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import <CoreGraphics/CoreGraphics.h>
#import "GraphicDrawer.h"
#import "Utility.h"
#import "DocumentHandle.h"

GraphicDrawer::GraphicDrawer(DocumentHandle* doc)
: m_Document(doc)
{
}

GraphicDrawer::~GraphicDrawer()
{

}

void GraphicDrawer::BreakDrawing()
{
	if (NULL != m_Document) {
		m_Document->BreakDrawing();
	}
}

// 2011/10/05 M.Chikyu (AR18595) start
void GraphicDrawer::ResetDrawing()
{
	if (NULL != m_Document)
	{
		m_Document->ResetDrawing();
	}
}
// 2011/10/05 M.Chikyu (AR18595) end

bool GraphicDrawer::Draw(CavansCtx& canvasCtx)
{
	// Check argument.
	if (canvasCtx.m_PageNum < 0) {
		return false;
	}
	
	if (canvasCtx.m_Scale <= 0) {
		return false;
	}

	if (nil == canvasCtx.m_Context) {
		return false;
	}
	
	if (NULL == m_Document) {
		return false;
	}
	
	FileInfo* fileInfo = m_Document->GetFileInfo();
	if (NULL == fileInfo) {
		return false;
	}
	
	int nPageCount = fileInfo->GetPageCount();
	if ( canvasCtx.m_PageNum + 1 > nPageCount ) {
		return false;
	}
	bool bRet = m_Document->DrawPage(canvasCtx.m_PageNum,
									 canvasCtx.m_Context,
									 canvasCtx.m_Scale,
									 CGRectNull);
	return  bRet;
}

bool GraphicDrawer::CtxEqualToCtx(const CANVAS_CTX& ctx1, const CANVAS_CTX& ctx2)
{
	bool bRet = true;
	
	bRet &= (ctx1.m_Scale        == ctx2.m_Scale);
	bRet &= (ctx1.m_PageNum      == ctx2.m_PageNum);
	
	return bRet;
}

GraphicDrawer::CANVAS_CTX GraphicDrawer::MakeEmptyCtx()
{
	CANVAS_CTX ctx;
	ctx.m_Context      = nil;
	ctx.m_Scale        = 0;
	ctx.m_PageNum      = -1;
	return ctx;
}

// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
bool GraphicDrawer::IsDrawingLockUsed()
{
	return m_Document->IsDrawingLockUsed();
}
// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
