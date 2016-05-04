/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_FontCache.h -- definition of Font Manager 

	Created:	Dec 03, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_FONTCACHE

#ifndef _FM_FONTCACHE_H_INCLUDED_
#define _FM_FONTCACHE_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"
#include "FM_DataCache.h"
#include "FM_FontConverter.h"
#include "MI_MemoryInterface.h"

#define FM_FONTCACHE_FONTSIZE 		(2048)
#define FM_FONTCACHE_NAMESIZE 		(256)
#define FM_FONTCACHE_NONAME 		(0xffffffff)

typedef struct FM_FontCacheInfo_t {
  unsigned long 		ID;
  long				rotate; 
  long				weight;
  long				width;
  long				height;
  long				italic;
  unsigned char			emulation;
  unsigned char			pitchfalimy;
  unsigned char			charset;
  unsigned char			code[2];
  unsigned char			faceNameSize;
  unsigned char			*faceName;
} FM_FontCacheInfo;

typedef struct FM_FontCacheData_t {
  union {
    FM_BitmapFont		bitmapFont;
    FM_EdgelistFont		edgelistFont;
  } font;
  unsigned long			type;
} FM_FontCacheData;

typedef struct FM_FontNameCell_t {
  char fontName[64];
} FM_FontNameCell;



typedef struct {
  void				*MI;
  FM_DataCache			*dataCache;
  FM_FontConverter		*fontConverter;
  FM_FontNameCell		*nameTable;
  long				maxNameSize;
  long				curNameSize;
} FM_FontCache;

/* public */

FM_FontCache* FM_FontCache_New(void *MI, unsigned char *cacheAddress, unsigned long size);
void FM_FontCache_Delete(FM_FontCache *handle);
long FM_FontCache_Append(FM_FontCache *handle, FM_FontCacheInfo *info, FM_FontCacheData *src, FM_FontCacheData *dst);
long FM_FontCache_Search(FM_FontCache *handle, FM_FontCacheInfo *info, FM_FontCacheData *data);

unsigned long FM_FontCache_SearchFontName(FM_FontCache *handle, unsigned char *faceName, unsigned char size);

#endif

#endif
