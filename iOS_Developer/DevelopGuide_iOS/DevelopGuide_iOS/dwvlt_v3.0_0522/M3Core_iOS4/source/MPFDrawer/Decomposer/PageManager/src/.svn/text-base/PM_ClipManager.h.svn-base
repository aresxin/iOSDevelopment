/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_ClipManager.h -- definition of Page Manager 

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef PM_CLIPMANAGER_H_INCLUDED
#define PM_CLIPMANAGER_H_INCLUDED

#include "PM_DeviceFigure.h"
#include "PM_InternalDefine.h"
#include "PM_ELMemoryManager.h"
#include "PM_PageGenerator.h"

typedef enum PM_ClipManager_ClipStatement
{
    PM_CLIP_STATEMENT_CLIP	= 0,
    PM_CLIP_STATEMENT_MAKE_AND	= 1,
    PM_CLIP_STATEMENT_MAKE_PUT	= 2,
    PM_CLIP_STATEMENT_MAKE_OR	= 3,
    PM_CLIP_STATEMENT_MAKE_DIFF	= 4,
    PM_CLIP_STATEMENT_MAKE_EXOR	= 5

} PM_ClipManager_ClipStatement;

typedef struct PM_ClipManager
{
    void				*MI;
    PM_ClipManager_ClipStatement	statement;
    long				maxpagewidth;
    long				maxpageheight;
    long				pagewidth;
    long				pageheight;
    void 				*output;
    PM_EdgeListCell			**clip_table;
    PM_EdgeListCell			**make_table;
    void				*make_ELM;
    void				*clip_ELM;
    long 				clip_rectcheck;
    long 				make_rectcheck;
    long				cux, cuy, clx, cly; 
    long				mux, muy, mlx, mly; 
    long				imagecheck;
    long				imageedgenum;
    PM_FEdge 				*imageedgeptr;
    PM_FEdge				**save;
    long				cursavelevel;
    long				maxsavelevel;
    
    PM_Error (*MakeELCell)(struct PM_ClipManager *p, long y, long sx, long ex);
    PM_Error (*MakeRect)(struct PM_ClipManager *p, long sx, long sy, long ex, long ey);

} PM_ClipManager;

/* constructer */

void* PM_ClipManager_New(void *MI, long maxpagewidth, long maxpageheight, long maxsavelevel, void *output);
PM_Error PM_ClipManager_Delete(void *handle);

/* public */
#ifndef DOCUWORKS_VIEWER
PM_Error PM_ClipManager_StartPage(void *handle, long pagewidth, long pageheight, long pagemode, COM_DeviceColorSpace *pmParameter);
#else
PM_Error PM_ClipManager_StartPage(void *handle, long pagewidth, long pageheight, long pagemode, COM_DeviceColorSpace *pmParameter, 
				  unsigned char *pageBuffer, long lineSize, long depth, void *DC);
#endif

PM_Error PM_ClipManager_GetPage(void *handle, void **dlinfo); 
PM_Error PM_ClipManager_EndPage(void *handle); 
PM_Error PM_ClipManager_InitClip(void *handle);
PM_Error PM_ClipManager_StartClip(void *handle, long mode);
PM_Error PM_ClipManager_EndClip(void *handle);
PM_Error PM_ClipManager_StartAttribute(void *handle, unsigned long mode, unsigned long color, void* pattern, unsigned long rop);
PM_Error PM_ClipManager_EndAttribute(void *handle);
PM_Error PM_ClipManager_DrawRectangle1(void *handle, PM_Rectangle *arg);
PM_Error PM_ClipManager_DrawRectangle2(void *handle, PM_Rectangle *arg);		
PM_Error PM_ClipManager_DrawTrapezoid1(void *handle, PM_Trapezoid *arg);
PM_Error PM_ClipManager_DrawTrapezoid2(void *handle, PM_Trapezoid *arg);
PM_Error PM_ClipManager_DrawEdge1(void *handle, PM_Edge *arg);	
PM_Error PM_ClipManager_DrawEdge2(void *handle, PM_Edge *arg);	
PM_Error PM_ClipManager_DrawVEdge1(void *handle, PM_VEdge *arg);	
PM_Error PM_ClipManager_DrawVEdge2(void *handle, PM_VEdge *arg);	
PM_Error PM_ClipManager_DrawLine(void *handle, PM_Line *arg);
PM_Error PM_ClipManager_DrawBitmap(void *handle, PM_Bitmap *arg);
PM_Error PM_ClipManager_DrawBitmapFont(void *handle, PM_BitmapFont *arg);
PM_Error PM_ClipManager_DrawEdgeFont(void *handle, PM_EdgeFont *arg);
PM_Error PM_ClipManager_DrawImageInfo(void *handle, PM_Image *arg);
PM_Error PM_ClipManager_DrawImageSet(void *handle);
PM_Error PM_ClipManager_DrawGrayMaskInfo(void *handle, PM_GrayMask *arg);
PM_Error PM_ClipManager_DrawGrayMaskSet(void *handle);
PM_Error PM_ClipManager_ExecFallback(void *handle);
PM_Error PM_ClipManager_SaveClip(void *handle);
PM_Error PM_ClipManager_RestoreClip(void *handle);
PM_Error PM_ClipManager_OffsetClip(void *handle, long offsetX, long offsetY);
PM_Error PM_ClipManager_CheckRectangleClip(void *handle, PM_FRectangle *src, long *ans, PM_FEdge **argEdgeArray, long *argNumEdge);

