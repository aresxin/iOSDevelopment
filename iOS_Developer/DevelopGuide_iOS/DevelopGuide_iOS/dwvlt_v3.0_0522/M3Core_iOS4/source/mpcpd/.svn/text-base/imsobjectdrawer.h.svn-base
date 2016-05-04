// File: IMSObjectDrawer.h
// Authors: Kiyoshi Tashiro
// Copyright (C) 2004 by Fuji Xerox Co., Ltd. All rights reserved.

// IMSフォーマット中の1つのオブジェクトを描画するクラス
// CImsObjectDrawerを定義する。

#ifndef __IMSOBJECTDRAWER_H__
#define __IMSOBJECTDRAWER_H__

#include "imsutil.h"

/// CImsObjectDrawerクラス
/// IMSオブジェクトのデコード、描画を行うクラス
class CImsObjectDrawer
{
public:
	/// デコード可能なオブジェクトか確認する。
	/// @return デコード可能ならMP_NOERROR、不可なら負の値。
	HRESULT AssertDecodable();
	/// 持っているオブジェクトのタイプを得る。
	/// @return オブジェクトのタイプ。
	CImsDefs::IMS_ObjectType GetObjectType() const;
	/// マスク用ラインデータを渡すポインタをセットする。
	/// @param pMaskLine マスク用のデータを渡すポインタ。
	///< NULL以外がセットされると、渡されたマスクが1の画素のみ描画する。
	/// @return エラーコード。
	HRESULT SetMaskLine(unsigned char* pMaskLine);

	/// 描画開始前の初期化処理をする。
	/// @param rootDim MRC画像全体のサイズ(ピクセル数)。
	///< この範囲をはみ出すオブジェクトはクリップして描画される。
	/// @param destPos デコードされた画像を貼る位置(MRC全体中のピクセル数)。
	/// @param destDim デコードされた画像を貼るサイズ(MRC全体中のピクセル数)。
	/// @param wantDim 最終的に利用されるMRC画像の中での、そのオブジェクトのサイズ(ピクセル数)。
	///< このサイズを参考に、JPEGで1/2、1/4、1/8デコードするなど描画の最適化を行う。
	/// @param HDC 最終的に描画したいデバイスコンテキストのハンドル。
	///< デバイスコンテキストの色数などを参考に、
	///< JPEGでグレースケールでデコードするなど描画の最適化を行う。
	/// @return エラーコード。
	HRESULT BeginGetLine(MP_Dim rootDim, MP_Pos destPos, MP_Dim destDim, MP_Dim wantDim, HDC_XD hdc, MP_Integer degree, int iPercent, MP_Integer iWantDepth);
	/// 1ライン分描画する。
	/// @param pDestBuff 描画データを書き込むポインタ。
	/// @return エラーコード。
	IDecoder::DecodeResult GetLine(unsigned char* pDestBuff);
	/// 描画の終了処理をする。
	/// @param
	/// @return
	void EndGetLine();

	/// オブジェクト間で共有するデータをセットする。JBIG2の辞書データ用。
	/// @param iDataLength データのバイト数。
	/// @param pData データの先頭ポインタ。
	/// @return エラーコード。
	HRESULT SetGlobalData(MP_Integer iDataLength, unsigned char* pData);

