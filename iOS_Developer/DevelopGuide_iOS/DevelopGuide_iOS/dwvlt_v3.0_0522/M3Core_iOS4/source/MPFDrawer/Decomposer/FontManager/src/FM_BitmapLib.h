/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_BitmapLib.h -- definition of Font Manager 

	Created:	Oct 04, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_BITMAPLIB

#ifndef _FM_BITMAPLIB_H_INCLUDED_
#define _FM_BITMAPLIB_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "MI_MemoryInterface.h"

typedef struct {
  void 		*MI;
} FM_BitmapLib;


/* public */

FM_BitmapLib* 	FM_BitmapLib_New(void *MI);
void 		FM_BitmapLib_Delete(FM_BitmapLib *handle);

long		FM_BitmapLib_Realize(FM_BitmapLib *handle, FM_BitmapFont *dstBitmapFont, FM_BitmapFont *srcBitmapFont, FM_Matrix *matrix);

/* private */

long		FM_BitmapLib_Scale(FM_BitmapLib *handle, FM_BitmapFont *dstBitmapFont, FM_BitmapFont *srcBitmapFont, double srcRateX, double srcRateY);
long		FM_BitmapLib_Rotate90(FM_BitmapLib *handle, FM_BitmapFont *dstBitmapFont, FM_BitmapFont *srcBitmapFont);
long		FM_BitmapLib_Rotate180(FM_BitmapLib *handle, FM_BitmapFont *dstBitmapFont, FM_BitmapFont *srcBitmapFont);
long		FM_BitmapLib_Rotate270(FM_BitmapLib *handle, FM_BitmapFont *dstBitmapFont, FM_BitmapFont *srcBitmapFont);
long 		FM_BitmapLib_CheckMatrix(FM_BitmapLib *handle, FM_Matrix *matrix, double *angle, double *scaleX, double *scaleY);

#endif

#endif
