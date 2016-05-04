// File: IMSUtil.h
// Authors: Kiyoshi Tashiro
// Copyright (C) 2004 by Fuji Xerox Co., Ltd. All rights reserved.

// IMSフォーマットを扱うクラスを定義する。
// CImsDefs : IMS関連の定数定義のみのクラス
// CImsDataRead : メモリまたはファイル上のIMSフォーマットを読み出すためのクラス。
// CImsObject : IMS中の各オブジェクトの情報を読み出すためのクラス。

#ifndef __MRCUTIL_H__
#define __MRCUTIL_H__

//07.09.19 - M.Chikyu UNICODE対応
#include "mpc_api.h"

//#include <windows.h>
#include "win2mpf.h"

/// CImsDefsクラス
/// IMSデータの解釈、生成に必要な定数を収めるためだけのクラス
class CImsDefs
{
public:
	/// IMS内の各オブジェクトのタイプを表す定数
	typedef enum {
		/// 不透明なcontone画像 (8 or 24bpp)
		contone_object = 1,
		/// マスク。次のオブジェクトはcontone_objectでなければならない。
		/// このマスクと次のオブジェクトで、masked imageとして扱われる。
		contone_mask   = 2,
		/// マスク。1はカレントカラーで塗られ、0は透明(現状に影響を与えない)
		color_mask     = 3,
		/// 色付きの矩形
		color_rect     = 4,
		/// JBIG2辞書。1ファイルに1つのみ。
		JBIG2_dict     = 5,
		/// サムネイル。
		thumbnail      = 6,
		/// 不透明な2値画像
		binary_object  = 7,
		/// 最終オブジェクト。numObjectのみが続く特殊なオブジェクト。
		trailer_object = 0xDEADFEED,
		/// エラーを表す値。(IMSフォーマットで定義された値ではない)
		IMS_ObjectTypeERROR = -1
	} IMS_ObjectType;

	/// IMS内の各オブジェクトの圧縮種別を表す定数
	typedef enum {
		RAW_pix_intl   = 1, ///< 画素単位のインターリーブ
		RAW_scn_intl   = 2, ///< スキャンライン単位のインターリーブ
		RAW_pln_intl   = 3, ///< 面単位のインターリーブ
		G3MH           = 16,
		G4MMR          = 17,
		JBIG2          = 18,
		XLZ            = 19, ///< Xerox内部の固有形式
		FX_ALLA        = 20, ///< FX拡張
		JPEG           = 32,
		JPEG2000       = 33,
		FX_ABMC        = 34, ///< FX拡張
		oldALLA        = 99, ///< ClientMRCから受け取る場合にのみ用いる。IMS仕様では未定義
		FX_ALLA_old_def = 16384, ///< FX拡張 (0x4000) 一時期定義されたので念のため対応する
		FX_ABMC_old_def = 16385, ///< FX拡張 (0x4001) 一時期定義されたのみ。
		IMS_CompressionTypeERROR = -1 ///< エラーを表す値。(IMSフォーマットで定義された値ではない)
	} IMS_CompressionType;

	/// IMS内の各オブジェクトの色空間を表す定数
	typedef enum {
		binary_one_is_black = 1, ///< 2値空間
		binary_one_is_white = 2,
		deviceGray          = 16, ///< 8bppグレー空間
		linearY             = 17,
		sY                  = 18,
		ITU_LStar           = 19,
		CIE_LStar           = 20,
		FX_LStar            = 21,
		deviceRGB           = 32, ///< 24bppカラー空間
		sRGB                = 33,
		linearSRGB          = 34,
		ITULAB              = 35,
		CIELAB              = 36,
		FXLAB               = 37,
		YCbCr               = 38,
		sYCC                = 39,
		IMS_ColorSpaceERROR = -1  ///< エラーを表す値。(IMSフォーマットで定義された値ではない)
	} IMS_ColorSpace;

protected:
	enum {
		MY_CAPABLE_IMS_VERSION = 0x10000
	};
	enum {
		IMS_ROOT_HEADER_BYTES = 28
	};
	enum {
		IMS_ROOT_HEADER_MAGIC_POS = 0,
		IMS_ROOT_HEADER_VERSION_POS = 4,
		IMS_ROOT_HEADER_XDIM_POS = 8,
		IMS_ROOT_HEADER_YDIM_POS = 12,
		IMS_ROOT_HEADER_XRES_POS = 16,
		IMS_ROOT_HEADER_YRES_POS = 20,
		IMS_ROOT_HEADER_SUBSAMPLIG_POS = 24
	};

