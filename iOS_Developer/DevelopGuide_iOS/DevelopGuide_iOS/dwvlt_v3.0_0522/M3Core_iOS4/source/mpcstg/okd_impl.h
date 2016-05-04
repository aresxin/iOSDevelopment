// File: OKD_IMPL.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _MP_OKD_IMPL_
#define _MP_OKD_IMPL_

#include "okd_pub.h"

#include "string.h"	// memset, memcpy

#define CHAR_BIT  8
#define USHRT_BIT  16

// 09.07.14 - M.Chikyu WindowsMobile対応
#ifdef _M3CORE_MP_
#undef UCHAR_MAX
#undef USHRT_MAX
#undef SHRT_MAX
#undef SHRT_MIN
#endif //_M3CORE_MP_

#define UCHAR_MAX ((1<<(sizeof(unsigned char)*8))-1)
#define USHRT_MAX ((1<<(sizeof(unsigned short)*8))-1)
#define SHRT_MAX ((1<<(sizeof(short)*8-1))-1)
#define SHRT_MIN (SHRT_MAX-USHRT_MAX)

#define MAXMATCH 256    /* formerly F (not more than UCHAR_MAX + 1) */
#define THRESHOLD  3    /* choose optimal value */
#define NC (UCHAR_MAX + MAXMATCH + 2 - THRESHOLD)
			/* alphabet = {0, 1, 2, ..., NC - 1} */
#define CBIT 9  /* $\lfloor \log_2 NC \rfloor + 1$ */

#ifdef _OKD_ENC_CPP_
	#define DICBIT	12 /* Dictionary-Size is 4K bytes. */
	//#define DICBIT	13 /* Dictionary-Size is 8k bytes. */ 
#else
	#define DICBIT	13
#endif
#define DICSIZE	(1 << DICBIT)
#define NP (DICBIT + 1)
#define NT (USHRT_BIT + 3)
#define PBIT 4  /* smallest integer such that (1 << PBIT) > NP */
#define TBIT 5  /* smallest integer such that (1 << TBIT) > NT */

#define NPT 0x80

typedef short  node;

#endif // _MP_OKD_IMPL_

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.11.10 - Ichiriki - 関数宣言を okd_enc.cpp に移動
//97.2.19 - R.Matsumura - 高速化: 辞書サイズを圧縮側だけ4k Bytesに変更(効果微)
