// File: mpc_secu.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MPC_SECU_H_
#define _MPC_SECU_H_

#include "mpc_spi.h"

//#include <windows.h>

const MP_RefInterfaceID MPC_IID_SecuritySPI_Selector = 7;

const MP_RefInterfaceID MPC_IID_SecuritySPI_Pswd = 5;
const MP_RefInterfaceID MPC_IID_SecuritySPI_DDSA = 6;
const MP_RefInterfaceID MPC_IID_SecuritySPI_Pswd128 = 11;	// V5:128bit暗号対応
const MP_RefInterfaceID MPC_IID_SecuritySPI_Pkst = 12;
	// V5: 印鑑ツールによる公開鍵セキュリティ
const MP_RefInterfaceID MPC_IID_SecuritySPI_SDES = 13;
	// V5: ISC SDES署名モジュールによる公開鍵セキュリティ



const MP_Integer MPC_REGISTERED_SECURITY_NUM = 5;
const MP_Integer MPC_REGISTERED_SECURITY_IDS[] = {
	MPC_IID_SecuritySPI_Pswd,
	MPC_IID_SecuritySPI_DDSA,
	MPC_IID_SecuritySPI_Pswd128,
	MPC_IID_SecuritySPI_Pkst,
	MPC_IID_SecuritySPI_SDES
};
const MP_Integer MPC_REGISTERED_SECURITY_TYPES[] = {
	MP_S_PROTECTED_BY_PSWD,
	MP_S_PROTECTED_BY_DDSA,
	MP_S_PROTECTED_BY_PSWD128,
	MP_S_PROTECTED_BY_PKST,
	MP_S_PROTECTED_BY_SDES
};


/*
§8. セキュリティインタフェース

DWコアとセキュリティモジュール間で用いる定義をまとめたものである。
DocuWorks システム全体で用いるセキュリティ関係の定義は基本的に MP_* で定義し、
mpc_api.h 内に記述する。(パーミッション情報など)
コアとセキュリティモジュール間だけで用いる定義は基本的に MPS_* で定義する。
*/


/*
§8.1 セキュリティインタフェース 共通定義

§8.1.1 定数・マクロ定義
*/

// セキュリティモジュール識別情報(7文字(NULL含め8Byte)とする)
typedef char MPS_SecurityLabel;
#define MPS_SECURITYLABEL_SIZE	8

#define MPS_SECURITYLABEL_PSWD	"DWSPswd"
#define MPS_SECURITYLABEL_DDSA	"DWSDDSA"
#define MPS_SECURITYLABEL_PSWD128	"Pswd128"	// V5:128bit暗号対応
#define MPS_SECURITYLABEL_PKST	"DWSPkst" // V5: 印鑑ツール
#define MPS_SECURITYLABEL_SDES	"DWSSDES" // V5: ISC SDESモジュール

// 64bitバインダリのデータを表す(デフォルトは64bitのみ)
// MPS_DataBlock で定義されたデータは必ず64bitバインダリであること
typedef MP_Octet	MPS_DataBlock;
#define MPS_DATABLOCK_DEFAULTSIZE	8

// 安全にデータ鍵を渡す際のデータ型
// はじめの1ブロック(64bit)の上位32bitに文書暗号化アルゴリズム指定子、
// 下位32bitには定数 MPS_SDATATYPE_DATAKEY を入れ、
// それ以降のブロックには指定アルゴリズムの文書鍵を入れて、
// 配列全体をセッション鍵で暗号化して格納する。
// このデータは DES の場合は2ブロック(128bit)、Triple DES の場合は3ブロック(192bit)である。
// V5:AES128bitの場合は3ブロック(192bit)となる。
typedef MPS_DataBlock	MPS_SDataKey;

// 文書暗号化アルゴリズム指定子
typedef MP_Integer	MPS_CryptType;
#define MPS_CRYPTTYPE_DES		1
#define MPS_CRYPTTYPE_TRIPLEDES	2
#define MPS_CRYPTTYPE_AES128	3	// V5:128bit暗号対応

// 保護データ種別識別子(データ鍵/パーミッション情報用タグ)
typedef MP_Integer	MPS_SDataType;
#define MPS_SDATATYPE_DATAKEY	1
#define MPS_SDATATYPE_MAC		2

// 安全に認証済みパーミッション情報を渡す際の構造体
// 上位32bitに perm の値、下位32bitに定数 MPS_SDATATYPE_MAC を入れた
// 64bitブロックと、通信に用いた乱数との排他論理輪を、
// セッション鍵で暗号化したものが pMac の内容と一致するかチェックされる。
typedef struct tag_MPS_SPermission {
	MP_Permission	perm;	// 認証済みパーミッション(暗号化されていない)
	MPS_DataBlock*	pMac;	// perm が正しいかどうかのチェック用 MAC
} MPS_SPermission;