	enum {
		IMS_OBJECT_HEADER_BYTES = 68
	};
	enum {
		IMS_OBJECT_HEADER_TYPE_POS = 0,
		IMS_OBJECT_HEADER_XPOS_POS = 4,
		IMS_OBJECT_HEADER_YPOS_POS = 8,
		IMS_OBJECT_HEADER_XDIM_POS = 12,
		IMS_OBJECT_HEADER_YDIM_POS = 16,
		IMS_OBJECT_HEADER_W_POS = 20,
		IMS_OBJECT_HEADER_H_POS = 24,
		IMS_OBJECT_HEADER_BYTES_PER_SCANLINE_POS = 28,
		IMS_OBJECT_HEADER_COMPRESSION_POS = 32,
		IMS_OBJECT_HEADER_COLOR_SPACE = 36,
		IMS_OBJECT_HEADER_WHITE_SEP_1_POS = 40,
		IMS_OBJECT_HEADER_WHITE_SEP_2_POS = 44, // AR14191 WhiteSep2位置の誤りを修正
		IMS_OBJECT_HEADER_WHITE_SEP_3_POS = 48, // AR14191 WhiteSep3位置の誤りを修正
		IMS_OBJECT_HEADER_SEP_1_POS = 52,
		IMS_OBJECT_HEADER_SEP_2_POS = 56,
		IMS_OBJECT_HEADER_SEP_3_POS = 60,
		IMS_OBJECT_HEADER_NUMBYTES_POS = 64,
	};
};

/// CImsHeader
/// IMSヘッダを読み書きするクラス
class CImsHeader : public CImsDefs
{
public:
	CImsHeader();

	int GetSize() const;
	void CopyData( unsigned char* pDstMem ) const;

	DWORD GetVersion() const;
	DWORD GetPixelsX() const;
	DWORD GetPixelsY() const;
	DWORD GetPixPerInchX() const;
	DWORD GetPixPerInchY() const;
	DWORD GetSubSampling() const;
	void SetVersion( DWORD dwVersion );
	void SetPixelsX( DWORD dwPixelsX );
	void SetPixelsY( DWORD dwPixelsY );
	void SetPixPerInchX( DWORD dwPixPerInchX );
	void SetPixPerInchY( DWORD dwPixPerInchY );
	void SetSubSampling( DWORD dwSubSampling );

private:
	static DWORD FourBytesToDWORD( const unsigned char* pByte );
	static void DWORDToFourBytes( DWORD dwData, unsigned char* pByte );

	DWORD m_dwVersion;
	DWORD m_dwPixelsX;
	DWORD m_dwPixelsY;
	DWORD m_dwPixPerInchX;
	DWORD m_dwPixPerInchY;
	DWORD m_dwSubSampling;
};
/// CImsHeader
/// IMSヘッダを読み書きするクラス
class CImsObjectHeader : public CImsDefs
{
public:
	CImsObjectHeader();

	int GetSize() const;
	void CopyData( unsigned char* pDstMem ) const;

	DWORD GetType() const;
	DWORD GetXPos() const;
	DWORD GetYPos() const;
	DWORD GetXDim() const;
	DWORD GetYDim() const;
	DWORD GetH() const;
	DWORD GetW() const;
	DWORD GetBytesPerScanline() const;
	DWORD GetCompression() const;
	DWORD GetColorSpace() const;
	DWORD GetWhiteSep1() const;
	DWORD GetWhiteSep2() const;
	DWORD GetWhiteSep3() const;
	DWORD GetSep1() const;
	DWORD GetSep2() const;
	DWORD GetSep3() const;
	DWORD GetNumBytes() const;
	void SetType( DWORD dwType );
	void SetXPos( DWORD dwXPos );
	void SetYPos( DWORD dwYPos );
	void SetXDim( DWORD dwXDim );
	void SetYDim( DWORD dwYDim );
	void SetH( DWORD dwH );
	void SetW( DWORD dwW );
	void SetBytesPerScanline( DWORD dwBytesPerScanline );
	void SetCompression( DWORD dwCompression );
	void SetColorSpace( DWORD dwColorSpace );
	void SetWhiteSep1( DWORD dwWhiteSep1 );
	void SetWhiteSep2( DWORD dwWhiteSep2 );
	void SetWhiteSep3( DWORD dwWhiteSep3 );
	void SetSep1( DWORD dwSep1 );
	void SetSep2( DWORD dwSep2 );
	void SetSep3( DWORD dwSep3 );
	void SetNumBytes( DWORD dwNumBytes );

private:
	static DWORD FourBytesToDWORD( const unsigned char* pByte );
	static void DWORDToFourBytes( DWORD dwData, unsigned char* pByte );

