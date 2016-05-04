// File: STG_SPI.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*	MPC_SPI.H	: Storage SPI definition
*
*	DWCore / Content/ContDocモデル実装者に提供するDWCore 内部インタフェース
*
*	MP / Content / ContDoc 実装モジュール以外が includeしてはならない。
*/

#ifndef MPC_SPI_H
#define MPC_SPI_H

#include "mpc_api.h"

/*
§7. 内部インタフェース

§7.1 内部共通定義

§7.1.1 定数・マクロ定義
*/
//! ASN.1のINT4 符号化時の最大バイト数。メモリ獲得時のサイズ概算に利用
#define MAX_INT_LEN 5
/*
§7.1.2 DLLの初期化

§MPCSPI_DLLCreateMPCObject
*/
DLLBINDFUNC_(MPCObject*, MPCSPI_DLLCreateMPCObject)(MP_RefObjectType type);

/*
§MPCSPI_CHECK_REVISION
*/
#define MPCSPI_REVISION	971021	//Ver3.0 1st Revesion

#define MPCSPI_CHECK_REVISION(VAR_CLSID) if ( VAR_CLSID == (MP_RefObjectType)0) { return (MPCObject*)MPCSPI_REVISION; }

/*
§7.2 セッションオブジェクトの内部インタフェース
*/

/*
§7.2.1 ISPISession インタフェース
*/
/*
§7.2.1.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_ISPISession, 0x1357);

/*
§7.2.1.2 メソッド一覧
*/
enum MPC_DBGCoreType {
//! 1 = PD,属性,ファイルのサイズ制限を外す。
UNLIMITEDSIZE = 1,
//! 1 = WMF, EMF のパッチを無効にしてPlayMetafileする。
NO_MF_PATCH = 2,
//! 1 = DIB/LWF->DWFile作成でオリジナルDIBを一時ファイルに保存する。
DUMP_BMP = 3,
//! 1 = Adaptive圧縮を適用しないで、常にOKD圧縮する
NO_ADAPTIVE = 4,
};

mpinterface ISPISession {
/*!
clsidで指定されたMPCObjectを生成し、初期化を実行せずに返す。
	
通常のMPCObject生成は、<br>
	新規生成ならば、IPersistMPCObject::OnCreate()      <br>
	ファイルロードならば、IPersistMPCObject::OnLoad()  <br>
をDWCore内部でコールするが、
このメソッドは、そのいずれの初期化も行わずにオブジェクトを返す。

この状態のオブジェクトをそのまま使用するとクラッシュする。<br>
各オブジェクトの内部に精通したモデル実装者以外は、このメソッドをコールしてはならない。<br>
コールする必要も無い。
	
V2までは、BodyContentとTemplateでモデルを複製する時に自分自身のnewの代わりに用いている。<br>
@param MP_ObjectType clsid
@param HRESULT *phres
@retval MPCObject* 初期化を実行していない不完全なMPCObjectのアドレス
@retval オブジェクト生成関連のエラー
*/
STDMETHOD_(MPCObject*, CreateNoInitializedMPCObject)(const MP_ObjectType clsid, HRESULT* phres=NULL) PURE;
/*!
mpcobjがファイルのルートオブジェクトかどうかを問い合わせる。

MPCObject::Destroyは、「ファイルのルートなら削除できない」仕様だが<br>
これを実装する時にストレージオブジェクトのDestroyを実行する前に<br>
削除可能かどうかの判定をし、GUIに削除通知を発行しなければならないオブジェクトが利用する。

現在利用しているのは、MetaPaperとBasicPageのみである。
@param MPCObject* mpcobj
@retval MP_S_OK	ファイルのルートオブジェクトである。
@retval MP_S_FALSE	ファイルのルートオブジェクトでない。
*/
STDMETHOD(IsFileRootMPCObject)(MPCObject* mpcobj) PURE;
/*!
DWCore V3 基本設計書の「障害解析支援」で記載したレジストリ内容の取得
	
typeに応じてリターン値になる。
	
@param MPC_DBGCoreType type
@retval UNLIMITEDSIZE	// 0=通常動作　1 = PD,属性,ファイルのサイズ上限を外す。
@retval NO_MF_PATCH		// 0=通常動作　1 = WMF, EMF のパッチを無効にし、PlayMetafileを実行する。
@retval DUMP_BMP		// 0=通常動作　1 = DIB/LWF->DWFile作成で入力imageをコピーする。

@note
@par typeがUNLIMITEDSIZE 
　上限チェックを外した性能評価を行う場合に利用する。

@par typeが、NO_MF_PATCHの場合
　MPCPDが利用し、EMFPDとWMFPDの描画方法を変える。
　WMF, EMF のパッチを無効にし、PlayMetafileを実行する。
　画質劣化障害がパッチに起因するものかMetafile描画本来の問題かの分析に使う。

@par typeが、DUMP_BMPの場合
　MPCPD が利用し、PD作成動作を変える。
　CreateBMPPD等でオリジナルのDIBファイルを一時ディレクトリに複製する。
　画質劣化がDCT圧縮が原因なのか、本来のスキャン画質の問題かの切り分けに使う。
*/
STDMETHOD(GetDBGCoreInfo)(MPC_DBGCoreType type) PURE;

/*!
DWCore内部で使用するユニークな名前の一時ファイルを作成し、そのパスをpathにセットして返す。

この関数が成功した場合、ファイルは生成されている。
利用者が明示的に削除しなければならない。

一時ファイルのパス名は<br>、
パス：　レジストリ Core\TempPath が設定値。未設定の場合はWinAPI GetTempPath()の位置<br>
ファイル名：　"MPC" + <固有番号> + ".tmp"	（例： "MPC1200.tmp"）<br>
@param MP_Path *path
*/
STDMETHOD(GetCoreTempFileName)(MP_Path* path) PURE;

/*!
一時ファイルのパスを返す(unicode版)。

仕様はGetCoreTempFileNameと同様。
@param MP_String& path
*/
STDMETHOD(GetCoreTempFileName)(MP_String& path) PURE;

// WindowsMobile対応
// 09/09/11 M.Chikyu
#if defined _PF_WINCE_

STDMETHOD(GetCoreTempFileNameWM)(MP_String& path,
								 MP_Integer size) PURE;

#endif
	
STDMETHOD_(MP_File*, CreateTempFile)(MP_Integer ext,
									 HRESULT* phres=NULL) PURE;
	
};

/*
§7.2.3 IFormatAttribute インタフェース

ASN.1の符号化・復号化を外部で利用する際のユーティリティ
*/
/*
§7.2.3.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IFormatAttribute,0x1358);

/*
§7.2.3.2 メソッド一覧
*/
mpinterface IFormatAttribute {
/*!
属性tagをEncodeするのに必要なバイト数を返す
@param MP_Integer tag
*/
STDMETHOD(TagSize)(MP_Integer tag) PURE;
/*!
lengthをEncodeするのに必要なバイト数を返す
@param MP_Integer length
*/
STDMETHOD(LengthSize)(MP_Integer length) PURE;
/*!
valueをint4でEncodeした時に必要なバイト数を返す
@param MP_Integer value
*/
STDMETHOD(IntegerSize)(MP_Integer value) PURE;
/*!
memPtrからタグをデコードして返す。
@param MP_Octet* memptr
@param  MP_Integer* tag
@retval return値は使ったバイト数を返す
*/
STDMETHOD(DecodeTag)(MP_Octet* memptr, MP_Integer* tag) PURE;
/*!
memPtrからInt4数値をデコードしてvalueに返す。
@param MP_Octet* memptr
@param  MP_Integer* value
@retval return値は使ったバイト数
*/
STDMETHOD(Decode)(MP_Octet* memptr, MP_Integer* value) PURE;
/*!
memPtrデコードして返す。
lengthに値のバイト長、valOffsetにmemptr中での値の開始バイト位置を返す。
@param MP_Octet* memptr
@param MP_Integer* length
@param MP_Octet** valptr
@retval return値は使ったバイト数
*/
STDMETHOD(Decode)(MP_Octet* memptr, MP_Integer* length, MP_Octet** valptr) PURE;
/*!
tagをエンコードしmemPtrに書き込む。
@param MP_Octet* memptr
@param MP_Integer tag
@retval 使ったバイト数を返す
*/
STDMETHOD(EncodeTag)(MP_Octet* memptr, MP_Integer tag) PURE;
/*!
valueをエンコードしmemPtrに書き込む。
@param MP_Octet* memptr
@param MP_Integer length
@param MP_Octet* valptr
@retval 使ったバイト数を返す
*/
STDMETHOD(Encode)(MP_Octet* memptr, MP_Integer length, const MP_Octet* valptr) PURE;
/*!
int4値をエンコードしmemPtrに書き込む。
@param MP_Octet* memptr
@param MP_Integer value
@retval 使ったバイト数を返す
*/
STDMETHOD(Encode)(MP_Octet* memptr, MP_Integer value) PURE;
};

