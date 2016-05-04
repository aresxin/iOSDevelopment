// File: mrcmutil.h
// Auther: 
// Copyright(C) 2007 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MPPUTIL_H_
#define _MPPUTIL_H_

#include "mpc_api.h"

HRESULT GetTempPathW(MPCSession* pSession, MP_String& wcpath);
HRESULT GetTempPath(MPCSession* pSession, char* pszTempPath);

#endif //MPC_SPI_H

