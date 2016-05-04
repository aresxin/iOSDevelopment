/** 
 * @file  XdwLinuxZaurusLib.h
 * @brief LinuxZaurus上のAPIをラップしたグローバル関数の定義
 *
 * @author Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-2-26
 * @version 1.0
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_LINUX_ZAURUS_LIB_H_
#define _XDW_LINUX_ZAURUS_LIB_H_

/**
 * @brief 現在のメモリ空き容量を取得(Byte単位)
 *
 * LinuxZaurus安全動作のために、約10Mbを引いた値を返している
 */
long XdwLinuxZaurusGetMemoryEmptySpaceSize();

#endif