/*
§7.2.4 IMediaIDManager インタフェース
*/

/*
§7.2.4.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IMediaIDManager, 0x1359);

/*
§7.2.4.2 メソッド一覧
*/
/*!
@note 
	"#mid"		子供にセットされる、親が管理する各オブジェクトのmid	<br>
	"lastmid"	通常は親オブジェクトにセットし、最後にアサインした"#mid"番号を保持する。<br>
	"mid_bcont"	cdoc下の参照stgobjにセット。どのbcontを参照しているか。"pageroot/bpage/bcont"の３階層をパックした値。<br>
	"mid_cdoc"	bodycontにセットする。このbcontはどのcdocから参照されているか。"cdocroot/cdoc"の２階層をパックした値。<br>
*/
mpinterface IMediaIDManager {
/*!
@param IStgObject* stgobj
*/
STDMETHOD(GetMID)(IStgObject* stgobj) PURE;
/*!
@param IStgObject* midkeeper
@param IStgObject* midslave
@note 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(GenerateMID)(IStgObject* midkeeper, IStgObject* midslave) PURE;
/*!
@param IStgObject* parent
@param MP_Integer mid
@param MP_Integer* rtn_nth
@param MP_Integer has_part
@param IStgObject** rtn_part
@param HRESULT* phres
@retval IStgObject*
*/
STDMETHOD_(IStgObject*, GetChildFromMID)(IStgObject* parent, MP_Integer mid, MP_Integer* rtn_nth = NULL, MP_Integer has_part = MP_NOPART, IStgObject** rtn_part = NULL, HRESULT* phres = NULL) PURE;
/*!
@param IStgObject* midslave
@note 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(StripMID)(IStgObject* midslave) PURE;
/*!
@param MP_AValue* avalue
@param MP_PtrArray* array
*/
STDMETHOD(EncodeRefMID)(MP_AValue* avalue, MP_PtrArray* array) PURE;
/*!
@param MP_AValue* avalue
@param MP_PtrArray* array
*/
STDMETHOD(DecodeRefMID)(MP_AValue* avalue, MP_PtrArray* array) PURE;
};
/*
§7.2.5 MPC_BigAlloc インタフェース
*/
/*
§7.2.5.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_MPC_BigAlloc, 0x1378);

/*
§7.2.5.2 メソッド一覧
*/
mpinterface MPC_BigAlloc {
/*!
引数sizeで指定されるサイズの領域を確保して、その結果を返す。
@param MP_Integer size 確保したい領域のサイズをバイト数で指定する
@retval 成功 MP_NOERRORを返す。
@retval 失敗 MP_E_INVALIDARG（引数が不正）、またはMP_E_UNEXPECTED（予期せぬエラー）を返す。
*/
STDMETHOD_(void*, Allocate)(MP_Integer size) PURE;
/*!
::Allocate()により確保した領域を解放する。
@param void* bigAllocPtr ::Allocate()により確保した領域の先頭アドレスを指定する
*/
STDMETHOD(Free)(void* bigAllocPtr) PURE;

// WindowsMobile対応
// 09/12/03 M.Chikyu
#ifdef _M3CORE_MP_

//
// 既存のファイルをメモリマップドファイルでラージメモリ空間に割り当てる
// READONLY
//
STDMETHOD_(void*, AllocateEx)(const MP_WPath *path, long offset, long size, bool fileDelete = false) PURE;

//
// 参照ポインタを作成する
//
STDMETHOD_(void*, GetRefPointer)(void* orgPointer, void* refPointer = NULL) PURE;

//
// 既存のメモリ領域をReadOnlyで再オープンする
//
STDMETHOD_(void*, ChangeReadOnly)(void* oldPointer, long size) PURE;

#endif

};

/*
§7.3 文書要素オブジェクトの内部インタフェース
*/

