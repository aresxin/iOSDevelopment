/*!	\file		buffer.h
 *	\brief		*Buffer class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.3
 *	\date		2004.08.25
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_BUFFER_H_
#define _LIBALLA_BUFFER_H_
#include <cstdlib>
#include <cstring>
#include "../include/alla-dev.h"
#include "macro.h"
#include "config.h"
#include "codeword.h"
namespace alla {
/*---------------------------------------------------------------------------*/
class Buffer {
private:
    Buffer				(void);
	//07.09.13 - M.Chikyu UNICODE対応
	const Buffer& operator=(const Buffer&) {return *this;};

protected:
    const Info		info;
    const int		buffer_byte;
    auint8 *		buffer;

    Buffer 				(const Info & info,
					 const int buffer_byte);
    virtual ~Buffer			(void);
};
/*---------------------------------------------------------------------------*/
class ImageBuffer : public Buffer
{
public:
#ifndef VC6
    template<typename T> void	
			set_outfield	(auint8 * outfield,
					 Type2Type<T>);
    template<typename T> void	
			fill_outfield	(Type2Type<T>);
    template<typename T> void	
			set_pend	(const T v);
#else
    void		set_outfield	(auint8 * outfield,
					 Type2Type<auint64>);
    void		set_outfield	(auint8 * outfield,
					 Type2Type<auint32>);
    void		set_outfield	(auint8 * outfield,
					 Type2Type<auint16>);
    void		set_outfield	(auint8 * outfield,
					 Type2Type<auint8>);
    void		fill_outfield	(Type2Type<auint64>);
    void		fill_outfield	(Type2Type<auint32>);
    void		fill_outfield	(Type2Type<auint16>);
    void		fill_outfield	(Type2Type<auint8>);
    void		set_pend	(const auint64 v);
    void		set_pend	(const auint32 v);
    void		set_pend	(const auint16 v);
    void		set_pend	(const auint8  v);
#endif
    template<typename T> T
			get_outfield	(Type2Type<T>) const
					    { return *(T *)outfield; }
    void		set_outfield	(auint8 * o,
					 const int component);
    void		fill_outfield	(const int component);
    auint8 *		get_pcur	(void) const
					    { return pcur; }
    auint8 *		get_pupp	(void) const
					    { return pupp; }
    auint8 *		get_pvap	(void) const
					    { return pvap; }
protected:
    const int		coding_buffer_byte;
    auint8 *		pcur;
    auint8 *		pupp;
    auint8 *		pend;
    auint8 *		pvap;
    auint8 *		pio;
    auint8		outfield[COMPONENT_MAX];

    ImageBuffer				(const Info & info,
					 const bool need_another_pio);
    void		swap		(void);
    int			get_sampling_pattern (void) const;
};

class InImageBuffer : public ImageBuffer
{
public:
    InImageBuffer			(const Info & info);
    void		read_line	(const int line_phase);
private:
    void		cst		(void);
    void		downsample_21	(void);
    void		downsample_12	(const int line_phase);
    void		downsample_22	(const int line_phase);
    void		downsample_121	(void);
    void		downsample_112	(const int line_phase);
    void		downsample_122	(const int line_phase);
    void		downsample_221	(void);
    void		downsample_212	(const int line_phase);
    void		downsample_222	(const int line_phase);
};

class OutImageBuffer : public ImageBuffer
{
public:
    OutImageBuffer			(const Info & info);
    void		copy_line	(void);
    void		write_line	(const int next_line_phase);
private:
    void		cst		(void);
    void		upsample_21	(void);
    void		upsample_12	(const int next_line_phase);
    void		upsample_22	(const int next_line_phase);
    void		upsample_121	(void);
    void		upsample_112	(const int next_line_phase);
    void		upsample_122	(const int next_line_phase);
    void		upsample_221	(void);
    void		upsample_212	(const int next_line_phase);
    void		upsample_222	(const int next_line_phase);
};
/*---------------------------------------------------------------------------*/
class CodeBuffer : public Buffer
{
public:
    int			get_code_byte (void) const
					{ return code_byte; }
protected:
    auint8 *		pstart;
    auint8 *		plook;
    auint8 *		pend;
    int			code_byte;
    auint32		cache;
    int			cache_bit;
    int			io_byte;

    CodeBuffer				(const Info & info,
					 const int buffer_byte);
    auint32		read_2bytes	(void);
    void		write_byte	(const auint8 data);
    void		write_bytes	(const auint32 data);
    int			get_code_buffer_byte (void) const
					{ return buffer_byte - sizeof (int); }
};

class InCodeBuffer : public CodeBuffer
{
public:
    InCodeBuffer			(const Info & info,
					 const int buffer_byte);
    auint32		read_bit_1	(void);
    auint32		read_bit_upto16 (const int bits);
    void		write_back_bit	(const int bits);
    void		expire_rest_bit	(void);
    int			read_rest_code	(void * ptr);
    int			get_rest_code_byte (void) const
					{ return (io_byte - code_byte) +
						    cache_bit / 8; }
};

