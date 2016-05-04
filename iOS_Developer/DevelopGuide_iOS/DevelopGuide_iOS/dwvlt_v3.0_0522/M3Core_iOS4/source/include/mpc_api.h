// File: MPC_API.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996-2007 by Fuji Xerox Co,. Ltd. All right reserved.

/*
 *	MPC_API.H	: MetaPaper Core API インタフェース定義
 *
 *	DWCore を利用するためのアプリケーションプログラムインタフェースを定義する。
 *	DWCore内部や、モデル間の対話に利用するインタフェースは含まない。
 */

#ifndef MPCOREAPI_H
#define MPCOREAPI_H

#define STRICT 1

#include "pfdepend.h"

// MP対応 T.Kitahashi(09/05/25)
#include "win2mpf.h" // CodePageの定義を利用

#pragma warning(disable:4099)


/*
 §4  インタフェース仕様
 
 ***************************
 §4.1 概要
 ***************************
 
 §4.1.1 利用対象
 DWCore APIは、DWDeskやDWViewerのようなアプリケーション層から利用するインタフェースである。
 
 §4.1.2 システム依存条件
 DWCoreの実装は、単一プロセス、同一アドレス空間での利用を想定する。
 また、スレッド等を利用する場合、利用者側でAPIコールを制御する必要がある。
 資源はセッションの単位で管理される。セッションの違うメモリオブジェクトは直接交換できない。
 Microsoft Visual C++ (32bit)によるC++言語を対象とする。
 
 §4.1.3 ヘッダ表記規則
 タブストップ＝４とする
 メンバ関数の定義は、関数名、変数も含めて１行で記載する。
 ただし、横に長くなりすぎるような場合は複数行に渡っても良い。
 
 §4.1.4 命名規則
 APIとして開示するインタフェースは、接頭辞を MPC とする。
 　（注：　但し、prototype時期から継承している名前はこの限りではない。
 ・MetaPaper全体で共通のデータやインタフェースは「MP」で始まる
 ・外部に公開しないインタフェースは 「I」または「SPI」で始まる
 ・WINAPI等で定義されたマクロ等は元の名前をそのまま流用する。
 等の命名規則の名残である。）
 
 CreateXXX と命名された関数から取得したオブジェクトは明示的なDestroyが必要である。
 逆にCreate以外の名前で取得したオブジェクトはDestroyしないでよい場合が多い。
 例外の一例
 UnlinkXXX等で単独になったオブジェクトはDestroyしなければならない
 CreateしたあとLinkChildしたオブジェクトはDestroyの義務がなくなる
 
 一般にコアから得たオブジェクトを解放する場合は、対応する解放関数を呼ぶ。
 delete / free など一般の解放処理を施してはならない。
 通常、MPCInterface を含むインタフェースの解放は、Destroy()で行う。
 ただし、
 MPCSessionの解放は、専用の関数をコールする
 ファイルのルートオブジェクトを解放する場合はMPCSession::CloseFile()をコールする。
 等の例外がある。
 */

/*
 §4.1.5 関数定義に関する表記
 
 関数の定義に使用するマクロ定義について説明する。
 
 §4.1.5.1 mpinterface のメンバ関数宣言マクロ
 mpinterface の全てのメソッドは、STDMETHODマクロか、STDMETHOD_マクロを用いて表記する。
 例えば、
 STDMETHOD(IsDirty)(MPCObject* obj) PURE;
 のように表記する。
 以下に各マクロについて記述する。
 */

#define PURE                    = 0
/*
 mpinterface のメソッド（＝メンバ関数）は、必ず仮想関数でなければならない。
 メソッド定義の末尾にPUREを付け、仮想関数である事を宣言する。
 */

#ifdef STDMETHODCALLTYPE
#undef STDMETHODCALLTYPE
#endif
#define STDMETHODCALLTYPE       STDCALL
/*
 STDMETHOD等の定義を　MSVC++ 4.2 の objbase.h の宣言に合致させるために使用
 */

#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
/*
 戻り値の型がHRESULTであり、関数名がmethodであるメンバ関数
 */

#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
/*
 戻り値の型がtypeであり、関数名がmethodであるメンバ関数
 */

/*
 §4.1.5.2 DLLの外部公開関数用マクロ
 DLLBINDFUNC_ は、DLLの外部に公開する関数を宣言するマクロである。
 */

#define DLLBINDFUNC_(type, method) extern "C" DECLSPEC_DLLEXPORT type STDCALL method
/*
 戻り値の型がtypeであり、関数名がmethodであるDLL外部に公開するグローバル関数
 */

/*
 §4.1.5.3 DLL内部のインプリメンテーションで利用する共通宣言
 
 mpinterface を実装するクラスのメンバ関数宣言マクロ
 */
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE
/*
 mpinterface でSTDMETHOD で定義したメソッドは、実装クラスで　STDMETHODIMP　を
 mpinterface でSTDMETHOD_で定義したメソッドは、実装クラスで　STDMETHODIMP_　を
 それぞれ対応させて実装する。
 */

/*
 §4.1.5.4 DLL内部の単独関数の共通宣言
 インプリメンテーションでメンバ関数以外の単独関数を宣言する時に利用する。
 */
#define BINDFUNC_(type, method)  type STDCALL method
/*
 戻り値の型がtypeであり、関数名がmethodであるDLL内部関数
 */

/*
 ***************************
 §4.2 共通定義
 ***************************
 
 §4.2.1 HRESULT型
 
 MP Core APIの一般的なRETURN値は、HRESULT型である。
 HRESULTの仕様は、COM・OLEの規定に準ずる。
 
 HRESULT型は、32bit整数で、
 ・正数	（＝最上位bitが0）	各メソッドで明記した場合に限り利用する。
 ・0		（＝最上位bitが0）	呼び出し成功
 ・負数	（＝最上位bitが1）	呼び出し失敗（または警告）
 と判別する。
 
 利用者は、負数をエラーとして扱わなければならない。
 代表的な値の定義を以下に示す。
 
 以下のインタフェースで特に明記していないHRESULT型は下記仕様に準拠する。
 
 §4.2.1.1 HRESULT型定義
 
 HRESULT型は 符号付き32bit整数とする。
 */

typedef long LONG;
typedef LONG HRESULT;
#define MP_HRESULT_TYPEDEF(_sc) ((HRESULT)_sc)

/*
 §4.2.1.2 HRESULT型 の値定義
 */

#define MP_NOERROR                          MP_HRESULT_TYPEDEF(0x00000000L)	//処理成功
#define MP_E_UNEXPECTED                     MP_HRESULT_TYPEDEF(0x8000FFFFL)		//予期せぬエラー

#define MP_S_OK                             MP_HRESULT_TYPEDEF(0x00000000L)	//論理値　真
#define MP_S_FALSE                          MP_HRESULT_TYPEDEF(0x00000001L)	//論理値　偽

/*
 MP_S_OK, MP_S_FALSEについて
 HRESULTで返す値のうち、MP_S_OK, MP_S_FALSEは、COMで規定されたS_OK、S_FALSEに準拠する。
 一般的な　TRUE / FALSEと逆の値なので、判定処理には注意が必要である。
 */

#define MPC_HRESULT_FROM_WIN32(x)   (x ? ((HRESULT) (((x) & 0x0000FFFF) | 0x80070000)) : ((HRESULT) 0) )
// winerror.h のHRESULT_FROM_WIN32に準拠


#define MP_E_FILE_NOT_FOUND					MPC_HRESULT_FROM_WIN32(2L)
/*
 「指定パスのファイルが見つからない。」
 例：　CreateFile() WinAPIが、ERROR_FILE_NOT_FOUNDコードを返した時
 */

#define MP_E_ACCESSDENIED                   MP_HRESULT_TYPEDEF(0x80070005L)		// = MPC_HRESULT_FROM_WIN32(5L)
/*
 例：　ファイルオープンの失敗（Write権のないファイルをUPDATEモードでオープン等）
 例：　ファイル生成の失敗（ファイル生成権のないディレクトリにファイルを生成等）
 例：　許可されていない属性をSetした
 例：　OpenMP()せずにページルートをGetInterfaceした
 */

#define MP_E_BAD_FORMAT						MPC_HRESULT_FROM_WIN32(11L)
/*
 「指定パスのファイルがDWファイルでない。」
 例：　ファイルのヘッダ内容などがDWフォーマットになっていない。
 例：　ファイルサイズが０だったり、小さすぎる場合
 */

#define MP_E_OUTOFMEMORY                    MP_HRESULT_TYPEDEF(0x8007000EL)		// = MPC_HRESULT_FROM_WIN32(14L)
/*
 「メモリの獲得に失敗した。」
 */

#define MP_E_WRITE_FAULT					MPC_HRESULT_FROM_WIN32(29L)
/*
 「書き込み中にエラーが発生」
 */

#define MP_E_SHARING_VIOLATION				MPC_HRESULT_FROM_WIN32(32L)
/*
 「ファイルが使用中」
 */

#define MP_E_DISK_FULL						MPC_HRESULT_FROM_WIN32(39L)
/*
 「ディスク不足」
 */

#define MP_E_FILE_EXISTS					MPC_HRESULT_FROM_WIN32(80L)
/*
 「ファイルがすでに存在する。」
 */

#define MP_E_INVALIDARG                     MP_HRESULT_TYPEDEF(0x80070057L)	// = MPC_HRESULT_FROM_WIN32(87L)
/*
 「引数の異常」
 例：　関数の引数に仕様外の値を渡した
 */

#define MP_E_INSUFFICIENT_BUFFER			MP_HRESULT_TYPEDEF(0x8007007AL)	// = MPC_HRESULT_FROM_WIN32(122L)
/*
 「警告：バッファ領域が不足しているため全データを取得できていない」
 例：　OCTS型データをGetAttributeする時に、格納サイズより少ない領域を渡した。
 */

#define MP_E_INVALID_NAME					MPC_HRESULT_FROM_WIN32(123L)
/*
 「名前が不正」
 例：　ファイルオープン時のパスの文字列長や拡張子が仕様外
 */

#define MP_E_DLL_INIT_FAILED				MPC_HRESULT_FROM_WIN32(1114L)
/*
 「DLLの初期化に失敗」
 例：コンテントのDLLのLoadLibraryに失敗した。（DLLが存在しない等）
 */

#define MP_E_NOTIMPL                        MP_HRESULT_TYPEDEF(0x80004001L)
/*
 「未実装の機能」
 デバッグ用メッセージ
 */

#define MP_E_NOINTERFACE                    MP_HRESULT_TYPEDEF(0x80004002L)
/*
 「指定したインタフェースがない」
 例：　GetInterface() でサポートしていないインタフェースを取得した
 */

#define MP_E_CANTSAVE						MP_HRESULT_TYPEDEF(0x80030103L)
/*
 「保存不可」
 例：　UPDATEモードで開いていないファイルにSave, SaveAsした
 */

#define MP_E_OLDFORMAT						MP_HRESULT_TYPEDEF(0x80030104L)
/*
 「DWファイルのバージョンが古いため開けない」
 */

#define MP_E_OLDDLL							MP_HRESULT_TYPEDEF(0x80030105L)
/*
 「DLLファイルのバージョンが古いためロードできない」
 */

#define MP_E_NOT_LWF						MP_HRESULT_TYPEDEF(0x800E0001L)
/*
 「指定ファイルはLWF(LWO専用イメージフォーマット)でない」
 例：ARSMP_LwfToMetaPaper()で指定ファイルがLWFでない
 */

#define MP_E_INVALID_REGISTRY				MP_HRESULT_TYPEDEF(0x800E0002L)
/*
 「レジストリ設定が無効」
 例：　オブジェクトIDに対応するDLLがレジストリに登録されていない
 */

#define MP_E_VERSION_MISMATCH				MP_HRESULT_TYPEDEF(0x800E0003L)
/*
 「バージョン不一致」
 例：　コンテントのDLLが現在のDWCoreのバージョンと異なる
 */

#define MP_E_NEWFORMAT						MP_HRESULT_TYPEDEF(0x800E0004L)
/*
 「DWファイルのバージョンが新しいため開けない」
 */

#define MP_E_BAD_NETPATH						MP_HRESULT_TYPEDEF(0x800E0005L)
/*
 「ネットワーク関連のエラー」
 例： ネットワークパスが間違っている
 例： パスワードが間違っている
 例： ログオンに失敗した
 */

#define MP_E_FATAL						MP_HRESULT_TYPEDEF(0x800E0006L)
/*
 「致命的なエラー。処理を続けられない。」
 MPCSession::Saveに限りこのエラーコードが返る。（ただし、DWCoreが外部から渡されたMP_Fileオブジェクトに結びついている場合に限る。）
 詳細はMPCSession::Saveの説明を参照。
 */

#define MP_E_BAD_FORMAT_ODOA						MP_HRESULT_TYPEDEF(0x800E0007L)
/*
 「ファイルが壊れている。0x0Aが0x0D0Aに変換されている可能性がある。」
 MPCSession::OpenFile時にこのエラーコードが返る。
 詳細はMPCSession::OpenFileの説明を参照。
 */

#define MP_E_BAD_CHECKSUM						MP_HRESULT_TYPEDEF(0x800E0008L)
/*
 「ファイルが壊れている。データのチェックサムが正しくない。」
 MPCSession::OpenFile、MPCProfile::CheckData、MPCObject::Duplicate、
 MPCObject::Unlink、MPCObject::GetAttribute系でこのエラーコードが返る。
 詳細はMPCSession::OpenFileの説明を参照。
 */

#define MP_E_AUTH_FAILED			MP_HRESULT_TYPEDEF(0x800E0009L)
/*
 認証に失敗、セキュリティモジュールでエラーメッセージは表示しなかった。
 Desk や Viewer で、「認証に失敗しました」といったメッセージを表示する。
 */

#define MP_E_AUTH_FAILED_NOMESSAGE	MP_HRESULT_TYPEDEF(0x800E000AL)
/*
 認証に失敗したが、セキュリティモジュールでエラーメッセージを表示したので、
 Desk や Viewer で メッセージを表示しない場合に返る。
 */

#define MP_E_INVALID_CALL			MP_HRESULT_TYPEDEF(0x800E000BL)
/*
 これはデバッグ用のエラーコードである。
 関数が不正に呼び出された場合(認証前にAddAuthenticationを呼んだなど)に返る。
 */

#define MP_E_PROTECTED_OBJECT			MP_HRESULT_TYPEDEF(0x800E000CL)
/*
 セキュリティで転記禁止されたオブジェクトについて
 MPCObjectをUnlinkChild() したり、ストレージオブジェクトをRemoveChild()すると、
 アンリンクは成功するが、内部にアクセスできない特殊なオブジェクトを返す。
 この結果を通知する時にMP_E_PROTECTED_OBJECTを返す。
 MPCObject::UnlinkChild(), IStgObject::RemoveChild() のみで使う。
 */

#define MP_E_OVER_MAX_SIZE			MP_HRESULT_TYPEDEF(0x800E000DL)
/*
 仕様で決めてある、扱えるサイズの上限を超えた場合に返る。
 このエラーコードが返った場合は、リトライなどを行っても無駄なので処理を終了すること。
 */

#define MP_E_OVER_MAX_DIM			MP_HRESULT_TYPEDEF(0x800E000EL)
/*
 仕様で決めてある、扱える寸法の上限を超えた場合に返る。
 このエラーコードが返った場合は、リトライなどを行っても無駄なので処理を終了すること。
 */

#define MP_E_NOPERMISSION			MP_HRESULT_TYPEDEF(0x800E000FL)
/*
 保護された文書を扱う場合で、許可されていない権利を必要とするAPIが呼ばれたときに返る。
 例：文書編集権がない文書に対して AddAuthentication(MP_PERM_PRINT)が呼ばれた
 例：印刷権がない文書に対して OnPrint が呼ばれた
 ただし、フルアクセスモードになっている場合は返らない(成功する)。
 */

#define MP_E_SIGNATURE_MODULE			MP_HRESULT_TYPEDEF(0x800E0010L)
/*
 署名関連の操作で、署名モジュール内でエラーが発生した。
 */

#define MP_E_NOT_ACCEPTABLE_IMS			MP_HRESULT_TYPEDEF(0x800E0011L)
/*
 MRCにできないIMSが入力された。AR11563対策
 */

#define MP_E_SECURITY_MODULE			MP_HRESULT_TYPEDEF(0x800E0012L)
/*
 保護関連の操作で、セキュリティモジュール内でエラーが発生した。
 */

#define MP_E_ORPHAN_SIGNATURE			MP_HRESULT_TYPEDEF(0x800E0013L)
/*
 署名文書でないのに署名オブジェクトがある状態でのエラーを表す
 */

#define MP_E_CUSTOMANN_DLL_UPDATED      MP_HRESULT_TYPEDEF(0x800E0014L)
/*
 カスタムアノテーションが更新された
 */

#define MP_E_APPLICATION_FAILED			MP_HRESULT_TYPEDEF(0x80001156L)
/*
 アプリケーションの起動に失敗した。
 */

#define MP_E_DWM_PRINTER_NOT_AVAILABLE	MP_HRESULT_TYPEDEF(0x80001157L)
/*
 文書生成処理エラー：プリンタを開けない、レジストリからプリンタ情報を取得できない
 */

#define MP_E_DWM_NOPAGE                 MP_HRESULT_TYPEDEF(0x80001158L)
/*
 文書生成処理エラー：印刷ジョブにページデータがない
 */

#define MP_E_DWM_READMF_FAILED          MP_HRESULT_TYPEDEF(0x80001159L)
/*
 文書生成処理エラー：MakerフォルダのMFの読み込みができない
 */

#define MP_E_DWM_READMPI_FAILED         MP_HRESULT_TYPEDEF(0x80001160L)
/*
 文書生成処理エラー：MakerフォルダのMPIファイルの読み込みができない
 */

#define MP_E_DWM_DELTEONCLOSE_ERROR     MP_HRESULT_TYPEDEF(0x80001161L)
/*
 文書生成処理エラー：AR12846対応
 McAfeeのパッチバージョンが古い場合MPCPDのデータ削減処理にて、
 CreateFile(DELET_ON_CLOSE)で失敗する。障害切り分け用
 */

#define MP_E_DWM_ADDCONTDOC_FAILED      MP_HRESULT_TYPEDEF(0x80001162L)
/*
 オリジナルデータの添付に失敗した
 */

/*
 §4.2.1.3 DWのファイルバージョンの定義
 */
// V6:共通で使えるように定義を作成
// DW文書のバージョン値　バージョンを上げるときは値を追加すること V6追加
// 既存のコードから、OLDESTの判断は3で行っていたため、OLDEST=3とする
#define DW_FILEVERSION_LATEST	DW_FILEVERSION_V7
#define DW_FILEVERSION_OLDEST	DW_FILEVERSION_INVALID
#define DW_FILEVERSION_V7		10	// V7
#define DW_FILEVERSION_V6		9	// V6
#define DW_FILEVERSION_V5		8	// V5
#define DW_FILEVERSION_V4		7	// V4
#define DW_FILEVERSION_V3		6	// V3
#define DW_FILEVERSION_V2		5	// V2
#define DW_FILEVERSION_V1		4	// V1
#define DW_FILEVERSION_INVALID	3	// 正規のDW文書ではない


/*
 §4.2.2 基本データ型定義
 
 API定義に使うデータ型を説明する。
 
 /*
 §MP_Integer	32bit符号付き整数
 */
typedef long	MP_Integer;

/*
 §MP_Octet	8bit任意データ
 */
typedef unsigned char	MP_Octet;

/*
 §MP_Pos		メディア座標系での位置（ｘ、ｙ）を表現する
 */
struct MP_Pos { MP_Integer x; MP_Integer y; };

/*
 §MP_Dim			メディア座標系での大きさ（幅×高）を表現する
 */
struct MP_Dim { MP_Integer cx; MP_Integer cy; };

/*
 §MP_Rect				矩形領域をメディア座標系で表現する
 */
struct MP_Rect { MP_Pos pos; MP_Dim dim; };

/*
 §MP_ObjectType	コンポーネントオブジェクト識別子
 */
typedef long MP_ObjectType;

/*
 §MP_RefObjectType	MPF_GetObjectType()などで使うオブジェクトクラスの識別子
 */
typedef const MP_ObjectType	MP_RefObjectType;

/*
 §MP_InterfaceID	インタフェースオブジェクト識別子
 */
typedef long MP_InterfaceID;

/*
 §MP_RefInterfaceID	オブジェクトが提供するインタフェースの識別子
 */
typedef const MP_InterfaceID	MP_RefInterfaceID;

/*!
 §MP_Text	テキスト(Unicode)
 
 MP_Textで表すワイド文字テキストは、UTF-16 BOMなしの形式とする。
 改行コードはCR-LF固定、エンディアンは処理系依存とする。
 
 */
#if defined _PF_WIN32_ || defined _PF_WINCE_

typedef wchar_t MP_Text;
#else

typedef unsigned short MP_Text;

#endif

/*
 * Linux対応 M.Chikyu(09/01/30)
 */

#if defined _PF_WIN32_ || defined _PF_WINCE_

const int MBTEXT_CODEPAGE = CP_ACP;

#else

//const int MBTEXT_CODEPAGE = CP_UTF8;
#define MBTEXT_CODEPAGE CP_UTF8

#endif


/*
 §MP_Path	ファイルを指定する場合の所在情報
 
 ディレクトリの区切り文字は処理系依存とする。
 ネットワークファイルパスは使用できないものとする。使用可能な関数は個別に明記する。
 
 MP_Path 
 Windows:
 システム既定のマルチバイト文字コードで表されたファイルパス。
 Linux:
 UTF-8 BOMなしのテキストで表されたファイルパス。
 
 MP_WPath
 UTF-16 BOMなしのテキストで表されたファイルパス。エンディアンは処理系依存とする。
 */
typedef char MP_Path;	// MP File path 

#if defined _PF_WIN32_ || defined _PF_WINCE_

typedef wchar_t MP_WPath;

#else

typedef unsigned short MP_WPath;

#endif

/*
 * Linux対応 M.Chikyu(09/01/30)
 */

#if defined _PF_WIN32_ || defined _PF_WINCE_

const int FILEPATH_CODEPAGE = CP_ACP;

#else

//const int FILEPATH_CODEPAGE = CP_UTF8;
#define FILEPATH_CODEPAGE CP_UTF8

#endif


#include "mpstring.h"
/*
 §4.2.3 属性定義
 
 MPCObject , StorageObjectでGet / Set する属性について定義する。
 */

/*
 §MP_AName	属性名
 */
typedef char MP_AName;	// MP Attribute name.

/*
 属性名の取りうる値について
 以下に例示するように、様々なモジュール層で定義し、利用している。
 
 ・ストレージオブジェクトで予約されている名前
 シャープ(#)文字で始まる名前は、ストレージで予約されている。
 
 例えば、
 "#dim"、"#pos"、"#pd"、"#bi"、"#dyd"、"#dyp"、"#spd"、"#iconpd"、"#lv"、"#cdl"、
 などがある。（各属性の意味はDWCore 基本設計書参照）
 
 ・各文書要素オブジェクトが個別に定義する名前
 各オブジェクト設計書の属性の説明を参照
 
 各コンテントモデルオブジェクトが、属性の利用規則を定める。
 全く自由にセットを許すオブジェクト
 一切のセットを禁止するオブジェクト
 など、様々である。
 
 例えば、MetaPaperオブジェクトの場合は、
 ダラー($)文字で始まる属性を、自己管理属性として解放している。
 パーセント(%)文字で始まる名前をアプリケーション定義属性として許可している。
 これ以外の名前は、MetaPaperオブジェクトが固有に利用する。外部設定を禁止する。
 等のチェックを実現している。
 
 ・アプリケーションが定義した名前
 各アプリケーション設計書の属性の説明を参照
 
 例えば、ツールバーツールは、MetaPaperオブジェクトの %規則を利用して
 ×印チェックの永続化に独自の属性をセットしている。
 
 属性名の長さ制限について
 属性名は1024バイト以下(NULL文字を含む）であること。
 
 */

/*
 §MP_AType	属性データ型
 */
typedef long MP_AType;	// Attribute Data type

/*
 MP_ATypeが取りうる値
 */
const MP_AType MP_A_UNKNOWN =   0;	// 型無指定（属性に関する情報を問い合わせ時に利用する）
const MP_AType MP_A_INT   =   2;	// 00 0 00010 Universal basic INTEGER,      MP_Integer
const MP_AType MP_A_OCTS  =   4;	// 00 0 00100 Universal basic OCTET STRING, MP_Octet
const MP_AType MP_A_POS   = 106;	// 01 1 01010 Application comp. 10,         MP_Pos
const MP_AType MP_A_DIM   = 107;	// 01 1 01011 Application comp. 11,         MP_Dim

/*
 2	integer型		MP_Integer	汎用,基本,整数		32bit 符号付き整数 -2147483647〜2147483647
 4	octet-string型	MP_Octet	汎用,基本,octstr	任意内容の8bit単位データ列
 106	xy-position型	MP_Pos		応用,構造,[10]		メディア座標系integer型×2
 107	dimension型		MP_Dim		応用,構造,[11]		メディア座標系integer型×2
 */

/*
 §MP_AValue	属性値
 */
struct MP_AValue {
	MP_Integer	asize;	// adataのデータ長（バイト数）
	MP_AType	atype;	// adataのデータ型
	void*		adata;	// 値（atypeに応じた内容が入る）
};

/*
 §MP_Attrs	属性
 */
struct	MP_Attrs {
	MP_AName*	aname;
	MP_AValue 	avalue;
};

/*
 MP_Attrsについて
 
 MP_Attrsは、属性名と属性値の対を１レコードとする属性配列情報である。
 配列の末尾は、属性名にNULLポインタを設定して表現する。
 
 MP_Attrsは、LinkChild() , CanLinkChild() で、同時にパート属性を指定する場合に使う。
 
 利用例
 MP_Attrs p_attrs[] = {
 { "#pos",	{ sizeof(pos), MP_A_POS, &pos } },
 { "#bi",	{ sizeof(bi), MP_A_INT, &bi } },
 { NULL }
 };
 mpcobj->LinkChild(mpcchild, -1, &p_attrs[0]);
 */

