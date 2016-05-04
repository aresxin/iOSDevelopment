/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	RND_DLEdgeSupport.h -- definition of Renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_DLEDGESUPPORT_H_INCLUDED
#define RND_DLEDGESUPPORT_H_INCLUDED

#include "RND_InternalDefine.h"
#include "CST_IF.h"


    
/* class definition */

typedef struct
{
    void 		*MI;
    long 		maxWidth;
    long 		maxHeight;
    long 		currentWidth;
    long 		currentHeight;
    RND_EdgeListCell  	*maskEL;
    RND_EdgeListCell  	*ELMemPool;
    RND_EdgeListCell  	*ELFreeList;
    long  		ELCount;
    COM_Edge 		*work;
    COM_Edge 		*target;
    long 		EC;
    long 		currentY;

} RND_DLEdgeSupport;


/* public method */

void* 		RND_DLEdgeSupport_New(void *MI, long maxWidth, long maxHeight);
void 		RND_DLEdgeSupport_Delete(void *handle);
RND_Error 	RND_DLEdgeSupport_StartPage(void *handle, long currentWidth, long currentHeight);
RND_Error 	RND_DLEdgeSupport_EndPage(void *handle);
RND_Error 	RND_DLEdgeSupport_StartLine(void *handle, COM_Edge *ptr);
RND_Error 	RND_DLEdgeSupport_ScanLine(void *handle, unsigned long color, unsigned long type, long sx, long ex);
RND_Error 	RND_DLEdgeSupport_EndLine(void *handle, long *edgeCount);

/* private method */

void RND_DLEdgeSupport_QSort(RND_DLEdgeSupport *self, COM_Edge *edge, long first, long last);
void RND_DLEdgeSupport_Connect(RND_DLEdgeSupport *self);
RND_EdgeListCell *RND_DLEdgeSupport_GetELCell(RND_DLEdgeSupport *self);
void RND_DLEdgeSupport_ReturnELCell(RND_DLEdgeSupport *self, RND_EdgeListCell *ptr);
void RND_DLEdgeSupport_ClearELCell(RND_DLEdgeSupport *self);

#endif 
