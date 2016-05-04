/*      Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 
	PM_DLRasterManager.h -- definition of Page Manager 

	Created:	Mar 1, 2001 By Kunihiko Kobayashi 
	Modified:
*/

#ifndef PM_DLRASTERMANAGER_H_INCLUDED
#define PM_DLRASTERMANAGER_H_INCLUDED

#include "PM_InternalDefine.h"
#include "PM_DeviceFigure.h"
#include "PM_DLDefine.h"

typedef struct PM_DLImageCell
{
    struct PM_DLImageCell 	*next;
    PM_DLImage			image;
    
} PM_DLImageCell;

typedef struct PM_DLPatternCell
{
    struct PM_DLPatternCell 	*next;
    PM_DLPattern		pattern;
    long			id;
    
} PM_DLPatternCell;

typedef struct PM_DLRasterSplitInfo
{
    long	splitAmount;
    long	splitAmountTmp;
    long	numOfImage;

}PM_DLRasterSplitInfo;

typedef struct
{
    void 			*MI;
    long 			maxWidth;
    long 			maxHeight;
    long 			currentWidth;
    long 			currentHeight;
    long 			splitHeight;
    long 			splitLimit;
    long 			splitNumber;
    PM_DLRasterSplitInfo	*splitInfo;
    long			imageMemLimit;
    long			imageFileLimit;
    PM_DLImageCell		*imageList;
    PM_DLPatternCell		*patternList;
    FILE			*imageFilePtr;
    PM_DLImage			imageSave;
    FILE			*imageSaveFilePtr;
    PM_DLPattern		patternSave;
    FILE			*patternSaveFilePtr;
    long			imageFileOffset;
    PM_DLPatternCell		**patternCache;
    long			patternCacheSize;
    char			*workBuffer;
    long			workBufferSize;

} PM_DLRasterManager;

/* public */

void *PM_DLRasterManager_New(void *MI, long maxWidth, long maxHeight);
PM_Error PM_DLRasterManager_Delete(void *handle);
PM_Error PM_DLRasterManager_StartPage(void *handle, int currentWidth, int currentHeight);
PM_Error PM_DLRasterManager_GetPage(void *handle, FILE **fp);
PM_Error PM_DLRasterManager_EndPage(void *handle);
PM_Error PM_DLRasterManager_ClearPage(void *handle);
PM_Error PM_DLRasterManager_SetImage(void *handle, PM_Image *image, PM_DLImage **dlimage, unsigned char rop, PM_DLPattern *dlpattern);
PM_Error PM_DLRasterManager_SetPattern(void *handle, PM_Pattern *pattern, PM_DLPattern **dlpattern, unsigned char rop);
PM_Error PM_DLRasterManager_SaveImage(void *handle, PM_DLImage *image);
PM_Error PM_DLRasterManager_SavePattern(void *handle, PM_DLPattern *pattern);
PM_Error PM_DLRasterManager_RestoreImage(void *handle, PM_DLImage **image);
PM_Error PM_DLRasterManager_RestorePattern(void *handle, PM_DLPattern **pattern);

/* private */

PM_Error PM_DLRasterManager_ClearImage(PM_DLRasterManager *p);
PM_Error PM_DLRasterManager_ClearPattern(PM_DLRasterManager *p);
PM_Error PM_DLRasterManager_ChangePatternType(PM_DLRasterManager *p, PM_DLPattern *dlpattern);
PM_Error PM_DLRasterManager_CopyFileData(PM_DLRasterManager *p, FILE *outfp, FILE *infp, long size);


#endif
