/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Context.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi
 * Modified:
 *
 */



#ifndef _OL_CONTEXT_H_INCLUDED_
#define _OL_CONTEXT_H_INCLUDED_

#define OL_CONTEXT_MI_LINK

enum {
    OL_CONTEXT_MI_USE = 0,
    OL_CONTEXT_MI_NOUSE = 0
} ;

typedef struct OL_Context_t {

    long memorySwitch;
    void *memoryInterface;  

} OL_Context;

OL_Context 	*OL_Context_New(void *memoryInterface);
void		OL_Context_Delete(OL_Context *handle);
void		*OL_Context_Malloc(OL_Context *handle, unsigned long nbytes);
void		OL_Context_Free(OL_Context *handle, void *ptr);

#endif
