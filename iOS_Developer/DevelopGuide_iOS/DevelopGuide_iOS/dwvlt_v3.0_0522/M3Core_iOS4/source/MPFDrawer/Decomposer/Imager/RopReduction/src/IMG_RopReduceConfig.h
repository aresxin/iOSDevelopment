/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_RopReduceConfig.h - ROP置換のコンフィグレーションヘッダ
 * Yozo Kashima 20.Jul.2001
 *
 */

#ifndef INC_IMG_RopReduceConfig_h
#define INC_IMG_RopReduceConfig_h


enum { IMG_MAX_ROP_STEP	= 4 };					/* ROPステップの最大数 */
enum { IMG_MAX_CANDIDATE = 4 };					/* ROP置換方法の候補の最大数 */
enum { IMG_MAX_CMD_CHECK = IMG_MAX_CANDIDATE };	/* コマンド検査オブジェクトの最大数 */


#endif /* INC_IMG_RopReduceConfig_h */

/*
 * Log
 * 18.Feb.2002 Yozo Kashima  Created
 */

/* end of IMG_RopReduceConfig.h */

