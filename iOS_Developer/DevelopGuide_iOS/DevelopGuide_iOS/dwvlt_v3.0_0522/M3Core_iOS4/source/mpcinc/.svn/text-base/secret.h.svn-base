// File: secret.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999-2004 by Fuji Xerox Co., Ltd. All right reserved.

// コアの秘密インタフェースをまとめたもの

#ifndef _MP_CORE_SECRET_H_
#define _MP_CORE_SECRET_H_

#include "mpc_api.h"

//#include <windows.h>

/*
§X.X.X MP_EMFPD インタフェース

mpc_pd.h から秘密インタフェースに移動

このインタフェースは、Ver4.0の　”ベクタＰＤ自前化”実施時までの暫定インタフェースである。
基本設計書本文には記載しない。

§X.X.X.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_MP_EMFPD, 0x136A);

/*
§X.X.X.2 メソッド一覧
*/
mpinterface MP_EMFPD
{
STDMETHOD_(HENHMETAFILE_XD,GetEMFHandle)() PURE;
STDMETHOD(SetEMF)(HENHMETAFILE_XD hemf) PURE;
};

/*
§X.X.X.3 各メソッドの定義

§GetEMFHandle
・パラメータ

・説明
PD内部で保持しているEMFのハンドルを（コピーせずに）直接返す。
DWViewerは、このハンドルの内容を変更したり、破棄してはならない。

このハンドルはPDオブジェクトを破棄すると同時に解放されて無効になる。
従って、必要に応じてメタファイルをコピーして利用する事。

注意）
このインタフェースは、Ver4.0の　”ベクタＰＤ自前化”実施時までの暫定インタフェースである。
DWViewerのテキスト検索機能以外で用いてはならない。
DWViewerは、MP_EMFPDがGetInterfaceできなかった場合の適切なエラー復帰処理を実装しておく事。

・リターン値
HENHMETAFILE	PD内部で保持しているEMFのハンドル

§SetEMF
・パラメータ
HENHMETAFILE hemf	内容変更後のEMFのハンドル

・説明
文字コード変換プラグインから使用するために用意した関数。
EMFPDからGetEMFHandleによって取り出したEMFの内容を加工し、本関数を用いて
EMFPDに戻す。

・リターン値
HRESULT		成功すればMP_NOERRORが返る。失敗すればエラー値が返る。
*/

/*
§X.X.X MP_WMFPD インタフェース

mpc_pd.h から秘密インタフェースに移動

このインタフェースは、Ver4.0の　”ベクタＰＤ自前化”実施時までの暫定インタフェースである。
基本設計書本文には記載しない。

§X.X.X.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_MP_WMFPD, 0x136B);

/*
§X.X.X.2 メソッド一覧
*/
mpinterface MP_WMFPD
{
STDMETHOD_(HMETAFILE_XD, GetWMFHandle)(LONG *mm = NULL, LONG *xExt = NULL, LONG *yExt = NULL) PURE;
STDMETHOD(GetText)(MP_Text* pbuffer, int cchbuffer) PURE;
};

/*
§X.X.X.3 各メソッドの定義

§GetWMFHandle
・パラメータ
LONG *mm		METAFILEPICT構造体の mm   を返す
LONG *xExt		METAFILEPICT構造体の xExt を返す
LONG *yExt		METAFILEPICT構造体の yExt を返す

・説明
PD内部で保持しているWMFのハンドルを（コピーせずに）直接返す。
DWViewerは、このハンドルの内容を変更したり、破棄してはならない。
このハンドルはPDオブジェクトを破棄すると同時に解放されて無効になる。
従って、必要に応じてメタファイルをコピーして利用する事。

mm, xExt, yExt が NULL 以外の場合、METAFILEPICT構造体の要素を返す。

注意）
このインタフェースは、Ver4.0の　”ベクタＰＤ自前化”実施時までの暫定インタフェースである。
DWViewerのテキスト検索機能以外で用いてはならない。
DWViewerは、MP_WMFPDがGetInterfaceできなかった場合の適切なエラー復帰処理を実装しておく事。

・リターン値
HMETAFILE		PD内部で保持しているWMFのハンドル

§GetText
・パラメータ
unsigned short* pbuffer		文字列を受け取るバッファ
int cchbuffer				バッファの文字数

・説明
WMF内部のテキストをバッファに取得する。テキストの形式はUNICODEである。
pbufferにNULLが渡された場合はバッファの文字数を返すのみ。

・リターン値
HRESULT		成功したときはバッファの文字数が返される
			失敗したときはエラーコードが返される
*/

