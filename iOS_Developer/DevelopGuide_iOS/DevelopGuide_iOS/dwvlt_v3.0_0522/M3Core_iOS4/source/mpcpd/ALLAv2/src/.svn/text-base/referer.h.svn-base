/*!	\file		referer.h
 *	\brief		Referer, Predictor and Distributor class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_REFERER_H_
#define _LIBALLA_REFERER_H_
#include <memory>
#include "../include/alla-dev.h"
#include "buffer.h"
#include "config.h"
#include "macro.h"
namespace alla {
/*---------------------------------------------------------------------------*/
class Referer {
public:
    enum Type {	noinuse, basic, statical, ruc };

    void		init_pref		(ImageBuffer * buf,
						 const int encode_byte);
    prediction		get_name		(void) const
						{ return name; }
    void		set_type		(const Type & type);
    void		set_name		(const prediction name);

private:
    Referer					(void);

	//07.09.13 - M.Chikyu UNICODE対応
	// 代入演算子は使用しない
	const Referer& operator=(const Referer&) {return *this;};

protected:
    auint8 *		pref;
    auint8 *		pcur;
    const Info		info;
    prediction		name;
    int			tag_mask;
    Type		type;
    auint8		ructab[COMPONENT_MAX * 2];

    Referer					(const Info & info);
    virtual ~Referer				(void);
};
/*---------------------------------------------------------------------------*/
class Predictor : public Referer {
public:
    Predictor					(const Info & info);
    ~Predictor					(void) {};
    auint8		get_line_end		(void) const;
#ifndef VC6
    template<typename T> T
			look_error		(const int offset_byte,
						 Type2Type<T>);
    template<typename T> int		
			look_run		(const int offset,
						 Type2Type<T>);
    template<typename T> void
			set_ructab		(const int offset,
						 Type2Type<T>);
#else
    auint64 		look_error		(const int offset_byte,
						 Type2Type<auint64>);
    auint32 		look_error		(const int offset_byte,
						 Type2Type<auint32>);
    auint16 		look_error		(const int offset_byte,
						 Type2Type<auint16>);
    auint8 		look_error		(const int offset_byte,
						 Type2Type<auint8>);
    int			look_run		(const int offset,
						 Type2Type<auint64>);
    int			look_run		(const int offset,
						 Type2Type<auint32>);
    int			look_run		(const int offset,
						 Type2Type<auint16>);
    int			look_run		(const int offset,
						 Type2Type<auint8>);
    void		set_ructab		(const int offset,
						 Type2Type<auint64>);
    void		set_ructab		(const int offset,
						 Type2Type<auint32>);
    void		set_ructab		(const int offset,
						 Type2Type<auint16>);
    void		set_ructab		(const int offset,
						 Type2Type<auint8>);
#endif
};
/*---------------------------------------------------------------------------*/
class Distributor : public Referer {
public:
    Distributor					(const Info & info);
    ~Distributor				(void) {};
    void		distribute_run		(const int offset_byte,
						 const int run_byte);
    void		distribute_error	(const int offset,
						 auint8 const * error);
    void		set_ructab		(const int offset);

};
/*---------------------------------------------------------------------------*/
// Predictor
INLINE Predictor::
Predictor (const Info & info)
    : Referer (info)
{
}

INLINE auint8 Predictor::
get_line_end (void) const
{
    return pref[info.sys.coding_width * info.sys.coding_component];
}

INLINE static auint8
differ (auint8 p,
	auint8 t,
	differing d)
{
    if (d == exor)
	return (t ^ p);
    else if (d == sub)
	return (t - p);
    else	// raw
	return t;
}

INLINE static void
differ (auint8 * err,
	auint8 const * pred,
	auint8 const * tgt,
	differing d,
	const int component)
{
    if (d == sub) {
	switch (component) {
	    case 7: *err++ = *tgt++ - *pred++;
	    case 6: *err++ = *tgt++ - *pred++;
	    case 5: *err++ = *tgt++ - *pred++;
	    case 4: *err++ = *tgt++ - *pred++;
	    case 3: *err++ = *tgt++ - *pred++;
	    case 2: *err++ = *tgt++ - *pred++;
	    case 1: *err++ = *tgt++ - *pred++;
	}
	return;
    } else if (d == exor) {
	switch (component) {
	    case 7: *err++ = *tgt++ ^ *pred++;
	    case 6: *err++ = *tgt++ ^ *pred++;
	    case 5: *err++ = *tgt++ ^ *pred++;
	    case 4: *err++ = *tgt++ ^ *pred++;
	    case 3: *err++ = *tgt++ ^ *pred++;
	    case 2: *err++ = *tgt++ ^ *pred++;
	    case 1: *err++ = *tgt++ ^ *pred++;
	}
	return;
    } else if (d == raw) {
	switch (component) {
	    case 7: *err++ = *tgt++;
	    case 6: *err++ = *tgt++;
	    case 5: *err++ = *tgt++;
	    case 4: *err++ = *tgt++;
	    case 3: *err++ = *tgt++;
	    case 2: *err++ = *tgt++;
	    case 1: *err++ = *tgt++;
	}
	return;
    }
}