/*
 §4.2.4 定数・マクロ定義
 
 DWCoreの中で共通に使うマクロ定義を記述する。
 */

#ifdef NULL
#undef NULL
#endif
#define NULL		0

#ifdef FALSE
#undef FALSE
#endif
#define FALSE		0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE		1

// 09.07.14 - M.Chikyu WindowsMobile対応
#ifndef _PF_WINCE_

#ifdef MAX_PATH
#undef MAX_PATH
#endif
#define MAX_PATH	_MAX_PATH

// 09.07.14 - M.Chikyu WindowsMobil対応
#endif

// コアで制限するデータ最大値のデフォルト
const MP_Integer MPC_MAX_PD_SIZE		= 1*1024*1024*1024;		// DW文書が格納できる１PDの圧縮前の最大サイズ（単位バイト）1GB
const MP_Integer MPC_MAX_PD_SIZE_V6		=    250*1024*1024;		// DW文書が格納できる１PDの圧縮前の最大サイズ(V6まで) 250MB
const MP_Integer MPC_MAX_ATTR_SIZE		=     50*1024*1024;		// DW文書が格納できる属性の圧縮前の最大サイズ（単位バイト） 50MB
const MP_Integer MPC_MAX_FILE_SIZE   =(1024+960)*1024*1024;		// DW文書としてSave, SaveAsできる最大サイズ（単位バイト）1.9GB

const MP_Integer MPC_MAX_PAGE_DIM_SIZE		= 240000;	// ページの最大サイズ 240cm 
const MP_Integer MPC_MAX_PAGE_DIM_SIZE_V6	=  50000;	// ページの最大サイズ(V6まで) 50cm
const MP_Integer MPC_MIN_PAGE_DIM_SIZE		=   3000;	// ページの最小サイズ 3cm

const MP_Pos  MP_NULL_POS = {0,0};
const MP_Dim  MP_NULL_DIM = {-1,-1};
const MP_Rect MP_NULL_RECT = { {0,0}, {-1,-1} };

const MP_Integer MP_ALL_CHILDREN = -1;
const MP_Integer MP_POST = 0;
const MP_Integer MP_PRE = 1;

const MP_Integer MP_TOPMOST = -1;
const MP_Integer MP_BOTTOMMOST = -2;
const MP_Integer MP_UP = -3;
const MP_Integer MP_DOWN = -4;

const MP_Integer MP_NOPART = 0;

/*
 MP_AccessMode		MPCSession::OpenFile() で利用するパラメータ
 */
enum MP_AccessMode {
    MP_UPDATE = 1,		//ファイルをSave可能なモードで開く。
    MP_READONLY = 2,	//ファイルをSaveできないモードで開く。
    MP_COPYREAD = 3		//ファイルを、コア内部の一時ファイルに複製し、ReadOnlyモードで開く
};

/*
 MP_OpenMode		SPI_MP_File::OpenMPFile() で利用するパラメータ
 */
enum MP_OpenMode {
    OM_READONLY  = 0,	//ReadOnlyで開く。誰かがROnly/Updateで開いていたらエラー
    OM_READWRITE = 2,	//Updateで開く。誰かがROnly/Updateで開いていたらエラー	
    OM_FORCE_READ = 10,	//ReadOnlyで開く。誰かが開いていても強引に開く	
    OM_MODEST_READ = 11, //必要なときのみ、ReadOnlyで開く。
    OM_NOT_OPEN	= -1	//GetOpenMode()でファイルが開かれていない状態を示す
};

/*
 MP_SeekMethod	MP_File::Seek() で使用するパラメータ
 */
enum MP_SeekMethod {
    MP_SEEK_BEGIN = 0,		//　ファイルの先頭からシークする
    MP_SEEK_CURRENT = 1,	//　ファイルの現在位置先頭からシークする
    MP_SEEK_END = 2			//　ファイルの最後からシークする
};

// 処理がキャンセルされる場合の汎用定義
#define MP_PROCESS_CONTINUE		1
#define MP_PROCESS_CANCEL		0
#define MP_S_PROCESS_FINISHED	0
#define MP_S_PROCESS_CANCELED	1

struct	MPC_AdvCancelInfo {
    MP_Integer	(STDCALL *callback) (void *userData, MP_Integer percent);
    void		*userData;
};

const	MP_Integer	MP_S_DRAW_FINISHED = 0;
const	MP_Integer	MP_S_DRAW_SUSPENDED = 1;

const	MP_Integer	MP_S_PRINT_FINISHED = MP_S_PROCESS_FINISHED;
const	MP_Integer	MP_S_PRINT_CANCELED = MP_S_PROCESS_CANCELED;

const	MP_Integer	MP_PRINT_CONTINUE = MP_PROCESS_CONTINUE;
const	MP_Integer	MP_PRINT_CANCEL = MP_PROCESS_CANCEL;

const	HRESULT		MP_TRY_AGAIN = 0;
const	HRESULT		MP_RETURN_ERROR = 1;


// V4  ページがカラーかモノクロかを表す。デバイス連携で、カラーモノクロ指定の際に用いる。
#define MP_COLORTYPE_MONO		0
#define MP_COLORTYPE_COLOR		1

// V4 セキュリティ関係の定義
// パーミッション情報の定義(32bit)
typedef MP_Integer MP_Permission;

// 各パーミッションの定義(ビットフラグを用いる)
#define MP_PERM_FULL				0x01 	// full access
#define MP_PERM_DOC_EDIT			0x02	// edit
#define MP_PERM_ANNO_EDIT			0x04	// annotation
#define MP_PERM_PRINT				0x08	// print
#define MP_PERM_COPY				0x10	// plain data copy

// 認証後にパーミッションが減る可能性がある場合、以下のビットを立てる
// GerPermissionの説明を参照
#define MP_CAN_CANCEL_PERM_FULL			0x0100
#define MP_CAN_CANCEL_PERM_DOC_EDIT		0x0200
#define MP_CAN_CANCEL_PERM_ANNO_EDIT	0x0400
#define MP_CAN_CANCEL_PERM_PRINT		0x0800
#define MP_CAN_CANCEL_PERM_COPY			0x1000

/*
 MP_AuthMode		MPCProfile::OpenMP() で使用するモードの定義
 */
enum MP_AuthMode {
	MP_AUTH_DIALOGUE = 1,	// 対話認証
	MP_AUTH_NODIALOGUE = 2,	// 非対話認証
	MP_AUTH_NOPROTECT = 3,	// 常に非対話で認証できる文書のみを認証 (パスワードの場合、パスワードが空の文書など)
	MP_AUTH_CONDITIONAL_DIALOGUE = 4,	// APIからの変更時のモード。CryptAPIからのGUIなどは許容する
};

/*
 MP_AuthInfo		MPCProfile::OpenMP() で使用するパラメータの定義
 */
typedef struct {
	MP_AuthMode		mode;	// 開くときのモード指定
	MP_Permission	perm;	// 開くときのパーミッション指定
} MP_AuthInfo;

// 文書がどのセキュリティモジュールで保護されているか
// (この数値は必ず11以降とする)
#define MP_S_PROTECTED_BY_PSWD	11
#define MP_S_PROTECTED_BY_DDSA	12
#define MP_S_PROTECTED_BY_PSWD128	13
#define MP_S_PROTECTED_BY_PKST	14
#define MP_S_PROTECTED_BY_SDES	15

const int MP_S_OPEN_SECURITY_ID_START = 1000;
const int MP_S_OPEN_SECURITY_NUM = 100;

// MPCProfile::EditSecurity() でセキュリティの設定が解除された場合の返り値
#define MP_S_PROTECTION_REMOVED	2		

// V5:文書が保護されているかどうかを調べる関数。
// hResFromOpenMPにMPCProfile::OpenMP()の返り値を入れて呼び出す。
inline bool MPC_IsDocumentProtected(HRESULT hResFromOpenMP)
{
	return ((hResFromOpenMP > 10) ? true : false);
}

/*
 V4.1
 MPC_SecurityTemplate		MPCProfile::CreateSecurityWithTemplate() で使用するセキュリティテンプレートの定義
 */
typedef struct {
	MP_Integer		type;	// セキュリティの種別(MP_S_PROTECTED_BY_*)
	void*			pData;	// テンプレートの実体
} MPC_SecurityTemplate;

/*
 V5
 SaveWithCompactionModeの追記モードの指定
 */
enum MP_SaveCompactionMode {
	MP_SAVE_COMPACTION_AUTO = 0,   // Save()と同様の動作
	MP_SAVE_COMPACTION_AS_POSSIBLE = 1,   // 可能な限り全更新保存
	MP_SAVE_COMPACTION_NEVER = 2,  // 常に追記保存
};

/*
 V5
 MPCSignature::GetVerificationData() で用いるデータ構造定義
 */
typedef struct _MP_VerificationCondition {
	int iStructSize;
	void* pDocImage;
	long int iPrevDocEnd;
	long int iCurDocEnd;
	long int iNextEditEnd;
	long int iNextDocEnd;
	long int iFullDocEnd;
	long int iVerificationDataStart;
	int iVerificationDataLen;
	int iVolatileDataLen;
	void* pVolatileData;
} MP_VerificationCondition;

/*
 §4.2.5  オブジェクトID, インタフェースIDに関する共通定義
 */
#define MPC_EXTERN_GUID(name, value) const MP_InterfaceID name = value

inline int MP_IsEqual(MP_RefInterfaceID rguid1, MP_RefInterfaceID rguid2)
{
	return(rguid1 == rguid2); 
}

inline int MP_IsInRange(MP_RefInterfaceID rguid, MP_RefInterfaceID min_rguid, MP_RefInterfaceID max_rguid)
{
	if ( min_rguid < max_rguid ) {
		return( (rguid >= min_rguid) && (rguid <= max_rguid) );
	}
	return( (rguid >= max_rguid) && (rguid <= min_rguid) );
    
}

//#define EXTERN_GUID(name, value) MPC_EXTERN_GUID(name, value)	// VC++5.0ではエラーになるため除去する。

/*
 DocuWorksシステムのオブジェクトID採番の規則
 
 DWCore内部で用いる番号は、 メディアID台帳（松本氏管理）で定義された
 メタペーパーオブジェクト＝		0xC013
 メタペーパー内部オブジェクト＝　0x13XX
 バインダオブジェクト＝			0xC014
 バインダ内部オブジェクト＝		0x14XX
 「代理ペン」オブジェクト＝		0x802A
 に基づいている。
 
 インタフェースIDの1000〜1099(10進)は、セキュリティモジュールの
 追加のために予約されており、この範囲のIDは使えない。
 定数MP_S_OPEN_SECURITY_ID_START(=1000)、MP_S_OPEN_SECURITY_NUM(=100)で
 定義されている。
 
 コンポーネントオブジェクトID、インタフェースオブジェクトID 一覧
 DWCoreで定義するID番号を以下に列挙する。
 
 0xC013	CLSID_METAPAPER
 0x1301	CLSID_BASICPAGE
 0x1302	OT_MP_PART
 0x1303	IID_MPCPageRoot
 0x1304	IID_MPCProfile
 0x1305	IID_MPCPaperRoot
 0x1306	IID_MPCContDocRoot
 0x1307	IID_MP_PtrArray
 0x1311	IID_MPCSession
 0x1312	IID_MPCRegisterForGUI
 0x1313	IID_INotificationToGUI
 0x1314	IID_SPISessionForDLL
 0x1315	IID_SPI_MP_File
 0x1316	IID_MP_File
 0x1317	IID_MPCHintFromGUI
 0x1318	IID_BitmapOperations
 0x1319	IID_MPCMediaAdv
 0x131A	IID_MPCText
 0x131B	IID_MPCSelectText
 0x131C	IID_MPCFind3
 0x131D	IID_MP_PDCache
 0x131E	IID_MPCSFXOperations
 0x131F	IID_MPCConvertVersion
 0x1320	IID_PDFactory	// V4追加
 0x1321	IID_DeviceUtilities	// V4追加
 0x1322	IID_MPCSecuritySPI	// V4追加
 0x1323	IID_MPCFind4	// 1999.6.1. V4検索用インタフェース（佐藤要求）
 0x1324	IID_AUTOROTATE	// 自動正立モジュール (1999.6.29)
 0x1325	IID_MPCSecuritySelectorSPI	//セキュリティセレクタ(99.7.16)
 0x1326	IID_PDFactory2  // MPC_PDFactory のV4.1拡張
 0x1327	IID_MPCPswdSecurityTemplateSPI	// V4.1 パスワード用テンプレートSPI
 0x1328	IID_MPCDDSASecurityTemplateSPI	// V4.1 DDSA用テンプレートSPI
 0x1329	IID_MPPModelSPI		// V4.1 プロセスモデルSPI
 
 // V5
 0x132A	IID_MPCSecuritySPI5	// IID_MPCSecuritySPI のV5拡張
 0x132B  IID_MPCSignature // 電子署名インタフェース
 0x132C	IID_MPCSDESSecurityTemplateSPI // SDES テンプレートSPI
 0x132D	IID_MPCPkstSecurityTemplateSPI // 印鑑ツール テンプレートSPI
 0x132E	IID_MPCPswd128SecurityTemplateSPI // V5 128bitパスワード用テンプレートSPI
 
 // V6
 0x132F	IID_MPCFind6	// V6検索インタフェース
 0x1330	IID_SPIBindTextSearch // V6テキスト検索用SPI
 0x1331	IID_PDFactory3 // MPC_PDFactory のV6拡張
 
 // V6.2
 0x1332	IID_MPCContextServiceSecurityTemplateSPI // V6.2 DEセキュリティ用テンプレートSPI
 
 // V7.0
 0x1333	IID_MPCTextAttributeHelper	// MultiByte/Unicodeテキスト属性のアクセス
 0x1334	IID_MPCInternalDocument		// 内部文書名のアクセス
 
 
 0x1350	IID_IPersistMPCObject
 //0x1351	IID_INotifyCallback
 //0x1352	IID_IMPNotificationRegister
 0x1353	IID_IContainer
 0x1354	IID_IContent
 0x1355	IID_IMPContDocInteraction
 0x1356	IID_IContDocument
 0x1357	IID_ISPISession
 0x1358	IID_IFormatAttribute
 0x1359	IID_IMediaIDManager
 0x1360	IID_MP_Children
 0x1361	IID_IReferenceMID
 0x1362	IID_MP_Canvas
 //0x1363	IID_MP_RichCanvas
 0x1364	IID_SPIBindCanvas
 0x1365	IID_SPIBindPD3
 0x1366	IID_MP_PD
 0x1367	IID_BMPPD
 0x1368	IID_WMFPD
 0x1369	IID_SPIBindMPCLT
 0x136A	IID_MP_EMFPD
 0x136B	IID_MP_WMFPD
 0x1370	IID_ImplProfile
 0x1371	IID_ImplBasicPage
 0x1372	IID_IStgObject
 0x1373	IID_CStorageObject
 //0x1374	IID_MPSPI_PDConverter1
 0x1375	IID_EMFPD
 0x1376	IID_ICompressedMPAttribute
 0x1377	IID_MP_JPEGPD
 0x1378	IID_MPC_BigAlloc
 0x1379	IID_MP_MMRPD	// V4追加
 0x137A	IID_ISpecialAttribute	//V4追加
 0x1380	IID_MP_MHPD		// V4追加
 0x1381	IID_MP_BMPMHPD	// V4追加
 0x1382	IID_MP_MRCPD //V6追加
 0x1383	IID_IReadOnlyPersist //V7追加
 0x13E0	CLSID_BASICCONT
 //0x13E1	CLSID_BASICCDOC
 0x13E2	OT_CDOC_REFOBJ
 0x13E3	OT_BASIC_PART
 0x13E4	CLSID_COMPOSITECONT
 //0x13E5	CLSID_PAGESET
 
 0x13F0	IID_MPCObject
 0x13F1	IID_MPCMedia
 0x13F2	IID_MPCContent
 0x13F3	IID_MPCContDocument
 //0x13F4	IID_MPCProcessModelInteraction
 0x13F5	IID_MPCInterface
 
 0x802A	CLSID_REPRESENTATIVE_PEN	// 「代理ペン」オブジェクト
 
 0xC014	CLSID_BINDER
 0x1401	IID_MPCDocRoot	// バインダのDW文書を束ねるインタフェース
 0x1402	OT_BINDER_PART	// バインダのパート要素
 
 
 
 セキュリティ追加用領域
 
 1000(0x03E8) 試験開発用
 1001(0x03E9) コンテキスト・セキュリティ
 */

/*
 §4.2.6 nth に関する共通定義
 
 変数名に、"nth"を含むパラメータは、特に明記されなければ以下の規則に従う。
 
 nthの値             問合せ時（GetNthChild等）の意味	    挿入時（LinkChild等）の意味
 ----------------------------------------------------------------------------------
 −１                末尾の要素を返す                    末尾に挿入する
 ０                  先頭の要素を返す                    先頭に挿入する
 １                  ２番目の要素を返す                  先頭要素と2番目の要素間に挿入
 要素数−１          末尾の要素を返す                    末尾要素の手前に挿入する
 要素数              （動作不定）                        末尾に挿入する
 
 要素数＋１以上      （動作不定）                       （動作不定）
 −２以下            （動作不定）                       （動作不定）
 */

/*
 §4.2.7  ファイルパス指定に関する共通定義
 
 XDWファイルのファイルパスは、以下の規則に従う。
 
 これは
 MPCSession::OpenFile()
 MPCSession::SaveAs()
 で指定するパスに適用される。
 
 ・フルパス形式である事（＝相対パス表現でない事）
 dir1\..\dir2\c.mp とかはダメ
 
 ・開くときは、全体で259バイト以下である事
 保存するときは、全体で255バイト以下である事
 注：Win95, WinNTの最長ファイルパスは終端の'\0'を含めて260バイトである。
 256バイト制限はWin3.1からの仕様を継承している。
 注2: V5.0.2以降、開くときの制限を255バイト以下→259バイト以下に緩和する。
 AR6978対策(IEのローカルキャッシュが256〜259バイトになることが多いため)。
 
 ・全体で、4バイト（例　"\a.a"）以上である事
 
 ・拡張子の末尾が記号でない事
 a.m$ とか、a.m- は不可
 
 ・ファイル名は、
 「ボディ名」 + "." + 「拡張子」
 「ボディ名」 := 1byte以上の文字列
 「拡張子」 := 1byte以上3byte以下の文字列
 から成る最低３バイトで構成される事。
 dir1\.mp とか、dir1\body. とかはダメ
 
 ・拡張子にパスの特殊文字（ . \ など）が含まれない事
 
 ・OSがエラーを返すファイル名は使用できない。
 
 注意：　同一ディレクトリ・同一ファイル名で拡張子末尾が記号のファイルはDWCore一時ファイルとして使用する。
 例えば、ファイルパス
 C:\dir\a.xdw のファイルをOpenFile、SaveAs、Save した場合
 C:\dir\a.xd#, C:\dir\a.xd$ といったパス名の一時ファイルを作成・削除する。
 
 もしこれらのファイルがあった場合、内容は無条件に削除される。
 */

/*
 §4.2.8 メモリ不足などの通知について
 
 アプリケーションは、メモリ不足等、処理が継続できない状況が発生した場合に
 呼ばれるコールバック関数を作成し、DWCoreに登録できる。
 */

/*
 §MPC_CallbackFunction	〜　DWCore障害用コールバック　関数
 */
typedef unsigned long MPC_CallbackID;

const MPC_CallbackID MP_CBID_BADALLOC = 1;	//処理を継続できないメモリ不足（PD描画等は除く）
const MPC_CallbackID MP_CBID_DISKFULL = 2;	//DWCore内部で一時ファイルへの出力ができない場合
const MPC_CallbackID MP_CBID_SAVEERROR = 3;	//MPCSession::Saveの処理中にMP_Fileオブジェクトへの出力に失敗しDWCoreが処理を継続できない場合（ただし、DWCoreが外部から渡されたMP_Fileオブジェクトに結びついている場合に限る。）

typedef HRESULT  (STDCALL * MPC_CallbackFunction)(MPC_CallbackID cbid, void *callback_arg, void *usr_arg);
/*
 ・パラメータ
 cbid			コールバックID
 callback_arg	コールバック引数
 usr_arg			ユーザ定義引数
 
 ・説明
 アプリケーションが実装するコールバック関数。
 
 コールバック引数はコールバックの種類によって違う。
 コールバックIDがMP_CBID_DISKFULLの場合、第2引数はMP_Path *型で、
 不足しているファイルパスもしくはディレクトリパスが入っているかもしれない(NULLならばパスは不明である)。
 コールバックIDがMP_CBID_BADALLOCの場合、第2引数は未定義である。
 コールバックIDがMP_CBID_SAVEERRORの場合、第2引数はMP_Path *型で、
 更新前のDWファイルのパスが入っている（MPCSession::Saveの説明を参照）。
 コールバック関数側では、第2引数を規定の型にキャストして利用すること。
 
 ユーザ定義引数は構造体MPC_Callbackでユーザが指定したもの
 
 ・リターン値
 再試行ならばMP_TRY_AGAINを返す。
 中止ならばMP_RETURN_ERRORを返す。
 */

/*
 §MPC_SetCallback	〜　DWCore障害用コールバック　登録
 */
struct MPC_Callback {
	MPC_CallbackFunction callback;
	void *usr_arg; //ユーザ定義引数
	MPC_Callback() : callback(0), usr_arg(0) {}
};

DLLBINDFUNC_(MPC_Callback*, MPC_SetCallback)(MPC_CallbackID cbid , MPC_Callback * cbdata);
/*
 ・説明
 コールバック関数を、DWCoreに登録する。
 
 コールバックIDをコールバック関数に渡すことによって、コールバック関数を1個にできる。
 ただし、メモリ不足用、一時ファイルディスク不足用とSave失敗用に登録は3回必要である。
 
 登録関数をグローバルにするので、登録はAPL起動時に1回行うだけでよい。
 必要ならば切り替えてもよい。（例えばsessionをユーザ定義引数にしたいとき）
 
 ・リターン値
 MPC_Callback*	それまで登録されていたMPC_Callback構造体を返す
 */

/*
 §MPC_DoCallbackFunction	〜　DWCore障害用コールバックの呼び出し
 */
DLLBINDFUNC_(HRESULT, MPC_DoCallbackFunction)(MPC_CallbackID cbid , void *callback_arg);
/*
 この関数はコールバックを実行するための関数である。
 例えばメモリ不足の場合、MPC_DoCallbackFunction(MP_CBID_BADALLOC, NULL) とコールする。
 */

/*
 §4.2.9 排他機能付きファイルコピー、移動、削除
 
 DWCore は、複製オープン処理と上書き保存処理にクリティカルな処理がある。
 このため、DWCoreはロックファイルを用いた排他制御を行っている。
 （ロックファイルについては §5.1.2.3 各メソッドの定義　を参照）
 
 MPCCopyFile, MPCMoveFile, MPCDeleteFile は、以下の特徴を持つ、
 
 ・内部でロックファイルによる排他制御を実行し、安全なファイル操作を提供する。
 ・Win32利用実装から移行しやすいよう、インタフェース仕様はWin32APIに合わせる。
 〜　引数、戻り値の仕様は、Win32APIと同じである。
 〜　リターン値が FALSE(=0) の場合、GetLastError() で原因を取得する。
 ・ファイルが使用中だった場合、関数内でリトライ処理を行わず即座に復帰する。
 
 ・排他チェックは、ロックファイルの生成でエラーコードがERROR_SHARING_VIOLATION　になるかどうかで判断する。
 ERROR_SHARING_VIOLATION 以外のエラーコードが発生した場合、ロックファイルが生成できなくても処理を継続する。
 これはファイルサーバやCD-ROMのようにファイル作成が禁止された環境でのファイル操作を想定している。
 
 ・ロックファイルは、FILE_FLAG_DELETE_ON_CLOSEモードで CreateFileするので通常は処理完了と同時にファイルを削除する。
 ただし、作成権が許可されていて削除権が禁止されているファイルシステムの場合、ファイルが残る場合もある。
 
 */

/*
 §MPCCopyFile	〜　排他機能付 CopyFile
 
 関数仕様は、基本的に Win32APIの CopyFile() と同じである。
 ただし以下の点が異なる。
 ・ERROR_SHARING_VIOLATIONが原因でロックファイルを獲得できなかった場合、エラー復帰する。
 ・コピー元とコピー先が同一の場合、CopyFileの結果は、ERROR_FILE_EXISTS になるが
 MPCCopyFile() はロックファイルの獲得に失敗するため ERROR_SHARING_VIOLATION になる。
 */

DLLBINDFUNC_(long, MPCCopyFile)(const char *lpExistingFileName, const char *lpNewFileName, long bFailIfExists );

/*
 §MPCMoveFile	〜　排他機能付 MoveFile
 
 関数仕様は、基本的に Win32APIの MoveFile() と同じである。
 ただし以下の点が異なる。
 ・ERROR_SHARING_VIOLATIONが原因でロックファイルを獲得できなかった場合、エラー復帰する。
 ・移動元と移動先が同一の場合、MoveFileExは結果は成功になるが、
 MPCMoveFileEx() はロックファイルの獲得に失敗するため ERROR_SHARING_VIOLATION になる。
 */

DLLBINDFUNC_(long, MPCMoveFile)(const char *pExistingFileName, const char *lpNewFileName);

/*
 §MPCDeleteFile	〜　排他機能付 DeleteFile
 
 関数仕様は、基本的に Win32APIの DeleteFile() と同じである。
 ただし以下の点が異なる。
 ・ERROR_SHARING_VIOLATIONが原因でロックファイルを獲得できなかった場合、エラー復帰する。
 */

DLLBINDFUNC_(long, MPCDeleteFile)(const char *lpFileName );

// V7 
DLLBINDFUNC_(long, MPCCopyFileW)(const MP_WPath* existingFileName, const MP_WPath* newFileName, long bFailIfExists );
DLLBINDFUNC_(long, MPCMoveFileW)(const MP_WPath* existingFileName, const MP_WPath* newFileName);
DLLBINDFUNC_(long, MPCDeleteFileW)(const MP_WPath* fileName);

