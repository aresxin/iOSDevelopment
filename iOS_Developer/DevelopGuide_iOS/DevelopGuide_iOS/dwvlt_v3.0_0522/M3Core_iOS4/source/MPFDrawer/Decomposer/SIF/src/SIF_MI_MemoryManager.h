/*
	Copyright (C) Fuji Xerox Co;Ltd. 2003. All rights reserved.
 
	SIF_MI_MemoryManager.h

	Created:	Jul 15, 2003 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef _SIF_MI_MEMORYMANAGER_H_INCLUDED_
#define _SIF_MI_MEMORYMANAGER_H_INCLUDED_

#if !defined(DOCUWORKS_VIEWER)
#define NALLOC 0x400
#else
#define NALLOC 0x008
#endif

typedef long SIF_MI_Align;

typedef union SIF_MI_MHeader {
    struct {
	union SIF_MI_MHeader 	*ptr;
	int			size;
    } s;
    SIF_MI_Align x;
} SIF_MI_MHeader;

typedef struct SIF_MI_MemoryManager
{
    SIF_MI_MHeader 			*fm_adr;
    SIF_MI_MHeader 			base;
    SIF_MI_MHeader 			*freep;
    long 			cur_mh_num;
    long 			max_mh_num;
    
} SIF_MI_MemoryManager;

typedef struct SIF_MI_MemoryState {
	long max;

	long cur;
	long freesize;
	long maxfreesize;
	long minfreesize;
	long freeblocks;
	double avgfreesize;
	double variance;

} SIF_MI_MemoryState;

SIF_MI_MemoryManager* 	SIF_MI_MemoryManager_New(char *ptr, long size);
void 			SIF_MI_MemoryManager_Delete(SIF_MI_MemoryManager *handle);

void* 			SIF_MI_MemoryManager_Malloc(SIF_MI_MemoryManager *handle, unsigned long nbytes);
void 			SIF_MI_MemoryManager_Free(SIF_MI_MemoryManager *handle, void *ptr);
void			SIF_MI_MemoryManager_MemoryReport(SIF_MI_MemoryManager *handle, SIF_MI_MemoryState *state);

void*			SIF_MI_MemoryManager_OS_Malloc(unsigned long nbytes);
void			SIF_MI_MemoryManager_OS_Free(void *ptr);

SIF_MI_MHeader*		SIF_MI_MemoryManager_MoreCore(SIF_MI_MemoryManager *handle, long nu);



#endif