// セキュリティ情報用構造体(長さ付きデータ)
typedef struct tag_MPS_SecurityInfo {
	MP_Integer	size;
	MP_Octet*	pInfo;
} MPS_SecurityInfo;

// セキュリティオブジェクトへのハンドル
class MPS_SecurityObj;		// 空クラスを定義(セキュリティモジュール内で固有の型にキャストする)
typedef MPS_SecurityObj*	MPS_SecurityHandle;

// セキュリティテンプレートの定義(V4.1より使用できるようにする)
#define MPS_SecurityTemplate	void


/*
§8.2 セキュリティインタフェース

§8.2.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_MPCSecuritySPI, 0x1322);

/*
§8.2.2 メソッド一覧
*/
mpinterface MPCSecuritySPI : public MPCInterface
{
// 12.02.17 Bito - セキュリティ対応
#ifndef _SEC_MP_
STDMETHOD(OpenSecurity)(MPS_SecurityInfo* pSecurityInfo, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle, MPS_SDataKey* pDataKey, MPS_SPermission* pAuthenticatedPerm) PURE;
#else
// セキュリティ認証に必要なデータを引数に追加
STDMETHOD(OpenSecurity)(MPS_SecurityInfo* pSecurityInfo, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, void* authdata, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle, MPS_SDataKey* pDataKey, MPS_SPermission* pAuthenticatedPerm) PURE;
#endif
STDMETHOD(AddAuthentication)(MPS_SecurityHandle securityHandle, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, MPS_SPermission* pAuthenticatedPerm) PURE;
STDMETHOD(GetAuthenticatedPermission)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SPermission* pAuthenticatedPerm) PURE;
STDMETHOD(GetPermission)(MPS_SecurityInfo* pSecurityInfo, MP_Permission* pPerm) PURE;
STDMETHOD(GetNewSecurityInfo)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SecurityLabel* pSecurityLabel, MPS_SDataKey* pDataKey, MPS_SecurityInfo* pSecurityInfo) PURE;
STDMETHOD(CloseSecurity)(MPS_SecurityHandle securityHandle) PURE;
STDMETHOD(EditSecurity)(MPS_SecurityHandle securityHandle) PURE;
STDMETHOD(CreateSecurity)(MPS_DataBlock* pNonce, MPS_SecurityTemplate* pSecurityTemplate, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle) PURE;
STDMETHOD(ShowSecurity)(MPS_SecurityInfo* pSecurityInfo) PURE;
STDMETHOD(OnBeginPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage) PURE;
STDMETHOD(OnEndPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage) PURE;
STDMETHOD(GetPermissionFromCache)(MPS_SecurityHandle securityHandle, MP_Permission* pPerm) PURE;
STDMETHOD(CreateSecurityIcon)(MP_Integer type, HBITMAP_XD* phBitmap) PURE;
};