/*
 §4.2.9 可逆圧縮を自動選択する機能について
 
 (V4.1で追加された機能)
 圧縮度合いを指定してイメージ系PDを生成する各関数の動作に影響を与える。
 これらの関数はmpc_pd.h、mppmodel.hで定義される。
 
 圧縮度合いを指定する引数 level に、フラグMPC_AUTO_LOSSLESS_FLAGが立っていれば、
 非可逆の方がサイズが小さくなると判断されたときに、非可逆が選択される。
 */

/*
 § MPC_AUTO_LOSSLESS_FLAG フラグ
 */
const MP_Integer MPC_AUTO_LOSSLESS_FLAG = 0x100;

/*
 § フラグ操作用マクロ
 */

#define MPC_AutoLossless(level) (((level) & MPC_AUTO_LOSSLESS_FLAG) != 0 )
#define MPC_SetAutoLossless(level) ( (level) | MPC_AUTO_LOSSLESS_FLAG )
#define MPC_LevelWithoutFlag(level) ( (level) & (~MPC_AUTO_LOSSLESS_FLAG ) )

/*
 MPC_AutoLossless(level) は値lebelにフラグMPC_AUTO_LOSSLESS_FLAGが
 立っていれば０以外の値に評価される。
 MPC_SetAutoLossless(level) は値lebelにフラグMPC_AUTO_LOSSLESS_FLAGを
 立てた値に評価される。
 MPC_LevelWithoutFlag(level) は値lebelからフラグMPC_AUTO_LOSSLESS_FLAGを
 除いた値に評価される。
 */


/*
 ****************************************
 §4.3 DWCoreの共通インタフェース定義
 ****************************************
 
 本節では、DWCoreのオブジェクトが提供するインタフェースの共通事項について記述する。
 
 インタフェースオブジェクトとは、COMの用語　”インタフェース”と同じ概念である。
 
 インタフェースオブジェクトは、mpinterface　で宣言する。
 */
#define mpinterface struct

/*
 mpinterface の内容には以下の規則を設ける。
 ・実装に関する宣言を含まない事。
 ＝　メンバ変数を含まない。
 ＝　メンバ関数は、全て仮想関数である。
 ・上位クラスを指定する場合は、上位クラスも mpinterface である事。
 */

/*
 §4.3.1 インタフェースオブジェクト一覧
 */
mpinterface MPCInterface;
mpinterface MPCObject;
mpinterface MPCProfile;
mpinterface MPCMedia;
mpinterface MPCContDocument;
mpinterface MPCSession;
mpinterface MPCRegisterForGUI;
mpinterface MPCHintFromGUI;
mpinterface INotificationToGUI;
mpinterface	MP_Canvas;				// DCをラップし、ＵＩとコアで描画関連情報を交換する。
mpinterface MP_PD;					// Presentation Data 共通インタフェース
mpinterface MP_PtrArray;			// 配列
mpinterface MP_Children;			// 子オブジェクト管理（BasicPageと付箋専用）
mpinterface SPI_MP_File;			// 一般ファイル操作インタフェース
mpinterface MP_File;				// 一般ファイルオブジェクト
mpinterface IContent;				// オブジェクトに従属するオブジェクトに必須のインタフェース
mpinterface IContainer;				// 親オブジェクトが、従属コンテント向けに提供するインタフェース
mpinterface IContDocument;			// Content Documentが備えるインタフェース
mpinterface IMPContDocInteraction;	// MetaPaperオブジェクトがContDoc向けに提供するインタフェース
mpinterface IPersistMPCObject;		// ファイル保存に関連する操作、DWファイルに格納できるオブジェクトに必須
mpinterface IStgObject;				// StorageObject がモデルに提供するインタフェース
mpinterface IFormatAttribute;		// ASN.1 符号化・復号化を実装するためのユーティリティ
mpinterface IMediaIDManager;		// Media ID に関するユーティリティ
mpinterface IReferenceMID;			// 親オブジェクトが備えるMedia ID操作インタフェース
mpinterface ISPISession;
mpinterface ICompressedMPAttribute;
mpinterface MPCSFXOperations;		// 自己解凍型DWファイルの操作インタフェース
mpinterface	MPCConvertVersion;		// DW文書データのバージョン変換
mpinterface MP_PDFactory;			// V4 PD生成インタフェース
mpinterface MP_PDFactory2;			// MP_PDFactory のV4.1拡張
mpinterface MP_DeviceUtilities;		// V4 デバイス連携インタフェース
mpinterface MP_PDFactory3;			// MP_PDFactory のV4.1拡張

mpinterface MPCSignatureHistory;


/*
 §4.3.2 MPCInterface
 
 MPCInterface は、別のインタフェースを取得できるオブジェクトや
 明示的な破棄が必要なオブジェクトが共通に提供するインタフェースである。
 
 §4.3.2.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCInterface, 0x13F5);

/*
 §4.3.2.2 メソッド一覧
 */
mpinterface MPCInterface
{
    STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL) PURE;
    STDMETHOD(Destroy)() PURE;
};

/*
 §4.3.2.3 各メソッドの定義
 
 §GetInterface
 ・パラメータ
 riid	インタフェースID
 phres	結果コードのアドレス
 
 ・説明
 インタフェース（オブジェクト）の取得
 
 複数のインタフェース（オブジェクト）を提供する（コンポーネント）オブジェクトについて
 riidで指定したインタフェースへのポインタを返す。
 
 取得したインタフェースは、
 　１、このインタフェースが属するオブジェクトを破棄する
 　２、このオブジェクトの上位オブジェクトを破棄する
 　３、このオブジェクトが属するファイルをCloseFileする
 　４、このオブジェクトが属するセッションオブジェクトを解放する
 まで有効である。
 
 ・リターン値
 成功した場合は、各インタフェースへのアドレスを返す。
 利用者は、インタフェースIDに応じた型にキャストして参照する。
 
 riidに対応するインタフェースが無い場合、NULLを返す。
 この時phresがNULLでなければエラーコードをセットする。
 
 エラーコードは、特別な障害（メモリ不足など）が起きない限り、
 MP_E_NOINTERFACE	指定IDに対応するインタフェースが無い
 である。
 
 §Destroy
 ・パラメータ
 
 ・説明
 （コンポーネント）オブジェクトを破棄する。
 
 特に明記されない限り、コアが提供するインタフェースに対して、new / delete 演算子を使用してはならない。
 このDestroyメソッドを使ってオブジェクトを解放しなければならない。
 
 Destroy()が成功すると、オブジェクトが提供する全てのインタフェースが無効となる。
 よって、Destroy()成功後、これらのインタフェースを参照してはならない。
 
 ・リターン値
 MP_NOERROR		破棄成功。以降このオブジェクトを参照してはならない。
 負数			破棄失敗（HRESULTのエラーコード参照）
 
 */

/*
 §4.3.3 MPCObject
 
 DocuWorksの文書要素オブジェクトが提供するインタフェース
 
 文書要素オブジェクトの基本操作である
 　オブジェクト識別
 　オブジェクト複製
 　属性操作
 　パート属性操作
 　構造操作
 のメソッドを提供する。
 
 §4.3.3.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCObject, 0x13F0);

/*
 §4.3.3.2 メソッド一覧
 */
mpinterface MPCObject : public MPCInterface
{
    STDMETHOD_(MPCSession*,GetSession)() PURE;
    STDMETHOD_(MP_ObjectType, GetClassID)() PURE;
    STDMETHOD_(MP_InterfaceID, GetIFID)() PURE;
    STDMETHOD_(MPCObject*,Duplicate)(HRESULT* phres = NULL) PURE;
    STDMETHOD(DoProcedure)(MP_Integer procedureID, MPCObject *mpcobj, void *argument, void **result) PURE;
    STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue = NULL, MP_Integer nth_element = -1) PURE;
    STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1) PURE;
    STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1) PURE;
    STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1) PURE;
    STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize) PURE;
    STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL) PURE;
    STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL) PURE;
    STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres = NULL) PURE;
    STDMETHOD(GetNumberOfChildren)() PURE;
    STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres = NULL) PURE;
    STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST) PURE;
    STDMETHOD(GetChildPosition)(MPCObject* child_obj) PURE;
    STDMETHOD_(MPCObject*, GetParent)() PURE;
    STDMETHOD_(MPCObject*, GetMP)() PURE;
    STDMETHOD(SetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue = NULL, MP_Integer nth_element = -1) PURE;
    STDMETHOD(GetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1) PURE;
    STDMETHOD(EnumPartAttribute)(MP_Integer nth_part, MP_AName* aname, MP_Integer namesize) PURE;
    // V7
    STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1) PURE;
    STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1) PURE;
};

/*
 §4.3.3.3 各メソッドの定義
 
 §GetInterface
 （　MP_Interface の説明を参照。　MPCObjectに固有の仕様はない。）
 
 §Destroy
 ・パラメータ
 （MP_Interface 参照）
 
 ・説明
 コンポーネントオブジェクトを破棄する。
 共通の仕様は、MP_Interface 参照
 
 このオブジェクトがルート（＝どのオブジェクトにも従属していない）の場合、
 このオブジェクトと子孫オブジェクトをメモリから解放する。
 
 このオブジェクトが他のオブジェクトに従属している場合、Destroyは失敗する。
 この場合は、親のUnlinkChildをコールしてから、Destroyを呼ぶ。
 
 このオブジェクトがファイルに結びついている場合、Destroyは失敗する。
 この場合は、MPCSession::CloseFile()を使って解放する。
 
 Destroy()が成功すると、
 　・オブジェクトが提供する全てのインタフェース、
 　・このオブジェクトの子孫オブジェクトが提供する全てのインタフェース
 が無効となる。
 よって、Destroy()成功後、これらのインタフェースを参照してはならない。
 
 ・リターン値
 （MP_Interface 参照）
 
 §GetSession
 ・パラメータ
 ・説明
 このオブジェクトが属しているセッションを返す。
 
 ・リターン値
 MPCSession*	セッションへのアドレス
 
 §GetClassID
 ・パラメータ
 ・説明
 オブジェクト種別を問い合わせる。
 例えば、MetaPaperオブジェクトに対して、GetClassID()を発行すると、CLSID_METAPAPERが返される。
 
 ・リターン値
 MP_ObjectType	オブジェクトID
 
 §GetIFID
 ・パラメータ
 ・説明
 現在参照しているインタフェースの代表種別を問い合わせる。
 
 例えば、MetaPaperオブジェクトの場合
 GetInterface(IID_MPCPageRoot)		で得たインタフェースは、IID_MPCPageRoot　を
 GetInterface(IID_MPCContDocRoot)	で得たインタフェースは、IID_MPCContDocRoot　を
 GetInterface(IID_MPCProfile)		で得たインタフェースは、IID_MPCProfile　を
 それぞれ返す。
 
 GetInterfaceした時の引数に必ず一致するとは限らない。例えば、MetaPaperの場合
 
 GetInterface(IID_MPCInterface)		で得たインタフェースは、IID_MPCProfile　を返す。
 
 これはMPCInterfaceが、MPCProfileの一部で構成している事を示している。
 
 ・リターン値
 MP_InterfaceID	このインタフェースの種別
 
 §Duplicate
 ・パラメータ
 phres	結果コードへのアドレス
 
 ・説明
 オブジェクトを複製して返す。
 オブジェクトの子孫にあたるストレージの複製も行う。複製後の子孫オブジェクトは未ロード状態になる。
 
 複製したオブジェクトは、ファイルから切り離されたスクラッチオブジェクトになる。
 不要になったらDestory()で解放しなければならない。
 
 ・リターン値
 MPCObject*	複製したオブジェクトのアドレス
 失敗した場合は、NULLを返す。この時phresがNULLで無ければエラーコードをセットする。
 *phresの値
 MP_E_BAD_CHECKSUM		属性データが壊れている
 
 ・セキュリティ
 転記禁止で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 
 §DoProcedure
 ・パラメータ
 MP_Integer procedureID	呼び出し番号　（意味はインタフェース毎に定義される。）
 MPCObject *mpcobj		呼び出し元のオブジェクト（意味はインタフェース毎に定義される。）
 void *argument			入力引数（意味はインタフェース毎に定義される。）
 void **result			出力引数（意味はインタフェース毎に定義される。）
 
 ・説明
 インタフェース固有の機能を提供する。
 機能の内容はインタフェース毎に定義される。
 
 ・リターン値
 （意味はインタフェース毎に定義される。）
 
 ・セキュリティ
 提供されてる機能とセキュリティ保護状態に応じてエラーになる場合がある。
 
 §SetAttribute
 オブジェクトに属性をセットする。
 
 ・パラメータ
 const MP_AName * aname,		//属性名
 const MP_AValue * avalue, 	//属性値（下記参照）
 MP_Integer nth_element		//属性の配列要素番号
 
 ・説明
 オブジェクトに属性をセットする。
 
 anameについて
 属性の名前を指定する。「4.2.3 属性定義」参照
 
 avalueについて
 名前	型			説明
 ---------------------------------------------------------------------
 asize	MP_Integer	adata が指す領域のバイト数を渡す
 atype	MP_AType	valueのデータ型を示す。（「4.2.3 属性定義」参照）
 adata	void *		atype で指定されたデータ型の属性値
 
 avalueにNULL（省略値）を指定した場合、anameで指定した属性の値を削除する。
 
 nth_element について
 通常、nth_elementは−１（省略値）を指定する。
 同一の属性名で複数の属性値を格納したい場合に配列要素番号を利用する。
 属性によって配列指定を拒否するものもある。
 
 ・リターン値
 
 MP_NOERROR		成功
 エラーコード
 属性名が不正
 属性のデータ型が異なる
 データ型とサイズが異なる
 無効な値
 一時格納のためのディスク容量が不足
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 対応するオブジェクトが文書要素かアノテ要素かは、各オブジェクトの定義を参照。
 文書要素のオブジェクトには、バインダ、メタペーパー、ページ、ヘテロ、ヘッダフッタなどがある。
 
 §SetAttributeF
 ・パラメータ
 const MP_AName* aname	属性名
 const MP_Path* path		属性値が入っているファイルのパス
 MP_Integer nth_element	配列要素番号
 
 ・説明
 SetAttributeFは、pathで指定されたファイルの内容を、OCTS型の属性値としてセットする。
 
 ファイルの内容は、SetAttributeFの中でコピーする。
 よってSetAttributeF　完了後は、pathで指定されたファイルを削除・変更しても構わない。
 
 その他の説明は、SetAttribute参照。
 
 ・リターン値
 SetAttributeのエラーに加えて
 
 pathで指定されたファイルが存在しない場合
 pathで指定されたファイルにアクセスできない
 pathで指定されたファイルが使用中である
 内部で値をコピーする際にディスク不足が発生した
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 
 §GetAttribute
 ・パラメータ
 const MP_AName * aname, 		//属性名
 const MP_AValue * rtn_avalue 	//属性値
 MP_Integer nth_element			//配列要素番号
 
 ・説明
 
 オブジェクトの属性値を取得する。
 
 anameに属性名を、rtn_avalueにオブジェクトから取得したい属性値の型、サイズと領域を渡す。
 通常の属性をgetする場合、nth_elementは−１（省略値）を指定する。
 配列としてセットされている属性をgetする場合、nth_elementに配列要素番号を指定する。
 
 rtn_avalue　について
 
 atype
 データ型を指定する。
 adataがNULLの場合、復帰時に属性のデータ型がセットされる。
 
 asize
 通常は、adataにメモリ確保した領域のバイト数を渡す。
 adataがNULLの場合、復帰時に属性のデータ長がセットされる。
 
 asizeが属性のサイズと異なる場合の扱い
 OCTS型以外の場合
 atypeで指定された型に適合するサイズがセットされていない場合エラーとなる。
 OCTS型の場合
 asizeが必要領域より少なかった場合、asize分のデータのセットしてMP_E_INSUFFICIENT_BUFFERエラーを返す。
 
 adata
 属性値を受け取る領域へのポインタ
 データ型とサイズだけを取得する場合はadataにNULLを指定する。
 
 
 ・リターン値
 サイズの問い合わせ、あるいは値の取得に成功した場合、MP_NOERRORを返す。
 anameで指定した属性がセットされていなかった場合は、エラーを返す。
 
 エラーを返した場合は、rtn_avalueやadata領域の内容は変わらない。
 但し、OCTS型でMP_E_INSUFFICIENT_BUFFERの場合に限り指定サイズ分のデータをセットして返す。
 
 MP_NOERROR	正常
 MP_E_INVALIDARG		属性名、属性データ型、サイズが不正
 MP_E_INSUFFICIENT_BUFFER	属性長がasizeより大きい
 MP_E_BAD_CHECKSUM		属性データが壊れている
 MP_E_ACCESSDENIED	セキュリティ機能、保護状態などにより読み出しが禁止されている
 
 ・セキュリティ
 #pd属性は属性として取得できない。MP_E_ACCESSDENIEDエラーになる。
 #pd属性にアクセスする場合は、MPCLoadPD() を使わなければならない。
 ただし、サイズ問い合わせは可能である。
 転記禁止の場合、nd、#ocrtext、#ocrrectの各属性を GetしようとするとMP_E_ACCESSDENIEDエラーになる。
 これはcont-docのオリジナルデータ、ヘテロのOCR結果テキストをストレージで保護するための特殊な仕様である。
 これらの属性がSetされていないオブジェクトに対してGetした場合はMP_E_ACCESSDENIEDエラーである。
 ただし、サイズ問い合わせは可能である。
 
 §GetAttributeF
 ・パラメータ
 const MP_AName * aname, 		//属性名
 const MP_Path* path			 	//属性値を取り出して格納するファイルのパス
 MP_Integer nth_element			//配列要素番号
 
 ・説明
 属性値をファイルに取り出す。
 
 GetAttributeFを使うと、OCTS型の属性値をpathで指定されたファイルに取り出す事ができる。
 不要になったファイルは利用者側で削除する。
 
 pathで指定されたファイルが存在する場合、無条件に削除して上書きする。
 ファイル作成中にエラーが発生した場合、削除可能ならファイルを削除する。
 
 その他の説明は、GetAttribute参照
 
 ・リターン値
 GetAttributeのエラーに加えて
 
 pathで指定されたファイルが生成できない。
 pathで指定されたファイルにアクセスできない
 pathで指定されたファイルが使用中である
 ファイル作成中にディスク不足が発生した
 
 ・セキュリティ
 GetAttribute参照
 
 §EnumAttribute
 ・パラメータ
 aname	利用者側でメモリを確保し、属性名または空文字列を入力として渡す。
 関数から復帰すると、次の属性名または空文字列がセットされている。
 
 namesize	anameで確保したメモリのバイト数。
 
 ・説明
 オブジェクトにセットされている属性名の数え上げ
 
 オブジェクトが現在保持している全ての属性をコア内部で管理している順序で数え上げる。
 先頭の名前を得る場合、aname領域に空文字列を設定してコールする。
 処理が成功すると、anameに指定された次の属性の名前がanameに返される。
 全ての属性を数え上げた場合、anameは空文字列となる。
 
 数え上げる属性名は、配列属性、組み込み自己管理属性、ユーザ定義属性を含む。
 配列属性の場合、複数の要素が格納されていても、１回と数えられる。
 
 リターン値がMP_NOERRORの場合、aname に見つかった属性名を設定する。
 リターン値がMP_NOERROR以外の場合、anameは空文字列を設定する。
 リターン値がMP_E_INSUFFICIENT_BUFFERの場合、anameには末尾が欠落した属性名を設定する。
 
 ・リターン値
 
 MP_NOERROR：	成功（次の属性が見つかった）
 
 MP_E_ACCESSDENIED：　未認証のためアクセスできない
 MP_E_INVALIDARG：パラメータ不良
 anameがNULL, namesize が 1 以下
 anameで指定された属性がセットされていない
 MP_E_UNEXPECTED： 想定外のエラー（メモリ獲得に失敗）
 MP_E_INSUFFICIENT_BUFFER：　aname の領域不足
 MP_S_FALSE：	次の属性がない。（指定された属性は最後の要素だった）
 
 ・利用例
 HRESULT	hres;
 char name[LEN];
 name[0]  =  '\0';
 for(hres = EnumAttribute(name,  LEN); name[0] ! =  '\0' ; hres = EnumAttribute(name,  LEN))
 if ( hres == MP_NOERROR ) {
 // ここでnameを利用する
 } else if ( hres  == MP_E_INSUFFICIENT_BUFFER ) {
 //名前領域 LEN を広げてやり直し
 } else {
 // 異常状態　数え上げ処理を中止する
 }
 
 
 §CanLinkChild
 
 ・パラメータ
 MPCObject * obj			//（LinkChild参照）
 MP_Integer nth			//（LinkChild参照）
 MP_Attrs * part_attrs	//（LinkChild参照）
 
 ・説明
 リンク可能かどうかの事前判定
 
 objをnth番目の従属オブジェクトとしてリンク可能かどうかを問い合わせる。
 GUIのドラッグ状態表示など、実行しないで結果を知りたい場合に利用する。
 
 ・リターン値
 MP_S_OK		リンク可能
 MP_S_FALSE	リンク不可
 
 注意：
 MP_S_OKはLinkChildの成功を保証はしない。
 たとえばメモリ不足等の実行時エラーが発生する可能性がある。
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）でLinkChildできない場合も、MP_S_FALSE になる。
 
 §LinkChild
 ・パラメータ
 MPCObject * obj			//子にしたいオブジェクト
 MP_Integer nth			//リンク挿入位置
 MP_Attrs * part_attrs	//パート属性
 
 ・説明
 オブジェクトの親子関係のリンク
 
 objをnth番目の従属オブジェクトとしてリンクする。
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 part_attrsが指定された場合、リンク後にSetPartAttributeを実行する。
 
 MetaPaperオブジェクトは複数の親子関係を持つ。
 BasicPageは、PageRootインタフェースにLinkChildする。
 ContentDocumentは、CDocRootインタフェースにLinkChildする。
 
 同一のセッションで生成・ロードしたオブジェクトのみリンク可能である。
 
 
 ・リターン値
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 
 §UnlinkChild
 ・パラメータ
 MP_Integer nth		// アンリンクするオブジェクトの位置
 HRESULT * phres		// 結果コード
 
 ・説明
 従属する子オブジェクトを切り離して返す
 
 このオブジェクトのnth番目の従属オブジェクトをアンリンクする。
 nthの定義は「4.2.6 nth に関する共通定義」参照
 
 成功した場合、リターン値として、アンリンクしたオブジェクトを返す。
 アンリンクしたオブジェクトは、不要になった時点で明示的にDestroy()しなければならない。
 
 nth 番目のオブジェクトが内部でロードされていない場合、ロードした後にアンリンクする。
 オブジェクトがロードできない場合、アンリンクは失敗する。
 
 ・リターン値
 MPCObject*	アンリンクしたオブジェクト
 
 エラーが起きると、リターン値は NULL になる。
 取得できない場合はNULLを返す。この時phresがNULLでなければエラーコードをセットする。
 *phresの値
 MP_E_BAD_CHECKSUM		属性データが壊れている
 
 
 親または子がアンリンクを拒否した場合
 一時ファイルへの書き込みに失敗した。
 オブジェクトがロードできない。
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 
 転記禁止の場合、MPCObjectをリターンし、かつ、phresは MP_E_PROTECTED_OBJECT エラーになる。
 このMPCObjectは、同一のＤＷファイルに再びLinkChildするまで、内部にアクセスできない。
 これはUndo機能などを実現するための特殊仕様である。
 
 §GetNumberOfChildren
 ・パラメータ
 ・リターン値
 子オブジェクトの数を問い合わせる。
 
 ・リターン値
 成功した場合、子オブジェクトの数（0以上の値）が戻る。
 
 
 §GetNthChild
 ・パラメータ
 MP_Integer nth		// 取り出す子オブジェクトの位置
 HRESULT* phres		// 結果コードのアドレス
 
 ・説明
 オブジェクトのnth番目の従属オブジェクトを求める
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 
 オブジェクトがロードできない場合、デフォルト動作はNULLを返す。
 
 ただしオブジェクトがロードできない場合でも
 BasicPageや付箋オブジェクトの場合に限り、代理ペンを生成して返す。
 代理ペンも生成できない場合のみNULLを返す。
 
 ・リターン値
 MPCObject*		取得した子オブジェクト（または代理ペンオブジェクト）
 取得できない場合はNULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 エラーコード
 コンテントのロードができない
 
 §ChangeChildOrder
 
 ・パラメータ
 MP_Integer src_nth	//移動前の位置
 MP_Integer dst_nth	//移動後の位置
 
 ・説明
 子オブジェクトのnth位置を、src_nthからdst_nthに変更する。
 
 dst_nth = MP_TOPMOSTの場合、末尾になる。
 dst_nth = MP_BOTTOMMOST の場合、先頭になる。
 dst_nth = MP_UP の場合、１つ後ろになる。
 dst_nth = MP_DOWN の場合、１つ前になる。
 
 ・利用例
 ChangeChildOrder(0, 1)				先頭の子供を2番目にする。
 ChangeChildOrder(8, 7)				9番目の子供を8番目にする。
 ChangeChildOrder(8, MP_DOWN )		9番目の子供を8番目にする。
 ChangeChildOrder(0, MP_TOPMOST)		先頭の子供を末尾にする。
 ChangeChildOrder(8, 8)				変化しない。
 
 ・リターン値
 
 ・セキュリティ
 文書編集禁止（またはアノテ編集禁止）で実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 
 §GetChildPosition
 
 ・パラメータ
 MPCObject * child_obj	// 位置を取得したい子オブジェクト
 
 ・説明
 指定オブジェクトが何番目に従属しているかを問い合わせる。
 
 ・リターン値
 成功した場合、HRESULTに従属オブジェクトの位置（0以上の値）が戻る。
 応答値の定義は、「4.2.6 nth に関する共通定義」参照
 
 エラーコード
 child_objは子オブジェクトでない。
 
 
 §GetParent
 ・パラメータ
 ・説明
 ・リターン値
 親オブジェクトを取得する。
 
 ・説明
 このオブジェクトの親を取得して返す
 
 ・リターン値
 MPCObject*		親オブジェクト
 親がいない場合はNULLを返す。
 
 
 §GetMP
 ・パラメータ
 
 ・説明
 このオブジェクトの最も近い親MetaPaperオブジェクトを求める。
 
 ・リターン値
 MetaPaperオブジェクトに対してGetMP()を発行した場合、自分自身を返す。
 このオブジェクトがMetaPaperオブジェクトに属していない場合、NULLを返す。
 
 §SetPartAttribute
 ・パラメータ
 nth_part		// どの子供に対応したパート属性かの位置指定
 aname			//（SetAttribute参照）
 avalue			//（SetAttribute参照）
 nth_element		//（SetAttribute参照）
 
 ・説明
 nth_part番目の従属オブジェクトに対応するパート属性を設定する。
 属性操作のパラメータは、SetAttribute参照
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 
 ・リターン値
 SetAttribute参照
 
 ・セキュリティ
 SetAttribute参照
 
 §GetPartAttribute
 ・パラメータ
 nth_part		// どの子供に対応したパート属性かの位置指定
 aname			//（GetAttribute参照）
 rtn_avalue		//（GetAttribute参照）
 nth_element		//（GetAttribute参照）
 
 ・説明
 nth_part番目の従属オブジェクトに対応するパート属性を問い合わせる。
 属性操作のパラメータは、GetAttribute参照
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 
 ・リターン値
 GetAttribute参照
 
 ・セキュリティ
 GetAttribute参照
 
 §EnumPartAttribute
 ・パラメータ
 nth_part	// どの子供に対応したパート属性かの位置指定
 aname		//（EnumAttribute参照）
 namesize	//（EnumAttribute参照）
 
 ・説明
 nth_part番目の従属オブジェクトに対応するパート属性の数え上げ
 aname、namesizeの意味は、EnumAttribute参照
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 
 ・リターン値
 
 
 §4.3.3.4 ファイルからロードされたときの制約
 
 V4では、ファイルからロードされたオブジェクトは、
 ストレージオブジェクトに対してOpenMP()をコールし成功するまでは、
 ストレージオブジェクトの操作が制約される。
 
 特に理由がなければ、OpenMP()のコールは、各オブジェクトの
 OnLoad()内が適当である。
 
 OpenMP()前のストレージオブジェクトの各メソッドの動作は、
 mpc_spi.h の IStgObject を参照のこと。
 */


