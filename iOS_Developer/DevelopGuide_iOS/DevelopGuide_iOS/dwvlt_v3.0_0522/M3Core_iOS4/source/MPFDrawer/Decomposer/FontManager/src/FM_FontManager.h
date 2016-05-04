/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_FontManager.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	
*/

#include "FM_Define.h"

#ifdef FM_LINK_FONTMANAGER

#ifndef _FM_FONTMANAGR_H_INCLUDED_
#define _FM_FONTMANAGR_H_INCLUDED_

#include "FM_TypeExt.h"

void* FM_New(void *arg1, void *arg2, long arg3, long arg4, long arg5, long arg6);
void FM_Delete(void *handle);
long FM_StartPage(void *handle, FM_PageInfo *arg1);
long FM_EndPage(void *handle);
long FM_StartAttribute(void *handle, FM_Attribute *arg1);
long FM_EndAttribute(void *handle);
long FM_SetLogFont(void *handle, FM_LogFont *arg1, FM_Matrix *arg2);
long FM_DrawCodeFont(void *handle, FM_Point *arg1, FM_CodeString *arg2, FM_RectOption arg3, FM_Rect *arg4, FM_Point *arg5);
long FM_DrawDataFont(void *handle, FM_Point *arg1, FM_DataCharacter *arg2, FM_Matrix *arg3);
long FM_StartFontRegister(void *handle);
long FM_EndFontRegister(void *handle);
long FM_GetFontRegister(void *handle, char **dataAddress, long *numOfChar);

#endif

#endif
