/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_FontRegister.h -- definition of Font Manager 

	Created:	Oct 04, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_FONTREGISTER

#ifndef _FM_FONTREGISTER_H_INCLUDED_
#define _FM_FONTREGISTER_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "FM_Define.h"
#include "MI_MemoryInterface.h"

typedef struct FM_FontRegisterMemory_t {
  struct FM_FontRegisterMemory_t *next;
  long currentNumOfChar;
  long limitNumOfChar;
  FM_CharInfo *charInfo;
  
} FM_FontRegisterMemory;

typedef struct {

  void 	*MI;
  long	openFlag;
  FM_FontRegisterMemory *top;
  FM_FontRegisterMemory *end;

} FM_FontRegister;


FM_FontRegister* 	FM_FontRegister_New(void *MI);
void 	FM_FontRegister_Delete(FM_FontRegister *handle);
long	FM_FontRegister_Clear(FM_FontRegister *handle);
long 	FM_FontRegister_Start(FM_FontRegister *handle);
long 	FM_FontRegister_End(FM_FontRegister *handle);
long	FM_FontRegister_Get(FM_FontRegister *handle, char **dataAddress, long *numOfChar);
long	FM_FontRegister_Add(FM_FontRegister *handle, long charSet, long charCode, FM_Point point[4]);

#endif

#endif