/*
 §4.3.4 MPCMedia
 
 MPCMediaは可視化可能なオブジェクトが提供するインタフェースである。
 MPCObjectの属性操作、構造操作に加え、描画操作のメソッドが追加される。
 
 §4.3.4.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCMedia, 0x13F1);

MPC_EXTERN_GUID(IID_MPCContent, 0x13F2);	// 特殊用途：DWViewerがBasicPageとContentの分別に利用している。他には仕様を開示しない。

/*
 §4.3.4.2 メソッド一覧
 */
mpinterface MPCMedia : public MPCObject
{
    STDMETHOD(OnDraw)(MP_Canvas* canvas, MPCObject* parent = NULL) PURE;
    STDMETHOD(OnPrint)(MP_Canvas* canvas, MPCObject* parent = NULL) PURE;
    STDMETHOD(CanRotate)(MP_Integer degree) PURE;
    STDMETHOD(Rotate)(MP_Integer degree) PURE;
};

/*
 §4.3.4.3 各メソッドの定義
 */

/*
 §OnDraw
 画面表示を想定した描画を実行する。
 
 ・パラメータ
 canvas	描画の出力対象（MP_Canvasの項を参照）
 parent	（未使用。必ずNULLをセットする。）
 
 ・説明
 canvas が指定する描画対象に、オブジェクトの画像を描画する。
 
 OnDrawは、画面表示を想定した描画を行う。
 75dpi程度に画像縮小され、画面上で頻繁に再描画が繰り返される事を想定して
 縮小時に読みやすい画質や、縮小結果をキャッシュし高速に再描画するモードである。
 
 また、表示障害が発生した場合、OnDrawにパッチを行う。
 
 画面表示以外では、サムネイルのように極端に画像縮小するビットマップ作成に用いる。
 
 OLEサーバの埋め込み表示にOnDrawを用いる。
 canvasのDCがCreateMetaFile()によって作られたDCである場合は表示画質を保証しない。
 この場合は表示結果をキャッシュしない。
 CreateEnhMetaFile()によって作られたDCへの描画はサポートしていない。
 
 canvasとは、DC、表示倍率、などアプリケーションとDWCoreで描画情報を交換し
 座標変換を管理する描画制御オブジェクトである。詳細はMP_Canvasの項を参照
 
 parent は、現在は利用していない。
 旧バージョンの、BasicPageがPaper部の親を持つ構造で、どちらの親からの描画要求かを指定するための名残である。
 
 ・リターン値
 全く描画ができなかった場合、エラーコードを返す。
 
 BasicPageは、子のcontentのOnDraw、または子のPDのOnDrawをコールする。
 各OnDrawがエラーだった場合、その領域に×印を描画する。×印描画に成功すればMP_NOERRORを返す。
 
 ・セキュリティ
 転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。
 印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
 
 §OnPrint
 印刷を想定した描画を実行する。
 
 ・パラメータ
 canvas	（OnDraw参照）
 parent	（OnDraw参照）
 
 ・説明
 OnPrintは、プリンタへの印刷を想定した描画を行う。
 
 また、プリンタドライバの特性に依存する印刷障害が発生した場合、OnPrintにパッチを行う。
 
 印刷以外では、イメージ変換出力のビットマップ作成に用いる。
 これは、”WindowsAPIの描画能力をそのままの画質”という仕様に基づく。
 
 OnDraw()とOnPrint()の結果が、同じか異なるかは、各オブジェクトによって異なる。
 
 ・リターン値
 （OnDraw参照）
 
 ・セキュリティ
 転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。
 印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
 
 §CanRotate
 ・パラメータ
 degree	// 90, 180, 270 のいずれか
 
 ・説明
 指定した角度の回転が可能かどうかを問い合わせる。
 実際の回転は行わない。
 これはGUIのツールバーのアクティブ・インアクティブ表示切替のためにある。
 
 BasicPageオブジェクトの場合、全ての子contentをロードし
 子オブジェクトのCanRotateを問い合わせる。
 子供がロードできない場合、子がMP_S_FALSEを応答した場合、MP_S_FALSEを返す。
 
 ・リターン値
 MP_S_OK		回転可能
 MP_S_FALSE	回転不可
 
 ただし結果がMP_S_OKでも、Rotate()の成功を保証するものではない。
 実行時のメモリ不足エラー等が発生する場合がある。
 
 ・セキュリティ
 文書編集禁止でRotateが実行できない場合、MP_S_FALSE　を返す。(TBD)
 
 §Rotate
 ・パラメータ
 degree	// 90, 180, 270 のいずれか
 
 ・説明
 90度単位の回転を実行する。
 
 ・リターン値
 
 ・注意
 DocuWorksはページ単位の回転のみをサポートする。
 アプリケーションは、ヘテロやヘッダフッタのRotateを単独でコールしてはならない。
 各アノテーションは単独で回転できず、Rotateは常にエラーを返す。
 
 ・セキュリティ
 basic-pageは、文書編集禁止でRotateが実行できない場合、MP_E_ACCESSDENIEDエラーになる。
 basci-page以外のRotateをコールしてはならない。コールした場合の動作は不定（実装依存）
 */

/*
 §4.3.5 MPCContDocument インタフェース
 
 MPCContDocumentはContentDocオブジェクトが提供するインタフェースである。
 
 §4.3.5.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCContDocument, 0x13F3);

/*
 §4.3.5.2 メソッド一覧
 */
mpinterface MPCContDocument : public MPCObject
{
#ifndef SFXVW
    STDMETHOD(RequestRegeneration)() PURE;
    STDMETHOD(BreakRegeneration)() PURE;
#endif //SFXVW
};

/*
 §4.3.5.3 各メソッドの定義
 
 §Request Regeneration
 ・パラメータ
 ・説明
 これはプロセスモデルからの利用を想定する。
 
 body-contentで表現するページ内容を最新状態にするよう要求する。
 実際にどのような処理が発生するかは、content-documentの種類に依存するが、原則としてbody-contentが最新状態になるまで関数から復帰しない動作を想定している。
 ・リターン値
 
 ・セキュリティ
 文書編集禁止または転記禁止の場合、MP_E_ACCESSDENIEDエラーになる。
 
 §Break Regeneration
 ・パラメータ
 ・説明
 これはプロセスモデルからの利用を想定する。
 
 実際にどのような処理が発生するかは、content-documentの種類に依存する。
 Request Regeneration() は処理が完了するまで復帰しないが、別スレッド等からBreakRegeneration()を発行すると、content-documentが処理をキャンセルして復帰するきっかけになる場合がある。
 
 ・リターン値
 */

/*
 §4.3.6 MPCRegisterForGUI インタフェース
 
 MPCRegisterForGUIは各モデルオブジェクトが提供するインタフェースである。
 
 MPCRegisterForGUIは、文書要素の変化を知る必要があるGUIアプリケーションに対する事象通知を想定する。
 MPCRegisterForGUIで登録は、そのオブジェクトがメモリにいる間のみ有効である。
 オブジェクトがメモリ解放された時点で登録は消滅する。
 その後再びファイルからロードしても復活しない。
 
 §4.3.6.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCRegisterForGUI, 0x1312);

/*
 §4.3.6.2 メソッド一覧
 */
mpinterface MPCRegisterForGUI
{
    STDMETHOD(RegisterGUI)(INotificationToGUI* gui, MPCObject* mpcobj = NULL) PURE;
    STDMETHOD(UnregisterGUI)(INotificationToGUI* gui, MPCObject* mpcobj = NULL) PURE;
};

/*
 §4.3.6.3 各メソッドの定義
 
 §RegisterGUI
 オブジェクトにguiで指定した事象通知関数テーブルを登録する。
 
 ・パラメータ
 gui		アプリケーションが実装した通知インタフェース
 mpcobj	登録したいインタフェースの指定
 
 ・説明
 アプリケーションは、guiを実装し、状態変化を知りたいオブジェクトに対してRegisterGUIをコールする。
 
 オブジェクトは、自分の状態が変化すると、登録されているguiの該当するメソッドをコールし変化を通知する。
 通知は、オブジェクトがメモリから消滅するまで通知が送られる。
 メモリから消滅する場合、INotificationToGUI::OnRemoveFromMemory()が通知される。
 
 アプリケーションは、UnregisterGUI()を発行するかOnRemoveFromMemory()通知を受け取るまでguiをメモリ中に保持しなければならない。
 
 同じguiを複数のインタフェースに登録することも可能である。この場合登録した全てのインタフェースにUnregisterGUI()を発行するか、全てのインタフェースからOnRemoveFromMemory()通知を受け取るまでは、guiをメモリ中に保持しなければならない。
 
 同一オブジェクトに異なるguiを登録しても構わない。
 同一オブジェクトに同一のguiを複数回登録した場合、次のUnregisterGUI()で、オブジェクトに対する全登録が解除される。
 
 登録したオブジェクトが複製された場合、複製後のオブジェクトは登録を継承しない。利用者側で複製後のオブジェクトに対してあらためて通知登録する。
 
 ・オブジェクト内部に構造を持つオブジェクトの場合
 MPのようにオブエジェクト内部に構造を持つ場合、どの構造に対する通知登録かを示すため、構造に対応するmpcobjを指定する。例えば、basic-page-rootに対する通知登録をする場合は、GetInterface(IID_MPCPageRoot)して得たインタフェースをmpcobjに指定する。内部構造を持たないオブジェクトであればmpcobjを省略して構わない。
 
 ・リターン値
 
 §UnregisterGUI
 RegisterGUI()で登録した事象通知を解除する。
 
 ・パラメータ
 gui		アプリケーションが実装した通知インタフェース
 mpcobj	登録したいインタフェースの指定
 
 ・説明
 オブジェクトが保持していた通知登録情報を破棄する。
 
 mpcobjにNULLを指定した場合、MPCRegisterForGUIインタフェースを持つオブジェクトの中の全てのインタフェースに対するgui登録を解除する。例えばMPの複数のインタフェースに同一のguiを登録していた場合などは、一括解除される。
 
 ・リターン値
 指定インタフェースに指定通知テーブルが登録されていない場合エラーを返す。
 
 */

/*
 §4.3.7 INotificationToGUI インタフェース
 
 アプリケーションが、オブジェクトから事象通知を受けるためのインタフェース
 
 モデルの状態変化を知る必要があるアプリケーションが実装して、
 MPCRegisterForGUI::RegisterGUI()でモデルオブジェクトに登録するインタフェース。
 
 アプリケーション側でINotificationToGUIを実装し、MPCRegisterForGUI::RegisterGUI()を通じてCore Objectに通知登録すると、Core Objectから通知を受け取ることができる。
 
 全てのメソッドを通じて、
 ・第１引数は、登録したオブジェクトのインタフェースである。
 ・第２引数にchildが渡されるメソッドは、どの子に関する通知かを示す。
 ・rect引数が渡される場合、メディア座標系の領域である。
 座標系は第１引数のオブジェクトの左上を原点とする
 
 
 §4.3.7.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_INotificationToGUI, 0x1313);

/*
 §4.3.7.2 メソッド一覧
 */
mpinterface INotificationToGUI
{
    STDMETHOD(OnRemoveFromMemory)(MPCObject* mpcobj) PURE;
    STDMETHOD(OnChangePresentation)(MPCObject* mpcobj, MP_Rect rect) PURE;
    STDMETHOD(OnChangeDimension)(MPCObject* mpcobj) PURE;
    STDMETHOD(OnMoveChild)(MPCObject* mpcobj, MPCObject* child) PURE;
    STDMETHOD(OnResizeChild)(MPCObject* mpcobj, MPCObject* child, MP_Rect rect) PURE;
    STDMETHOD(OnReorderChild)(MPCObject* mpcobj, MPCObject* child) PURE;
    STDMETHOD(OnLinkChild)(MPCObject* mpcobj, MPCObject* child) PURE;
    STDMETHOD(PreUnlinkChild)(MPCObject* mpcobj, MPCObject* child) PURE;
    STDMETHOD(PostUnlinkChild)(MPCObject* mpcobj, MPCObject* child) PURE;
    STDMETHOD(DoProcedure)(MP_Integer procedureID, MPCObject *mpcobj, void *argument, void **result) PURE;
};

/*
 §4.3.7.3 各メソッドの定義
 
 §OnRemoveFromMemory
 ・パラメータ
 mpcobj	事象が起きたオブジェクト
 
 ・説明
 mpcobjがメモリから消滅する処理の途中で呼び出される。
 メモリから消滅する原因は、スクラッチオブジェクトツリーの削除、ファイルのアンロード、セッションのクローズなど、である。
 ファイルに保存する場合も、しないで破棄する場合もこのメソッドをコールする。
 
 通知を受けたアプリケーションは、OnRemoveFromMemoryの中やその後の処理で、
 １、mpcobjインタフェースのメソッド
 ２、mpcobjに対応するオブジェクトの別のインタフェース
 ３、mpcobjに従属する子・子孫オブジェクトに対する全インタフェース
 ４、mpcobjの親・祖先オブジェクトに対する全インタフェース
 にアクセスしてはならない。
 OnRemoveFromMemory通知後に内部で登録情報を破棄する。
 よってOnRemoveFromMemory() を受けたアプリケーションは、UnregisterGUIを明示的にコールする義務はない。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §OnChangePresentation
 ・説明
 登録したmpcobjがメディアの場合、メディアの可視化状態が変わった後に通知される。
 
 
 §OnChangeDimension
 ・説明
 mpcobjの寸法が変わった後に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §OnMoveChild
 ・説明
 mpcobjに従属するchildのXY位置が変わった後に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §OnResizeChild
 ・説明
 mpcobjに従属するchildの可視化情報の大きさが変わった後に通知される。
 rectにはリサイズ前の領域を渡す。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §OnReorderChild
 ・説明
 mpcobjに従属するchildのnth位置が移動した場合に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §OnLinkChild
 ・説明
 mpcobjにchildがリンクした後に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §PreUnlinkChild
 ・説明
 mpcobjがchildをアンリンクする前に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §PostUnlinkChild
 ・説明
 mpcobjがchildをアンリンクした後に通知される。
 
 ・リターン値
 MP_NOERRORを返す事
 
 §DoProcedure
 ・説明
 オブジェクト固有の拡張定義用。内容については各オブジェクトに依存する。
 
 ・リターン値
 MP_NOERRORを返す事
 
 */

/*
 §4.3.8 MPCHintFromGUI インタフェース
 
 アプリケーションがモデルにヒント情報を与える際のインタフェース
 
 利用方法：
 MPCMedia*	bp = 表示するBasicPageを設定
 MPCHintFromGUI* hint = (MPCHintFromGUI*)bp->GetInterface(IID_MPCHintFromGUI);
 if ( hint )
 hint->DrawFrequently();
 
 
 §4.3.8.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCHintFromGUI, 0x1317);

/*
 §4.3.8.2 メソッド一覧
 */
mpinterface MPCHintFromGUI
{
    STDMETHOD_(void, DrawFrequently)() PURE;
    STDMETHOD_(void, DeletePDCash)() PURE;
};

/*
 §4.3.8.3 各メソッドの定義
 
 §DrawFrequently
 ・説明
 アプリケーションがOnDraw()を頻繁に発行する場合、
 DrawFrequently() を発行しておくと、早くなる可能性がある。
 
 §DeletePDCash
 ・説明
 アプリケーションがDWCore内部でキャッシュしているPD画像を
 明示的に破棄したい場合にコールする。
 画面の色数が変わった場合などに利用する。
 */

/*
 §4.3.9  MPCConvertVersion インタフェース
 
 DW文書データバージョン変換用インタフェース
 
 §4.3.9.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCConvertVersion, 0x131F);

/*
 §4.3.9.2 メソッド一覧
 */
mpinterface MPCConvertVersion
{
    STDMETHOD(DoConvert)(MP_Integer version=0) PURE;
};

/*
 §4.3.9.3 各メソッドの定義
 
 §DoConvert
 ・パラメータ
 version		必ず０を指定する。
 
 ・説明
 文書データを指定したバージョンに変換する。
 versionに０を指定した場合、動作環境の最新のバージョンに変換する。
 Ver3でこのインタフェースを実装するのは、
 　MetaPaperオブジェクト、BasicPageオブジェクト、BodyContentオブジェクト
 のみである。
 
 ・コンテント実装者への注意：
 このメソッドは、DWDeskの「V3一括変換プラグイン」が実行された場合に限りコールされる。
 すなわち、新しいバージョンで動作する前に必ずコールされるものではない。
 各コンテントは、このメソッドが呼び出されなくても古いバージョンのデータで動作しなければならない。
 このメソッドは「V3変換プラグイン」が実行されるたびに何度でもコールされる。
 既に変換済みかどうかは各コンテントで判断し、変換済みの場合はすみやかにリターンすべきである。
 
 ・リターン値
 コンバートが成功した場合、MP_NOERRORを返す。
 MP_NOERROR以外の場合、何らかの理由でバージョン変換に失敗したことを示す。
 
 versionに０以外を指定した場合、エラーを返す。
 その他、変換に失敗する原因は各オブジェクトによって異なる。
 
 子供のオブジェクトがロードできない場合、
 ロードできたオブジェクトだけを変換して、MP_NOERRORを返す。
 */

/*
 §4.4 特別なインタフェースIDの定義
 
 インタフェースIDはインタフェースの宣言があるヘッダに書くのが慣例だが、
 mpcstg/session.cppで参照するためだけに必要なものは、慣例とは異なりここで
 ID番号だけは宣言することにする。詳細はインタフェースのヘッダを参照すること。
 */

/*
 §4.4.1 パスワード用セキュリティテンプレートインタフェースID
 (インタフェースの詳細はmpc_pswd.hを参照)
 */

MPC_EXTERN_GUID(IID_MPCPswdSecurityTemplateSPI, 0x1327);

/*
 §4.4.2 DDSA用セキュリティテンプレートインタフェースID
 (インタフェースの詳細はDDSAグループ提供のヘッダファイルを参照)
 */

MPC_EXTERN_GUID(IID_MPCDDSASecurityTemplateSPI, 0x1328);

/*
 §4.4.3 SDES用セキュリティテンプレートインタフェースID
 */
MPC_EXTERN_GUID(IID_MPCSDESSecurityTemplateSPI, 0x132C);

/*
 §4.4.4 印鑑ツール用セキュリティテンプレートインタフェースID
 */
MPC_EXTERN_GUID(IID_MPCPkstSecurityTemplateSPI, 0x132D);

/*
 §4.4.5 128bitパスワード用セキュリティテンプレートインタフェースID
 */
MPC_EXTERN_GUID(IID_MPCPswd128SecurityTemplateSPI, 0x132E);

/*
 §4.4.6 DEセキュリティ用セキュリティテンプレートインタフェースID
 */
MPC_EXTERN_GUID(IID_MPCContextServiceSecurityTemplateSPI, 0x1332);

/*
 §4.4.7 プロセスモデル用インタフェースID
 (インタフェースの詳細はmppmodel.hを参照)
 */

MPC_EXTERN_GUID(IID_MPPModelSPI, 0x1329);

/*
 §4.5 テンプレートによるセキュリティ設定のための関数
 */
/*
 §4.5.1 セキュリティテンプレートの生成
 
 §MPC_CreateSecurityTemplate
 */

DLLBINDFUNC_(HRESULT, MPC_CreateSecurityTemplate)(MPCSession* pSession, MPC_SecurityTemplate** ppSecutiryTemplate);

/*
 ユーザにセキュリティモジュールを選択させ、さらにそのセキュリティモジュールによる
 セキュリティの設定を行わせる。設定パラメータがセキュリティテンプレートに格納される。
 MPCProfile::CreateSecurityWithTemplate()の引数にセキュリティテンプレートを渡せば、
 設定にしたがった保護をかけることができる。
 
 この関数でセキュリティテンプレートの生成に成功した場合、
 テンプレート使用後に必ず MPC_DestroySecurityTemplate()を呼ぶこと。
 
 pSession <<input>>
 セッションのポインタ
 ppSecutiryTemplate <<output>>
 生成したセキュリティテンプレートのポインタ
 エラー時はNULL
 返り値
 MP_NOERROR 成功
 MP_S_PROCESS_CANCELED ユーザがキャンセルした
 MP_E_INVALIDARG pSession または ppSecutiryTemplate が NULL
 その他(負数) エラー
 */

/*
 §4.5.2 セキュリティテンプレートの開放
 
 §MPC_DestroySecurityTemplate
 */
DLLBINDFUNC_(HRESULT, MPC_DestroySecurityTemplate)(MPCSession* pSession, MPC_SecurityTemplate* pSecutiryTemplate);

/*
 MPC_CreateSecurityTemplate()で生成したテンプレートを開放する。
 
 pSession <<input>>
 セッションのポインタ
 ppSecutiryTemplate <<input>>
 開放するセキュリティテンプレート。
 NULLなら何もせずにMP_NOERRORでリターンする。このときは pSession がNULLでも MP_NOERROR
 返り値
 MP_NOERROR 成功
 MP_E_INVALIDARG pSession が NULL
 その他(負数) エラー
 */


/*
 ****************************************
 §5 オブジェクトと固有インタフェースの定義
 ****************************************
 
 コンポーネントオブジェクト定義
 
 ”コンポーネントオブジェクト”は、複数のインタフェースを提供する。
 
 以下に、DWCoreが提供するコンポーネントオブジェクトと、
 その固有インタフェースについて説明する。
 */

/*
 §5.1	セッション　オブジェクト
 
 アプリケーションがDWCoreと対話するために最初に取得しなければならないオブジェクト。
 DW文書ファイルを開きルートオブジェクトを取得したり、DWCoreが提供する各種インタフェースを取り出すための窓口になる。
 
 複数のMPCSessionを同時に生成する事は可能である。
 ただし異なるMPCSession間でオブジェクトの交換はできない。
 
 §5.1.1 セッションオブジェクトの生成と破棄
 
 §5.1.1.1 生成
 */

/*
 §MPCCreateMPCSession
 */
DLLBINDFUNC_(MPCSession*, MPCCreateMPCSession)(HRESULT* phres = NULL);

/*
 ・パラメータ
 phres	結果コード
 
 ・説明
 新しいMPCSessionインタフェースを生成する。
 
 ・リターン値
 成功した場合、MPCSession*　にアドレスを返す。
 失敗した場合、NULLを返す。この時phresがNULLでなければエラーコードを返す
 
 ・注意
 生成したセッションオブジェクトは、MPCDestroyMPCSession()で破棄する。
 MPCSession::Destroyをコールしてはならない。
 */

/*
 §5.1.1.2 破棄
 */
/*
 §MPCDestroyMPCSession
 */
DLLBINDFUNC_(HRESULT, MPCDestroyMPCSession)(MPCSession*);

/*
 ・パラメータ
 MPCSession*		セッションオブジェクトへのアドレス
 
 ・説明
 MPCSessionインタフェースを破棄する。
 MPCSessionから生成した全インタフェースは無効となる。
 明示的な解放が必要なオブジェクトは、MPCDestroyMPCSessionの前に解放しておく事。
 
 ・リターン値
 成功した場合、MPCSession*　にアドレスを返す。
 失敗した場合、NULLを返す。この時phresがNULLでなければエラーコードを返す
 
 ・注意
 生成したセッションオブジェクトは、MPCDestroyMPCSession()で破棄する。
 MPCSession::Destroyをコールしてはならない。
 */

/*
 §5.1.2 MPCSession インタフェース
 
 DWファイルにアクセスしたり、オブジェクトを生成・参照するためのインタフェースである。
 
 §5.1.2.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCSession, 0x1311);

/*
 §5.1.2.2 メソッド一覧
 */
