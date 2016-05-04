//
//  MXCImage.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCImage.h	DWCORE Draw Object Class
 *
 *	MXCImageクラスとその派生クラスのインターフェースを定義する。
 */

#ifndef MXCIMAGE_H
#define MXCIMAGE_H

#include "MXCWrapper.h"
#include "MXCWrapperConst.h"
#include "w2mpf_gdi_def.h"

#ifdef __cplusplus

class MXCImagePD;

/**
 * MXCImage : DW文書 描画オブジェクトクラス
 * 
 * アノテーション以外の「描画オブジェクト」を表すクラス。
 * 描画オブジェクトの数だけ作成される。
 */
class MXCImage {

public:
	virtual ~MXCImage(){};
	
    /**
     * imageKind : 画像の種別を返す
     * 画像の種別を定数で返す。
     *
     * 返り値：
     * 画像種別定数
     */
    virtual int imageKind() = 0;
    
    /**
     * width : 画像の幅を返す
     *
     * 返り値：
     * 画像の幅
     */
    virtual int width() = 0;
    
    /**
     * height : 画像の高さを返す
     *
     * 返り値：
     * 画像の高さ
     */
    virtual int height() = 0;

    /**
     * x : 画像のX座標を返す
     *
     * 返り値：
     * 画像のX座標
     */
    virtual int x() = 0;
    
    /**
     * y : 画像のY座標を返す
     *
     * 返り値：
     * 画像のY座標
     */
    virtual int y() = 0;

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCRasterPDか
	 * MXCEMFPD、もしくはMXCWMFPDのものとなる。
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;

	/**
	 * bodyContent : 画像データのDWCOREオブジェクト(HeteroBodyCont)を返す
	 * 検索の際に使用する。今のところ他に使用する所はない。
	 * void* を返すようにしているので、コールした側で必ずキャストする。
	 *
	 * 返り値：
	 * DWCOREオブジェクト(HeteroBodyCont)
	 */
	virtual void* bodyContent() = 0;

    /**
	 * [for Version 6.0]
     * unloadPD : PDのアンロードを行う
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadPD() = 0;

    /**
	 * [for Version 6.0]
     * thumbnailPd : サムネイル画像のPDを返す。
	 *
     * サムネイル画像のメタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCRasterPDで、
	 * V2の文書ならOKD(V2)、それ以降はOKD(V3)のフォーマットとなる。
	 * サムネイル画像を持たない場合は、NULLを返す。
	 * このメソッドを呼ばれたタイミングで、サムネイルのPDをロードする。
     *
     * 返り値：
     * サムネイル画像のPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* thumbnailPd() = 0;

    /**
	 * [for Version 6.0]
     * unloadThumbnailPd : サムネイル画像のPDをunloadする。
	 *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadThumbnailPd() = 0;

    /**
     * rotateAngle : 画像データの回転角度を数値で返す。
     * 返る数値は 0, 90, 180, 270 のうちのいずれか。
     * width(), height()メソッドで返る値が回転された後のサイズだと推測されるため、
     * この値を使用して回転前のサイズを割り出すようにする。
     *
     * 返り値：
     * 画像データの回転角度
     */
    virtual int rotateAngle() = 0;
};

/**
 * MXCImagePD : 画像PDクラス
 * 
 * 画像描画オブジェクトが持つデータ(PD)を表すクラス
 */
class MXCImagePD {

public:
	virtual ~MXCImagePD(){};
	
    /**
     * pdKind : ベクタ画像の種別を返す
     * ベクタ画像の種別を定数で返す。
	 * 定数は（互換性の為）MXCImage::imageKind()で使用する定数と共通の物にする。
     *
     * 返り値：
     * 画像種別定数
     */
    virtual int pdKind() = 0;
 	
    /**
     * rotateAngle : 画像データの回転角度を数値で返す。
     * 返る数値は 0, 90, 180, 270 のうちのいずれか。
     * width(), height()メソッドで返る値が回転された後のサイズだと推測されるため、
     * この値を使用して回転前のサイズを割り出すようにする。
     *
     * 返り値：
     * 画像データの回転角度
     */
    virtual int rotateAngle() = 0;
    
};

/**
 * MXCRasterPD : ラスタ画像PDクラス
 * 
 * 描画オブジェクトの中でもラスタ画像のオブジェクトを表すクラス。
 * 
 */
class MXCRasterPD : public MXCImagePD {

public:

