/*!	\file		huffman.h
 *	\brief		Huffman* class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.314
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_HUFFMAN_H_
#define _LIBALLA_HUFFMAN_H_
#include <memory>
#include <vector>
#include "../include/alla-dev.h"
#include "codeword.h"
#include "buffer.h"
#include "config.h"
#include "macro.h"
namespace alla {
/*---------------------------------------------------------------------------*/
enum {		dcode_entry = 256, dht_threshold = 8,
		max_bit_order = 6, max_bit_run = 20, max_bit_error = 12,
		max_bit_tag = 4, max_bit_marker = 7 };

struct DirectCodewordEnc {
    auint16		code;
    auint8		len;
}; 

struct DirectCodewordDec {
    auint8		group;
    auint8		len;
};

template<typename DCW, class BUFFER>
class Huffman {
public:
    virtual ~Huffman			(void);
    void		set_order	(const huffmanTable h);
    int			get_code_byte	(void) const
				    { return codebuffer.get_code_byte (); }
private:
    Huffman				(void);
protected:
    struct CodewordTable {
	int			cw_entry;
	int			dcw_entry;
	int			minimum_value;
	Codeword const *	cw;
	std::vector<DCW>	dcw;
    };

    const Info		info;
    BUFFER		codebuffer;
    CodewordTable	order_tab;
    CodewordTable	run_tab;
    CodewordTable	error_tab;
    CodewordTable 	tag_tab;
    CodewordTable	marker_tab;
    int			dht_count;
    Huffman				(const Info &	info);
    void		set_run		(void);
    void		set_error	(void);
    void		set_marker	(void);
    void		set_tag		(void);
};

class HuffmanEnc : public Huffman<DirectCodewordEnc, OutCodeBuffer> {
public:
    HuffmanEnc				(const Info &	info);
    ~HuffmanEnc				(void);
    void		encode_run	(const int,
					 const int);
    void		encode_error	(auint8 const *	error);
    void		encode_tag	(const auint8);
    void		encode_marker	(const auint8);
    void		encode_very_raw	(const auint8 * data);
    void		encode_very_raw	(const auint8 * data,
					 int byte);
    void		examine_dht	(void);
    int			terminate	(void);
    void		fill_rest_bit	(void)
				{ codebuffer.fill_rest_bit (); }
private:
    int			get_group	(Codeword const * codeword,
					 const int	  value,
					 const int	  limit) const;
    void		set_direct_code	(void);
    void		set_direct_code_internal
					(CodewordTable *	cwt);
    void		write_code	(const CodewordTable &	cwt,
					 const int		value);
    void		write_direct_code
					(const DirectCodewordEnc & dcw);
    void		write_direct_code
					(const DirectCodewordEnc & dcw1,
					 const DirectCodewordEnc & dcw2);
};

class HuffmanDec : public Huffman<DirectCodewordDec, InCodeBuffer> {
public:
    HuffmanDec				(const Info & info);
    ~HuffmanDec				(void);
    void		apply_dht	(void);
    void		decode_symbol	(Symbol * symbol);
    void		decode_very_raw	(auint8 * data,
					 int	  byte);
    void		decode_very_raw	(auint8 * data);
    void		expire_rest_bit	(void)
				{ codebuffer.expire_rest_bit (); }
    int			get_rest_code_byte (void) const
				{ return codebuffer.get_rest_code_byte (); }
    int			read_rest_code	(void * ptr)
				{ return codebuffer.read_rest_code (ptr); }
private:
    int			read_code	(const CodewordTable & ct);
    int			decode_order	(void);
    int			decode_run	(void);
    int			decode_tag	(void);
    void		decode_error	(auint8 * error);
    marking		decode_marker	(void);
    DirectCodewordDec	get_group	(const auint32 code,
					 const int limit,
					 Codeword const * cw);
    void		set_direct_code	(void);
    void		set_direct_code_internal
					(CodewordTable * cwt);
};
/*---------------------------------------------------------------------------*/
// templates
template<typename D, class B>
Huffman<D, B>::
Huffman (const Info &	info_)
    : info (info_),
      codebuffer (info_, info_.sys.buffer.code_buf_byte),
      dht_count (0)
{
    set_order  (graphic);
    set_run    ();
    set_error  ();
    set_tag    ();
    set_marker ();
}

