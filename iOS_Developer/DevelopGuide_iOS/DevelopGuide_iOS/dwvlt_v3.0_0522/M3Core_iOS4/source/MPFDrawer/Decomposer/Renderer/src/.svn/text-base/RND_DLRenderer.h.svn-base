/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	RND_DLRenderer.h -- definition of Renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_DLRENDERER_H_INCLUDED
#define RND_DLRENDERER_H_INCLUDED

#include "RND_InternalDefine.h"
#include "RND_DLDefine.h"
#include "RND_DLEdgeSupport.h"
#include "RND_DLRasterSupport.h"
#include "RND_DLObjectCheck.h"
#include "RND_PageRenderer.h"
#include "CST_IF.h"



/* class definition */

typedef struct RND_DLRenderer
{
    void			*MI;
    void 			*ES;
    void 			*RS;
    void 			*OC;
    void			*ESS;
    void 			*CST;
    COM_EdgeLine		*workLine[2];
    unsigned char		*tagBuffer;
    unsigned char		*workBuffer;
    unsigned char		*ropBuffer[3];
    long			maxWidth;
    long			maxHeight;
    long			currentWidth;
    long			currentHeight;
    long			order[4];
    long			orderSame;
    unsigned long		tagMaskR[32];
    unsigned long		tagMaskL[32];
    unsigned long		tagMaskT[16];
    unsigned long		tagBitMask;
    long			tagBitSize;
    long			tagTileSize;
    long			tagNumPixelsInTile;
    long			tagNumPixelsInByte;
    long			tagNum;
    long			colorMask;
    long			colorMaskDL;
    long			colorMaskOUT;
    ES_DistributorTarget	target;
    COM_OutputLocation		prerendered;
    COM_OutputLocation		output;
    COM_DeviceColorSpace	outputColor;
    COM_DeviceColorSpace	DLColorConstant;
    COM_DeviceColorSpace	DLColorImage;
    COM_Edge			backgroundDL;
    COM_Edge			backgroundOUT;
    long			imageExpandCheck;
    unsigned char		ropTransferTable[16];
    long			ropTransferFlag;
    long			fallbackFlag;
    COM_OutputLocation		FD;

    
    RND_Error (*PaintImage)(struct RND_DLRenderer *self, 
			    void *color, long y, long sx, long ex, 
			    unsigned char *buffer, long tag);
    
    RND_Error (*PaintPattern)(struct RND_DLRenderer *self, 
			      void *color, long y, long sx, long ex, 
			      unsigned char *buffer, long tag);
    
    RND_Error (*PaintConstant)(struct RND_DLRenderer *self, 
			       unsigned long color, long y, long sx, long ex, 
			       unsigned char *buffer, long tag);

}RND_DLRenderer;



/* public method */

void* RND_DLRenderer_New(void *MI, long ResolutionX, long ResolutionY, long maxPageX, long maxPageY, void *CSTparameter);
RND_Error RND_DLRenderer_Delete(void *handle);
RND_Error RND_DLRenderer_ShowPage(void *handle, void *ESS, unsigned char *work, long size, void *DLInfo, 
				  COM_DeviceColorSpace *DCS, void *CSTparameter, COM_OutputLocation *FD);
RND_Error RND_DLRenderer_StartJob(void *handle);
RND_Error RND_DLRenderer_EndJob(void *handle);



/*private method */

RND_Error RND_DLRenderer_RenderPage(RND_DLRenderer *self, RND_DLHeader **displayList, char *rasterFlag, void *CST);
RND_Error RND_DLRenderer_RenderPageROP(RND_DLRenderer *self, RND_DLHeader **displayList, char *rasterFlag, void *CST);

RND_Error RND_DLRenderer_RenderListEdge(RND_DLRenderer *self, long y, RND_DLHeader **list, COM_EdgeLine *edgeLine, long ropFlag, long CSTFlag);
RND_Error RND_DLRenderer_RenderListRaster(RND_DLRenderer *self, long y, RND_DLHeader **list, COM_EdgeLine *edgeLine, long ropFlag, long CSTFlag);

RND_Error RND_DLRenderer_UpdateList1(RND_DLRenderer *self, long y, RND_DLHeader **currentList, RND_DLHeader **nextList, void *CST, long order);
RND_Error RND_DLRenderer_UpdateList2(RND_DLRenderer *self, long y, RND_DLHeader **currentList, RND_DLHeader **nextList, void *CST, long order);
RND_Error RND_DLRenderer_ReverseList(RND_DLRenderer * self, RND_DLHeader **list);
RND_Error RND_DLRenderer_TransList(RND_DLRenderer *self, long y, RND_DLHeader *list, void *CST, long order);