/*
§X.X.X ICompressedMPAttribute インタフェース

mpc_spi.h から秘密インタフェースに移動

§X.X.X.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_ICompressedMPAttribute, 0x1376);

/*
§X.X.X.2 メソッド一覧
*/
mpinterface ICompressedMPAttribute {
STDMETHOD(SetCompressedAttribute)(IStgObject* stgobj, const MP_AName* aname, const MP_AValue* avalue = NULL, MP_Integer nth_element = -1, MP_Integer do_assign = 1) PURE;
STDMETHOD(GetCompressedAttribute)(IStgObject* stgobj, const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1) PURE;
STDMETHOD(OKDEncode)(MP_Integer orgBytes, const void* orgMem, void* packedMem) PURE;
STDMETHOD(OKDDecode)(MP_Integer packedBytes, const void* packedMem, MP_Integer orgBytes, void* orgMem) PURE;
STDMETHOD(OKDEncodeF)(const char* srcfile, MP_File* dstfile, HRESULT* phres=NULL, long* rtn_srcSize=NULL, unsigned long* rtn_errCheck=NULL) PURE;
STDMETHOD(OKDDecodeF)(long offset, long packedBytes, MP_File* srcfile, long orgSize, const char* dstfile, HRESULT* phres=NULL, unsigned long* errCheck=NULL) PURE;
STDMETHOD(OKDEncodeFW)(const MP_WPath* srcfile, MP_File* dstfile, HRESULT* phres=NULL, long* rtn_srcSize=NULL, unsigned long* rtn_errCheck=NULL) PURE;
STDMETHOD(OKDDecodeFW)(long offset, long packedBytes, MP_File* srcfile, long orgSize, const MP_WPath* dstfile, HRESULT* phres=NULL, unsigned long* errCheck=NULL) PURE;
};

