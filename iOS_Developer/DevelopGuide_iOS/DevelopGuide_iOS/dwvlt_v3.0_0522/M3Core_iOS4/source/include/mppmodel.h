// File: mppmodel.h
// Author: Osamu Nagano
// Copyright(C) 1996 by Fuji Xerox Co., Ltd. All right reserved.  

#ifndef MPPMODEL_H
#define MPPMODEL_H

#include "mpc_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
@defgroup pmodel_function_process_document [PModel]文書処理の関数
@{
*/

/*!
@brief オリジナルデータを用いて文書の更新を行う。
<pre>
mpのコンテントドキュメントcontDocにボディコンテントを更新させ、その結果を
ページにも反映させる。これらの処理が完了するまで、この関数は復帰しない。
ただし、処理中にMPPMBreakUpdatePagesが呼び出されたときは、この関数は速やかに
復帰する。このとき、 mpの状態は関数の呼び出し前と変わらない。
mpはOpenMPされていなければならない。
mpが文書編集禁止または転記禁止の場合、MP_E_NOPERMISSION エラーになる。
mpはDW文書を指定する。(バインダを指定した場合の動作は不定）
</pre>
@param[in] session セッション
@param[in] mp メタペーパオブジェクト
@param[in] contDoc コンテントドキュメントオブジェクト
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMUpdatePages)(
	MPCSession* session, MPCObject* mp, MPCContDocument* contDoc);

/*!
@brief MPPMUpdatePagesの処理中止を要求する。
<pre>
mpのコンテントドキュメントcontDocについて、 MPPMUpdatePagesの処理中であった
場合、その処理を速やかに中止させる。この関数によってMPPMUpdatePages が復帰した
ときは、mpの状態はMPPMUpdatePages呼び出し前と変わらない。
MPPMUpdatePagesの処理中でなかったときは、何もしない。
</pre>
@param[in] mp メタペーパオブジェクト
@param[in] contDoc コンテントドキュメントオブジェクト
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMBreakUpdatePages)(
	MPCObject* mp, MPCContDocument* contDoc);

/*!
@brief 文書を別の文書に挿入する。
<pre>
src_mpの複製をdst_mpのnth番目のページに挿入する．src_mpは変化しない．
src_mp, dst_mp共に、OpenMPされていなければならない。
nthが0の時はdst_mpの先頭ページへ，nthが5の時はdst_mpの5ページ目の後ろへ，
nthが-1の時にはdst_mpの末尾に挿入する．
nthが-2以下，dst_mpのページ数+1以上の時はエラーで返る．
src_mpが転記禁止またはdst_mpが文書編集禁止の場合、MP_E_NOPERMISSION エラーになる。
src_mp,dst_mpはDW文書を指定する。(バインダを指定した場合の動作は不定）
</pre>
@param[in] dst_mp 挿入先メタペーパオブジェクト
@param[in] src_mp 挿入元メタペーパオブジェクト
@param[in] nth 挿入先ページ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMMergeMP)(
	MPCObject* dst_mp, MPCObject* src_mp, MP_Integer nth = -1);

/*!
白紙1ページからなるメタペーパを生成して返す。生成されたメタペーパはファイル
に結びついていない状態(スクラッチ)である。nameはメタペーパ名で、プロファイルの
属性#nameに設定される。dimはページサイズで、生成されたページの属性#dimに設定さ
れる。
返されるメタペーパはOpenMPされている。
@param[in] session セッション
@param[in] name メタペーパ名
@param[in] dim ページサイズ
@param[out] phres リザルトコード
@return MPCObject* 生成されたメタペーパ
*/
DLLBINDFUNC_(MPCObject*, MPPMCreateNewMetaPaper)(
	MPCSession* session, MP_Octet* name, MP_Dim dim,
	HRESULT* phres = NULL);

DLLBINDFUNC_(MPCObject*, MPPMCreateNewMetaPaperW)(
	MPCSession* session, const MP_Text* name, MP_Dim dim,
	HRESULT* phres = NULL);

/*!
MPPMPullOutOnePageは無効になる。V4以降はMPPM4PullOutOnePage()を使うこと
*/
DLLBINDFUNC_(MPCObject*, MPPMPullOutOnePage)(
	MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL);

/*!
<pre>
mpのnthで特定されるページを複製し、そのページ1ページからなるメタペーパを生
成して返す。生成されたメタペーパはファイルに結びついていない状態(スクラッチ)で
ある。生成されたメタペーパーのプロファイル属性には原則としてmpと同一のプロファ
イル属性が付加される。プロファイルコンテントは付加される。コンテントドキュメン
トは持たない。mpはOpenMPされていなければならない。返されるメタペーパはOpenMPさ
れている。mpが転記禁止の場合、MP_E_NOPERMISSION エラーになる。
mpはDW文書を指定する。
V4.1より、バインダーに対してもこの関数を実行できるようになる。
mpがバインダーであった場合は、指定nthページが属する内部文書のプロファイル属性からなる
メタペーパーが複製される。
</pre>
@param[in] mp メタペーパオブジェクト
@param[in] nth 複製するページ
@param[out] phres リザルトコード
@return MPCObject* 生成されたメタペーパ
*/
DLLBINDFUNC_(MPCObject*, MPPMCopyOnePage)(
	MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL);
//! @}

/*!
@defgroup pmodel_function_from_image [PModel]画像からの変換関数
@{
*/
/*!
@brief BMPファイルからXDW文書ファイルを作成する@par
srcPathで指定されたDIBファイルからMetaPaperを生成し、dstPathで指定したファイル名で保存する。
引数の意味はMPPMDIBFileToBasicPageと同じである。
@param[in] session セッション
@param[in] srcPath 入力JPEGファイルのパス
@param[in] dstPath 出力XDWファイルのパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[in] level 圧縮レベル
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMDIBFileToMetaPaper)(
	MPCSession* session, const MP_Path* srcPath, const MP_Path* dstPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level);

/*!
@brief BMPファイルからXDW文書ファイルを作成する (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMDIBFileToMetaPaperW)(
	MPCSession* session, const MP_WPath* srcPath, const MP_WPath* dstPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level);

/*!
@brief BMPファイルからBasicPageを生成して返す。
<pre>
srcPathで指定されたDIBファイルからPDを生成して、寸法dimPdのBodyContと、
寸法dimPageのBasicPageを作り、BasicPageのpos位置にBodyContを貼って返す。
画質指定（劣化なし=1、高画質=2、標準=3、高圧縮=4）をlevelの値としてセットすること

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。
</pre>
@param[in] session セッション
@param[in] srcPath JPEGファイルのパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[in] level 圧縮レベル
@param[out] phres リザルトコードのポインタ
@return MPCObject* 生成したBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMDIBFileToBasicPage)(
	MPCSession* session, const MP_Path* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL);

/*!
@brief BMPファイルからBasicPageを生成して返す (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMDIBFileToBasicPageW)(
	MPCSession* session, const MP_WPath* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL);

/*!
@brief JPEGファイルからBasicPageを生成して返す。

srcPathで指定されたJPEGファイルをPD（外部JPEGとして保持）に変換して、寸法dimPdのBodyContと、
寸法dimPageのBasicPageを作り、BasicPageのpos位置にBodyContを貼って返す。
@param[in] session セッション
@param[in] srcPath JPEGファイルのパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[out] phres リザルトコードのポインタ
@return MPCObject* 生成したBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMJPEGFileToBasicPage)(
	MPCSession* session, const MP_Path* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL);

/*!
@brief JPEGファイルからBasicPageを生成して返す (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMJPEGFileToBasicPageW)(
	MPCSession* session, const MP_WPath* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL);

//////////////////// V4 追加分 //////////////////////////////////////

/*!
@brief 経過表示＆キャンセル機構を追加した MPPMDIBFileToBasicPage()。
<pre>
MPC_AdvCancelInfo で指定するコールバック関数は、
処理続行ならMP_PROCESS_CONTINUEを、キャンセルならMP_PROCESS_CANCELを返すこと。
phres には、キャンセルされたらMP_S_PROCESS_CANCELED(==1)が、
成功ならMP_S_OK(==0)が格納される。
コールバック関数は、約0.5秒間隔で呼ばれる。
その他のキャンセルの仕様は MediaAdv::OnPrint() と同じである。
キャンセルまたはエラーの場合はNULLを返す。
info == NULL の場合は MPPMDIBFileToBasicPage() と同じ動作をする。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。
</pre>
@param[in] session セッション
@param[in] srcPath BMPファイルパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[in] level 圧縮レベル
@param[out] phres リザルトコードのポインタ
@param[in] info キャンセル情報
@return MPCObject* 生成したBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMDIBFileToBasicPageAdv)(
	MPCSession* session, const MP_Path* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);

/*!
@brief 経過表示＆キャンセル機構を追加した MPPMDIBFileToBasicPage (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMDIBFileToBasicPageAdvW)(
	MPCSession* session, const MP_WPath* srcPath,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);

/*!
@brief メモリ上のhDIBからBasicPageを作成する。
<pre>
ここで hDIB を void* で定義しているが、これは windows.h をこのヘッダ内で
インクルードしなくてもいいようにするためである。
利用者は特に意識せずに HGLOBAL で定義された hDIB を渡せば良い。
hDIBは、BITMAPINFOとパレット(あれば)とビットデータが連続して格納されているものとする。
この関数にhDIBを渡す前に GlobalUnlock() をしておくこと。
経過表示＆キャンセルの仕様は MPPMDIBFileToBasicPageAdv() と同じである。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。
</pre>
@param[in] session セッション
@param[in] hDIB DIBのハンドル
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[in] level 圧縮レベル
@param[out] phres リザルトコードのポインタ
@param[in] info キャンセル情報
@return MPCObject* 生成したBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMHDIBToBasicPageAdv)(
	MPCSession* session, void* hDIB,
	MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);


/*!
<pre>
マルチページTIFFファイルを MP_File で ReadOnly で開いたものに対して、
ファイルに格納されている nth 目のイメージを BasicPage に変換する。nth は 0 基数である。
ppage には、タグに PageNumber があればその値を格納する。なければ何も行わない。
ppage : NULL の場合は PageNumber タグがあっても何も行わない。
その他のパラメータは MPPMDIBFileToBasicPage() や MPPMJPEGFileToBasicPage() と同じである。
取り込めるTIFFは以下の条件を満たすものである。
  IFDエントリについて
	ImageWidth		9以上65535以下
	ImageLength		2以上
	BitsPerSample	1のみ(モノクロの意味)
	PhotometricInt.	0のみ(白が0、黒が1の意味)
	Compression		4のみ(G4, MMR圧縮の意味)
	XResolution		正の値
	YResolution		正の値
	ResolutionUnit	2or3のみ(インチまたはセンチメートルの意味)
	Orientation		1のみ(原点が左上の意味)
	FillOrder		1のみ(順ビット並びの意味)
	RowsPerStrip	ImageLengthと同じ値(Stripが一つだけの意味)
	T6Options		0(無圧縮データは現れないの意味)
	StripOffsets	必要
	StripByteCounts	必要
	PageNumber		存在すれば見る
  これ以外のエントリは無視する。存在しないエントリはデフォルト値として扱う。
  また、MMRのデータが壊れているもの、圧縮率が30%より悪いのものは取り込まない。
</pre>
@param[in] session セッション
@param[in] mpfile MP_Fileオブジェクト
@param[in] nth 変換するイメージの番号(0基数)
@param[out] ppage ページ番号を受け取るポインタ
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos PDのページ上の位置
@param[out] phres リザルトコードのポインタ
@return MPCObject* 生成したBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMTIFFMPFileToBasicPage)(
	MPCSession* session, MP_File* mpfile, MP_Integer nth, MP_Integer* ppage,
	MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, HRESULT* phres = NULL);
//! @}


/*!
@defgroup pmodel_function_convert_to_image [PModel]画像への変換関数
@{
*/
// 以下、イメージ変換出力関数用の定義
#define	MPPM_CONVDIB_RESO_LOW_LIMIT		10		//!< イメージ変換出力解像度の下限
#define	MPPM_CONVDIB_RESO_HIGH_LIMIT	600		//!< イメージ変換出力解像度の上限

//! @brief DIB変換モードの指定
enum MPPM_CONVDIB_MODE {
	//! CreateDIBSection()を用いて1bitモノクロのDIBを出力する。
	MPPM_CONVDIB_MONO			= 0,
	//! ディスプレイが4bitか8bitならMPF_CreateCompatibleBitmap()を用いてディスプレイと同じbit数のDIBを出力する。
	//! それ以外ならCreateDIBSection()を用いて24bitのDIBを出力する。
	MPPM_CONVDIB_COL_DEFAULT	= 1,	
	//! ディスプレイが8bitならMPF_CreateCompatibleBitmap()を用いて8bitのDIBを出力する。
	//! それ以外ならCreateDIBSection()を用いて24bitのDIBを出力する。
	MPPM_CONVDIB_COL_OVER8BIT	= 2,	
	//! CreateDIBSection()を用いて24bitのDIBを出力する。
	MPPM_CONVDIB_COL_FULL		= 3,
	//! 白黒 1bit 高画質出力
	MPPM_CONVDIB_MONO_HIQUALITY	= 4,
};

/*!
@brief BasicPageをメモリDIBに変換する
<pre>
bp で指定された BasicPage を dpi で指定された解像度(10-600)、mode で指定されたモードで
hDIB に変換して返す。
mode は MPPM_CONVDIB_MODE に従う。
MediaAdv::OnPrint()と同じ仕様の経過表示＆キャンセル機構を info で指定できる(内部で
OnPrint()を使用しているため)。
アノテーションは、表示フラグが立っていれば出力され、なければ出力されない。
返す hDIB は内部でアロケートしたものである。利用者はいらなくなったら GlobalFree()
で解放すること。
hDIB には、BITMAPINFOとパレット(あれば)とビットデータが連続して格納されている。
ここでリターン値を void* で定義しているが、これは windows.h をこのヘッダ内でインクルード
しなくてもいいようにするためである。
利用者は特に意識せずに HGLOBAL に代入して良い。
エラーなら NULL を返し、phres があればエラーコードを格納する。
この関数はイメージ変換出力のコード整理のために追加された。
</pre>
@param[in] session セッション
@param[in] bp BasicPage
@param[in] dpi 出力解像度
@param[in] mode 変換モード
@param[out] phres リザルトコードのポインタ
@param[in] info キャンセル情報
@return void* DIBのポインタ
*/
DLLBINDFUNC_(void*, MPPMConvertBasicPageToHDIB)(
	MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL);

/*!
@brief BasicPageをメモリDIBに変換する
<pre>
infoまでの引数はMPPMConvertBasicPageToHDIB()と同じ
</pre>
@param[in] iCentiDPI 出力解像度を100倍した値
@param[in] bClipInside 外周1画素分の白枠を付けるか。従来動作(=省略値)はtrue(=白枠が付く)
@param[in] bHighQuality サムネールと同じ画質で作成する。従来動作(=省略値)はfalse
*/

DLLBINDFUNC_(void*, MPPMConvertBasicPageToHDIBCentiDPI)(
	MPCSession* session, MPCObject* bp, MP_Integer iCentiDPI, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL, bool bClipInside = true, bool bHighQuality = false);

/*!
@brief BasicPageをBMPファイルに変換する
<pre>
bp で指定された BasicPage を dpi で指定された解像度(75-600)、mode で指定された
モードでビットマップファイルに変換する。
dstPath に BITMAPFILEHEADER 付きのビットマップファイルを作成することと、
返り値がエラーコード HRESULT であること以外は MPPMConvertBasicPageToHDIB
と同じ仕様である。
</pre>
@param[in] session セッション
@param[in] bp BasicPage
@param[in] dstPath 出力BMPファイルパス
@param[in] dpi 出力解像度
@param[in] mode 変換モード
@param[in] info キャンセル情報
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMConvertBasicPageToDIBFile)(
	MPCSession* session, MPCObject* bp, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);

/*!
@brief BasicPageをBMPファイルに変換する (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMConvertBasicPageToDIBFileW)(
	MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);

/*!
@brief PDをメモリDIBに変換する
<pre>
pd で指定された PD を指定パラメータで hDIB に変換して返す。
pd に変換したい PD を指定する以外は、各パラメータは MPPMConvertBasicPageToHDIB に従う。
この関数は V4 ページ加工プラグインでアプリのページをイメージに変換する際に用いるために追加された。
注：画質はディスプレイ色と OnPrint() による Windows GDI によるので、
オリジナルイメージ取り出しをしたいだけの場合は MP_PD::ConvertToDIB* を用いること。
</pre>
@param[in] session セッション
@param[in] pd PD
@param[in] dpi 出力解像度
@param[in] mode 変換モード
@param[out] phres リザルトコードのポインタ
@param[in] info キャンセル情報
@return void* DIBのポインタ
*/
DLLBINDFUNC_(void*, MPPMConvertPDToHDIB)(
	MPCSession* session, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL);

/*!
@brief PDをBMPファイルに変換する
<pre>
pd で指定された PD を指定パラメータでビットマップファイルに変換する。
dstPath に BITMAPFILEHEADER 付きのビットマップファイルを作成することと、
返り値がエラーコード HRESULT であること以外は MPPMConvertBasicPageToHDIB と同じ仕様である。
注：画質はディスプレイ色と OnPrint() による Windows GDI によるので、
    オリジナルイメージ取り出しをしたいだけの場合は MP_PD::ConvertToDIB* を用いること。
</pre>
@param[in] session セッション
@param[in] pd PD
@param[in] dstPath 出力BMPファイルパス
@param[in] dpi 出力解像度
@param[in] mode 変換モード
@param[in] info キャンセル情報
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMConvertPDToDIBFile)(
	MPCSession* session, MP_PD* pd, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);

/*!
@brief PDをBMPファイルに変換する (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMConvertPDToDIBFileW)(
	MPCSession* session, MP_PD* pd, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);
//! @}


/*!
@addtogroup pmodel_function_process_document
@{
*/
/*!
@brief 指定ページを文書から抜き取り、抜いたページからなるメタペーパを作成する。
<pre>
mpのnthで特定されるページをmpから抜き取り、そのページ1ページからなるメタ
ペーパを生成して返す。生成されたメタペーパはファイルに結びついていない状態(ス
クラッチ)である。生成されたメタペーパのプロファイル属性には、MPコアで自動的に
付けられるもの以外は付けられない。mpはOpenMPされていなければならない。
返されるメタペーパはOpenMPされている。
withContDoc が 1の場合、抜き取るページが関連づいているオリジナルデータがある場合、
そのオリジナルデータも抜き取って（Unlinkして）新しいメタペーパーに付けて、
新しいメタペーパーでページとオリジナルデータを関連づける。
ページとオリジナルデータが抜き取られた元のmpからページとオリジナルデータはなくなり、
抜き取ったオリジナルデータと他のページとの関連づけも消滅する。
withContDoc が 0の場合、オリジナルデータはつかないし、mpから抜き取られない。
withContDocが0,1以外の場合エラーになる。
セキュリティ保護されている場合でも、新しく作られるメタペーパーは未保護状態になる。
mpが文書編集禁止または転記禁止の場合、MP_E_NOPERMISSION エラーになる。
mpはDW文書を指定する。(バインダを指定した場合の動作は不定）
</pre>
@param[in,out] mp メタペーパオブジェクト
@param[in] nth 抜き取るページ
@param[in] withContDoc オリジナルデータを移動するかどうか。
@param[out] phres リザルトコードのポインタ
@return MPCObject* 生成されたメタペータ
*/
DLLBINDFUNC_(MPCObject*, MPPM4PullOutOnePage)(
	MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL);
//! @}


//////////////////// V4 追加分(終了) //////////////////////////////////////

//////////////////// V4.1 追加分 ////////////////////////////////////////////

/*!
@addtogroup pmodel_function_process_document
@{
*/
/*!
  「表示ページで分割」用
	mpで指定される文書を、先頭〜nth-1, nth〜総ページ(nthは0基数)で分割し、その後半部分
	からなるメタペーパを生成して返す。mpはその前半部分だけの文書にメモリ上で更新される。
	生成されたメタペーパはファイルに結びついていない状態(スクラッチ)で
	ある。生成されたメタペーパーのプロファイル属性には、原則としてmpと
	同一のプロファイル属性が付加される。プロファイルコンテントは付加される。
-	withContDoc==0の場合は、全てのオリジナルデータは前半(mp)に付いた
	ままで、生成される後半のメタペーパにはオリジナルデータは付かない。
-	withContDoc==1の場合は、オリジナルデータは最初に関連付けられた
	ページが含まれるメタペーパ側に付く(移動する)。
-	ページに関連付けられていないオリジナルデータは常に前半(mp)側に付く。
-	オリジナルデータとページの関連付けは、オリジナルデータが含まれる
	メタペーパ内のページに関してのみ保持される。
-	mpはOpenMPされていなければならない。返されるメタペーパはOpenMPされている。
-	mpが文書編集禁止あるいは転記禁止の場合、MP_E_NOPERMISSION エラーになる。
-	エラーが発生したとき、mpは更新されている場合があることに注意する。
-	mpはDW文書を指定する(バインダを指定した場合の動作は不定)。

	@param[in] mp メタペーパ
	@param[in] nth 分割するページ
	@param[in] withContDoc オリジナルデータのつけ方
	@param[out] phres リザルトコードのポインタ
	@return MPCObject* 生成したメタペーパ
*/
DLLBINDFUNC_(MPCObject*, MPPMDivideAtCurrentPage)(
		MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL);

#define MPPM_BE_MAX_MARGIN		5000		//!< わく消し幅の最大値[1/100mm]

/*!
@brief 指定basicPageのわく消しを行う。
<pre>
top, bottom, left, right, centerLeft, centerRight はそれぞれ
上下左右と中消しの左右の位置を示し、単位はメディア座標系の1/100mmとする。
centerLeft == centerRight の場合は中わくは消さない。
上下左右中の消し幅はMPPM_BE_MAX_MARGINを超えるとエラーとなる。
MPC_AdvCancelInfo で指定するコールバック関数は、
処理続行ならMP_PROCESS_CONTINUEを、キャンセルならMP_PROCESS_CANCELを返すこと。
返り値はHRESULTで結果を表し、キャンセルされたらMP_S_PROCESS_CANCELED(==1)が、
成功ならMP_S_OK(==0)が、エラーならMP_E_*のエラーコードが返る。
info == NULL の場合は途中キャンセルは行わない。
成功した場合はbasicPageの中身のイメージがわく消しされたものに入れ替わる。
アノテーションなどはすべて保存される。
対象は白黒1bitイメージのみで、カラーイメージやアプリ文書の場合はエラー
(INVALIDARG)となる。
編集権が必要。権利がない場合はエラーが返る。
</pre>
@param[in] session セッション
@param[in,out] basicPage わく消しを行うBasicPage
@param[in] top 上余白の幅
@param[in] bottom 下余白の幅
@param[in] left 左余白の幅
@param[in] right 右余白の幅
@param[in] centerLeft 中消し左の位置
@param[in] centerRight 中消し右の位置
@param[in] pCancelInfo キャンセル情報
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMEraseBorder)(
	MPCSession* session, MPCObject* basicPage,
	MP_Integer top, MP_Integer bottom, MP_Integer left, MP_Integer right, MP_Integer centerLeft, MP_Integer centerRight, MPC_AdvCancelInfo* info = NULL);
//! @}
//////////////////// V4.1 追加分(終了) //////////////////////////////////////

//////////////////// V5.0 追加分(開始) //////////////////////////////////////
/*!
@defgroup pmodel_function_document_attribute [PModel]文書属性の関数
@{
*/
//文書属性 (概要) の属性名
#define	ANAME_TITLE		"%doc_att_title"	//!<概要の属性名: タイトル
#define	ANAME_SUBJECT	"%doc_att_subject"	//!<概要の属性名: 表題
#define	ANAME_AUTHOR	"%doc_att_author"	//!<概要の属性名: 作成者
#define	ANAME_KEYWORDS	"%doc_att_keywords"	//!<概要の属性名: キーワード
#define	ANAME_COMMENTS	"%doc_att_comments"	//!<概要の属性名: コメント

#define ANAME_TITLE_W		L"%doc_att_title"
#define ANAME_SUBJECT_W		L"%doc_att_subject"
#define ANAME_AUTHOR_W		L"%doc_att_author"
#define ANAME_KEYWORDS_W	L"%doc_att_keywords"
#define ANAME_COMMENTS_W	L"%doc_att_comments"

static const char* DocAtt_SummaryInfoName[] = {
	ANAME_TITLE,
	ANAME_SUBJECT,
	ANAME_AUTHOR,
	ANAME_KEYWORDS,
	ANAME_COMMENTS,
	0
} ;
/*!
@brief 文書属性の設定
@param[in] mp メタペーパオブジェクト
@param[in] lpszAttributeName 属性名へのポインタ
@param[in] nAttributeType 属性値の型
@param[in] pAttributeValue 属性値へのポインタ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMSetDocumentAttribute)(
	MPCObject* mp, const char* lpszAttributeName, int nAttributeType, char* pAttributeValue);

/*!
@brief 文書属性の設定 (unicode)
unicode版は、属性名、文字列属性の値はそれぞれワイドキャラクタ文字列を指定すること
@param[in] mp メタペーパオブジェクト
@param[in] lpszAttributeName 属性名へのポインタ
@param[in] nAttributeType 属性値の型
@param[in] pAttributeValue 属性値へのポインタ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMSetDocumentAttributeW)(
	MPCObject* mp, const MP_Text* lpszAttributeName, int nAttributeType, const void* pAttributeValue, MP_TAType tatype, int codepage);

/*!
@brief 文書属性数の取得
@param mp [in]属性を取得するメタペーパオブジェクト
@retval 正数 文書属性数
@retval 負数 エラー
*/
DLLBINDFUNC_(HRESULT, MPPMGetDocumentAttributeNumber)(MPCObject* mp);

/*!
@brief 属性名指定での文書属性の取得
@param[in] mp メタペーパオブジェクト
@param[in] lpszAttributeName 属性名へのポインタ
@param[out] nAttributeType 属性値の型
@param[out] pAttributeValue 属性値へのポインタ
@param[in] nDataSize pAttributeValue に割り当てられたバイト数
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetDocumentAttributeByName)(
	MPCObject* mp, const char* lpszAttributeName, int* nAttributeType,
	char* pAttributeValue, int nDataSize);

/*!
@brief 属性名指定での文書属性の取得 (unicode)
unicode版は、属性名にワイドキャラクタ文字列を指定すること
文字列属性の値はワイドキャラクタ文字列である
*/
DLLBINDFUNC_(HRESULT, MPPMGetDocumentAttributeByNameW)(
	MPCObject* mp, const MP_Text* lpszAttributeName, int& attributeType,
	void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage);

/*!
@brief 番号指定での文書属性の取得
@param[in] mp メタペーパオブジェクト
@param[in] nOrder 番号
@param lpszAttributeName 属性名へのポインタ
@param nAttributeType 属性値の型
@param pAttributeValue 属性値へのポインタ
@param nDataSize pAttributeValue に割り当てられたバイト数
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetDocumentAttributeByOrder)(
	MPCObject* mp, int nOrder, char* lpszAttributeName, int* nAttributeType, char* pAttributeValue, int nDataSize);

/*!
@brief 番号指定での文書属性の取得 (unicode)
unicode版は、属性名、文字列属性の値はそれぞれワイドキャラクタ文字列である

@param[in] mp メタペーパオブジェクト
@param[in] nOrder 番号
@param[out] attributeName 属性名を受け取る文字列オブジェクト
@param[out] attributeType 属性値の型
@param[out] pAttributeValue 属性値へのポインタ
@param[in] datasize pAttributeValue に割り当てられたバイト数
@param[out] tatype テキスト属性のタイプ
@param[in] codepage 文字コード変換する際のコードページ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetDocumentAttributeByOrderW)(
	MPCObject* mp, int nOrder, MP_String &attributeName, int& attributeType,
	void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage);
/* @} */

/*!
@defgroup pmodel_function_succeed_document [PModel]文書情報継承の関数
@{
*/
//V5.0 文書属性、アノテーションの継承
const int DOC_ATT_LENGTH = (255 + 20);		//!<属性名の長さ (最大 255byte + prefix)

const int MP_DOCATT_UNKNOWN	= 1;				//!<文書属性の型は取得できなかった
const int MP_DOCATT_INT		= 2;				//!<文書属性の型：数値
const int MP_DOCATT_OCTS	= 4;				//!<文書属性の型：文字列
const int MP_DOCATT_DATE	= 1000000;			//!<文書属性の型：日付
const int MP_DOCATT_BOOL_XD	= 2000000;			//!<文書属性の型：真偽値
const int MP_DOCATT_OTHER	= 3000000;			//!<文書属性の型：その他
// 削除予定 begin
// MP_DOCATT_* への移行が完了してから削除する
#define	MP_A_DATE		1000000				//!<属性型: 日付
#define	MP_A_BOOL_XD		2000000				//!<属性型: 真偽値
#define	MP_A_OTHER		3000000				//!<属性型: その他
// 削除予定 end

//! 継承元情報
typedef struct DW_referenceinfo {
	MPCObject*	mp ;
	MP_Integer	internalDocNumber ;
	MP_Integer	originalDataNumber ;
} DW_refinf ;

//継承の対象
#define	MPPM_SUMMARY_INFO	1				//!<継承対象: 文書属性(概要)
#define MPPM_USER_DEF		2				//!<継承対象: 文書属性(ユーザ定義)
#define	MPPM_ANNOTATION		4				//!<継承対象: アノテーション
/*!
@brief 文書属性、アノテーションの継承
@param[in] mp 編集する(継承先)メタペーパ
@param[in] refDWInfo 参照する DocuWorks 文書情報
@param[in] nSuccession 継承の対象
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMSucceedAttribute)(
	MPCObject* mp, DW_refinf* refDWInfo, MP_Integer	nSuccession);
/* @} */

/*!
@addtogroup pmodel_function_convert_to_image
@{
*/
/*!
@brief BasicPageをメモリDIBに変換する
<pre>
引数bWithAnnoがTRUEだった場合はアノテーション含みで、FALSEだった場合はアノテーションを含まない変換関数。
それ以外のパラメータはMPPMConvertBasicPageToHDIBに従う。
※この関数はAR7859対応のために追加された。
</pre>
@param[in] session セッション
@param[in] bp BasicPage
@param[in] dpi 解像度
@param[in] mode 変換モード
@param[out] phres リザルトコード
@param[in] info キャンセル情報
@param[in] bWithAnno アノテーションを含むかどうか
@return void* DIBのハンドル
*/
DLLBINDFUNC_(void*, MPPMConvertBasicPageToHDIBEx)(
	MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);

/*!
@brief BasicPageをBMPファイルに変換する(アノテつき)
<pre>
引数bWithAnnoがTRUEだった場合はアノテーション含みで、FALSEだった場合はアノテーションを含まない変換関数。
それ以外のパラメータはMPPMConvertBasicPageToDIBFileに従う。
※この関数はAR7859対応のために追加された。
</pre>
@param[in] session 
@param[in] bp 
@param[in] dstPath 
@param[in] dpi 
@param[in] mode 
@param[in] info 
@param[in] bWithAnno 
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMConvertBasicPageToDIBFileEx)(
	MPCSession* session, MPCObject* bp, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);

/*!
@brief BasicPageをBMPファイルに変換する(アノテつき) (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMConvertBasicPageToDIBFileExW)(
	MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);
//! @}
//////////////////// V5.0 追加分(終了) //////////////////////////////////////

//////////////////// V6.0 追加分 //////////////////////////////////////

/*!
@defgroup pmodel_function_mrc [PModel]MRC関連操作の関数
@{
*/
/*!
@brief IMSファイルから直接取り込みによりBasicPageを生成する
<pre>
pszImsPathで指定されたIMSファイルから直接取り込みによりBasicPageを生成して返す。
pszImsPathで指定されたIMSファイルをPD（MRCとして保持）に変換して、寸法dimPdのBodyContと、
寸法dimPageのBasicPageを作り、BasicPageのposPd位置にBodyContを貼って返す。
</pre>
@param[in] pSession セッション
@param[in] pszImsPath IMSファイルパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] posPd PDの位置
@param[in] iRotate 回転角
@param[out] phres リザルトコード
@return MPCObject* 生成されたBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMDirectImportIMSFileToBasicPage)(
		MPCSession* pSession,
		const MP_Path* pszImsPath,
		MP_Dim dimPd,
		MP_Dim dimPage,
		MP_Pos posPd,
		MP_Integer iRotate,
		HRESULT* phres = NULL );

/*!
@brief IMSファイルから直接取り込みによりBasicPageを生成する (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMDirectImportIMSFileToBasicPageW)(
		MPCSession* pSession,
		const MP_WPath* pszImsPath,
		MP_Dim dimPd,
		MP_Dim dimPage,
		MP_Pos posPd,
		MP_Integer iRotate,
		HRESULT* phres = NULL );

/*!
@brief IMSファイルからBasicPageを生成する
<pre>
pszImsPathで指定されたIMSファイルからBasicPageを生成して返す。
pszImsPathで指定されたIMSファイルを単層の画像に変換して取り込む。
寸法dimPdのBodyContと、
寸法dimPageのBasicPageを作り、BasicPageのposPd位置にBodyContを貼って返す。
画質指定（劣化なし=1、高画質=2、標準=3、高圧縮=4）をlevelの値としてセットすること

levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。
</pre>
@param[in] pSession セッション
@param[in] pszImsPath IMSファイルパス
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] posPd PDの位置
@param[in] iRotate 回転角
@param[in] level 圧縮レベル
@param[out] phres リザルトコード
@return MPCObject* 生成されたBasicPage
*/
DLLBINDFUNC_(MPCObject*, MPPMConvertIMSFileToBasicPage)(
		MPCSession* pSession,
		const MP_Path* pszImsPath,
		MP_Dim dimPd,
		MP_Dim dimPage,
		MP_Pos posPd,
		MP_Integer iRotate,
		MP_Integer level,
		HRESULT* phres = NULL,
		MPC_AdvCancelInfo* pCancelInfo = NULL );

/*!
@brief IMSファイルからBasicPageを生成する (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMConvertIMSFileToBasicPageW)(
		MPCSession* pSession,
		const MP_WPath* pszImsPath,
		MP_Dim dimPd,
		MP_Dim dimPage,
		MP_Pos posPd,
		MP_Integer iRotate,
		MP_Integer level,
		HRESULT* phres = NULL,
		MPC_AdvCancelInfo* pCancelInfo = NULL );

/*!
@brief BMPファイルからIMSファイルを生成する
@param[in] pszDibPath BMPファイルパス
@param[in] pszImsPath IMSファイル
@param[in] level 圧縮レベル
@param[in] info info キャンセル情報
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMDIBFileToIMSFile)(
	const MP_Path* pszDibPath, const MP_Path* pszImsPath,
	MP_Integer level, MPC_AdvCancelInfo *info = NULL );

/*!
@brief BMPファイルからIMSファイルを生成する (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMDIBFileToIMSFileW)(
	const MP_WPath* pszDibPath, const MP_WPath* pszImsPath,
	MP_Integer level, MPC_AdvCancelInfo *info = NULL );

/*!
@brief メモリ上のDIBからIMSデータを生成する
@param[in] pDibMem
@param[in] level 圧縮レベル
@param[out] phres リザルトコードのポインタ
@param[in] info キャンセル情報
@return void* IMSデータのポインタ
*/
DLLBINDFUNC_(void*, MPPMDIBMemToIMSMem)(
	const unsigned char* pDibMem, MP_Integer level,
	HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL );


/*!
@brief IMSファイルの画像の画素数と解像度を返す。
@param[in] srcPath IMSファイルのパス
@param[in] pImagePix 画像のピクセル数
@param[in] pImageRes 画像の解像度
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetIMSInfo)(
	const MP_Path* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes );

/*!
@brief IMSファイルの画像の画素数と解像度を返す (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMGetIMSInfoW)(
	const MP_WPath* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes );


/*!
@brief MPC-PDのページからPDFファイルを生成する
<pre>
pPage で指定された PD がMRCのとき、pszDestPathへ高圧縮PDFとして取り出す。
pPageがMRC-PDを持たなければエラー。
転記権が必要。権利がない場合はエラーが返る。
</pre>
@param[in] pSession セッション
@param[in] pPage ページオブジェクト
@param[out] pszDestPath PDFファイルのパス
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetPDFFromMRCPDPage)(
	MPCSession* pSession, MPCObject* pPage, const MP_Path* pszDestPath );

/*!
@brief MPC-PDのページからPDFファイルを生成する (unicode)
*/
DLLBINDFUNC_(HRESULT, MPPMGetPDFFromMRCPDPageW)(
	MPCSession* pSession, MPCObject* pPage, const MP_WPath* pszDestPath );
//! @}

/*!
@addtogroup pmodel_function_from_image
@{
*/
/*!
@brief メモリ上のDIBからPDを生成する
@param[in] pSession セッション
@param[in] pBmpInfo 
@param[in] pImageData ビットマップデータのポインタ
@param[in] dimPD PDのサイズ
@param[in] iCompLevel 圧縮レベル
@param[out] phres リザルトコードのポインタ
@param[in] pCancelInfo キャンセル情報
@return MP_PD* 生成したPD
*/
DLLBINDFUNC_(MP_PD*, MPPMCreatePDfromMemBitmap)(
	MPCSession* pSession, void* pBmpInfo, unsigned char* pImageData, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo );

/*!
@brief BMPファイルからPDを作成する。
@param[in] pSession セッション
@param[in] pszBmpPath BMPファイル
@param[in] dimPD PDのサイズ
@param[in] iCompLevel 圧縮レベル
@param[out] phres リザルトコードのポインタ
@param[in] pCancelInfo キャンセル情報
@return MP_PD* 生成されたPD
*/
DLLBINDFUNC_(MP_PD*, MPPMCreatePDfromBmpFile)(
	MPCSession* pSession, const MP_Path* pszBmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo );

/*!
@brief BMPファイルからPDを作成する (unicode)
*/
DLLBINDFUNC_(MP_PD*, MPPMCreatePDfromBmpFileW)(
	MPCSession* pSession, const MP_WPath* pszBmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo );
//! @}

/*!
@defgroup pmodel_function_layout_information [PModel]ページレイアウト情報の関数
@{
*/
/*!
@brief ページのレイアウト情報を保存する。
<pre>
DW変換後のページのサイズまたはヘテロの位置が、変換前(PDFなど)の
ページのサイズ、画像の位置と異なるときはこの関数で保存しておく。
ヘテロ・オブジェクトの"orgpagedim"、"orgimagepos"属性として保存される。
MPPMGetPDFFromMRCPDPage()とMPPMGetPageLayoutInfo()は上記の属性が
あればそれを優先して用いる。
</pre>
@param[in] pBasicPage 情報を保存するページ
@param[in] dimOrgPage 元のページサイズ
@param[in] posOrgImage 元の画像の位置
@param[in] dimOrgImage 元の画像のサイズ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMSetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim dimOrgPage, MP_Pos posOrgImage, MP_Dim dimOrgImage );

/*!
@brief ページのレイアウト情報を読み出す。
@param[in] pBasicPage 情報を取得するページ
@param[out] pDimOrgPage ページのサイズ
@param[out] pPosOrgImage 画像の位置
@param[out] pDimOrgImage 画像のサイズ
@return HRESULT リザルトコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim* pDimOrgPage, MP_Pos* pPosOrgImage, MP_Dim* pDimOrgImage );
//! @}

/*!
@addtogroup pmodel_function_mrc
@{
*/
/*!
@brief JPEGファイルからBasicPageを生成する。@par
- srcPathで指定されたJPEGファイルからBasicPageを生成して返す。
- srcPathで指定されたJPEGファイルをMRC-PDまたはJPEG-PDに変換して、寸法dimPdのBodyContと、
寸法dimPageのBasicPageを作り、BasicPageのpos位置にBodyContを貼って返す。
- iCompLevelは6-9のとき、MRC分離できた場合はMRC-PDとし、
分離できなかった場合には、JPEGを外部JPEGとして取り込む。
- 9(外部MRC)が指定されたら7(標準MRC)として扱う。
- iCompLevelが0-5のときはMPPMJPEGFileToBasicPage()と同じ動作。
(外部JPEGとして取り込む)

@param[in] session セッション
@param[in] srcPath JPEGファイルのパス
@param[in] iCompLevel 圧縮レベル
@param[in] dimPd PDのサイズ
@param[in] dimPage ページのサイズ
@param[in] pos 
@param[out] phres リザルトコードのポインタ
@param[in] pCancelInfo
@return MPCObject*
*/
DLLBINDFUNC_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRC)(
	MPCSession* session, const MP_Path* srcPath, MP_Integer iCompLevel,
	MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo);

