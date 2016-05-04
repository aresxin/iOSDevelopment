/*
	Copyright (C) Fuji Xerox Co;Ltd. 2003. All rights reserved.
 
	RND_DLObjectCheck.h -- definition of Renderer

	Created:	Jun 09, 2003 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_DLOBJECTCHECK_H_INCLUDED
#define RND_DLOBJECTCHECK_H_INCLUDED

#include "RND_InternalDefine.h"
#include "RND_DLDefine.h"

/* class definition */

typedef struct RND_DLObjectCheck
{
    void			*MI;
    long			width;
    long			height;

}RND_DLObjectCheck;



/* public method */

void* RND_DLObjectCheck_New(void *MI);
RND_Error RND_DLObjectCheck_Delete(void *handle);
RND_Error RND_DLObjectCheck_Check(void *handle, void *dlinfo, long tagBitWidth, long rectCheck, 
				  long *lx, long *ly, long *ux, long *uy);

/* private method */

RND_Error RND_DLObjectCheck_Change2bit(RND_DLObjectCheck *self, RND_DLHeader **displayList);
RND_Error RND_DLObjectCheck_GetObjectRect(RND_DLObjectCheck *self, RND_DLHeader **displayList, 
					  long *lx, long *ly, long *ux, long *uy);
RND_Error RND_DLObjectCheck_GetRect(RND_DLObjectCheck *self, RND_DLHeader *dl, long *lx, long *ux, long *h);
RND_Error RND_DLObjectCheck_GetIELRect(RND_DLObjectCheck *self, RND_DLHeader *dl, long *lx, long *ux, long *h);

#endif
