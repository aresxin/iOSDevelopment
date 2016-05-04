/*!	\file		alla-dev.h
 *	\brief		ALLAv2 libarary, developer interface
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef	_LIBALLA_ALLA_DEV_H_
#define	_LIBALLA_ALLA_DEV_H_
#include <cstdio>

// 09.07.14 - M.Chikyu WindowsMobile対応
#ifdef _M3CORE_MP_
#undef CALLBACK
#endif //_M3CORE_MP_

#include "alla.h"

namespace alla {
/*---------------------------------------------------------------------------*/
// Dummy Definitions
class LrleEnc;
class LrleDec;
class HuffmanEnc;
class HuffmanDec;
class Crc32;
class Info;
class Exception;
struct Chunk;

typedef void (* APP_CALLBACK) (const void * ptr, const int byte);
typedef void (* CHUNK_CALLBACK) (const Chunk & chunk);
/*---------------------------------------------------------------------------*/
// Constants
const int	COMPONENT_MAX	= 7;
const int	CODE_BUF_BYTE	= 1024;
const int	OUTFIELD	= 0;

enum common {	common_default=0, crc_cancell=0 };
enum prediction	{
		 A=0x01,  Z2=0x02,  Z3=0x03,  Z4=0x04,
		 Z5=0x05,  Z6=0x06,  Z7=0x07,  Z8=0x08,
		 Z9=0x09, Z10=0x0a, Z11=0x0b, Z12=0x0c,
		Z13=0x0d, Z14=0x0e, Z15=0x0f, Z16=0x10,
		Z17=0x11, Z18=0x12, Z19=0x13, Z20=0x14,
		Z21=0x15, Z22=0x16, Z23=0x17, Z24=0x18,
		Z25=0x19, Z26=0x1a, Z27=0x1b, Z28=0x1c,
		Z29=0x1d, Z30=0x1e, Z31=0x1f, Z32=0x20,
		  C=0x80,   B=0x81,   D=0x82,   E=0x83,
		  F=Z8,   RUC=0xf0, VAP=0xf1,
		prediction_noinuse = 0xff, prediction_num=5,
		prediction_lmargin=32, prediction_rmargin=3 };
enum differing {
		sub=1, exor=2, raw=3,
		differing_image=sub, differing_tag=exor};
enum huffmanTable {
		graphic=1, image=2, binary=3, through=4, ver1=5,
		ver2=6,
		bit1, bit2, bit3,
		huffmanTable_order=graphic,
		huffmanTable_run=graphic,
		huffmanTable_error=graphic,
		huffmanTable_marker=ver2,
		huffmanTable_runmax_graphic=17057,
		huffmanTable_runmax_scan=1040 };
enum format {	tail=0, head=1,
		no_sample=0, big_format=1, small_format=2 };
enum cst {	no_cst=0, rgb_ycc=1, bgr_ycc=2 };
enum marking {	DHT, EOL, EOI, RAW, CPY, FIL, APP, EOB,
		marking_v2_num=8, marking_v1_num=3, no_marker=-1 };
enum ordering {	first=0, second=1, third=2, fourth=3, fifth=4, diff=5,
		marker=6, ordering_num=7 };
enum chunk {	IHDR, APRM, BPRM, IDAT, IEND, sPRm, rPRm, aTXt, pHYS };
enum req {	req_initial_order=0x01000000, req_run_max=0x02000000,
		req_z_offset=0x04000000, req_differing=0x08000000,
		req_diff_base=0x10000000, req_htable=0x20000000,
		req_eol=0x40000000,
		req_ver1_marker=0x00000001, req_raw=0x00000002,
		req_cpy=0x00000004, req_fil=0x00000008,
		req_app=0x00000010, req_eob=0x00000020,
		req_outfield=0x00000040, req_h_sample=0x00000080,
		req_v_sample=0x00000100, req_big_format=0x00000200,
		req_cst=0x00000400, req_ruc=0x00000800,
		req_vap=0x00001000, req_idat_crc=0x00002000,
		basic_req_reserved=0x80000000,
		extended_req_reserved=0x00ffc000 };