	DWORD m_dwType;
	DWORD m_dwXPos;
	DWORD m_dwYPos;
	DWORD m_dwXDim;
	DWORD m_dwYDim;
	DWORD m_dwH;
	DWORD m_dwW;
	DWORD m_dwBytesPerScanline;
	DWORD m_dwCompression;
	DWORD m_dwColorSpace;
	DWORD m_dwWhiteSep1;
	DWORD m_dwWhiteSep2;
	DWORD m_dwWhiteSep3;
	DWORD m_dwSep1;
	DWORD m_dwSep2;
	DWORD m_dwSep3;
	DWORD m_dwNumBytes;
};


/// CImsDataReadクラス
/// IMSデータから情報を読み出すためのクラス
class CImsDataRead : public CImsDefs
{
public:
	/// CImsObjectローカルクラス
	/// IMSデータ中の各オブジェクトを表すクラス
	class CImsObject
	{
	public:
		/// オブジェクトタイプを得る。
		/// @return オブジェクトタイプ。
		CImsDefs::IMS_ObjectType GetType() const;
		/// 圧縮種別を得る。
		/// @return 圧縮種別。
		CImsDefs::IMS_CompressionType GetCompressionType() const;
		/// オブジェクトが全体画像内で貼られる位置のX座標を得る。
		/// @return X座標。全体画像のピクセルで表現。
		DWORD GetPositionX() const;
		/// オブジェクトが全体画像内で貼られる位置のY座標を得る。
		/// @return Y座標。全体画像のピクセルで表現。
		DWORD GetPositionY() const;
		/// オブジェクトが全体画像内で貼られる幅を得る。
		/// @return 幅。全体画像のピクセルで表現。
		DWORD GetPixelsX() const;
		/// オブジェクトが全体画像内で貼られる高さを得る。
		/// @return 高さ。全体画像のピクセルで表現。
		DWORD GetPixelsY() const;
		/// オブジェクト自身の幅を得る。
		/// @return 幅。ピクセルで表現。
		DWORD GetSizeX() const;
		/// オブジェクト自身の高さを得る。
		/// @return 高さ。ピクセルで表現。
		DWORD GetSizeY() const;
		/// オブジェクトの色空間を得る。
		/// @return 色空間。
		CImsDefs::IMS_ColorSpace GetColorSpace() const;
		/// オブジェクトの色を得る。
		/// @return 色。GetColorSpaceで得られる色空間で表現される。
		DWORD GetColor() const;
		/// オブジェクトの画像データの大きさを得る。
		/// @return 大きさ。バイト数で表現。
		DWORD GetImageDataBytes() const;
		/// オブジェクトの画像データの先頭ポインタを得る。
		/// @return 先頭ポインタ。
		unsigned char* GetImageData() const;
		/// 自分の次のオブジェクトを得る。
		/// @return 次のオブジェクト。
		CImsObject GetNextObject() const;
		/// 画像がカラーか調べる。
		/// @return カラーならば非0値。グレー/白黒なら0。
		BOOL_XD IsColor() const;
		/// 先頭ポインタを引数に取るコンストラクタ。
		/// @param iBytesToImsEnd Ims全体の終端までのバイト数。
		/// @param pObjectTop オブジェクトのデータが始まる先頭ポインタ。
		CImsObject( long int iBytesToImsEnd, unsigned char* pObjectTop );
		/// 自分と同じヘッダ情報をもつCImsObjectHeaderを返す。
		CImsObjectHeader GetHeader() const;
		/// デコンストラクタ。
		virtual ~CImsObject();
	private:
		/// YCCの色値をRGBに変換する。
		/// @param dwYCC YCC色値。
		/// @return RGB色値。
		static DWORD YCCtoRGB( DWORD dwYCC );
		/// カラースペースを考慮して色値を読み出す。
		/// @return 読み出した色値。
		DWORD ReadColorConsideringColorSpace() const;
		/// 自分のデータが始まるポインタ。
		const unsigned char* m_pTop;
		long m_iBytesLeft;
	};