/*
§8.2.3 各メソッドの定義
「DocuWorks セキュリティインタフェース仕様」も参照すること。

§OpenSecurity
・パラメータ
MPS_SecurityInfo* pSecurityInfo			(入力)保護された文書のセキュリティ情報
MP_Permission requestedPerm				(入力)開くときの要求パーミッション
MPS_DataBlock* pNonce					(入力)通信用データ(乱数)
MP_AuthMode mode						(入力)認証時のモード(対話、非対話)
MPS_DataBlock* pSessionKey				(出力)通信用セッション鍵の格納先
MPS_SecurityHandle* pSecurityHandle		(出力)セキュリティオブジェクトのハンドルの格納先
MPS_SDataKey* pDataKey					(出力)暗号化アルゴリズム指定子と文書鍵の格納先
MPS_SPermission* pAuthenticatedPerm		(出力)認証済みパーミッション情報の格納先

・説明
保護された文書を開く際の認証を行う。

引数pSecurityInfoには、文書ファイルから読み出されたセキュリティ情報が渡される。
認証時にパーミッションが必要な場合(印刷モードで起動された場合など)は
引数requestedPermにそのパーミッション情報が指定される。必要なパーミッションが
無い場合(文書を開くだけの場合など)はrequestedPermに0が指定される。
引数pNonceには、毎回異なる64bit乱数が渡される。
引数modeは認証動作における対話/非対話などが指定される。
引数pSessionKey, pSecurityHandle, pDataKey, pAuthenticatedPermにはそれぞれ、
DocuWorks側で確保したメモリのポインタが渡される。もしNULLであればエラーを返す。

セキュリティモジュールは認証処理を行って、セッション鍵、セキュリティオブジェクト、
文書鍵、パーミッション情報を生成し、それぞれ引数pSessionKey、pSecurityHandle、
pDataKey、pAuthenticatedPermで指定されたポインタに格納する。
セッション鍵はセキュリティオブジェクトに対応して以降の通信に用いられる。

引数modeにMP_AUTH_DIALOGUEが指定されているときのみ、セキュリティモジュールは
GUI動作を行って良い。その他のモードの場合はエラーメッセージの表示も含めて
GUI動作を行ってはならない。

文書データの暗号化アルゴリズムに応じて、文書暗号化アルゴリズム指定子に次の定数を指定する。
- 56bit鍵長DESアルゴリズム(V4互換): MPS_CRYPTTYPE_DES
- 128bit鍵長AESアルゴリズム(V5以降): MPS_CRYPTTYPE_AES128

・リターン値
HRESULT
MP_NOERROR					認証成功
MP_S_PROCESS_CANCELED		ユーザ操作によりキャンセルされた
MP_E_AUTH_FAILED			認証に失敗し、セキュリティモジュールでメッセージを表示した
MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗し、セキュリティモジュールでメッセージを表示していない
MP_E_INVALIDARG				パラメータ不正
MP_E_BAD_FORMAT				セキュリティ情報が不正
MP_E_OUTOFMEMORY			メモリ不足
MP_E_INVALID_CALL			不正な呼び出し(要求パーミッションにMP_PERM_FULLが含まれていた場合など)
MP_E_NOPERMISSION			文書のパーミッションに要求パーミッションが含まれていなかった


§AddAuthentication
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MP_Permission requestedPerm				(入力)追加認証の要求パーミッション
MPS_DataBlock* pNonce					(入力)通信用データ(乱数)
MP_AuthMode mode						(入力)認証時のモード(対話、非対話)
MPS_SPermission* pAuthenticatedPerm		(出力)認証済みパーミッション情報の格納先

・説明
すでに認証済みの文書に対してパーミッションを追加認証する。

引数securityHandleには、OpenSecurityで生成されたセキュリティオブジェクトの
ハンドルが渡される。
引数requestedPermには追加認証するパーミッションが指定される。
引数pNonceには、毎回異なる64bit乱数が渡される。
引数modeは認証動作における対話/非対話などが指定される。
引数pAuthenticatedPermには、DocuWorks側で確保したメモリのポインタが渡される。
もしNULLであればエラーを返す。

セキュリティモジュールは追加認証に必要な認証処理を行って、
成功した場合にはpAuthenticatedPermに認証されたパーミッション情報を格納する。
要求されたパーミッションが既に認証済みである場合には、成功を返す。
既にセキュリティが解除されているときに呼ばれた場合はエラーを返す。

引数modeにMP_AUTH_DIALOGUEが指定されているときのみ、セキュリティモジュールは
GUI動作を行って良い。その他のモードの場合はエラーメッセージの表示も含めて
GUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR					追加認証成功
MP_S_PROCESS_CANCELED		キャンセルされた
MP_E_AUTH_FAILED			認証に失敗し、セキュリティモジュールでメッセージを表示した
MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗し、セキュリティモジュールでメッセージを表示していない
MP_E_INVALIDARG				パラメータ不正
MP_E_INVALID_CALL			不正な呼び出し(既に解除されているときに呼ばれた場合など)
MP_E_OUTOFMEMORY			メモリ不足
MP_E_NOPERMISSION			文書のパーミッションに要求パーミッションが含まれていなかった


§GetAuthenticatedPermission
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MPS_DataBlock* pNonce					(入力)通信用データ(乱数)
MPS_SPermission* pAuthenticatedPerm		(出力)認証済みパーミッション情報の格納先

・説明
認証済みパーミッションを得る。

引数securityHandleには、OpenSecurityで生成されたセキュリティオブジェクトの
ハンドルが渡される。
引数pNonceには、毎回異なる64bit乱数が渡される。
引数pAuthenticatedPermには、DocuWorks側で確保したメモリのポインタが渡される。
もしNULLであればエラーを返す。

セキュリティモジュールはpAuthenticatedPermに既に認証しているパーミッションを格納する。
この関数は頻繁に呼ばれるため、セキュリティオブジェクト内に認証済みパーミッションの
情報を記憶するなどして、時間のかかる処理は行わずに制御を返すように実装する。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合など)
MP_E_OUTOFMEMORY		メモリ不足


§GetPermission
・パラメータ
MPS_SecurityInfo* pSecurityInfo			(入力)保護された文書のセキュリティ情報
MP_Permission* pPerm					(出力)文書のパーミッション情報の格納先

・説明
文書に設定されているパーミッション情報を得る。
文書の認証状態には関係なく、OpenSecurityの前に呼ばれることもある。

引数pSecurityInfoには、文書ファイルから読み出されたセキュリティ情報、
またはGetNewSecurityInfoで生成されたセキュリティ情報が渡される。
引数pPermには、DocuWorks側で確保したメモリのポインタが渡される。
もしNULLであればエラーを返す。

セキュリティモジュールは、pSecurityInfoの情報から文書に設定されている
パーミッションを得て、pPermに格納する。

OpenSecurityの前に呼ばれたとき、
認証後に許す可能性のあるパーミッション(MP_PERM_*)は1を返す。
MP_PERM_*に1を返すが認証後にパーミッションを与えない可能性があるときは
MP_CAN_CANCEL_PERM_*に1を返す。
MP_PERM_* が 1、MP_CAN_CANCEL_PERM_* が 0 : 認証後に有り
MP_PERM_* が 1、MP_CAN_CANCEL_PERM_* が 1 : 認証後に有り/無しの可能性
MP_PERM_* が 0                            : 認証後に無し

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_BAD_FORMAT			セキュリティ情報が不正
MP_E_OUTOFMEMORY		メモリ不足


§GetNewSecurityInfo
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MPS_DataBlock* pNonce					(入力)通信用データ(乱数)
MPS_SecurityLabel* pSecurityLabel		(出力)セキュリティモジュール識別情報の格納先
MPS_SDataKey* pDataKey					(出力)暗号化アルゴリズム指定子と文書鍵の格納先
MPS_SecurityInfo* pSecurityInfo			(出力)新しいセキュリティ情報の格納先

・説明
新しいセキュリティ情報と文書鍵を生成して返す。
EditSecurityまたはCreateSecurityが成功した後、または文書鍵を変更するとき
(全更新保存時)にこのメソッドが呼ばれる。

引数securityHandleには、OpenSecurityまたはCreateSecurityで生成された
セキュリティオブジェクトのハンドルが渡される。
引数pNonceには、毎回異なる64bit乱数が渡される。
引数pSecurityLabel、pDataKey、pSecurityInfoにはそれぞれ、DocuWorks側で
確保したメモリのポインタが渡される。pSecurityInfoがNULLであれば、
セキュリティ情報に必要なバイト数を返す。

セキュリティモジュールは、pSecurityInfoがNULLのときはセキュリティ情報の
格納に必要なバイト数を計算して返り値に返す。それ以外のとき、
pSecurityLabelにモジュール固有の識別情報を格納し、文書鍵、セキュリティ情報を
生成して、それぞれpDataKey、pSecurityInfoに格納する。

セキュリティ情報の文書暗号化アルゴリズム指定子には次の定数を指定する。
- 56bit鍵長DESアルゴリズム(V4互換): MPS_CRYPTTYPE_DES
- 128bit鍵長AESアルゴリズム(V5以降): MPS_CRYPTTYPE_AES128

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_OUTOFMEMORY		メモリ不足
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合など)


§CloseSecurity
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル

・説明
セキュリティオブジェクトを解放する。
文書の保護が解除されたとき、文書が閉じられたときなどに呼ばれる。

引数securityHandleには、OpenSecurityまたはCreateSecurityで
生成されたセキュリティオブジェクトのハンドルが渡される。

セキュリティモジュールは、セキュリティオブジェクトそのもの及びセキュリティ
オブジェクトに必要であった資源を解放する。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正


§EditSecurity
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル

・説明
保護された文書のセキュリティの設定を変更する。
認証済みの保護文書の設定を変更する際に呼ばれる。
保護されていない文書に新規にセキュリティをかける場合には
CreateSecurityが呼ばれる。

引数securityHandleには、OpenSecurityまたはCreateSecurityで
生成されたセキュリティオブジェクトのハンドルが渡される。

セキュリティモジュールは、ユーザにセキュリティの設定内容を変更させ、
必要であればセキュリティオブジェクトの内容を変更する。
セキュリティが解除された場合には解除された状態を記憶し、そのセキュリティ
オブジェクトに対してAddAuthentication、GetAuthenticatedPermission、
GetNewSecurityInfo、EditSecurity、OnBeginPrint、OnEndPrint
などが呼ばれたときにエラーを返す。

フルアクセスモードになっていない場合にこの関数が呼ばれた場合はエラーを返す。
フルアクセスパーミッションが無いときに呼ばれた場合はエラーを返す。

・リターン値
HRESULT
MP_NOERROR				成功(設定が変更された)
MP_S_PROCESS_CANCELED	ユーザ操作によりキャンセルされた(設定は変更されなかった)
MP_S_PROTECTION_REMOVED	セキュリティが解除された
MP_E_INVALIDARG			パラメータ不正
MP_E_OUTOFMEMORY		メモリ不足
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合、
						フルアクセスパーミッションが無いときに呼ばれた場合など)


§CreateSecurity
・パラメータ
MPS_DataBlock* pNonce					(入力)通信用データ(乱数)
void* pSecurityTemplate					(入力)セキュリティテンプレート
MPS_DataBlock* pSessionKey				(出力)通信用セッション鍵の格納先
MPS_SecurityHandle* pSecurityHandle		(出力)セキュリティオブジェクトのハンドルの格納先

・説明
新規にセキュリティをかける。
保護されていない文書にセキュリティをかける際に呼ばれる。
認証済みの保護文書の設定を変更する場合には
EditSecurityが呼ばれる。

引数pNonceには、毎回異なる64bit乱数が渡される。
引数pSecurityTemplateには、セキュリティテンプレートデータへのポインタ
またはNULLが指定される。
引数pSessionKey、pSecurityHandleにはそれぞれ、DocuWorks側で
確保したメモリのポインタが渡される。もしNULLであればエラーを返す。

セキュリティモジュールは、pSecurityTemplateがNULLでない場合、
セキュリティテンプレートからセキュリティの設定に必要な情報を得て、
セッション鍵、セキュリティオブジェクトを生成し、それぞれ
pSessionKey、pSecurityHandleに格納する。

pSecurityTemplateがNULLの場合、ユーザにセキュリティの設定内容を
指定させて、セッション鍵、セキュリティオブジェクトを生成し、
それぞれpSessionKey、pSecurityHandleに格納する。

pSecurityTemplateがNULLの場合のみ、セキュリティモジュールはGUI動作を
行って良い。その他のモードの場合はエラーメッセージの表示も含めて
GUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功(設定された)
MP_S_PROCESS_CANCELED	キャンセルされた(設定されなかった)
MP_E_INVALIDARG			パラメータ不正
MP_E_OUTOFMEMORY		メモリ不足


§ShowSecurity
・パラメータ
MPS_SecurityInfo* pSecurityInfo			(入力)保護された文書のセキュリティ情報

・説明
セキュリティモジュールが固有の情報を表示する。
Desk/Viewerなどの文書プロパティダイアログのセキュリティタブの追加情報ボタンが
押された際に呼ばれる。

引数pSecurityInfoには、文書ファイルから読み出されたセキュリティ情報、
またはGetNewSecurityInfoで生成されたセキュリティ情報が渡される。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_BAD_FORMAT			セキュリティ情報が不正
MP_E_OUTOFMEMORY		メモリ不足


§OnBeginPrint
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MP_Canvas* pCanvas						(入力)プリンタキャンバス
MPCObject* pBasicPage					(入力)印刷するページオブジェクト

・説明
保護文書の印刷内容にセキュリティモジュール固有の情報を付加する。
各ページのOnPrint()処理の前に呼ばれる。

引数securityHandleには、OpenSecurityまたはCreateSecurityで
生成されたセキュリティオブジェクトのハンドルが渡される。
引数pCanvasには、印刷するページのキャンバスオブジェクトが渡される。
引数pBasicPageには、印刷対象のページオブジェクトが渡される。

セキュリティモジュールは、必要であればpCanvasに対して描画する。
pCanvasにセットされている状態やプリンタDC、pBasicPageを変更してはならない。
既にセキュリティが解除されているときに呼ばれた場合はエラーを返す。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合など)
MP_E_OUTOFMEMORY		メモリ不足


§OnEndPrint
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MP_Canvas* pCanvas						(入力)プリンタキャンバス
MPCObject* pBasicPage					(入力)印刷するページオブジェクト

・説明
保護文書の印刷内容にセキュリティモジュール固有の情報を付加する。
各ページのOnPrint()処理の後に呼ばれる。

引数securityHandleには、OpenSecurityまたはCreateSecurityで
生成されたセキュリティオブジェクトのハンドルが渡される。
引数pCanvasには、印刷するページのキャンバスオブジェクトが渡される。
引数pBasicPageには、印刷対象のページオブジェクトが渡される。

セキュリティモジュールは、必要であればpCanvasに対して描画する。
pCanvasにセットされている状態やプリンタDC、pBasicPageを変更してはならない。
既にセキュリティが解除されているときに呼ばれた場合はエラーを返す。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合など)
MP_E_OUTOFMEMORY		メモリ不足


§GetPermissionFromCache
・パラメータ
MPS_SecurityHandle securityHandle		(入力)セキュリティオブジェクトのハンドル
MP_Permission* pPerm					(出力)文書のパーミッション情報の格納先

・説明
文書に設定されているパーミッション情報を得る。

引数securityHandleには、OpenSecurityまたはCreateSecurityで
生成されたセキュリティオブジェクトのハンドルが渡される。
引数pPermには、DocuWorks側で確保したメモリのポインタが渡される。
もしNULLであればエラーを返す。

セキュリティモジュールは、securityHandleの情報から文書に設定されている
パーミッションを得て、pPermに格納する。セキュリティオブジェクト内に
文書に設定されているパーミッションの情報を記憶するなどして、
時間のかかる処理は行わずに制御を返すように実装する。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_INVALID_CALL		不正な呼び出し(既に解除されているときに呼ばれた場合など)
MP_E_OUTOFMEMORY		メモリ不足


§CreateSecurityIcon
・パラメータ
MP_Integer type			(入力)セキュリティオブジェクトのハンドル
HBITMAP* phBitmap		(出力)アイコンのビットマップの格納先

・説明
セキュリティモジュール固有の、保護されている状態を示すアイコンを得る。

引数typeには、アイコンの種類が指定される。
11: 未認証状態のアイコン
12: 未認証状態のアイコンのマスク
21: 認証済み状態のアイコン
22: 認証済み状態のアイコンのマスク
引数phBitmapには、DocuWorks側で確保したメモリのポインタが渡される。
もしNULLであればエラーを返す。

セキュリティモジュールは、typeで指定された種類のアイコンの
HBITMAPを生成し、phBitmapに格納する。
typeが11、12のアイコンのサイズは幅33画素×高さ34画素、
21、22のアイコンのサイズは幅19画素×高さ25画素であり、
色数は16色となるようなビットマップを生成する。

セキュリティモジュールはエラーメッセージの表示も含めてGUI動作を行ってはならない。

・リターン値
HRESULT
MP_NOERROR				成功
MP_E_INVALIDARG			パラメータ不正
MP_E_OUTOFMEMORY		メモリ不足

*/