mpinterface MPCSession : public MPCInterface
{
    STDMETHOD_(MPCObject*, CreateScratchMPCObject)(const MP_ObjectType clsid, HRESULT* phres = NULL) PURE;
    STDMETHOD_(MPCObject*, OpenFile)(const MP_Path* path, HRESULT* phres = NULL, MP_AccessMode access = MP_UPDATE ) PURE;
    STDMETHOD(CloseFile)(MPCObject* obj,MP_Integer commit = 1) PURE;
    
#ifndef SFXVW
    STDMETHOD(Save)(MPCObject* obj) PURE;
    STDMETHOD(SaveAs)(MPCObject* obj, const MP_Path* path) PURE;
    STDMETHOD(IsDirty)(MPCObject* obj) PURE;
#endif //SFXVW
    
    STDMETHOD(ForceReleaseResource)() PURE;
    STDMETHOD_(MPCObject*, CreateFileMPCObject)(MP_File* mpfile, MP_Integer delete_mpfile, HRESULT* phres = NULL) PURE;
    
#ifndef SFXVW
    STDMETHOD(SaveToPath)(MPCObject* obj, const MP_Path* path, MP_Integer withobj, MP_Integer overwrite) PURE;
    STDMETHOD(SaveToFileObject)(MPCObject* obj, const MP_File* mpfile, MP_Integer withobj) PURE;
    
    // V5
    STDMETHOD(SaveWithSignature)(MPCObject* pRootObj, MPCObject* pSignatureObj, const MP_Path* path, MP_Integer withobj, MP_Integer overwrite) PURE;
    STDMETHOD(SaveWithCompactionMode)(MPCObject* obj, MP_SaveCompactionMode iCompactionMode) PURE;
    STDMETHOD(RollbackToPath)(MPCObject* obj, const MP_Path* path, MP_Integer iBeforeSignature ) PURE;
    
    STDMETHOD(CanSaveWithSignature)(MPCObject* pRootObj) PURE;
    
    STDMETHOD_(MPCObject*, OpenFileFromHandle)(const MP_Path* path, void* hFileHandle, HRESULT* phres = NULL, MP_AccessMode access = MP_UPDATE ) PURE;
#endif //SFXVW
    
    // 6.0
    STDMETHOD_(MPCSignatureHistory*, CreateSignatureHistory)( MPCObject* obj, HRESULT* phres = NULL ) PURE;
    
    // 7.0
    STDMETHOD_(MPCObject*, OpenFileW)(const MP_WPath* path, HRESULT* phres = NULL, MP_AccessMode access = MP_UPDATE ) PURE;
#ifndef SFXVW
    STDMETHOD(SaveAsW)(MPCObject* obj, const MP_WPath* path) PURE;
    STDMETHOD(SaveToPathW)(MPCObject* obj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite) PURE;
    STDMETHOD(SaveWithSignatureW)(MPCObject* pRootObj, MPCObject* pSignatureObj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite) PURE;
    STDMETHOD(RollbackToPathW)(MPCObject* obj, const MP_WPath* path, MP_Integer iBeforeSignature ) PURE;
    STDMETHOD_(MPCObject*, OpenFileFromHandleW)(const MP_WPath* path, void* hFileHandle, HRESULT* phres = NULL, MP_AccessMode access = MP_UPDATE ) PURE;
#endif //SFXVW
};

/*
 §5.1.2.3 各メソッドの定義
 
 §GetInterface
 ・説明
 （MPCInterface参照）
 
 §Destroy
 ・説明
 MPCSession::DestroyはDWCore外部から利用してはならない。Destroyに関する唯一の例外である。
 セッションオブジェクトを解放する場合、MPCSession::Destroyではなく、MPCDestroyMPCSession()を使う。
 
 §CreateScratchMPCObject
 ・パラメータ
 clsid	オブジェクト識別番号
 phres	結果コードアドレス
 
 ・説明
 clsidで指定したメモリオブジェクトを生成し、MPCObjectインタフェースを返す。
 clsidの値はDocuWorksシステムで一意に定義された値である。
 
 オブジェクトが複数のインタフェースを提供する場合、どのインタフェースが返されるかはオブジェクトに依存する。
 
 
 生成されたオブジェクトは、内部処理OnCreate()によって初期化され、
 ファイルに結びついていないメモリオブジェクトとして動作する。
 生成したオブジェクトが不要になったら、Destroy()で解放しなければならない。
 
 clsidに対応するオブジェクトが生成できない場合、生成は失敗する。
 
 ・リターン値
 MPCObject*		生成が成功した場合、インタフェースのアドレスを返す
 失敗した場合、NULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 
 §OpenFile
 ・パラメータ
 path	オープンするDWファイルのパス
 phres	結果コードアドレス
 access	オープンするモード
 
 ・説明
 pathで指定されたファイルをオープンし、ルートオブジェクトをロードして返す。
 どのインタフェースを返すかは各オブジェクトに依存する。
 pathの内容は、「4.2.7  ファイルパス指定に関する共通定義」を参照
 
 オープンに成功すると、オープンしたDWファイルのルートオブジェクトを生成して返す。
 取得したオブジェクトが不要になったら、CloseFile() で解放しなければならない。
 
 ファイルのルートオブジェクトが生成できない場合、OpenFileは失敗する。
 
 accessの指定により、次のように動作する。
 
 MP_UPDATE
 書き込み可能モードでオープンし、開ければオブジェクトを返す。
 ファイルが存在しない場合は、生成せずにエラーを返す。
 内部処理のオープン可否は、WinAPI
 ::CreateFile( path, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の動作に準ずる。
 この時点で一時ファイルは作成しない。（Save,SaveAs中に作成する）
 
 MP_READONLY
 読み取り専用モードでオープンし、開ければオブジェクトを返す。
 
 内部処理のオープン可否は、WinAPI
 ::CreateFile( path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の動作に準ずる。
 この時点で一時ファイルは作成しない。（SaveAs中に作成する）
 
 MP_COPYREAD
 一時ファイルに内容を複製し、読取専用でオープンする。
 pathで指定されたファイルは、複製の間だけ一時的にオープンし、複製完了と同時にクローズする。
 
 このモードでオープンしたファイルに対してSave()を発行するとエラーになる。
 
 指定ファイルのオープン可否は、WinAPI
 ::CreateFile( path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の動作に準ずる。
 
 ・複製先の一時ファイルについて
 ファイル名：　レジストリで指定したコア一時ディレクトリに作成するユニークファイル名
 オープンモード： GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, FILE_FLAG_DELETE_ON_CLOSE
 
 何らかの理由により、一時ファイルが生成できない場合、オープンは失敗する。
 一時ファイルの生成に成功した場合、CloseFileまで一時ファイルをオープンし続ける。
 CloseFile時に一時ファイルは削除される。
 
 ・ロックファイルについて
 ファイル名：　pathの拡張子末尾を$にした名前
 オープンモード：GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, FILE_FLAG_DELETE_ON_CLOSE
 
 ファイル内容を一時ファイルに複製する処理は、SaveやSaveAsの処理と競合しないようロックファイルを作成する。
 複製が完了し、pathファイルをクローズした時点でロックファイルをクローズ＆削除する。
 
 ファイルの削除権が無いファイルシステムの場合等、ロックファイルが削除できず残る場合がある。
 仮にロックファイルが残っても、他がオープンしていなければオープンは成功する。
 
 ディレクトリが読取専用でもオープンできるように、ロックファイルが生成できなくても複製は実行する。
 ロックファイルが存在し、かつ使用中だった場合に限りオープンは失敗する。
 ロックファイルが生成できなければ、SaveやSaveAsとの競合は発生しない。
 
 複製中に、DWシステム以外のアプリケーションが直接pathの内容を変更した場合の動作は保証しない。
 大半はファイル内容の異常の検出してエラー復帰するが、
 基本的にDWCoreを経由せずにDWファイルの内容を変更する利用形態はDWCore想定対象外である。
 
 
 ・リターン値
 
 MPCObject*		オープンが成功した場合、インタフェースのアドレスを返す
 失敗した場合、NULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 １、ファイルが存在しない。
 エラーコード ： MP_E_FILE_NOT_FOUND
 メッセージ例    「指定ファイルは存在しません」
 対処            致命的でない失敗。正しいファイル名を指定して再操作する
 
 ２、ファイルが使用中
 エラーコード ： MP_E_SHARING_VIOLATION
 メッセージ例    「指定ファイルは使用中のためオープンできません」
 対処            致命的でない失敗。正しいファイル名を指定して再操作する
 
 ３、アクセスが拒否された
 エラーコード ： MP_E_ACCESSDENIED
 メッセージ例    「指定ファイルをオープンできません。ファイル名やアクセス権の有無を確認してください。」
 対処            致命的でない失敗。正しいファイル名を指定して再操作する
 
 原因詳細の具体例：
 floppy disk を入れていない。
 存在しないドライブを指定した。
 読み取り専用ファイルを書き込み可能でオープンしようとした
 アクセス権がない。
 
 ４、ＭＰ形式でない：非ＭＰファイル、ヘッダ異常、0 バイトのファイル、など
 エラーコード ： MP_E_BAD_FORMAT
 メッセージ例    「指定ファイルはＭＰ形式のファイルではありません」
 対処            正しいファイル名を指定して再度操作する
 
 原因詳細の具体例：
 ファイルサイズがヘッダ分に満たない
 ファイルの先頭1バイトが 0x60 でない
 ファイルのヘッダから、ルートオブジェクト種別情報が見つからない
 ファイルのヘッダから、バージョン情報が見つからない
 ファイル末尾4バイトのトレイラオフセットが異常
 トレイラサイズの不一致
 
 ５、バージョン不一致（フォーマットが古い）：
 エラーコード ： MP_E_OLDFORMAT
 メッセージ例    「指定ファイルは、このバージョンでは開けません」
 対処            ＤＬＬ入れ替え。　将来的にコンバータ起動など
 
 原因詳細の具体例：
 バージョン番号が異常（Ｖ１以前のバージョン番号が入っていた）
 現在市場に出ている版で本エラーが発生したらデータ破壊とみなしてよい。
 
 ６、DLLロード不可：       ＤＬＬがロードできない
 エラーコード ： MP_E_DLL_INIT_FAILED
 メッセージ例    「インストールが正しいか確認して下さい」
 対処            ＤＬＬ入れ替え
 
 ７、バージョン不一致（フォーマットが新しい）：
 エラーコード ： MP_E_NEWFORMAT
 メッセージ例：「DWファイルのバージョンが新しいため開けない」
 対処：	DocuWorks ソフトを新しいバージョンに入れ替える
 
 ８、ファイル名不正： コアのMPファイル名の制限を満たさない、
 エラーコード ： MP_E_INVALID_NAME
 メッセージ例    「正しいファイル名を指定して下さい。」
 対処            名前を変えて再操作する
 
 原因詳細の具体例：
 ファイルパスが指定されていない
 ファイルパス長が 4 バイト未満
 ファイルパス長が 256 バイト以上 (開くときは 260 バイト以上)
 拡張子がない
 拡張子が4文字以上
 ファイル名がない（＝拡張子しかないファイル名）
 ファイルパスの末尾の1バイトがアルファニューメリックでない。
 
 ９、DLLバージョン不一致： DLLのバージョンが異なる
 エラーコード ： MP_E_VERSION_MISMATCH
 メッセージ例    「インストールが正しいか確認して下さい」
 対処            ＤＬＬ入れ替え
 
 １０、レジストリ不良： コア動作に必要なレジストリが設定されていない
 エラーコード ： MP_E_INVALID_REGISTRY
 メッセージ例    「インストールが正しいか確認して下さい」
 対処            レジストリの再設定
 
 １１、その他の致命的エラー ：ReadFile()( WinAPI )のエラー、など。
 エラーコード ： MP_E_UNEXPECTED
 メッセージ例    「オープン時に致命的エラーが発生しました」
 対処            ＭＰ終了　または システム再起動
 
 １２、0D0A変換エラー ：0x0Aを0x0D0Aに変換されたためファイルが壊れている
 エラーコード ： MP_E_BAD_FORMAT_0D0A
 メッセージ例    「指定ファイルの内容が壊れています」
 対処            そのファイルは開けない。正しいファイル名を指定して再度操作する
 
 １３、チェックサムエラー ：ファイルのトレーラ部分のチェックサムが正しくない
 エラーコード ： MP_E_BAD_CHECKSUM
 メッセージ例    「指定ファイルの内容が壊れています」
 対処            そのファイルは開けない。正しいファイル名を指定して再度操作する
 
 
 §CloseFile
 ・パラメータ
 obj			DWファイルのルートオブジェクト
 commit		0 = 破棄終了。　1 = 保存終了（内部でSave実行後ファイルを閉じる）
 
 ・説明
 
 objで指定されたルートオブジェクトに対応するDWファイルを閉じる。
 CloseFile() はオブジェクトの解放（Destroy処理）も同時に実行する。
 利用者は、CloseFile()成功後に、objとその子孫オブジェクトにアクセスしてはならない。
 
 objはDWファイルのルートオブジェクトでなければならない。
 
 objがファイルに結びついていない場合、エラーを返す。
 ファイルに結びついていないオブジェクトをストレージに格納する場合は、SaveAs()を使う。
 
 commit==0でCloseFileした場合、最後にSave、SaveAs した後の変更は破棄される。
 
 commitが1の場合、クローズ前にそれまでの編集内容がDWファイルに保存される。
 保存に失敗した場合、クローズしないで復帰する。（保存に関する動作は、Saveを参照）
 エラーコードが返された場合、オブジェクトは解放されない。この場合、
 commit==1でリトライするか、
 commit==0で破棄終了して、
 オブジェクトを解放しなければならない。
 
 ・リターン値
 Save()のエラーを参照
 
 
 §Save
 ・パラメータ
 obj			DWファイルのルートオブジェクト
 
 ・説明
 objとその子孫の変更をファイルに保存する。
 objがファイルに結びついたルートオブジェクトでない場合、セーブは失敗する。
 UPDATEモードでオープンしていない場合、セーブは失敗する。
 
 追記条件が成立した場合、追記保存を行う。
 　追記保存を行うと、編集内容に関わらずファイルサイズは増加する。
 
 追記条件は、
 (1) 追記保存後の無効データが5MB未満
 (2) 追記保存後の無効データが全サイズの半分未満
 (3) 追記保存後の全サイズが1GB以下
 のすべてを満たすこと。追記保存後の無効データサイズ、全サイズは
 保存前に近似推定しているので、誤差を含む。
 
 ・全更新時の一時ファイルについて
 追記条件が成立しない場合、Saveはファイル全体を更新する。
 この場合、
 １、それまでのファイルを　pathの末尾を#にしたファイル名にMoveする
 ２、pathの名前のファイルを生成し更新内容を出力する。
 ３、出力に成功したら、末尾#のファイルを削除する。
 という手順で行う。
 もし一時ファイルに移動できない場合、Saveは失敗する。
 この場合、末尾#のファイルを元に戻してエラー復帰する。
 
 末尾#のファイルが既に存在する場合、無条件に上書きする。
 
 ・利用者がMP_Fileオブジェクトを渡したファイルを更新する場合、
 上記手順とは異なる更新処理を行う。
 追記条件が成立した場合はMP_Fileオブジェクトの末尾に更新
 データを追記する。
 
 追記条件が成立しない場合、SaveはMP_Fileオブジェクトの
 全データを更新する。
 この場合、
 １、一時ファイルを作成する。
 ２、MP_Fileオブジェクトの内容を一時ファイルにコピーする。
 ３、MP_Fileオブジェクトに更新内容を出力する。
 ４、出力に成功したら、一時ファイルを削除する。
 という手順で行う。
 もし一時ファイルにコピーできない場合や更新内容を出力できない
 場合、Saveは失敗する。
 通常の失敗では、Saveはエラー復帰する（エラーコードは”リター
 ン値”を参照）。	
 致命的な失敗では、SaveはエラーコードMP_E_FATALを返す。致命的
 な失敗は、外部から渡されたMP_Fileオブジェクトにデータを出力で
 きないことが原因である。SaveがMP_E_FATALを返した場合、アプリ
 ケーションは以後DWCoreを参照してはならない。
 
 ・コールバック関数について
 ディスクフルが原因でMP_Fileオブジェクトの内容を一時ファイルに
 コピーできない場合、SaveはコールバックIDがMP_CBID_DISKFULLの
 コールバック関数を発行する。コールバック関数がMP_TRY_AGAINを
 返した場合、Saveは一時ファイルへの出力をリトライし、正常復帰
 する場合がある。コールバック関数がMP_TRY_AGAIN以外を返した場
 合、Saveはエラー復帰する。コールバックIDがMP_CBID_DISKFULLの
 コールバック関数はアプリケーションに一時ファイルのファイルパス
 を与える（セクション”MPC_CallbackFunction”を参照）。
 
 外部から渡されたMP_Fileオブジェクトにデータを出力できない場合、
 SaveはコールバックIDがMP_CBID_SAVEERRORのコールバック関数を発
 行する。関数がMP_TRY_AGAINを返した場合、SaveはMP_Fileオブジェ
 クトへの出力をリトライし、エラー復帰をする場合がある。コールバッ
 ク関数がMP_TRY_AGAIN以外を返した場合SaveはエラーコードMP_E_FATAL
 を返す。コールバックIDがMP_CBID_SAVEERRORのコールバック関数は
 アプリケーションに更新前のDWファイル（一時ファイル）のファイル
 パスを与える。ただし、Save処理中はDWCoreが一時ファイルをMP_UPDATE
 モードで開いている。
 
 ・ロックファイルについて
 Saveは、OpenFile（複製モード）やSaveAsと処理が競合しないように
 パスの拡張子末尾を$にしたロックファイルを作成する。（詳細はOpenFile参照）
 このロックファイルはSave完了と同時に削除される。
 
 ・リターン値
 
 保存時のエラーコード （ MPCSession::Save(), SaveAs() の 返り値 )
 
 １、保存できないＭＰだ：
 原因
 UPDATEモードでオープンしていないファイルをSaveしようとした。
 スクラッチオブジェクトだった。
 エラーコード ： MP_E_CANTSAVE
 メッセージ例    「上書き保存できません。別の名前で保存して下さい。」
 対処            SaveAsする
 
 
 ２、ファイル生成不可： ファイル生成失敗
 エラーコード ：MP_E_WRITE_FAULT 
 メッセージ例    「保存できません。別の名前で再度操作して下さい。」
 対処            SaveAsする
 
 ３、ディスクフル：      　
 エラーコード ： MP_E_DISK_FULL
 メッセージ例    「ディスクフル。」
 対処            ファイルを削除して再操作。あるいは別ドライブにSaveAs
 
 ４、ファイル名不正： コアのMPファイル名の制限を満たさない、ドライブがない
 エラーコード ： MP_E_INVALID_NAME
 メッセージ例    「正しいファイル名を指定して下さい。」
 対処            名前を変えてSaveAsする
 
 ５、ファイルサイズが最大値を超えている：
 エラーコード ： MP_E_OUTOFMEMORY
 メッセージ例    「ファイルを小さくして保存してください。」
 対処			ファイルサイズを小さくしてから再操作。
 
 ６、ファイル名不良：　アクセス権がない。読込専用ファイル
 エラーコード ： MP_E_ACCESSDENIED
 メッセージ例    「ファイルのアクセス権を確認してください。」
 対処			別名でSaveAsまたは
 
 ７、ファイルが使用中：　OpenFile（COPYREAD)中。他プロセスで編集中。
 エラーコード ： MP_E_SHARING_VIOLATION
 メッセージ例    「使用中です。再度操作してください」
 対処			しばらくして再操作。または、別名保存
 
 
 ８、その他のエラー：
 主な原因：
 各モデルが保存を拒否した（Sync()でNULL復帰）
 objがルートオブジェクトでない
 objがファイルに結びついていない
 
 disk full以外のWriteFile()( WinApi )エラー,引数不正、
 オブジェクトがファイルに結びついていない、など。
 エラーコード ： MP_E_UNEXPECTED
 メッセージ例    「システム障害。別の名前で保存して再起動して下さい。」
 対処            一時的に別名保存をしてオリジナルを残してシステム再起動
 
 §SaveAs
 ・パラメータ
 obj			ルートオブジェクト
 path		保存するファイルパス
 
 ・説明
 pathにファイルを作成して、objとその子孫をファイルに書き込む。
 objはルートオブジェクトでなければならない。
 pathをUPDATEモードで作成できない場合、SaveAsは失敗する。
 pathで指定されたファイルが既に存在した場合、無条件にファイル内容を削除する。
 
 SaveAs()に成功した場合、それまでオープンしていたファイルは閉じられ、pathに作成したファイルをUPDATEモードでOpenFileした状態になる。
 
 SaveAs内部でCreateFile成功後に書き込みエラーが発生した場合は無条件にファイルを削除する。ただし、アクセス権等の理由でファイルが削除できない場合は不完全なファイルが残る。CreateFile前にエラーが発生した場合は既存ファイルを削除しない。
 
 
 ・リターン値
 Save()の記述を参照
 
 
 
 §IsDirty
 ・パラメータ
 obj
 
 ・説明
 指定されたMPCオブジェクトが更新されているかどうかを問い合わせる。
 更新後まだストレージに未保存であれば、MP_S_OKを、
 最後にストレージに保存されてから更新されていない場合、MP_S_FALSEを返す。
 objがルートオブジェクトでなかった場合の応答値は不定である。
 
 1. CreateScratchMPCObject()、OpenFile()、で取得した直後のオブジェクトはMP_S_FALSEを返す。
 2. その後、objか、objの子孫に変更が発生した場合、MP_S_OKを返す。
 3. Save()、SaveAs()した直後のオブジェクトはMP_S_FALSEを返す。
 
 ・リターン値
 MP_S_OK		保存必要
 MP_S_FALSE	保存不要
 
 
 §ForceReleaseResource
 ・パラメータ
 
 ・説明
 この関数を呼んだ時点で不必要なSession以下のメモリ資源を解放する。
 しかし、必ずしも空きができるとは限らない。
 
 ・リターン値
 常にMP_NOERRORを返す。
 
 §CreateFileMPCObject
 ・パラメータ
 MP_File* mpfile		// DWCoreの外部でオープンされたファイル
 MP_Integer delete_mpfile	// 1: MPCSession::CloseFile()とMPCSession::SaveAs()の内部でmpfileのMP_File::Destroy()をコールする 0: しない
 HRESULT* phres	//結果コードへのアドレス
 
 ・説明
 既に開かれているMP_Fileオブジェクトを利用して、ルートのMPCObjectを返す。
 データベース中やネットワークサーバなど、特殊な環境下にあるDWファイルを直接アクセスするケースを想定している。
 利用者は、個々の環境に合わせたMP_Fileインタフェースを実装して利用する。
 通常のファイルをオープンする場合は、MPCSession::OpenFile() を利用する事。
 
 DWファイルデータはmpfileの先頭シーク位置から始まり末尾シーク位置で終わる事。
 CreateFileMPCObjectの内部でシーク位置を0にしてからDWファイルデータを読み出す。よって、CreateFileMPCObject発行時に与えるmpfileのシーク位置は任意で良い。
 
 CreateFileMPCObjectを実行してから、CloseFile()またはSaveAs()で解放するまでの間mpfileが参照するデータの内容やオブジェクト状態（パス名やシーク位置）を外部から変えてはならない。
 CloseFile()またはSaveAs()で解放した後、mpfileのシーク位置は任意である。
 
 delete_mpfileが１の場合、CloseFile()またはSaveAs()を発行するとmpfileのMP_File::Destroy()が呼ばれる。よって、その後mpfileを参照してはならない。
 delete_mpfileが0の場合、CloseMPFile()またはSaveAs()を発行すると、その後CreateFileMPCObjectではmpfileを参照しない。よって、呼び出し側でmpfileを破棄しなければならない。
 
 MP_FileのモードがOM_READWRITE以外場合、Save()とCloseFile()での保存は失敗する。
 
 ・リターン値
 （OpenFile参照）
 
 §SaveToPath
 ・パラメータ
 MPCObject* obj		// DWファイルのルートオブジェクト
 const MP_Path* path	// 保存先ファイルパス
 MP_Integer withobj		// 1: 保存後、MPCObjectを保存先ファイルに結びつける。 0: 結びつけず、もとのままにする。
 MP_Integer overwrite	// 1: 既に保存先ファイルが存在する場合、上書き保存する。 0: 既にファイルが存在する場合、関数は失敗する。
 
 ・説明
 pathにファイルを作成して、objとその子孫をファイルに書き込む。
 objはルートオブジェクトでなければならない。
 pathをUPDATEモードで作成できない場合、SaveToPathは失敗する。
 
 SaveToPath()に成功した場合、withobjが１であればそれまでオープンしていたファイルを閉じ、pathに作成したファイルをUPDATEモードでOpenFileした状態になる。
 SaveToPath()に成功した場合、withobjが0であれば元のファイルに結びついたままの状態になり、保存先pathのファイルは閉じる。
 
 pathで指定されたファイルが既に存在する場合、overwriteが１であれば既存ファイルを削除してから保存する。よって、ファイル作成中に書き込みエラーなどが発生しSaveToPathが失敗した場合、既存ファイルは削除されている。
 
 pathで指定されたファイルが既に存在する場合、overwriteが0であればSaveToPathは失敗し既存ファイルを削除しない。
 
 SaveToPathが失敗した場合、objの内容は変わらない。
 
 保存先ファイル作成後に書き込みエラーが発生した場合は保存先ファイルを削除する。ただし、アクセス権等の理由でファイルが削除できない場合は不完全なファイルが残る。
 
 ・リターン値
 Save()のリターン値を参照。さらに以下のリターン値が返る場合がある。
 
 保存先ファイルが存在する：      　
 エラーコード ： MP_E_FILE_EXISTS	 
 メッセージ例   「保存先ファイルは既に存在します。」
 対処              ファイルを削除して再操作。あるいは別名で再操作。
 
 §SaveToFileObject
 ・パラメータ
 MPCObject* obj		// DWファイルのルートオブジェクト
 MP_File* mpfile		// 保存先ファイルオブジェクト
 MP_Integer withobj	// 1: 保存後、MPCObjectを保存先ファイルオブジェクトに結びつける。 0: 結びつけず、もとのままにする。
 
 ・説明
 objとその子孫をmpfileに書き込む。
 objはルートオブジェクトでなければならない。
 mpfileがREADWRITEモードでない場合、SaveToFileObjectは失敗する。
 
 SaveToFileObjectは内部でmpfileのSeekを発行し、シーク位置を先頭に移動してからDWファイルデータを書き込む。DWデータ書き込み後は、mpfileのSetFileSizeを発行し、mpfileのサイズを書き込んだDWデータサイズにする。
 
 書き込みエラーなどでSaveToFileObjectが失敗した場合、
 mpfileの内容は変更され不完全なデータが書き込まれる。
 よって、呼び出し側でmpfileの不完全データを破棄しなければならない。
 
 SaveToFileObject()に成功した場合、withobjが１であればそれまでオープンしていたファイルを閉じ、mpfileをCreateFileMPCObjectでオープンした状態になる。よって、CloseFile()またはSaveAs()で解放するまでの間mpfileが参照するデータの内容やオブジェクト状態（パス名やシーク位置）を外部から変えてはならない。
 CloseFile()またはSaveAs()で解放するときにmpfileのDestroyは発行しないので呼び出し側でmpfileを破棄する必要がある。
 
 SaveToFileObject()に成功した場合、withobjが0であればobjは元のファイルに結びついたままの状態である。mpfileのCloseやDestroyは発行しないので、呼び出し側で破棄する必要がある。
 
 SaveToFileObject発行後のmpfileのシーク位置は任意である。
 
 ・リターン値
 Save()の記述を参照。
 mpfileの操作中にmpfileがエラーを返した場合は、そのエラーを返す。
 
 
 §SaveWithSignature
 ・パラメータ
 MPCObject* pRootObj		// DWファイルのルートオブジェクト
 MPCObject* pSignatureObj	// 署名オブジェクト
 const MP_Path* path		// 保存先ファイルパス
 MP_Integer withobj		// 1: 保存後、MPCObjectを保存先ファイルに結びつける。 0: 結びつけず、もとのままにする。
 MP_Integer overwrite	// 1: 既に保存先ファイルが存在する場合、上書き保存する。 0: 既にファイルが存在する場合、関数は失敗する。
 
 ・説明
 署名を付けて保存する。
 
 
 §SaveWithCompactionMode
 ・パラメータ
 MPCObject* obj
 MP_SaveCompactionMode iCompactionMode
 
 ・説明
 追記/全更新を明示的に指定して保存する。
 iCompactionModeの意味はMP_SaveCompactionModeの宣言部を参照。
 
 
 §RollbackToPath
 ・パラメータ
 MPCObject* obj
 const MP_Path* path
 MP_Integer iBeforeSignature
 
 ・説明
 署名直前/直後の状態に復元する。
 iBeforeSignatureが0なら署名直前、0以外なら署名直後。
 
 §CanSaveWithSignature
 ・パラメータ
 MPCObject* pRootObj
 
 ・説明
 署名保存ができるか確認する。
 現状の実装では、署名文書でなく、かつ署名オブジェクトが文書中にある
 場合を確認する(この場合MP_E_ORPHAN_SIGNATUREを返す)。
 */

