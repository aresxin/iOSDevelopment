/*
 *  DocumentRendering.h
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#import <map>
#import "Canvas.h"
#import <CoreGraphics/CoreGraphics.h>

class GraphicDrawer;
class DocumentHandle;
class RenderingListener;
@class RenderingThread;
@class DWPageView;

// typedef of canvas's map.
typedef std::pair< int, Canvas* > PAGENUM_CANVAS_PAIR;
typedef std::map< int, Canvas* >::iterator PAGENUM_CANVAS_ITERATOR;
typedef std::map< int, Canvas* > PAGENUM_CANVAS_MAP;

class DocumentRendering
{
public:
	DocumentRendering(DocumentHandle* document, int nPreDrawPageCount);
	virtual ~DocumentRendering();

	// Stop current thread. Must call Start() after called this method.
	bool ChangeDocument(DocumentHandle* document, int nPreDrawPageCount);
	
	// Drawing methods.
	// Use bitmap context as cache.
	bool DrawPage(DWPageView* page);
	
	// V4
	// Use layer's context, not bitmap context.
	// Do not use drawing thread.
	bool DrawPage(DWPageView* page, CGContextRef ctcx, CGRect sourceRect);
	
	// Getter and Setter
	bool SetDrawer(GraphicDrawer* drawer, bool bOwnDrawer);
	void SetListener(RenderingListener* listener){ m_Listener = listener; }
	int  GetDrawPageCount() { return m_PageCount; }
	int  GetDrawingPage() { return m_DrawingPage; }	 
	GraphicDrawer* GetDrawer() { return m_Drawer; }           
	
	Canvas* GetCanvas(int nPageNum);	 // sync call
	bool GetStartPage(int* pStartPage);	 // sync call
	
	// These method only be used by RenderingThread.
	// But can't be declared as private, because objcetc class can't be a friend of a c++ class.
	
	void SetDrawingPage(int nDrawingPage);
	void GetResetStartPageFlag(bool* pResetStartPageFlag);              // sync call
	void SetResetStartPageFlag();                                       // sync call
	void GetResetStartPageFlagAndReversFlag(bool* pResetStartPageFlag); // sync call

	bool BeContinue(){ return m_bContinue;}
	void FinishedDrawing(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx);
	bool AddCanvas(int nPageNum, Canvas* canvas, bool bOwnCanvas);	// sync call
	void DeleteCanvas(int nPageNum);	                            // sync call
	
	void DoLock();
	BOOL TryLock();
	void DoUnlock();
	
private:
	// create a new thread and begin to rendering pages.
	bool Start(int nStartPage);
	// cancel current thread.
	void Stop();
	// cancel current thread and clean resource.
	void CleanUp();		

private:
	
	DocumentHandle* m_Document;	

	int m_PageCount;
	int m_StartPage;
	
	bool m_bOwnDrawer;
	GraphicDrawer* m_Drawer;
	
	RenderingThread* m_WorkingThread;
	NSLock* m_WorkingThreadLock;
	int m_DrawingPage;
	
	bool m_bContinue;
	bool m_bResetStartPage;
	
	PAGENUM_CANVAS_MAP m_canvas;
	PAGENUM_CANVAS_MAP m_canvasNeedToDelete;
	
	RenderingListener* m_Listener;
};