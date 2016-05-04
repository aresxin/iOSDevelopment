/*
 * Copyright (C) 2004 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_ES_Formatter.h -- Formatterフック関数の定義
 *
 * Created : 2004.04.12 Hisashi.Ichioka(FXPS)
 *
 */

#if !defined(COM_ES_FORMATTER_H_INCLUDED)
#define COM_ES_FORMATTER_H_INCLUDED

/*--------------------------------------------------*/
/*	EdgeSink固有のCodecFilter仕様の拡張				*/
/*--------------------------------------------------*/
int
SIF_ES_EdgeSinkFactory_ExtendCodecFilterSpec(
	ES_Spec				*spec,
	ES_CodecFilterSpec	*cfspec );

ES_EdgeSinkIF *
SIF_ES_EdgeSinkFactory_CreateEdgeSink(
	ES_Spec				*spec,
	ES_EdgeLineMgr		*elmgr,
	int					isspool,
	ES_TrueSpoolWrite	splfunc,
	int					rx,
	int					ry,
	void				*mmgr );

int
SIF_ES_EdgeSinkFactory_SetFunction(
	ES_EdgeSinkIF	*sink,
	int				formatter );

#endif
