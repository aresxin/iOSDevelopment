/*
   Copyright (C) Fuji Xerox Co;Ltd. 2003. All rights reserved.
   
   SIF_MI_MemoryInterface.h
   
   Created:	Jul 15, 2003 By Kunihiko Kobayashi 
   Modified:	

*/

#ifndef _SIF_MI_MEMORYINTERFACE_H_INCLUDED_
#define _SIF_MI_MEMORYINTERFACE_H_INCLUDED_

#include 	<stdio.h>
#include 	<stdlib.h>

void* 	SIF_MI_New(char **ptr, long *size, long nblock, char *filepath);
void 	SIF_MI_Delete(void *handle);
void* 	SIF_MI_Malloc(void *handle, unsigned long nbytes);
void 	SIF_MI_Free(void *handle, void *ptr);
void 	SIF_MI_MemoryReport(void *handle);

FILE* 	SIF_MI_FOpen(void *handle, char *filename, char *mode);
int 	SIF_MI_FClose(void *handle, FILE *stream);
size_t 	SIF_MI_FRead(void *handle, void* buffer, size_t size, size_t count, FILE *stream);
size_t 	SIF_MI_FWrite(void *handle, void *buffer, size_t size, size_t count, FILE *stream);
int 	SIF_MI_FSeek(void *handle, FILE *stream, long offset, int origin);
long 	SIF_MI_FTell(void *handle, FILE *stream);
long 	SIF_MI_Remove(void *handle, char *filename);
FILE*	SIF_MI_Tmpfile(void *handle);
int 	SIF_MI_Fileno(void *handle, FILE *stream);
int 	SIF_MI_Tmpnam(void *handle, char *filename);
char*	SIF_MI_Tmppath(void *handle);

void*	SIF_MI_OS_Malloc(unsigned long nbytes);
void	SIF_MI_OS_Free(void *ptr);

/* for debug */
int 	SIF_MI_WriteLog(void *handle, const char *format, ...);

#endif
