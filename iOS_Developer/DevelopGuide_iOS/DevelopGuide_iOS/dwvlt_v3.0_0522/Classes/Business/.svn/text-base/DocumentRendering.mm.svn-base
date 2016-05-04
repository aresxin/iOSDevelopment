/*
 *  DocumentRendering.cpp
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "DocumentRendering.h"
#import "GraphicDrawer.h"
#import "RenderingThread.h"
#import "RenderingListener.h"
#import "DWPageView.h"

DocumentRendering::DocumentRendering(DocumentHandle* document, int nPreDrawPageCount)
:m_Document(document)
,m_PageCount(nPreDrawPageCount)
,m_StartPage(-1)
,m_bOwnDrawer(false)
,m_Drawer(NULL)
,m_DrawingPage(-1)
,m_bContinue(false)
,m_bResetStartPage(false)
,m_Listener(NULL)
{
#ifdef THREAD_DEBUG
	NSLog(@"DocumentRendering::DocumentRendering() Start...");
#endif	
	m_WorkingThread = nil;
	m_WorkingThreadLock = nil;
	
	// V4 TMP
	m_Drawer = new GraphicDrawer(m_Document);
	
	
	m_WorkingThreadLock = [[NSLock alloc]init];
	if (nil == m_WorkingThreadLock) {
	}
}

DocumentRendering::~DocumentRendering()
{
#ifdef THREAD_DEBUG
	NSLog(@"DocumentRendering::~DocumentRendering() Start...");
#endif	
	CleanUp();
}

bool DocumentRendering::ChangeDocument(DocumentHandle* document, int nPreDrawPageCount)
{
#ifdef THREAD_DEBUG
	NSLog(@"ChangeDocument(nDrawPageCount = %d) Start...", nPreDrawPageCount);
#endif
	if (NULL == document) {
		return false;
	}
	
	CleanUp();
	
	m_Document = document;
	m_PageCount = nPreDrawPageCount;
	
	return true;
}
#pragma mark -
#pragma mark Drawing Method
bool DocumentRendering::DrawPage(DWPageView* page)
{
	
	// V4 TMP
	return false;
	
#ifdef THREAD_DEBUG
	NSLog(@"DrawPage Start...");
#endif

	if (Nil == page) {
		return false;
	}
	
	// Page number should be >=0
	int nPageNum = page.m_PageInfoA.m_PageNum;
	if (nPageNum < 0) {
		return false;
	}
	
	// If canvas's not exist, create it.
	Canvas* canvas = GetCanvas(nPageNum);
	if (NULL == canvas) {
		canvas = new Canvas();
		if (NULL == canvas) {
			return false;
		}
		AddCanvas(nPageNum, canvas, true);
	} 
	
	// Operations belows must be sync.
	canvas->DoLock();
	
	//lock canvas-------------------------------------------------
	if (canvas->GetPage() != page || page.isReuse == YES) {
		canvas->SetNeedRedrawStatus(); //Draw page fit.
		canvas->SetPage(page);
	}
	
	if (page.isFacingMode) {
		canvas->SetFacingMode(Canvas::kTowPage);
	} else {
		canvas->SetFacingMode(Canvas::kOnePage);
	}

	Canvas::CavansCtx ctxA = canvas->GetCtxA();
	Canvas::CavansCtx ctxB = canvas->GetCtxA();
	
	Canvas::CavansCtx tmpCtxA = Canvas::MakeEmptyCtx();

	tmpCtxA.m_Scale = page.m_PageInfoA.m_Scale;
	tmpCtxA.m_PageFitScale = page.m_PageInfoA.m_PageFitScale;
	tmpCtxA.m_SrcRect = page.m_PageInfoA.m_SrcRect;
	tmpCtxA.m_DestRect = page.m_PageInfoA.m_DestRect;
	tmpCtxA.m_PageNum = page.m_PageInfoA.m_PageNum;
	
	// if ctx chagned, must redraw this page.
	if (!Canvas::CtxEqualToCtx(tmpCtxA, ctxA)) {
		canvas->SetNeedRedrawStatus(); //Need Draw page.
		canvas->SetCtxA(tmpCtxA);
	}
	
	// draw two page on one view.
	if (page.isFacingMode) {
		Canvas::CavansCtx tmpCtxB = Canvas::MakeEmptyCtx();

		// if ctx chagned, must redraw this page.
		tmpCtxB.m_Scale = page.m_PageInfoB.m_Scale;
		tmpCtxB.m_PageFitScale = page.m_PageInfoB.m_PageFitScale;
		tmpCtxB.m_SrcRect = page.m_PageInfoB.m_SrcRect;
		tmpCtxB.m_DestRect = page.m_PageInfoB.m_DestRect;
		tmpCtxB.m_PageNum = page.m_PageInfoB.m_PageNum;
		
		if (!Canvas::CtxEqualToCtx(tmpCtxB, ctxB)) {
			canvas->SetNeedRedrawStatus(); //Need Draw page.
			canvas->SetCtxB(tmpCtxB);
		}
	}
	
	if (canvas->IsNeedRedraw()) {
		if (NULL != m_Drawer) {
			//m_Drawer->BreakDrawing();
		}
		///V4
		/*
	    // draw background when Tow Page mode.	
		if (canvas->GetFacingMode() == Canvas::kTowPage) {
			// draw background of first page 
			if (canvas->GetCtxA().m_PageNum != -1) {
				page.needDrawBGGround = YES;
				CGRect rect = canvas->GetCtxA().m_DestRect;
				NSValue* rectValue = [NSValue valueWithCGRect:rect];
				[page performSelectorOnMainThread:@selector(setNeedsDisplayInRectAsValue:) withObject:rectValue waitUntilDone:YES];		
			}
			// draw background of sec page 
			if (canvas->GetCtxB().m_PageNum != -1) {
				page.needDrawBGGround = YES;
				CGRect rect = canvas->GetCtxB().m_DestRect;
				NSValue* rectValue = [NSValue valueWithCGRect:rect];
				[page performSelectorOnMainThread:@selector(setNeedsDisplayInRectAsValue:) withObject:rectValue waitUntilDone:YES];		
			}
		}*/
	}
	canvas->DoUnlock();
	return false;
	
	
	// unlock canvas-------------------------------------------------
	
	
	// for Tow Page mode, page number is the samll one.
	nPageNum = canvas->GetCtxA().m_PageNum;
	if (page.isFacingMode && canvas->GetCtxB().m_PageNum >= 0 && 
		canvas->GetCtxB().m_PageNum < nPageNum ) {
		nPageNum = canvas->GetCtxB().m_PageNum;
	}
	// change start page, working thread will start draw current page.
	DoLock();
	m_StartPage = nPageNum;
	m_bResetStartPage = true;
	DoUnlock();
	
	// if thread is not working, start it.
	if (nil == m_WorkingThread) {
		return Start(m_StartPage);
	}
	return true;
}