/* private */

PM_Error PM_ClipManager_MakeDrawRectangle1(PM_ClipManager *p, PM_Rectangle *arg);
PM_Error PM_ClipManager_MakeDrawRectangle2(PM_ClipManager *p, PM_Rectangle *arg);
PM_Error PM_ClipManager_MakeDrawTrapezoid1(PM_ClipManager *p, PM_Trapezoid *arg);
PM_Error PM_ClipManager_MakeDrawTrapezoid2(PM_ClipManager *p, PM_Trapezoid *arg);
PM_Error PM_ClipManager_MakeDrawEdge1(PM_ClipManager *p, PM_Edge *arg);
PM_Error PM_ClipManager_MakeDrawEdge2(PM_ClipManager *p, PM_Edge *arg);
PM_Error PM_ClipManager_MakeDrawVEdge1(PM_ClipManager *p, PM_VEdge *arg);
PM_Error PM_ClipManager_MakeDrawVEdge2(PM_ClipManager *p, PM_VEdge *arg);
PM_Error PM_ClipManager_MakeDrawLine(PM_ClipManager *p, PM_Line *arg);
PM_Error PM_ClipManager_MakeDrawBitmap(PM_ClipManager *p, PM_Bitmap *arg);
PM_Error PM_ClipManager_MakeDrawBitmapFont(PM_ClipManager *p, PM_BitmapFont *arg);
PM_Error PM_ClipManager_MakeDrawEdgeFont(PM_ClipManager *p, PM_EdgeFont *arg);
PM_Error PM_ClipManager_MakeDrawImageInfo(PM_ClipManager *p, PM_Image *arg);
PM_Error PM_ClipManager_MakeDrawImageSet(PM_ClipManager *p);
PM_Error PM_ClipManager_MakeDrawGrayMaskInfo(PM_ClipManager *p, PM_GrayMask *arg);
PM_Error PM_ClipManager_MakeDrawGrayMaskSet(PM_ClipManager *p);

PM_Error PM_ClipManager_ClipDrawRectangle1(PM_ClipManager *p, PM_Rectangle *arg);
PM_Error PM_ClipManager_ClipDrawRectangle2(PM_ClipManager *p, PM_Rectangle *arg);
PM_Error PM_ClipManager_ClipDrawTrapezoid1(PM_ClipManager *p, PM_Trapezoid *arg);
PM_Error PM_ClipManager_ClipDrawTrapezoid2(PM_ClipManager *p, PM_Trapezoid *arg);
PM_Error PM_ClipManager_ClipDrawEdge1(PM_ClipManager *p, PM_Edge *arg);
PM_Error PM_ClipManager_ClipDrawEdge2(PM_ClipManager *p, PM_Edge *arg);
PM_Error PM_ClipManager_ClipDrawVEdge1(PM_ClipManager *p, PM_VEdge *arg);
PM_Error PM_ClipManager_ClipDrawVEdge2(PM_ClipManager *p, PM_VEdge *arg);
PM_Error PM_ClipManager_ClipDrawLine(PM_ClipManager *p, PM_Line *arg);
PM_Error PM_ClipManager_ClipDrawBitmap(PM_ClipManager *p, PM_Bitmap *arg);
PM_Error PM_ClipManager_ClipDrawBitmapFont(PM_ClipManager *p, PM_BitmapFont *arg);
PM_Error PM_ClipManager_ClipDrawEdgeFont(PM_ClipManager *p, PM_EdgeFont *arg);
PM_Error PM_ClipManager_ClipDrawImageInfo(PM_ClipManager *p, PM_Image *arg);
PM_Error PM_ClipManager_ClipDrawImageSet(PM_ClipManager *p);
PM_Error PM_ClipManager_ClipDrawGrayMaskInfo(PM_ClipManager *p, PM_GrayMask *arg);
PM_Error PM_ClipManager_ClipDrawGrayMaskSet(PM_ClipManager *p);