/*
§7.3.1 IPersistMPCObject インタフェース
*/
/*
§7.3.1.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IPersistMPCObject, 0x1350);

/*
§7.3.1.2 メソッド一覧
*/
mpinterface IPersistMPCObject {
/*!
このオブジェクトと子孫が更新されているかどうかを問い合わせる。

IsDirty()をコールされたオブジェクトは、<br>
・自身の内容が変化している場合には、MP_S_OKを応答する。<br>
・変更が無く、保存の必要が無い場合は、MP_S_FALSEを返す。<br>
 一度Dirty状態になったオブジェクトは、SaveComplete()を受け取った時点で、Dirty状態を解除できる。

@par 親オブジェクトの処理
　子をメモリにロードしているオブジェクトは、<br>
　たとえ自身がDirty状態でなくても、ロード済みの子に対してIsDirty()を発行し、<br>
　１つ以上の子からMP_S_OKを受け取ったら、自身もMP_S_OKを返さなければならない。<br>

　逆に自身がIsDirtyであれば子のIsDirty()をコールせずにMP_S_OKを返してよい。

@par body-contentに関する注意
　body-contentは、ロード状況によってBasicPageとContDocから２回IsDirty()がコールされる場合があるので留意する。
@retval MP_S_OK		更新有り（保存が必要）
@retval MP_S_FALSE	更新無し（保存不要）
*/
STDMETHOD(IsDirty)() PURE;
/*!
このオブジェクトの更新をストレージに格納する前にコールされる。

@retval IStgObject*	必ず、OnLoad、OnCreateで受け取ったIStgObjectを返す。
@note 
Synchronize()をコールされたオブジェクトは、<br>
OnLoad、OnCreateで受け取ったIStgObjectに、自身の状態をセットして、IStgObjectを返す。<br>
Synchronizeでセットしなかった情報はDWファイルに永続化されない。<br>

@par IsDirty()　と Synchronize()　の依存関係<br>
　１、更新が必要な場合、IsDirtyでMP_S_OKを返すこと。<br>
　　　IsDirty()でMP_S_FALSEを返した場合、Synchronize()が呼ばれずにファイルに保存される場合がある。<br>
　２、IsDirty()を呼ばずに直接Synchronize()を呼ばれる場合もある。

@par SynchronizeとSaveCompleteとIsDirtyの関係
	各オブジェクトは、Synchronize()が完了しても、
	SaveComplete()をコールされるまではDirty状態を維持する。
	SaveCompleteが呼ばれてはじめてファイルへの永続化が成功したと判断し、Dirty状態をクリアする。

@par 親オブジェクトの処理
	子をメモリにロードしているオブジェクトは、IsDirty()でMP_S_OKを返した子のSynchronize()をコールする義務がある。<br>
	IsDirty()でMP_S_OKを返さないオブジェクトのSynchronize()はコールしてもしなくてもよい。<br>
	メモリにロードされていない従属オブジェクトのSynchronize()はコールする必要がない。<br>
	子のSynchronizeからIStgObjectが戻らなかった場合の扱いは自由である。<br>

@par body-contentに関する注意
	body-contentは、BasicPageとContDocから２回Synchronize()がコールされる場合があるので留意する。<br>

@par 追記保存と属性の更新
	変更があった属性だけをセットする事が望ましい。<br>
	特にサイズが１ＫＢを超える属性は、保存性能向上のために<br>
	ストレージ内部での全データ比較判定は行わず無条件にファイルに出力する。<br>
	各モデルで、変更があったばあいのみセットするよう強く推奨する。<br>
*/
STDMETHOD_(IStgObject*, Synchronize)() PURE;
/*!
ストレージへの保存が完了した場合、あるいは最初に受け取ったIStgObjectが無効になった場合にコールされる。
@param IStgObject* stgobj
@note SaveCompletedをコールされたオブジェクトは、次の処理を行う。<br>
1. 自身のDirty状態(IsDirtyの応答値の状態変数の事）をクリアする。<br>
2. 保持しているIStgObjectを、渡されたstgobjに持ち変える。<br>
3. SaveCompleted()がコールされた時、保持していたIStgObjectは既に無効になっている場合がある。<br>
	古いIStgObjectを参照してはならないし解放する必要もない。

@par 親オブジェクトの処理
子をメモリにロードしているオブジェクトは、
ロード済みの子のSaveCompleted()をコールする義務がある。
@par
この時の子に渡すstgobjは、新しく渡された自身のIStgObjectから、
新たにGetNthChildで取得して渡さなければならない。

@par body-contentに関する注意
	body-contentは、BasicPageとContDocから２回SaveCompleted()がコールされる場合があるので留意する。
*/
STDMETHOD(SaveCompleted)(IStgObject* stgobj) PURE;
/*!
ファイルに結びついていないメモリオブジェクトを生成した場合に呼ぶ。

OnCreateをコールされたオブジェクトは、自身が新規生成された事を知り、
自身とIStgObjectの初期化を行う。

OnCreate() をコールされたオブジェクトは、その後即座にセーブされても構わない様に、オブジェクトの初期状態を構築しなければならない。
@param IStgObject* stgobj このオブジェクトの内容をストレージに記録する時のインタフェース
@param MPCSession* session	このオブジェクトが属するセッションオブジェクト
*/
STDMETHOD(OnCreate)(IStgObject* stgobj, MPCSession* session) PURE;
/*!
ストレージに格納されていた永続化情報から<br>
オブジェクトがメモリにロードされた時にコールされる。

parentは、このオブジェクトをロードした親オブジェクトである。<br>
ルートオブジェクトの場合NULLが渡される。<br>
MPCObject::GetParent()の実装は、このparentを返す。

stgobjは、ストレージ層へのインタフェースとして保持し、<br>
SaveCompletedが呼ばれるまでの間、必要に応じて更新できる。

@par 親オブジェクトの処理
子を持つオブジェクトは、OnLoad() をコールされた時点では自身の初期化のみ行えばよい。<br>
従属オブジェクトを再帰的にロードすべきではない。
@par
親オブジェクトは、MPCObject::GetNthChild()の実装の中で、<br>
　1. 自身が管理する構造の中から対応するIStgObjectを取得し、<br>
　2. オブジェクト種別に対応するオブジェクトを生成するようローダに要求し、<br>
　3. 生成されたオブジェクトのOnLoadをコールしてIStgObjectインタフェースを渡す。<br>
という処理を行う必要がある。
@param IStgObject* stgobj このオブジェクトの内容を記録したストレージインタフェース
@param MPCObject* parent このオブジェクトをロードした親オブジェクト
@param MPCSession* session このオブジェクトが属するセッションオブジェクト
*/
STDMETHOD(OnLoad)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) PURE;
/*!
@warning 現在この関数は使われていない。

旧版とのバイナリ互換性維持のためだけに残されている。
新しくコンテントを実装する場合は、何も実行せずに、
常に MP_E_NOTIMPL　を返すよう実装しなければならない。
*/
STDMETHOD(OnReload)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) PURE;
/*!
オブジェクトに対して、子オブジェクトの解放を要求する。

従属オブジェクトを持つオブジェクトは、<br>
nthで指定された従属オブジェクトをメモリにロードしている場合、<br>
従属オブジェクトのUnload()をコールし、自身のロード済みリストから除外する。

指定されたオブジェクトをメモリにロードしていない場合は何もしなくてよい。

UnloadChildに限り、nthが-1（MP_ALL_CHILDREN）の場合、末尾ではなく"全て"を意味する。<br>
MP_ALL_CHILDRENの場合、自分がロードしている全ての子オブジェクトをアンロードする。
@param MP_Integer nth	
*/
STDMETHOD(UnloadChild)(MP_Integer nth = MP_ALL_CHILDREN) PURE;
/*!
親オブジェクトが従属オブジェクトをアンロードする場合に使う。

Unloadをコールされたオブジェクトは<br>
自分がロードしている全ての従属オブジェクトにUnloadを発行した後、<br>
親オブジェクトがいる場合でも自身をDestroyしメモリから解放する。

通常のDestroyは親オブジェクトがいる場合はエラーとなる点が異なる。<br>
親以外の第３者がUnloadをコールしてはならない。
@param MPCObject* parent このオブジェクトをロードした親オブジェクト

*/
STDMETHOD(Unload)(MPCObject* parent) PURE;
};
/*
§7.3.2 IContent インタフェース
		Contentモデルオブジェクトが実装し、ＭＰに提供する
*/
/*
§7.3.2.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_IContent, 0x1354);
/*
§7.3.2.2 メソッド一覧
*/
mpinterface IContent  {
/*!
「貼る前」通知
containerがcontentに貼れるかどうかを問い合わせる。
contentは拒否できる。

@param MPCObject* parent 親
@param MP_Integer nth 挿入位置
@param MP_Attrs* part_attrs パート属性
@retval MP_S_OK		リンク可能
@retval その他		リンク拒否

*/
STDMETHOD(PreAttach)(MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs) PURE;
/*!
「貼った後」通知

containerがcontentを貼った時、このI/Fでcontentに伝える。<br>
contentは通知要求を登録したり、はみ出し要求を発行したり、MPと対話できる。

@warning 1998.6.16 AR2837対策のため、<br>
		PreAttach, PostAttatch中に親に対してSetAttribute, SetPartAttributeを<br>
		実行しても通知が発生しないようパッチを入れた。<br>
		この中で見栄えの変更やサイズ変更を行ってもアプリケーションに<br>
		通知されない事に注意する。<br>
@param MPCObject* parent 親
@param MP_Integer nth 挿入位置
@param MP_Attrs* part_attrs パート属性
*/
STDMETHOD(PostAttach)(MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs) PURE;
/*!
「剥がす前」通知

containerがcontentを剥がす前に、このI/Fでcontentに伝える。<br>
contentは通知要求を解除したり、ログを残すなどMPと対話できる。

contentはdetachを拒否できる。
@param MPCObject* parent 親
@param MP_Integer nth 剥がすコンテントの位置
@retval MP_S_OK		アンリンク可能
@retval その他		アンリンク拒否
*/
STDMETHOD(PreDetach)(MPCObject* parent, MP_Integer nth) PURE;
/*!
「剥がした後」通知

containerがcontentをunlinkした後に、このI/Fでcontentに伝える。
@param MPCObject* parent 親
@param MP_Integer nth 剥がすコンテントの位置
*/
STDMETHOD(PostDetach)(MPCObject* parent, MP_Integer nth) PURE;
};
/*
§7.3.3 IContainer インタフェース
		MetaPaperが実装し、Contentに提供する
*/
/*
§7.3.3.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IContainer, 0x1353);

/*
§7.3.3.2 メソッド一覧
*/
//! IContainer　変化通知用　ビットフラグ
typedef MP_Integer MP_ContentChangeInfo;
const MP_ContentChangeInfo	MP_CONTENTCHANGEINFO_PRESENTATION = 0x1;
const MP_ContentChangeInfo	MP_CONTENTCHANGEINFO_DIMENSION = 0x2;
const MP_ContentChangeInfo	MP_CONTENTCHANGEINFO_DOCUMENT = 0x4;
const MP_ContentChangeInfo	MP_CONTENTCHANGEINFO_DATE = 0x8;
const MP_ContentChangeInfo	MP_CONTENTCHANGEINFO_ROTATE = 0x10;

