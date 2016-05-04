/*
   Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
   
   MI_FileManager.h -- definition of Memory Interface Module
   
   Created:	Mar 08, 2001 By Kunihiko Kobayashi 
   Modified:	
	
*/

#ifndef _MI_FILEMANAGER_H_INCLUDED_
#define _MI_FILEMANAGER_H_INCLUDED_

#include 	<stdio.h>


#include 	"MI_MemoryManager.h"


#define MI_FILEMANAGER_TEMPPREFIX 	"tmphb_"

/* WindowsNT */
#define MI_FILEMANAGER_MAXFILEOPEN 	20
#define MI_FILEMANAGER_MAXFILENAME	260

/* Linux */
/* cygwin */
/* sun x86 */
/* sun sparc */
/*
#define MI_FILEMANAGER_MAXFILEOPEN 	16
#define MI_FILEMANAGER_MAXFILENAME	4096
#define MI_FILEMANAGER_MAXFILEOPEN 	20
#define MI_FILEMANAGER_MAXFILENAME	1024
#define MI_FILEMANAGER_MAXFILEOPEN 	60
#define MI_FILEMANAGER_MAXFILENAME	1024
#define MI_FILEMANAGER_MAXFILEOPEN 	20
#define MI_FILEMANAGER_MAXFILENAME	1024
*/


typedef struct MI_FileHandle
{
    struct MI_FileHandle *next;
    char filename[MI_FILEMANAGER_MAXFILENAME];
    char type;
    char open;
    FILE *fp;

} MI_FileHandle;

typedef struct MI_FileManager
{
    MI_MemoryManager *MM;
    MI_FileHandle *filelist;
    char *basepath;
    long callOfTmpNam;

    MI_FileHandle *poolFileHandle;
    MI_FileHandle *freeFileHandle;
    long currentFileHandleUsed;

} MI_FileManager;

/* public method */

MI_FileManager* MI_FileManager_New(MI_MemoryManager *MM, char *filepath);
void 		MI_FileManager_Delete(MI_FileManager *handle);

FILE* 	MI_FileManager_FOpen(MI_FileManager *handle, char *filename, char *mode);
int 	MI_FileManager_FClose(MI_FileManager *handle, FILE *stream);
size_t 	MI_FileManager_FRead(MI_FileManager *handle, void* buffer, size_t size, size_t count, FILE *stream);
size_t 	MI_FileManager_FWrite(MI_FileManager *handle, void *buffer, size_t size, size_t count, FILE *stream);
int 	MI_FileManager_FSeek(MI_FileManager *handle, FILE *stream, long offset, int origin);
long 	MI_FileManager_FTell(MI_FileManager *handle, FILE *stream);
long 	MI_FileManager_Remove(MI_FileManager *handle, char *filename);
FILE*	MI_FileManager_Tmpfile(MI_FileManager *handle);
int 	MI_FileManager_Fileno(MI_FileManager *handle, FILE *stream);
int 	MI_FileManager_Tmpnam(MI_FileManager *handle, char *filename);
char*	MI_FileManager_Tmppath(MI_FileManager *handle);
FILE* 	MI_FileManager_IOpen(MI_FileManager *handle, char *filename, char *mode);
int 	MI_FileManager_IClose(MI_FileManager *handle, FILE *stream);

/* private method */

MI_FileHandle *MI_FileManager_MallocFileHandle(MI_FileManager *handle);
void 	MI_FileManager_FreeFileHandle(MI_FileManager *handle, MI_FileHandle *p);

#endif
