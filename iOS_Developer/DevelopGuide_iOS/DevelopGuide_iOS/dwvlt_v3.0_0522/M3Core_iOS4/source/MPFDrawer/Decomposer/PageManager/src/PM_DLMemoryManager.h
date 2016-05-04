/*
      Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.

      PM_DLMemoryManager.h -- definition of Page Manager 

      Created:        Mar 1, 2001 By Kunihiko Kobayashi
      Modified:
*/

#ifndef PM_DLMEMORYMANAGER_H_INCLUDED
#define PM_DLMEMORYMANAGER_H_INCLUDED

#include "PM_InternalDefine.h"


typedef struct PM_DLCellBlock
{
    struct PM_DLCellBlock 	*next;
    long 			cp;
    long 			maxNumOfCell;
    long 			newFlag;
    PM_DisplayListCell 		*buffer;

} PM_DLCellBlock;

typedef struct
{
    void			*MI;
    PM_DLCellBlock 		*top;
    PM_DLCellBlock 		*end;
    PM_DisplayListCell 		*freeList;
    long 			maxNumOfCell;
    long 			currentNumOfCell;
    long 			blockNumOfCell;
    long 			extendBlockSize;
    long 			totalMemorySize;
    unsigned char       	*fixedBuffer;
    unsigned char       	fixedBufferSize;

}PM_DLMemoryManager;


/* public */

void *PM_DLMemoryManager_New(void *MI, unsigned char *buffer, int buffersize, int extendsize, int limitsize);
void PM_DLMemoryManager_Delete(void *handle);
void PM_DLMemoryManager_Clear(void *handle);
PM_DisplayListCell * PM_DLMemoryManager_GetDLCell(void *handle); 
void PM_DLMemoryManager_ReturnDLCell(void *handle, PM_DisplayListCell *dlcell);


/* utility */

PM_DLCellBlock *PM_DLMemoryManager_CreateDLCellBlock(void *MI, unsigned char *buffer, int size);
void PM_DLMemoryManager_DeleteDLCellBlock(void *MI, PM_DLCellBlock *cell);



#endif