mpinterface IContainer  {
/*!
content変更事前通知

contentは、自身の表示状態や寸法を変える前に、このメソッドを使ってcontainerに通知する義務がある。MPから拒否が返された場合、その変更を中止する。

@param MPCObject* content 変化するコンテント（自分自身）のアドレス
@param MP_ContentChangeInfo change_info 変化の内容

@note
change_info は以下の値のビットＯＲによる組み合わせである。<br>
MP_CONTENTCHANGEINFO_PRESENTATION　　見栄えの変化<br>
MP_CONTENTCHANGEINFO_DIMENSION　　　サイズの変更<br>
MP_CONTENTCHANGEINFO_DOCUMENT　　　　ドキュメントの編集にあたる (DID破棄要求)<br>
MP_CONTENTCHANGEINFO_DATE　　　　　　最終変更日時更新の要求<br>

*/
STDMETHOD(PreChangeContent)(MPCObject* content, MP_ContentChangeInfo change_info) PURE;
/*!
rectは、見栄えの変化のときの見栄えが変わる領域を示す。<br>
contentは、自分の表示状態が変わった場合、このメソッドでcontainerに通知する義務がある。

@param MPCObject* content 変化するコンテント（自分自身）のアドレス
@param MP_ContentChangeInfo change_info 変化の内容
@param MP_Rect rect = MP_NULL_RECT 変化した領域
@note
change-infoの意味は、PreChangeContentと同じ。
*/
STDMETHOD(PostChangeContent)(MPCObject* content, MP_ContentChangeInfo change_info, MP_Rect rect = MP_NULL_RECT) PURE;
/*!
@warning 現在この関数は使われていない。
@note
旧版とのバイナリ互換性維持のためだけに残されている。
新しくコンテントを実装する場合は、何も実行せずに、
常に MP_E_NOTIMPL　を返すよう実装しなければならない。
@param MPCObject* content 変化するコンテント（自分自身）のアドレス
@param MP_Pos position 新しいコンテント貼り付け位置（増減分）
*/
STDMETHOD(MoveXYPosition)(MPCObject* content, MP_Pos position) PURE;
};
/*
§7.3.3.3 各メソッドの定義
Contentコアオブジェクト実装者は、
	contentの文書可視化内容が変化する場合
	contetnのサイズ(領域）が変化する場合
	文書の編集にあたる内部変化があった場合
	ＭＰの最終日時更新が必要な場合
PreChangeContent, PostChangeContentでＭＰに通知する義務がある
*/

/*
§7.3.4 IContDocument インタフェース
		ContDocオブジェクトが実装し、MetaPaper に提供する
*/
/*
§7.3.4.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IContDocument,0x1356);

/*
§7.3.4.2 メソッド一覧
*/
mpinterface IContDocument {
/*!
「テイクイン前」通知

MPがcontent-documentをリンクする前に、このI/Fでcontent-documentに伝える。<br>
content-documentはリンクを拒否できる。
@param MPCObject* cdoc_root MetaPaperオブジェクトの ContDocRootインタフェースのアドレス
@param MP_Integer nth ContDocRootへの挿入位置
@retval MP_S_OK MPはこのContDocを載せる。
@retval MP_S_OK以外 MPはContDocを載せない。
*/
STDMETHOD(PreTakeIn)(MPCObject* cdoc_root, MP_Integer nth) PURE;
/*!
「テイクイン後」通知

MPがcontent-documentを載せた時、このI/Fでcontent-documentに伝える。
@param MPCObject* cdoc_root MetaPaperオブジェクトの ContDocRootインタフェースのアドレス
@param MP_Integer nth ContDocRootへの挿入位置
*/
STDMETHOD(PostTakeIn)(MPCObject* cdoc_root, MP_Integer nth) PURE;
/*!
「テイクアウト前」通知

MPがcontent-documentをアンリンクする前に、このI/Fでcontent-documentに伝える。<br>
content-documentはアンリンクを拒否できる。
@param MPCObject* cdoc_root MetaPaperオブジェクトの ContDocRootインタフェースのアドレス
@param MP_Integer nth ContDocRootから降ろすContDocの位置
@retval MP_S_OK MPはこのContDocを降ろす。
@retval MP_S_OK以外 MPはContDocを降ろさない。
*/
STDMETHOD(PreTakeOut)(MPCObject* cdoc_root, MP_Integer nth) PURE;
/*!
「テイクアウト後」通知

MPがcontent-documentをアンリンクした後に、このI/Fでcontent-documentに伝える。
@param MPCObject* cdoc_root
@param MP_Integer nth
*/
STDMETHOD(PostTakeOut)(MPCObject* cdoc_root, MP_Integer nth) PURE;
/*!
body-contentの参照化指示

basic-pageがbody-contentをLinkChildする際にコールされる。<br>
このメソッドをコールされたcontent-documentは、bcontをアンリンクして引き渡す。

cont-docは、body-contentがあった位置に代わりにrefmidを記録しておく。<br>
以降、body-contentを参照する場合は、IMPContDocInteraction::GetReferenceContentを使ってMPに取得要求する。

自分の子供の中に、bcontが存在しない場合はエラーを返す。
@param MPCObject* bcont ContDocがアンリンクしなければならないBodyContのアドレス
@param MP_AValue* refmid BodyContent参照用の情報
*/
STDMETHOD(UnlinkAndReferTo)(MPCObject* bcont, MP_AValue* refmid) PURE;
/*!
参照しているbody-contentがMPからアンリンク時にコールされる。

MPからbody-contentがアンリンクされるケースは<br>
　１、basic-pageがbody-contentをUnlinkChild() する場合<br>
　２、MPがbasic-pageをUnlinkChild() する場合<br>
の２つがある。

このbody-contentを参照しているcontent-documentに対して
NotifyDetachReference発行する。

content-documentは、保持していた参照情報を破棄しなければならない。
@param MP_AValue* refmid
@param MPCObject* bcont
*/
STDMETHOD(NotifyDetachReference)(MP_AValue* refmid, MPCObject* bcont) PURE;
};
/*
§7.3.5 IMPContDocInteraction インタフェース
*		ＭＰが実装し、ContDocに提供する
*/