/*
 §5.1.3 SPI_MP_File インタフェース
 
 一般ファイルを操作するためのインタフェースである。
 
 §5.1.3.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_SPI_MP_File, 0x1315);

/*
 §5.1.3.2 メソッド一覧
 */
mpinterface SPI_MP_File
{
    STDMETHOD_(MP_File*, CreateMPFile)(const MP_Path* path, HRESULT* phres = NULL) PURE;
    STDMETHOD_(MP_File*, OpenMPFile)(const MP_Path* path, MP_OpenMode omode = OM_READONLY, HRESULT* phres = NULL) PURE;
    STDMETHOD(DeleteMPFile)(const MP_Path* path) PURE;
    STDMETHOD(MoveMPFile)(const MP_Path* oldpath, const MP_Path* newpath) PURE;
    STDMETHOD(CopyMPFile)(const MP_Path* oldpath, const MP_Path* newpath) PURE;
	
    // V7
    STDMETHOD_(MP_File*, CreateMPFileW)(const MP_WPath* path, HRESULT* phres = NULL) PURE;
    STDMETHOD_(MP_File*, OpenMPFileW)(const MP_WPath* path, MP_OpenMode omode = OM_READONLY, HRESULT* phres = NULL) PURE;
    STDMETHOD(DeleteMPFileW)(const MP_WPath* path) PURE;
    STDMETHOD(MoveMPFileW)(const MP_WPath* oldpath, const MP_WPath* newpath) PURE;
    STDMETHOD(CopyMPFileW)(const MP_WPath* oldpath, const MP_WPath* newpath) PURE;
};

/*
 §5.1.3.3 各メソッドの定義
 
 §CreateMPFile
 
 ・パラメータ
 const MP_Path* path		作成するファイルのパス
 HRESULT* phres			結果コードのアドレス
 
 ・説明
 ファイルを作成する。
 作成に成功すると、ファイルは MP_OpenMode::OM_READWRITE でオープンされた状態になる。
 
 この関数内部はMPCSessionインタフェースで定義したロックファイル操作は行わない。
 
 詳細動作は Win32 API の
 ::CreateFile( path, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の仕様に準ずる。
 
 ・リターン値
 MP_File*
 ファイル作成に成功すると、MP_Fileオブジェクトのアドレスを返す。
 失敗するとNULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 エラーコードは、Win32 API のGetLastError()の値に応じて返す。
 
 GetLastError()の値			エラーコード
 -----------------------------------------------
 ERROR_PATH_NOT_FOUND:		MP_E_INVALID_NAME
 ERROR_FILE_NOT_FOUND:		MP_E_INVALID_NAME
 ERROR_INVALID_DRIVE:		MP_E_INVALID_NAME
 ERROR_INVALID_NAME:			MP_E_INVALID_NAME
 ERROR_SHARING_VIOLATION:	MP_E_SHARING_VIOLATION
 ERROR_LOCK_VIOLATION:		MP_E_SHARING_VIOLATION
 ERROR_DISK_FULL:			MP_E_DISK_FULL
 ERROR_ACCESS_DENIED:		MP_E_ACCESSDENIED;
 その他のエラー:				MP_E_WRITE_FAULT
 
 
 §OpenMPFile
 
 ・パラメータ
 const MP_Path* path		オープンするファイルのパス
 MP_OpenMode omode		モード
 HRESULT* phres			結果コードのアドレス
 
 ・説明
 
 ファイルが存在しない場合は、エラーになる。
 
 OM_READONLYの場合、詳細動作は Win32 API の
 ::CreateFile( path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の仕様に準ずる。
 
 OM_READWRITEの場合、詳細動作は Win32 API の
 ::CreateFile( path, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の仕様に準ずる。
 
 OM_FORCE_READの場合、詳細動作は Win32 API の
 ::CreateFile( path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
 の仕様に準ずる。
 
 OM_MODEST_READの場合、ファイルからの読み込みが必要な場合に、都度
 OM_READONLYと同じ仕様で開いて読み込む。
 OpenMPFile時は、開けることを確認後、実際のファイルはクローズする。
 
 この関数内部はMPCSessionインタフェースで定義したロックファイル操作は行わない。
 
 
 ・リターン値
 MP_File*
 ファイルオープンに成功すると、MP_Fileオブジェクトのアドレスを返す。
 失敗するとNULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 エラーコードは、Win32 API のGetLastError()の値に応じて返す。
 
 GetLastError()の値			エラーコード
 -----------------------------------------------
 ERROR_PATH_NOT_FOUND:		MP_E_INVALID_NAME
 ERROR_INVALID_DRIVE:		MP_E_INVALID_NAME
 ERROR_INVALID_NAME:			MP_E_INVALID_NAME
 ERROR_FILE_NOT_FOUND:		MP_E_FILE_NOT_FOUND
 ERROR_SHARING_VIOLATION:	MP_E_SHARING_VIOLATION
 ERROR_LOCK_VIOLATION:		MP_E_SHARING_VIOLATION
 ERROR_ACCESS_DENIED:		MP_E_ACCESSDENIED;
 その他のエラー:				MP_E_UNEXPECTED
 
 §DeleteMPFile
 ・パラメータ
 const MP_Path* path		削除するファイルのパス
 
 ・説明
 pathで指定されたファイルを削除する。
 実装はWin32 APIの、DeleteFile()をコールする。
 
 ・注意
 DeleteMPFileは、DWCoreのDWファイルアクセスとの排他制御を行わない。
 一般アプリケーションがDWファイルを削除する場合は MPCDeleteFile を使うこと。
 
 ・リターン値
 
 
 §MoveMPFile
 ・パラメータ
 const MP_Path* oldpath
 const MP_Path* newpath
 
 ・説明
 oldpathからnewpathにファイルを移動する。
 仕様詳細は、Win32 APIの、MoveFile()に準ずる。
 
 ・注意
 MoveMPFileは、DWCoreのDWファイルアクセスとの排他制御を行わない。
 一般アプリケーションがDWファイルを移動する場合は MPCMoveFileEx を使うこと。
 
 ・リターン値
 
 §CopyMPFile
 ・パラメータ
 const MP_Path* oldpath
 const MP_Path* newpath
 
 ・説明
 oldpathからnewpathにファイルをコピーする。
 newpathにファイルが存在する場合、上書きする。
 仕様詳細は、Win32 APIの、CopyFile()に準ずる。
 
 ・注意
 CopyMPFileは、DWCoreのDWファイルアクセスとの排他制御を行わない。
 一般アプリケーションがDWファイルをコピーする場合は MPCCopyFile を使うこと。
 
 ・リターン値
 
 */

/*
 §5.1.4 MPCSFXOperations インタフェース
 
 ”自己解凍型DWファイル”に関する操作を提供するインタフェースである。
 
 §5.1.4.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCSFXOperations, 0x131E);

/*
 §5.1.4.2 メソッド一覧
 */

struct MPC_SFXInfo {
	unsigned long	creationtime_low;	//DWFileの作成日時（下位32ビット）
	unsigned long	creationtime_high;	//DWFileの作成日時（上位32ビット
	unsigned long	lastwritetime_low;	//DWFileの最終更新日時（下位32ビット）
	unsigned long	lastwritetime_high;	//DWFileの最終更新日時（上位32ビット）
	unsigned long	attributes;			//DWFileのファイル属性
	MP_Integer		seekpos;			//SFXFile中のDWFile開始位置（０基数）
	MP_Integer		filesize;			//SFXFile中のDWFileサイズ（バイト数）
};

mpinterface MPCSFXOperations  {
#ifndef SFXVW
    STDMETHOD(CreateSFXFile)(const MP_Path* dwfilepath, const MP_Path* sfxfilepath, const MP_Path* sfxexepath, const MP_Path* qvexepath) PURE;
    STDMETHOD(GetSFXInfo)(const MP_Path* sfxfilepath, MPC_SFXInfo* sfxinfo=NULL) PURE;
    STDMETHOD(ConvertSFXFileToDWFile)(const MP_Path* sfxfilepath, const MP_Path* dwfilepath) PURE;
#endif //SFXVW
    
    STDMETHOD_(MP_File*, OpenPartialMPFile)(const MP_Path* path, MP_Integer startpos, MP_Integer size, MP_OpenMode omode = OM_READONLY, HRESULT* phres = NULL) PURE;
    
    // V7
#ifndef SFXVW
    STDMETHOD(CreateSFXFileW)(const MP_WPath* dwfilepath, const MP_WPath* sfxfilepath, const MP_WPath* sfxexepath, const MP_WPath* qvexepath) PURE;
    STDMETHOD_(MP_File*, OpenPartialMPFileW)(const MP_WPath* path, MP_Integer startpos, MP_Integer size, MP_OpenMode omode = OM_READONLY, HRESULT* phres = NULL) PURE;
    STDMETHOD(GetSFXInfoW)(const MP_WPath* sfxfilepath, MPC_SFXInfo* sfxinfo=NULL) PURE;
    STDMETHOD(ConvertSFXFileToDWFileW)(const MP_WPath* sfxfilepath, const MP_WPath* dwfilepath) PURE;
#endif //SFXVW
};

/*
 §5.1.4.3 各メソッドの定義
 
 
 §CreateSFXFile
 
 自己解凍型DWファイルを作成する。
 
 ・パラメータ
 
 const MP_Path* dwfilepath	自己解凍化するDW文書ファイルのパス
 const MP_Path* sfxfilepath	作成結果を出力するパス
 const MP_Path* sfxexepath	mpcsfx.exe があるファイルパスを指定する
 const MP_Path* qvexepath	dwqview.exe があるファイルパスを指定する
 
 ・説明
 dwfilepathで指定された DW文書ファイルを自己解凍型ファイルにする。
 作成された自己解凍型ファイルはsfxfilepathで指定されたファイル名に出力する。
 
 sfxexepathとqvexepathは、自己解凍型ファイルに格納されるプログラムである。
 各exeのファイル名をフルパスで指定する。
 
 dwfilepath、sfxexepath、qvexepathは、READONLYでオープンできる事
 他のプロセスが各ファイルをUPDATEモードでオープンしている場合、作成は失敗する。
 
 dwfilepathの内容がDW文書ファイルかどうかのチェックは行わない。
 ファイルが０バイトの場合はファイルを作成せずにエラー復帰する。
 
 ・リターンコード
 作成に成功した場合、MP_NOERRORを返す。
 
 dwfilepathをREADONLYでオープンする際のエラーは、
 SPI_MP_File::OpenMPFileのエラーコードに準ずる。
 
 sfxexepathをファイルクリエイトする際のエラーは
 SPI_MP_File::CreateMPFileのエラーコードに準ずる。
 
 sfxexepath、qvexepathをREADONLYでオープンする際のエラーは、
 資源使用中の場合は、MP_E_SHARING_VIOLATIONを返す。
 それ以外の場合は、MP_E_INVALIDARG　を返す。
 
 書き込み時にディスクスペースがない場合、MP_E_DISK_FULL　を返す。
 DW文書ファイルが０バイトの場合、MP_E_BAD_FORMATを返す。
 DW文書ファイルの属性や日時情報が取得できない場合　MP_E_UNEXPECTEDを返す。
 その他のエラーの場合、MP_E_UNEXPECTED、MP_E_WRITE_FAULT等を返す。
 
 ・セキュリティ
 dwfilepathが保護されたＤＷ文書の場合、
 MP_S_PROTECTED_BY_PSWD		パスワードによって保護されている
 MP_S_PROTECTED_BY_DDSA		DDSAによって保護されている
 など、OpenMPに依存したエラーコードを返す。
 
 §GetSFXInfo
 SFXファイルかどうかの判定と、管理情報の取得
 
 ・パラメータ
 const MP_Path* sfxfilepath	情報を取得したい自己解凍型DW文書ファイル
 MPC_SFXInfo* sfxinfo		SFXに関する情報をセットする領域を渡す（NULL指定可）
 
 ・説明
 sfxfilepathで指定した自己解凍型DW文書ファイルに関する情報を取得する。
 情報は、リターンコードとsfxinfoにセットする。
 sfxinfoがNULL（省略値）の場合、リターンコードのみを返す。
 
 sfxinfoにセットされる値は以下のとおり
 
 ・creationtime_low;		//DWFileの作成日時（ファイル時間の下位32ビット）
 ・creationtime_high;	//DWFileの作成日時（ファイル時間の上位32ビット
 ・lastwritetime_low;	//DWFileの最終更新日時（ファイル時間の下位32ビット）
 ・lastwritetime_high;	//DWFileの最終更新日時（ファイル時間の上位32ビット）
 SFXファイル作成時に、
 　BOOL_XD GetFileTime(hFile, lpftCreation, lpftLastAccess, lpftLastWrite)
 で得たlpftCreationとlpftLastWriteを返す。
 値の意味はWin32APIの仕様に準ずる。
 
 ・attributes;			//DWFileのファイル属性
 は、SFXファイル作成時に、
 　DWORD GetFileAttributes(lpszFileName)
 で得たリターン値を返す。
 値の意味はWin32APIの仕様に準ずる。
 
 ・seekpos;			//SFXFile中のDWFile開始位置（０基数）
 ・filesize;			//SFXFile中のDWFileのサイズ（バイト数）
 SFXファイルに格納されているDW文書ファイルのシーク位置とサイズを返す
 
 ・リターンコード
 １以上	自己解凍型DW文書ファイルである
 SFXファイルのバージョン番号を返す。
 （ストレージバージョン番号とは異なる）
 ０		自己解凍型DW文書ファイルでない
 （＝ファイル末尾の数バイトの内容を参照して判定する）
 負数	ファイルアクセスに関するエラーが発生した場合
 MP_E_INVALID_NAME		ドライブ名やパスが不正
 MP_E_FILE_NOT_FOUND		ファイルが存在しない
 MP_E_ACCESSDENIED		アクセス権がない
 MP_E_SHARING_VIOLATION	使用中でオープンできない
 MP_E_UNEXPECTED			他、メッセージ想定外のエラー
 などを返す。
 
 §ConvertSFXFileToDWFile
 ・パラメータ
 const MP_Path* sfxfilepath
 const MP_Path* dwfilepath
 
 ・説明
 sfxfilepathで指定した自己解凍型DW文書ファイルから
 DW文書ファイルを取り出して、dwfilepathに出力する。
 
 作成したファイルの属性は、WinAPIのCreateFile()のデフォルト動作に準ずる。
 ファイル属性の設定は、必要に応じて呼び出し側で処理する。
 
 ・リターンコード
 作成に成功した場合、MP_NOERRORを返す。
 
 sfxexepathをREADONLYでオープンする際のエラーは、
 SPI_MP_File::OpenMPFileのエラーコードに準ずる。
 dwfilepathをファイルクリエイトする際のエラーは
 SPI_MP_File::CreateMPFileのエラーコードに準ずる。
 
 書き込み時にディスクスペースがない場合、MP_E_DISK_FULL　を返す。
 
 その他のエラーの場合、MP_E_UNEXPECTED、MP_E_WRITE_FAULT等を返す。
 
 §OpenPartialMPFile
 ファイルの一部を参照するMP_Fileオブジェクトを生成する。
 
 ・パラメータ
 const MP_Path* path		オープンするファイルのパス
 MP_Integer startpos		ファイルの何バイト目をMP_Fileの先頭位置とみなすかの指定
 MP_Integer size			MP_Fileで扱うファイルサイズの指定
 MP_OpenMode omode		必ずOM_READONLYを指定する。
 HRESULT* phres			結果コードのアドレス
 
 ・説明
 ミニビューワが、自己解凍型DW文書ファイル（EXE）中にあるDW文書を直接オープン
 するために　MPCSession::CreateFileMPCObject() と併用して使う。
 
 OpenPartialMPFile()は、pathのstartposバイト目からsizeバイトを参照する
 MP_Fileを生成する。生成されたMP_Fileオブジェクトは、
 指定範囲のRead()が可能である。
 Seek()はファイルの先頭が指定するとstartposバイト目とみなし
 ファイルの末尾を指定すると(startpos+size-1)バイト目とみなす
 Size()はsizeを返す。
 Write(), SetFileSize() はエラーになる。
 
 ・リターンコード
 MP_File*	ファイルオープンに成功すると、MP_Fileオブジェクトのアドレスを返す。
 失敗するとNULLを返す。この時phresがNULLでなければエラーコードをセットする。
 
 phresのエラーコードは、
 指定した部分領域がファイルの全長を超える場合、MP_E_INVALIDARGを返す。
 omodeにOM_READONLY以外を指定した場合、MP_E_INVALIDARGを返す。
 その他は、SPI_MP_File::OpenMPFile()に準ずる。
 
 */

/*
 §5.2	MetaPaper　オブジェクト
 
 DW文書ファイルのルートとなり、BasicPageやContDocを束ねるオブジェクトである。
 */

/*
 §5.2.1 MetaPaper オブジェクトの生成と破棄
 
 §5.2.1.1 生成
 MPCSession::CreateScratchMPCObject()
 MPCSession::OpenFile()
 のいずれかで生成される。
 
 何らかのオブジェクトに従属した場合、親の
 MPCObject::UnlinkChild()
 MPCObject::GetNthChild()
 でロードされる。
 
 §5.2.1.2 破棄
 スクラッチなルートの場合、自身のDestroy()で破棄する。
 DWファイルのルートの場合、MPCSession::CloseFile()で破棄する。
 ルート以外の場合、親のMPCObject::UnlinkChild()でスクラッチなルートにしてから破棄する。
 
 §5.2.1.3　オブジェクトID
 */
MPC_EXTERN_GUID(CLSID_METAPAPER, 0xC013);

/*
 §5.2.2 MPCPageRoot インタフェース
 
 BasicPageを管理するインタフェース
 このインタフェースの子として、BasicPageオブジェクトをリンクできる。
 
 §5.2.2.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCPageRoot, 0x1303);

/*
 §5.2.2.2 メソッド一覧
 
 mpinterface MPCObjectと同じ
 
 §5.2.2.3 各メソッドの定義
 
 （MPCObjectの説明参照）
 */

/*
 §5.2.3 MPCContDocRoot インタフェース
 
 ContDocを管理するインタフェース
 このインタフェースの子として、ContDocオブジェクトをリンクできる。
 
 §5.2.3.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCContDocRoot, 0x1306);

/*
 §5.2.3.2 メソッド一覧
 
 mpinterface MPCObjectと同じ
 
 §5.2.3.3 各メソッドの定義
 （MPCObjectの説明参照）
 */

/*
 §5.2.4 MPCProfile インタフェース
 
 このインタフェースの子として、content オブジェクトをリンクできる。
 
 §5.2.4.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCProfile, 0x1304);

/*
 §5.2.4.2 メソッド一覧
 */
mpinterface MPCProfile : public MPCObject
{
// 12.02.17 Bito - セキュリティ対応
#ifndef _SEC_MP_
    STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL) PURE;
#else
    // セキュリティ認証に必要なデータを引数に追加
    STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL, void* authdata = NULL) PURE;
#endif
    STDMETHOD(DefineAttribute)(const MP_AName* aname, MP_AType atype, MP_Integer nth_element = -1) PURE;
    STDMETHOD(UndefineAttribute)(const MP_AName* aname) PURE;
    STDMETHOD_(MPCProfile*,ShallowDuplicate)(HRESULT* phres = NULL) PURE;
    STDMETHOD(GetStorageVersion)() PURE;
    STDMETHOD(GetFilePath)(MP_Integer size, MP_Path* path) PURE;
    // V4 追加
    STDMETHOD(AddAuthentication)(MP_Permission perm) PURE;
    STDMETHOD(EditSecurity)() PURE;
    STDMETHOD_(MP_Permission, GetPermission)(HRESULT* phres = NULL) PURE;
    STDMETHOD_(MP_Permission, GetAuthenticatedPermission)(HRESULT* phres = NULL) PURE;
    STDMETHOD(ShowSecurityInfo)() PURE;
#ifndef SFXVW
    STDMETHOD(CheckData)(MP_Integer* nth_page, MP_Integer* nth_org, MP_Integer* others, MPC_AdvCancelInfo* info = NULL) PURE;