	friend class CImsObject;

public:
	/// ファイルパスを引数に取るコンストラクタ。
	/// @param pszFilePath ファイルパス。
	CImsDataRead( const char* pszFilePath );
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	CImsDataRead( const MP_WPath* pszFilePathW );

	/// 先頭ポインタを引数に取るコンストラクタ。
	/// @param iMemorySize オブジェクトのデータのバイト数。
	/// @param pMemory オブジェクトのデータが始まる先頭ポインタ。
	CImsDataRead( long int iMemorySize, const unsigned char* pMemory );
	/// デストラクタ。
	virtual ~CImsDataRead();

	/// IMSフォーマットバージョンを得る。
	/// @return フォーマットバージョン。
	DWORD GetVersion() const;
	/// IMS画像全体の幅を得る。
	/// @return 幅。ピクセルで表される。
	DWORD GetPixelsX() const;
	/// IMS画像全体の高さを得る。
	/// @return 高さ。ピクセルで表される。
	DWORD GetPixelsY() const;
	/// IMS画像全体のX方向の解像度を得る。
	/// @return X方向の解像度。ピクセル/インチで表される。
	DWORD GetPixPerInchX() const;
	/// IMS画像全体のY方向の解像度を得る。
	/// @return Y方向の解像度。ピクセル/インチで表される。
	DWORD GetPixPerInchY() const;
	/// サブサンプリング値を得る。
	/// @return サブサンプリング値。
	DWORD GetSubSampling() const;
	/// IMS画像内のオブジェクトの数を得る。
	/// サムネイルやJBIG2辞書など描画されないオブジェクトもカウントされる。
	/// @return オブジェクト数。最後のdeadfeadオブジェクトは数えない。
	int GetNumObjects() const;
	/// IMS画像内で描画されるオブジェクトの数を得る。
	/// @return オブジェクト数。最後のdeadfeadオブジェクトは数えない。
	int GetNumDrawableObjects() const;
	/// IMS画像内の先頭オブジェクトを得る。
	/// @return 先頭オブジェクト。
	CImsObject GetFirstObject() const;
	/// IMS画像内のNth番目オブジェクトを得る。
	/// @param iNth 何番目か。0から始まる。
	/// @return オブジェクト。
	CImsObject GetNthObject( int iNth ) const;
	/// IMS全体としてカラーか調べる。
	/// @return カラーならば非0値。グレー/白黒なら0。
	BOOL_XD IsColor() const;
	/// IMS全体のデータサイズを得る。
	/// @return データサイズ(バイト)。
	long int GetTotalSize() const;
	/// IMS全体のデータをコピーする。
	/// @param pDstMem コピー先の先頭ポインタ。
	void CopyTotalData( unsigned char* pDstMem ) const;
	/// 自分と同じヘッダ情報をもつCImsHeaderを返す。
	CImsHeader GetHeader() const;

	/// 最新のエラー値を得る。
	/// @return mpc_api.hで定義されるエラー値。
	HRESULT GetLastMPCError() const;

private:
	void VerifyIMSRootHeader();
	static DWORD FourBytesToDWORD( const unsigned char* pByte );

	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	void InitObject( const MP_WPath* pszFilePathW );

	HANDLE m_hFile;
	HANDLE m_hFileMapping;
	unsigned char* m_pMappedMemory;
	const unsigned char* m_pMemory;
	long int m_iLastMPCError;
	unsigned char* m_pRootHeader;
	DWORD m_dwVersion;
	long int m_iTotalSize;

};


#endif // __MRCUTIL_H__


//CHANGE LOG
//2004.04.07 - Tashiro - 新規作成(V6)
//2004.04.28 - Tashiro - CImsDataRead拡張、IMS仕様拡張への対応
//2004.06.07 - Tashiro - ヘッダ、オブジェクトヘッダの操作クラス追加
//2004.07.29 - Tashiro - AR9314 ALLA/ABMCの定数変更に対応