/*!
@brief JPEGファイルからBasicPageを生成する (unicode)
*/
DLLBINDFUNC_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRCW)(
	MPCSession* session, const MP_WPath* srcPath, MP_Integer iCompLevel,
	MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo);
//! @}

const int CUSTOM_ATT_NAME_LENGTH = 256;		// 属性名の長さ。NULL文字を含んだ文字数(設定できる文字数は-1)
const int CUSTOM_ATT_TEXT_MAX_LENGTH = 1024;	// テキスト属性値の長さNULL文字を含んだ文字数(設定できる文字数は-1)

const int MP_CUSTOMATT_UNKNOWN	= 1;
const int MP_CUSTOMATT_INT		= 2;
const int MP_CUSTOMATT_OCTS		= 4;
const int MP_CUSTOMATT_DATE		= 1000000;
const int MP_CUSTOMATT_BOOL_XD		= 2000000;
const int MP_CUSTOMATT_OTHER	= 3000000;


/*!
@brief ユーザー定義属性構造体

@param	pszName		属性名
@param	type		属性の型
@param	pValue		属性値
@param	valueSize	属性のサイズ(テキストの場合はNULLを含んだサイズ)
*/
typedef struct tag_MP_CustomAttribute {
	MP_Text pszName[CUSTOM_ATT_NAME_LENGTH];
	int type;
	void* pValue;
	int valueSize;
} MP_CustomAttribute;

