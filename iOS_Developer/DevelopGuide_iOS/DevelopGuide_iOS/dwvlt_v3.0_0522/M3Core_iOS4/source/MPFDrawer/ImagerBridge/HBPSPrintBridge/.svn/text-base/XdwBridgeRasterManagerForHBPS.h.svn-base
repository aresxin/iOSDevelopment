/*!
  @file  XdwBridgeRasterManager.h
  @brief XdwBridgeRasterManager関連ヘッダファイル

  XdwBridgeRasterManager classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-07-18
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-18	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERMANAGER_H_INCLUDED
#define XDWBRIDGERASTERMANAGER_H_INCLUDED

#include "XdwError.h"
#include "XdwRaster.h"
#include "XdwDataObject.h"
#include "XdwDataObjectBinary.h"

class XdwBridgeRasterOutputAdapter;
class XdwBridgeDecodeStrategy;

class XdwBridgeRasterManager {
    
public:
    XdwBridgeRasterManager();
    virtual ~XdwBridgeRasterManager();

    /*! 初期化
     * XdwBridgeRasterManager classとその派生classにおいて，
     * 動的に生成されるオブジェクトが存在する場合，ここで初期化される．<br>
     * メンバ変数の場合はたいていコンストラクタの方で初期化する予定．
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
    */
    virtual XdwErrorCode Initialize( void ) = 0;

    /*! MaskとRaster Imageの描画
     *
     * XdwDataObject::Binary Objectから読み込まれたEncoded Raster Image,
     * Encoded Mask をDecodeして，XdwBridgeRasterOutputAdapter Objectへ
     * 出力する.<br>
     * クライアント側で出力先をnewしなければならないことに注意.
     *
     * @param out		出力先
     * @param img_attr		Image属性
     * @param img_data		Image読込先
     * @param img_offset	Encoded Dataまでのオフセット
     * @param img_size		Encoded Dataのサイズ
     * @param mask_attr		Mask属性
     * @param mask_data		Mask読込先
     * @param mask_offset	Encoded Dataまでのオフセット
     * @param mask_size		Encoded Dataのサイズ
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode DrawImage( XdwBridgeRasterOutputAdapter	*out,
				    const XdwRasterImageAttribute	&img_attr,
				    XdwDataObject::Binary		*img_data,
				    const long				&img_offset,
				    const long				&img_size,
				    const XdwRasterImageAttribute	&mask_attr,
				    XdwDataObject::Binary		*mask_data,
				    const long				&mask_offset,
				    const long				&mask_size ) = 0;

    /*! MaskとRaster Imageの分割描画開始
     *
     * XdwDataObject::Binary Objectから読み込まれたEncoded Raster Image,
     * Encoded Mask をDecodeして，XdwBridgeRasterOutputAdapter Objectへ
     * 出力するための初期設定.<br>
     * クライアント側で出力先をnewしなければならないことに注意.
     * 一連の処理はスキャンイメージなどの全面イメージを対象とする.
     *
     * @param out		出力先
     * @param img_attr		Image属性
     * @param img_data		Image読込先
     * @param img_offset	Encoded Dataまでのオフセット
     * @param img_size		Encoded Dataのサイズ
     * @param mask_attr		Mask属性
     * @param mask_data		Mask読込先
     * @param mask_offset	Encoded Dataまでのオフセット
     * @param mask_size		Encoded Dataのサイズ
     * @param nlines		DrawDividedImage一回あたりの描画ライン数
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    virtual XdwErrorCode StartDrawDividedImage(
					XdwBridgeRasterOutputAdapter	*out,
				    const XdwRasterImageAttribute	&img_attr,
				    XdwDataObject::Binary	*img_data,
				    const long				&img_offset,
				    const long				&img_size,
				    const XdwRasterImageAttribute	&mask_attr,
				    XdwDataObject::Binary	*mask_data,
				    const long				&mask_offset,
				    const long				&mask_size,
					long					nlines) = 0;
    /*! MaskとRaster Imageの分割描画
     *
     * StartDrawDividedImageでセットされたイメージとパラメータに従って分割出力する
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_CONTINUE	引き続き処理が可能
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    virtual XdwErrorCode DrawDividedImage( void ) = 0;
    /*! MaskとRaster Imageの分割描画終了
     *
     * StartDrawDividedImage->DrawDividedImageの順で処理される一連のイメージ描画処理を終了する。
     * 処理を中断する場合でも必ず呼ばれなければならない。
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    virtual XdwErrorCode EndDrawDividedImage( void ) = 0;
};

class imgImager;
class XdwBridgeDecoStDIB;

class XdwBridgeRasterManagerForHBPS {
private:
    void	*imagerF;
    XdwBridgeDecoStDIB	*DIB_CodecF;
    XdwBridgeRasterOutputAdapter *current_out;
	XdwBridgeDecodeStrategy	*image;
	XdwBridgeDecodeStrategy	*mask;

    XdwBridgeDecodeStrategy* GenerateDecoder(
				XdwBridgeRasterOutputAdapter *,
				const XdwRasterImageAttribute &,
				XdwDataObject::Binary * );
public:
    XdwBridgeRasterManagerForHBPS( void *imager );
    ~XdwBridgeRasterManagerForHBPS();

    XdwErrorCode Initialize( void );
    XdwErrorCode DrawImage(
				XdwBridgeRasterOutputAdapter *out,
			    const XdwRasterImageAttribute	&img_attr,
			    XdwDataObject::Binary	*img_data,
			    const long				&img_offset,
			    const long				&img_size,
			    const XdwRasterImageAttribute	&mask_attr,
			    XdwDataObject::Binary	*mask_data,
			    const long				&mask_offset,
			    const long				&mask_size );
    XdwErrorCode DrawImagePattern(
				XdwBridgeRasterOutputAdapter *out,
			    const XdwRasterImageAttribute	&img_attr,
			    XdwDataObject::Binary	*img_data,
			    const long				&img_offset,
			    const long				&img_size,
				int						drawMethod);
    XdwErrorCode StartDrawDividedImage(
				XdwBridgeRasterOutputAdapter *out,
			    const XdwRasterImageAttribute	&img_attr,
			    XdwDataObject::Binary	*img_data,
			    const long				&img_offset,
			    const long				&img_size,
			    const XdwRasterImageAttribute	&mask_attr,
			    XdwDataObject::Binary	*mask_data,
			    const long				&mask_offset,
			    const long				&mask_size,
				long					nlines );
	XdwErrorCode DrawDividedImage( void );
	XdwErrorCode EndDrawDividedImage( void );
};

#endif /* XDWBRIDGERASTERMANAGER_H_INCLUDED */