enum chunk_req {
		BPRM_chunk=0x01000000, IDAT_bytes_unknown=0x02000000,
		sPRm_chunk=0x00000001, rPRm_chunk=0x00000002,
		aTXt_chunk=0x00000004, pHYS_chunk=0x00000008,
		chunk_req_reserved=0xfe000000,
		chunk_option_reserved=0x00fffff0 };
/*---------------------------------------------------------------------------*/
// Cores
struct Symbol {
    int			order;
    union {
	int		run;
	auint8	 	error[COMPONENT_MAX];
	marking		marker;
    }			side_info;
};

template<int v> struct Int2Type
{
    enum { value = v };
};

template<typename T> struct Type2Type
{
    typedef T OriginalType;
};

class Core {
public:
    Core				(const Info & info);
    virtual	~Core			(void);
protected:
    Info *	alla_info;
    int		current_line;

    void	set_buffer_info		(void * ptr);
    void	normalize_alla_info	(void);
    virtual void
		set_huffman_info	(void * ptr) = 0;
private:
    Core				(void);
    Core				(const Core &);
    int		get_right_margin	(void) const;
    int		get_left_margin		(void) const;
    int		get_total_margin	(void) const;
};

class CoreEnc : public Core {
public:
    CoreEnc				(Info & info);
    ~CoreEnc				(void);
    int		encode_line		(const marking marker = no_marker,
					 const void * side = NULL);
    int		insert_marker		(const marking marker,
					 const char * msg = NULL);
    int		terminate		(const marking marker = EOI,
					 const bool is_raw = false);
private:
    LrleEnc *	lrle;
    HuffmanEnc *
		huffman;

    void	set_huffman_info	(void * ptr);
    void	encode_marker_terminating_run
					(const marking marker);
#ifndef VC6
    template<typename T> int	
		encode_line_internal	(bool is_raw);
#else
    int		encode_line_internal	(bool is_raw,
					 Type2Type<auint64>);
    int		encode_line_internal	(bool is_raw,
					 Type2Type<auint32>);
    int		encode_line_internal	(bool is_raw,
					 Type2Type<auint16>);
    int		encode_line_internal	(bool is_raw,
					 Type2Type<auint8>);
#endif
};

class CoreDec : public Core {
public:
    CoreDec				(Info & info);
    ~CoreDec				(void);
    int		decode_line		(void);
    int		terminate		(void);
    void	set_read_APP		(APP_CALLBACK func);
    int		get_rest_byte		(void) const;
    int		read_rest		(void * ptr);
private:
    LrleDec *	lrle;
    HuffmanDec *
		huffman;
    APP_CALLBACK
		read_APP;

    void	set_huffman_info	(void * ptr);
    int		feed_marker		(const marking marker,
					 const int i);
    int		decode_line_internal	(void);
};
/*---------------------------------------------------------------------------*/
// Info
struct BufferInfo {
    int			left_margin;
    int			total_margin;
    int			io_component;
    int			io_line_byte;
    int			code_buf_byte;
};

struct HuffmanInfo {
    int			order_dcw_entry;
    int			run_dcw_entry;
    int			error_dcw_entry;
    int			marker_dcw_entry;
    int			tag_dcw_entry;
};

struct Sys {
    CALLBACK		callback_in;
    void * 		userdata_in;
    CALLBACK		callback_out;
    void * 		userdata_out;
    int			component;
    int			coding_component; // not equals to component of encoder
    int			coding_width;
    int			coding_line_byte;
    HuffmanInfo		huffman;
    BufferInfo		buffer;
};

struct Ihdr {
    auint32		req;
    auint32		chunk_req;
    int			width;
    int			height;
    int			image_bit;
    int			tag_bit;
    format		tag_position;
    color_space		cspace;
};

struct Aprm {
    int			runmax;
    prediction		referer[prediction_num];
    int			differer;
    differing		image_differing;
    differing		tag_differing;
    huffmanTable	run_huffmanTable;
    huffmanTable	error_huffmanTable;
    huffmanTable	marker_huffmanTable;
    auint8		tag_outfield;
    auint8		image_outfield;
};

