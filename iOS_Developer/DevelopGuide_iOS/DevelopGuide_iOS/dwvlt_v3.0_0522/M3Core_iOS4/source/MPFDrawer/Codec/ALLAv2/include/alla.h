/*!	\file		alla.h
 *	\brief		ALLAv2 libarary, user interface
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.2-woexception-1
 *	\date		2004.08.06
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_ALLA_H_
#define _LIBALLA_ALLA_H_
#include <stdlib.h>
#include "alla-config.h"
#include "alla-exception.h"
namespace alla_v2 {
/*---------------------------------------------------------------------------*/
// Definitions
class CoreEnc;
class CoreDec;
class Formatter;
class Info;

enum color_space {
		brightness=0, density=0x80,
		unspecified_cs=0, reserved=0x80,
		app_begin=0x1, app_end=0xf,
		// single component colorspaces
		bnw=(0x10|density), bnw_brightness=(0x10|brightness),
		gray=(0x11|brightness), gray_density=(0x11|density),
		// plural components colorspaces
		rgb=(0x30|brightness), bgr=(0x31|brightness),
		ymck=(0x40|density), cmyk=(0x41|density),
		kymc=(0x42|density), kcmy=(0x43|density)
};
typedef int (* MY_CALLBACK) (void *, const int, void *);
/*---------------------------------------------------------------------------*/
// Enc
class Enc {
public:
    Enc 				(void) NO_THROW;
    ~Enc 				(void) NO_THROW;
    void		set_image_profile
					(const int	width,
					 const int	height,
					 const int	image_bit,
					 const int	tag_bit = 0,
					 color_space	cs = unspecified_cs)
					       NO_THROW;
    void		open		(MY_CALLBACK	in_func  = NULL,
					 void *		in_data  = NULL,
					 MY_CALLBACK	out_func = NULL,
					 void *		out_data = NULL)
					       NO_THROW;
    int			encode_line	(void) NO_THROW;
    int			close		(const bool is_abort = false)
					       NO_THROW;
    bool		is_bad		(void) const NO_THROW;
    Status		get_status	(void) const NO_THROW;
private:
    Formatter *		formatter;
    CoreEnc *		core;
    Info *		info;
    Status		status;
};
/*---------------------------------------------------------------------------*/
// Dec
class Dec {
public:
    Dec 				(void) NO_THROW;
    ~Dec 				(void) NO_THROW;
    void		open		(MY_CALLBACK	in_func	 = NULL,
					 void *	  	in_data	 = NULL,
					 MY_CALLBACK 	out_func = NULL,
					 void *   	out_data = NULL)
					       NO_THROW;
    int			decode_line	(void) NO_THROW;
    int			close		(const bool	is_abort = false)
					       NO_THROW;
    int			get_width	(void) const NO_THROW;
    int			get_height	(void) const NO_THROW;
    int			get_image_bit	(void) const NO_THROW;
    int			get_tag_bit	(void) const NO_THROW;
    color_space		get_color_space	(void) const NO_THROW;
    bool		is_bad		(void) const NO_THROW;
    Status		get_status	(void) const NO_THROW;
private:
    struct callback_param {
	auint8 *	rest_code;
	auint8 *	rest_code_p;
	int		rest_code_byte;
	MY_CALLBACK	func;
	void		* userdata;
    };
    Formatter *		formatter;
    CoreDec *		core;
    Info *		info;
    Status		status;
    callback_param	in;

    void		proc_succeeding_chunk
					(void);
    static int		wrap_callback_in
					(void *		ptr,
					 const int	bytes,
					 void *		userdata);
};
/*---------------------------------------------------------------------------*/
};
#endif //_LIBALLA_ALLA_H_