RND_Error RND_DLRenderer_CheckEdgeLine(RND_DLRenderer *self, COM_EdgeLine *edgeLine, long *preRenderdFlag);
RND_Error RND_DLRenderer_MergeEdgeLine(RND_DLRenderer *self, COM_EdgeLine *edgeLine0, COM_EdgeLine *edgeLine1, COM_EdgeLine *workLine, long component);
RND_Error RND_DLRenderer_ExtendEdgeLine(RND_DLRenderer *self, COM_EdgeLine *edgeLine, long component);
RND_Error RND_DLRenderer_TransEdgeLine(RND_DLRenderer *self, COM_EdgeLine *edgeLine, void *CST);

RND_Error RND_DLRenderer_EdgeIEL(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end);
RND_Error RND_DLRenderer_EdgeLine(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end);
RND_Error RND_DLRenderer_EdgeRectangle(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end);
RND_Error RND_DLRenderer_EdgeTrapezoid1(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end);
RND_Error RND_DLRenderer_EdgeTrapezoid2(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end);
RND_Error RND_DLRenderer_EdgePattern(RND_DLRenderer * self, void *color, long y, long sx, long ex, long tag);

RND_Error RND_DLRenderer_RasterIEL(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end, unsigned char *buffer);
RND_Error RND_DLRenderer_RasterLine(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end, unsigned char *buffer);
RND_Error RND_DLRenderer_RasterRectangle(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end, unsigned char *buffer);
RND_Error RND_DLRenderer_RasterTrapezoid1(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end, unsigned char *buffer);
RND_Error RND_DLRenderer_RasterTrapezoid2(RND_DLRenderer *self, long y, RND_DLHeader *H, long *end, unsigned char *buffer);

RND_Error RND_DLRenderer_SetTagInfo(RND_DLRenderer *self);
RND_Error RND_DLRenderer_SetColorInfo(RND_DLRenderer *self, COM_DeviceColorSpace *dcs);
RND_Error RND_DLRenderer_DivideEdge(RND_DLRenderer *self, COM_EdgeLine *edgeLine, long component);
RND_Error RND_DLRenderer_ChangeOrder(RND_DLRenderer *self, CST_PixelBufferInfo *in, CST_PixelBufferInfo *out);
RND_Error RND_DLRenderer_SetBackGroundColor(RND_DLRenderer *self, void *CST);

/* paint functions */

RND_Error RND_DLRenderer_PaintConstant44(RND_DLRenderer *self, unsigned long color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintImage44(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintPattern44(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);

RND_Error RND_DLRenderer_PaintConstant43(RND_DLRenderer *self, unsigned long color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintImage43(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintPattern43(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);

RND_Error RND_DLRenderer_PaintConstant43R(RND_DLRenderer *self, unsigned long color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintImage43R(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintPattern43R(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);

RND_Error RND_DLRenderer_PaintROP24(RND_DLRenderer *self, long RUN, unsigned long *D, unsigned long *S, unsigned char CODE);
RND_Error RND_DLRenderer_PaintROP34(RND_DLRenderer *self, long RUN, unsigned long *D, unsigned long *S, unsigned long *P, unsigned char CODE);
RND_Error RND_DLRenderer_PaintTagChange4(RND_DLRenderer *self, long sx, long ex, long tag, 
					 unsigned long *OD, unsigned long *ND, unsigned long *S, unsigned long *P, unsigned char CODE);
					
RND_Error RND_DLRenderer_PaintConstant11(RND_DLRenderer *self, unsigned long color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintImage11(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintPattern11(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);

RND_Error RND_DLRenderer_PaintConstant11R(RND_DLRenderer *self, unsigned long color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintImage11R(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);
RND_Error RND_DLRenderer_PaintPattern11R(RND_DLRenderer *self, void* color, long y, long sx, long ex, unsigned char *buffer, long tag);

RND_Error RND_DLRenderer_PaintROP21(RND_DLRenderer *self, long RUN, unsigned char *D, unsigned char *S, unsigned char CODE);
RND_Error RND_DLRenderer_PaintROP31(RND_DLRenderer *self, long RUN, unsigned char *D, unsigned char *S, unsigned char *P, unsigned char CODE);
RND_Error RND_DLRenderer_PaintTagChange1(RND_DLRenderer *self, long sx, long ex, long tag, 
					 unsigned char *OD, unsigned char *ND, unsigned char *S, unsigned char *P, unsigned char CODE);


RND_Error RND_DLRenderer_PaintTagPut(RND_DLRenderer *self, long sx, long ex, long tag);
RND_Error RND_DLRenderer_PaintTagExor(RND_DLRenderer *self, long sx, long ex, long tag);



#endif
