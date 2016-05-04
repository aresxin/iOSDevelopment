/*
      Copyright (C) Fuji Xerox Co; Ltd. 2001. All rights reserved.

      RND_PageRenderer.h -- definition of Renderer


      Created:        Feb 23, 2001 By Kunihiko Kobayashi
      Modified:
*/

#ifndef RND_PAGERENDERER_H_INCLUDED
#define RND_PAGERENDERER_H_INCLUDED

#include "RND_InternalDefine.h"

/* public method */

void* RND_PageRenderer_New(void *MI, long ResolutionX, long ResolutionY, long maxPageX, long maxPageY,
			   void *CSTparameter, RND_RendererType type);
RND_Error RND_PageRenderer_Delete(void *handle);
RND_Error RND_PageRenderer_StartJob(void *handle);
RND_Error RND_PageRenderer_EndJob(void *handle);
RND_Error RND_PageRenderer_ShowPage(void *handle, void *ESS, unsigned char *work, long size, 
				    void *info, COM_DeviceColorSpace *dcs, void *cst, COM_OutputLocation *FD);
				    
/* class definition */

typedef struct RND_PageRenderer
{
    RND_RendererType 		type;
    void 			*handle;

} RND_PageRenderer;


#endif
