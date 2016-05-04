/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	RND_Renderer.h -- definition of Renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_RENDERER_H_INCLUDED
#define RND_RENDERER_H_INCLUDED

#include "COM_DeviceColorSpace.h"
#include "COM_OutputLocation.h"

void* RND_New(void *MI, long ResolutionX, long ResolutionY, 
	      long maxPageX, long maxPageY, void *CSTParameter);
long RND_Delete(void *RND);
long RND_StartJob(void *RND);
long RND_EndJob(void *RND);
long RND_ShowPage(void *RND, void *ESS, void *DLInfo, COM_DeviceColorSpace *DCS, 
		  void *CSTParameter, COM_OutputLocation *FD);
long RND_GetMemSize(long ResolutionX, long ResolutionY);

#endif