/*
§7.3.5.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IMPContDocInteraction, 0x1355);

/*
§7.3.5.2 メソッド一覧
*/
mpinterface IMPContDocInteraction {
/*!
content-documentがrefidで参照しているbody-contentを取得する時に使う。

MPは、refidに対応するbody-contentを見つけて、そのアドレスを返す。
見つからなかった場合は、エラーを返す。

主にcontent-documentのGetNthChild()からの利用を想定している。
@param MPCObject* cdoc 呼び出し元のcontent-document
@param MP_AValue* refid 参照情報
@param HRESULT* phres 結果コードへのアドレス
@retval MPCObject*		refidに対応するbody-contentのアドレス
*/
STDMETHOD_(MPCObject*, GetReferenceContent)(MPCObject* cdoc, MP_AValue* refid, HRESULT* phres=NULL) PURE;
/*!
MPの中にbcontがいるかどうかを探す。

bcontが見つかったら、cdocによって参照されているかどうか確認する。<br>
参照されている場合は、body-contentの参照IDを返す。<br>
見つからなかった場合はエラーを返す。

主にcontent-documentのGetChildPosition()からの利用を想定している。
@param MPCObject* cdoc 呼び出し元のcontent-document
@param MPCObject* bcont 参照情報を取得したいbody-content
@param MP_AValue* rtn_refid 結果を返すための参照情報領域
*/
STDMETHOD(GetReferenceID)(MPCObject* cdoc, MPCObject* bcont, MP_AValue* rtn_refid) PURE;
/*!
content-documentがbody-contentを参照する場合に使う。

これは、content-documentが、既にbasic-pageに従属しているbody-contentをLinkChildされた場合に、参照関係を生成する場合の利用を想定している。
@param MPCObject* cdoc
@param MPCObject* bcont
@param MP_AValue* rtn_refid
@par セキュリティ
文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
@note 
MPは、<br>
　　1. bcontで指定されたbody-contentがbasic-pageに従属している事<br>
　　2. content-documentがこのMPに従属している事<br>
　　3. bcontは他のcontent-documentから参照されていない事<br>
　など、処理可能か確認した後、MP内部に被参照情報を設定し、参照IDを返す。
*/
STDMETHOD(CreateReferenceID)(MPCObject* cdoc, MPCObject* bcont, MP_AValue* rtn_refid) PURE;
/*!
content-documentがbody-contentを参照しなくなった事をMPに通知する。

これは<br>
　　１、content-documentがMPからUnlinkChildされる場合、<br>
　　２、body-contentがcontent-documentからUnlinkChildされる場合<br>
　に発行される。

これを受けたMPは、body-contentに関する被参照情報をクリアする。
@param MPCObject* cdoc
@param MP_AValue* refid
@par セキュリティ
文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(NotifyDetachReference)(MPCObject* cdoc, MP_AValue* refid) PURE;
};

/*
§7.3.6 IReferenceMID インタフェース
*/

/*
§7.3.6.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IReferenceMID, 0x1361);
/*
§7.3.6.2 メソッド一覧
*/
mpinterface IReferenceMID  {
/*!
@param MP_PtrArray* midarray
@param IStgObject** rtn_stgobj
@param IStgObject** rtn_part
@param HRESULT* phres
@retval MPCObject*
*/
STDMETHOD_(MPCObject*, GetReferenceObject)(MP_PtrArray* midarray, IStgObject** rtn_stgobj = NULL, IStgObject** rtn_part = NULL, HRESULT* phres = NULL) PURE;
/*!
@param MP_PtrArray* midarray
@param MPCObject* mpcchild
@param MPCObject** rtn_ancestor
*/
STDMETHOD(GenerateMIDArray)(MP_PtrArray* midarray, MPCObject* mpcchild, MPCObject** rtn_ancestor) PURE;
};
/*
§7.4 ストレージオブジェクト

DWCoreが扱う文書要素オブジェクトの最小単位
ドキュメントデータモデル層の各文書要素オブジェクトは１つ以上のストレージオブジェクトを保持できる。
ストレージオブジェクトは、属性操作と階層構造操作を永続化する。

*/
/*
§7.4.1 ストレージオブジェクトの生成と破棄
*/
/*
§7.4.1.1 生成
*/

/*
§7.4.1.2 破棄
*/

/*
§7.4.2 IStgObject インタフェース
*/
/*
§7.4.2.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_IStgObject, 0x1372);

/*
§7.4.2.2 メソッド一覧
*/
mpinterface IStgObject : public MPCInterface {
//Basic Method
/*!
自身をルートとするIStgObjectツリーの複製を生成して返す。

複製結果はファイルに結びついていない。
@param HRESULT* phres 結果コードへのアドレス
@retval IStgObject* 複製結果のスクラッチオブジェクト
@par セキュリティ
転記禁止の場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD_(IStgObject*,Duplicate)(HRESULT* phres = NULL) PURE;
/*!
従属構造を含まない、自身だけの複製を生成して返す。
複製結果はファイルに結びついていない。
転記禁止の場合、MP_ACCESSDENIEDエラーになる。
@param HRESULT* phres 結果コードへのアドレス
@retval IStgObject* 複製結果のスクラッチオブジェクト
@par セキュリティ
転記禁止の場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD_(IStgObject*,ShallowDuplicate)(HRESULT* phres = NULL) PURE;
/*!
ファイルに結びついていないストレージオブジェクトを１つ生成し、
そのIStgObjectインタフェースを返す。
@param MP_RefObjectType clsid オブジェクト種別
@param HRESULT* phres 結果コードへのアドレス
@retval IStgObject* 新たに生成したストレージオブジェクト
*/
STDMETHOD_(IStgObject*, CreateIStgObject)(MP_RefObjectType clsid, HRESULT* phres = NULL) PURE;
// Methods for children
/*!
従属オブジェクトの数を返す
@retval ０以上の値 従属オブジェクトの数
*/
STDMETHOD(GetNumberOfChildren)() PURE;
/*!
nth 番目の従属オブジェクトを取得する。
@param long nth
@param  HRESULT* phres 結果コードへのアドレス
@retval IStgObject* nth 番目の従属オブジェクト
*/
STDMETHOD_(IStgObject*,GetNthChild)(long nth, HRESULT* phres = NULL) PURE;
/*!
指定したstgobjが自身のこの場合、nth位置を返す。
@param IStgObject* obj
@retval ０以上の整数	stgobjの位置
@retval 従属オブジェクトでない場合はエラーを返す。
*/
STDMETHOD(GetChildPosition)(IStgObject* obj) PURE;
/*!
stgobjをnth位置に挿入する。

stgobjが、他のストレージオブジェクトに従属している場合は失敗する。
	
@param IStgObject* obj
@param long nth
@par セキュリティ
文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(InsertChild)(IStgObject* obj, long nth) PURE;
/*!
nth位置の子との従属関係を削除して（＝アンリンクして）返す。

@param long nth
@param HRESULT* phres 結果コードへのアドレス

@retval IStgObject* アンリンクされた子

@par セキュリティ
文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。

@note 
転記禁止の場合は、IStgObjectをリターンし、かつ、phresは MP_E_PROTECTED_OBJECT エラーになる。<br>
このIStgObjectは、同一のファイルに再びInsertChildするまで、内部にアクセスできない。<br>
これはUndo機能などを実現するための特殊仕様である。
*/
STDMETHOD_(IStgObject*,RemoveChild)(long nth, HRESULT* phres = NULL) PURE;
// Methods for attributes
/*!
ストレージオブジェクトに属性をセットする。
パラメータの定義は、MPCObject::SetAttribute() と同じである。

do_assignは、もし指定した属性名が未定義だった場合に
属性定義処理をするかエラーとするかの指定である。

@param MP_AName* aname
@param MP_AValue* avalue
@param MP_Integer nth_element
@param MP_Integer do_assign 1:未定義の場合は属性定義する。0:未定義の場合はエラー復帰する
@note セキュリティ
文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_ACCESSDENIEDエラーになる。<br>
但し、#color、lastmid、canrotate はSet可能。
*/
STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue = NULL, MP_Integer nth_element = -1, MP_Integer do_assign = 1) PURE;
/*!
ファイルの内容を読み込み、ストレージオブジェクトに属性としてセットする。

do_assignは、IStgObject::SetAttribute参照

@param MP_AName* aname
@param MP_Path* path
@param MP_Integer nth_element
@param MP_Integer do_assign

@note 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_ACCESSDENIEDエラーになる。
但し、#color、lastmid、canrotate はSet可能。
	
@note
 パラメータの定義は、MPCObject::SetAttributeF() と同じである。
*/
STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1, MP_Integer do_assign = 1) PURE;
/*!
ストレージオブジェクトの属性を取り出す。

@param MP_AName* aname
@param MP_AValue* rtn_avalue
@param MP_Integer nth_element = -1
	
@par セキュリティ
#pd属性は属性として取得できない。MP_E_ACCESSDENIEDエラーになる。<br>
転記禁止の場合、nd属性をGetしようとするとMP_E_ACCESSDENIEDエラーになる。<br>
nd属性がSetされていないオブジェクトに対してGetした場合の動作はTBD

@note
パラメータの定義は、MPCObject::GetAttribute() と同じである。
*/
STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1) PURE;
/*!
§GetAttributeF
ストレージオブジェクトの属性をファイルに取り出す。

@param MP_AName* aname
@param MP_Path* path
@param MP_Integer nth_element
@par セキュリティ
#pd属性は属性として取得できない。MP_E_ACCESSDENIEDエラーになる。<br>
転記禁止の場合、nd属性をGetしようとするとMP_E_ACCESSDENIEDエラーになる。<br>
nd属性がSetされていないオブジェクトに対してGetした場合の動作はTBD

@note
パラメータの定義は、MPCObject::GetAttributeF() と同じである。
*/
STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1) PURE;
/*!
ストレージオブジェクトの属性を数え上げる。

@param MP_AName* aname
@param MP_Integer namesize

@note
パラメータの定義は、MPCObject::EnumAttribute() と同じである。

*/
STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize) PURE;

