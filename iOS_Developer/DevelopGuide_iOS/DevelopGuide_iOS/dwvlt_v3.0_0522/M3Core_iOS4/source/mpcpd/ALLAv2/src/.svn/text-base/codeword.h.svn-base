/*!	\file		codeword.h
 *	\brief		Codeword class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_CODEWORD_H_
#define _LIBALLA_CODEWORD_H_
#include "../include/alla-dev.h"
#include "macro.h"
#include "config.h"
namespace alla {
/*---------------------------------------------------------------------------*/
enum huffman_table_private {
			major_len_max = 6 };
enum entry {		entry_cw_order = 7, entry_cw_run = 16,
			entry_cw_error = 10, entry_cw_tag = 6,
			entry_cw_marker = 4 };
enum min_value {	min_cw_order = first, min_cw_run = 1,
			min_cw_error = -128, min_cw_tag = 0,
			min_cw_marker = 0 };

struct Codeword {
    int		min;
    int		max;
    int		base;
    int		major_len;
    int		sign_len;
    int		addbit_len;
    auint32	major_code;
};
/*---------------------------------------------------------------------------*/
/* cw_order			theo	actual
 *		entry		7	7
 * 		max major	6	5
 * 		max add		0	0
 */
extern const Codeword cw_order_graphics[entry_cw_order];
extern const Codeword cw_order_image[entry_cw_order];
/*---------------------------------------------------------------------------*/
/* cw_run			theo	actual
 *		entry		16	14
 * 		max major	6	6
 * 		max add		14	14
 */
extern const Codeword cw_run_graphics[entry_cw_run];
extern const Codeword cw_run_image[entry_cw_run];
/*---------------------------------------------------------------------------*/
/* cw_error			theo	actual
 *		entry		10	10
 * 		max major	5	5
 * 		max add		7	7
 */
extern const Codeword cw_error_graphics[entry_cw_error];
extern const Codeword cw_error_image[entry_cw_error];
extern const Codeword cw_error_binary[entry_cw_error];
extern const Codeword cw_error_through[entry_cw_error];
/*---------------------------------------------------------------------------*/
/* cw_tag			theo	acutal
 *		entry		6	5
 * 		max major	3	3
 * 		max add		1	1
 */
extern const Codeword cw_tag_bit2[entry_cw_tag];
extern const Codeword cw_tag_bit1[entry_cw_tag];
extern const Codeword cw_tag_bit3[entry_cw_tag];
/*---------------------------------------------------------------------------*/
/* cw_marker			theo	actual
 *		entry		N/A	4
 * 		max major	N/A	3
 * 		max add		N/A	4
 */
extern const Codeword cw_marker_ver2 [entry_cw_marker];
extern const Codeword cw_marker_ver1 [entry_cw_marker];
/*---------------------------------------------------------------------------*/
}
#endif	//_LIBALLA_CODEWORD_H_
