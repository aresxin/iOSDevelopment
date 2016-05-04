/*
 * Copyright (C) 2004 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_FilterParameter.h -- Filterパラメータの定義
 *
 * Created : 2004.04.13 Hisashi.Ichioka(FXPS)
 *
 */

#if !defined(COM_FILTERPARAMETER_H_INCLUDED)
#define COM_FILTERPARAMETER_H_INCLUDED

/*----------------------------------*/
/*	Filter_Parameter型の定義		*/
/*----------------------------------*/
typedef struct Filter_ParameterT {
	HANDLE			handle;
	unsigned long	size;
	unsigned char	data[1];
} Filter_Parameter;

/*----------------------------------*/
/* Filterパラメータの取得			*/
/*----------------------------------*/
extern	Filter_Parameter *
SIF_GetFilterParameter( int id );

/*----------------------------------*/
/* Filterパラメータの開放			*/
/*----------------------------------*/
extern	void
SIF_FreeFilterParameter( Filter_Parameter* filter );

#endif
