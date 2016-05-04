/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_Processor.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_PROCESSOR

#ifndef _FM_PROCESSOR_H_INCLUDED_
#define _FM_PROCESSOR_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "PM_PageManager.h"
#include "MI_MemoryInterface.h"

typedef struct {

    void 	*PM;
    void 	*MI;

} FM_Processor;

void* 	FM_Processor_New(void *MI, void *PM, long resoX, long resoY);
void 	FM_Processor_Delete(void *handle);
long 	FM_Processor_StartPage(void *handle, FM_PageInfo *pageInfo);
long 	FM_Processor_EndPage(void *handle);
long	FM_Processor_StartAttribute(void *handle, FM_Attribute *attribute);
long	FM_Processor_EndAttribute(void *handle);
long 	FM_Processor_SetLogFont(void *handle, FM_LogFont *logFont, FM_Matrix *deviceMatrix);
long 	FM_Processor_DrawCodeFont(void *handle, FM_Point *startPoint, FM_CodeString *codeString, FM_RectOption rectOption, FM_Rect *clipArea, FM_Point *adjustment);
long 	FM_Processor_DrawDataFont(void *handle, FM_Point *startPoint, FM_DataCharacter *dataCharacter, FM_Matrix *deviceMatrix);
long 	FM_Processor_StartFontRegister(void *handle);
long 	FM_Processor_EndFontRegister(void *handle);
long 	FM_Processor_GetFontRegister(void *handle, char **dataAddress, long *numOfChar);

#endif

#endif
