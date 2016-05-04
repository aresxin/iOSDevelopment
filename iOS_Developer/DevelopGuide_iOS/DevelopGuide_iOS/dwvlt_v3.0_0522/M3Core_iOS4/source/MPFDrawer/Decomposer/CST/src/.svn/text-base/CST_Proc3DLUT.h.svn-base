/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_Proc3DLUT.h	3D-LUT処理モジュールヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	Apr,2,2001	Toshio Yamazaki
 *
 * <<参考>>
 * Limoges MDS Driver Load Balance enhanced MDS_CST.h, MDS_CST_.h
 */
#include "CST_IF.h"
#include "COM_CSTParameter.h"

#ifndef CST_PROC3DLUT_H_INCLUDED
#define CST_PROC3DLUT_H_INCLUDED

/*
 * DLUT構造の定義
 */
/* 定数 */
#define CST_PARADATA3DLUT_INPUTCHANNEL	3
#define CST_PARADATA3DLUT_OUTPUTCHANNEL	4
#define CST_PARADATA3DLUT_GRID_POINTS	17
#define CST_PARADATA3DLUT_GRID_FULL	(CST_PARADATA3DLUT_GRID_POINTS-1)
#define CST_PARADATA3DLUT_GRID_BITS	4
#define CST_PARADATA3DLUT_GRID_MASK	0x0F

/*
 * I/F の宣言
 */
int CST_Proc3DLUT_TransValueWithTag( const CST_ParaData3DLUT *, unsigned char * );
int CST_Proc3DLUT_TransBufferWithTag( const CST_ParaData3DLUT *, CST_PixelBufferInfo *,
				      CST_PixelBufferInfo * );

#endif /* CST_PROC3DLUT_H_INCLUDED */
