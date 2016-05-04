/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_OutlineLib.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */



#ifndef _OL_OUTLINELIB_H_INCLUDED_
#define _OL_OUTLINELIB_H_INCLUDED_


#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"
#include "OL_Common.h"
#include "OL_Pattern.h"
#include "OL_Composer.h"
#include "OL_Error.h"
#include "OL_Context.h"


typedef struct OL_OutlineLib_t {

  OL_Context		*context;
  CMP_ComposerIF	*composer;
  OL_STATUS		status;
  OL_INT		resolutionX;
  OL_INT		resolutionY;

} OL_OutlineLib;

/* public */
   
OL_OutlineLib* 		OL_OutlineLib_New(void *memoryInterface, OL_INT resoX, OL_INT resoY);
OL_VOID			OL_OutlineLib_Delete(OL_OutlineLib *handle);
OL_STATUS 		OL_OutlineLib_GetPatternByOL(OL_OutlineLib *self, 
						     OL_PatternInfo     *p_info,
						     OL_ComposerControl ctrl,
						     OL_Outline         *data,
						     OL_SHORT           weight,
						     OL_REAL            pointSize,
						     OL_INT             weightPixels,
						     OL_INT		weightMode);
OL_STATUS		OL_OutlineLib_PurgePattern(OL_OutlineLib *handle, 
						     OL_PatternInfo *p_info);
						     
/* private */

// 20030625 H.Ichioka BST-032
//OL_UINT32 		OL_OutlineLib_GetBoldPixel(float size);
OL_UINT32 		OL_OutlineLib_GetBoldPixel(float size, OL_SHORT weight);
// 20030625 end

#endif //_OL_OUTLINELIB_H_INCLUDED_

