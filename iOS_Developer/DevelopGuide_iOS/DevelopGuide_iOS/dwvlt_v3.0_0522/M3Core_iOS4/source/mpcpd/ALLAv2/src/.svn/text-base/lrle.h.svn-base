/*!	\file		lrle.h
 *	\brief		Lrle class definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.3
 *	\date		2004.09.01
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_LRLE_H_
#define _LIBALLA_LRLE_H_
#include <memory>
#include "../include/alla-dev.h"
#include "referer.h"
#include "buffer.h"
#include "config.h"
#include "macro.h"
namespace alla {
/*---------------------------------------------------------------------------*/
template<class BUFFER, class REFERER>
class Lrle {
public:
    virtual ~Lrle				(void);
    void		apply_initial_order	(void);
    virtual void	apply_outfield		(void) = 0;
    void		disable_order_shift	(void)
						    { order_shift = 0; }
    void		examine_order_shift	(const int ord);
    void		init_referer		(void);
    auint8 *		get_pcur		(void);
    const Symbol &	get_last_symbol		(void) const
						    { return last_symbol; }
private:
    Lrle					(void);
protected:
    std::auto_ptr<BUFFER>
			imagebuffer;
    const Info		info;
    REFERER *		order[prediction_num];
    REFERER *		differer;
    std::auto_ptr<REFERER>
			referer[prediction_num];

    Symbol		last_symbol;
    int			order_shift;
    int			dht_count;
    int			ruc_pred;

    Lrle					(const Info & 	info);
    void		reorder			(int		hit);
    void		calc_outfield		(auint8 *	ptr);
    void		init			(void);
};

class LrleEnc : public Lrle<InImageBuffer, Predictor> {
public:
    LrleEnc					(const Info & info);
    ~LrleEnc					(void);
    void		init			(void);
    void		apply_outfield		(void);
    void		enter_line		(const int line_phase);
    void		init_last_symbol	(void);
#ifndef VC6
    template<typename T> void
			exit_line		(Type2Type<T>);
    template<typename T> const Symbol &
			look_last_run		(Type2Type<T>);
    template<typename T> const Symbol &
			look_longest_run	(const int offset,
						 Type2Type<T>,
						 Int2Type<5>);
#else
    void		exit_line		(Type2Type<auint64>);
    void		exit_line		(Type2Type<auint32>);
    void		exit_line		(Type2Type<auint16>);
    void		exit_line		(Type2Type<auint8>);
    const Symbol &	look_last_run		(Type2Type<auint64>);
    const Symbol &	look_last_run		(Type2Type<auint32>);
    const Symbol &	look_last_run		(Type2Type<auint16>);
    const Symbol &	look_last_run		(Type2Type<auint8>);
    const Symbol &	look_longest_run	(const int offset,
						 Type2Type<auint64>,
						 Int2Type<5>);
    const Symbol &	look_longest_run	(const int offset,
						 Type2Type<auint32>,
						 Int2Type<5>);
    const Symbol &	look_longest_run	(const int offset,
						 Type2Type<auint16>,
						 Int2Type<5>);
    const Symbol &	look_longest_run	(const int offset,
						 Type2Type<auint8>,
						 Int2Type<5>);
#endif
private:
    void		set_sentinel		(void);
#ifndef VC6
    template <typename T> void	
			remove_sentinel		(Type2Type<T>);
#else
    void		remove_sentinel		(Type2Type<auint64>);
    void		remove_sentinel		(Type2Type<auint32>);
    void		remove_sentinel		(Type2Type<auint16>);
    void		remove_sentinel		(Type2Type<auint8>);
#endif
};

