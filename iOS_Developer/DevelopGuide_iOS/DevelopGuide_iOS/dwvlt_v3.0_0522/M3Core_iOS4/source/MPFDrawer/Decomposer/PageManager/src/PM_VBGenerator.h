/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_VBGenerator.h -- definition of Page Manager 

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef PM_VBGENERATOR_H_INCLUDED
#define PM_VBGENERATOR_H_INCLUDED

#include "PM_DeviceFigure.h"
#include "PM_InternalDefine.h"
#include "PM_PageGenerator.h"
#include "PM_VBDefine.h"
#include "PM_VBRasterManager.h"


typedef struct PM_VBGenerator
{
    void			*MI;
    void			*RND;
    long			maxWidth;
    long			maxHeight;
    long 			numOfPage;
    PM_PageInfo			*pageInfo;
    PM_Pattern			dummyPattern;
    unsigned char		dummyPatternData[64];
    unsigned char		*pageBuffer;
    unsigned char		*workBuffer[2];
    long			lineSize;
    PM_VBMode			drawMode;			
    PM_VBRasterManager		*rasterManager;			
    long			GrayMaskFlag;

    PM_Error 			(*PaintEdge)(struct PM_VBGenerator *self, 
					     long y, long sx, long ex, 
					     unsigned char *lineBuffer);

} PM_VBGenerator;


    
/** public **/

void* PM_VBGenerator_New(void *MI, void *RND, void *ESS, long maxwidth, long maxheight, PM_GeneratorType type);
PM_Error PM_VBGenerator_Delete(void *handle);

#ifndef DOCUWORKS_VIEWER
PM_Error PM_VBGenerator_StartPage(void *handle, long width, long height, long mode, COM_DeviceColorSpace *pmParameter);
#else
PM_Error PM_VBGenerator_StartPage(void *handle, long currentWidth, long currentHeight, long colorType, COM_DeviceColorSpace *pmParameter,
									unsigned char *pageBuffer, long lineSize, long depth, void *DC);
#endif

PM_Error PM_VBGenerator_Delete(void *handle);
PM_Error PM_VBGenerator_GetPage(void *handle, void **dlinfo); 
PM_Error PM_VBGenerator_EndPage(void *handle); 
PM_Error PM_VBGenerator_ExecFallback(void *handle); 
PM_Error PM_VBGenerator_StartAttribute(void *handle, unsigned long mode, unsigned long color, void *pattern, unsigned long rop);
PM_Error PM_VBGenerator_EndAttribute(void *handle);
PM_Error PM_VBGenerator_DrawRectangle1(void *handle, PM_Rectangle *arg);
PM_Error PM_VBGenerator_DrawRectangle2(void *handle, PM_Rectangle *arg);		
PM_Error PM_VBGenerator_DrawFRectangle(void *handle, PM_FRectangle *arg);		
PM_Error PM_VBGenerator_DrawTrapezoid1(void *handle, PM_Trapezoid *arg);
PM_Error PM_VBGenerator_DrawTrapezoid2(void *handle, PM_Trapezoid *arg);
PM_Error PM_VBGenerator_DrawEdge1(void *handle, PM_Edge *arg);	
PM_Error PM_VBGenerator_DrawEdge2(void *handle, PM_Edge *arg);	
PM_Error PM_VBGenerator_DrawVEdge1(void *handle, PM_VEdge *arg);	
PM_Error PM_VBGenerator_DrawVEdge2(void *handle, PM_VEdge *arg);	
PM_Error PM_VBGenerator_DrawFixedEdge(void *handle, PM_FEdge *arg);	
PM_Error PM_VBGenerator_DrawFixedVEdge(void *handle, PM_FVEdge *arg);	
PM_Error PM_VBGenerator_DrawLine(void *handle, PM_Line *arg);
PM_Error PM_VBGenerator_DrawBitmap(void *handle, PM_Bitmap *arg);	
PM_Error PM_VBGenerator_DrawBitmapFont(void *handle, PM_BitmapFont *arg);
PM_Error PM_VBGenerator_DrawEdgeFont(void *handle, PM_EdgeFont *arg);
PM_Error PM_VBGenerator_DrawImageInfo(void *handle, PM_Image *arg);
PM_Error PM_VBGenerator_DrawImageSet(void *handle, PM_FEdge *arg1, long arg2);
PM_Error PM_VBGenerator_DrawGrayMaskInfo(void *handle, PM_GrayMask *arg);
PM_Error PM_VBGenerator_DrawGrayMaskSet(void *handle, PM_FEdge *arg1, long arg2);

/** private **/

PM_Error PM_VBGenerator_SetPaintFunction(PM_VBGenerator *self);

PM_Error PM_VBGenerator_PaintConstant44(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintImage44(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintGrayMask44(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintPattern44(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintConstant44R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintImage44R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintGrayMask44R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintPattern44R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintROP2C4(PM_VBGenerator *self, long SX, long EX, unsigned long *D, unsigned long *S, unsigned char CODE);
PM_Error PM_VBGenerator_PaintROP3C4(PM_VBGenerator *self, long SX, long EX, unsigned long *D, unsigned long *S, unsigned long *P, unsigned char CODE);

PM_Error PM_VBGenerator_PaintConstant33(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintImage33(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintGrayMask33(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintPattern33(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintConstant33R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintImage33R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintGrayMask33R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintPattern33R(PM_VBGenerator *self, long y, long sx, long ex, unsigned char *lineBuffer);
PM_Error PM_VBGenerator_PaintROP2C3(PM_VBGenerator *self, long SX, long EX, unsigned char *D, unsigned char *S, unsigned char CODE);
PM_Error PM_VBGenerator_PaintROP3C3(PM_VBGenerator *self, long SX, long EX, unsigned char *D, unsigned char *S, unsigned char *P, unsigned char CODE);

#endif
