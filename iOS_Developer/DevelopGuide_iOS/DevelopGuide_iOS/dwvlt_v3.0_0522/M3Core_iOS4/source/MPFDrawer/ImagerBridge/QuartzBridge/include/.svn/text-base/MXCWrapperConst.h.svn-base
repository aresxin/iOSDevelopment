//
//  MXCWrapperConst.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
*	MXCWrapperConst.h
*
*	DWCOREとU/Iとのやり取りで使用する定数を定義する。
*/

// ラッパーのメソッドの返り値
// 今後増える可能性あり。
#define MXC_OK				0       // OK
#define	MXC_ERROR			-1		// その他エラー
#define MXC_AUTH_FAILED		1		// 認証失敗(ファイルオープンの際)
#define MXC_AUTH_NEEDED		2       // 認証が必要である
#define MXC_VER_ERROR		3       // 文書のバージョンエラー
#define MXC_ACCESSDENIED	4		// ファイルのアクセス権がない

#define MXC_TRUE			1
#define MXC_FALSE			0

// MXCImage : 描画オブジェクトの種類
#define MXC_IMAGE_RASTER	1	//ラスタ画像
#define MXC_IMAGE_EMF		2	//EMF画像
#define MXC_IMAGE_WMF		3	//WMF画像

// MXCImagePD : PDの種類
#define MXC_PD_IMAGE_V2_OKD	1	//V2 無圧縮フォーマット BMPPDSeed
#define MXC_PD_IMAGE_MH		2	//MHフォーマット BMPMHPDSeed or MHPDSeed
#define MXC_PD_IMAGE_MMR	3	//MMRフォーマット MMRPDSeed
#define MXC_PD_IMAGE_JPEG	4	//JPEGフォーマット JpegPDSeed
#define MXC_PD_IMAGE_OKD	5	//OKDフォーマット OKDPDSeed
#define MXC_PD_IMAGE_ADP	6	//ALLAフォーマット ADPPDSeed
#define MXC_PD_IMAGE_EMF	7	//EMFフォーマット
#define MXC_PD_IMAGE_WMF	8	//WMFフォーマット
#define MXC_PD_IMAGE_MRC	9	//MRCフォーマット MrcPDSeed
#define MXC_PD_UNKNOWN		-1	//タイプ不明

// MXCRasterImage : bitmapLine() の返り値
#define MXC_PD_GETLINE_CONTINUE	0	// まだラインはある
#define MXC_PD_GETLINE_COMPLETE	1	// もう返すラインは残っていない
#define MXC_PD_GETLINE_ERROR	-1	// 何かエラー発生 or not implemented

// MXCAnnotation : アノテーションの種類
#define MXC_ANNOTATION_LABEL	0	//付箋
#define MXC_ANNOTATION_DEFAULT	1	//デフォルト (旧：線)DWVLT70 V7Format 2008.09.18 by marumo 
#define MXC_ANNOTATION_TEXT		2	//テキスト
#define MXC_ANNOTATION_LINK		3	//リンク
#define MXC_ANNOTATION_IMAGE	4	//ラスタ画像
#define MXC_ANNOTATION_CUSTOM	5	//カスタムアノテーション since DWVLT70 V7Format 2008.07.14 by akiyoshi
#define MXC_ANNOTATION_GROUP	6	//グループアノテーション since DWVLT70 V7Format 2008.07.14 by akiyoshi

// MXCLinkAnnotation : リンクアノテーションの種別
#define MXC_LINK_TO_MYPAGE		0	//同じ文書内のページ
#define MXC_LINK_TO_MYDOC		1	//同じ文書内の別内部文書のページ
#define MXC_LINK_TO_MYLINK		2	//同じ文書内のリンクアノテーションのタイトル
#define MXC_LINK_TO_XDW			3	//別文書
#define MXC_LINK_TO_URL			4	//URL
#define MXC_LINK_TO_OTHERFILE   5	//別のファイル
#define MXC_LINK_TO_MAIL		6	//メールアドレス
#define MXC_LINK_UNKNOWN		-1	//リンクできない