	/// コンストラクタ。
	/// @param pIms IMS全体のデータ。
	/// @param iNth 描画するオブジェクトの指定。0から初めてiNth番目のオブジェクト。
	CImsObjectDrawer( CImsDataRead* pIms, int iNth );
	/// デストラクタ。
	/// @param
	/// @return
	virtual ~CImsObjectDrawer();

private:
	/// CLineAdder 内部クラス
	/// 1ライン分のデコード結果を描画する
	class CLineAdder
	{
	public:
		CLineAdder( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual ~CLineAdder();
		virtual HRESULT AddLine(unsigned char* pDestBuff) = 0;
		HRESULT InitCommon(MP_Dim rootDim, MP_Pos destPos, MP_Dim destDim, BITMAPINFO* pBmpInfo, MP_Integer iWantDepth);
		virtual HRESULT SetMaskLine(unsigned char* pMaskLine);

		virtual HRESULT SetupDotTransferTable() = 0;
		HRESULT SetLineBuffer( unsigned char* pLineBuffer );

		typedef HRESULT ( __stdcall AddLineFuncType)(CLineAdder* pMe, unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc() = 0;



	private:
		MP_Dim m_RootDim;

	protected:
		unsigned char** m_ppucSrcAddressTable;
		int m_iDestDepth;
		MP_Pos m_DestPos;
		unsigned char* m_pColorMap;
		unsigned char* m_pucBitMaskTable;
		DWORD m_dwColor; // RGB表現 上位から、ダミー/R/G/B
		CImsDefs::IMS_ObjectType m_Type;
		MP_Dim m_DestDim;
		MP_Dim m_MyDim;
		int m_iBitCount;
		unsigned char* m_pSrcLine;
		long int m_xAddLineStart;
		long int m_xAddLineEnd;
	};

	/// CLineAdder24 内部クラス
	/// 24bit/画素の1ライン分のデコード結果を描画する
	class CLineAdder24 : public CLineAdder
	{
	public:
		CLineAdder24( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT SetupDotTransferTable();
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternalTo24(CLineAdder* pMe, unsigned char* pDestBuff);
	};
	friend class CLineAdder24;

	/// CLineAdder24 内部クラス
	/// 24bit/画素の1ライン分のデコード結果をマスクに従って描画する
	class CLineAdder24Masked : public CLineAdder24
	{
	public:
		CLineAdder24Masked( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		HRESULT SetMaskLine(unsigned char* pMaskLine);
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
		unsigned char* m_pMaskLine;
	};
	friend class CLineAdder24Masked;

	/// CLineAdder8 内部クラス
	/// 8bit/画素の1ライン分のデコード結果を描画する
	class CLineAdder8 : public CLineAdder
	{
	public:
		CLineAdder8( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT SetupDotTransferTable();
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
	};
	friend class CLineAdder8;

	/// CLineAdder24 内部クラス
	/// 8bit/画素の1ライン分のデコード結果をマスクに従って描画する
	class CLineAdder8Masked : public CLineAdder8
	{
	public:
		CLineAdder8Masked( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		HRESULT SetMaskLine(unsigned char* pMaskLine);
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
		unsigned char* m_pMaskLine;
	};
	friend class CLineAdder8Masked;

	/// CLineAdder1 内部クラス
	/// 1bit/画素の1ライン分のデコード結果を描画する
	class CLineAdder1 : public CLineAdder
	{
	public:
		CLineAdder1( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT SetupDotTransferTable();
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
	protected:
		BOOL_XD m_bMap1to1;
	};
	friend class CLineAdder1;

	/// CLineAdder1Reverse 内部クラス
	/// 1bit/画素の1ライン分のデコード結果を1=白で描画する
	class CLineAdder1Reverse : public CLineAdder1
	{
	public:
		CLineAdder1Reverse( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
	};
	friend class CLineAdder1Reverse;

	/// CLineAdder1Masker 内部クラス
	/// 1bit/画素の1ライン分のデコード結果をマスクデータ生成用に描画する
	class CLineAdder1Masker : public CLineAdder1
	{
	public:
		CLineAdder1Masker( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
	};
	friend class CLineAdder1Masker;

	/// CLineAdder1Transparent 内部クラス
	/// 1bit/画素の1ライン分のデコード結果を1値部分のみ描画する
	class CLineAdder1Transparent : public CLineAdder1
	{
	public:
		CLineAdder1Transparent( CImsDefs::IMS_ObjectType Type, DWORD dwColor);
		virtual HRESULT AddLine(unsigned char* pDestBuff);
		virtual AddLineFuncType* GetAddLineFunc();
	private:
		//static HRESULT __stdcall AddLineInternal(CLineAdder* pMe, unsigned char* pDestBuff);
		static HRESULT __stdcall AddLineInternalTo24Map1to1(CLineAdder* pMe, unsigned char* pDestBuff);
		static HRESULT __stdcall AddLineInternalTo24(CLineAdder* pMe, unsigned char* pDestBuff);
		static HRESULT __stdcall AddLineInternalTo8(CLineAdder* pMe, unsigned char* pDestBuff);
		static HRESULT __stdcall AddLineInternalTo1(CLineAdder* pMe, unsigned char* pDestBuff);
	};
	friend class CLineAdder1Transparent;

	CLineAdder* CreateLineAdder(BITMAPINFO* pBmpInfo);
	HRESULT SetNumBytesPerLine( int iBytes );
	static IDecoder* CreateDecoder( CImsDefs::IMS_ObjectType ObjectType, CImsDefs::IMS_CompressionType Type );

	unsigned char* m_pMaskLine;
	CLineAdder* m_pLineAdder;

	int m_iNumBytesPerLine;
	int m_iNumLinesFinished;
	unsigned char* m_pLineBuff;
	long int m_iLineBuffBytes;
	MP_Dim m_DestDim;
	MP_Dim m_MyDim;
	MP_Pos m_DestPos;
	int m_iPosLineToDraw;
	int m_iPosLineToGet;
	int m_iPosLineGot;
	CImsDefs::IMS_ObjectType m_Type;
	DWORD m_dwColor; // RGB空間 上位から、ダミー/R/G/B
	CImsDefs::IMS_ColorSpace m_ColorSpace;

	CLineAdder::AddLineFuncType* m_pAddLineFunc;


	virtual BITMAPINFO* CallInitFor( MP_Dim destDim, MP_Dim wantDim, HDC_XD hdc, MP_Integer degree, int iPercent ) = 0;
	virtual IDecoder::GetLineFunctionType* CallGetFuncToGetLine() = 0;
	virtual IDecoder::DecodeResult CallGetLine(unsigned char* pDestBuff) = 0;
	virtual void CallFinishFor() = 0;

protected:
	IDecoder* m_pDecoder;
	HRESULT InitCommon(MP_Dim rootDim, MP_Pos destPos, MP_Dim destDim, BITMAPINFO* pBmpInfo, MP_Integer iWantDepth );
	IDecoder::GetLineFunctionType* m_pGetLineFunc;
};

/// CImsObjectDrawerForDraw クラス
/// IMSオブジェクトの画面表示用のデコード、描画を行うクラス
class CImsObjectDrawerForDraw : public CImsObjectDrawer
{
public:
	CImsObjectDrawerForDraw( CImsDataRead* pMrc, int iNth );
private:
	virtual BITMAPINFO* CallInitFor( MP_Dim destDim, MP_Dim wantDim, HDC_XD hdc, MP_Integer degree, int iPercent );
	virtual IDecoder::GetLineFunctionType* CallGetFuncToGetLine();
	virtual IDecoder::DecodeResult CallGetLine(unsigned char* pDestBuff);
	virtual void CallFinishFor();
};

/// CImsObjectDrawerForPrint クラス
/// IMSオブジェクトの印刷用のデコード、描画を行うクラス
class CImsObjectDrawerForPrint : public CImsObjectDrawer
{
public:
	CImsObjectDrawerForPrint( CImsDataRead* pMrc, int iNth );
private:
	virtual BITMAPINFO* CallInitFor( MP_Dim destDim, MP_Dim wantDim, HDC_XD hdc, MP_Integer degree, int iPercent );
	virtual IDecoder::GetLineFunctionType* CallGetFuncToGetLine();
	virtual IDecoder::DecodeResult CallGetLine(unsigned char* pDestBuff);
	virtual void CallFinishFor();
};

/// CImsObjectDrawerForGetDIB クラス
/// IMSオブジェクトの画像データ生成用のデコード、描画を行うクラス
class CImsObjectDrawerForGetDIB : public CImsObjectDrawer
{
public:
	CImsObjectDrawerForGetDIB( CImsDataRead* pMrc, int iNth );
private:
	virtual BITMAPINFO* CallInitFor( MP_Dim destDim, MP_Dim wantDim, HDC_XD hdc, MP_Integer degree, int iPercent );
	virtual IDecoder::GetLineFunctionType* CallGetFuncToGetLine();
	virtual IDecoder::DecodeResult CallGetLine(unsigned char* pDestBuff);
	virtual void CallFinishFor();
};

#endif //__IMSOBJECTDRAWER_H__


//CHANGE LOG
//2004.04.07 - Tashiro - 新規作成(V6)
//2004.11.12 - Tashiro - AR11704 マスクされた8bitグレーに対応