/*
§8.3 セキュリティモジュール実装時の注意点

セキュリティモジュールはDWコアから呼び出されるので、
コアのDLL呼び出し規約に従ったモジュールにしなければならない。

MPCSecuritySPI は純粋仮想関数の宣言だけであるので、
実体をセキュリティモジュール内で実装しなければならない。
以下は実装例である。

// 実体の定義
class ImplSecuritySPI : MPCSecuritySPI
{
STDMETHOD(OpenSecurity)(MPS_SecurityInfo* pSecurityInfo, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle, MPS_DataBlock* pDataKey, MPS_SPermission* pAuthenticatedPerm);
STDMETHOD(AddAuthentication)(MPS_SecurityHandle securityHandle, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MPS_SPermission* pAuthenticatedPerm);
STDMETHOD(GetAuthenticatedPermission)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SPermission* pAuthenticatedPerm);
STDMETHOD(GetPermission)(MPS_SecurityInfo* pSecurityInfo, MP_Permission* pPerm);
STDMETHOD(GetNewSecurityInfo)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SecurityLabel* pSecurityLabel, MPS_DataBlock* pDataKey, MPS_SecurityInfo* pSecurityInfo);
STDMETHOD(CloseSecurity)(MPS_SecurityHandle securityHandle);
STDMETHOD(EditSecurity)(MPS_SecurityHandle securityHandle);
STDMETHOD(CreateSecurity)(MPS_DataBlock* pNonce, void* pSecurityTemplate, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle);
STDMETHOD(ShowSecurity)(MPS_SecurityInfo* pSecurityInfo);
STDMETHOD(OnBeginPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage);
STDMETHOD(OnEndPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage);
STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres);
STDMETHOD(Destroy)();
};

// 各関数の実体
STDMETHODIMP ImplSecuritySPI::CloseSecurity(MPS_SecurityHandle securityHandle)
{
	MPS_SecurityObjectLocal* pObj = (MPS_SecurityObjectLocal*)securityHandle;
	pObj->Destroy();
	return MP_NOERROR;
}

STDMETHODIMP_(void*) ImplSecuritySPI::GetInterface(MP_RefInterfaceID riid, HRESULT* phres)
{
	if (phres) *phres = MP_E_NOINTERFACE;
	return NULL;
}

// ...


DLLの初期化には、

DLLBINDFUNC_(MPCObject*, MPCSPI_DLLCreateMPCObject)(MP_RefObjectType type);

が呼ばれるので、これを実装しなければならない。
(これが InitializeModule() に相当する)
この関数は DWコア ストレージの CMediaLoader から呼ばれる。
以下は実装例である。

DLLBINDFUNC_(MPCObject*, MPCSPI_DLLCreateMPCObject)(MP_RefObjectType type)
{
	MPCSPI_CHECK_REVISION(type);	// このマクロは mpc_spi.h に定義されている

	MPCObject* rtnobj = NULL;

	if (type == IID_MPCSecuritySPI) {
		rtnobj = (MPCObject*) new ImplSecuritySPI;

		// ここで初期化時の固有処理を行う

	}

	return rtnobj;
}

DLL解放時には、MPCInterface の Destroy() が呼ばれるので、
このときに必要な処理を行う。
(これが ReleaseModule() に相当する)
以下は実装例である。

STDMETHODIMP ImplSecuritySPI::Destroy()
{
	// ここで固有の終了処理を行う

	delete this;
	return MP_NOERROR;
}

*/

