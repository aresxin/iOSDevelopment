//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
/*
 *  MXCBitmapWrapper.h
 *
 *  Created by A-Vis(Marumo,K.) on Wed Dec 17 2003.
 *
 * MXCBitmapWrapper 関数の宣言。
 * MXCBitmapWrapper を使用するプログラムでは、このヘッダーをインクルードすること。
 *
 */
 
 #ifndef MXCBITMAPWRAPPER_H
 #define MXCBITMAPWRAPPER_H

/**
 * BITMAPINFOHEADERのbiHeight操作
 */
long getBiHeight(unsigned char* bitmap);
void setBiHeight(unsigned char* bitmap, long h); 

/**
 * BITMAPINFOHEADERのbiWidth操作
 */
long getBiWidth(unsigned char* bitmap);

/**
 * BITMAPFILEHEADERのbfOffBits操作
 */ 
unsigned long getBfOffBits(unsigned char* bitmap);

/**
 * BITMAPINFOHEADERの内容を標準出力にプリント
 */
void debugPrintBitmapInfoHeader(unsigned char* bitmap);

#endif // MXCBITMAPWRAPPER_H