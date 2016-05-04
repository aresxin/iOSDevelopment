/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_PageManager.h -- definition of Page Manager 

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef PM_PAGEMANAGER_H_INCLUDED
#define PM_PAGEMANAGER_H_INCLUDED

#include "PM_DeviceFigure.h"
#include "COM_DeviceColorSpace.h"

void* PM_New(void *arg1, void *arg2, void *arg3, long arg4, long arg5, long arg6, long arg7, long arg8);

#ifndef DOCUWORKS_VIEWER
long PM_StartPage(void *PM, long arg1, long arg2, long arg3, COM_DeviceColorSpace *pmParameter);
#else
long PM_StartPage(void *PM, long arg1, long arg2, long arg3, COM_DeviceColorSpace *pmParameter, 
		  unsigned char *pageBuffer, long lineSize, long depth, void *DC);
#endif

long PM_Delete(void *PM);
long PM_StartJob(void *PM);
long PM_EndJob(void *PM); 
long PM_GetPage(void *PM, void **arg1); 
long PM_EndPage(void *PM); 
long PM_InitClip(void *PM);
long PM_StartClip(void *PM, long arg1);
long PM_EndClip(void *PM);
long PM_OffsetClip(void *PM, long arg1, long arg2);
long PM_SaveClip(void *PM);
long PM_RestoreClip(void *PM);
long PM_CheckRectangleClip(void *PM, PM_FRectangle *arg1, long *arg2, PM_FEdge **arg3, long *arg4);
long PM_StartAttribute(void *PM, unsigned long arg1, unsigned long arg2, void* arg3, unsigned long arg4);
long PM_EndAttribute(void *PM);
long PM_DrawRectangle1(void *PM, PM_Rectangle *arg);
long PM_DrawRectangle2(void *PM, PM_Rectangle *arg);		
long PM_DrawTrapezoid1(void *PM, PM_Trapezoid *arg);
long PM_DrawTrapezoid2(void *PM, PM_Trapezoid *arg);
long PM_DrawEdge1(void *PM, PM_Edge *arg);	
long PM_DrawEdge2(void *PM, PM_Edge *arg);	
long PM_DrawVEdge1(void *PM, PM_VEdge *arg);	
long PM_DrawVEdge2(void *PM, PM_VEdge *arg);	
long PM_DrawLine(void *PM, PM_Line *arg);
long PM_DrawBitmap(void *PM, PM_Bitmap *arg);
long PM_DrawBitmapFont(void *PM, PM_BitmapFont *arg);
long PM_DrawEdgeFont(void *PM, PM_EdgeFont *arg);
long PM_DrawImageInfo(void *PM, PM_Image *arg);
long PM_DrawImageSet(void *PM);
long PM_DrawGrayMaskInfo(void *PM, PM_GrayMask *arg);
long PM_DrawGrayMaskSet(void *PM);
long PM_ExecFallback(void *PM);
long PM_GetMemSize(long arg1, long arg2);

#endif
