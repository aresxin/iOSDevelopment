/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	MI_MemoryManager.h -- definition of Memory Interface Module

	Created:	Mar 08, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef _MI_MEMORYMANAGER_H_INCLUDED_
#define _MI_MEMORYMANAGER_H_INCLUDED_

#define NALLOC 0x400

typedef long MI_Align;

typedef union MI_MHeader {
    struct {
	union MI_MHeader 	*ptr;
	int			size;
    } s;
    MI_Align x;
} MI_MHeader;

typedef struct MI_MemoryManager
{
    MI_MHeader 			*fm_adr;
    MI_MHeader 			base;
    MI_MHeader 			base_dl;
    MI_MHeader 			*freep;
    MI_MHeader 			*freep_dl;
    long 			cur_mh_num;
    long 			cur_mh_num_dl;
    long 			max_mh_num;
    long			dl_lock;
    long			work_lock;
    long			dl_max;
    long			dl_min;
    long			(*dl_fallback_func)(void*);
    void			*dl_fallback_handle;
    
} MI_MemoryManager;

typedef struct MI_MemoryState {
	long max;

	long cur;
	long freesize;
	long maxfreesize;
	long minfreesize;
	long freeblocks;
	double avgfreesize;
	double variance;

	long cur_dl;
	long freesize_dl;
	long maxfreesize_dl;
	long minfreesize_dl;
	long freeblocks_dl;
	double avgfreesize_dl;
	double variance_dl;
} MI_MemoryState;

MI_MemoryManager* 	MI_MemoryManager_New(char *ptr, long size);
void 			MI_MemoryManager_Delete(MI_MemoryManager *handle);

void* 			MI_MemoryManager_Malloc(MI_MemoryManager *handle, unsigned long nbytes);
void 			MI_MemoryManager_Free(MI_MemoryManager *handle, void *ptr);
void* 			MI_MemoryManager_MallocDL(MI_MemoryManager *handle, unsigned long nbytes);
void 			MI_MemoryManager_FreeDL(MI_MemoryManager *handle, void *ptr);
long 			MI_MemoryManager_SetDL(MI_MemoryManager *handle, long limit, long (*fallback)(void*), void *h);
void 			MI_MemoryManager_LockDL(MI_MemoryManager *handle);
void 			MI_MemoryManager_UnLockDL(MI_MemoryManager *handle);
void 			MI_MemoryManager_MallocWork(MI_MemoryManager *handle, unsigned char **ptr, long *size);
void 			MI_MemoryManager_FreeWork(MI_MemoryManager *handle, void *ptr);
void			MI_MemoryManager_MemoryReport(MI_MemoryManager *handle, MI_MemoryState *state);

#ifdef MI_MEMORYDUMP

void* 			MI_MemoryManager_Malloc_MEMORYDUMP(MI_MemoryManager *handle, unsigned long nbytes, char *filename, long linenumber);
void 			MI_MemoryManager_Free_MEMORYDUMP(MI_MemoryManager *handle, void *ptr, char *filename, long linenumber);
void* 			MI_MemoryManager_MallocDL_MEMORYDUMP(MI_MemoryManager *handle, unsigned long nbytes, char *filename, long linenumber);
void 			MI_MemoryManager_FreeDL_MEMORYDUMP(MI_MemoryManager *handle, void *ptr, char *filename, long linenumber);
void 			MI_MemoryManager_MEMORYDUMP();

#endif

void*			MI_MemoryManager_OS_Malloc(unsigned long nbytes);
void			MI_MemoryManager_OS_Free(void *ptr);

MI_MHeader*		MI_MemoryManager_MoreCore(MI_MemoryManager *handle, long nu);
MI_MHeader*		MI_MemoryManager_MoreCoreDL(MI_MemoryManager *handle, long nu);



#endif