/*
§8.4 セキュリティセレクタインタフェース

§8.4.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_MPCSecuritySelectorSPI, 0x1325);

/*
§8.4.2 メソッド一覧
*/
mpinterface MPCSecuritySelectorSPI : MPCInterface
{
	STDMETHOD(SelectModule)() PURE;
	// V5 security
	STDMETHOD(SelectNewInterfaceModule)( MP_InterfaceID id ) PURE;
	// V5 signature
	STDMETHOD(SelectSignatureModule)() PURE;
	STDMETHOD_(void*, LoadSignatureModule)( MP_InterfaceID iModuleID, HRESULT* phres = NULL ) PURE;
	STDMETHOD_(HBITMAP_XD, CreateSignatureIcon)( MP_Integer iType, HRESULT* phres = NULL ) PURE;
	STDMETHOD_(void*, EnumSignatureModules)( MP_InterfaceID* piRecentID, HRESULT* phres = NULL ) PURE;
	// V6
	STDMETHOD(GetOptionSelectSignatureModule)() PURE;
	STDMETHOD(SetOptionSelectSignatureModule)( UINT mode ) PURE;
	STDMETHOD(GetOptionSignatureModuleID)() PURE;
	STDMETHOD(SetOptionSignatureModuleID)(MP_InterfaceID id) PURE;
	STDMETHOD(GetSignatureModuleName)( char* pName, MP_InterfaceID id ) PURE;
};

