/**
 * @file  XdwGraphicFormatEMFEMRSetColorAdjustmentRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetColorAdjustmentRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_COLORADJUSTMENT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_COLORADJUSTMENT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約*/
//#include "XdwGraphicFormatGDIPoint.h"
//#include "XdwGraphicFormatGDIRectangle.h"
/**
 * @brief SetColorAdjustmentレコードを規定するクラス
 *
 * COLORADJISTMENT構造体は定義していないのでこのクラスで読み込む
 */
class XdwGraphicFormat::EMF::EMR::SetColorAdjustmentRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetColorAdjustmentRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetColorAdjustmentRecord();
    
    /**
     * @brief SetColorAdjustmentレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

	
	/*集約*/

/* MSDN より
パラメータ
caSize 
	構造体のサイズをバイト単位で指定します。 
caFlags 
	出力イメージを準備する方法を指定します。このメンバには、NULL または次の値を組み合わせることができます。 
	CA_NEGATIVE   オリジナルのイメージを反転表示するように指定します。 
	CA_LOG_FILTER   対数関数が出力カラーの最終濃度に適用されるように指定します。この指定により、輝度が低いときに色のコントラストが増加します。 
caIlluminantIndex 
	イメージ オブジェクトが表示される環境下での光源の輝度を指定します。このメンバには次の値のいずれかを設定します。 
	ILLUMINANT_EQUAL_ENERGY 
	ILLUMINANT_A 
	ILLUMINANT_B 
	ILLUMINANT_C 
	ILLUMINANT_D50 
	ILLUMINANT_D55 
	ILLUMINANT_D65 
	ILLUMINANT_D75 
	ILLUMINANT_F2 
	ILLUMINANT_TURNGSTEN 
	ILLUMINANT_DAYLIGHT 
	ILLUMINANT_FLUORESCENT 
	ILLUMINANT_NTSC 
caRedGamma 
	ソース カラーの原色の赤の n 次ガンマ補正値を指定します。値は、2,500 から 65,000 の範囲にする必要があります。値 10,000 はガンマ補正をしないことを意味します。 
caGreenGamma 
	ソース カラーの原色の緑の n 次ガンマ補正値を指定します。値は、2,500 から 65,000 の範囲にする必要があります。値 10,000 はガンマ補正をしないことを意味します。 
caBlueGamma 
	ソース カラーの原色の青の n 次ガンマ補正値を指定します。値は、2,500 から 65,000 の範囲にする必要があります。値 10,000 はガンマ補正をしないことを意味します。 
caReferenceBlack 
	ソース カラーのブラック リファレンスを指定します。これよりも暗い色はすべて黒と見なします。値は、0 から 4,000 の範囲にする必要があります。 
caReferenceWhite 
	ソース カラーのホワイト リファレンスを指定します。これよりも明るい色はすべて白と見なします。値は、6,000 から 10,000 の範囲にする必要があります。 
caContrast 
	ソース オブジェクトに適用されるコントラストの量を指定します。値は、-100 から 100 までの範囲にする必要があります。値 0 はコントラストの調整をしないことを意味します。 
caBrightness 
	ソース オブジェクトに適用される明度の量を指定します。値は、-100 から 100 までの範囲にする必要があります。値 0 は明度の調整をしないことを意味します。 
caColorfulness 
	ソース オブジェクトに適用される彩度の量を指定します。値は、-100 から 100 までの範囲にする必要があります。値 0 は彩度の調整をしないことを意味します。 
caRedGreenTint 
	ソース オブジェクトに適用される赤色、または緑色の濃淡補正の量を指定します。値は、-100 から 100 までの範囲にする必要があります。正の値は赤色方向、負の値は緑色方向に補正されます。値 0 は濃淡の補正をしないことを意味します。 
*/
	unsigned short fSize;
	unsigned short fFlags;
  	unsigned short fIlluminantIndex;
	unsigned short fRedGamma;
	unsigned short fGreenGamma;
	unsigned short fBlueGamma;
	unsigned short fReferenceBlack;
	unsigned short fReferenceWhite;
	short fContrast;
	short fBrightness;
	short fColorfulness;
	short RedGreenTint;
	
	
};

#endif
