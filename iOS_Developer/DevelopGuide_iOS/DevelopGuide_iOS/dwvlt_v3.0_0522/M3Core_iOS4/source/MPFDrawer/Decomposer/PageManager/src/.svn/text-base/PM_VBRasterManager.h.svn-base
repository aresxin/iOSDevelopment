/*      Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 
	PM_VBRasterManager.h -- definition of Page Manager 

	Created:	Mar 1, 2001 By Kunihiko Kobayashi 
	Modified:
*/

#ifndef PM_VBRASTERMANAGER_H_INCLUDED
#define PM_VBRASTERMANAGER_H_INCLUDED

#include "PM_InternalDefine.h"
#include "PM_DeviceFigure.h"
#include "PM_VBDefine.h"

typedef struct
{
    void 			*MI;
    long 			maxWidth;
    long 			maxHeight;
    long 			currentWidth;
    long 			currentHeight;
    long			memLimit;
    long			fileLimit;
    PM_VBImage			*currentImage;
    PM_VBPattern		*currentPattern;
    FILE			*imageFile;
    unsigned char		*renderBuffer;
    long			renderBufferSize;
    unsigned char		*readBuffer;
    long			readBufferSize;
    unsigned char		*palletBuffer;
    long			palletBufferSize;

} PM_VBRasterManager;

/* public */

void *PM_VBRasterManager_New(void *MI, long maxwidth, long maxheight);
PM_Error PM_VBRasterManager_Delete(void *handle);
PM_Error PM_VBRasterManager_StartPage(void *handle, int width, int height);
PM_Error PM_VBRasterManager_EndPage(void *handle);
PM_Error PM_VBRasterManager_ClearPage(void *handle);
PM_Error PM_VBRasterManager_SetImage(void *handle, PM_Image *image, PM_VBImage **VBI, unsigned char rop, PM_VBPattern *VBP);
PM_Error PM_VBRasterManager_SetGrayMask(void *handle, PM_GrayMask *gmask, PM_VBImage **VBI);
PM_Error PM_VBRasterManager_SetPattern(void *handle, PM_Pattern *pattern, PM_VBPattern **VBP, unsigned char rop);
PM_Error PM_VBRasterManager_ClearImage(void *handle);
PM_Error PM_VBRasterManager_ClearPattern(void *handle);
PM_Error PM_VBRasterManager_LoadImage(void *handle, long y);

/* private */

PM_Error PM_VBRasterManager_LoadData(PM_VBRasterManager *self, PM_VBImage *VBI, long startLine, long endLine);
PM_Error PM_VBRasterManager_ChangeOrder(PM_VBRasterManager *self, PM_VBPixelBufferInfo *in, PM_VBPixelBufferInfo *out);
PM_Error PM_VBRasterManager_ChangePatternType(PM_VBRasterManager *p, PM_VBPattern *VBP);
PM_Error PM_VBRasterManager_ExpandPixel(PM_VBRasterManager *self, long sBits, long dBytes, unsigned char *source, 
					unsigned char *destination, long width, long height, unsigned char *pallet);
					
					
#endif
