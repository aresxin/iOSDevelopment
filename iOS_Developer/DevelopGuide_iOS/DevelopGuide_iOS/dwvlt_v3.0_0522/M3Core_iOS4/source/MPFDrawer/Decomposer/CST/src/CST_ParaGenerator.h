/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_ParaGenerator.h	CSTパラを生成するパッケージ
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	Apr,3,2001	Toshio Yamazaki
 *
 */
#include "CST_IF.h"
#include "CST_InternalDef.h"

#ifndef CST_PARAGENERATOR_H_INCLUDED
#define CST_PARAGENERATOR_H_INCLUDED

int CST_ParaGenerator_MakeParameter( CST * );

/*
 * 汎用色補正/色変換用パラメータ
 * Globalなスコープをもつやつ
 */
/* RGB→sRGB色変換の出力側のLUT */
extern const unsigned char CST_Default_XYZ2sRGB_1DLUT_Data[4096];

#endif /* CST_PARAGENERATOR_H_INCLUDED */
