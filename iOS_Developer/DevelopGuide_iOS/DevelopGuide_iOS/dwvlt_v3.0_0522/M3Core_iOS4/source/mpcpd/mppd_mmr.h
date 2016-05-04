// File: MPPD_MMR.H
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

/*
*	MPPD_MMR.H	: MP PD MMR encode / decode
*
*	MMR圧縮・伸張 (libTIFFのアルゴリズムを改良)
*/

#ifndef MPPD_MMR_H
#define MPPD_MMR_H

//#include <windows.h>
#include "win2mpf.h"

//
// 09/12/04 新規追加 M.Chikyu
//
#ifdef _M3CORE_MP_

#include "mpc_api.h"
#include "mpc_spi.h"
#include "mpc_pd.h"

#endif

// error
#define MPMMR_E_INVALIDARG		((int)0x80040100)
#define MPMMR_E_OUTOFMEMORY		((int)0x80040101)
#define MPMMR_E_UNEXPECTED		((int)0x80040102)
#define MPMMR_E_OVERBUF			((int)0x80040103)	// Over Buf
#define MPMMR_E_BADCODE			((int)0x80040104)	// Bad code word at scanline
#define MPMMR_E_EXTENSION		((int)0x80040105)	// Uncompressed data (not supported) at scanline
// warning
#define MPMMR_W_BADLENGTH		((int)0x80040106)	// Line length mismatch
#define MPMMR_W_PREMATURE_EOL	((int)0x80040107)	// Premature EOF

// Encode/Decode する幅・高さの最小・最大値を設定
#define MMR_MIN_WIDTH	8
#define MMR_MIN_HEIGHT	2
#define MMR_MAX_WIDTH	65535	// ランレングスを2Bytesで表現するため
#define MMR_MAX_HEIGHT	65535	// 現在は使用しない

// 1Lineのランレングスデータを1LineのDIBに変換する関数
// 1Lineのランレングスデータは、白黒白…の順でランの長さが各 unsigned short (2Byte) で格納されている。
void RLtoDIBLine(unsigned char* buf, unsigned short* runs, unsigned short* erun, unsigned long lastx);


class MP_MMRDecode {
public:
	MP_MMRDecode();

	//
	// 09/12/04 新規追加 M.Chikyu
	//
#ifdef _M3CORE_MP_
	MP_MMRDecode(MPCSession *);
#endif

	~MP_MMRDecode();

	// 伸長してDIBを作成する関数(mppd_mh互換)
	int Decode(unsigned char* pMMRBuf, unsigned long codeSize, unsigned long width, unsigned long height);		// mppd_mh との互換用

	// 伸長してランレングスデータを作成する関数
	int Decode_RL(unsigned char* pMMRBuf, unsigned long codeSize, unsigned long width, unsigned long height);

	// 正しいMMRデータかどうかチェックする関数
	int Decode_Check(unsigned char* pMMRBuf, unsigned long codeSize, unsigned long width, unsigned long height);


	HANDLE m_hDIB;					// 伸長後のDIBを格納するバッファ：Decode
	unsigned char* m_pRLBuf;		// 伸長後のランレングスデータを格納するバッファ：Decode_RL
	// m_pRLBuf には、(1Lineランレングスデータのコードサイズ(unsigned long, 4Byte) + 1Lineのランレングスデータ)の集合が格納される。
	unsigned long  m_RLSize;		// 伸長後のランレングスデータのサイズ：Decode_RL

private:

	//
	// 09/12/04 新規追加 M.Chikyu
	//
#ifdef _M3CORE_MP_
	MPCSession* m_session;
	MPC_BigAlloc* m_mpcBigAlloc;
#endif
};

class MP_MMREncode {
public:
	MP_MMREncode();
	~MP_MMREncode();

	// 各圧縮関数
	// BITMAPINFO以下にビットマップデータがあるとき
	int Encode(LPBITMAPINFO lpBI);

	// BITMAPINFOとビットマップデータが分かれているとき
	int Encode(LPBITMAPINFO lpBI, unsigned char* pBMPBuf);

	// ビットマップデータと幅・高さ・パレット情報から圧縮したいとき
	int Encode(unsigned char* pBMPBuf, unsigned long width, unsigned long height, int bNeedInvert);

	unsigned char* m_pMMRBuf;	// Encode結果を格納するバッファ
	unsigned long m_codeSize;	// Encode結果のバイト数

	unsigned long m_limitsize;	// Encodeを打ち切るサイズ(デフォルト：元イメージの 1/2)

	// 1Line単位で圧縮を行う(メモリ節約用)
	int InitForEncodeLine(LPBITMAPINFO lpBI);	// まずこれを呼ぶ
	int EncodeLine(unsigned char *lineBuf);		// lineBufに1Line分のビットマップデータのポインタを渡す
												// エラー時には、内部で確保したバッファは開放される
	int FinishForEncodeLine();					// height分だけ EncodeLine を実行した後、最後に呼ぶ(バッファの開放もする)

private:
	// 1Line単位で圧縮を行う場合のみ
	unsigned long m_height;
	unsigned char *m_buf;
	unsigned long m_BMPWidthByte;
	int m_bNeedInvert;
	void* m_mmrs;
	unsigned long m_lineBytes;
	int m_ret;

};

#endif // MPPD_MMR_H

//CHANGE LOG
//98.09.01 - Nakazawa - 作成
//98.09.18 - Nakazawa - Encode/Decode する幅・高さの最小・最大値を設定
//98.11.11 - Nakazawa - メモリ節約用のEncodeLine等追加
//99.05.31 - Nakazawa - コメント修正