class LrleDec : public Lrle<OutImageBuffer, Distributor> {
public:
    LrleDec					(const Info & info);
    ~LrleDec					(void);
    void		init			(void);
    void		apply_outfield		(void);
    void		enter_line		(void);
    void 		exit_line		(const int next_line_phase);
    void		copy_line		(void)
			    { imagebuffer->copy_line (); }
    int			feed_last_run		(void);
    int			feed_symbol		(const int offset,
						 const Symbol & symbol);
private:
    int			feed_run		(const int offset_byte);
    void		feed_error		(const int offset);
};
/*---------------------------------------------------------------------------*/
// Lrle
template<class B, class R>
Lrle<B, R>::
Lrle (const Info & info_)
    : imagebuffer (new B (info_)), info (info_)
{
    order[0] = order[1] = order[2] = order[3] = order[4] = NULL;
    for (int i = 0; i < prediction_num; i++) {
	std::auto_ptr<R>	r (new R (info_));
	referer[i]	= r;
	// "referer[i].reset (new R (info_)); " can't be used on VC6
	order[i]	= referer[i].get ();
    }
    init ();
}

template<class B, class R>
Lrle<B, R>::
~Lrle (void)
{
}

template<class B, class R>
void Lrle<B, R>::
init (void)
{
    last_symbol.order			= marker;
    last_symbol.side_info.marker	= EOI;
    differer				= order[info.aprm.differer];
				    // this needs already constrcted referers
    disable_order_shift ();
}

template<class B, class R>
INLINE void Lrle<B, R>::
reorder (int	hit)
{
    R * const	the_first = order[hit];
    while (hit) {
	order[hit] = order[hit - 1];
	hit--;
    }
    order[0] = the_first;
}

template<class B, class R>
void Lrle<B, R>::
calc_outfield (auint8 * ptr)
{
    int i (0);
    if (info.ihdr.tag_bit) {
	if (info.ihdr.tag_position == tail) {
	    for (; i < info.sys.component - 1; i++)
		ptr[i] = info.aprm.image_outfield;
	    ptr[i++] = info.aprm.tag_outfield;
	} else {
	    ptr[i++] = info.aprm.tag_outfield;
	    for (; i < info.sys.component - 1; i++)
		ptr[i] = info.aprm.image_outfield;
	}
    } else {
	for (; i < info.sys.component; i++)
	    ptr[i] = info.aprm.image_outfield;
    }
    while (i < (int)sizeof (auint64))
	ptr[i++] = 0;
}

template<class B, class R>
INLINE void Lrle<B, R>::
init_referer (void)
{
    for (int i = 0; i < prediction_num; i++)
	referer[i]->init_pref (imagebuffer.get (), info.sys.coding_component);
}

template<class B, class R>
void Lrle<B, R>::
apply_initial_order (void)
{
    for (int j = 0; j < prediction_num; j++)
	referer[j]->set_type (Distributor::noinuse);
    int rp (prediction_num);
    for (int i = 0; i < prediction_num; i++) {
	const prediction pred (info.aprm.referer[i]);
	referer[i]->set_name (pred);
	if (pred == A)
	    referer[i]->set_type (Distributor::statical);
	else if (pred == RUC) {
	    if (rp != prediction_num)
		throw Exception ("Lrle::apply_initial_order(): RUC defined doubly", 190);
	    rp = i;
	    referer[i]->set_type (Distributor::ruc);
	} else if (pred == prediction_noinuse)
	    referer[i]->set_type (Distributor::noinuse);
	else
	    referer[i]->set_type (Distributor::basic);
    }
    ruc_pred = rp == prediction_num ? 0 : rp;
}

template<class B, class R>
INLINE void Lrle<B, R>::
examine_order_shift (const int ord)
{
    if ((last_symbol.side_info.run == info.aprm.runmax) || 
	((order[ord])->get_name () == RUC))
	disable_order_shift ();
    else
	order_shift = -1;
}

template<class B, class R>
auint8 * Lrle<B, R>::
get_pcur (void)
{
    return imagebuffer->get_pcur ();
}