/*!
@brief ユーザー定義属性取得関数
すべてのユーザー定義属性をまとめて取得する
関数内でpAttributesの領域を確保するので、呼び出し側は不要になったらMPPMDestroyCustomAttributesで破棄する
MP_PtrArrayの生成も関数内で行う

@param	pObj		ユーザー定義属性を取得するMPCObjectのポインタ
@param	ppAttributes	格納する構造体の配列のポインタのポインタ
@return	HRESULT	成功したら0、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetCustomAttributes)(
	MPCObject* pObj, MP_PtrArray** ppAttributes);

/*!
@brief ユーザー定義属性構造体配列破棄関数
すべてのユーザー定義属性をまとめて破棄する
MP_PtrArrayの破棄も関数内で行う

@param	pAttribute	破棄する構造体配列のポインタ
@return	HRESULT	成功したら0、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMDestroyCustomAttributes)(
	MP_PtrArray* pAttributes);

/*!
@brief ユーザー定義属性取得関数
nth番目のユーザー定義属性を取得する

@param	pObj		ユーザー定義属性を取得するMPCObjectのポインタ
@param	order			取得する番号(1起算)
@param	pAttribute	格納する構造体のポインタ
		pAttribute->pValue == NULLのときはpValueのサイズをpAttribute->valueSizeにセットする
@return	HRESULT	成功したら0、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetCustomAttributeByOrder)(
	MPCObject* pObj, int order, MP_CustomAttribute* pAttribute);

/*!
@brief ユーザー定義属性取得関数
属性名pAttribute->pszNameのユーザー定義属性を取得する

@param	pObj		ユーザー定義属性を取得するMPCObjectのポインタ
@param	pAttribute	格納する構造体のポインタ
		pAttribute->pValue == NULLのときはpValueのサイズをpAttribute->valueSizeにセットする
@return	HRESULT	成功したら0、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetCustomAttributeByName)(
	MPCObject* pObj, MP_CustomAttribute* pAttribute);

/*!
@brief ユーザー定義属性の数を取得する

@param	pObj		ユーザー定義属性の数を取得するMPCObjectのポインタ
@return	HRESULT	成功したら属性数、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMGetCustomAttributeNumber)(
	MPCObject* pObj);

/*!
@brief ユーザー定義属性設定関数
pAttributeで指定されたユーザー定義属性を設定する
pAttribute->pValue == NULLのときは属性を削除する

@param	pObj		ユーザー定義属性を取得するMPCObjectのポインタ
@param	pAttribute	格納する構造体のポインタ
@return	HRESULT	成功したら0、失敗したらエラーコード
*/
DLLBINDFUNC_(HRESULT, MPPMSetCustomAttribute)(
	MPCObject* pObj, MP_CustomAttribute* pAttribute);




