/*!	\file		ycc.h
 *	\brief		rgb<->ycc color conversion
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.3
 *	\date		2004.09.01
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_YCC_H_
#define _LIBALLA_YCC_H_
#include "macro.h"
ALLA_NAMESPACE_BEGIN
/*---------------------------------------------------------------------------*/

#define DISCREET	12

#define OFST(X)	((X) + 2047)

#define YCC_Y(R,G,B)	(OFST(1225*(R) +2404*(G) +467*(B) ) >> DISCREET)
#define YCC_CB(R,G,B)	(OFST(-691*(R) -1357*(G) +2048*(B)) >> DISCREET)
#define YCC_CR(R,G,B)	(OFST(2048*(R) -1715*(G) -333*(B) ) >> DISCREET)

#define RGB_R(Y,CB,CR)	CLIP((Y)+(OFST(           +5743*(CR)) >> DISCREET))
#define RGB_G(Y,CB,CR)	CLIP((Y)+(OFST(-1410*(CB) -2925*(CR)) >> DISCREET))
#define RGB_B(Y,CB,CR)	CLIP((Y)+(OFST( 7258*(CB)           ) >> DISCREET))
/*---------------------------------------------------------------------------*/
ALLA_NAMESPACE_END
#endif //_LIBALLA_YCC_H_
