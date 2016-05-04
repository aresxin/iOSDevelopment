//
//  DWDrawer.h
//  DWViewer
//
//  Created by tongjo on 10-12-5.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/QuartzCore.h>
#import "GraphicDrawer.h"

@interface DWDrawer : NSObject {
	GraphicDrawer* drawer;
	NSLock* drawingLock;
	BOOL bContinue;
}

- (id) initWithDocumentHandle:(DocumentHandle*)docHandle;
- (void) drawWithCtx:(GraphicDrawer::CavansCtx&)canvasCtx;
- (void) breakDrawing;
// 2011/10/05 M.Chikyu (AR18595) start
- (void) resetDrawing;
// 2011/10/05 M.Chikyu (AR18595) end

@end

@interface DWLayer : CATiledLayer {

}
@property (nonatomic, retain)DWDrawer* drawer;

@end