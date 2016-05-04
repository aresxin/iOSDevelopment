/*!	\file		crc32.h
 *	\brief		Crc32 class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_CRC32_H_
#define _LIBALLA_CRC32_H_
#include "../include/alla-dev.h" 
#include "macro.h"
#include "config.h"
ALLA_NAMESPACE_BEGIN
/*---------------------------------------------------------------------------*/
class Crc32 {
public:
    Crc32					(void);
    ~Crc32					(void)		{};
    void		update			(const auint8 * buf,
						 int len);
    void		clear			(void);
    auint32	 	get			(void) const;
private:
    int			table_computed, size;
    auint32		crc, table [256];
    void 		make_crc_table		(void);
};
/*---------------------------------------------------------------------------*/
ALLA_NAMESPACE_END
#endif //_LIBALLA_CRC32_H_