#endif //SFXVW
    // V4.1 追加
    STDMETHOD(CreateSecurityWithTemplate)(MPC_SecurityTemplate* pTemplate) PURE;
    // V5
    STDMETHOD(GetNumberOfSignatures)() PURE;
    STDMETHOD_(MPCObject*, GetNthSignatureObject)(MP_Integer nth, HRESULT* phres = NULL) PURE;
    STDMETHOD(GetSaveStorageVersion)() PURE;
    // V6
    STDMETHOD(GetTrailerAttribute)(unsigned long iTag, MP_AValue* rtn_avalue=NULL) PURE;
    
    STDMETHOD(ReleaseSecurity)() PURE;
    STDMETHOD(AddAuthenticationEx)(MP_AuthInfo* auth) PURE;
    // V62
    STDMETHOD(GetSecurityModuleData)(char* pModuleData) PURE;
    // V7
    STDMETHOD(GetFilePathW)(MP_String &path) PURE;
};
/*
 §5.2.4.3 各メソッドの定義
 
 （MPCObjectの説明参照）
 
 §OpenMP
 
 ・パラメータ
 auth	認証用情報（Ｖ３では常にNULLを指定する）
 
 ・説明
 OpenMPを実行し、成功すると、文書（またはバインダ）の内部にアクセスできるようになる。
 一度OpenMP()を発行すると、CloseFile() するまで有効である。
 
 文書が保護されていない場合、OpenMPは 常に成功し MP_NOERROR になる。（auth の値は無視される。）
 文書が保護されていて、auth == NULL の場合は、
 MP_S_PROTECTED_BY_PSWD		パスワードによって保護されている
 MP_S_PROTECTED_BY_DDSA		DDSAによって保護されている
 を返す。
 文書が保護されていて、auth を指定した場合は、authで指定した条件で認証処理を行う。
 auth->mode は、対話操作の有無を指定する。
 MP_AUTH_DIALOGUE を指定すると、必要があれば対話操作を実行して認証を行う
 MP_AUTH_NODIALOGUE を指定すると、対話操作なしで認証できる場合に限り認証を行う。
 対話操作を実行しないと認証できない場合、OpenMPは失敗し MP_E_AUTH_FAILEDを返す。
 auth->permは、その後の処理に必要な権利を限定する場合に指定する。
 　通常に開く場合は 0 を指定する。
 　印刷を実行するために開く場合は、MP_PERM_PRINT を指定する。
 
 認証に成功すると MP_NOERROR を返す。
 一旦認証したパーミッションは、CloseFile() するまで有効である。
 保護された文書の場合、既に認証が成功しているのに auth が指定されて呼ばれた場合は MP_E_INVALID_CALL になる。
 
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
 
 ・リターン値
 MP_NOERROR : 成功
 MP_S_PROTECTED_BY_*			セキュリティモジュールによって保護されている(正の値であることに注意)
 MP_S_PROCESS_CANCELED		キャンセルされた
 MP_E_AUTH_FAILED			認証に失敗した。必要であれば Viewer 等でエラーメッセージを表示する。
 MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗したが、セキュリティモジュールでエラー表示したので Viewer 等ではメッセージ表示しないでほしい。
 MP_E_INVALID_CALL			認証が成功しているのに auth が指定されて呼ばれた
 
 
 §DefineAttribute
 
 　この関数は仕様から削除する。利用してはならない。
 
 §UndefineAttribute
 
 　この関数は仕様から削除する。利用してはならない。
 
 §ShallowDuplicate
 ・パラメータ
 phres	結果コード
 
 ・説明
 従属構造を含まない、メタペーパーだけの複製を生成して返す。
 複製結果はファイルに結びついていない。
 
 従属構造とは、basic-page, cont-doc, profile-contentである。
 MPCProfileにセットした属性は複製される。
 OpenMP前には成功せず、リターン値はNULL、phres に MP_E_ACCESSDENIED を返す。
 
 ・リターン値
 MPCProfile*		複製したメタペーパーオブジェクト
 
 ・セキュリティ
 転記禁止の場合、MP_E_ACCESSDENIEDエラーになる。
 
 §GetStorageVersion
 ・パラメータ
 
 ・説明
 DWファイルのバージョンを問い合わせる。
 各ファイルバージョンと数値との関係は[§4.2.1.3 DWのファイルバージョンの定義]を参照。
 
 V4.0で生成された文書データは 7 を返す。
 
 V3.0、V3.1で生成されたデータファイルをロードした場合、
 ファイルに保存するまでは 6 が返される。
 一度DWファイルに保存すると、次回のアクセスから 7 が返される。
 
 V2.0で生成されたデータファイルをロードした場合、
 ファイルに保存するまでは 5 が返される。
 一度DWファイルに保存すると、次回のアクセスから 7 が返される。
 
 V1.0で生成されたデータファイルをロードした場合、
 ファイルに保存するまでは 4 が返される。
 一度DWファイルに保存すると、次回のアクセスから 7 が返される。
 
 8以上は、今後の拡張のために予約されている。
 3以下は、正規のＤＷ文書ファイルでない。
 
 OpenMP前でも成功する。
 
 ・リターン値
 バージョン番号
 
 §GetFilePath
 ・パラメータ
 size	pathに用意した領域のサイズ（単位　バイト）
 path	ファイルパスを受け取る領域
 
 ・説明
 このオブジェクトが結びついているファイルパスをpathにセットして返す。
 ファイルパスは、MPCSession::OpenFile、MPCSession::SaveAs、MPCSession::SaveToPathで指定されたパス文字列である。
 CreateFileMPCObject()、SaveToFileObject()で指定されたファイルオブジェクトに結びついている場合、そのファイルオブジェクトのMP_File::GetFilePathがパスを返した場合はそのパスをセットする。MP_File::GetFilePathがNULLを返した場合はpathに値をセットせずMP_E_INVALIDARGを返す。
 
 OpenFileでMP_COPYREADを指定し、ファイルを複製オープンした場合であっても、OpenFileで指定されたパス文字列をpathにセットする。
 OpenMP前でも成功する。
 
 ・リターン値
 MP_NOERROR					取得成功
 MP_E_INSUFFICIENT_BUFFER	ファイルパスを受け取る領域のサイズが足りない。
 MP_E_INVALIDARG				このストレージオブジェクトはファイルに結びついていない、またはファイルオブジェクトのGetFilePathがNULLを返した。
 
 MP_NOERROR以外のリターン値の場合、pathに値をセットしない。
 
 
 // V4 追加分
 §AddAuthentication
 ・パラメータ
 MP_Permission perm		パーミッション情報
 
 ・説明
 perm で指定されたパーミッションに対する追加認証を行う。
 この関数が呼ばれると、セキュリティモジュールが認証ダイアログを出す。
 フルアクセスモードになりたい場合は AddAuthentication(MP_PERM_FULL) とすればよい。
 既に認証済みのパーミッションが指定された場合は、内部では何もせずに成功を返す。
 一旦認証したパーミッションは、CloseFile() するまで有効である。
 OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR (==0)			成功
 MP_S_PROCESS_CANCELED		キャンセルされた
 MP_E_AUTH_FAILED			認証に失敗した。必要であれば Viewer 等でエラーメッセージを表示する。
 MP_E_AUTH_FAILED_NOMESSAGE	認証に失敗したが、セキュリティモジュールでエラー表示したので Viewer 等ではメッセージ表示しないでほしい。
 MP_E_INVALID_CALL			認証が成功する前に呼ばれた
 
 
 §EditSecurity
 ・パラメータ
 なし
 
 ・説明
 文書にセキュリティの設定を行う。
 この関数が呼ばれると、セキュリティモジュールが設定ダイアログを出す。
 保護されている文書に対して、フルアクセスモードでない場合に呼ばれるとエラーを返す。
 OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR (==0)			成功
 MP_S_PROCESS_CANCELED		キャンセルされた
 MP_S_PROTECTION_REMOVED		解除された
 MP_E_INVALID_CALL			認証が成功する前に呼ばれた
 
 
 §GetPermission
 ・パラメータ
 HRESULT* phres	結果コード
 
 ・説明
 文書に現在設定されているパーミッション情報を返す。
 セキュリティの設定を変更して、ファイルに保存する前に呼ばれた場合は、
 ファイルの状態ではなく変更後の状態を返す。
 保護されていない場合は全て可能(全てのビットが1)を返す。
 hres が指定されていた場合は、
 MP_NOERROR					保護されていない
 MP_S_PROTECTED_BY_PSWD		パスワードによって保護されている
 MP_S_PROTECTED_BY_DDSA		DDSAによって保護されている
 負の値						エラー
 を格納する。
 OpenMP前でも成功する。
 
 OpenMP(認証)前と認証後にパーミッションが変わるセキュリティがある。
 このようなセキュリティにおいてOpenMP前にこの関数を呼ぶ場合、
 認証後に許される可能性のあるパーミッションのビット(MP_PERM_*)は1が返る。
 認証後に許されない可能性のあるパーミッションは、MP_CAN_CANCEL_PERM_*のビットに1が返る
 MP_PERM_* が 1、MP_CAN_CANCEL_PERM_* が 0 : 認証後に有り
 MP_PERM_* が 1、MP_CAN_CANCEL_PERM_* が 1 : 認証後に有り/無しの可能性
 MP_PERM_* が 0                            : 認証後に無し
 
 
 ・リターン値
 MP_Permission	文書に設定されているパーミッション情報
 エラーの場合はパーミッションなし(全てのビットが0)を返す
 
 
 §GetAuthenticatedPermission
 ・パラメータ
 HRESULT* phres	結果コード
 
 ・説明
 現在認証されているパーミッション情報を返す。
 hres が指定されていた場合は GetPermission() と同じ値を格納する。
 OpenMP前には、リターン値に0(全パーミッション無し)、phres に MP_E_ACCESSDENIED を返す。
 
 ・リターン値
 MP_Permission	現在認証されているパーミッション情報
 エラーの場合はパーミッションなし(全てのビットが0)を返す
 
 §ShowSecurityInfo
 ・パラメータ
 なし
 
 ・説明
 Desk や Viewer の「文書プロパティ」で、「セキュリティ」タブの「追加情報」を
 表示する際に呼ばれる。
 OpenMP前でも成功する。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR		成功
 負の値はエラー
 
 §CheckData
 ・パラメータ
 MP_Integer* nth_page		一番最初にエラーが見つかった BasicPage の通し番号
 MP_Integer* nth_org			一番最初にエラーが見つかったオリジナルデータの通し番号
 MP_Integer* others			その他の個所でエラーが見つかった
 MPC_AdvCancelInfo* info		キャンセル用構造体
 
 ・説明
 データチェック用関数。
 この関数が呼ばれると、ストレージが文書ファイルをチェックし、
 BasicPage でエラーがあった場合はその通し番号を nth_page に、
 オリジナルデータでエラーがあった場合はその通し番号を nth_org に、
 その他の個所でエラーが見つかった場合は others に 1 が格納される。
 通し番号は 0 基数で、バインダ文書の場合も同様である。
 エラーがない場合は、各変数には -1 が格納され、MP_NOERROR を返す。
 時間がかかる処理なので、info による途中経過表示＆キャンセルができる。
 キャンセルのやり方は MPCMediaAdv::OnPrint() などを参照すること。
 
 OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
 スクラッチの状態では成功せず、MP_E_INVALID_CALL を返す。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR				エラーはなかった
 MP_E_BAD_CHECKSUM		チェックサム不整合エラーがあった
 MP_E_BAD_FORMAT_ODOA	改行コード関係のエラーがあった
 
 
 (V4.1新規追加)
 §CreateSecurityWithTemplate
 ・パラメータ
 MPC_SecurityTemplate* pTemplate		セキュリティテンプレート
 
 ・説明
 テンプレートにより、文書に新規にセキュリティの設定を行う。
 ダイアログ等のUIは出ない。
 保護されている文書に対して呼ばれるとエラーを返す。
 OpenMP前には成功せず、MP_E_ACCESSDENIED を返す。
 パスワードの場合は、全ての操作が許可されていて、
 かつ開く・フルアクセスパスワードが空であった場合は、
 保護する意味がないのでMP_E_INVALIDARGエラーを返す。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR (==0)			成功
 MP_E_INVALIDARG				テンプレートが不正
 MP_E_ACCESSDENIED			認証が成功する前に呼ばれた
 
 (V5 新規追加)
 
 §GetNumberOfSignatures
 
 ・説明
 文書に付いている署名の数を返す。
 内部文書のProfileに対して呼ぶときは、その内部文書に付いている書名の数を返す。
 
 ・リターン値
 0以上	成功 文書に付いている署名の数
 負数	エラー
 
 §GetNthSignatureObject
 ・パラメータ
 MP_Integer nth		取り出す署名オブジェクトのインデックス
 
 ・説明
 その文書にnth番目(0基数)に付けられた署名の、文書上のオブジェクトを返す。
 nthの定義は、「4.2.6 nth に関する共通定義」参照
 ただし順序は署名が付けられた順序となる。
 
 署名オブジェクトがロードできない場合はNULLを返す。
 
 ・リターン値
 MPCObject*		取得した署名オブジェクト
 
 
 §GetSaveStorageVersion
 ・パラメータ
 
 ・説明
 保存後のDWファイルのバージョンを問い合わせる。
 V5.0ででは 7 (V4互換) または 8 (V5) を返す。
 
 9以上は、今後の拡張のために予約されている。
 3以下は、正規のＤＷ文書ファイルでない。
 
 OpenMP前でも成功する。
 スクラッチの状態では成功せず、MP_E_INVALID_CALL を返す。
 
 ・リターン値
 バージョン番号
 
 §GetTrailerAttribute
 ・パラメータ
 unsigned long iTag
 MP_AValue* rtn_avalue
 
 ・説明
 ファイルから開いている文書のトレーラ属性を取得する。
 取得したいトレーラ属性のタグIDをiTagで指定し、rtn_avalueに結果を得る。
 rtn_avalueの仕様はGetAttribute()に順ずる。
 OpenMP()成功前(⊃セキュリティの認証成功前)でも実行可能。
 ファイルから開かれていない場合は失敗する。
 
 (6.0.4追加)
 
 §ReleaseSecurity
 ・パラメータ
 
 ・説明
 セキュリティを解除する。
 すでにフルアクセスの認証が成功している必要がある。
 保護されていなかったらMP_S_PROCESS_CANCELEDが返る。
 
 ・リターン値
 HRESULT	結果コード
 MP_NOERROR (==0)			成功(保護が解除された)
 MP_S_PROCESS_CANCELED		もともと保護されていなかった
 MP_E_INVALID_CALL			フルアクセスになっていない
 
 §AddAuthenticationEx
 ・パラメータ
 MP_AuthInfo* auth  追加したいパーミッションと認証時の対話操作モード
 
 ・説明
 AddAuthenticationに、認証時の対話操作モードの明示的指定を追加したもの。
 APIからフルアクセスになるときなどに使用する。
 対話操作モード以外の動作はAddAuthenticationと同じ。
 */


/*
 §5.3	BasicPage オブジェクト
 
 ドキュメントデータモデル層のページを表現するコンポーネントオブジェクト。
 Content操作、ページ描画、ページ回転を提供する。
 
 §5.3.1 BasicPage オブジェクトの生成と破棄
 
 通常、BasicPageはDWファイルのルートオブジェクトにならない。
 
 §5.3.1.1 生成
 MPCSession::CreateScratchMPCObject()
 で生成される。
 
 親の
 MPCObject::UnlinkChild()
 MPCObject::GetNthChild()
 でロードされる。
 
 §5.3.1.2 破棄
 スクラッチなルートの場合、自身のDestroy()で破棄する。
 ルート以外の場合、親のMPCObject::UnlinkChild()でスクラッチなルートにしてから破棄する。
 
 §オブジェクトID
 */
MPC_EXTERN_GUID(CLSID_BASICPAGE, 0x1301);

/*
 §5.3.2 BasciPageのインタフェース
 
 BasicPage オブジェクトは、共通インタフェースで記載した
 IID_MPCInterface
 IID_MPCObject
 IID_MPCMedia
 IID_MPCRegisterForGUI
 IID_MPCHintFromGUI
 の各インタフェースを提供する。
 
 また、BasicPage オブジェクトは、IID_MPCContentに対してMP_E_NOINTERFACEを返す。
 DWViewerはIID_MPCContentの応答でBasicPageかどうかを判別する。（Ｖ１仕様）
 */

/*
 §5.3.3 MPCMediaAdv インタフェース
 
 中断可能なページ描画機能を提供する。
 
 §5.3.3.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MPCMediaAdv, 0x1319);

/*
 §5.3.3.2 メソッド一覧
 */
typedef	MP_Integer	MPC_AdvDrawHandle;

mpinterface MPCMediaAdv
{
#ifndef SFXVW
    STDMETHOD(OnDraw)(MP_Canvas* canvas, MPC_AdvDrawHandle* handle = NULL) PURE;
    STDMETHOD(OnPrint)(MP_Canvas* canvas, MPC_AdvCancelInfo* info = NULL) PURE;
    STDMETHOD(AddErasingBkgndRect)(MP_Rect rect) PURE;
#endif //SFXVW
};

/*
 §5.3.3.3 各メソッドの定義
 
 §OnDraw
 ・パラメータ
 canvas		MPCMedia ::OnDrawの引数と同じ
 handle		MP_AdvDrawHandle型ハンドルのポインタ。
 
 ・説明
 本I/Fは表示処理をアプリケーション側で分割制御するためのものである。
 分割単位毎の表示処理が終了した時点で、この関数はアプリケーションに制御を返す。
 
 初回（またははじめから表示し直す場合）は、*handleに0を指定する。
 2回目以降は前回の呼び出しで返ってきた*handleを指定する。
 handleがNULLの場合は、MPCMedia::OnDraw()と同様に1回で全てを描画する。
 
 分割対象となるのは、BodyContentのPDのみであり、他のPDは分割されない。
 したがって、BodyContentの表示処理が終了してからその他のPDの表示処理が終了するまでの間は、アプリケーションには制御が返らない。
 
 表示を中断したい場合の後処理は不要である。
 
 ・リターン値
 MP_S_DRAW_FINISHED(==MP_NOERROR==0)
 OnDraw()処理終了を示す。
 BMP系PDの場合は、表示に必要な領域の表示イメージが出来上がったことを示す。
 MF系PDの場合は、表示キャッシュがページ全体分作成終了したことを示す。
 
 MP_S_DRAW_SUSPENDED(==1)
 表示イメージ作成が未完であることを示す。
 表示処理を継続させたい場合は、再度MPCMediaAdv::OnDraw()を呼び出す。
 
 その他(<0)
 エラー
 
 ・セキュリティ
 転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。
 印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
 
 §OnPrint
 ・パラメータ
 canvas		MPCMedia ::OnPrintと同様
 info		MP_AdvCancelInfo型構造体のポインタ
 印刷中断およびステータス情報取得用のコールバック関数を指定する
 info.callbackにはアプリケーションが実装したコールバック関数のポインタを指定する。
 info.userDataは各アプリケーションが自由に設定、使用できる。
 
 ・説明
 中断可能なOnPrint描画
 コアはMPCMediaAdv::OnPrint実行中に指定されたコールバック関数を呼び出す。
 
 アプリケーションはコールバック関数のリターン値として、
 MP_PRINT_CONTINUE
 または
 MP_PRINT_CACNCEL
 のいずれかを指定すること。
 
 コールバック関数のリターン値が
 　MP_PRINT_CONTINUEの場合、コアは描画処理を継続する。
 　MP_PRINT_CANCELの場合は描画処理MPCMediaAdv::OnPrintを中断し制御をアプリケーションに返す。
 
 コールバック関数の引数percentは、 BodyContentの印刷処理の進捗ステータスである。BodyContent以外の処理は考慮されていない。したがって進捗ステータスのあくまで目安であり、percent=100%になってもOnPrint終了を示しているわけではないので注意する事。
 
 コールバック関数の中で別の描画処理を発行してはならない。
 異なるスレッドから同時に別の描画処理を発行してはならない。
 
 引数infoがNULL、またはinfo->callbackがNULLの場合は、コアはコールバック関数を呼び出さない。したがってこの場合はOnPrintを中断することはできない。
 
 ・リターン値
 MP_S_PRINT_FINISHED(==MP_NOERROR==0)
 OnPrint()処理終了を示す。
 
 MP_S_PRINT_CANCELED(==1)
 OnPrint()が中断されたことを示す。
 
 その他(<0)
 エラー
 
 ・セキュリティ
 転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。
 印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
 
 §AddErasingBkgndRect
 ・パラメータ
 rect		MP_Rect型
 
 ・説明
 本I/Fは逐次表示寺中にスクロール等の発生により再描画が必要になった場合、それをコアに通知するためのものである。
 引数rectは、アプリケーションのビューの左上を原点とし、単位0.01mmの座標情報でなければならない。
 
 ・リターン値
 MP_NOERROR		成功
 その他(<0)		エラー
 
 */

/*
 §5.4	配列オブジェクト
 */

/*
 §5.4.1 配列オブジェクトの生成と破棄
 
 §5.4.1.1 生成
 
 §MPCreateMPPtrArray
 */

DLLBINDFUNC_(MP_PtrArray*, MPCreateMPPtrArray)(MPCSession* session, HRESULT* phres=NULL);
/*
 ・説明
 配列オブジェクトを生成し、MP_PtrArrayインタフェースのアドレスを返す。
 */

/*
 
 §5.4.1.2 破棄
 MP_PtrArray自身のDestroy()で破棄する。
 */

/*
 §5.4.2 MP_PtrArray インタフェース
 
 §5.4.2.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MP_PtrArray, 0x1307);

/*
 §5.4.2.2 メソッド一覧
 */

typedef void* MP_ELEMENT;

mpinterface MP_PtrArray : public MPCInterface
{
    STDMETHOD(GetSize)() PURE;
    STDMETHOD(GetUpperBound)() PURE;
    STDMETHOD(SetSize)(MP_Integer nNewSize, MP_Integer nGrowBy = -1) PURE;
    
    STDMETHOD(FreeExtra)() PURE;
    STDMETHOD(RemoveAll)() PURE;
    
    STDMETHOD_(MP_ELEMENT, GetAt)(MP_Integer nIndex, HRESULT* phres = NULL) PURE;
    STDMETHOD(SetAt)(MP_Integer nIndex, MP_ELEMENT newElement) PURE;
    
    STDMETHOD(SetAtGrow)(MP_Integer nIndex, MP_ELEMENT newElement) PURE;
    STDMETHOD(Add)(MP_ELEMENT newElement) PURE;
    
    STDMETHOD(InsertAt)(MP_Integer nIndex, MP_ELEMENT newElement, MP_Integer nCount = 1) PURE;
    STDMETHOD(RemoveAt)(MP_Integer nIndex, MP_Integer nCount = 1) PURE;
    STDMETHOD(InsertAt)(MP_Integer nStartIndex, MP_PtrArray* pNewArray) PURE;
};

/*
 §5.4.2.3 各メソッドの定義
 
 （開発メモ：　特に記載がない項は、MFC4.2 の CPtrArray の仕様に準ずる。）
 
 §GetSize
 ・パラメータ
 
 ・説明
 
 ・リターン値
 
 §GetUpperBound
 ・パラメータ
 
 ・説明
 
 ・リターン値
 
 §SetSize
 ・パラメータ
 MP_Integer nNewSize
 MP_Integer nGrowBy
 
 ・説明
 
 ・リターン値
 
 §FreeExtra
 ・パラメータ
 
 ・説明
 
 ・リターン値
 
 §RemoveAll
 ・パラメータ
 
 ・説明
 
 ・リターン値
 
 
 §GetAt
 ・パラメータ
 MP_Integer nIndex
 HRESULT* phres
 
 ・説明
 
 ・リターン値
 MP_ELEMENT
 
 §SetAt
 ・パラメータ
 MP_Integer nIndex
 MP_ELEMENT newElement
 
 ・説明
 
 ・リターン値
 
 §SetAtGrow
 ・パラメータ
 MP_Integer nIndex
 MP_ELEMENT newElement
 
 ・説明
 
 ・リターン値
 
 §Add
 ・パラメータ
 MP_ELEMENT newElement
 ・説明
 
 ・リターン値
 
 §InsertAt
 ・パラメータ
 MP_Integer nIndex
 MP_ELEMENT newElement
 MP_Integer nCount
 
 ・説明
 
 ・リターン値
 
 §RemoveAt
 ・パラメータ
 MP_Integer nIndex
 MP_Integer nCount
 
 ・説明
 
 ・リターン値
 
 §InsertAt
 ・パラメータ
 MP_Integer nStartIndex
 MP_PtrArray* pNewArray
 
 ・説明
 
 ・リターン値
 
 */

/*
 §5.5	ファイル オブジェクト
 */
/*
 §5.5.1 ファイル オブジェクトの生成と破棄
 
 サイズが2Gbytesより小さい一般ファイルのアクセスを制御するオブジェクト
 
 §5.5.1.1 生成
 
 SPI_MP_File::CreateMPFile()	で生成する
 SPI_MP_File::OpenMPFile()	で生成する
 
 §5.5.1.2 破棄
 MP_File 自身のDestroy()で破棄する。
 MP_File 自身のClose(1)で破棄する。
 */

/*
 §5.5.2 MP_File インタフェース
 
 §5.5.2.1 インタフェースID
 */
MPC_EXTERN_GUID(IID_MP_File, 0x1316);

/*
 §5.5.2.2 メソッド一覧
 */
mpinterface MP_File : public MPCInterface {
    STDMETHOD(Seek)(MP_Integer seekpos, MP_SeekMethod seekmode = MP_SEEK_BEGIN) PURE;
    STDMETHOD(Read)(void* rbuf, MP_Integer rsize) PURE;
    STDMETHOD(Write)(const void* wbuf, MP_Integer wsize) PURE;
    STDMETHOD(Close)(MP_Integer bDestroy=1) PURE;
    STDMETHOD(Size)() PURE;
    STDMETHOD_(const MP_Path*, GetFilePath)() PURE;
    STDMETHOD_(MP_OpenMode, GetOpenMode)() PURE;
    STDMETHOD(SetFileSize)(MP_Integer size) PURE;
    STDMETHOD(CheckValidity)() PURE;
    STDMETHOD(GetFilePathW)(MP_String &path) PURE;
};

/*
 §5.5.2.3 各メソッドの定義
 
 §Destroy
 ・説明
 通常のDestroyの処理と同時に、ファイルがオープンしていたらクローズも合わせて実行する。
 
 §Seek
 ・パラメータ
 MP_Integer seekpos
 MP_SeekMethod seekmode
 
 ・説明
 オープンされたファイル内の、 現在のファイル位置を変更する。
 
 seekmodeの値に応じて
 
 MP_SEEK_BEGIN	ファイルの先頭からseekposバイト目にシークする。
 MP_SEEK_CURRENT	現在のファイル位置からseekposバイト目にシークする。
 MP_SEEK_END		ファイルの終端からseekposバイト目にシークする。
 
 関数が正常に終了した場合は、 新しいファイル 位置を返す。
 この関数は、2Gbytesまでのサイズのファイルしか操作できない。
 
 その他の詳細動作は、Win32 API の SetFilePointer() の仕様に準ずる。
 
 ・リターンコード
 成功した場合、新しいファイル位置を返す。
 エラーが発生した場合は、HRESULT型のエラーコード を返す。
 
 §Read
 ・パラメータ
 void* rbuf		ファイルから読み取ったデータを受け取るバッファを指すポインタ
 MP_Integer rsize	ファイルから読み取るバイト数
 
 ・説明
 シークポインタで示された位置を始点として、 ファイルからデータを読み取る。
 関数が成功した場合は、rsizeで指定されたバイト数のデータを読み取る。ただし、読み取り途中でファイル末尾を超えた場合は、ファイル末尾までのデータを読み取る。
 オープンモードOM_MODEST_READで開かれている場合、開いた時点とRead時で
 ファイルのサイズまたは更新日時が変わっている場合はMP_E_FILE_NOT_FOUNDエラーとなる。
 
 この関数は、2Gbytesまでのサイズのファイルしか操作できない。
 
 その他の詳細動作は、Win32 API の ReadFile() の仕様に準ずる。
 
 ・リターンコード
 成功した場合、実際に読み込んだバイト数を返す。
 エラーが発生した場合は、HRESULT型のエラーコード を返す。
 
 §Write
 ・パラメータ
 const void* wbuf	ファイルに書き込むデータを含むバッファを指すポインタ
 MP_Integer wsize	ファイルに書き込むバイト数
 
 ・説明
 シークポインタで示された位置を始点として、 ファイルにデータを書き込む。
 関数が成功した場合は、wsizeで指定されたバイト数のデータが書き込まれる。
 
 この関数は、2Gbytesまでのサイズのファイルしか操作できない。
 
 その他の詳細動作は、Win32 API の WriteFile() の仕様に準ずる。
 
 ・リターンコード
 成功した場合、出力したバイト数を返す。
 エラーが発生した場合は、HRESULT型のエラーコード を返す。
 
 §Close
 ・パラメータ
 MP_Integer bDestroy		0: 同時にオブジェクトを解放しない。1:解放する。
 
 ・説明
 ファイルハンドルを閉じる。
 Closeは必ず成功する。
 Close()発行後に可能な操作は、Destroy()とGetFilePath()のみである。
 通常は、bDestroy=1（省略値）を指定し、同時にオブジェクトを解放する。
 
 ・リターンコード
 必ずMP_NOERRORを返す。
 
 
 §Size
 ・パラメータ
 
 ・説明
 ファイルのサイズをバイト単位で取得します。
 この関数は、2Gbytesまでのサイズのファイルしか操作できない。
 
 ・リターンコード
 成功した場合、ファイルのサイズを返す。
 エラーが発生した場合は、HRESULT型のエラーコード を返す。
 
 §GetFilePath
 ・パラメータ
 
 ・説明
 ファイルパスを返す。
 CreateMPFile、OpenMPFile、OpenPartialFileで指定されたファイルパスを返す。
 
 ・リターンコード
 const MP_Path*
 ファイルパスが取得できない場合は、NULLを返す。
 
 §GetOpenMode
 ・パラメータ
 
 ・説明
 MP_Fileオブジェクト生成時のオープンしたモードを返す。
 
 ・リターンコード
 MP_OpenMode のいずれかの値を返す。
 
 
 §SetFileSize
 ・パラメータ
 size	新しく設定したいファイルサイズ
 
 ・説明
 MP_Fileで扱っているファイルのサイズを size に変更する。
 この関数は、 ファイルのサイズの切り捨てや拡張に使うことができる。
 ファイルを拡張した場合、 拡張した部分の内容は、 未定義になる。
 
 ・リターンコード
 成功した場合は、MP_NOERRORを返す。
 エラーが発生した場合は、HRESULT型のエラーコード を返す。
 
 
 §CheckValidity
 ・パラメータ
 
 ・説明
 MP_Fileが有効な状態か確認する。
 オープンモードOM_MODEST_READで開かれている場合、開いた時点とRead時で
 ファイルのサイズまたは更新日時が変わっている場合はMP_E_FILE_NOT_FOUNDエラーとなる。
 
 ・リターンコード
 成功した場合、MP_NOERRORを返す。
 MP_Fileが有効な状態で無い場合、エラーが発生した場合は、HRESULT型のエラーコード を返す。
 */