PM_Error PM_ClipManager_AndELCell(PM_ClipManager *p, long y, long sx, long ex);
PM_Error PM_ClipManager_AndRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
PM_Error PM_ClipManager_AddELCell(PM_ClipManager *p, long y, long sx, long ex);
PM_Error PM_ClipManager_AddRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
PM_Error PM_ClipManager_SubELCell(PM_ClipManager *p, long y, long sx, long ex);
PM_Error PM_ClipManager_SubRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
PM_Error PM_ClipManager_ExorELCell(PM_ClipManager *p, long y, long sx, long ex);
PM_Error PM_ClipManager_ExorRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
PM_Error PM_ClipManager_ClipELCell(PM_ClipManager *p, long y, long sx, long ex);
PM_Error PM_ClipManager_ClipELCellImage(PM_ClipManager *p, long lx, long ly, long ux, long uy, PM_FEdge **ptr, long *num);
PM_Error PM_ClipManager_ConnectClipELCell(PM_ClipManager *p);
PM_Error PM_ClipManager_ConnectMakeELCell(PM_ClipManager *p);
PM_Error PM_ClipManager_SwapClipTable(PM_ClipManager *p);

void PM_ClipManager_SetClipRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
void PM_ClipManager_GetClipRect(PM_ClipManager *p, long *lx, long *ly, long *ux, long *uy);
void PM_ClipManager_SetMakeRect(PM_ClipManager *p, long lx, long ly, long ux, long uy);
void PM_ClipManager_GetMakeRect(PM_ClipManager *p, long *lx, long *ly, long *ux, long *uy);
long PM_ClipManager_GetClipRectCheck(PM_ClipManager *p);
void PM_ClipManager_SetClipRectCheck(PM_ClipManager *p);
void PM_ClipManager_ResetClipRectCheck(PM_ClipManager *p);
long PM_ClipManager_GetMakeRectCheck(PM_ClipManager *p);
void PM_ClipManager_SetMakeRectCheck(PM_ClipManager *p);
void PM_ClipManager_ResetMakeRectCheck(PM_ClipManager *p);
long PM_ClipManager_ClearClipTable(PM_ClipManager *p);
long PM_ClipManager_ClearMakeTable(PM_ClipManager *p);
long PM_ClipManager_OffsetClipTable(PM_ClipManager *p, long offsetX, long offsetY);
long PM_ClipManager_OffsetMakeTable(PM_ClipManager *p, long offsetX, long offsetY);
PM_EdgeListCell* PM_ClipManager_GetMakeELCell(PM_ClipManager *p);		
PM_EdgeListCell* PM_ClipManager_GetClipELCell(PM_ClipManager *p);		
void PM_ClipManager_ReturnMakeELCell(PM_ClipManager *p, PM_EdgeListCell* el);
void PM_ClipManager_ReturnClipELCell(PM_ClipManager *p, PM_EdgeListCell* el);
void PM_ClipManager_ClearMakeELCell(PM_ClipManager *p);
void PM_ClipManager_ClearClipELCell(PM_ClipManager *p);
int PM_ClipManager_GetMakeCellNum(PM_ClipManager *p);
int PM_ClipManager_GetClipCellNum(PM_ClipManager *p);

void PM_ClipManager_Print(PM_ClipManager *p);

#endif
