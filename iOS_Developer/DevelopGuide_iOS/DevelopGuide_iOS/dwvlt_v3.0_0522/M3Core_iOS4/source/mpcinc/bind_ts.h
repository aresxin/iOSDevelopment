// File: BIND_TS.H
// Auther: Toshiyuki Komoda
// Copyright(C) 2004 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef BIND_TS_H
#define BIND_TS_H

#ifndef MPCOREAPI_H
#include "mpc_api.h"
#endif

/*
#ifndef _WINDOWS_
#include "windows.h"
#endif
*/

#include "mpc_text.h"

MPC_EXTERN_GUID(IID_SPIBindTextSearch, 0x1330);

mpinterface SPIBindTextSearch : public MPCInterface
{
STDMETHOD_(MPCTextSearch*, CreateTextSearch)(MPCSession* session, HRESULT* phres) PURE;
};

#endif
