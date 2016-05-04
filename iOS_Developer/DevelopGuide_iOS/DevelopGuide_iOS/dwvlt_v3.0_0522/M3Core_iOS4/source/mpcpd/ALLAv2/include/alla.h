/*!	\file		alla.h
 *	\brief		ALLAv2 libarary, user interface
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_ALLA_H_
#define _LIBALLA_ALLA_H_
#include <cstdlib>
#include "alla-config.h"
#include "alla-exception.h"
namespace alla {
/*---------------------------------------------------------------------------*/
// Definitions
class CoreEnc;
class CoreDec;
class Formatter;
class Exception;
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
typedef int (* CALLBACK) (void *, const int, void *);
/*---------------------------------------------------------------------------*/
// Enc
class Enc {
public:
    Enc 				(void) throw ();
    ~Enc 				(void);
    void		set_image_profile
					(const int	width,
					 const int	height,
					 const int	image_bit,
					 const int	tag_bit = 0,
					 color_space	cs = unspecified_cs);
    void		open		(CALLBACK	in_func  = NULL,
					 void *		in_data  = NULL,
					 CALLBACK	out_func = NULL,
					 void *		out_data = NULL);
    int			encode_line	(void);
    int			close		(const bool is_abort = false);
private:
    Formatter *		formatter;
    CoreEnc *		core;
    Info *		info;
};
/*---------------------------------------------------------------------------*/
// Dec
class Dec {
public:
    Dec 				(void) throw ();
    ~Dec 				(void);
    void		open		(CALLBACK	in_func	 = NULL,
					 void *	  	in_data	 = NULL,
					 CALLBACK 	out_func = NULL,
					 void *   	out_data = NULL);
    int			decode_line	(void);
    int			close		(const bool	is_abort = false);
    int			get_width	(void) const throw ();
    int			get_height	(void) const throw ();
    int			get_image_bit	(void) const throw ();
    int			get_tag_bit	(void) const throw ();
    color_space		get_color_space	(void) const throw ();
private:
    struct callback_param {
	auint8 *	rest_code;
	auint8 *	rest_code_p;
	int		rest_code_byte;
	CALLBACK	func;
	void		* userdata;
    };
    Formatter *		formatter;
    CoreDec *		core;
    Info *		info;
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