// misc. methods
/*!
ストレージのバージョンを問い合わせる。

@note 
V3.0で生成されたストレージは 6 を返す。<br>
V2.0で生成されたストレージをロードした場合、<br>
最初にファイルに格納されるまで 5 が返される。<br>
一度DWファイルに保存すると、次回のアクセスから 6 が返される。
*/
STDMETHOD(GetStorageVersion)() PURE;
/*!
ストレージオブジェクトの種類を取得する。

@retval MP_ObjectType
@note 
CreateIStgObjectで指定したclsid<br>
または、SetObjectTypeで設定した値が返される。<br>

*/
STDMETHOD_(MP_ObjectType, GetObjectType)() PURE;
/*!
ストレージオブジェクトの種類を後から変更する。<br>
@param MP_RefObjectType clsid
@warning 
一般には、当事者以外の第3者がオブジェクト種別を変えてはならない。<br>
特殊用途に限られる。<br>
V4で削除する。

*/
STDMETHOD(SetObjectType)(MP_RefObjectType clsid) PURE;
/*!
現在時刻情報を指定された属性にセットする。

セットする情報は、ランタイムライブラリ関数　time() で得た整数である。

anameにNULL（省略）を指定した場合、"#updatetime"にセットする。

@warning
本メソッドは外部仕様に連結していないため削除する可能性がある。
V4で削除する。
@param MP_AName* aname 時刻をセットする属性名
@note
time() の仕様は、<br>
「システム クロックに従って、<br>
　万国標準時 (UCT) の 1970 年 1 月 1 日の 00:00:00 からの経過時間を<br>
　秒単位で表した数値を返します。」
*/
STDMETHOD(SetCurrentDateTime)(const MP_AName* aname = NULL ) PURE;
/*!
このストレージオブジェクトが結びついているファイルパスをpathにセットして返す。

ファイルパスは、MPCSession::OpenFile、MPCSession::SaveAs で指定されたパス文字列である。<br>
sizeの領域が足りない場合、MP_E_INSUFFICIENT_BUFFERを返す。<br>
スクラッチオブジェクトに対して発行された場合MP_E_INVALIDARGを返す。<br>
MP_NOERROR以外のリターン値の場合、pathには値をセットしない。

@param MP_Integer size	pathに用意した領域のサイズ（単位　バイト）
@param MP_Path* path	ファイルパスを受け取る領域

@retval MP_NOERROR					取得成功
@retval MP_E_INSUFFICIENT_BUFFER	領域のサイズが足りない。
@retval MP_E_INVALIDARG				このストレージオブジェクトはファイルに結びついていない。
*/
STDMETHOD(GetFilePath)(MP_Integer size, MP_Path* path) PURE;