class OutCodeBuffer : public CodeBuffer
{
public:
    OutCodeBuffer			(const Info & info,
					 const int buffer_byte);
    void		write_bit	(const int bits,
					 const auint32 code);
    void		fill_rest_bit	(void);
    int			flush_buffer	(void);
};
/*---------------------------------------------------------------------------*/
// templates
#define SET_OUTFIELD(T)							\
{									\
    *(T*)outfield = *(T*)o;						\
    fill_outfield (Type2Type<T>());					\
}

#define FILL_OUTFIELD(T)						\
{									\
    T * p = (T *)buffer;						\
    T *pp = (T *)(buffer + coding_buffer_byte);				\
    while (p < pp)							\
	*p++ = *(T *)outfield;						\
}

#define SET_PEND(T)							\
{									\
    *(T *)pend = v;							\
}

#ifndef VC6
template<typename T> void ImageBuffer::
set_outfield (auint8 * o,
	      Type2Type<T>)
{
    SET_OUTFIELD(T)
}

template<typename T> void ImageBuffer::
fill_outfield (Type2Type<T>)
{
    FILL_OUTFIELD(T)
}

template<typename T> void ImageBuffer::
set_pend (const T v)
{
    SET_PEND(T)
}
#endif
/*---------------------------------------------------------------------------*/
// inlines
INLINE auint32 CodeBuffer::
read_2bytes (void)
{
    const int rest ((int)(pend - plook));
    code_byte += 2;
    if (rest >= 2) {
	plook += 2;
	return (plook[-2] << 8) | plook[-1];
    }
    io_byte += (* info.sys.callback_in) (pstart, get_code_buffer_byte (),
					    info.sys.userdata_in);
    if (!rest) {
	plook = pstart + 2;
	return ((pstart[0] << 8) | pstart[1]);
    } else {
	plook = pstart + 1;
	return ((pend[-1] << 8) | pstart[0]);
    }
}

#define CALL_CALLBACK							\
{									\
    const int bytes (get_code_buffer_byte ());				\
    									\
    if ((* info.sys.callback_out) (pstart, bytes, info.sys.userdata_out)\
	    != bytes)							\
	throw Exception							\
	    ("CodeBuffer::write_byte(): callback_out returns bad bytes", 180);\
    io_byte	+= bytes;						\
    plook	= pstart;						\
}

INLINE void CodeBuffer::
write_bytes (const auint32 data)
{
    const int rest ((int)(pend - plook));
    code_byte += 4;
    if (rest > 4) {
	*plook++ = data >> 24;
	*plook++ = data >> 16;
	*plook++ = data >> 8;
	*plook++ = data;
	return;
    }
    switch (rest) {
	case 4: plook[3] = data;
	case 3: plook[2] = data >> 8;
	case 2: plook[1] = data >> 16;
	case 1: plook[0] = data >> 24;
    }
    CALL_CALLBACK;
    switch (rest) {
	case 1: *plook++ = data >> 16;
	case 2:	*plook++ = data >> 8;
	case 3:	*plook++ = data;
    }
}

#define BIT_LONG	(sizeof(auint32) * 8)
#define BIT_SHORT	(sizeof(auint16) * 8)
#define BIT_CHAR	(sizeof(auint8) * 8)
INLINE auint32 InCodeBuffer::
read_bit_1 (void)
{
    return (cache >> --cache_bit) & 1;
}

INLINE auint32 InCodeBuffer::
read_bit_upto16 (const int bits)	// in fact, 17bit can be acceptable
{
    // pack to right hand side
    cache_bit	-= bits;
    if (cache_bit >= 0)
	return (cache >> cache_bit) & ((1U << bits) - 1);
    cache	= (cache << BIT_SHORT) | read_2bytes ();
    cache_bit	+= BIT_SHORT;
    return (cache >> cache_bit) & ((1U << bits) - 1);
}

INLINE void InCodeBuffer::
write_back_bit (const int bits)
{
    // assume right code was returned
    cache_bit	+= bits;		// cashe_bit <= 32
}

INLINE void OutCodeBuffer::
write_bit (const int bits,
	   const auint32 code)
{
    DPRINT (stderr, "(%d ", bits);
    DPRINT (stderr, "%x) ", code);

    int	len (BIT_LONG - bits - (cache_bit & 0x1f));
    cache_bit += bits;

    if (len > 0) {
	cache |= (code << len);
	return;
    }
    write_bytes (cache | (code >> -len));
    // add 0x1f mask to ignore 32bit left shift (04.08.25)
    cache = (auint32)((code & ((1 << -len) - 1)) << ((BIT_LONG + len) & 0x1f));
}
#undef	BIT_LONG
#undef	BIT_SHORT
#undef	BIT_CHAR
/*---------------------------------------------------------------------------*/
}
#endif	//_LIBALLA_BUFFER_H_
