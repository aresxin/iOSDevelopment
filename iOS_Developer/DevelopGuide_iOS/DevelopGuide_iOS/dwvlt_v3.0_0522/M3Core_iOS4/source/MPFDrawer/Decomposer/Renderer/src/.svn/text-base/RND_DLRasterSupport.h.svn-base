/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	RND_DLRasterSupport.h -- definition of Renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_DLRASTERSUPPORT_H_INCLUDED
#define RND_DLRASTERSUPPORT_H_INCLUDED

#include "RND_DLDefine.h"
#include "RND_InternalDefine.h"
#include "CST_IF.h"


/* class definition */

typedef struct
{
    void 			*MI;
    void			*CST;
    long 			maxWidth;
    long 			maxHeight;
    long 			currentWidth;
    long 			currentHeight;
    unsigned char		*workBuffer;
    long			workBufferSize;
    unsigned char		*readBuffer;
    long			readBufferSize;
    unsigned char		*IEBuffer;
    long			IEBufferSize;
    unsigned char		*palletBuffer;
    long 			palletBufferSize;
    long			cp;
    long			IEcp;
    long			splitHeight;
    long			outputOrder[4];
    long			outputBytes;
    RND_DLImageExtend		*IEalloc;
    RND_DLImageExtend		*IEfree;
    FILE			*imageFP;

} RND_DLRasterSupport;
    

/* public method */

void* RND_DLRasterSupport_New(void *MI, long maxWidth, long maxHeight, void *CST);
void RND_DLRasterSupport_Delete(void *handle);
RND_Error RND_DLRasterSupport_StartPage(void *handle, long width, long height, long *order, long bytes, FILE *imageFP);
RND_Error RND_DLRasterSupport_EndPage(void *handle);
RND_Error RND_DLRasterSupport_LoadRaster(void *handle, RND_DLImage *DLI, long y, long tag, long order);
RND_Error RND_DLRasterSupport_LoadPattern(void *handle, RND_DLPattern *DLP, long tag, long order);
RND_Error RND_DLRasterSupport_UpdateRaster(void *handle, long y);


/* private method */

unsigned char *RND_DLRasterSupport_GetWork(RND_DLRasterSupport *p);
void RND_DLRasterSupport_ReturnWork(RND_DLRasterSupport *p, unsigned char *ptr);

unsigned char *RND_DLRasterSupport_MallocBuffer(RND_DLRasterSupport *self, long size);
void RND_DLRasterSupport_ClearBuffer(RND_DLRasterSupport *self);

RND_DLImageExtend *RND_DLRasterSupport_GetDLImageExtend(RND_DLRasterSupport *self);
void RND_DLRasterSupport_ReturnDLImageExtend(RND_DLRasterSupport *self, RND_DLImageExtend *ptr);


RND_Error RND_DLRasterSupport_ChangeOrder(RND_DLRasterSupport *self, 
					  CST_PixelBufferInfo *in, 
					  CST_PixelBufferInfo *out);

RND_Error RND_DLRasterSupport_ExpandPixel(RND_DLRasterSupport *self, 
					  long sBits, long dBytes, 
					  unsigned char *source, 
					  unsigned char *destination, 
					  long width, long height, 
					  unsigned char *pallet);

RND_Error RND_DLRasterSupport_ClipImage(RND_DLRasterSupport *self, 
					RND_DLImage *DLI);

RND_Error RND_DLRasterSupport_CalcReadLine(RND_DLRasterSupport *self, 
					   RND_DLImage *DLI, long y, 
					   long *startLine, 
					   long *endLine);

RND_Error RND_DLRasterSupport_LoadData(RND_DLRasterSupport *self, 
				       RND_DLImage *DLI, 
				       RND_DLImageExtend *IE, 
				       long startLine, long endLine, 
				       long outComponent);


#endif 