// MXCDefaultAnnotation : 線アノテーションの種別
#define MXC_LINEANN_STROKE		0	//自由曲線
#define MXC_LINEANN_LINE		1	//直線
#define MXC_LINEANN_RECT		2	//矩形
#define MXC_LINEANN_ARC			3	//楕円
#define MXC_LINEANN_POLIGON		4	//多角形
#define MXC_LINEANN_STAMP		5	//スタンプ
#define MXC_LINEANN_SIGNATURE   6	//署名
#define MXC_LINEANN_OLE			7	//OLE
#define MXC_LINEANN_OTHER		-1	//その他

// MXCSecurity : セキュリティの種別
#define MXC_SECURITY_NONE		0	//保護されていない
#define MXC_SECURITY_PSWD		1	//64bitパスワードによる保護
#define MXC_SECURITY_PSWD128	2	//128bitパスワードによる保護
#define MXC_SECURITY_DDSA		3	//ver.4 DDSAによる保護

// MXCPage : ページ情報(オリジナル種別)
#define MXC_PAGE_ORIG_APP		0	//アプリケーション文書
#define MXC_PAGE_ORIG_IMG		1	//イメージ文書
#define MXC_PAGE_ORIG_ETC		2	//その他

// MXCPage : 色数
#define MXC_DEPTH_LEVEL1        1   //"2色（モノクローム）"
#define MXC_DEPTH_LEVEL4        2   //"16色"
#define MXC_DEPTH_LEVEL8        3   //"256色"
#define MXC_DEPTH_LEVEL16       4   //"32768色"
#define MXC_DEPTH_LEVEL24       5   //"16777216色"
#define MXC_DEPTH_LEVEL32       6   //"4294967296色"


// MXCPage : ページ情報(解像度)
#define MXC_PAGE_RES_FAX_STD		0	//ファックス標準
#define MXC_PAGE_RES_FAX_HIGH		1	//ファックス高画質(200dpi)
#define MXC_PAGE_RES_FAX_SUPER_HIGH 2	//ファックス高画質(200x400dpi)
#define MXC_PAGE_RES_ETC			3	//その他(解像度を直接表示する)
#define MXC_PAGE_RES_UNKNOWN		4	//不明

// MXCPage : ページ情報(圧縮モード)
#define MXC_PAGE_COMP_HIGH		0	//JPEG圧縮(圧縮率優先)
#define MXC_PAGE_COMP_STD		1	//JPEG圧縮(標準)
#define MXC_PAGE_COMP_LOW		2	//JPEG圧縮(画質優先)
#define MXC_PAGE_COMP_NONE		3	//画像劣化なし
#define MXC_PAGE_COMP_JPEG		4	//JPEG圧縮(その他)
#define MXC_PAGE_COMP_MRCHIGH   5	//MRC圧縮(圧縮率優先)
#define MXC_PAGE_COMP_MRCSTD	6	//MRC圧縮(標準)
#define MXC_PAGE_COMP_MRCLOW	7	//MRC圧縮(画質優先)
#define MXC_PAGE_COMP_MRCOTHER  8	//MRC圧縮(その他)

// MXCDocument/MXCBinder : ページサイズ／バインダーサイズ
// 用紙幅、高さ
// DWVLT70 PaperSize 2008.09.27 by marumo <<--
#define _L2A0LENGTH		237800
#define	_L2A0WIDTH		84100
#define	A0LENGTH		118900
#define	A0WIDTH			84100
#define	A1LENGTH		84100
#define	A1WIDTH			59400
#define	A2LENGTH		59400
#define	A2WIDTH			42000
// -->>
#define	A3LENGTH		42000
#define	A3WIDTH			29700
#define	A4LENGTH		29700
#define	A4WIDTH			21000
#define	A5LENGTH		21000
#define	A5WIDTH			14800
#define	B4LENGTH		36400
#define	B4WIDTH			25700
#define	B5LENGTH		25700
#define	B5WIDTH			18200
#define	LETTERLENGTH	27900
#define	LETTERWIDTH		21600
#define	LEGALLENGTH		35600
#define	LEGALWIDTH		21600
#define HAGAKILENGTH	14800
#define HAGAKIWIDTH		10000
// added by M.Futamata at 05/12/27
#define FOLIOLENGTH		33000
#define FOLIOWIDTH		21600
#define PAKAILENGTH		38900
#define PAKAIWIDTH		26700
#define LEDGERLENGTH	43200
#define LEDGERWIDTH		27900
#define _9X11LENGTH		27900
#define _9X11WIDTH		22900
#define _16KLENGTH		26700
#define _16KWIDTH		19400
// --