/*
§X.X.X.3 各メソッドの定義

§SetCompressedAttribute
・パラメータ
stgobj
aname
avalue
nth_element
do_assign

・説明
主にMPCPDが利用する。

ストレージ層がOKD圧縮を行わずに、受け取った属性値のままファイルに保存する。

これは、JPEGやMHなど、既に圧縮されたデータをSetAttributeする場合
ストレージ内部でOKD圧縮を試みてもオリジナル以下になるケースで、
OKD圧縮を実行し失敗する時間を省くためのバイパスである。

データ圧縮しない点を除けば、IStgObject::SetAttributeと同じ動作をする。

・リターン値
IStgObject::SetAttribute参照


§GetCompressedAttribute
・パラメータ
stgobj
aname
rtn_avalue
nth_element

・説明
主にMPCPDが利用する。

SetCompressedAttributeで保存した属性を、OKD伸張せずにそのまま取り出す。

データ伸張しない点を除けば、IStgObject::GetAttributeと同じ動作をする。

・リターン値
IStgObject::GetAttribute参照


§OKDEncode
・パラメータ
orgBytes	オリジナルデータのサイズ（単位　バイト）
orgMem		オリジナルデータが入っている領域
packedMem	圧縮結果を格納するorgBytesバイト以上の領域

・説明
主にMPCPDが利用する。
通常は、ストレージ内部で自動的に圧縮を実行するため
アプリケーションがSetAttribute時に明示的に圧縮する必要はない。

orgMemが指す領域の内容をorgBytesバイトOKD圧縮して
圧縮結果のデータをpackedMemにセットする。

packedMem は、利用者がorgBytesバイト以上の領域を確保して渡す。
圧縮の結果がorgBytes以上になる場合、処理を打ち切って失敗と返す。

・リターン値
成功したら圧縮結果のバイト数（１以上）を返す。


§OKDDecode
・パラメータ
packedBytes	圧縮データのサイズ（単位　バイト）
packedMem	圧縮データが入っている領域
orgBytes	orgMemに用意した領域のサイズ（単位　バイト）
orgMem		伸張結果を格納する領域

・説明
主にMPCPDが利用する。
通常は、ストレージ内部で自動的に伸張を実行するため
アプリケーションがGetAttribute時に明示的に伸張する必要はない。

packedMemが指すpackedBytesバイトの内容を、OKD伸張して
伸張結果のデータをorgMemにセットする。
途中でもorgBytesに成った時点伸張で処理を終了する。

orgBytesに０以下をセットしてこの関数をコールしない事

・リターン値
成功したらorgBytesを返す。

§OKDEncodeF
・パラメータ
srcfile			OKD圧縮の対象となるファイルのパス名を指定する
dstfile			OKD圧縮結果を格納するMP_Fileオブジェクトを指定する
phres			結果コードのアドレス
rtn_srcSize		srcfileで指定されたファイルサイズのアドレス
rtn_errCheck	OKD圧縮結果に対する誤り検出用データのアドレス

・説明
srcfileで指定されるファイルの全データを対象として、OKD圧縮した結果をdstfileで指定されるMP_Fileへ保存する。
結果は、MP_Fileオブジェクトに関連する実際のファイルの最後部に付加する。phresがNULLでなければ、phresにエラー
コードをセットする。rtn_srcSizeがNULLでなければ、rtn_srcSizeにsrcfileで指定されるファイルのサイズをセット
する。rtn_errCheckがNULLでなければ、rtn_errCheckに圧縮結果に対する誤り検出用データをセットする。

・リターン値
成功したとき、圧縮後サイズ（バイト数）を結果として返す。
失敗したとき、原因が圧縮不可能なデータによる場合は0を返す。それ以外の失敗の場合は-1を返す。

§OKDDecodeF
・パラメータ
offset			MP_Fileオブジェクトの先頭ポインタから伸長対象のOKD圧縮データへのオフセット
packedBytes		伸長対象のOKD圧縮データのサイズをバイト数で指定する
srcfile			伸長対象のOKD圧縮データを格納するMP_Fileオブジェクト
orgSize			OKD圧縮前のオリジナルデータサイズをバイト数で指定する（OKDEncodeFの戻り値）
dstfile			伸長した結果を格納するファイルのパス名
phres			結果コードのアドレス
errCheck		OKD圧縮データに対する誤り検出用データ

・説明
srcfileで指定されるMP_Fileオブジェクト中のOKD圧縮されたデータを対象として、伸長した結果をdstfileで指定される
ファイルへ書き込む。OKD圧縮されたデータは、srcfileで指定されるファイルの先頭位置からoffsetサイズSeekさせ、そ
の位置からpackedBytes分のデータであるとする。phresがNULLでなければ、phresにエラーコードをセットする。errCheck
がNULLでなければOKD圧縮データに対して誤り検出を実行する。なお、errCheckにはOKDEncodeFで取得した値をセットする。

・リターン値
成功したとき、orgSizeを結果として返す。
エラーが発生したときは、ゼロを結果として返す。

§OKDEncodeFW
・説明
OKDEncodeFのUnicode I/F

§OKDDecodeFW
・説明
OKDDecodeFのUnicode I/F
*/

/*
§X.X.X ISpecialAttribute インタフェース

§X.X.X.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_ISpecialAttribute, 0x137A);


/*
§X.X.X.2 メソッド一覧
*/
mpinterface ISpecialAttribute {
STDMETHOD(GetSpecialAttribute)(MPCObject* obj, const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1) PURE;
};

/*
§X.X.X.3 各メソッドの定義


§GetSpecialAttribute
・パラメータ
aname
rtn_avalue
nth_element

・説明
HBocyContが文字認識結果を取り出すときに利用する。

文字認識結果の属性#ocrtext、#ocrrectを、保護状態を無視して取り出す。

転記権なしでも取り出せる点を除けば、IStgObject::GetAttributeと同じ動作をする。

・リターン値
IStgObject::GetAttribute参照
*/

#endif // _MP_CORE_SECRET_H_

// CHANGE LOG
// 1999.05.27 - Nakazawa - 新規作成
// 1999.06.14 - Tashiro - 0x137A IID_ISpecialAttribute V4文字認識結果取得用I/F 追加
// 2004.03.29 - Komoda - V6.0 MP_EMFPD, MP_WMFPDにGetTextを追加
// 2007.08.13 - Komoda - V7.0 Unicode I/Fの追加
