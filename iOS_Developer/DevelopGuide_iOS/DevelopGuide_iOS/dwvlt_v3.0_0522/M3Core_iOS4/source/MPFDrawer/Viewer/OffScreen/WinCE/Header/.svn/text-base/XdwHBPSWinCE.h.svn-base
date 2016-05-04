/** 
 * @file  XdwHBPSWinCE.h
 * @brief Windows CE上でIMG_StartPageをたたくための関数の宣言
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwHBPSWinCE.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_HBPS_WIN_CE_H_
#define _XDW_HBPS_WIN_CE_H_

extern "C"{

/**
 * @brief IMG_StartPage関数をたたく
 * 
 * windows.hをIncludeして、IMG_Imager.hをIncludeすると、XdwBridgeDrawIF::CreateFontかPOINT構造体かで選択を迫れる
 * HBPSBridgeでは、Windows環境に依存させないため、こちら側もこの用に対応
 * 
 * @return IMG_StartPageの戻り値
 */
int XdwWinCE_HBPS_StartPage(void *imager, unsigned short x, unsigned short y, unsigned char	*pageBuffer, long lineSize, long depth, void *DC);

}

#endif
