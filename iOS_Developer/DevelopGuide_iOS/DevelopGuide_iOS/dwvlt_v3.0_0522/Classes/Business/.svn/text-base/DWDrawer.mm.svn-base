//
//  DWDrawer.mm
//  DWViewer
//
//  Created by tongjo on 10-12-5.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DWDrawer.h"


@implementation DWDrawer
- (id) initWithDocumentHandle:(DocumentHandle*)docHandle
{
	if ([super init] != nil)
	{
		if (docHandle != NULL)
		{
			drawer = new GraphicDrawer(docHandle);
			
			// 2012.02.01(Ver2.1 New) M.Chikyu
			if (drawer->IsDrawingLockUsed() == true)
			{
				drawingLock = [[NSLock alloc]init];
			}
			else
			{
				drawingLock = nil;
			}
			// 2012.02.01(Ver2.1 New) M.Chikyu
		}
		
		bContinue = YES;
	}
	
	return self;
}

- (void) drawWithCtx:(GraphicDrawer::CavansCtx&)canvasCtx
{
	if (drawer != NULL)
	{
		if (drawingLock != nil)
		{
			[drawingLock lock];
		}
		
		if (bContinue)
		{
			drawer->Draw(canvasCtx);
		}
		
		if (drawingLock != nil)
		{
			[drawingLock unlock];
		}
	}
}

- (void) breakDrawing
{
	if (drawer != NULL)
	{
		drawer->BreakDrawing();
	}
	
	if (drawingLock != nil)
	{
		[drawingLock lock];
		bContinue = NO;
		[drawingLock unlock];
	}
}

// 2011/10/05 M.Chikyu (AR18595) start

- (void) resetDrawing
{
	if (drawingLock != nil)
	{
		[drawingLock lock];
		
		bContinue = YES;
		
		if (drawer != NULL)
		{
			drawer->ResetDrawing();
		}
		
		[drawingLock unlock];
	}
}

// 2011/10/05 M.Chikyu (AR18595) end

- (void) dealloc
{
	if (drawer != NULL)
	{
		delete drawer;
		drawer = NULL;
	}
	
	if (drawingLock != nil)
	{
		[drawingLock release];
		drawingLock = nil;
	}
	
    [super dealloc];
}

@end

@implementation DWLayer

@synthesize drawer;

- (void) dealloc
{
	if (drawer != NULL)
	{
		[drawer release];
		drawer = NULL;
	}
	
    [super dealloc];
}

@end
