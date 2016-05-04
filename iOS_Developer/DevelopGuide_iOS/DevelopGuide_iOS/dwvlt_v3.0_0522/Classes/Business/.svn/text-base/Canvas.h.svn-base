/*
 *  Canvas.h
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#import <CoreGraphics/CoreGraphics.h>
@class DWPageView;
class Canvas
{
	
public:
	typedef enum CanvasStatus
	{
		kNoDraw = 0,
		KDrawing,
		KEndDraw
	} CANVAS_STATUS;
	
	typedef struct CavansCtx
	{
		CGContextRef  m_Context;
		CGImageRef    m_Image;
		long          m_Scale;
		long          m_PageFitScale;
		CGRect        m_SrcRect;
		CGRect        m_DestRect;
		int           m_PageNum;
		CANVAS_STATUS m_DrawStatus;
	} CANVAS_CTX;
	
	typedef enum FacingMode
	{
		kOnePage = 0,
		kTowPage
	} CANVAS_FACINGMODE;
	
public:
	Canvas();
	virtual ~Canvas();

	// Status Operator
	bool ReverseNeedRedrawFlag();
	bool IsNeedRedraw() { return m_IsNeedRedraw; };
	void SetNeedRedrawStatus();
	
	void DoLock();
	void DoUnlock();
	
	// Getter and Setter
	void SetCtxA(const CANVAS_CTX& ctx);
	CANVAS_CTX GetCtxA() { return m_CtxA; };
	void SetCtxB(const CANVAS_CTX& ctx);
	CANVAS_CTX GetCtxB() { return m_CtxB; };
	void SetPage(DWPageView* page) { m_Page = page; };
	DWPageView* GetPage() { return m_Page; };
	
	void CleanCtxA();
	void CleanCtxB();
	
	void SetFacingMode(CANVAS_FACINGMODE facingMode) { m_FacingMode = facingMode; };
	CANVAS_FACINGMODE GetFacingMode() { return m_FacingMode; };

	static bool CtxEqualToCtx(const CANVAS_CTX& ctx1, const CANVAS_CTX& ctx2);
	static CANVAS_CTX MakeEmptyCtx();
private:
	void CleanCtx(CANVAS_CTX& ctx);

private:
	CANVAS_FACINGMODE m_FacingMode;

	CANVAS_CTX m_CtxA;
	CANVAS_CTX m_CtxB;
	
	bool m_IsNeedRedraw;
	NSLock* m_StatusLock;
	
	DWPageView* m_Page;
};