// V4 Security
/*!
OpenMPを実行し、成功すると、文書（またはバインダ）の内部にアクセスできるようになる。<br>
一度OpenMP()を発行すると、CloseFile() するまで有効である。

バインダの内部DW文書について

バインダ内部の各DW文書は、OpenMP()をコールする必要はない。
コールした場合、
　文書が保護されていなければ、何回コールしてもMP_NOERROR になる。
　文書が保護されている場合、
　　auth == NULL ならば、何回コールしても、MP_S_PROTECTED_BY_* になる。
	auth != NULL ならば、MP_E_INVALID_CALL になる。（バインダで OpenMP()が成功しているとみなす）

・auth->perm について
　auth->permは、１つの文書に複数の認可情報が設定されている場合にのみ意味がある。
例えばDDSAは１文書に複数のチケットを設定でき、チケットによってパーミッションが異なる場合がある。
この時、指定したパーミッションを持つチケットで認証するよう特定するためのヒントとして使う。
通常に開く場合、auth->perm = 0 とする。
auth->perm == 0 の場合は、一番始めに見つかったチケットで認証を行う。
もし 0 以外を指定した場合、指定したパーミッションで認証できなかった場合はエラーを返す。
auth->perm に MP_PERM_FULL を指定することはできない。含まれている場合はエラーを返す。
(いきなりフルアクセスモードで開くことはできない仕様)
（パスワードの場合は文書に設定されているパーミッションは１つなので無関係）

@param MP_AuthInfo* auth	 認証用情報（Ｖ３では常にNULLを指定する）

@retval MP_NOERROR : 成功
@retval MP_S_PROTECTED_BY_*			セキュリティモジュールによって保護されている(正の値であることに注意)
@retval MP_S_PROCESS_CANCELED		キャンセルされた
@retval MP_E_AUTH_FAILED			認証に失敗した。必要であれば Viewer 等でエラーメッセージを表示する。
@retval MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗したが、セキュリティモジュールでエラー表示したので Viewer 等ではメッセージ表示しないでほしい。
@retval MP_E_INVALID_CALL			認証が成功しているのに auth が指定されて呼ばれた
@note 
文書が保護されていない場合、
　　　OpenMPは 常に成功し MP_NOERROR になる。（auth の値は無視される。）
@note
文書が保護されていて、auth == NULL の場合は、<br>
　　　MP_S_PROTECTED_BY_PSWD　　　パスワードによって保護されている<br>
　　　MP_S_PROTECTED_BY_DDSA　　　DDSAによって保護されている<br>
を返す。<br>
@note
文書が保護されていて、auth を指定した場合は、authで指定した条件で認証処理を行う。<br>
auth->mode は、対話操作の有無を指定する。<br>
　　　MP_AUTH_DIALOGUE を指定すると、必要があれば対話操作を実行して認証を行う<br>
　　　MP_AUTH_NODIALOGUE を指定すると、対話操作なしで認証できる場合に限り認証を行う。<br>
　　　対話操作を実行しないと認証できない場合、OpenMPは失敗し MP_E_AUTH_FAILEDを返す。<br>
@note
auth->permは、その後の処理に必要な権利を限定する場合に指定する。<br>
　　　通常に開く場合は 0 を指定する。<br>
　　　印刷を実行するために開く場合は、MP_PERM_PRINT を指定する。
@note
認証に成功すると MP_NOERROR を返す。<br>
一旦認証したパーミッションは、CloseFile() するまで有効である。<br>
保護された文書の場合、既に認証が成功しているのに auth が指定されて呼ばれた場合は MP_E_INVALID_CALL になる。

*/
// 12.02.17 Bito - セキュリティ対応
#ifndef _SEC_MP_
STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL) PURE;
#else
// セキュリティ認証に必要なデータを引数に追加
STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL, void* authdata = NULL) PURE;
#endif
/*!
perm で指定されたパーミッションに対する追加認証を行う。

この関数が呼ばれると、セキュリティモジュールが認証ダイアログを出す。

フルアクセスモードになりたい場合は AddAuthentication(MP_PERM_FULL) とすればよい。<br>
既に認証済みのパーミッションが指定された場合は、内部では何もせずに成功を返す。<br>
一旦認証したパーミッションは、CloseFile() するまで有効である。<br>
OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
	
@param MP_Permission perm		パーミッション情報

@retval HRESULT	結果コード
@retval MP_NOERROR (==0)			成功
@retval MP_S_PROCESS_CANCELED		キャンセルされた
@retval MP_E_AUTH_FAILED			認証に失敗した。必要であれば Viewer 等でエラーメッセージを表示する。
@retval MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗したが、セキュリティモジュールでエラー表示したので Viewer 等ではメッセージ表示しないでほしい。
@retval MP_E_INVALID_CALL			認証が成功する前に呼ばれた
*/
STDMETHOD(AddAuthentication)(MP_Permission perm) PURE;
/*!
文書にセキュリティの設定を行う。

この関数が呼ばれると、セキュリティモジュールが設定ダイアログを出す。<br>
保護されている文書に対して、フルアクセスモードでない場合に呼ばれるとエラーを返す。<br>
OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
 
@retval HRESULT	結果コード
@retval MP_NOERROR (==0)			成功
@retval MP_S_PROCESS_CANCELED		キャンセルされた
@retval MP_S_PROTECTION_REMOVED		解除された
@retval MP_E_INVALID_CALL			認証が成功する前に呼ばれた
*/
STDMETHOD(EditSecurity)() PURE;
/*!
文書に現在設定されているパーミッション情報を返す。
@param HRESULT* phres	結果コード

@retval MP_Permission	文書に設定されているパーミッション情報
@retval エラーの場合はパーミッションなし(全てのビットが0)を返す

@par セキュリティの設定を変更して、
@note
ファイルに保存する前に呼ばれた場合は、ファイルの状態ではなく変更後の状態を返す。
@note
保護されていない場合は全て可能(全てのビットが1)を返す。
@note
hres が指定されていた場合は、<br>
　　　MP_NOERROR　　　　　　　　保護されていない<br>
　　　MP_S_PROTECTED_BY_PSWD　　パスワードによって保護されている<br>
　　　MP_S_PROTECTED_BY_DDSA　　DDSAによって保護されている<br>
　　　負の値　　　　　　　　　　エラー
を格納する。<br>
OpenMP前でも成功する。
	
*/
STDMETHOD_(MP_Permission, GetPermission)(HRESULT* hres = NULL) PURE;
/*!
現在認証されているパーミッション情報を返す。

hres が指定されていた場合は GetPermission() と同じ値を格納する。<br>
OpenMP前には、リターン値に0(全パーミッション無し)、phres に MP_E_ACCESSDENIED を返す。

@param HRESULT* phres	結果コード

@retval MP_Permission	現在認証されているパーミッション情報
@retval エラーの場合はパーミッションなし(全てのビットが0)を返す
*/
STDMETHOD_(MP_Permission, GetAuthenticatedPermission)(HRESULT* hres = NULL) PURE;
/*!
/*!
Desk や Viewer の「文書プロパティ」で、「セキュリティ」タブの「追加情報」を
表示する際に呼ばれる。<br>
OpenMP前でも成功する。

@retval HRESULT	結果コード
@retval MP_NOERROR	成功
@retval 負の値はエラー
*/
STDMETHOD(ShowSecurityInfo)() PURE;
/*!
データチェック用関数

この関数が呼ばれると、ストレージが文書ファイルをチェックし、<br>
BasicPage でエラーがあった場合はその通し番号を nth_page に、<br>
オリジナルデータでエラーがあった場合はその通し番号を nth_org に、<br>
その他の個所でエラーが見つかった場合は others に 1 が格納される。<br>
通し番号は 0 基数で、バインダ文書の場合も同様である。<br>
エラーがない場合は、各変数には -1 が格納され、MP_NOERROR を返す。<br>
時間がかかる処理なので、info による途中経過表示＆キャンセルができる。<br>
キャンセルのやり方は MPCMediaAdv::OnPrint() などを参照すること。

OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。<br>
スクラッチの状態では成功せず、MP_E_INVALID_CALL を返す。

@param MP_Integer* nth_page		一番最初にエラーが見つかった BasicPage の通し番号
@param MP_Integer* nth_org			一番最初にエラーが見つかったオリジナルデータの通し番号
@param MP_Integer* others			その他の個所でエラーが見つかった
@param MPC_AdvCancelInfo* info		キャンセル用構造体

@retval HRESULT	結果コード
@retval MP_NOERROR				エラーはなかった
@retval MP_E_BAD_CHECKSUM		チェックサム不整合エラーがあった
@retval MP_E_BAD_FORMAT_ODOA	改行コード関係のエラーがあった
*/
STDMETHOD(CheckData)(MP_Integer* nth_page, MP_Integer* nth_org, MP_Integer* others, MPC_AdvCancelInfo* info = NULL) PURE;
/*!
ImplBasicPage::OnPrint() 内で、DrawSelf() の前にこの関数を呼ぶこと。

この関数がエラーでも処理を進める。

@param MP_Canvas* pCanvas pCanvas	プリンタキャンバス
@param MPCObject* pBasicPage pBasicPage		印刷するページオブジェクト
@note 
mpc_secu.h内のMPCSecuritySPI::OnBeginPrint()も参照のこと。
*/
STDMETHOD(OnBeginPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage) PURE;
/*!
ImplBasicPage::OnPrint() 内で、印刷が終了する前にこの関数を呼ぶこと。
この関数がエラーでも処理を進める。

@param MP_Canvas* pCanvas プリンタキャンバス
@param MPCObject* pBasicPage 印刷するページオブジェクト
@note
mpc_secu.h内のMPCSecuritySPI::OnEndPrint()も参照のこと。

*/
STDMETHOD(OnEndPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage) PURE;
// V4.1追加
/*!
テンプレートにより、文書に新規にセキュリティの設定を行う。

ダイアログ等のUIは出ない。<br>
保護されている文書に対して呼ばれるとエラーを返す。<br>
OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。<br>
パスワードの場合は、全ての操作が許可されていて、<br>
かつ開く・フルアクセスパスワードが空であった場合は、<br>
保護する意味がないのでMP_E_INVALIDARGエラーを返す。

@param MPC_SecurityTemplate* pTemplate セキュリティテンプレート
	
@retval HRESULT	結果コード
@retval MP_NOERROR (==0) 成功
@retval MP_E_INVALIDARG	テンプレートが不正
@retval MP_E_ACCESSDENIED 認証が成功する前に呼ばれた
*/
STDMETHOD(CreateSecurityWithTemplate)(MPC_SecurityTemplate* pTemplate) PURE;
//V5
STDMETHOD(GetNumberOfObjectsWithGivenType)( MP_ObjectType type ) PURE;
STDMETHOD_(MP_VerificationCondition, MakeVerificationCondition)(HRESULT* phres = NULL) PURE;
STDMETHOD(DestroyDocImage)() PURE;
STDMETHOD(GetSaveStorageVersion)() PURE;
//V6
STDMETHOD(GetTrailerAttribute)(unsigned long iTag, MP_AValue* rtn_avalue=NULL) PURE;

/*!
セキュリティを解除する。

すでにフルアクセスの認証が成功している必要がある。<br>
保護されていなかったらMP_S_PROCESS_CANCELEDが返る。<br>

@retval HRESULT	結果コード
@retval MP_NOERROR (==0) 成功(保護が解除された)
@retval MP_S_PROCESS_CANCELED もともと保護されていなかった
@retval MP_E_INVALID_CALL フルアクセスになっていない
*/
STDMETHOD(ReleaseSecurity)() PURE;
/*!
AddAuthenticationに、認証時の対話操作モードの明示的指定を追加したもの。

APIからフルアクセスになるときなどに使用する。<br>
対話操作モード以外の動作はAddAuthenticationと同じ。

@param MP_AuthInfo* auth  追加したいパーミッションと認証時の対話操作モード
*/
STDMETHOD(AddAuthenticationEx)(MP_AuthInfo* auth) PURE;

//V62
STDMETHOD(GetSecurityModuleData)(char* pModuleData) PURE;

/*!
ファイルの内容を読み込み、ストレージオブジェクトに属性としてセットする(unicode版)。

仕様はSetAttributeFと同様。
*/
STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1, MP_Integer do_assign = 1) PURE;

/*!
ストレージオブジェクトの属性をファイルに取り出す(unicode版)。

仕様はGetAttributeFと同様。
*/
STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1) PURE;