INLINE int LrleDec::
feed_last_run (void)
{
    if (IS_HIT (last_symbol.order)) {
	const int trun (last_symbol.side_info.run > info.sys.coding_width ?
			    info.sys.coding_width : last_symbol.side_info.run);
	DPRINT (stderr, "run continues... %d\n", trun);
	order[0]->distribute_run (0, trun * info.sys.coding_component);
	last_symbol.side_info.run -= trun;
	return trun;
    } else {
	return 0;
    }
}
/*---------------------------------------------------------------------------*/
// LrleEnc
#define LOOK_LAST_RUN(T)						\
{									\
    if (IS_NOT_HIT (last_symbol.order)) return last_symbol;		\
    int r (order[0]->look_run (0, Type2Type<T>()));			\
    last_symbol.side_info.run = 					\
	(last_symbol.side_info.run + r) < info.aprm.runmax ?		\
	    last_symbol.side_info.run + r : info.aprm.runmax;		\
    return last_symbol;							\
}

#define REMOVE_SENTINEL(T)						\
{									\
    imagebuffer->set_pend (imagebuffer->get_outfield (Type2Type<T>()));	\
}

#define EXIT_LINE(T)							\
{									\
    remove_sentinel (Type2Type<T>());					\
}

#ifndef VC6
template<typename T> const Symbol & LrleEnc::
look_last_run (Type2Type<T>)
{
    LOOK_LAST_RUN(T)
}

template<typename T> void LrleEnc::
remove_sentinel (Type2Type<T>)
{
    REMOVE_SENTINEL(T)
}

template<typename T> void LrleEnc::
exit_line (Type2Type<T>)
{
    EXIT_LINE(T)
}
#endif

#define PROC_HIT {							\
    reorder (tmp_order);						\
    tmp_order 			+= order_shift;				\
    last_symbol.order		= tmp_order;				\
    last_symbol.side_info.run	= tmp_run;				\
    return last_symbol;							\
}

#define LOOK_LONGEST_RUN_INTERNAL(I,T)					\
{									\
    const int r (order[I]->look_run (offset, Type2Type<T>()));		\
    if (r > tmp_run) {							\
	tmp_order = I;							\
	if (r < runmax) {						\
	    tmp_run = r;						\
	} else {							\
	    tmp_run = runmax;						\
	    PROC_HIT;							\
	}								\
    }									\
}

#define LOOK_LONGEST_RUN(T)						\
{									\
    int		tmp_order (diff);					\
    int		tmp_run (0);						\
    const int	runmax (info.aprm.runmax);				\
    for (int i = 0; i < prediction_num; i++) {				\
	LOOK_LONGEST_RUN_INTERNAL(i,T);					\
    }									\
    DPRINT (stderr, "%d(", tmp.order);					\
    DPRINT (stderr, "%x,", order[0] ? order[0]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[1] ? order[1]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[2] ? order[2]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[3] ? order[3]->get_name () : 0);	\
    DPRINT (stderr, "%x/", order[4] ? order[4]->get_name () : 0);	\
    DPRINT (stderr, "%d), 0x", order_shift);				\
    if (IS_DIFF (tmp_order)) {						\
	DPRINT (stderr, "%x ", *(int *)last_symbol.side_info.error);	\
	last_symbol.order = tmp_order;					\
	*((T *)(last_symbol.side_info.error))				\
	    = differer->look_error (offset, Type2Type<T>());		\
	referer[ruc_pred]->set_ructab (offset, Type2Type<T>());		\
	disable_order_shift ();						\
	return last_symbol;						\
    }									\
    DPRINT (stderr, "%x ", tmp_run);					\
    PROC_HIT;								\
}

#define LOOK_LONGEST_RUN_5(T)						\
{									\
    int		tmp_order (diff);					\
    int		tmp_run (0);						\
    const int	runmax (info.aprm.runmax);				\
    LOOK_LONGEST_RUN_INTERNAL (0,T);					\
    LOOK_LONGEST_RUN_INTERNAL (1,T);					\
    LOOK_LONGEST_RUN_INTERNAL (2,T);					\
    LOOK_LONGEST_RUN_INTERNAL (3,T);					\
    LOOK_LONGEST_RUN_INTERNAL (4,T);					\
									\
    DPRINT (stderr, "%d(", tmp_order);					\
    DPRINT (stderr, "%x,", order[0] ? order[0]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[1] ? order[1]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[2] ? order[2]->get_name () : 0);	\
    DPRINT (stderr, "%x,", order[3] ? order[3]->get_name () : 0);	\
    DPRINT (stderr, "%x/", order[4] ? order[4]->get_name () : 0);	\
    DPRINT (stderr, "%d), 0x", order_shift);				\
    if (IS_DIFF (tmp_order)) {						\
	last_symbol.order = tmp_order;					\
	*((T *)(last_symbol.side_info.error))				\
	    = differer->look_error (offset, Type2Type<T>());		\
	DPRINT (stderr, "%x ", *(int *)last_symbol.side_info.error);	\
	referer[ruc_pred]->set_ructab (offset, Type2Type<T>());		\
	disable_order_shift ();						\
	return last_symbol;						\
    }									\
    DPRINT (stderr, "%x ", tmp_run);					\
    PROC_HIT;								\
}

