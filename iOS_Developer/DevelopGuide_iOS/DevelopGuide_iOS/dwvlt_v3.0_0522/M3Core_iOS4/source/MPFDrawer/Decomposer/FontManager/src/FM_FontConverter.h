/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_FontConverter.h -- definition of Font Manager 

	Created:	Dec 03, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_FONTCONVERTER

#ifndef _FM_FONTCONVERTER_H_INCLUDED_
#define _FM_FONTCONVERTER_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "FM_Define.h"
#include "MI_MemoryInterface.h"

typedef struct {
  void				*MI;
} FM_FontConverter;

/* public */

FM_FontConverter* FM_FontConverter_New(void *MI);
void FM_FontConverter_Delete(FM_FontConverter *handle);
long FM_FontConverter_ToEdgelistFont(FM_FontConverter *handle, 
				   FM_BitmapFont *bfont, FM_EdgelistFont *efont);
long FM_FontConverter_ToBitmapFont(FM_FontConverter *handle, 
				   FM_EdgelistFont *efont, FM_BitmapFont *bfont);

#endif

#endif
