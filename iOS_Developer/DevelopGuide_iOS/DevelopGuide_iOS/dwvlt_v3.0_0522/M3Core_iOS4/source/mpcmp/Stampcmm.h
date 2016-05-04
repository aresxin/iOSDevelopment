// File: STAMPCMM.H
// Author: Hideo Fujii
// Copyright (C) 1996 by Fuji Xerox Co., Ltd.  All rights reserved.
#ifndef _STAMPCMM_H_
#define _STAMPCMM_H_

// オブジェクトタイプ（OBJECT_TYPE)
#define	AID_STAMP	0x8033

//日付印コンテントの属性
#define	STAMPATT_NAME		"STAMPATT_NAME"	//ﾃﾞｰﾄ印の氏名文字列
#define	STAMPATT_POST		"STAMPATT_POST"	//所属･役職文字列
#define STAMPATT_DATE		"STAMPATT_DATE"	//日付文字列
#define	STAMPATT_DATEFLAG	"STAMPATT_DATEFLAG"	//日付を自動設定するか？
#define	STAMPATT_COLOR		"STAMPATT_COLOR"	//ﾃﾞｰﾄ印の色
//以下97/4/25追加
#define STAMPATT_DAY		"STAMPATT_DAY"	//日の文字列
#define STAMPATT_MONTH		"STAMPATT_MONTH"	//月の文字列
#define STAMPATT_YEAR		"STAMPATT_YEAR"	//年の文字列
// V40
#define STAMPATT_ERA		"STAMPATT_ERA"	// 基準年指定かどうか
#define STAMPATT_BASEYEAR	"STAMPATT_BASEYEAR"	// 基準年の値
#define STAMPATT_PREFIX		"STAMPATT_PREFIX"	// 日付の先頭に表示される文字
// V62
#define STAMPATT_DATEFORMAT "STAMPATT_DATEFORMAT" // 日付の書式文字列
#define STAMPATT_DATEORDER  "STAMPATT_DATEORDER"  // 年月日の表示順

#define STAMP_LINE_OFFSET 29// y^2 + x^2 = (c/2)^2 & y = c3/22(4:3:4に分割) & c = 1500  のときの (c/2 - x)	の値
#define MAX_STAMP_STRING 26//最大文字列長 12BYTE*2 + "\r\n"
#define MAX_PREFIX_STRING 1//半角1文字
#define DEFAULT_PREFIX_STRING "'" // V30互換なのでハードコードした

#define POST	0
#define DATE	1
#define NAME	2

//リソースで定義したタイムフォーマット内の年､月､日の順番
#define YEAR_MONTH_DAY	0
#define YEAR_DAY_MONTH	1
#define MONTH_YEAR_DAY	2
#define MONTH_DAY_YEAR	3
#define DAY_YEAR_MONTH	4
#define DAY_MONTH_YEAR	5

#define STAMP_DEFAULT_DATE "00"

const MP_Dim STAMP_SIZE = {1500, 1500};

const int MINIMUMSIZE = 1000;
const int MAXIMUMSIZE = 50000;

#endif //#ifndef _STAMPCMM_H_


//
// CHANGE LOG
// 96.12.02	- Fujii -	Create