/*!
このストレージオブジェクトが結びついているファイルパスをpathにセットして返す(unicode版)。

仕様はGetFilePathと同様。
@param MP_String& path
*/
STDMETHOD(GetFilePathW)(MP_String& path) PURE;

};
/*
§7.4.2.3 各メソッドの定義
§Destroy
自身をルートとするIStgObjectツリーを解放する。
IStgObjectが別のIStgObjectに従属している場合、
あるいはIStgObjectがファイルに結びついている場合、Destroyは失敗する。
*/


/*
§7.5 ”従属オブジェクト管理”オブジェクト
*/
/*
§7.5.1 オブジェクトの生成と破棄
*/

/*
§7.5.1.1 生成
*/
/*
§MPCreateMPChildren
*/
DLLBINDFUNC_(MP_Children*, MPCreateMPChildren)(MPCSession* session, MPCObject* mpcobj, IStgObject* stgobj, MP_Integer part_objtype = MP_NOPART, IStgObject* reserved = NULL, HRESULT* phres = NULL);

/*
§MPCreateMPCDocRootChildren
*/
DLLBINDFUNC_(MP_Children*, MPCreateMPCDocRootChildren)(MPCSession* session, MPCObject* mpcobj, IStgObject* stgobj, MP_Integer part_objtype = MP_NOPART, IStgObject* reserved = NULL, HRESULT* phres = NULL);

/*
§7.5.1.2 破棄
*/

/*
§7.5.1.3 定数
*/

//! MP_Children::GetChildRect()の結果値
const HRESULT MPCHILD_NO_DIM = 1;
//! MP_Children::GetChildRect()の結果値
const HRESULT MPCHILD_NO_POS = 2;
//! MP_Children::GetChildRect()の結果値
const HRESULT MPCHILD_NO_BORDER_IGN = 4;


//! CreateMPCDocChildrenで扱うbcont参照
MPC_EXTERN_GUID(OT_CDOC_REFOBJ, 0x13E2);


/*
§7.5.2 MP_Children インタフェース
*/
/*
§7.5.2.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_MP_Children, 0x1360);

/*
§7.5.2.2 メソッド一覧
*/
mpinterface MP_Children : public MPCInterface
{
STDMETHOD(Reload)(IStgObject* stgobj) PURE;

STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs) PURE;
STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs, IStgObject** rtn_stgchild = NULL, IStgObject** rtn_part = NULL) PURE;
STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres) PURE;
STDMETHOD(GetMaxNumberOfPreLoadChildren)() PURE;
STDMETHOD(GetNumberOfChildren)() PURE;
STDMETHOD_(MPCObject*,GetNthPreLoadChild)(MP_Integer nth, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres = NULL) PURE;
STDMETHOD(GetChildPosition)(MPCObject* mpcchild) PURE;
STDMETHOD(IsDirty)() PURE;
STDMETHOD(Synchronize)() PURE;
STDMETHOD(SaveCompleted)(IStgObject* stgobj) PURE;
STDMETHOD(UnloadChild)(MP_Integer nth = MP_ALL_CHILDREN) PURE;

STDMETHOD_(IStgObject*,GetNthStgObj)(MP_Integer nth, IStgObject** rtn_part = NULL, HRESULT* phres = NULL) PURE;
STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth, MPCObject** rtn_obj = NULL) PURE;

// MediaID によるコンテント参照と、参照情報の作成ユーティリティ
STDMETHOD_(MPCObject*, GetReferenceObject)(MP_PtrArray* midarray, IStgObject** rtn_stgobj, IStgObject** rtn_part, HRESULT* phres = NULL) PURE;
STDMETHOD(GetChildMID)(MPCObject* mpcchild) PURE;

STDMETHOD(GetChildPosFromMID)(MP_Integer mid, IStgObject** rtn_stgchild, IStgObject** rtn_part) PURE;
STDMETHOD(GetChildRect)(MP_Integer nth, MP_Rect* rtn_rect, MP_Integer* rtn_border_ignorance) PURE;
STDMETHOD_(MP_PD*, GetPD)(MP_Integer nth) PURE;
STDMETHOD(SetPD)(MP_Integer nth, MP_PD* pd) PURE;
STDMETHOD(DestroyPD)(MP_Integer nth = MP_ALL_CHILDREN) PURE;
STDMETHOD(SetDirtyInfo)(MP_Integer nth, MP_Integer dirtyinfo) PURE;
STDMETHOD(GetDirtyInfo)(MP_Integer nth) PURE;
};
/*
§7.5.2.3 各メソッドの定義

このインタフェースはBasicPageと付箋専用である。
内容も一方的に変更するため、他で利用してはならない。

仕様も公開しない。

*/

/*
§7.5.3 IReadOnlyPersist インタフェース

バイトサーブの実装のため、用意されている。
バイトサーブでMPCGetDataRange()に渡されるMPCObjectのみに実装される。
現在実装されているのは、
	BasicMedia (mpcmp: ページ表示など)
	Profile (mpcmp: 文書属性)
	HeteroContDoc (mphcntdc: オリジナルデータ取り出し)
今後、他のオブジェクトにバイトサーブ動作が拡張されるときは、
そのオブジェクトにIReadOnlyPersisインタフェースを実装する必要がある。
*/
/*
§7.5.3.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_IReadOnlyPersist, 0x1383);

/*
§7.5.3.2 メソッド一覧
*/
mpinterface IReadOnlyPersist
{
STDMETHOD_(IStgObject*, GetStgObjWithoutSync)() PURE;
};
/*
§7.5.3.3 各メソッドの定義

§GetStgObjWithoutSync
Synchronzie動作無しでIStgObjectを取得する。
*/

#endif //MPC_SPI_H

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.15 - Ichiriki - SetAttribute()/SetAttributeF() TRUEを1に変更
//96.8.7 - Ichiriki - ICompressedMPAttributeの追加, MPCSPI_REVISION アップ
//97.10.21 - Ichiriki - バイナリ互換消失に伴いMPCSPI_REVISIONを971021に変更
//97.10.28 - Ichiriki - MPC_DBGCoreTypeの定義変更
//97.10.30 - Nagano - ICompressedMPAttributeのインターフェース変更
//97.11.7 - Ichiriki - GetDBGCoreInfoの説明の修正
//97.12.12 - Ichiriki - AR1807 MP_CONTENTCHANGEINFO_ROTATEの追加
//98.06.16 - Ichiriki - AR2837 IContentの注意事項　コメント追記
//98.06.26 - Nagano - V3.1 CreateTempFileの追加
//99.05.18 - Tashiro - V4.0: セキュリティ関連メソッドの追加、保護文書での動作の追記
//99.05.18 - Ichiriki - V4.0: 保護文書での動作の追記
//99.05.27 - Nakazawa - V4.0: ICompressedMPAttribute を削除
//99.06.30 - Ichiriki - V4.0: NO_ADAPTIVE 追加
//00.09.25 - Nakazawa - V4.1: CreateSecurityWithTemplate 追加
//----V5開発g
//2002.02.23 - Tashiro - IStgObject に署名関連の拡張
//2002.04.19 - Tashiro - 署名検証用メソッドの追加
//2002.04.29 - Tashiro - 署名の数→指定タイプの子孫の数にI/Fを一般化
//2002.05.01 - Tashiro - IStgObject 変更
//2002.05.12 - Tashiro - IStgObject 変更(署名検証用ファイルイメージの管理を変更)
//2002.06.28 - Tashiro - AR7369 保存後のファイルバージョンを問い合わせるメソッド追加
//---- V6
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
// --- 6.0.4 ---
//2005.09.29 - Tashiro - APIセキュリティ機能拡張のためにIStgObjectにメソッド追加
// --- 6.2 ---
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
// --- 7.0 ---
//2008.09.01 - Tashiro - SynchronizeしないでIStgObjectを取得するI/Fの追加(AR15514)