struct Bprm {
    int			horizontal_sample;
    int			vertical_sample;
    format		sample_format;
    cst			cst_format;
};

class Info {
public:
    Sys		sys;
    Ihdr	ihdr;
    Aprm	aprm;
    Bprm	bprm;

    Info 				(void);
    ~Info 				(void) {};
    void	set_callbacks		(CALLBACK in_callback,
					 void * in_userdata,
    					 CALLBACK out_callback,
					 void * out_userdata);
    void	set_image_profile	(const int	width,
					 const int	height,
					 const int	image_bit);
    void	set_tag_profile		(const int	tag_bit,
					 const format	tag_positon);
    void	set_color_space		(const color_space space);
    void	set_huffman		(const huffmanTable run,
					 const huffmanTable error
						 = huffmanTable_error,
					 const huffmanTable marker
						 = huffmanTable_marker);
    void	set_initial_order	(const prediction
						preds[prediction_num]);
    void	set_differer		(const int order);
    void	set_outfield		(const auint8 image);
    void	set_outfield		(const auint8 image,
					 const auint8 tag);
    void	set_runmax		(const int runmax);
    void	set_differing		(const differing image,
					 const differing tag);
    void	set_sample_rate		(const int horizontal,
					 const int vertical = 1);
    void	set_sample_format	(const format form);
    void	set_cst			(const cst cst_format);
    void	set_aprm		(const Aprm & aprm);
    void	set_bprm		(const Bprm & bprm);
    void	normalize		(void);
    void	enable_marker		(const marking marker);
    void	enable_all_marker	(void);
    void	enable_chunk		(const chunk id);
    void	enable_IDAT_bytes_unknown
					(void);
    char const *
		get_version		(void) const;
    int		get_component		(void) const;
    int		get_io_line_byte	(void) const;
    int		get_io_component	(void) const;
private:
    int		get_coding_width	(void) const;
};
/*---------------------------------------------------------------------------*/
// Formatter
class Formatter {
public:
    Formatter				(Info & info);
    ~Formatter				(void);
    void	write_ala_header	(void);
    void	write_acf_before_IDAT	(void);
    void	write_acf_after_IDAT	(void);
    Info	read_ala_header		(void);
    Info 	read_acf_before_IDAT	(void);
    Info	read_acf_after_IDAT	(const auint32 calced_crc);
    void	set_read_sPRm		(CHUNK_CALLBACK func);
    void	set_read_rPRm		(CHUNK_CALLBACK func);
    void	set_read_aTXt		(CHUNK_CALLBACK func);
    void	set_read_pHYS		(CHUNK_CALLBACK func);
    bool	get_is_iend		(void) const { return is_iend; }
private:
    Info 	alla_info;
    Crc32 *	crc;
    CHUNK_CALLBACK
		read_sPRm;
    CHUNK_CALLBACK
		read_rPRm;
    CHUNK_CALLBACK
		read_aTXt;
    CHUNK_CALLBACK
		read_pHYS;
    bool	is_iend;

    Formatter				(void) {};
    auint32	calc_crc		(const auint8 * data,
					 const int size,
					 const auint8 * initial_value
								     = NULL);
    int		write_long		(const auint32 data);
    int		write_data		(void * data,
					 const int bytes);
    auint32	read_long		(void);
    int		read_data		(void * data,
					 int bytes);
    void 	write_chunk		(Chunk & chunk);
    void	write_IHDR		(void);
    void	write_APRM		(void);
    void	write_BPRM		(void);
    void	write_pre_IDAT		(void);
    void	write_post_IDAT		(void);
    void	write_IEND		(void);
    int		read_chunk		(void);
    void	read_IHDR		(const Chunk & chunk);
    void	read_APRM		(const Chunk & chunk);
    void	read_BPRM		(const Chunk & chunk);
};
/*---------------------------------------------------------------------------*/
};	// namespace alla
#endif	//_LIBALLA_ALLA_DEV_H_