#define LOOK_ERROR(T)							\
{									\
    if (! info.ihdr.tag_bit) {						\
	const int	offset_byte (o * sizeof (T));			\
	T		retval;						\
	differ ((auint8 *)(&retval), pref + offset_byte,		\
		pcur + offset_byte, info.aprm.image_differing,		\
		info.sys.component);					\
	return retval;							\
    } else {								\
	const int	offset_byte (o * sizeof (T));			\
	T		retval;						\
	auint8 const *	pred	= pref + offset_byte;			\
	auint8 const *	target	= pcur + offset_byte;			\
	auint8 *	pret	= (auint8 *)(&retval);			\
	const int	compo (info.sys.component - 1);			\
	if (info.ihdr.tag_position == head)				\
	    *pret++ = differ (*pred++, *target++, info.aprm.tag_differing) &\
			tag_mask;					\
	differ (pret, pred, target, info.aprm.image_differing, compo);	\
	if (info.ihdr.tag_position == tail)				\
	    pret[compo] = differ (pred[compo], target[compo],		\
				    info.aprm.tag_differing) & tag_mask;\
	return retval;							\
    }									\
}

#ifndef VC6
template<typename T> INLINE T Predictor::
look_error (const int o,
	    Type2Type<T>)
{
    LOOK_ERROR(T)
}
#else
INLINE auint64 Predictor::
look_error (const int o,
	    Type2Type<auint64>)
{
    LOOK_ERROR(auint64)
}
INLINE auint32 Predictor::
look_error (const int o,
	    Type2Type<auint32>)
{
    LOOK_ERROR(auint32)
}
INLINE auint16 Predictor::
look_error (const int o,
	    Type2Type<auint16>)
{
    LOOK_ERROR(auint16)
}
INLINE auint8 Predictor::
look_error (const int o,
	    Type2Type<auint8>)
{
    LOOK_ERROR(auint8)
}
#endif
#undef LOOK_ERROR

#define LOOK_RUN(T)							\
{									\
    T const * 		pp = (T *)pcur + offset;			\
    T const * const 	ps = pp;					\
    switch (type) {							\
	case basic: 							\
	    {								\
		T const *	p  = (T *)pref + offset;		\
		while (*p == *pp) {					\
		    p++; pp++;						\
		}							\
	    }								\
	    break;							\
	case statical:							\
	    {								\
		const T		v (*((T *)pref + offset));		\
		while (v == *pp) {					\
		    pp++;						\
		}							\
	    }								\
	    break;							\
	case ruc:							\
	    {								\
		const T		v (*((T *)ructab) == *((T *)pref + offset) ?\
				    *((T *)ructab+1) : *((T *)ructab));	\
		while (v == *pp) {					\
		    pp++;						\
		}							\
	    }								\
	    break;							\
	case noinuse:							\
	    return 0;							\
    }									\
    return (int)(pp - ps);						\
}

#ifndef VC6
template<typename T> INLINE int Predictor::
look_run (const int offset,
	  Type2Type<T>)
{
    LOOK_RUN(T)
}
#else
INLINE int Predictor::
look_run (const int offset,
	  Type2Type<auint64>)
{
    LOOK_RUN(auint64)
}
INLINE int Predictor::
look_run (const int offset,
	  Type2Type<auint32>)
{
    LOOK_RUN(auint32)
}
INLINE int Predictor::
look_run (const int offset,
	  Type2Type<auint16>)
{
    LOOK_RUN(auint16)
}
INLINE int Predictor::
look_run (const int offset,
	  Type2Type<auint8>)
{
    LOOK_RUN(auint8)
}
#endif
#undef LOOK_RUN

#define SET_RUCTAB(T)							\
{									\
    if (type != ruc) return;						\
    *((T *)ructab)	= *((T *)ructab+1);				\
    *((T *)ructab+1)	= *((T *)pcur+offset);				\
}

