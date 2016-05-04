//
//  MXDDCForVectorDraw.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDDeviceContextDraw.h"

#import "MXDVectorSource.h"

// *****ベクター化モード用定数定義*****
// 演算方法の定数
typedef enum MXD_DM {
	MXD_DM00_COPY,
	MXD_DM01_GRAPHICS_NONE,
	MXD_DM02_GRAPHICS_BLACK,
	MXD_DM03_GRAPHICS_WHITE,
	MXD_DM04_GRAPHICS_AND,
	MXD_DM05_GRAPHICS_OR,
	MXD_DM06_GRAPHICS_XOR,
	MXD_DM07_GRAPHICS_NOTWHITE_XOR,
	MXD_DM08_MONOPATTERN_AND,
	MXD_DM09_MONOIMAGE_AND,
	MXD_DM10_MONOIMAGE_OR,
	MXD_DM11_MONOIMAGE_XOR,
	MXD_DM12_MONOIMAGE_NOT_S_OR,
	MXD_DM13_MONOIMAGE_NOT_S_AND,
	MXD_DM14_IMAGE_AND,
	MXD_DM15_IMAGE_OR,
	MXD_DM16_IMAGE_XOR,
	
	MXD_DM17_MONOIMAGE_PSPDxax,
	MXD_DM18_MONOIMAGE_DSPDxax,
	MXD_DM19_IMAGE_NOT_S,
	MXD_DM20_GRAPHICS_ANDPEN,
	MXD_DM21_GRAPHICS_ANDBRUSH_PEN,
	
	
	MXD_DMXX_STRANGE
} MXD_DM;

// 状態定数定義
// 最上位バイト -> 代替描画モードフラグ
// 上位2バイトめ -> 描画形式決定フラグ
typedef enum MXD_STATE {
	MXD_STATE_USUAL,
	
	MXD_STATE_START = 0xF0000000,
	
	MXD_STATE_1,
	MXD_STATE_2,
	MXD_STATE_3,
	MXD_STATE_4,
	MXD_STATE_5,
	MXD_STATE_6,
	MXD_STATE_7,
	
	MXD_STATE_4_1,
	MXD_STATE_4_2,
	MXD_STATE_4_3,
	
	MXD_STATE_6_1,
	MXD_STATE_6_2,
	
	MXD_STATE_7_1,
	MXD_STATE_7_2,
	
	MXD_STATE_7_1_1,
	
	MXD_STATE_END = 0xFF000000,
	MXD_STATE_END_TYPE_A,
	MXD_STATE_END_TYPE_B,
	MXD_STATE_END_TYPE_C,
	MXD_STATE_END_TYPE_D,
	MXD_STATE_END_TYPE_E,
	MXD_STATE_END_TYPE_F,
	MXD_STATE_END_TYPE_G,
	MXD_STATE_END_TYPE_H,
	MXD_STATE_END_TYPE_I,
	MXD_STATE_END_TYPE_J,
	MXD_STATE_END_TYPE_K,
	MXD_STATE_END_TYPE_L,
	MXD_STATE_END_TYPE_M,
	MXD_STATE_END_TYPE_N,
	MXD_STATE_END_TYPE_O,
	MXD_STATE_END_TYPE_P,
	MXD_STATE_END_TYPE_Q,
	MXD_STATE_END_TYPE_R,
	MXD_STATE_END_TYPE_S,
	MXD_STATE_END_TYPE_T,
	
	MXD_STATE_END_TYPE_U,
	MXD_STATE_END_TYPE_V,
	MXD_STATE_END_TYPE_W,
	
	MXD_STATE_STRANGE = 0xFFFFFFFF
} MXD_STATE;

@interface MXDDCForVectorDraw : MXDDeviceContextDraw  {
	// 現在の描画モードと前の入力の演算方法
	MXD_DM		_currentDM;
	MXD_STATE   _currentState;
	
	// ベクターモード用の保存場所
	MXDVectorSource*	_tmpDataForoVector;
	int					_graphicsCounterForCheck;   // パス描画の回数を比較するため
	int					_tmpPathCont;				// 形式Cのための特別なやつ
	int					_clipPathCounterForCheck;   // パス描画の回数を比較するため
	int					_imageDataCounterForCheck;  // イメージ描画の回数を比較するため
	
	// bug #310対策
	bool			_didTtypeW;
	unsigned long	_penColorOfTypeW;
	
	// テスト用 形式カウンタ
#ifdef _GDI_VECTOR_DEBUG_1
	int		typeA_Counter;
	int		typeB_Counter;
	int		typeC_Counter;
	int		typeD_Counter;
	int		typeE_Counter;
	int		typeF_Counter;
	int		typeG_Counter;
	int		typeH_Counter;
	int		typeI_Counter;
	int		typeJ_Counter;
	int		typeK_Counter;
	int		typeL_Counter;
	int		typeM_Counter;
	int		typeN_Counter;
	int		typeO_Counter;
	int		typeP_Counter;
	int		typeQ_Counter;
	int		typeR_Counter;
	int		typeS_Counter;
	int		typeT_Counter;
	int		typeU_Counter;
	int		typeV_Counter;
	int		typeW_Counter;
#endif
}

- (id)initWithCGContextRef: (CGContextRef)canvas
					width: (int)deviceWidth
					height: (int)deviceHeight
					scale: (float)scale
					documentDpi: (int)documentDpi
					isTransparency: (BOOL)isTransparency;

@end
