/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_CodeConverter.h -- definition of Font Manager 

	Created:	Dec 03, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_CODECONVERTER

#ifndef _FM_CODECONVERTER_H_INCLUDED_
#define _FM_CODECONVERTER_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "MI_MemoryInterface.h"

typedef struct {
  void		*MI;
} FM_CodeConverter;

/* public */

FM_CodeConverter* FM_CodeConverter_New(void *MI); 
void FM_CodeConverter_Delete(FM_CodeConverter *handle);

long FM_CodeConverter_ANSItoUNICODE(FM_CodeConverter *handle, 
				    unsigned char *dataPtr,
				    long dataSize, 
				    unsigned char **unicodePtr, 
				    long *numChar);

long FM_CodeConverter_SJIStoUNICODE(FM_CodeConverter *handle, 
				    unsigned char *dataPtr, 
				    long dataSize, 
				    unsigned char **unicodePtr, 
				    long *numChar);

long FM_CodeConverter_ONEBYTEtoUNICODE(FM_CodeConverter *handle, 
				       unsigned char *dataPtr, 
				       long dataSize, 
				       unsigned char **unicodePtr, 
				       long *numChar);

long FM_CodeConverter_TWOBYTEStoUNICODE(FM_CodeConverter *handle, 
					unsigned char *dataPtr, 
					long dataSize, 
					unsigned char **unicodePtr, 
					long *numChar);
					
#endif

#endif