/*!
@brief プロセスモデルインタフェース

mppmodel.libをリンクしなくてもプロセスモデルの関数を使用できるように、
mpcinterfaceによりプロセスモデルの各関数を利用できるようにする。
このインタフェースはMPCSessionのGetInterface(IID_MPPModelSPI)により取得できる。

@par インタフェースID
mpc_api.h に定義済み
MPC_EXTERN_GUID(IID_MPPModelSPI, 0x1329);

@par メソッド一覧
各メソッドの定義はすべて同名のプロセスモデル関数と同じ動作なので省略
*/
mpinterface MPPModelSPI : public MPCInterface
{
STDMETHOD(MPPMUpdatePages)(MPCSession* session, MPCObject* mp, MPCContDocument* contDoc) PURE;
STDMETHOD(MPPMBreakUpdatePages)(MPCObject* mp, MPCContDocument* contDoc) PURE;
STDMETHOD(MPPMMergeMP)(MPCObject* dst_mp, MPCObject* src_mp, MP_Integer nth = -1) PURE;
STDMETHOD_(MPCObject*, MPPMCreateNewMetaPaper)(MPCSession* session, MP_Octet* name, MP_Dim dim, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMPullOutOnePage)(MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMCopyOnePage)(MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL) PURE;
STDMETHOD(MPPMDIBFileToMetaPaper)(MPCSession* session, const MP_Path* srcPath, const MP_Path* dstPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level) PURE;
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPage)(MPCSession* session, const MP_Path* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPage)(MPCSession* session, const MP_Path* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageAdv)(MPCSession* session, const MP_Path* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMHDIBToBasicPageAdv)(MPCSession* session, void* hDIB, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMTIFFMPFileToBasicPage)(MPCSession* session, MP_File* mpfile, MP_Integer nth, MP_Integer* ppage, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, HRESULT* phres = NULL) PURE;
STDMETHOD_(void*, MPPMConvertBasicPageToHDIB)(MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD(MPPMConvertBasicPageToDIBFile)(MPCSession* session, MPCObject* bp, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD_(void*, MPPMConvertPDToHDIB)(MPCSession* session, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD(MPPMConvertPDToDIBFile)(MPCSession* session, MP_PD* pd, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD_(MPCObject*, MPPM4PullOutOnePage)(MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMDivideAtCurrentPage)(MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL) PURE;
STDMETHOD(MPPMEraseBorder)(MPCSession* session, MPCObject* basicPage, MP_Integer top, MP_Integer bottom, MP_Integer left, MP_Integer right, MP_Integer centerLeft, MP_Integer centerRight, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD(MPPMSetDocumentAttribute)(MPCObject* mp, const char* lpszAttributeName, int nAttributeType, char* pAttributeValue) PURE ;
STDMETHOD(MPPMGetDocumentAttributeNumber)(MPCObject* mp) PURE ;
STDMETHOD(MPPMGetDocumentAttributeByName)(MPCObject* mp, const char* lpszAttributeName, int* nAttributeType, char* pAttributeValue,int nDataSize) PURE ;
STDMETHOD(MPPMGetDocumentAttributeByOrder)(MPCObject* mp, int nOrder, char*lpszAttributeName, int* nAttributeType, char* pAttributeValue, int nDataSize) PURE ;
STDMETHOD(MPPMSucceedAttribute)(MPCObject* mp, DW_refinf* refDWInfo, MP_Integer nSuccession) PURE ;
STDMETHOD_(void*, MPPMConvertBasicPageToHDIBEx)(MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true) PURE;
STDMETHOD(MPPMConvertBasicPageToDIBFileEx)(MPCSession* session, MPCObject* bp, const MP_Path* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true) PURE;
STDMETHOD_(MPCObject*, MPPMDirectImportIMSFileToBasicPage)(MPCSession* session, const MP_Path* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer iRotate, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMConvertIMSFileToBasicPage)(MPCSession* pSession, const MP_Path* pszImsPath, MP_Dim dimPd, MP_Dim dimPage, MP_Pos posPd, MP_Integer iRotate, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo* pCancelInfo = NULL) PURE;
STDMETHOD(MPPMDIBFileToIMSFile)(const MP_Path* pszDibPath, const MP_Path* pszImsPath,	MP_Integer level, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD_(void*, MPPMDIBMemToIMSMem)(const unsigned char* pDibMem, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD(MPPMGetIMSInfo)(const MP_Path* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes) PURE;
STDMETHOD(MPPMGetPDFFromMRCPDPage)(MPCSession* pSession, MPCObject* pPage, const MP_Path* pszDestPath ) PURE;
STDMETHOD_(MP_PD*, MPPMCreatePDfromMemBitmap)(MPCSession* pSession, void* pBmpInfo, unsigned char* pImageData, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo) PURE;
STDMETHOD_(MP_PD*, MPPMCreatePDfromBmpFile)(MPCSession* pSession, const MP_Path* pszBmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo) PURE;
STDMETHOD(MPPMSetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim dimOrgPage, MP_Pos posOrgImage, MP_Dim dimOrgImage ) PURE;
STDMETHOD(MPPMGetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim* pDimOrgPage, MP_Pos* pPosOrgImage, MP_Dim* pDimOrgImage ) PURE;
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRC)( MPCSession* session, const MP_Path* srcPath, MP_Integer iCompLevel, MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo ) PURE;
// V70追加 Unicode版
STDMETHOD_(MPCObject*, MPPMCreateNewMetaPaperW)(MPCSession* session, const MP_Text* name, MP_Dim dim, HRESULT* phres = NULL) PURE;
STDMETHOD(MPPMDIBFileToMetaPaperW)(MPCSession* session, const MP_WPath* srcPath, const MP_WPath* dstPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level) PURE;
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageAdvW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD(MPPMConvertBasicPageToDIBFileW)(MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD(MPPMConvertPDToDIBFileW)(MPCSession* session, MP_PD* pd, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL) PURE;
STDMETHOD(MPPMSetDocumentAttributeW)(MPCObject* mp, const MP_Text* attributeName, int attributeType, const void* pAttributeValue, MP_TAType tatype, int codpage) PURE ;
STDMETHOD(MPPMGetDocumentAttributeByNameW)(MPCObject* mp, const MP_Text* attributeName, int& attributeType, void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage) PURE ;
STDMETHOD(MPPMGetDocumentAttributeByOrderW)(MPCObject* mp, int nOrder, MP_String &attributeName, int& attributeType, void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage) PURE ;
STDMETHOD(MPPMConvertBasicPageToDIBFileExW)(MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true) PURE;
STDMETHOD_(MPCObject*, MPPMDirectImportIMSFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer iRotate, HRESULT* phres = NULL) PURE;
STDMETHOD_(MPCObject*, MPPMConvertIMSFileToBasicPageW)(MPCSession* pSession, const MP_WPath* imsPath, MP_Dim dimPd, MP_Dim dimPage, MP_Pos posPd, MP_Integer iRotate, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo* pCancelInfo = NULL) PURE;
STDMETHOD(MPPMDIBFileToIMSFileW)(const MP_WPath* dibPath, const MP_WPath* imsPath, MP_Integer level, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD(MPPMGetIMSInfoW)(const MP_WPath* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes) PURE;
STDMETHOD(MPPMGetPDFFromMRCPDPageW)(MPCSession* pSession, MPCObject* pPage, const MP_WPath* destPath ) PURE;
STDMETHOD_(MP_PD*, MPPMCreatePDfromBmpFileW)(MPCSession* pSession, const MP_WPath* bmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo) PURE;
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRCW)( MPCSession* session, const MP_WPath* srcPath, MP_Integer iCompLevel, MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo ) PURE;
// V70 ユーザー定義属性追加
STDMETHOD(MPPMGetCustomAttributes)(MPCObject* pObj, MP_PtrArray** ppAttributes) PURE;
STDMETHOD(MPPMDestroyCustomAttributes)(MP_PtrArray* pAttributes) PURE;
STDMETHOD(MPPMGetCustomAttributeByOrder)(MPCObject* pObj, int order, MP_CustomAttribute* pAttribute) PURE;
STDMETHOD(MPPMGetCustomAttributeByName)(MPCObject* pObj, MP_CustomAttribute* pAttribute) PURE;
STDMETHOD(MPPMGetCustomAttributeNumber)(MPCObject* pObj) PURE;
STDMETHOD(MPPMSetCustomAttribute)(MPCObject* pObj, MP_CustomAttribute* pAttribute) PURE;
};

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // MPPMODEL_H 

// CHANGE LOG
// 96.2.26 - Nagano - 生成
// 96.7.03 - Nagano - MPPMMergeMP(）変更，MPPMDIBFileToMetaPaper() MPPMDIBFileToBasicPage()追加
// 97.1.21 - Nagano - MPPMPullOutOnePage() MPPMCopyOnePage() のコメントを削除
// 97.9.17 - Sumida - MPPMDIBFileToMetaPaper(), MPPMDIBFileToBasicPage()に引数levelを追加
//						& MPPMJPEGFileToBasicPage()を追加定義
// 99.5.17 - Ichiriki - V4 追加分 MPPM4PullOutOnePage() の定義と 仕様の追記
// 99.5.18 - Nakazawa - V4 追加分実装
// 99.5.27 - Nakazawa - ConvertPDToDIBの仕様変更
// 99.6.10 - Nakazawa - windows.h のインクルードをやめ、HGLOBAL を void* に変更
// 99.9.3 - Ichiriki - コメント修正：バインダは対象外,MP_E_ACCESSDENIEDをMP_E_NOPERMISSIONに変更
// 99.9.22 - Nakazawa - コメント修正：MMR取り込みの圧縮率を30%に修正
// 00.9.25 - Nakazawa - V4.1 表示ページで分割改善、わく消しコア化の関数追加
// 00.9.26 - Nakazawa - V4.1 CopyOnePageをバインダーで使用できるように関数説明を修正
// 00.9.26 - Nakazawa - V4.1 コアI/F用 MPPModelSPI 追加
// 00.9.29 - Tashiro - V4.1 イメージPD生成系の関数で引数levelの意味拡張に伴いコメント追加
// 00.10.12 - Nakazawa - V4.1 コードレビューの結果を反映
// 2001.12.06 - Ichikawa - V5.0 白黒 1bit 高画質イメージ出力、文書属性・アノテーション継承 追加
// 2002.07.18 - Nakazawa - V5.0 AR7859対応 イメージ変換にアノテ有無フラグを追加
// ---V6開発
// 2004.05.21 - Tashiro - V6.0 MRC関連I/F追加
// 2004.06.08 - Tashiro - V6.0 MPPMDirectImportIMSFileToBasicPageの不要引数を削除
// 2004.07.30 - Tashiro - V6.0 AR10336 (API)MRC-PDページからPDFを取り出す機能の追加
// 2004.07.30 - Tashiro - V6.0 AR10117 BMPからMRC-PD化も含めてPD生成する機能を共通化
// 2004.08.03 - Tashiro - V6.0 AR9966 関連 MPPMCreatePDfromBmpFile()引数変更
// 2004.08.10 - Tashiro - V6.0新規追加関数をインタフェース・クラスにも追加
// 2004.10.07 - Tashiro - AR11341 元のPDFのページレイアウト情報をset/getする関数を追加
// 2004.10.07 - Tashiro - AR11303 JPEGのMRC変換を試み失敗したら直接取り込む関数を追加
// 2004.10.18 - Tashiro - AR11421 PDFの回転状態をDWページに反映させるための機能追加
// ---V70開発
// 2007.08.06 - Komoda - ヘッダファイルのdoxygen対応
// 2007.08.07 - Komoda - Unicode I/Fの追加
// 2008.01.11 - Tashiro - MPPMConvertBasicPageToHDIBCentiDPIを追加
// 2008.01.17 - Kudo - ユーザー定義属性I/Fの追加
// 2008.03.13 - Tashiro - AR14268 MPPMConvertBasicPageToHDIBCentiDPIに白枠を付けない機能を追加
// 2008.05.27 - Tashiro - AR14867 MPPMConvertBasicPageToHDIBCentiDPIに17%と同様の画質で描画する引数を追加
