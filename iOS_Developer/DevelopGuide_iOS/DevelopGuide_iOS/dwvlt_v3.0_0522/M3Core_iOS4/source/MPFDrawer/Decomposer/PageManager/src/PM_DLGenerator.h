/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_DLGenerator.h -- definition of Page Manager 

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef PM_DLGENERATOR_H_INCLUDED
#define PM_DLGENERATOR_H_INCLUDED

#include "PM_DeviceFigure.h"
#include "PM_InternalDefine.h"
#include "PM_DLDefine.h"
#include "PM_DLMemoryManager.h"
#include "PM_DLRasterManager.h"
#include "PM_PageGenerator.h"


typedef enum PM_DLGenerator_IELStatement
{
    PM_DLGENERATOR_IELSTATEMENT_IEL	= 0,
    PM_DLGENERATOR_IELSTATEMENT_EL	= 1

} PM_DLGenerator_IELStatement;

typedef struct
{
    PM_DisplayListCell 		*topCell;
    PM_DisplayListCell 		*endCell;
    unsigned char 		*currentBuffer;
    long 			bufferSize;
    long 			cp;			
    long 			sp;			
    long			cn;			
    long 			psx;			
    long 			pex;			
    long 			py;			
    long 			pdx;			
    long 			pdy;			
    long 			prun;			
    long			rep;

} PM_DLGenerator_MemInfo;

typedef struct
{
    unsigned char 	rasterFlag;
    unsigned char	ropMode;
    unsigned char	ropCode;
    unsigned long	tag;
    PM_DLImage		*image;
    PM_DLPattern	*pattern;
    union {
	unsigned long 	value;
	unsigned char	comp[4];
	void 	  	*ptr;
    }color;

} PM_DLGenerator_Mode;

typedef struct PM_DLGenerator
{
    void			*MI;
    void			*RND;
    void			*ESS;
    void 			*DLMM;
    PM_DLRasterManager		*DLRM;
    long			maxWidth;
    long			maxHeight;
    PM_DLGenerator_Mode		drawMode;			
    PM_DLGenerator_MemInfo	memInfo;
    unsigned long		objectID;
    long 			pageNumber;
    PM_PageInfo			*pageInfo;
    PM_DLData			*DLData;
    PM_Pattern			dummyPattern;
    unsigned char		dummyPatternData[64];
    long			ELMax;
    long			ELMin;
    long			ELCount;
    PM_EdgeListCell  		*ELPool;
    PM_EdgeListCell  		**ELTable;
    PM_DLGenerator_IELStatement	IELStatement;

} PM_DLGenerator;


    
/** public **/

void* PM_DLGenerator_New(void *MI, void *RND, void *ESS, long maxwidth, long maxheight, PM_GeneratorType type);
PM_Error PM_DLGenerator_Delete(void *handle);
PM_Error PM_DLGenerator_StartPage(void *handle, long width, long height, long mode, COM_DeviceColorSpace *pmParameter);
PM_Error PM_DLGenerator_GetPage(void *handle, void **dlinfo); 
PM_Error PM_DLGenerator_EndPage(void *handle); 
PM_Error PM_DLGenerator_ExecFallback(void *handle); 
PM_Error PM_DLGenerator_StartAttribute(void *handle, unsigned long mode, unsigned long color, void *pattern, unsigned long rop);
PM_Error PM_DLGenerator_EndAttribute(void *handle);
PM_Error PM_DLGenerator_DrawRectangle1(void *handle, PM_Rectangle *arg);
PM_Error PM_DLGenerator_DrawRectangle2(void *handle, PM_Rectangle *arg);		
PM_Error PM_DLGenerator_DrawFRectangle(void *handle, PM_FRectangle *arg);		
PM_Error PM_DLGenerator_DrawTrapezoid1(void *handle, PM_Trapezoid *arg);
PM_Error PM_DLGenerator_DrawTrapezoid2(void *handle, PM_Trapezoid *arg);
PM_Error PM_DLGenerator_DrawEdge1(void *handle, PM_Edge *arg);	
PM_Error PM_DLGenerator_DrawEdge2(void *handle, PM_Edge *arg);	
PM_Error PM_DLGenerator_DrawVEdge1(void *handle, PM_VEdge *arg);	
PM_Error PM_DLGenerator_DrawVEdge2(void *handle, PM_VEdge *arg);	
PM_Error PM_DLGenerator_DrawFixedEdge(void *handle, PM_FEdge *arg);	
PM_Error PM_DLGenerator_DrawFixedVEdge(void *handle, PM_FVEdge *arg);	
PM_Error PM_DLGenerator_DrawLine(void *handle, PM_Line *arg);
PM_Error PM_DLGenerator_DrawBitmap(void *handle, PM_Bitmap *arg);	
PM_Error PM_DLGenerator_DrawBitmapFont(void *handle, PM_BitmapFont *arg);
PM_Error PM_DLGenerator_DrawEdgeFont(void *handle, PM_EdgeFont *arg);
PM_Error PM_DLGenerator_DrawImageInfo(void *handle, PM_Image *arg);
PM_Error PM_DLGenerator_DrawImageSet(void *handle, PM_FEdge *arg1, long arg2);
PM_Error PM_DLGenerator_DrawGrayMaskInfo(void *handle, PM_GrayMask *arg);
PM_Error PM_DLGenerator_DrawGrayMaskSet(void *handle, PM_FEdge *arg1, long arg2);

/** private **/

PM_Error PM_DLGenerator_InitStoreIEL(PM_DLGenerator *self);
PM_Error PM_DLGenerator_SetStoreIEL(PM_DLGenerator *self, long number);
PM_Error PM_DLGenerator_ResetStoreIEL(PM_DLGenerator *self);
PM_Error PM_DLGenerator_StoreIEL(PM_DLGenerator *self, long y, long sx, long ex);
PM_Error PM_DLGenerator_StoreIEL1(PM_DLGenerator *self, long y, long sx, long ex);
PM_Error PM_DLGenerator_StoreIEL2(PM_DLGenerator *self, long y, long sx, long ex);
PM_Error PM_DLGenerator_StoreEdge(PM_DLGenerator *self, long y, long sx, long ex);
PM_Error PM_DLGenerator_StoreLine(PM_DLGenerator *self, long y, float x, float s, long h);
PM_Error PM_DLGenerator_StoreRectangle(PM_DLGenerator *self, long y, long sx, long ex, long h);
PM_Error PM_DLGenerator_StoreTrapezoid1(PM_DLGenerator *self, long y, float lx, float ux, float ls, float us, long h);
PM_Error PM_DLGenerator_StoreTrapezoid2(PM_DLGenerator *self, long y, float lx, float ux, float ls, float us, long h);

PM_Error PM_DLGenerator_Extend(PM_DLGenerator *self);
PM_Error PM_DLGenerator_ExecFallbackInternal(PM_DLGenerator *self);
unsigned long PM_DLGenerator_GetInformation(PM_DLGenerator *self, unsigned long shape, unsigned long ID);


#endif