#ifndef VC6
template<typename T> INLINE const Symbol & LrleEnc::
look_longest_run (const int offset,
		  Type2Type<T>,
		  Int2Type<5>)
{
    LOOK_LONGEST_RUN_5(T)
}
#else
INLINE const Symbol & LrleEnc::
look_longest_run (const int offset,
		  Type2Type<auint64>,
		  Int2Type<5>)
{
    LOOK_LONGEST_RUN_5(auint64)
}
INLINE const Symbol & LrleEnc::
look_longest_run (const int offset,
		  Type2Type<auint32>,
		  Int2Type<5>)
{
    LOOK_LONGEST_RUN_5(auint32)
}
INLINE const Symbol & LrleEnc::
look_longest_run (const int offset,
		  Type2Type<auint16>,
		  Int2Type<5>)
{
    LOOK_LONGEST_RUN_5(auint16)
}
INLINE const Symbol & LrleEnc::
look_longest_run (const int offset,
		  Type2Type<auint8>,
		  Int2Type<5>)
{
    LOOK_LONGEST_RUN_5(auint8)
}
#endif
#undef PROC_HIT
#undef LOOK_LONGEST_RUN_INTERNAL
#undef LOOK_LONGEST_RUN
#undef LOOK_LONGEST_RUN_5
/*---------------------------------------------------------------------------*/
// LrleDec
INLINE int LrleDec::
feed_run (const int offset)
{
    const int	rest (info.sys.coding_width - offset);
    const int	trun (rest < last_symbol.side_info.run ?
			rest : last_symbol.side_info.run);
    order[last_symbol.order]->
	distribute_run (offset * info.sys.coding_component,
			trun * info.sys.coding_component);
    last_symbol.side_info.run -= trun;
    return trun;
}

INLINE void LrleDec::
feed_error (const int offset)
{
    differer->distribute_error (offset, last_symbol.side_info.error);
}

INLINE int LrleDec::
feed_symbol (const int offset,
	     const Symbol & symbol)
{
    last_symbol = symbol;
    DPRINT (stderr, "%d(", last_symbol.order);
    DPRINT (stderr, "%x,", order[0] ? order[0]->get_name () : 0);
    DPRINT (stderr, "%x,", order[1] ? order[1]->get_name () : 0);
    DPRINT (stderr, "%x,", order[2] ? order[2]->get_name () : 0);
    DPRINT (stderr, "%x,", order[3] ? order[3]->get_name () : 0);
    DPRINT (stderr, "%x/", order[4] ? order[4]->get_name () : 0);
    DPRINT (stderr, "%d), 0x", order_shift);
    DPRINT (stderr, "%x ", last_symbol.order == 5 ?
	    *(int *)last_symbol.side_info.error : last_symbol.side_info.run);
    if (IS_DIFF (symbol.order)) {
	feed_error (offset);
	disable_order_shift ();
	referer[ruc_pred]->set_ructab (offset);
	return 1;
    } else if (IS_HIT (symbol.order)) {
	last_symbol.order -= order_shift;	// before examine order-shift
	examine_order_shift (last_symbol.order);	// before feeding run
	const int run (feed_run (offset));
	reorder (last_symbol.order);
	return run;
    } else { // last_symbol.order == marker
	return 0;
    }
}
/*---------------------------------------------------------------------------*/
}
#endif	//_LIBALLA_LRLE_H_