// 用紙定数
#define MXC_PAPER_INVALID			-1		// 不正な用紙
#define MXC_PAPER_USER_DEFINE		0		// ユーザ定義
#define MXC_PAPER_NO_PAGE			1		// 紙片無し？
#define MXC_PAPER_A3_PORTRAIT		2		// A3たて
#define MXC_PAPER_A3_LANDSCAPE		3		// A3よこ
#define MXC_PAPER_A4_PORTRAIT		4		// A4たて
#define MXC_PAPER_A4_LANDSCAPE		5		// A4よこ
#define MXC_PAPER_A5_PORTRAIT		6		// A5たて
#define MXC_PAPER_A5_LANDSCAPE		7		// A5よこ
#define MXC_PAPER_B4_PORTRAIT		8		// B4たて
#define MXC_PAPER_B4_LANDSCAPE		9		// B4よこ
#define MXC_PAPER_B5_PORTRAIT		10		// B5たて
#define MXC_PAPER_B5_LANDSCAPE		11		// B5よこ
#define MXC_PAPER_LETTER_PORTRAIT	12		// レターたて
#define MXC_PAPER_LETTER_LANDSCAPE  13		// レターよこ
#define MXC_PAPER_LEGAL_PORTRAIT	14		// リーガルたて
#define MXC_PAPER_LEGAL_LANDSCAPE	15		// リーガルよこ
#define MXC_PAPER_HAGAKI_PORTRAIT	16		// はがきたて
#define MXC_PAPER_HAGAKI_LANDSCAPE  17		// はがきよこ
#define MXC_PAPER_BINDER_PAGE_FIT	18		// ページ最大サイズ
// added by M.Futamata at 05/12/27
#define MXC_PAPER_FOLIO_PORTRAIT	19		// フォリオたて
#define MXC_PAPER_FOLIO_LANDSCAPE	20		// フォリオよこ
#define MXC_PAPER_PAKAI_PORTRAIT	21		// パーカイたて
#define MXC_PAPER_PAKAI_LANDSCAPE	22		// パーカイよこ
#define MXC_PAPER_LEDGER_PORTRAIT	23		// レジャーたて
#define MXC_PAPER_LEDGER_LANDSCAPE	24		// レジャーよこ
#define MXC_PAPER_9X11_PORTRAIT		25		// 9x11"たて
#define MXC_PAPER_9X11_LANDSCAPE	26		// 9x11"よこ
#define MXC_PAPER_16K_PORTRAIT		27		// 16開たて
#define MXC_PAPER_16K_LANDSCAPE		28		// 16開よこ
// --
// DWVLT70 PaperSize 2008.09.26 by marumo <<--
#define MXC_PAPER_L2A0_PORTRAIT		29		// 2A0長尺たて
#define MXC_PAPER_L2A0_LANDSCAPE	30		// 2A0長尺よこ
#define MXC_PAPER_A0_PORTRAIT		31		// A0たて
#define MXC_PAPER_A0_LANDSCAPE		32		// A0よこ
#define MXC_PAPER_A1_PORTRAIT		33		// A1たて
#define MXC_PAPER_A1_LANDSCAPE		34		// A1よこ
#define MXC_PAPER_A2_PORTRAIT		35		// A2たて
#define MXC_PAPER_A2_LANDSCAPE		36		// A2よこ
// -->>

// dwvlt_win/include/textcmmn.h より流用
// フォントスタイル定数
#define MXC_STYLE_ITALIC_FLAG			1
#define MXC_STYLE_BOLD_FLAG				2
#define MXC_STYLE_UNDERLINE_FLAG		4
#define MXC_STYLE_STRIKEOUT_FLAG		8
