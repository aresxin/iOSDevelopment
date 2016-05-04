/*!
  @file  XdwBridgeRasterOutputAdapter.h
  @brief XdwBridgeRasterOutputAdapter関連ヘッダファイル

  XdwBridgeRasterOutputAdapter classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-07-18
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-18	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED
#define XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED

#include "XdwError.h"
#include "XdwRaster.h"

class XdwBridgeDecodeStrategy;

/*!Image出力用 Adapter class
 *
 * Raseter Imageを出力するクラスのI/F定義クラス．
 * 各クラスは，このクラスを継承して，XdwBridgeRasterManager
 * をclientとしたAdapter Patternを構成する.
 */
class XdwBridgeRasterOutputAdapter {
public:
    /*!コンストラクタ
     * コンストラクタ
     */
    XdwBridgeRasterOutputAdapter() {};
    /*!デストラクタ
     * デストラクタ
     */
    virtual ~XdwBridgeRasterOutputAdapter() {};

    /*! MaskとRaster Imageの描画
     *
     * XdwBridgeDecodeStrategy ObjectからDecodeされた
     * Raster Image or Maskを読み込み，出力先へ描画する.<br>
     * 引数にNULLが指定されていた場合，そのデータ無いものとして動作する.
     *
     * @param img_attr		Image属性
     * @param image		Image読込先
     * @param mask_attr		Mask属性
     * @param mask		Mask読込先
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Draw(const XdwRasterImageAttribute	&img_attr,
			      XdwBridgeDecodeStrategy	*image,
			      const XdwRasterImageAttribute	&mask_attr,
			      XdwBridgeDecodeStrategy	*mask ) = 0;
    /***************************************************/
    /*! @name サーポート問い合わせI/F
     * XdwBridgeRasterOutputAdapterの出力先がサポートする，
     * 圧縮形式・ラスター形式等を問い合わせる関数
     */
    /***************************************************/
    /*@{*/
    /*!Indexed Rasterサポート問い合わせ
     * XdwBridgeRasterOutputAdapterが
     * Indexed Rsterをサポートするか否か答える．
     * @retval true サポート
     * @retval false 非サポート
     */
    virtual bool IsIndexedRasterSupport(void) = 0;
    /*@}*/
};

#include "imgImager.h"

//class imgImager;
class XdwBridgeGraphicStateManager;

class XdwBridgeRasterOutputAdapterForGlobe : public XdwBridgeRasterOutputAdapter {
private:
    imgImager				*imagerF;
    XdwBridgeGraphicStateManager	*gstateF;

    IMG_COLORSPACE_MODE ConvBridgeCS2GlobeCS( XdwColorSpaceID );

    unsigned char* GeneratePalette( const XdwRasterImageAttribute & );
    unsigned char* GeneratePaletteBW( const XdwRasterImageAttribute & );
    XdwErrorCode DrawImage(const XdwRasterImageAttribute	&,
			   XdwBridgeDecodeStrategy		* );
    XdwErrorCode DrawImageAndMask(const XdwRasterImageAttribute	&,
				  XdwBridgeDecodeStrategy	*,
				  const XdwRasterImageAttribute	&,
				  XdwBridgeDecodeStrategy	* );
    XdwErrorCode DrawMask(const XdwRasterImageAttribute	&,
			  XdwBridgeDecodeStrategy		* );
public:
    XdwBridgeRasterOutputAdapterForGlobe() {};
    XdwBridgeRasterOutputAdapterForGlobe( imgImager *,
					  XdwBridgeGraphicStateManager *);
    ~XdwBridgeRasterOutputAdapterForGlobe() {};

    bool IsIndexedRasterSupport(void);
    XdwErrorCode Draw(const XdwRasterImageAttribute	&img_attr,
		      XdwBridgeDecodeStrategy	*image,
		      const XdwRasterImageAttribute	&mask_attr,
		      XdwBridgeDecodeStrategy	*mask );
};
#endif /* XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED */
