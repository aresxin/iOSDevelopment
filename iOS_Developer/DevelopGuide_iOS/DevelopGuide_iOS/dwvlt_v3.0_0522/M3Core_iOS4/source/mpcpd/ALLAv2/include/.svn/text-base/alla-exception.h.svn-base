/*!	\file		alla-exception.h
 *	\brief		exception class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_ALLA_EXCEPTION_H_
#define _LIBALLA_ALLA_EXCEPTION_H_
#include <exception>
namespace alla {
/*---------------------------------------------------------------------------*/
/*  id
 *   0	unknown
 *  10	OutImageBuffer::write_line 	unknown sample pattern
 *  11	OutImageBuffer::write_line	callback_out returns bad bytes
 *  20	InImageBuffer::read_line	unknown sample pattern
 *  21	InImageBuffer::read_line	callback_in returns bad bytes
 *  30	CoreDec::proc_terminating_marker
 *  					bad marker position
 *  31	CoreDec::feed_marker		bad alloc
 *  32	CoreDec::feed_marker		early EOI
 *  33	CoreDec::feed_marker		unknown marker
 *  34	CoreDec::terminate		no EOI
 *  35	CoreDec::CoreDec		bad alloc
 *  40	CoreEnc::encode_line		unknown component
 *  41	CoreEnc::encode_line		CPY not supported for midline
 *  42	CoreEnc::encode_line		FIL not supported for midline
 *  43	CoreEnc::encode_line		bad marker
 *  44	CoreEnc::insert_marker		bad marker
 *  45	CoreEnc::terminate		only EOI and EOB are acceptable
 *  46	CoreEnc::CoreEnc		bad alloc
 *  50	Formatter::write_chunk		unknown chunk
 *  51	Formatter::write_APRM		unknown referer
 *  52	Formatter::write_APRM		unknown image_differing
 *  53	Formatter::write_APRM		unknown tag_differing
 *  54	Formatter::write_APRM		unknown run_htable
 *  55	Formatter::write_APRM		unknown error_htable
 *  56	Formatter::write_APRM		unknown marker_htable
 *  57	Formatter::read_chunk		unknown chunk
 *  58	Formatter::read_chunk		bad crc
 *  59	Formatter::read_IHDR		not ACF file
 *  60	Formatter::read_IHDR		unsupported minor version
 *  61	Formatter::read_IHDR		unsupported requirement
 *  62	Formatter::read_IHDR		unsupported chunk
 *  63	Formatter::read_APRM		unknown referer
 *  64	Formatter::read_APRM		unknown differer
 *  65	Formatter::read_APRM		unknown image_differing
 *  66	Formatter::read_APRM		unknown tag_differing
 *  67	Formatter::read_APRM		unknown error_htable
 *  68	Formatter::read_APRM		unknown marker_htable
 *  69	Formatter::read_ala_header	no ALA file
 *  70	Formatter::read_acf_befoer_IDAT	no IHDR
 *  71	Formatter::read_acf_befoer_IDAT another IHDR
 *  73	Formatter::read_acf_befoer_IDAT no IDAT
 *  74	Formatter::read_acf_befoer_IDAT unknown chunk
 *  75	Formatter::read_acf_after_IDAT	bad crc
 *  76	Formatter::read_acf_after_IDAT	another IHDR
 *  78	Formatter::read_chunk		bad alloc
 *  79	Formatter::read_acf_after_IDAT 	unknown chunk
 *  80	Formatter::read_BPRM		unknown vertical_sample
 *  81	Formatter::read_BPRM		unknown vertical_sample
 *  82	Formatter::read_BPRM		unknown sample_format
 *  83	Formatter::read_BPRM		unknown cst_format
 *  84	Formatter::read_APRM		unknown vertical_sample
 *  85	Formatter::write_data		callback_out returns bad bytes
 *  86	Formatter::read_data		callback_in returns bad bytes
 *  90 	HuffmanEnc::get_group		undefined symbol
 * 100	Huffman::set_order		unknown order table
 * 101	Huffman::set_run		unknown run table
 * 102	Huffman::set_error		unknown error table
 * 103	Huffman::set_marker		unknown marker table
 * 104	Huffman::set_tag		unknown tag table
 * 110	Info::set_differer		bad differer
 * 111	Info::normalize			bad parameter of ihdr
 * 112	Info::normalize			bad parameter of APRM
 * 113	Info::normalize			bad parameter of BPRM
 * 120	Referer::init_pref		referer can't constructed
 * 130	Buffer::Buffer			bad alloc
 * 140	Dec::close			can't find EOI
 * 141	Dec::decode_line		early IEND
 * 150	HuffmanDec::get_group		undefined code
 * 160	Core::Core			bad alloc
 * 171	OutCodeBuffer::flush_buffer	callback_out returns bad bytes
 * 180	CodeBuffer::write_byte		callback_out returns bad bytes
 * 190	Lrle::apply_initial_order	RUC defined doubly
 * 200	Distributor::apply_initial_order
 * 					RUC defined doubly
 * 210	Enc::open			null info
 */
class Exception : public std::exception
{
private:
    const char *	message;
    const int		id;

	//07.09.13 - M.Chikyu UNICODE対応
	// 代入演算子は使用不能とする
	Exception& operator=(const Exception& src)
	{return *this;};

public:
	Exception (const char * S = "alla::Exception (liballa exception) is thrown (this is default message, detail unknown)",
		const int i = -1) throw () : message (S), id (i)
	{};

	const char *	what			(void) const throw ()
	{ return message; }

    const int		get_id			(void) const throw ()
	{ return id; }
};
/*---------------------------------------------------------------------------*/
};
#endif //_LIBALLA_ALLA_EXCEPTION_H_
