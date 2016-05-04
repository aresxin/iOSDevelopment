/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_DataFontSupport.h -- definition of Font Manager 

	Created:	Oct 04, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_DATAFONTSUPPORT

#ifndef _FM_DATAFONTSUPPORT_H_INCLUDED_
#define _FM_DATAFONTSUPPORT_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "FM_Define.h"
#include "MI_MemoryInterface.h"
#include "FM_BitmapLib.h"
#include "OL_OutlineLib.h"
#include "FM_FontConverter.h"

typedef struct {

  void 			*MI;
  OL_OutlineLib		*OL;
  FM_BitmapLib  	*BL;
  FM_FontConverter  	*FC;

} FM_DataFontSupport;


/* public */

FM_DataFontSupport* 	FM_DataFontSupport_New(void *MI, OL_OutlineLib *OL);
void 	FM_DataFontSupport_Delete(FM_DataFontSupport *handle);

long	FM_DataFontSupport_GetBitmapFont(FM_DataFontSupport *handle, char *dataAddress, 
					FM_BitmapFont *bitmapFont, FM_Matrix *matrix);
long 	FM_DataFontSupport_GetEdgelistFont(FM_DataFontSupport *handle, char *dataAddress, 
					FM_EdgelistFont *edgelistFont, FM_Matrix *matrix); 


/* private */

void FM_DataFontSupport_MatrixPoint(void *handle, FM_Matrix *matrix, FM_Point *point, FM_Point *ans);

// CheckMatrixの変更 2004.4.8 FXPS
//long FM_DataFontSupport_CheckMatrix(FM_DataFontSupport *handle, FM_Matrix *matrix, double *angle, double *scaleX, double *scaleY);
long FM_DataFontSupport_CheckMatrix(FM_DataFontSupport *handle, FM_Matrix *matrix, double *scale);


#endif

#endif

