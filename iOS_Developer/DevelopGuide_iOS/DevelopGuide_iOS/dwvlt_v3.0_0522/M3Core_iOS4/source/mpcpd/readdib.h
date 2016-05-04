// File: READDIB.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

// BASEPEN.CPP から READDIB.CPP を利用するインタフェースは、これ１つである

//HBITMAP OctetStringToBitmap(HDC hdc, unsigned char* octets, long oct_len, LPBITMAPINFOHEADER lpbi, HPALETTE* p_hpal);
LPBITMAPINFOHEADER OctetStringToBITMAPINFOHEADER(unsigned char* octets, long oct_len, LPBITMAPINFOHEADER lpbi);

/*
*	HBITMAPとHPALETTEから、メモリDIBを生成する。
*/
HGLOBAL	HBITMAPtoDIBHandle(HBITMAP_XD hBmp, HPALETTE hPal, long cx, long cy, HRESULT* phres);

/*
*	メモリ上のDIBにBITMAPFILEHEADERを付けて、octetsに格納する。
*		octets == NULL なら、格納に必要なバイト数を返す
*/
long HDibToOctetString(HANDLE hdib, long cx, long cy, unsigned char* octets, long oct_len);

long MemDibToOctetString(BITMAPINFO* dibinfo, unsigned char* imagedata, long cx, long cy, unsigned char* octets, long oct_len);


unsigned short DibNumColors (LPBITMAPINFOHEADER lpbi);
unsigned short PaletteSize (LPBITMAPINFOHEADER lpbi);

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.6.21 - nagano - OctetStringToBitmap()変更（bitmap印刷改善）
//96.7.3 - Ichiriki - 生成系実装
//96.7.9 - Ichiriki - 引数型変更
//96.7.27 - Ichiriki - AR576. DibNumColors() のグローバル関数化
//96.8.8 - Ichiriki - PDフォーマット変更 ：PaletteSize() のグローバル関数化
//96.8.26 - Ichiriki - CreateGray16Palette() I/F変更
//96.8.30 - Ichiriki - WMFキャッシュに伴いCreateGray16Palette定義をpd3impl.hへ移動