#ifndef VC6
template<typename T> INLINE void Predictor::
set_ructab (const int offset,
	    Type2Type<T>)
{
    SET_RUCTAB(T)
}
#else
INLINE void Predictor::
set_ructab (const int offset,
	    Type2Type<auint64>)
{
    SET_RUCTAB(auint64)
}
INLINE void Predictor::
set_ructab (const int offset,
	    Type2Type<auint32>)
{
    SET_RUCTAB(auint32)
}
INLINE void Predictor::
set_ructab (const int offset,
	    Type2Type<auint16>)
{
    SET_RUCTAB(auint16)
}
INLINE void Predictor::
set_ructab (const int offset,
	    Type2Type<auint8>)
{
    SET_RUCTAB(auint8)
}
#endif
#undef SET_RUCTAB
/*---------------------------------------------------------------------------*/
// Distributor
INLINE Distributor::
Distributor (const Info & info)
    : Referer (info)
{
}

INLINE void Distributor::
distribute_run (const int offset_byte,
		const int run_byte)
{
    auint8 *		pp = pcur + offset_byte;
    auint8 * const 	pe = pp   + run_byte;
    switch (type) {
	case basic:
	    {
		auint8 *	p = pref + offset_byte;
		while (pp < pe) *pp++ = *p++;
	    }
	    break;
	case statical:
	    {
		auint8 * const p = pref + offset_byte;
		while (pp < pe)
		    for (int i = 0; i < info.sys.component; i++)
			*pp++ = p[i];
	    }
	    break;
	case ruc:
	    {
		auint8 * p = (memcmp ((char const *)pref + offset_byte,
			    (char const *)ructab, info.sys.component)) ?
				ructab : ructab + COMPONENT_MAX;
		while (pp < pe) {
		    for (int i = 0; i < info.sys.component; i++)
			*pp++ = p[i];
		}
	    }
	    break;
	case noinuse:
	    throw Exception ("Distributor::distribute_run(): stated is no in use", 200);
	    break;
    }
}

// general, pixel by pixel
INLINE static auint8
anti_differ (auint8 p,
	     auint8 e,
	     differing d)
{
    if (d == exor)
	return (p ^ e);
    else if (d == sub)
	return (p + e);
    else	// raw
	return e;
}

// genral, vectorised
INLINE static void
anti_differ (auint8 * tgt,
	     auint8 const * pred,
	     auint8 const * err,
	     differing d,
	     const int component)
{
    if (d == sub) {
	switch (component) {
	    case 7: *tgt++ = *pred++ + *err++;
	    case 6: *tgt++ = *pred++ + *err++;
	    case 5: *tgt++ = *pred++ + *err++;
	    case 4: *tgt++ = *pred++ + *err++;
	    case 3: *tgt++ = *pred++ + *err++;
	    case 2: *tgt++ = *pred++ + *err++;
	    case 1: *tgt++ = *pred++ + *err++;
	}
	return;
    } else if (d == exor) {
	switch (component) {
	    case 7: *tgt++ = *pred++ ^ *err++;
	    case 6: *tgt++ = *pred++ ^ *err++;
	    case 5: *tgt++ = *pred++ ^ *err++;
	    case 4: *tgt++ = *pred++ ^ *err++;
	    case 3: *tgt++ = *pred++ ^ *err++;
	    case 2: *tgt++ = *pred++ ^ *err++;
	    case 1: *tgt++ = *pred++ ^ *err++;
	}
	return;
    } else if (d == raw) {
	switch (component) {
	    case 7: *tgt++ = *err++;
	    case 6: *tgt++ = *err++;
	    case 5: *tgt++ = *err++;
	    case 4: *tgt++ = *err++;
	    case 3: *tgt++ = *err++;
	    case 2: *tgt++ = *err++;
	    case 1: *tgt++ = *err++;
	}
	return;
    }
}

INLINE void Distributor::
distribute_error (const int o,
		  auint8 const * error)
{
    const int offset_byte (o * info.sys.component);
    if (!info.ihdr.tag_bit) {
	anti_differ (pcur + offset_byte,
		     pref + offset_byte, error,
		     info.aprm.image_differing, info.sys.component);
    } else {
	auint8 const *	pred	= pref + offset_byte;
	auint8 *	target	= pcur + offset_byte;
	const int	compo (info.sys.component - 1);
	if (info.ihdr.tag_position == head)
	    *target++ = anti_differ (*pred++, *error++,
					info.aprm.tag_differing) & tag_mask;
	anti_differ (target, pred, error, info.aprm.image_differing, compo);
	if (info.ihdr.tag_position == tail)
	    target[compo] = anti_differ (pred[compo], error[compo],
					 info.aprm.tag_differing) & tag_mask;
    }
}

INLINE void Distributor::
set_ructab (const int offset)
{
    if (type != ruc) return;
    auint8 * const second = ructab + COMPONENT_MAX;
    memcpy (ructab, second, info.sys.component);
    memcpy (second, pcur + offset * info.sys.component,
		info.sys.component);
}
/*---------------------------------------------------------------------------*/
}
#endif	//_LIBALLA_REFERER_H_