/*
§8.4.3 各メソッドの定義

§SelectModule
・パラメータ
	なし

・説明
	文書に新規に保護をかけるときに使うセキュリティモジュールを選択する。
	実際にセキュリティモジュールのインタフェース取得を試み、
	利用可能なモジュールのみが選択肢となる。
	利用可能なモジュールが2つ以上の場合は選択ダイアログを表示して
	ユーザに選択させる。
	利用可能なモジュールが1つの場合はダイアログは出さずにそのレジストリ番号を返す。

・リターン値
HRESULT
0				未定義
負数			何らかのエラーが発生した場合（V4.0では存在しない）
MP_S_PROCESS_CANCELED		セキュリティが選択されなかった事を示す
その他の正数	選択されたセキュリティモジュールのレジストリ登録番号を返す。
				V4.0 では以下の２モジュールをサポートする。
				5	パスワードセキュリティ
				6	DDSAセキュリティ
				V5以降はmpc_secu.hを参照。


§SelectNewInterfaceModule
	(V5新規)
・パラメータ
	MP_InterfaceID id  要求するインタフェースID

・説明
	SelectModule()の機能に追加して、id で要求されたインタフェースを
	持つセキュリティモジュールを選択する。

§SelectSignatureModule
	(V5新規)
・パラメータ
	なし
・説明
	署名モジュールを選択する。
	動作はSelectModule()と同様。
・リターン値
	選択された署名モジュールID。

§LoadSignatureModule
	(V5新規)
・パラメータ
	int iModuleID	署名モジュールID
	HRESULT* phres	エラーコード格納先
・説明
	iModuleIDで指定された署名モジュールの署名インタフェースを得る。
	MPCSession::GetInterface()に相当するが、外部に公開可能な
	プロトコルによってインタフェースを得る。
・リターン値
	取得したインタフェース


§CreateSignatureIcon
・パラメータ
	MP_Integer iType
		アイコンのタイプ mpc_pd.hのMPCCreateSignatureIcon()の
		記述を参照。
・説明
	iTypeで指定された署名アイコンを生成して返す。
	この署名アイコンはDeskサムネール上に付けるためのもので
	署名モジュールには依存しない。
	取得したHBITMAPは取得側が開放する。
・リターン値
	生成した署名アイコンのビットマップ

  §GetOptionSingnatureModule
	(V5新規)
・パラメータ
	なし
・説明
	署名モジュールを選択する。
	動作はSelectModule()と同様。
・リターン値
	選択された署名モジュールID。

*/