#pragma mark -
#pragma mark Setter/Getter

bool DocumentRendering::SetDrawer( GraphicDrawer* drawer, bool bOwnDrawer)
{
#ifdef THREAD_DEBUG
	NSLog(@"SetDrawer() Start...");
#endif
	if (NULL == drawer) {
		return false;
	}
	if (NULL != m_Drawer && bOwnDrawer) {
		delete m_Drawer;
	}
	m_Drawer = drawer;
	m_bOwnDrawer = bOwnDrawer;
	
	return true;
}

Canvas* DocumentRendering::GetCanvas(int nPageNum)
{
#ifdef THREAD_DEBUG
	NSLog(@"GetCanvas(nPageNum = %d) Start...", nPageNum);
#endif	
	Canvas* canvas = NULL;
	DoLock();
	PAGENUM_CANVAS_ITERATOR pcIt = m_canvas.find(nPageNum);
	if (pcIt != m_canvas.end()) {
		canvas = pcIt->second;
	}
	DoUnlock();
	return canvas;
}

bool DocumentRendering::GetStartPage(int* pStartPage)
{
#ifdef THREAD_DEBUG
	NSLog(@"GetStartPage Start...");
#endif
	if (NULL == pStartPage) {
		return false;
	}
	
	DoLock();
	*pStartPage = m_StartPage;
	DoUnlock();
	
	return true;
}

