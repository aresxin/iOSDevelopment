/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_DataCache.h -- definition of Font Manager 

	Created:	Dec 03, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_LINK_DATACACHE

#ifndef _FM_DATACACHE_H_INCLUDED_
#define _FM_DATACACHE_H_INCLUDED_

#include "FM_Type.h"
#include "FM_TypeExt.h"


#define FM_DATACACHE_KEYINFOSIZE  	(40)
#define FM_DATACACHE_HASHTABLE 		(109)
#define FM_DATACACHE_HASHLIMIT 		(15)          /* percent */
#define FM_DATACACHE_LIMITSIZE		(1024 * 15)   /* bytes */
#define FM_DATACACHE_GCAMOUNT		(100)         /* number of data */

typedef struct FM_DataCacheInfo_t {
  unsigned char 		*dataAddress;
  long				dataSize;
  unsigned long			ID; /* hash-ID */
  unsigned char			keyInfo[FM_DATACACHE_KEYINFOSIZE];
  long				keySize;
} FM_DataCacheInfo;

typedef struct FM_DataCacheHeader_t {
  struct FM_DataCacheHeader_t 	*next;
  long				size;
} FM_DataCacheHeader;

typedef struct FM_DataCacheHashCell_t {
  struct FM_DataCacheHashCell_t *nextH;	   /* hash link */
  struct FM_DataCacheHashCell_t *nextP;    /* priority link */
  struct FM_DataCacheHashCell_t *prevP;    /* priority link */
  FM_DataCacheInfo		info;
} FM_DataCacheHashCell;

typedef struct {
  FM_DataCacheHeader 		baseList;
  FM_DataCacheHeader 		*freeList;
  FM_DataCacheHashCell		**hashTable;
  FM_DataCacheHashCell		*hashPool;
  FM_DataCacheHashCell		*hashFreeList;
  FM_DataCacheHashCell		*pListTop;
  FM_DataCacheHashCell		*pListEnd;
  long				maxHeader;
  long				curHeader;
  long				maxHashCell;
  long				curHashCell;
  long				hashTableSize;
} FM_DataCache;

/* public */

FM_DataCache* FM_DataCache_New(char *cacheAddress, long size);
void FM_DataCache_Delete(FM_DataCache *handle);
long FM_DataCache_Append(FM_DataCache *handle, FM_DataCacheInfo *info);
long FM_DataCache_Search(FM_DataCache *handle, FM_DataCacheInfo *info);
long FM_DataCache_Remove(FM_DataCache *handle, FM_DataCacheInfo *info);
long FM_DataCache_GetFreeSize(FM_DataCache *handle, unsigned long *size);
long FM_DataCache_GetFreeNumber(FM_DataCache *handle, unsigned long *number);

/* private */

unsigned long FM_DataCache_GetHashID(FM_DataCache *handle, unsigned long key);
FM_DataCacheHeader* FM_DataCache_Alloc(FM_DataCache *handle, unsigned long nbytes);
void FM_DataCache_Free(FM_DataCache *handle, FM_DataCacheHeader *address);
FM_DataCacheHashCell *FM_DataCache_GetHashCell(FM_DataCache *handle);
void FM_DataCache_ReturnHashCell(FM_DataCache *handle, FM_DataCacheHashCell *cell);
long FM_DataCache_GC(FM_DataCache *handle);

#endif

#endif
