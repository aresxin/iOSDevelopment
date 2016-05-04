/*!	\file		formatter.h
 *	\brief		Formatter class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_FORMATTER_H_
#define _LIBALLA_FORMATTER_H_
#include "../include/alla-dev.h" 
#include "macro.h"
#include "config.h"
ALLA_NAMESPACE_BEGIN
/*---------------------------------------------------------------------------*/
const auint32	ALA_MAGIC	= 0xc2c0cfbaUL;
const auint32	ACF_MAGIC_1	= 0x41434689UL;	// "acf "
const auint32	ACF_MAGIC_2	= 0x0d0a1a0aUL;	// CR,LF,^Z,LF
const auint32	ACF_VERSION	= 0;
const auint32	ALLOWED_REQ	= 0x7f000fffUL;
const auint32	ALLOWED_CHUNK	= 0x0300000fUL;
enum chunk_id {	ihdr, aprm, bprm, idat, iend, sprm, rprm, atxt, phys, xxxx};

struct Chunk {
    auint32	data_size;
    chunk_id	id;
    void *	data;
};

struct IhdrImage {
    auint8	magic[8];
    auint8	minor_version[2];
    auint8	req[4];
    auint8	chunk_req[4];
    auint8	width[4];
    auint8	height[4];
    auint8	image_depth[1];
    auint8	tag_depth[1];
    auint8	tag_position[1];
    auint8	cspace[1];
    auint8	reserve[2];
};

struct AprmImage {
    auint8	run_max[4];
    auint8	initial_order[5];
    auint8	diff_base[1];
    auint8	image_diff[1];
    auint8	tag_diff[1];
    auint8	run_htable[1];
    auint8	error_htable[1];
    auint8	marker_htable[1];
    auint8	outfield[2];
    auint8	reserve[3];
};

struct BprmImage {
    auint8	h_sample[1];
    auint8	v_sample[1];
    auint8	sample_format[1];
    auint8	cst_format[1];
    auint8	reserve[4];
};

struct IdatImage {
};

struct IendImage {
};

struct SprmImage {
};

struct RprmImage {
};

struct AtxtImage {
};

struct PhysImage {
    auint8	ppu_x[4];
    auint8	ppu_y[4];
    auint8	unit[1];
};
/*---------------------------------------------------------------------------*/
ALLA_NAMESPACE_END
#endif //_LIBALLA_FORMATTER_H_
