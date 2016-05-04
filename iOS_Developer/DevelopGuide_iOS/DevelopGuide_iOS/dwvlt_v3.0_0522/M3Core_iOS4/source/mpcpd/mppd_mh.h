// File: MPPD_MH.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*	MPPD_MH.H	: MP PD MH encode / decode
*
*	MH圧縮・伸張（Fill等の仕様はLeadToolに合わせる）
*/

#ifndef MPPD_MH_H
#define MPPD_MH_H

#define STRICT 1


//#include "windows.h"
#include "win2mpf.h"

class MP_MHDecode {
public:
	MP_MHDecode();
	~MP_MHDecode();

	long	Decode(unsigned char* packedmemory, long packedlen, long width, long height);
	int	GetBitmapDim(unsigned char* packedmemory, long packedlen, long* pw, long* ph);

	HGLOBAL	m_hdib;


private:
	inline int getbits(unsigned char n, int fill = 1);
	inline void fillbuf(unsigned char n);
	long DecodeLine(LPBYTE pBits);

    unsigned char *	m_dec_packedmemory;
    long	m_dec_packedsize;

    unsigned char *	m_dec_cur_ptr;
    unsigned char	m_dec_subbitbuf;
    unsigned char	m_dec_bitcount;
    unsigned long	m_dec_bitbuf;
};

class MP_MHEncode {
public:
	MP_MHEncode();
	~MP_MHEncode();
	long Encode(LPBITMAPINFO lpbi);

	unsigned long* m_encoded_buf;	// Encode結果を格納するバッファ
	long m_encoded_size;			// Encode結果のバイト数

private:
	unsigned char* m_curbytep;	// m_encoded_bufのうち、現在ビット加工処理をしているバイトへのポインタ
	long m_limitsize;			// 圧縮結果がこの値を超えたら効率よく圧縮できないデータとしてエラー復帰
	long m_bmpwidth;			// Encodeしているビットマップの横幅 (pixel)
	long m_curbit;				// 現在 *m_curbytep の何ビット目を処理しているか
	long m_whitevalue;			// 1と0のどちらを白として扱うか

	inline long EncodeLine(unsigned char* dibbits);
	inline void SetRun(int color, int runlen);

	inline void putcode(const struct codeTable* pct);
};

#endif // MPPD_MH_H

//CHANGE LOG
//96.8.7 - Ichiriki - 作成