void DocumentRendering::SetDrawingPage(int nDrawingPage)
{
#ifdef THREAD_DEBUG
	NSLog(@"SetDrawingPage(nDrawingPage = %d) Start...", nDrawingPage);
#endif
	m_DrawingPage = nDrawingPage;
}

void DocumentRendering::GetResetStartPageFlag(bool* pResetStartPageFlag)
{
#ifdef THREAD_DEBUG
	NSLog(@"GetResetStartPageFlag() Start...");
#endif
	if (NULL == pResetStartPageFlag) {
		return;
	}
	*pResetStartPageFlag = m_bResetStartPage;
}

void DocumentRendering::SetResetStartPageFlag()
{
#ifdef THREAD_DEBUG
	NSLog(@"SetResetStartPageFlag() Start...");
#endif
	DoLock();
	m_bResetStartPage = true;
	DoUnlock();
	
}

void DocumentRendering::GetResetStartPageFlagAndReversFlag(bool* pResetStartPageFlag)
{
#ifdef THREAD_DEBUG
	//NSLog(@"GetResetStartPageFlagAndReversFlag() Start...");
#endif
	if (NULL == pResetStartPageFlag) {
		return;
	}
	DoLock();
	*pResetStartPageFlag = m_bResetStartPage;
	if (m_bResetStartPage) {
		m_bResetStartPage = false;
	}
	DoUnlock();
}

#pragma mark -
#pragma mark Finished Drawing
void DocumentRendering::FinishedDrawing(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx)
{
#ifdef THREAD_DEBUG
	NSLog(@"FinishedDrawing(nPageNum = %d) Start...", nPageNum);
#endif
	if (NULL != m_Listener) {
		m_Listener->FinishedDrawing(nPageNum, canvas, ctx);
	}
	m_DrawingPage = -1;
}

#pragma mark -
#pragma mark Manage canvas
bool DocumentRendering::AddCanvas(int nPageNum, Canvas* canvas, bool bOwnCanvas)
{
#ifdef THREAD_DEBUG
	NSLog(@"AddCanvas(nPageNum = %d) Start...", nPageNum);
#endif	
	if (NULL == canvas) {
		return false;
	}
	
	if (nPageNum < 0) {
		return false;
	}
	
	DoLock();
	PAGENUM_CANVAS_PAIR pcPair(nPageNum, canvas);
	std::pair< PAGENUM_CANVAS_ITERATOR, bool > retPair = m_canvas.insert(pcPair);
	if (bOwnCanvas && retPair.second) {
		m_canvasNeedToDelete.insert(pcPair);
	}
	DoUnlock();
	
	return retPair.second;
}

void DocumentRendering::DeleteCanvas(int nPageNum)
{
#ifdef THREAD_DEBUG
	NSLog(@"DeleteCanvas(nPageNum = %d) Start...", nPageNum);
#endif	
	Canvas* canvas = NULL;
	
	DoLock();
	PAGENUM_CANVAS_ITERATOR pcIt = m_canvas.find(nPageNum);
	if (pcIt != m_canvas.end()) {
		canvas = pcIt->second;
		if (NULL != canvas) {
			delete canvas;
			canvas = NULL;
		}
		m_canvas.erase(pcIt);
	}
	
	PAGENUM_CANVAS_ITERATOR pcItNeedToDelete = m_canvasNeedToDelete.find(nPageNum);
	if (pcItNeedToDelete != m_canvasNeedToDelete.end()) {
		canvas = pcItNeedToDelete->second;
		if (NULL != canvas) {
			delete canvas;
			canvas = NULL;
		}
		m_canvasNeedToDelete.erase(pcIt);
	}
	DoUnlock();
}

