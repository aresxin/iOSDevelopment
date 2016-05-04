/*
 *  GraphicDrawer.h
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _GRAPHIC_DRAWER_H_
#define _GRAPHIC_DRAWER_H_

class DocumentHandle;

class GraphicDrawer
{
public:
	
	typedef struct CavansCtx
	{
		CGContextRef  m_Context;
		long          m_Scale;
		int           m_PageNum;
	} CANVAS_CTX;
	
	
public:
	GraphicDrawer(DocumentHandle* m_Document);
	~GraphicDrawer();
	
	// draw
	bool Draw(CavansCtx& canvasCtx);
	// break
	void BreakDrawing();
    
    // 2011/10/05 M.Chikyu (AR18595) start
	void ResetDrawing();
	// 2011/10/05 M.Chikyu (AR18595) end
	
	static bool CtxEqualToCtx(const CANVAS_CTX& ctx1, const CANVAS_CTX& ctx2);
	static CANVAS_CTX MakeEmptyCtx();
	
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	bool IsDrawingLockUsed();
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu

private:
	bool DrawPageOnContext(CavansCtx& canvasCtx);
	// document handle, DWDocumentHandle or PDFDocumentHandle.
	DocumentHandle* m_Document;
};

#endif