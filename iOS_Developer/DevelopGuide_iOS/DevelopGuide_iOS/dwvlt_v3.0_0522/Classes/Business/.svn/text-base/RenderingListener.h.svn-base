/*
 *  RenderingListener.h
 *  DWViewer
 *
 *  Created by tongjo on 10-11-1.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#import "Canvas.h"
class RenderingListener
{
public:
	virtual void FinishedDrawing(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx) = 0;
};

class DrawingListener : public RenderingListener

{
public:
	virtual void FinishedDrawing(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx);
private:
	// finished whole page
	virtual void FinishedOnePage(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx);
	// finished whold page, but dest is a rect.
	virtual void FinishedRect(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx);
	
	// finished offscreen
	virtual void FinishedOffscreen(int nPageNum, Canvas *canvas, const Canvas::CANVAS_CTX ctx);
};