template<typename D, class B>
Huffman<D, B>::
~Huffman (void)
{
}

template<typename D, class B>
void Huffman<D, B>::
set_order (const huffmanTable h)
{
    switch (h) {
	case graphic:	order_tab.cw = cw_order_graphics;	break;
	case image:	order_tab.cw = cw_order_image;		break;
	default: throw Exception ("Huffman::set_order(): unknown order table", 100);
    }
    order_tab.cw_entry		= entry_cw_order;
    order_tab.dcw_entry		= info.sys.huffman.order_dcw_entry;
    order_tab.minimum_value	= min_cw_order;
    order_tab.dcw.resize (order_tab.dcw_entry);
}

template<typename D, class B>
void Huffman<D, B>::
set_run	(void)
{
    switch (info.aprm.run_huffmanTable) {
	case graphic:	run_tab.cw = cw_run_graphics;		break;
	case image:	run_tab.cw = cw_run_image;		break;
	default: throw Exception ("Huffman::set_run(): unknown run table", 101);
    }
    run_tab.cw_entry		= entry_cw_run;
    run_tab.dcw_entry		= info.sys.huffman.run_dcw_entry;
    run_tab.minimum_value	= min_cw_run;
    run_tab.dcw.resize (run_tab.dcw_entry);
}

template<typename D, class B>
void Huffman<D, B>::
set_error (void)
{
    switch (info.aprm.error_huffmanTable) {
	case graphic:	error_tab.cw = cw_error_graphics;	break;
	case image:	error_tab.cw = cw_error_image;		break;
	case binary:	error_tab.cw = cw_error_binary;		break;
	case through:	error_tab.cw = cw_error_through;	break;
	default: throw Exception ("Huffman::set_error(): unknown error table", 102);
    }
    error_tab.cw_entry		= entry_cw_error;
    error_tab.dcw_entry		= info.sys.huffman.error_dcw_entry;
    error_tab.minimum_value	= min_cw_error;
    error_tab.dcw.resize (error_tab.dcw_entry);
}

template<typename D, class B>
void Huffman<D, B>::
set_marker (void)
{
    switch (info.aprm.marker_huffmanTable) {
	case ver1:	marker_tab.cw = cw_marker_ver1; 	break;
	case ver2:	marker_tab.cw = cw_marker_ver2; 	break;
	default: throw Exception ("Huffman::set_marker(): unknown marker table", 103);
    }
    marker_tab.cw_entry		= entry_cw_marker;
    marker_tab.dcw_entry	= info.sys.huffman.marker_dcw_entry;
    marker_tab.minimum_value	= min_cw_marker;
    marker_tab.dcw.resize (marker_tab.dcw_entry);
}

template<typename D, class B>
void Huffman<D, B>::
set_tag (void)
{
    switch (info.ihdr.tag_bit) {
	case 0:		// go through
	case 1:		tag_tab.cw = cw_tag_bit1; 		break;
	case 2:		tag_tab.cw = cw_tag_bit2; 		break;
	case 3:		tag_tab.cw = cw_tag_bit3; 		break;
	default: throw Exception ("Huffman::set_tag(): unknown tag table", 104);
    }
    tag_tab.cw_entry		= entry_cw_tag;
    tag_tab.dcw_entry		= info.sys.huffman.tag_dcw_entry;
    tag_tab.minimum_value	= min_cw_tag;
    tag_tab.dcw.resize (tag_tab.dcw_entry);
}
/*---------------------------------------------------------------------------*/
// inlines
INLINE void HuffmanEnc::
write_direct_code (const DirectCodewordEnc & dcw)
{
    codebuffer.write_bit (dcw.len, dcw.code);
}

INLINE void HuffmanEnc::
write_direct_code (const DirectCodewordEnc & dcw1,
		   const DirectCodewordEnc & dcw2)
{
    codebuffer.write_bit (dcw1.len + dcw2.len,
			    (dcw1.code << dcw2.len) | dcw2.code);
}

INLINE void HuffmanEnc::
encode_run (const int o,
	    const int v)
{
    DPRINT (stderr, "%d/", s.order);
    DPRINT (stderr, "%d ", s.side_info.run);
    dht_count += !o ? 1 : 0;
    if (v < run_tab.dcw_entry) {
	write_direct_code (order_tab.dcw[o], run_tab.dcw[v]);
    } else {
	write_direct_code (order_tab.dcw[o]);
	write_code (run_tab, v);
    }
}

