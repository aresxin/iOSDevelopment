/*
   Copyright (C) Fuji Xerox Co;Ltd. 2003. All rights reserved.
   
   SIF_MI_FileManager.h
   
   Created:	Jul 15, 2003 By Kunihiko Kobayashi 
   Modified:	
	
*/

#ifndef _SIF_MI_FILEMANAGER_H_INCLUDED_
#define _SIF_MI_FILEMANAGER_H_INCLUDED_

#include 	<stdio.h>


#include 	"SIF_MI_MemoryManager.h"


#define SIF_MI_FILEMANAGER_TEMPPREFIX 	"tmpsif_"

/* WindowsNT */
#define SIF_MI_FILEMANAGER_MAXFILEOPEN 	20
#define SIF_MI_FILEMANAGER_MAXFILENAME	260

/* Linux */
/* cygwin */
/* sun x86 */
/* sun sparc */
/*
#define SIF_MI_FILEMANAGER_MAXFILEOPEN 	16
#define SIF_MI_FILEMANAGER_MAXFILENAME	4096
#define SIF_MI_FILEMANAGER_MAXFILEOPEN 	20
#define SIF_MI_FILEMANAGER_MAXFILENAME	1024
#define SIF_MI_FILEMANAGER_MAXFILEOPEN 	60
#define SIF_MI_FILEMANAGER_MAXFILENAME	1024
#define SIF_MI_FILEMANAGER_MAXFILEOPEN 	20
#define SIF_MI_FILEMANAGER_MAXFILENAME	1024
*/


typedef struct SIF_MI_FileHandle
{
    struct SIF_MI_FileHandle *next;
    char filename[SIF_MI_FILEMANAGER_MAXFILENAME];
    char type;
    char open;
    FILE *fp;

} SIF_MI_FileHandle;

typedef struct SIF_MI_FileManager
{
    SIF_MI_MemoryManager *MM;
    SIF_MI_FileHandle *filelist;
    char *basepath;
    long callOfTmpNam;

    SIF_MI_FileHandle *poolFileHandle;
    SIF_MI_FileHandle *freeFileHandle;
    long currentFileHandleUsed;

} SIF_MI_FileManager;

/* public method */

SIF_MI_FileManager* SIF_MI_FileManager_New(SIF_MI_MemoryManager *MM, char *filepath);
void 		SIF_MI_FileManager_Delete(SIF_MI_FileManager *handle);

FILE* 	SIF_MI_FileManager_FOpen(SIF_MI_FileManager *handle, char *filename, char *mode);
int 	SIF_MI_FileManager_FClose(SIF_MI_FileManager *handle, FILE *stream);
size_t 	SIF_MI_FileManager_FRead(SIF_MI_FileManager *handle, void* buffer, size_t size, size_t count, FILE *stream);
size_t 	SIF_MI_FileManager_FWrite(SIF_MI_FileManager *handle, void *buffer, size_t size, size_t count, FILE *stream);
int 	SIF_MI_FileManager_FSeek(SIF_MI_FileManager *handle, FILE *stream, long offset, int origin);
long 	SIF_MI_FileManager_FTell(SIF_MI_FileManager *handle, FILE *stream);
long 	SIF_MI_FileManager_Remove(SIF_MI_FileManager *handle, char *filename);
FILE*	SIF_MI_FileManager_Tmpfile(SIF_MI_FileManager *handle);
int 	SIF_MI_FileManager_Fileno(SIF_MI_FileManager *handle, FILE *stream);
int 	SIF_MI_FileManager_Tmpnam(SIF_MI_FileManager *handle, char *filename);
char*	SIF_MI_FileManager_Tmppath(SIF_MI_FileManager *handle);

/* private method */

SIF_MI_FileHandle *SIF_MI_FileManager_MallocFileHandle(SIF_MI_FileManager *handle);
void 	SIF_MI_FileManager_FreeFileHandle(SIF_MI_FileManager *handle, SIF_MI_FileHandle *p);

#endif