    /**
     * data : 画像データをchar*で返す。
     * 逐次描画をしないフォーマット(無圧縮・MH・JPEG)で使用する。
     * 画像データを持ったバッファのポインタを返す。
     *
     * 返り値：
     * 画像データバッファのポインタ
     */
    virtual char* data() = 0;
    
    /**
     * size : 画像データのサイズを返す。
     * 逐次描画をしないフォーマット(無圧縮・MH・JPEG)で使用する。
     * data()メソッドで返る画像データのサイズを返す。
     *
     * 返り値：
     * 画像データのサイズ
     */
    virtual long size() = 0;
    
    /**
     * bitmapHeader : ビットマップヘッダを返す
     * 逐次描画をするフォーマット(ALLA/MMR/OKD)で使用する。
     * ビットマップヘッダのバッファのポインタを返す
     * 返すヘッダはビットマップ画像として正しいヘッダのため、リトルエンディアンになっている。
     * また、このときにbitmapLine()メソッドを呼ぶための初期化も行う。
     *
     * 返り値：
     * ビットマップヘッダバッファのポインタ
     */
    virtual unsigned char* bitmapHeader() = 0;
    
    /**
     * bitmapHeaderSize : ビットマップヘッダのサイズを返す。
     * 逐次描画をするフォーマット(ALLA/MMR/OKD)で使用する。
     * bitmapHeader()メソッドで返るビットマップヘッダのサイズを返す。
     * BITMAPFILEHEADER(14byte) + BITMAPINFOHEADER(40byte) + パレットデータ
     *
     * 返り値：
     * ビットマップヘッダのサイズ
     */
    virtual long bitmapHeaderSize() = 0;

    /**
     * bitmapLine : DIBデータを一行ずつ返す
     * 逐次描画をするフォーマット(ALLA/MMR/OKD)で使用する。
     * 画像データを一行格納したバッファのポインタを返す
     *
     * 引数：
     * 一行の画像データのバッファのポインタ
     * 
     * 返り値：
     *  MXC_PD_GETLINE_CONTINUE     まだラインはある
     *  MXC_PD_GETLINE_COMPLETE     もう返すラインは残っていない
     *  MXC_PD_GETLINE_ERROR        何かエラー発生 or not implemented     
     */
    virtual int bitmapLine(unsigned char* buffer) = 0;

    /**
     * bitmapLine : DIBデータ１行のバッファサイズを返す
     * 逐次描画をするフォーマット(ALLA/MMR/OKD)で使用する。
     * 画像データ一行を格納するためのバッファのサイズを返す。
     *
     * 返り値：
     * 一行の画像データのサイズ
     */
    virtual long lineBufSize() = 0;

    /**
     * freeBitmapHeader : ビットマップヘッダを解放する
     * 逐次描画をするフォーマット(ALLA/MMR/OKD)で使用する。
     * bitmapHeader()メソッドで取得したビットマップヘッダはPDSeed内部で確保したものなので
     * 必要なくなったら必ずこれを呼ぶこと。
     *
     * 引数：
     * ビットマップヘッダのバッファのポインタ
     */
    virtual void freeBitmapHeader(unsigned char* pInfo) = 0;

    /**
     * setSize : ビットマップのサイズを設定する
     * 出力するビットマップのサイズをピクセルで指定する。
	 *
	 * このメソッドを呼んでサイズを指定した場合はdata()およびbitmapLine()のコールの際に
	 * 指定サイズにビットマップを縮小して返す。
	 * 指定しない（このメソッドを呼ばない）、もしくはオリジナルのデータより大きい値、不正な値を指定した場合は
	 * オリジナルのサイズでビットマップを返す。
     *
     * 引数：
     * width	IN 縮小後の幅（ピクセル）
	 * height   IN 縮小後の高さ（ピクセル）
     */
    virtual void setSize(int width, int height) = 0;
};

/**
 * MXCEMFPD : EMF画像PDクラス
 * 
 * EMF画像のメタファイルデータを表す。
 * 
 */
class MXCEMFPD : public MXCImagePD {

public:

    /**
     * emf : 拡張メタファイルをchar*で返す。
     * メモリー上に展開された拡張メタファイルデータの先頭へのポインタを返す。
     *
     * 返り値：
     * 拡張メタファイルデータのポインタ
     */
    virtual char* emf() = 0;
	
	/**
	 * ユーザーデータの初期化
	 */
	virtual void initEnumUserData() = 0;
	
	/**
	 * EMR_GDICOMMENT型のレコードの解凍
	 * 必要に応じて、メタレコードをコピーして、コピー先の領域に解凍したデータを設定する。
	 * コピーした領域は、引数 enhr で返す。
	 */
	virtual void expandGDIComment(PENHMETARECORD* enhr) = 0;
	
