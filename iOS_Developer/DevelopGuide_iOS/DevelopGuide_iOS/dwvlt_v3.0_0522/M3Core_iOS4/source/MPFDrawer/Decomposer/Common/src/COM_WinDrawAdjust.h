/*
 * Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_WinDrawAdjust.h -- ハーフスキャン方式でのWindows描画のための補正値
 *
 * Created : 2004.04.26 Masao.Morita
 *
 */

#if !defined(COM_WINDRAWADJUST_H_INCLUDED)
#define COM_WINDRAWADJUST_H_INCLUDED

#define HB_WINDRAW_SCALEDOWN_LIMIT	0.125	/* 1/8縮小まで考慮			*/
#define HB_WINDRAW_DBITS			4		/* Windowsの小数点ビット数	*/
#define HB_WINDRAW_ADJUST_EPSILON	(1.0f / (1 << (HB_WINDRAW_DBITS * 2))) * HB_WINDRAW_SCALEDOWN_LIMIT
/* HB_WINDRAW_ADJUST_EPSIONの意味　Windowsの小数点同士の掛け算後にさらにSCALEDOWNされても優位な値	*/

#define	HB_WINDRAW_R000_ADJUST_X	(float)((0.5f) - (HB_WINDRAW_ADJUST_EPSILON))
#define HB_WINDRAW_R000_ADJUST_Y	(float)((0.5f) - (HB_WINDRAW_ADJUST_EPSILON))

#define HB_WINDRAW_R090_ADJUST_X	(float)(-0.5f)
#define HB_WINDRAW_R090_ADJUST_Y	(float)((0.5f) - (HB_WINDRAW_ADJUST_EPSILON))

#define HB_WINDRAW_R180_ADJUST_X	(float)(-0.5f)
#define HB_WINDRAW_R180_ADJUST_Y	(float)(-0.5f)

#define	HB_WINDRAW_R270_ADJUST_X	(float)((0.5f) - (HB_WINDRAW_ADJUST_EPSILON))
#define HB_WINDRAW_R270_ADJUST_Y	(float)(-0.5f)


#endif

