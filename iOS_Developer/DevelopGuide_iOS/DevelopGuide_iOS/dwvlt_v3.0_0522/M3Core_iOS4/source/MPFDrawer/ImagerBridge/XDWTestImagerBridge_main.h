/*---------------------------------------------------------------------------*/
/* Copyright (C) Fuji Xerox Co.,Ltd. 1997. All right reserved.               */
/*                                                                           */
/*  XDWTestImagerBridge_main.h --- main routine of XDW Imager Bridge Beta_Version.  */
/*  plw_main.h --- を修正						     */
/*                                                                           */
/*  Created       :  April 30, 1997 By Toshiaki Kato (ATEC DITDD CT2CG)      */
/*  Modified      :  Sep.  2   1998 by Yozo Kashima (AR1327,1329)	     */
/*  Modified      :  April.10  1999 by Yozo Kashima (added cache reset i/f)  */
/*  Modified      :  Jun.15    2000 by Toshiaki Kato(added PlwDeleteForm i/f)*/
/*  Last Modified :                                                          */
/*---------------------------------------------------------------------------*/

#ifndef XDWTESTIMAGERBRIDGE_INCLUDED
#define XDWTESTIMAGERBRIDGE_INCLUDED

#include	"XdwError.h"

#define		NEW_JOB		1
#define		RENEW_JOB	2

#define		PLW_MAX_FORM_NUM	2048

extern		XdwErrorCode XdwImagerBridgeTest_StstartProcess(bool,bool,bool,bool);
extern		XdwErrorCode XdwImagerBridgeTest_DoProcess(void);
extern		XdwErrorCode XdwImagerBridgeTest_EndProcess(void);
#ifdef SIF
extern		XdwErrorCode XdwImagerBridgeTest_FontCacheClear(void);


#endif

void XdwImagerBridgeTest_InitForm(int max_num_forms);
void XdwImagerBridgeTest_DeleteForm(const char *formName, unsigned short int formId);

#endif // XDWTESTIMAGERBRIDGE_INCLUDED
