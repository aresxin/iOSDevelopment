/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Context.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Context_h
#define INC_IMG_Context_h

#include <stdio.h>

#include "MI_MemoryInterface.h"
#define IMG_MALLOC(context,size)	MI_Malloc((context)->memoryInterface,size)
#define IMG_FREE(context,address)	MI_Free((context)->memoryInterface,address)

#ifdef NDEBUG

	#define IMG_OBJ_ALLOC(context, obj, className) \
			if ( (obj = (className *)IMG_MALLOC(context, sizeof(className))) == IMG_NULL) \
				{ IMG_Context_WriteLog(context, "Cannot allocate object %s file = %s line = %d\n", #className, __FILE__, __LINE__); }

	#define IMG_BUF_ALLOC(context, buf, type, size) \
			if ( (buf = (type *)IMG_MALLOC(context, size)) == IMG_NULL) \
				{ IMG_Context_WriteLog(context, "Cannot allocate buffer %d bytes file = %s line = %d\n", size, __FILE__, __LINE__); }

/* NDEBUG */
#else

	#define IMG_OBJ_ALLOC(context, obj, className) \
			obj = (className *) IMG_Context_Malloc(context, sizeof(className), #className, __FILE__, __LINE__)

	#define IMG_BUF_ALLOC(context, buf, type, size) \
			buf = (type *)IMG_Context_Malloc(context, size, #type, __FILE__, __LINE__)

/* NDEBUG */
#endif

/*
 * ファイルアクセス制御マクロ
 *
 * FILE  *IMG_FOPEN(IMG_Context *context, char *filename, char *mode);
 * int 	  IMG_FCLOSE(IMG_Context *context, FILE *stream);
 * size_t IMG_FWRITE(IMG_Context *context, void *buffer, size_t size, size_t count, FILE *stream);
 */

#define IMG_FOPEN(context, fileName, mode) \
					MI_FOpen((context)->memoryInterface, fileName, mode)
#define IMG_FCLOSE(context, file) \
					MI_FClose((context)->memoryInterface, file)
#define IMG_FWRITE(context, buffer, size, count, stream) \
					MI_FWrite((context)->memoryInterface, buffer, size, count, stream)

/*
 * IMG_Contextの定義
 */
typedef struct img_context {
    void *memoryInterface;		/* MemoryInterfaceへのハンドル */
	void *pageManager;			/* PageManagerへのハンドル */
	void *renderer;				/* Rendererへのハンドル */
	FILE *logFile;				/* エラーログ書き込みファイル */
#ifndef IMG_FM_NODEFINE
    void *fontManager;          /* FontManagerへのハンドル */
#endif
    void *edgeSinkSet;          /* EdgeSinkSetへのハンドル */
	struct img_job	*job;
} IMG_Context;

extern int IMG_Context_OpenLogFile(
	IMG_Context	*context,
	const char *fileName);

extern void IMG_Context_CloseLogFile(
	IMG_Context	*context);

extern void IMG_Context_WriteLog(
	IMG_Context		*context,
	const char		*fmt, ...);

extern void IMG_Context_Fail(
	IMG_Context		*context);

extern void *IMG_Context_Malloc(
	IMG_Context		*context,
	unsigned long	size,
	char			*className,
	char			*file,
	int				line);

/* INC_IMG_Context_h */
#endif

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 11.Apr.2001 Yozo Kashima IMG_MALLOCとIMG_FREEの引数contextを括弧で括る。
 *							IMG_REQUIRE2をここに移動。
 *							IMG_USE_MIを削除。IMG_RELEASEを使うよう修正。
 * 13.Apr.2001 Yozo Kashima IMG_Context_WriteLogを追加。
 * 15.Apr.2001 Yozo Kashima IMG_Context_Failを追加。
 * 10.Aug.2001 Yozo Kashima AssertionマクロをIMG_Assert.hに移動。
 * 03.Oct.2001 Yozo Kashima 障害#129(fh8008g0-08)の対応。
 *							IMG_Context_Mallocを追加しメモリ枯渇のログを取得する。
 * 09.Oct.2003 Yozo Kashima IMG_RELEASEマクロの廃止。
 *							IMG_Context_{OpenLogFile,CloseLogFile}を追加。
 */

/* end of IMG_Context.h */
