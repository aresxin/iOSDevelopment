/*
      Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.

      PM_ELMemoryManager.h -- definition of Page Manager 

      Created:        Mar 1, 2001 By Kunihiko Kobayashi
      Modified:
*/

#ifndef PM_ELMEMORYMANAGER_H_INCLUDED
#define PM_ELMEMORYMANAGER_H_INCLUDED

#include "PM_InternalDefine.h"


typedef struct PM_ELCellBlock
{
    struct PM_ELCellBlock 	*next;
    long 			cp;
    long 			maxNumOfCell;
    long 			newFlag;
    PM_EdgeListCell 		*buffer;

} PM_ELCellBlock;

typedef struct
{
    void			*MI;
    PM_ELCellBlock 		*top;
    PM_ELCellBlock 		*end;
    PM_EdgeListCell 		*freeList;
    long 			maxNumOfCell;
    long 			currentNumOfCell;
    long 			blockNumOfCell;
    long 			extendBlockSize;
    long 			totalMemorySize;
    unsigned char       	*fixedBuffer;
    unsigned char       	fixedBufferSize;

}PM_ELMemoryManager;


/* public */

void *PM_ELMemoryManager_New(void *MI, unsigned char *buffer, int buffersize, int extendsize, int limitsize);
void PM_ELMemoryManager_Delete(void *handle);
void PM_ELMemoryManager_Clear(void *handle);
PM_EdgeListCell * PM_ELMemoryManager_GetELCell(void *handle); 
void PM_ELMemoryManager_ReturnELCell(void *handle, PM_EdgeListCell *elcell);
long PM_ELMemoryManager_GetCurrentCellNum(void *handle);


/* utility */

PM_ELCellBlock *PM_ELMemoryManager_CreateELCellBlock(void *MI, unsigned char *buffer, int size);
void PM_ELMemoryManager_DeleteELCellBlock(void *MI, PM_ELCellBlock *cell);



#endif
