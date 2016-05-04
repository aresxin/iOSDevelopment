//
//  RenderingThread.m
//  DWViewerw
//
//  Created by tongjo on 10-10-30.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "RenderingThread.h"
#import "GraphicDrawer.h"
#import "DWPageView.h"

@implementation RenderingThread
- (id)initWithRendering:(DocumentRendering*)Rendering
{
	if ((self = [super init]) != nil) {
		m_DocumentRendering = Rendering;
	}
	return self;
}

-(void)main
{
#ifdef THREAD_DEBUG
	NSLog(@"RenderingThread::main Start...");
#endif
	
	if (NULL == m_DocumentRendering) {
		return;
	}
	GraphicDrawer* drawer = m_DocumentRendering->GetDrawer();
	if (NULL == drawer) {
		return;
	}
	
	while (m_DocumentRendering->BeContinue()) {
		
		NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
		bool bResetStartPage = false;
		m_DocumentRendering->GetResetStartPageFlagAndReversFlag(&bResetStartPage);
		
		// begin a new task.
		if (bResetStartPage) {
			// Get current page.
			int nDrawPageCount = m_DocumentRendering->GetDrawPageCount();
			int nStartPage = 0;
			m_DocumentRendering->GetStartPage(&nStartPage);
			
			for (int i = 0; i < nDrawPageCount; i++) {
				
				// Check bResetStartPage again.
				bool bResetStartPage = false;
				m_DocumentRendering->GetResetStartPageFlag(&bResetStartPage);
				
				// if start page changed or drawing is broken, break, goto next page.
				if (bResetStartPage || !m_DocumentRendering->BeContinue()) {
					break;
				}
				
				int nCurrPage = i + nStartPage;
				
				// Drawer will create new CGContextRef.
				Canvas* currCanvas = m_DocumentRendering->GetCanvas(nCurrPage);
				if (NULL == currCanvas) {
					continue;
				}
				
				bool bNeedRedrawFlag = false;
				
				// draw firt page.
				// if there's only one page, it is CtxA also.
				Canvas::CavansCtx canvasCtxA = Canvas::MakeEmptyCtx();
				// lock canvas and get canvas status.
				currCanvas->DoLock();
				bNeedRedrawFlag = currCanvas->ReverseNeedRedrawFlag();
				canvasCtxA = currCanvas->GetCtxA();
				currCanvas->DoUnlock();
				
				if (bNeedRedrawFlag) {
					// notificate rendering current drawing page.
					m_DocumentRendering->SetDrawingPage(nCurrPage);
					// Draw page
					// if m_PageNum is -1, it's empty ctx.
					if (canvasCtxA.m_PageNum >= 0) {
						bool bDrawRet = drawer->Draw(canvasCtxA.m_PageNum, canvasCtxA);
						if (bDrawRet) {
							// Chage cavas's status
							canvasCtxA.m_DrawStatus = Canvas::KEndDraw;
							currCanvas->DoLock();
							currCanvas->SetCtxA(canvasCtxA);
							currCanvas->DoUnlock();

							// for Two Page mode, draw white background for paper.
							if (currCanvas->GetFacingMode() == Canvas::kTowPage) {
								DWPageView* page = currCanvas->GetPage();
								if (nil != page) {
									// dest rect should be clear and draw use white color.
									if (!CGRectIsEmpty(canvasCtxA.m_DestRect)) {
										// draw rect method will reset this falg when done the work.
										page.needDrawFirstPageBKGround = YES;
										CGRect rect = canvasCtxA.m_DestRect;
										NSValue* rectValue = [NSValue valueWithCGRect:rect];
										[page performSelectorOnMainThread:@selector(setNeedsDisplayInRectAsValue:) withObject:rectValue waitUntilDone:YES];		
									}
								}
							}
							// notificate renderings
							m_DocumentRendering->FinishedDrawing(nCurrPage, currCanvas, currCanvas->GetCtxA());
						} else {
							currCanvas->DoLock();
							currCanvas->SetNeedRedrawStatus();
							currCanvas->DoUnlock();
							continue;
						}
					}

					// second page
					if (currCanvas->GetFacingMode() == Canvas::kTowPage) {
						// Draw page
						Canvas::CavansCtx canvasCtxB = Canvas::MakeEmptyCtx();
						// lock canvas and get canvas status.
						currCanvas->DoLock();
						canvasCtxB = currCanvas->GetCtxB();
						currCanvas->DoUnlock();
						if (canvasCtxB.m_PageNum >= 0) {
							bool bDrawRet = drawer->Draw(canvasCtxB.m_PageNum, canvasCtxB);
							if (bDrawRet) {
								// Chage cavas's status
								canvasCtxB.m_DrawStatus = Canvas::KEndDraw;
								currCanvas->DoLock();
								currCanvas->SetCtxB(canvasCtxB);
								currCanvas->DoUnlock();
								// draw white background
								DWPageView* page = currCanvas->GetPage();
								if (nil != page) {
									page.needDrawSecPageBKGround = YES;
									CGRect rect = canvasCtxB.m_DestRect;
									NSValue* rectValue = [NSValue valueWithCGRect:rect];
									[page performSelectorOnMainThread:@selector(setNeedsDisplayInRectAsValue:) withObject:rectValue waitUntilDone:YES];		
								}
								
								m_DocumentRendering->FinishedDrawing(nCurrPage, currCanvas, currCanvas->GetCtxB());
							} else {
								currCanvas->DoLock();
								currCanvas->SetNeedRedrawStatus();
								currCanvas->DoUnlock();
								continue;
							}
						}
					} 
				} // end if (bNeedRedrawFlag) 
				[NSThread sleepForTimeInterval:0.1];
			} // end for (int i = 0; i < nDrawPageCount; i++)
		} else {
			[NSThread sleepForTimeInterval:0.1];
		} // end if
		[pool release];
	}// end while
}

@end