#pragma mark -
#pragma mark Lock/Unlock
void DocumentRendering::DoLock()
{
#ifdef THREAD_DEBUG
	//NSLog(@"DoLock Start...");
#endif
	if (nil != m_WorkingThreadLock) {
		[m_WorkingThreadLock lock];
	}
	
}

BOOL DocumentRendering::TryLock()
{
#ifdef THREAD_DEBUG
	//NSLog(@"DoUnlock Start...");
#endif
	if (nil != m_WorkingThreadLock) {
		return [m_WorkingThreadLock tryLock];
	}
	
	return NO;
}


void DocumentRendering::DoUnlock()
{
#ifdef THREAD_DEBUG
	//NSLog(@"DoUnlock Start...");
#endif
	if (nil != m_WorkingThreadLock) {
		[m_WorkingThreadLock unlock];
	}
}

#pragma mark -
#pragma mark Control Working Tread
bool DocumentRendering::Start(int nStartPage)
{
#ifdef THREAD_DEBUG
	NSLog(@"Start(nStartPage = %d) Start...", nStartPage);
#endif
	bool bRet = true;
	
	if (nStartPage < 0) {
		return false;
	}
	
	m_StartPage = nStartPage;
	
	if (NULL == m_Drawer) {
		if (NULL == m_Document) {
			return false;
		} 
		m_Drawer = new GraphicDrawer(m_Document);
		if (NULL == m_Drawer) {
			return false;
		}
		m_bOwnDrawer = true;
	}
	// V4 tmp
	m_WorkingThreadLock = [[NSLock alloc]init];
	if (nil == m_WorkingThreadLock) {
		return false;
	}
	
	// Start Working tread.
	m_bContinue = true;
	SetResetStartPageFlag();
	m_WorkingThread = [[RenderingThread alloc]initWithRendering:this];
	if (nil != m_WorkingThread) {
		[m_WorkingThread start];
	} else {
		CleanUp();
		return false;
	}
	
	return bRet;
}

void DocumentRendering::Stop()
{
#ifdef THREAD_DEBUG
	NSLog(@"Stop() Start...");
#endif
	// Stop Thread.
	if (NULL != m_Drawer) {
		m_Drawer->BreakDrawing();
	}
	m_bContinue = false;
	
	if (nil != m_WorkingThread) {
		// Sleep 3 sec.
		double sleeptimes = 3;
		while (sleeptimes > 0) {
			[NSThread sleepForTimeInterval:0.01];
			if ([m_WorkingThread isFinished] || [m_WorkingThread isCancelled]) {
				break;
			}
			sleeptimes -= 0.01;
		}
		if ([m_WorkingThread isExecuting]) {
			[m_WorkingThread cancel];
		}	
		[m_WorkingThread dealloc];
		m_WorkingThread = nil;
	}
}

void DocumentRendering::CleanUp()
{
#ifdef THREAD_DEBUG
	NSLog(@"CleanUp() Start...");
#endif	
	// Stop Thread.
	Stop();
	// Delete Lock.
	if (nil != m_WorkingThreadLock) {
		[m_WorkingThreadLock dealloc];
		m_WorkingThreadLock = nil;
	}

	m_Document = NULL;
	m_PageCount  = 0;
	m_StartPage  = -1;
	m_DrawingPage = -1;
	
	if (m_bOwnDrawer && NULL != m_Drawer) {
		delete m_Drawer;
	}
	m_Drawer = NULL;

	m_canvas.clear();
	PAGENUM_CANVAS_ITERATOR it = m_canvasNeedToDelete.begin();
	while (it != m_canvasNeedToDelete.end()) {
		Canvas* canvasToBeDelete = it->second;
		if (NULL != canvasToBeDelete) {
			delete canvasToBeDelete;
		}
	}
	m_canvasNeedToDelete.clear();
}
















