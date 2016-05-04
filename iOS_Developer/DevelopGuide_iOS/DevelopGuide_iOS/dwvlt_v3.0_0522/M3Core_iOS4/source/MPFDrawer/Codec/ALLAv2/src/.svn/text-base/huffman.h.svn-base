/*!	\file		huffman.h
 *	\brief		Huffman* class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.2-woexception-0
 *	\date		2004.08.04
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
ALLA_NAMESPACE_BEGIN
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

template<class DCW, class BUFFER>
class Huffman {
public:
    virtual ~Huffman			(void);
    void		set_order	(Status *	status,
					 const huffmanTable h);
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
    Huffman				(Status *	status,
					 const Info &	info);
    void		set_run		(Status *	status);
    void		set_error	(Status *	status);
    void		set_marker	(Status *	status);
    void		set_tag		(Status *	status);
};

class HuffmanEnc : public Huffman<DirectCodewordEnc, OutCodeBuffer> {
public:
    HuffmanEnc				(Status *	status,
					 const Info &	info);
    ~HuffmanEnc				(void);
    void		encode_run	(Status *	status,
					 const int,
					 const int);
    void		encode_error	(Status *	status,
					 auint8 const *	error);
    void		encode_tag	(Status *	status,
					 const auint8);
    void		encode_marker	(Status *	status,
					 const auint8);
    void		encode_very_raw	(Status *	status,
					 const auint8 * data);
    void		encode_very_raw	(Status *	status,
					 const auint8 * data,
					 int byte);
    void		examine_dht	(Status *	status);
    int			terminate	(Status *	status);
    void		fill_rest_bit	(Status *	status)
				{ codebuffer.fill_rest_bit (status); }
private:
    int			get_group	(Status *		status,
					 Codeword const *	codeword,
					 const int		value,
					 const int		limit) const;
    void		set_direct_code	(Status *		status);
    void		set_direct_code_internal
					(Status *		status,
					 CodewordTable *	cwt);
    void		write_code	(Status *		status,
					 const CodewordTable &	cwt,
					 const int		value);
    void		write_direct_code
					(Status *			status,
					 const DirectCodewordEnc &	dcw);
    void		write_direct_code
					(Status *			status,
					 const DirectCodewordEnc &	dcw1,
					 const DirectCodewordEnc &	dcw2);
};

class HuffmanDec : public Huffman<DirectCodewordDec, InCodeBuffer> {
public:
    HuffmanDec				(Status *	status,
					 const Info & info);
    ~HuffmanDec				(void);
    void		apply_dht	(Status *	status);
    void		decode_symbol	(Symbol *	symbol);
    void		decode_very_raw	(auint8 *	data,
					 int	 	byte);
    void		decode_very_raw	(auint8 *	data);
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
    DirectCodewordDec	get_group	(Status *		status,
					 const auint32		code,
					 const int		limit,
					 Codeword const *	cw);
    void		set_direct_code	(Status *		status);
    void		set_direct_code_internal
					(Status *		status,
					 CodewordTable *	cwt);
};
/*---------------------------------------------------------------------------*/
// templates
template<class D, class B>
Huffman<D, B>::
Huffman (Status *	status,
	 const Info &	info_)
    : info (info_),
      codebuffer (status, info_, info_.sys.buffer.code_buf_byte),
      dht_count (0)
{
    set_order  (status, graphic);
    if (IS_BAD (*status))	return;
    set_run    (status);
    if (IS_BAD (*status))	return;
    set_error  (status);
    if (IS_BAD (*status))	return;
    set_tag    (status);
    if (IS_BAD (*status))	return;
    set_marker (status);
}

template<class D, class B>
Huffman<D, B>::
~Huffman (void)
{
}

template<class D, class B>
void Huffman<D, B>::
set_order (Status *		status,
	   const huffmanTable	h)
{
    switch (h) {
	case graphic:	order_tab.cw = cw_order_graphics;	break;
	case image:	order_tab.cw = cw_order_image;		break;
	default:
	    THROW (status, "Huffman::set_order(): unknown order table", 100);
	    return;
    }
    order_tab.cw_entry		= entry_cw_order;
    order_tab.dcw_entry		= info.sys.huffman.order_dcw_entry;
    order_tab.minimum_value	= min_cw_order;
    order_tab.dcw.resize (order_tab.dcw_entry);
}

template<class D, class B>
void Huffman<D, B>::
set_run	(Status *	status)
{
    switch (info.aprm.run_huffmanTable) {
	case graphic:	run_tab.cw = cw_run_graphics;		break;
	case image:	run_tab.cw = cw_run_image;		break;
	default:
	    THROW (status, "Huffman::set_run(): unknown run table", 101);
	    return;
    }
    run_tab.cw_entry		= entry_cw_run;
    run_tab.dcw_entry		= info.sys.huffman.run_dcw_entry;
    run_tab.minimum_value	= min_cw_run;
    run_tab.dcw.resize (run_tab.dcw_entry);
}