/*
§8.5 V5拡張セキュリティインタフェース

§8.5.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_MPCSecuritySPI5, 0x132A);

/*
§8.5.2 メソッド一覧
*/
mpinterface MPCSecuritySPI5 : public MPCSecuritySPI
{
STDMETHOD(CreateSecurityTemplate)(MPC_SecurityTemplate** ppSecutiryTemplate) PURE;
STDMETHOD(DestroySecurityTemplate)(MPC_SecurityTemplate* pSecutiryTemplate) PURE;
STDMETHOD(GetSecurityName)(char* pSecurityName) PURE;
};

/*
§8.5.3 各メソッドの定義

§CreateSecurityTemplate
・パラメータ
	MPC_SecurityTemplate** ppSecutiryTemplate
		生成したセキュリティテンプレートのポインタを格納するポインタ。

・説明
	複数文書への一括セキュリティ設定のためのセキュリティテンプレートデータを
	生成し、生成したセキュリティテンプレートのポインタをppSecutiryTemplateで
	指定されたポインタへ格納する。
	セキュリティモジュールは、セキュリティテンプレートの構造体そのもの及び
	構造体のpDataフィールドに指定するモジュール独自のデータに必要なメモリを
	確保する。
	セキュリティモジュールはこのメソッドでGUI動作を行って良い。

・リターン値
HRESULT
	エラーコード。
	正常時: MP_NOERROR
	ユーザがキャンセル: MP_S_PROCESS_CANCELED
	メモリ不足: MP_E_OUTOFMEMORY
	など。

§DestroySecurityTemplate
・パラメータ
	MPC_SecurityTemplate* pSecutiryTemplate
		破棄するセキュリティテンプレートのポインタ。

・説明
	引数pSecutiryTemplateで指定されたセキュリティテンプレートデータを
	破棄する。セキュリティモジュールは、指定されたセキュリティテンプレートの
	構造体そのもの及びセキュリティテンプレートの生成に伴って確保された
	メモリーなどの資源を解放する。
	セキュリティモジュールはこのメソッドでGUI動作を行うべきではない。

・リターン値
HRESULT
	エラーコード。

§GetSecurityName
・パラメータ
	char* pSecurityName
		セキュリティモジュールの名称を書き込むポインタ。

・説明
	モジュールの名称を表す文字列データをpSecurityNameで示されたポインタに
	書き込む。pSecurityNameがNULLのときはデータを書き込まず、必要なバイト数を
	返り値に返す。
	文字列の内容は、セキュリティモジュールをユーザに選択させるときなどに
	表示される。文字コードは使われるWindowsで用いられるコード
	(Windows日本語版ではSihft-JIS)。
	セキュリティモジュールはこのメソッドでGUI動作を行うべきではない。

・リターン値
HRESULT
	成功時は文字列データに必要なバイト数。失敗時はエラーコード。

*/


