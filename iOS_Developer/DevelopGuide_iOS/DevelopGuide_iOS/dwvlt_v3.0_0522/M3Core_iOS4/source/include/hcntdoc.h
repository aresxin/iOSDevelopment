// File: hcntdoc.h
// Author: Takashi Matsumoto
// Copyright(C) 1996,1997 by Fuji Xerox Co,. Ltd. All right reserved.  

#ifndef HCNTDOC_H
#define HCNTDOC_H

#include "mpc_api.h"

MPC_EXTERN_GUID(CLSID_HCONTDOC, 0x1000);
MPC_EXTERN_GUID(CLSID_HBODYCONT, 0x8010);

MPC_EXTERN_GUID(IID_HCONTDOC, 0x1001);
MPC_EXTERN_GUID(IID_HBODYCONT, 0x1002);

// IHeteroContDocインタフェース
mpinterface IHeteroContDoc : public MPCContDocument
{
#ifndef SFXVW
// UpdateBodyは実装が不完全
STDMETHOD(UpdateBody)(const char* infPathName, int page = -1) PURE;
STDMETHOD(SetNative)(const char* pathName) PURE;
STDMETHOD_(MPCObject*, GetReferencePage)(
	MP_Integer nth, HRESULT* phres = NULL) PURE;

/*!
@brief オリジナルデータをセットする(MultiByteパス)
@param[in] pathName セットするオリジナルデータのパス
@param[in] tatype オリジナルデータ名のテキスト属性の形式
@param[in] codepage Unicode属性に変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf,nd,ut属性が更新される
*/
STDMETHOD(SetNativeFile)(const MP_Path* pathName, MP_TAType tatype, int codepage) PURE;
/*!
@brief オリジナルデータをセットする(Unicodeパス)
@param[in] pathName セットするオリジナルデータのパス
@param[in] tatype オリジナルデータ名のテキスト属性の形式
@param[in] codepage MultiByte属性に変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf,nd,ut属性が更新される
*/
STDMETHOD(SetNativeFileW)(const MP_WPath* pathName, MP_TAType tatype, int codepage) PURE;

/*!
@brief オリジナルデータ名を変更する(MultiByteで渡す)
@param[in] path セットするオリジナルデータ名
@param[in] tatype オリジナルデータ名のテキスト属性の形式
@param[in] codepage Unicode属性に変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf属性を変更する
*/
STDMETHOD(SetNativeName)(const char* name, MP_TAType tatype, int codepage) PURE;
/*!
@brief オリジナルデータ名を変更する(Unicodeで渡す)
@param[in] path セットするオリジナルデータ名
@param[in] tatype オリジナルデータ名のテキスト属性の形式
@param[in] codepage MultiByte属性に変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf属性を変更する
*/
STDMETHOD(SetNativeNameW)(const MP_Text* name, MP_TAType tatype, int codepage) PURE;
#endif //SFXVW

/*!
@brief オリジナルデータをファイルに出力する(MultiByteパス)
@param[out] pathName オリジナルデータを出力するパス
@return HRESULT リターンコード
@note nd属性を読み出す、ファイルのタイムスタンプをut属性の値に合わせる
*/
STDMETHOD(GetNativeData)(const MP_Path* pathName) PURE;
/*!
@brief オリジナルデータをファイルに出力する(Unicodeパス)
@param[out] pathName オリジナルデータを出力するパス
@return HRESULT リターンコード
@note nd属性を読み出す、ファイルのタイムスタンプをut属性の値に合わせる
*/
STDMETHOD(GetNativeDataW)(const MP_WPath* pathName) PURE;

/*!
@brief オリジナルデータ名を読み出す(MultiByteで受け取る)
@param[out] name オリジナルデータ名を受け取る
@param[out] tatype テキスト属性の形式を受け取る
@param[in] codepage Unicode属性を変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf属性を読み出す
*/
STDMETHOD(GetNativeName)(MP_MBString& name, MP_TAType& tatype, int codepage) PURE;
/*!
@brief オリジナルデータ名を読み出す(Unicodeで受け取る)
@param[out] name オリジナルデータ名を受け取る
@param[out] tatype テキスト属性の形式を受け取る
@param[in] codepage MultiByte属性を変換する際に使用するコードページ
@return HRESULT リターンコード
@note nf属性を読み出す
*/
STDMETHOD(GetNativeNameW)(MP_String& name, MP_TAType& tatype, int codepage) PURE;
};

// HeteroContDocの属性
#define ANAME_NATIVEDATA "nd"	// MP_Octet
#define ANAME_NATIVEFILE "nf"	// MP_Octet
#define ANAME_UPDATETIME "ut"	// MP_Integer(time_t)

// IHeteroBodyContインタフェース
mpinterface IHeteroBodyCont : public MPCMedia
{
#ifndef SFXVW
// Updateは現在中が実装されていない
STDMETHOD(Update)(const char* infPathName, int page) PURE;
STDMETHOD(SetPD)(MP_PD* pd, MP_Dim dim = MP_NULL_DIM) PURE;
STDMETHOD_(MP_PD*,GetPD)(HRESULT* phres = NULL) PURE;
#endif //SFXVW
};

// HeteroBodyContの属性
//#define ANAME_DISPLAYPD "dpd"		// MP_Octet -- 未使用
#define ANAME_DIMENSION "#dim"		// MP_Dim
#define ANAME_PD "#pd"				// MP_Octet
#define ANAME_ICONPD "#iconpd"		// MP_Octet

// V3.0 新規属性
#define ANAME_MONOMODE "mm"			// MP_Integer
#define ANAME_DOCNAME "dn"			// MP_Octet
#define ANAME_APPLICATION "ap"		// MP_Integer
#define ANAME_TOTALRECORDS "rs"		// MP_Integer
#define ANAME_RESOLUTION "dpi"		// MP_Integer
#define ANAME_CANROTATE "canrotate"	// MP_Integer
#define ANAME_PDPLATFORM "pf"		// MP_Octet
#define ANANE_PDVERSION "pv"		// MP_Octet
#define ANAME_PDDEPTH "dpt"			// MP_Integer
#define ANAME_PDCLASS "org"			// MP_Integer
#define ANAME_PDCOMPRESSION "cmp"	// MP_Integer

// V4.1 元サイズ判定用新規属性
#define ANAME_PDPIXELS		"imgsize"	// MP_Dim
#define ANAME_PDRESOLUTIONS	"imgreso"	// MP_Dim
#define ANAME_ORGSIZE		"orgsize"	// MP_Dim

// ANAME_APPLICATIONの値
#define APP_UNKNOWN 0
#define APP_WORD 1
#define APP_EXCEL 2
#define APP_POWERPOINT 3
#define APP_LOTUS123 4
#define APP_FREELANS 5
#define APP_TARO6 6
#define APP_TARO7 7
#define APP_TARO8 8
#define APP_OASYS 9

#endif // HCNTDOC_H

// CHANGE LOG
// 96.3.3 - Matsumoto - 生成
// 96.7.2 - Nagano - SetPD()追加
// 97.9.12 - Matsumoto - IHeteroBodyCont::GetPDを追加、属性を追加
// 97.9.24 - Matsumoto - EXTERN_GUIDをMPC_EXTERN_GUIDに変更
// 97.10.8 - Matsumoto - IID_HCONTDOC, IID_HBODYCONTを追加
// 99.9.6 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
// 00.9.28 - Nakazawa - V4.1 元サイズ判定用新規属性追加
// 07.12.06 - Komoda - V7.0 Unicode I/Fの追加