template<class D, class B>
void Huffman<D, B>::
set_error (Status *	status)
{
    switch (info.aprm.error_huffmanTable) {
	case graphic:	error_tab.cw = cw_error_graphics;	break;
	case image:	error_tab.cw = cw_error_image;		break;
	case binary:	error_tab.cw = cw_error_binary;		break;
	case through:	error_tab.cw = cw_error_through;	break;
	default:
	    THROW (status, "Huffman::set_error(): unknown error table", 102);
	    return;
    }
    error_tab.cw_entry		= entry_cw_error;
    error_tab.dcw_entry		= info.sys.huffman.error_dcw_entry;
    error_tab.minimum_value	= min_cw_error;
    error_tab.dcw.resize (error_tab.dcw_entry);
}

template<class D, class B>
void Huffman<D, B>::
set_marker (Status *	status)
{
    switch (info.aprm.marker_huffmanTable) {
	case ver1:	marker_tab.cw = cw_marker_ver1; 	break;
	case ver2:	marker_tab.cw = cw_marker_ver2; 	break;
	default:
	    THROW (status, "Huffman::set_marker(): unknown marker table", 103);
	    return;
    }
    marker_tab.cw_entry		= entry_cw_marker;
    marker_tab.dcw_entry	= info.sys.huffman.marker_dcw_entry;
    marker_tab.minimum_value	= min_cw_marker;
    marker_tab.dcw.resize (marker_tab.dcw_entry);
}

template<class D, class B>
void Huffman<D, B>::
set_tag (Status *	status)
{
    switch (info.ihdr.tag_bit) {
	case 0:		// go through
	case 1:		tag_tab.cw = cw_tag_bit1; 		break;
	case 2:		tag_tab.cw = cw_tag_bit2; 		break;
	case 3:		tag_tab.cw = cw_tag_bit3; 		break;
	default:
	    THROW (status, "Huffman::set_tag(): unknown tag table", 104);
	    return;
    }
    tag_tab.cw_entry		= entry_cw_tag;
    tag_tab.dcw_entry		= info.sys.huffman.tag_dcw_entry;
    tag_tab.minimum_value	= min_cw_tag;
    tag_tab.dcw.resize (tag_tab.dcw_entry);
}
/*---------------------------------------------------------------------------*/
// inlines
INLINE void HuffmanEnc::
write_direct_code (Status *			status,
		   const DirectCodewordEnc &	dcw)
{
    codebuffer.write_bit (status, dcw.len, dcw.code);
}

INLINE void HuffmanEnc::
write_direct_code (Status *			status,
		   const DirectCodewordEnc &	dcw1,
		   const DirectCodewordEnc &	dcw2)
{
    codebuffer.write_bit (status, dcw1.len + dcw2.len,
			    (dcw1.code << dcw2.len) | dcw2.code);
}

INLINE void HuffmanEnc::
encode_run (Status *	status,
	    const int	o,
	    const int	v)
{
    DPRINT (stderr, "%d/", o);
    DPRINT (stderr, "%d ", v);
    dht_count += !o ? 1 : 0;
    if (v < run_tab.dcw_entry) {
	write_direct_code (status, order_tab.dcw[o], run_tab.dcw[v]);
    } else {
	write_direct_code (status, order_tab.dcw[o]);
	if (IS_BAD (*status))	return;
	write_code (status, run_tab, v);
    }
}

INLINE void HuffmanEnc::
encode_tag (Status *		status,
	    const auint8	v)
{
    write_direct_code (status, tag_tab.dcw[v]);
}

INLINE void HuffmanEnc::
encode_error (Status *		status,
	      auint8 const *	v)
{
    DPRINT (stderr, "error/%x ", v[0]);
    dht_count -= 1;

    std::vector<DirectCodewordEnc> const & dcw	= error_tab.dcw;
    if (! info.ihdr.tag_bit) {
	write_direct_code (status, order_tab.dcw[diff], dcw[*v++]);
	switch (info.sys.component) {
	    case 7:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 5:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 3:	write_direct_code (status, dcw[v[0]], dcw[v[1]]);
	    case 1:	
			return;
	    case 6:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 4:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 2:	write_direct_code (status, dcw[v[0]]);
			return;
	}
    } else {
	write_direct_code (status, order_tab.dcw[diff]);
	if (info.ihdr.tag_position == head)
	    encode_tag   (status, *v++);
	switch (info.sys.component - 1) {
	    case 6:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 4:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 2:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
			break;
	    case 7:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 5:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 3:	write_direct_code (status, dcw[v[0]], dcw[v[1]]); v += 2;
	    case 1:	write_direct_code (status, dcw[*v++]);
			break;;
	}
	if (info.ihdr.tag_position == tail)
	    encode_tag   (status, *v);
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
	    return - (cw.base + in.read_bit_upto16 (cw.addbit_len));
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
ALLA_NAMESPACE_END
#endif	//_LIBALLA_HUFFMAN_H_