INLINE void HuffmanEnc::
encode_tag (const auint8 v)
{
    write_direct_code (tag_tab.dcw[v]);
}

INLINE void HuffmanEnc::
encode_error (auint8 const * v)
{
    DPRINT (stderr, "error/%x ", *(int *)s.side_info.error);
    dht_count -= 1;

    std::vector<DirectCodewordEnc> const & dcw	= error_tab.dcw;
    if (! info.ihdr.tag_bit) {
	write_direct_code (order_tab.dcw[diff], dcw[*v++]);
	switch (info.sys.component) {
	    case 7:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 5:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 3:	write_direct_code (dcw[v[0]], dcw[v[1]]);
	    case 1:	
			return;
	    case 6:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 4:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 2:	write_direct_code (dcw[v[0]]);
			return;
	}
    } else {
	write_direct_code (order_tab.dcw[diff]);
	if (info.ihdr.tag_position == head)
	    encode_tag   (*v++);
	switch (info.sys.component - 1) {
	    case 6:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 4:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 2:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
			break;
	    case 7:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 5:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 3:	write_direct_code (dcw[v[0]], dcw[v[1]]); v += 2;
	    case 1:	write_direct_code (dcw[*v++]);
			break;;
	}
	if (info.ihdr.tag_position == tail)
	    encode_tag   (*v);
    }
}
/*---------------------------------------------------------------------------*/
INLINE int HuffmanDec::
read_code (const CodewordTable & ct)
{
    InCodeBuffer &		in	= codebuffer;
#ifdef DBG
    const auint32		code 	(in.read_bit_upto16 (major_len_max));
    DirectCodewordDec const &	dcw	= ct.dcw[code];
#else
    DirectCodewordDec const &	dcw	= ct.dcw[in.read_bit_upto16 (major_len_max)];
#endif

    in.write_back_bit (major_len_max - dcw.len);
    const Codeword &		cw 	= ct.cw[dcw.group];
    DPRINT (stderr, "(%d+", dcw.len);
    DPRINT (stderr, "%d,", cw.sign_len + cw.addbit_len);
    DPRINT (stderr, "%x) ", code >> (6 - dcw.len));
    if (!cw.sign_len) {
	if (cw.min >= 0)
	    return (cw.base + in.read_bit_upto16 (cw.addbit_len));
	else
	    return (-1) * (cw.base + in.read_bit_upto16 (cw.addbit_len));
    } else {
	const int sign (1 - 2 * in.read_bit_1 ());
	return (cw.base + in.read_bit_upto16 (cw.addbit_len)) * sign;
    }
}

INLINE marking HuffmanDec::
decode_marker (void)
{
    return (marking)(read_code (marker_tab));
}

INLINE int HuffmanDec::
decode_order (void)
{
    return read_code (order_tab);
}

INLINE int HuffmanDec::
decode_run (void)
{
    return read_code (run_tab);
}

INLINE int HuffmanDec::
decode_tag (void)
{
    return read_code (tag_tab);
}

INLINE void HuffmanDec::
decode_error (auint8 * e)
{
    const CodewordTable & tab = error_tab;
    if (!info.ihdr.tag_bit) {
	for (int i = info.sys.component; i > 0; i--)
	    *e++ = read_code (tab);
    } else {
	if (info.ihdr.tag_position == head)
	    *e++ = decode_tag ();
	for (int i = info.sys.component - 1; i > 0; i--)
	    *e++ = read_code (tab);
	if (info.ihdr.tag_position == tail)
	    *e++ = decode_tag ();
    }
}

INLINE void HuffmanDec::
decode_symbol (Symbol * symbol)
{
    if (IS_DIFF (symbol->order = decode_order ())) {
	decode_error (symbol->side_info.error);
    } else if (IS_HIT (symbol->order)) {
	symbol->side_info.run = decode_run ();
    } else {	// marker
	symbol->side_info.marker = decode_marker ();
    }
}
/*---------------------------------------------------------------------------*/
}
#endif	//_LIBALLA_HUFFMAN_H_