/*
 §5.6	代理ペン　オブジェクト
 
 紙片や付箋に貼られたコンテントを代替するオブジェクトである。
 */

/*
 §5.6.1 代理ペン オブジェクトの生成と破棄
 
 §5.6.1.1 生成
 
 利用者がBasicPage及び付箋の MPCObject::GetNthChild()をコールした時
 本来のオブジェクトがロードできない場合に代理のコンテントを生成して返す。
 代理ペンすら生成できない異常環境の場合はNULLを返す事もある。
 代理ペンの生成は紙片及び付箋に貼られたアノテーションに限る。
 
 注：代理ペンを返さない例
 
 1.MPCSession::OpenFile()でファイルのルートオブジェクトが存在しない場合
 2.MPCSession::CreateScratchMPCObject()で指定オブジェクトが存在しない場合
 3.紙片の UnlinkChild() をコールした時、Unlinkするアノテーションが存在しない場合
 
 はNULLを返しエラー復帰する。
 
 
 §5.6.1.2 破棄
 共通インタフェース定義 MPCObejctのDestroy（§4.3.3.3）の動作に準ずる。
 
 
 §5.6.1.3　オブジェクトID
 */
MPC_EXTERN_GUID(CLSID_REPRESENTATIVE_PEN, 0x802A);

/*
 §5.6.2 代理ペンのインタフェース
 
 代理ペンオブジェクトは、
 MPCInterface
 MPCObject
 MPCMedia
 MPCContent
 IPersistMPCObject
 IContent
 のインタフェースを提供する。
 
 以下に代理ペン独特の動作を定義する。
 
 ・MPCMedia インタフェース
 
 GetInterface()		共通インタフェース定義（§4.3.3 参照）に準ずる
 Destroy()			共通インタフェース定義（§4.3.3 参照）に準ずる
 GetSession()		共通インタフェース定義（§4.3.3 参照）に準ずる
 GetClassID()		代理ペンのオブジェクトID( CLSID_REPRESENTATIVE_PEN )を返す
 GetIFID()			IID_MPCMediaを返す
 Duplicate()			複製可能（メモリ不足等のエラーが発生したらエラーを返す）
 DoProcedure()		固有I/Fで本来のオブジェクトIDを返す機能を提供する。
 SetAttribute()		エラーを返す
 SetAttributeF()		エラーを返す
 GetAttribute()		IStgObjectで定義した任意属性の取得が可能
 GetAttributeF()		IStgObjectで定義した任意属性の取得が可能
 EnumAttribute()		IStgObjectで定義した動作が可能
 CanLinkChild()		MP_E_UNEXPECTEDを返す
 LinkChild()			MP_E_UNEXPECTEDを返す
 UnlinkChild()		NULLを返す。（エラーコード＝MP_E_UNEXPECTED）
 GetNumberOfChildren()	MP_E_UNEXPECTEDを返す
 GetNthChild()		NULLを返す。（エラーコード＝MP_E_UNEXPECTED）
 ChangeChildOrder()	MP_E_UNEXPECTEDを返す
 GetChildPosition()	MP_E_UNEXPECTEDを返す
 GetParent()			共通インタフェース定義（§4.3.3 参照）に準ずる
 GetMP()				共通インタフェース定義（§4.3.3 参照）に準ずる
 SetPartAttribute()	MP_E_UNEXPECTEDを返す
 GetPartAttribute()	MP_E_UNEXPECTEDを返す
 EnumPartAttribute()	MP_E_UNEXPECTEDを返す
 OnDraw()			格納されたPDで描画する(PDなければ×印）
 OnPrint()			格納されたPDで描画する(PDなければ×印）
 CanRotate()			エラーを返す
 Rotate()			エラーを返す
 
 
 ・IContent インタフェース
 
 PreAttach()		拒否（= MP_S_OK 以外)を返す
 PostAttach()	動作未定義
 PreDetach()		拒否（= MP_S_OK 以外)を返す
 PostDetach()	動作未定義
 
 */


/*
 §5.7 バインダオブジェクト
 
 バインダファイルのルートとなり、DW文書を束ねるオブジェクトである。
 
 §5.7.1 バインダ オブジェクトの生成と破棄
 
 §5.7.1.1 生成
 
 MPCSession::CreateScratchMPCObject()
 MPCSession::OpenFile()
 のいずれかで生成される。
 
 何らかのオブジェクトに従属した場合、
 親のMPCObject::UnlinkChild()
 MPCObject::GetNthChild()
 でロードされる。
 
 §5.7.1.2 破棄
 
 スクラッチなルートの場合、自身のDestroy()で破棄する。
 DWファイルのルートの場合、MPCSession::CloseFile()で破棄する。
 ルート以外の場合、親のMPCObject::UnlinkChild()でスクラッチなルートにしてから破棄する。
 
 §5.7.1.3　オブジェクトID
 */

MPC_EXTERN_GUID(CLSID_BINDER, 0xC014);

/*
 §5.7.2 MPCPageRoot インタフェース
 
 バインダ内の各内部DW文書のBasicPageを管理するインタフェース
 各内部DW文書の全BasicPageに対して、あたかもフラットな１つの文書のように参照できる。
 
 §5.7.2.1 インタフェースID
 IID_MPCPageRoot
 
 §5.7.2.2 メソッド一覧
 mpinterface MPCObjectと同じ
 
 §5.7.2.3 各メソッドの定義
 
 §GetInterface
 （MP_Interface 参照）
 §Destroy
 （MP_Interface 参照）
 §GetSession
 このオブジェクトが属しているセッションを返す。
 §GetClassID
 CLSID_BINDER を返す
 §GetIFID
 IID_MPCPageRoot を返す
 §Duplicate
 エラー
 §DoProcedure
 (MPCObject参照)
 §SetAttribute
 (MPCObject参照)
 §SetAttributeF
 (MPCObject参照)
 §GetAttribute
 (MPCObject参照)
 §GetAttributeF
 (MPCObject参照)
 §EnumAttribute
 (MPCObject参照)
 §CanLinkChild
 MP_S_FALSE を返す
 §LinkChild
 エラー
 §UnlinkChild
 エラー
 §GetNumberOfChildren
 成功した場合、バインダ内の全内部DW文書のBasicPage数の合計を返す
 §GetNthChild
 nth番目のBasicPageを返す。nthはバインダ内の全内部DW文書の通し番号。
 例えば、バインダに、2ページ、3ページ、1ページの３つの内部DW文書がある場合、
 nth == 0 ならば最初の文書の1ページ目
 nth == 3 ならば2番目の文書の2ページ目
 nth == 5 ならば3番目の文書の1ページ目
 のBasicPageが取得できる。
 §ChangeChildOrder
 エラー
 §GetChildPosition
 そのBasicPageの位置を返す。バインダ内の全内部DW文書の通し番号。
 §GetParent
 親オブジェクトを返す。V4ではNULL
 §GetMP
 NULLを返す。
 §SetPartAttribute
 エラー
 §GetPartAttribute
 エラー
 §EnumPartAttribute
 エラー
 
 §5.7.3 MPCContDocRoot インタフェース
 
 バインダ内の各内部DW文書のContDocを管理するインタフェース
 各内部DW文書の全ContDocオブジェクトに対して、あたかもフラットな１つの文書のように参照できる。
 
 §5.7.3.1 インタフェースID
 IID_MPCContDocRoot
 
 §5.7.3.2 メソッド一覧
 mpinterface MPCObjectと同じ
 
 §5.7.3.3 各メソッドの定義
 
 §GetIFID
 IID_MPCContDocRoot を返す
 
 §その他のメソッド
 バインダ オブジェクトのMPCPageRootインターフェースのBasicPageをContDocに読み替える。
 
 §5.7.4 MPCProfile インタフェース
 
 このインタフェースの子として、content オブジェクトをリンクできる。
 
 §5.7.4.1 インタフェースID
 IID_MPCProfile
 
 §5.7.4.2 メソッド一覧
 mpinterface MPCObjectと同じ
 
 §5.7.4.3 各メソッドの定義
 
 MetaPaperオブジェクトのMPCProfileインタフェースに同じ
 
 */

/*
 §5.7.5 MPCDocRoot インタフェース
 
 バインダ内のDW文書を操作するためのインタフェース
 このインタフェースの子として、MetaPaperオブジェクトをリンクできる。
 
 §5.7.5.1 インタフェースID
 */

MPC_EXTERN_GUID(IID_MPCDocRoot, 0x1401);

/*
 §5.7.5.2 メソッド一覧
 mpinterface MPCObjectと同じ
 
 §5.7.5.3 各メソッドの定義
 
 §GetInterface
 （MP_Interface 参照）
 
 §Destroy
 （MP_Interface 参照）
 
 §GetSession
 このオブジェクトが属しているセッションを返す。
 
 §GetClassID
 CLSID_BINDER を返す
 
 §GetIFID
 IID_MPCDocRoot を返す
 
 §Duplicate
 バインダ以下を複製して返す
 
 §DoProcedure
 (MPCObject参照)
 
 §SetAttribute
 バインダオブジェクトに対して SetAttributeする
 SetAttributeの説明はMPCObject参照
 
 §SetAttributeF
 バインダオブジェクトに対して SetAttributeFする
 SetAttributeFの説明はMPCObject参照
 
 §GetAttribute
 バインダオブジェクトに対して GetAttributeする
 GetAttributeの説明はMPCObject参照
 
 §GetAttributeF
 バインダオブジェクトに対して GetAttributeFする
 SetAttributeの説明はMPCObject参照
 
 §EnumAttribute
 バインダオブジェクトに対して EnumAttributeする
 EnumAttributeの説明はMPCObject参照
 
 §CanLinkChild
 バインダの子オブジェクトとしてリンク可能かどうかを返す
 
 §LinkChild
 （DW文書を)nth番目の子オブジェクトとしてリンクする
 
 §UnlinkChild
 nth番目の子オブジェクト(DW文書)を切り離す
 
 §GetNumberOfChildren
 子オブジェクトの数(バインダ内のDW文書数)を返す
 
 §GetNthChild
 nth番目の子オブジェクト(DW文書)を返す
 
 §ChangeChildOrder
 src_nth番目の子オブジェクト(DW文書)をdst_nth番目に変更する
 
 §GetChildPosition
 そのDW文書の位置を返す。
 
 §GetParent
 親オブジェクトを返す。V4ではNULL
 
 §GetMP
 NULLを返す。
 
 §SetPartAttribute
 nth番目の子オブジェクト(DW文書)に対応するパート属性を設定する
 束ねる前のファイル名、ファイル属性などを想定
 
 §GetPartAttribute
 nth番目の子オブジェクト(DW文書)に対応するパート属性を返す
 
 §EnumPartAttribute
 nth番目の子オブジェクトに対応するパート属性の数え上げ
 
 */


/*
 §5.8 MPCSignature インタフェース
 
 電子署名機能を操作するためのインタフェース
 
 §5.8.1 インタフェースID
 */

MPC_EXTERN_GUID(IID_MPCSignature, 0x132B);

/*
 §5.8.2 メソッド一覧
 */
mpinterface MPCSignature : public MPCInterface {
    STDMETHOD(AttachModule)() PURE;
    STDMETHOD(FillContent)(MP_Integer iModuleID, void* pSignatureHandle) PURE;
    STDMETHOD(ShowProperty)() PURE;
    STDMETHOD(UpdateStatus)(MP_Integer *pbAppearanceChanged) PURE;
    STDMETHOD(DrawOnDocument)(MP_Canvas* canvas, MP_Integer bShowStatus) PURE;
    STDMETHOD(GetModuleID)() PURE;
    STDMETHOD(GetModuleName)(char* pszName = NULL) PURE;
    STDMETHOD_(void*, GetModuleIcon)() PURE;
    STDMETHOD_(long, GetSignedTime)() PURE;
    STDMETHOD(GetSignatureName)(char* pszName = NULL) PURE;
    STDMETHOD(GetStatusLabel)(char* pszLabel = NULL ) PURE;
    STDMETHOD(GetTooltipText)(char* pszText = NULL ) PURE;
    STDMETHOD(GetVerificationDataSize)() PURE;
    STDMETHOD(GetVerificationData)(MP_VerificationCondition Condition, void* pData ) PURE;
    STDMETHOD(GetVolatileData)(void* pData) PURE;
    STDMETHOD(SetVolatileData)(int iSize, void* pData) PURE;
    STDMETHOD(RollBack)(MP_Path* pPath, int iWithoutMe ) PURE;
    // 5.0.5追加
    STDMETHOD(SetInteractiveMode)(int iMode) PURE;
    STDMETHOD(SetModuleOption)(void* pOption) PURE;
    STDMETHOD(UpdateStatusEx)(MP_Integer *pbAppearanceChanged, void* pModuleOption) PURE;
    STDMETHOD(GetModuleInformation)(void* pModuleInfo) PURE;
    STDMETHOD(GetModuleError)(int* piError) PURE;
    // 6.0
    STDMETHOD_(MPCSignatureHistory*, CreateHistory)( HRESULT* phres = NULL ) PURE;
    // 7.0
    STDMETHOD(GetSignatureNameW)(MP_String &name) PURE;
    STDMETHOD(RollBackW)(const MP_WPath* path, int iWithoutMe ) PURE;
};

/*
 §5.9 MPCSignatureHistory インタフェース
 
 電子署名機能を操作するための補助インタフェース
 
 §5.9.1 インタフェースID
 
 このインタフェースはインタフェースIDを持たない。
 MPCIntefaceを継承しない
 
 §5.9.2 メソッド一覧
 */

mpinterface MPCSignatureHistory {
    STDMETHOD(GetSignatureVersionSelf)(char* pszText = NULL) PURE;
    STDMETHOD(HasEditSave)() PURE;
    STDMETHOD(HasNextSignature)() PURE;
    STDMETHOD(GetSignatureVersionNext)(char* pszText = NULL) PURE;
    STDMETHOD(Destroy)() PURE;
};


#include "mpc_textattribute.h"
#include "internaldoc.h"


#endif // MPCOREAPI_H

//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.25 - Ichiriki - AR490 コアで制限するデータ最大値の追加
//96.8.8 - Ichiriki - AR490 + 8/6議事録、MPC_MAX_ATTR_SIZE を 10MB に変更
//96.9.3 - Nagano - OpenFile(), Save(),SaveAs()のエラーコード追加
//96.9.27 - Ichiriki - AR1142. MPCProfile::OnDraw() を削除
//97.2.20 - Sumida - #define MPC_MAX_*の値を3個所とも変更
//97.3.21 - ysato - MPC_MAX_ATTR_SIZEを10MBに戻す
//97.10.2 - Sumida - IID_MPCText, IID_MPCSelectText, IID_MPCFind3のインタフェースオブジェクトIDの追加
//97.10.14 - Ichiriki - MPCProfileに、ShallowDuplicate, GetStorageVersion, GetFilePathを追加
//97.10.21 - Ichiriki - DELETED_Reload, DELETED_SetAplLog　削除。仕様の補記
//97.11.11 - Nagano - コメント行の修正.OpenMPFile()のエラーコードを実装に合わせた
//97.11.21 - Nagano - AR1653:エラーコードMP_E_NEWFORMATを追加
//97.12.2 - ysato - AR1379(表示ちらつき対策)、MPCMediaAdv::AddErasingBkgndRect()追加
//97.12.8 - Ichiriki - AR1598 IID_MP_PDCache のコメント記述を追加
//97.12.11 - Ichiriki - AR1843 IID_MPCSFXOperations のコメント記述を追加
//97.12.11 - Nagano - AR1843 MPCSFXOperationsインターフェースを追加
//97.12.12 - Ichiriki - AR1808 MPCConvertVersionインターフェースを追加
//97.12.22 - Ichiriki - AR2057 代理ペンの定義一式を追加
//97.12.26 - Nagano - AR2105 エラーコードMP_E_BAD_NETPATHを追加
//98.5.28 - Nagano - V3.1:CreateFileMPCObject()の仕様説明を修正
//98.6.9 - Nagano - V3.1:SaveToPath(), SaveToFileObject()を追加.GetFilePath()の変更.
//98.6.11 - Ichiriki - V3.1:仕様記述（コメント）部分の誤記修正
//98.6.12 - Nagano - V3.1:MP_E_FILE_EXISTSのレビュー後修正
//98.6.12 - Ichiriki - V3.1:GetStorageVersion仕様加筆。MP_Fileリターン値の仕様変更
//98.6.16 - Ichiriki - V3.1:6/16設計ボード〜EXTERN_GUIDの定義削除
//98.6.17 - Komoda - V3.1:MPCMedia::OnDraw()にOLEサーバ関連の記述を追加
//98.6.19 - Nagano - V3.1:MP_File インタフェース仕様追記
//98.6.26 - Nagano - V3.1:OLEサーバー用エラーコードMP_E_FATALの追加、コールバック関数の追加
//99.5.13 - Ichiriki - V4.0:OpenFileのエラーコード説明の追記
//99.5.18 - Tashiro - V4.0:MP_E_BAD_FORMAT_ODOA、MP_E_BAD_CHECKSUMの定義を追加
//99.5.18 - Ichiriki - V4.0:バインダの定義、セキュリティの仕様を追加
//99.5.18 - Nakazawa - V4 MAX_PD_SIZEの上限を250MBに緩和、キャンセル関係のPROCESS*追加、IID_* 追加、セキュリティ関係の実装追加
//99.5.20 - Ichiriki - V4:バインダ(MPCDocRoot インタフェース)の定義
//99.5.20 - Ichiriki - V4:バインダのオブジェクトIDを松本氏発行の番号に変更
//99.5.21 - Ichiriki - V4: OpenMP の仕様を追記
//99.6.1 - Nakazawa - V4: GetPermission の HRESULT の説明を変更
//99.6.1 - Ichiriki - コメント：　0x1323 IID_MPCFind4  V4検索用（佐藤要求）追加
//99.6.14 - Tashiro - コメント：　GetStorageVersionの説明をV4に合せて変更
//99.6.14 - Tashiro - コメント：　0x137A IID_ISpecialAttribute  V4文字認識結果取得用I/F 追加
//99.6.14 - Tashiro - コメント：　MPCObject の記述に OpenMP()前の制約を追加
//99.6.14 - Nakazawa - コメント： V4: 0x1380 IID_MP_MHPD, 0x1381 IID_MP_BMPMHPD 追加(MH->MMRコンバータ用)
//99.6.25 - Ichiriki - コメント： EnumAttribute() の仕様補記。
//99.6.28 - Ichiriki - MPCCopyFile,MPCMoveFileEx,MPCMoveFile,MPCDeleteFile追加
//99.6.28 - Tashiro - コメント：MPCObject::GetAttribute、Duplicate、UnlinkChildにMP_E_BAD_CHECKSUMの説明追加
//99.6.29 - Ichiriki - コメント：MPCCopy/Move/DeleteFileでチェックはSHARING_VIOLATIONのみに限定と付記
//99.6.29 - Ichiriki - コメント： 0x1324	IID_AUTOROTATE 追加
//99.7.3 - Ichiriki - エラーコードにHRESULT型明示宣言追加
//99.7.7 - Ichiriki - MPC_MAX_FILE_SIZE を 1GBに変更
//99.7.16 - Ichiriki - コメント：セキュリティセレクタ IID 追加
//99.7.28 - Tashiro - コメント：GetAttributeのセキュリティ関連仕様を追加
//99.7.30 - Nakazawa - エラーコード MP_E_OVER_MAX_* 追加、MP_S_PROTECTED_* のコメント追加
//99.8.3 - Ichiriki - AR4160 MPCMoveFileEx() を MPCMoveFile() に変更
//99.8.20 - Nakazawa - エラーコード MP_E_NOPERMISSION 追加
//99.8.30 - Tashiro - コメント：MPCProfile各関数のOpenMP前の動作を記述
//99.9.6 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//99.9.21 - Tashiro - コメント：MPCSession::Saveの説明に追記保存条件を記述
//99.10.1 - Ichiriki - コメント：MPCProfile::Define/UndefineAttribute仕様削除
//----V41開発
//00.09.25 - Tashiro - V41 メモリからのJPEG直接取り込みを追加
//00.09.25 - Nakazawa - V4.1 テンプレートによるセキュリティ設定の定義を追加
//00.09.26 - Nakazawa - V4.1 プロセスモデルのID追加、各セキュリティテンプレートIDのコメントを修正
//00.10.12 - Nakazawa - V4.1 コードレビューの結果を反映
//00.11.30 - Tashiro - AR6224 可逆圧縮の自動選択を指定するフラグ定義をmpc_pd.hから移動
//----V5開発
//2002.02.08 - Tashiro - セキュリティ一括設定、電子署名用のI/F追加
//2002.02.14 - Tashiro - OpenMP()に「常に非対話で認証できる文書のみを認証」モードの追加
//2002.02.23 - Tashiro - セキュリティタイプ追加、MPCSession, MPCProfile, MPCSignature変更
//2002.02.26 - Nakazawa - 文書が保護されているかどうかを調べる関数を追加
//2002.02.26 - Tashiro - MPCSignature、MPCSession変更中
//2002.02.28 - Tashiro - SaveWithSignature()引数追加
//2002.04.19 - Tashiro - 署名検証用データ、メソッドの追加
//2002.04.29 - Tashiro - 署名関連I/Fの変更
//2002.05.01 - Tashiro - MPCSignature拡張(モジュールID取得)
//2002.05.12 - Tashiro - MPCSignature拡張(署名保存時の非保存データの追加)
//2002.05.14 - Nakazawa - 128bitパスワード用テンプレートSPIのIDを追加
//2002.05.18 - Tashiro - MPCSignature/MPCSignature拡張(署名時へのロールバック)
//2002.05.21 - Tashiro - AR7390 署名検証用データに自分が最後の署名か分かるデータを追加
//2002.06.28 - Tashiro - AR7369 保存後のファイルバージョンを問い合わせるメソッド追加
//----5.0.2
//2002.11.12 - Tashiro - 5.0.2 AR6978 ファイルパス長の仕様に関する記述を変更
//----5.0.5
//2003.08.12 - Tashiro - 5.0.5 MPCSignature拡張(署名API用)
//----V6開発
//2004.03.26 - Komoda - V6.0 検索用のIDを追加
//2004.04.06 - Tashiro - V6.0 OpenModeのOM_MODEST_READ、MP_File::IsValid()追加
//2004.04.07 - Tashiro - V6.0 仕様コメント追加、IsValid→CheckValidity名称変更
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
//2004.07.29 - Tashiro - AR10326 署名履歴表示機能の追加
//2004.10.29 - Tashiro - AR11563 MRC-PD生成時のエラーコードを新規追加
//2004.11.17 - Tashiro - AR11796 スクラッチのときのMPCProfile::CheckData/GetSaveStorageVersionはエラーとする
// --- 6.0.4 ---
//2005.09.29 - Tashiro - APIセキュリティ機能拡張のためにMPCProfileにメソッド追加
//2006.01.16 - Tashiro - AR12665 MPCSessionに署名可能か確認するメソッド追加
// --- 6.2 ---
//2006.07.20 - Tashiro - DE2.0向け拡張
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
//2006.09.29 - Tashiro - AR13076 属性定義のINTの記述に具体的数値を明記
//2006.10.11 - Tashiro - AR13029 新規セキュリティID用の予約領域の記述を追加
// --- 7.0 ---
//2007.09.11 - Komoda  - V7.0 Unicode I/Fの追加
//2007.11.30 - Komoda  - V7.0 DW_FILEVERSIONの変更
//2007.12.18 - Komoda  - V7.0 MAX_FILE_SIZE, MAX_PD_SIZE, MAX_PAGE_DIM_SIZE の拡大
//2008.09.01 - Tashiro - V7.0 SynchronizeしないでIStgObjectを取得するI/Fを追加(AR15514)
