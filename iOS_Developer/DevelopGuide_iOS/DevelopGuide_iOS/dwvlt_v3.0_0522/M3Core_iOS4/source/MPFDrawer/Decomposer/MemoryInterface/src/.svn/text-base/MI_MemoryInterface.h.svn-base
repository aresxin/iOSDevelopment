/*
   Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
   
   MI_MemoryInterface.h -- definition of Memory Interface Module
   
   Created:	Mar 08, 2001 By Kunihiko Kobayashi 
   Modified:	

*/

#ifndef _MI_MEMORYINTERFACE_H_INCLUDED_
#define _MI_MEMORYINTERFACE_H_INCLUDED_

#include 	<stdio.h>
#include 	<stdlib.h>


#ifndef MI_MEMORYDUMP

void* 	MI_Malloc(void *handle, unsigned long nbytes);
void 	MI_Free(void *handle, void *ptr);
void* 	MI_MallocDL(void *handle, unsigned long nbytes);
void 	MI_FreeDL(void *handle, void *ptr);

#else

void* 	MI_Malloc_MEMORYDUMP(void *handle, unsigned long nbytes, char *filename, long linenumber);
void 	MI_Free_MEMORYDUMP(void *handle, void *ptr, char *filename, long linenumber);
void* 	MI_MallocDL_MEMORYDUMP(void *handle, unsigned long nbytes, char *filename, long linenumber);
void 	MI_FreeDL_MEMORYDUMP(void *handle, void *ptr, char *filename, long linenumber);

#define MI_Malloc(a, b)     	MI_Malloc_MEMORYDUMP(a, b, __FILE__, __LINE__)
#define MI_Free(a, b)       	MI_Free_MEMORYDUMP(a, b, __FILE__, __LINE__)
#define MI_MallocDL(a, b)     	MI_MallocDL_MEMORYDUMP(a, b, __FILE__, __LINE__)
#define MI_FreeDL(a, b)       	MI_FreeDL_MEMORYDUMP(a, b, __FILE__, __LINE__)

#endif

void* 	MI_New(char **ptr, long *size, long nblock, char *filepath);
void 	MI_Delete(void *handle);
void 	MI_StartRenderer(void *handle);
void 	MI_EndRenderer(void *handle);
void 	MI_MemoryReport(void *handle);
long 	MI_SetDL(void *handle, long limit, long (*fallback)(void *), void *h);
void 	MI_LockDL(void *handle);
void 	MI_UnLockDL(void *handle);
void 	MI_MallocWork(void *handle, unsigned char **ptr, long *size);
void 	MI_FreeWork(void *handle, void *ptr);


FILE* 	MI_FOpen(void *handle, char *filename, char *mode);
int 	MI_FClose(void *handle, FILE *stream);
size_t 	MI_FRead(void *handle, void* buffer, size_t size, size_t count, FILE *stream);
size_t 	MI_FWrite(void *handle, void *buffer, size_t size, size_t count, FILE *stream);
int 	MI_FSeek(void *handle, FILE *stream, long offset, int origin);
long 	MI_FTell(void *handle, FILE *stream);
long 	MI_Remove(void *handle, char *filename);
FILE*	MI_Tmpfile(void *handle);
int 	MI_Fileno(void *handle, FILE *stream);
int 	MI_Tmpnam(void *handle, char *filename);
char*	MI_Tmppath(void *handle);
FILE* 	MI_IOpen(void *handle, char *filename, char *mode);
int 	MI_IClose(void *handle, FILE *stream);

void*	MI_OS_Malloc(unsigned long nbytes);
void	MI_OS_Free(void *ptr);

/* for debug */
int 	MI_WriteLog(void *handle, const char *format, ...);

#endif