	/**
	 * 外部イメージのオブジェクトモードを返す。
	 * 戻り値:
	 * 0=NONE, 1=DIB, 2=JPEG
	 */
	virtual int dibObjectMode() = 0;

	 /**
	 * 外部イメージデータのBITMAPINFOを返す。
	 * 返す構造体の内部は、ビッグエンディアンであること。
	 * 外部イメージがDIBの場合は、保持しているBITMAPINFOへのポインタを戻り値で返す。
	 * 外部イメージがJPEGの場合は、情報を引数に設定して、戻り値で引数のポインタを返す。
	 * 外部イメージが上記以外の場合は、戻り値でNULLを返す。
	 */
	virtual BITMAPINFO * bitmapInfo() = 0;
	virtual unsigned long bitmapInfoSize() = 0;
	
	/**
	 * 外部イメージの画像データを取得する。
	 * 外部イメージがDIBの場合は、保持しているビットデータへのポインタを戻り値で返す。
	 * 外部イメージがJPEGの場合は、JPEGデータへのポインタを返す。
	 * 外部イメージが上記以外の場合は、戻り値でNULLを返す。
	 */
	virtual unsigned char * bitmapBits() = 0;
	virtual unsigned long bitmapBitsSize() = 0;
	
	/**
	 * 外部イメージデータがJPEGの場合、
	 * JPEGのサイズを取得する（DIBはBITMAPINFOに入っている）
	 * JPEG以外の場合は 0 を返す。
	 */
	virtual int jpegSize() = 0;

};

/**
 * MXCWMFPD : WMF画像PDクラス
 * 
 * WMF画像のメタファイルデータを表す。
 * 
 */
class MXCWMFPD : public MXCImagePD {

public:

    /**
     * wmf : Windowsメタファイルをchar*で返す。
     * メモリー上に展開されたWindowsメタファイルデータの先頭へのポインタを返す。
     *
     * 返り値：
     * Windowsメタファイルデータのポインタ
     */
    virtual char* wmf() = 0;
	
	/**
	 * ユーザーデータの初期化
	 */
	virtual void initEnumUserData() = 0;
	
	/**
	 * META_ESCAPEのレコードの解凍
	 * 必要に応じて、メタレコードをコピーして、コピー先の領域に解凍したデータを設定する。
	 * コピーした領域は、引数 mr で返す。
	 */
	virtual void expandEscape(METARECORD** ppmr) = 0;
	
	/**
	 * 外部イメージデータのオブジェクトモードを返す。
	　　* 戻り値：
	 * 0=NONE, 1=DIB, 2=JPEG
	 */
	virtual int dibObjectMode() = 0;
	
	/**
	 * 外部イメージデータのBITMAPINFOを返す。
	 * 返す構造体の内部は、ビッグエンディアンであること。
	 * 外部イメージがDIBの場合は、保持しているBITMAPINFOへのポインタを戻り値で返す。
	 * 外部イメージがJPEGの場合は、情報を引数に設定して、戻り値で引数のポインタを返す。
	 * 外部イメージが上記以外の場合は、戻り値でNULLを返す。
	 */
	virtual BITMAPINFO * bitmapInfo() = 0;
	virtual unsigned long bitmapInfoSize() = 0;
	
	/**
	 * 外部イメージの画像データを取得する。
	 * 外部イメージがDIBの場合は、保持しているビットデータへのポインタを戻り値で返す。
	 * 外部イメージがJPEGの場合は、JPEGデータへのポインタを返す。
	 * 外部イメージが上記以外の場合は、戻り値でNULLを返す。
	 */
	virtual unsigned char * bitmapBits() = 0;
	virtual unsigned long bitmapBitsSize() = 0;
	
	/**
	 * 外部イメージデータがJPEGの場合、
	 * JPEGのサイズを取得する（DIBはBITMAPINFOに入っている）
	 * JPEG以外の場合は 0 を返す。
	 */
	virtual int jpegSize() = 0;
	
	/**
	 * PDの表示サイズ（幅、高さ）を100分の1ミリ単位で返す。
	 */
	virtual int width() = 0;
	virtual int height() = 0;

};

/**
 * MXCPageform : 見出しクラス
 * 
 * 描画オブジェクトの中で見出しを表すクラス。
 * 
 */
class MXCPageform : public MXCImage {

};

#endif // __cplusplus

#endif // MXCIMAGE_H
