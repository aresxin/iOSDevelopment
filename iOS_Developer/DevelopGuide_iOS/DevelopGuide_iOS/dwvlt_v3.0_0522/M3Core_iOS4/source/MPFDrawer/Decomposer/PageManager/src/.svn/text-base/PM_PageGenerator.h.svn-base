/*
      Copyright (C) Fuji Xerox Co; Ltd. 2001. All rights reserved.

      PM_PageGenerator.h -- definition of Page Manager 


      Created:        Feb 23, 2001 By Kunihiko Kobayashi
      Modified:
*/

#ifndef PM_PAGEGENERATOR_H_INCLUDED
#define PM_PAGEGENERATOR_H_INCLUDED

#include "PM_InternalDefine.h"
#include "PM_DeviceFigure.h"


typedef struct PM_PageGenerator
{
    PM_GeneratorType 	type;
    void		*handle;

} PM_PageGenerator;


void* PM_PageGenerator_New(void *MI, void *RND, void *ESS, long maxwidth, long maxheight, PM_GeneratorType type);

#ifndef DOCUWORKS_VIEWER
PM_Error PM_PageGenerator_StartPage(void *handle, long arg1, long arg2, long arg3, COM_DeviceColorSpace *pmParameter);
#else
PM_Error PM_PageGenerator_StartPage(void *handle, long arg1, long arg2, long arg3, COM_DeviceColorSpace *pmParameter,
				    unsigned char *pageBuffer, long lineSize, long depth, void *DC);
#endif

PM_Error PM_PageGenerator_Delete(void *handle);
PM_Error PM_PageGenerator_StartJob(void *handle);
PM_Error PM_PageGenerator_EndJob(void *handle); 
PM_Error PM_PageGenerator_GetPage(void *handle, void **arg1); 
PM_Error PM_PageGenerator_EndPage(void *handle); 
PM_Error PM_PageGenerator_ExecFallback(void *handle); 
PM_Error PM_PageGenerator_StartAttribute(void *handle, unsigned long arg1, unsigned long arg2, void* arg3, unsigned long arg4);
PM_Error PM_PageGenerator_EndAttribute(void *handle);
PM_Error PM_PageGenerator_DrawRectangle1(void *handle, PM_Rectangle *arg);
PM_Error PM_PageGenerator_DrawRectangle2(void *handle, PM_Rectangle *arg);
PM_Error PM_PageGenerator_DrawFRectangle(void *handle, PM_FRectangle *arg);
PM_Error PM_PageGenerator_DrawTrapezoid1(void *handle, PM_Trapezoid *arg);
PM_Error PM_PageGenerator_DrawTrapezoid2(void *handle, PM_Trapezoid *arg);
PM_Error PM_PageGenerator_DrawEdge1(void *handle, PM_Edge *arg);
PM_Error PM_PageGenerator_DrawEdge2(void *handle, PM_Edge *arg);
PM_Error PM_PageGenerator_DrawVEdge1(void *handle, PM_VEdge *arg);
PM_Error PM_PageGenerator_DrawVEdge2(void *handle, PM_VEdge *arg);
PM_Error PM_PageGenerator_DrawFixedEdge(void *handle, PM_FEdge *arg);
PM_Error PM_PageGenerator_DrawFixedVEdge(void *handle, PM_FVEdge *arg);
PM_Error PM_PageGenerator_DrawLine(void *handle, PM_Line *arg);
PM_Error PM_PageGenerator_DrawBitmap(void *handle, PM_Bitmap *arg);
PM_Error PM_PageGenerator_DrawBitmapFont(void *handle, PM_BitmapFont *arg);
PM_Error PM_PageGenerator_DrawEdgeFont(void *handle, PM_EdgeFont *arg);
PM_Error PM_PageGenerator_DrawImageInfo(void *handle, PM_Image *arg);
PM_Error PM_PageGenerator_DrawImageSet(void *handle, PM_FEdge *arg1, long arg2);
PM_Error PM_PageGenerator_DrawGrayMaskInfo(void *handle, PM_GrayMask *arg);
PM_Error PM_PageGenerator_DrawGrayMaskSet(void *handle, PM_FEdge *arg1, long arg2);


#endif