/*
§8.5 V6.2拡張セキュリティインタフェース

§8.5.1 インタフェースID
*/

MPC_EXTERN_GUID(IID_MPCSecuritySPI6, 0x1333);

/*
§8.5.2 メソッド一覧
*/
mpinterface MPCSecuritySPI6 : public MPCSecuritySPI5
{
STDMETHOD(GetModuleData)(MPS_SecurityHandle securityHandle, char* pModuleData) PURE;
};


#endif // _MPC_SECU_H_

// CHANGE LOG
// 1999.05.19 - Nakazawa - 新規作成
// 1999.05.20 - Nakazawa - MPS_SecurityLabel の定義変更、説明文追加
// 1999.05.24 - Nakazawa - 文書暗号化アルゴリズム指定子を追加、説明文追加
// 1999.05.31 - Nakazawa - GetPermissionFromCache 追加
// 1999.06.01 - Nakazawa - GetPermissionFromCache の説明文修正
// 1999.06.11 - Nakazawa - AddAuthentication に対話モードを追加、コメント修正
// 1999.06.16 - Nakazawa - CreateSecurity で pSecurityTemplate の宣言を void* に変更
// 1999.06.18 - Nakazawa - CreateSecurity で pSecurityTemplate の宣言を MPS_SecurityTemplate* に変更
// 1999.06.29 - Nakazawa - MPS_SDataType追加、コメント修正
// 1999.07.05 - Nakazawa - CreateSecurityIcon追加
// 1999.07.16 - Ichiriki - セキュリティセレクタの定義追加
// 1999.08.20 - Nakazawa - MP_E_NOPERMISSION の記述を追加
// 1999.08.20 - Ichiriki - コメント修正：セレクタのキャンセル時のリターン値変更
// 2000.09.25 - Nakazawa - V4.1 テンプレートによるセキュリティ設定の記述を追加
// --- V5 開発
// 2002.02.08 - Tashiro - MPCSecuritySPI5追加(一括設定など)
// 2002.02.19 - Nakazawa - 128bit暗号対応
// 2002.02.23 - Tashiro - MPCSecuritySelectorSPIの拡張と実装変更、新規セキュリティIDの追加
// 2002.04.15 - Tashiro - V4時代からのコメント分の不備を修正(協業部門へ開示のため)
// 2002.08.27 - Tashiro - VコメントがI/F利用者向けになっていないのを修正
//---- 6.2 ----
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
