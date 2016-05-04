// File: CoreByteServ.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 1999-2000 by Fuji Xerox Co,. Ltd. All right reserved.

// このファイルは、以下の構造体と関数を宣言する
//
//	構造体
//		MPC_Range	ファイル中のデータ領域を示す
//	関数
//		MPCGetDataRange()
//			オブジェクトとその子供がもつバルクデータのデータ領域を調べる
//		MPCAssertInitialRange()
//			読み込み済みの領域がOpenFile()に十分であるか検証する。
//		MPCSetByteServeMark()
//			バイトサーブで扱うファイルであるというマークをつける
//		MPCUnsetByteServeMark()
//			バイトサーブで扱うファイルであるというマークをはずす


#ifndef _CORE_BYTE_SERV_H_
#define _CORE_BYTE_SERV_H_

//#include <windows.h>

class MPC_Range {
public:
	MPC_Range(){}
	~MPC_Range(){}

	MPC_Range( long lStart , long lLen ) : start( lStart ) , len( lLen ){}

	long start;
	long len;
};


__declspec(dllexport) HRESULT MPCGetDataRange( MP_PtrArray* pNeedsRanges, MPCObject* obj, int bIconPdOnly = FALSE, int bOnlyMe = FALSE );
//DLLBINDFUNC_(HRESULT ,MPCGetDataRange)( MP_PtrArray* pNeedsRanges, MPCObject* obj, int bIconPdOnly = FALSE );

/*
・パラメータ
pNeedsRanges 参照バルクデータの領域を示すMPC_Range構造体のポインタを追加するアレイ
obj	調べるオブジェクト
bIconPdOnly アイコンPDのみを調べる
bOnleyMe 自分の属性のみ調べる(子孫の属性は調べない) AR12762にて追加

・説明
自身と子孫の属性が参照するファイル内のバルクデータの
それぞれの位置と長さのポインタを pNeedsRanges に追加する。
位置はファイル先頭から。位置と長さの単位はバイト。
隣接している領域があっても連結はしない。
重複している領域があっても削除はしない(因数化されているとき)。
バルクデータが1つも無いときは、pNeedsRanges に何も追加しない。
エラー時はエラーコードを返す。
pNeedsRanges は呼び出し側が MPCreateMPPtrArray() で生成し、
破棄するときは、各要素を delete 後に pNeedsRanges->Destroy() する。

objに指定するMPCObjectには、IReadOnlyPersistインタフェースが実装されている必要がある。

bIconPdOnlyが0以外のときは、属性#iconpdのみを対象とする。

bOnlyMeが0以外のときは、そのオブジェクトの属性のみを対象とする。

・リターン値
MP_E_INVALIDARG
	pNeedsRangesがNULL
	objがNULL
	objがストレージオブジェクトに結びついていない
	objがスクラッチオブジェクト
MP_E_UNEXPECTED
	子供のロードに失敗した
	MP_PtrArrayの生成に失敗した
	ツリーのデータ不整合
	VLT(forWeb)以外のビルドで呼んだ(TBD)
MP_E_ACCESSDENIED
	OpenMPに成功していない

・セキュリティ
この関数内では認証は発生しない(認証済みのはず)
OpenMP()前だとMP_E_ACCESSDENIEDエラー(objがルートオブジェクトの場合)
保護文書中のオブジェクトのときは、暗号化されている状態での位置/長さ
*/



__declspec(dllexport) HRESULT MPCAssertInitialRange( MP_PtrArray* pNeedsRanges, MP_PtrArray* pReadyRanges, MP_File* pFile );

/*
・パラメータ
pNeedsRanges さらに必要な領域を示すMPC_Range構造体のポインタのアレイ
pReadyRanges 読み込み済みの領域を示すMPC_Range構造体のポインタのアレイ
pFile 調べるファイル

・説明
ファイル pFile 内の読み込み済み領域 pReadyRanges が、
ヘッダ/トレーラ/ツリーを完全に含んでいるか検証する。
含んでいる場合は、pNeedsRanges に何も追加しない。
不十分な場合は、不足している領域を示すMPC_Range構造体のポインタを
pNeedsRanges に追加する。
エラー時はエラーコードを返す。
pNeedsRanges の領域を読めば全部揃う、ということは保証しないので、
読み込み後にまたMPCAssertInitialRange()を呼んで確かめる。
pNeedsRanges は呼び出し側が MPCreateMPPtrArray() で生成し、
破棄するときは、各要素を delete 後に pNeedsRanges->Destroy() する。
ファイルがV1文書のときはMP_E_OLDFORMATを返す。V1文書を開くときは、
(1)この関数でMP_E_OLDFORMAT
(2)ファイルデータを全部読み込んでから、OpenFile()してみてエラーでなければV1文書
という処理になる。

・リターン値
MP_E_INVALIDARG
	pFileがNULL
	pNeedsRangesがNULL
	pReadyRangesがNULL
	pReadyRangesの要素数が0
	pReadyRangesのある要素の内容が不正(ex. startが負など)
MP_E_FILE_NOT_FOUND
	lpFileNameが見つからない
MP_E_ACCESSDENIED
	lpFileNameが開けない
MP_E_BAD_FORMAT
	lpFileNameが(読み込み済みの範囲内で)正しいフォーマットでない
MP_E_NEWFORMAT
	lpFileNameのフォーマットが新しすぎる
MP_E_OLDFORMAT
	lpFileNameのフォーマットが古すぎる
	V1文書はこのエラーを返す(事実上バイトサービングできないため)
MP_E_UNEXPECTED
	MP_PtrArrayの生成に失敗した
	VLT(forWeb)以外のビルドで呼んだ(TBD)

・セキュリティ
この関数内では認証は発生しない
保護文書のときは、暗号化されている状態での位置/長さ
*/

__declspec(dllexport) HRESULT MPCSetByteServeMark( MP_File* pFile );
/*
・パラメータ
pFile 書き換えるファイル

・説明
ファイル pFile の先頭バイトをバイトサーブ用マークに書き換える。
書き換えられたファイルは、DWBYTESERVE を定義してビルドした
mpcstg でのみ OpenFile() できる。

・リターン値
MP_E_INVALIDARG
	pFileがNULL
その他ファイル系のエラー
*/

__declspec(dllexport) HRESULT MPCUnsetByteServeMark( MP_File* pFile );
/*
・パラメータ
pFile 書き換えるファイル

・説明
ファイル pFile の先頭バイトを書き戻して、通常の mpcstg
で扱える状態にする。

・リターン値
MP_E_INVALIDARG
	pFileがNULL
	先頭バイトが、正常値でもバイトサーブ用マークでもない
その他ファイル系のエラー
*/

__declspec(dllexport) MPC_Range* CreateMPC_Range();
__declspec(dllexport) MPC_Range* CreateMPC_Range(int nSize);
__declspec(dllexport) void DeleteMPC_Range( MPC_Range* pRange );
__declspec(dllexport) void DeleteMPC_Ranges( MPC_Range* pRange );
__declspec(dllexport) void DeletePtrArray( MP_PtrArray* pRanges );

#endif // _CORE_BYTE_SERV_H_

//
//CHANGE LOG
//1999.11.17 - Tashiro - 作成
//2000.05.30 - Tashiro - 関数仕様変更、マーキング関数追加
