//
// w2m_mutex.h
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.4 $, $Date: 2009/12/22 08:11:18 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2007 Fuji Xerox Co., Ltd. All rights reserved.
//
//  since DWVLT62 BTS#33

#ifndef __W2M_MUTEX_H__
#define __W2M_MUTEX_H__

// MXDDecodeUtl の mutex
int LockMutexForMXCDecodeUtl_GetDIBHeaderDst();
int UnlockMutexForMXCDecodeUtl_GetDIBHeaderDst();

// w2m_base の mutex
int LockMutexForW2MBase_DeleteOnCloseHandles();
int UnlockMutexForW2MBase_DeleteOnCloseHandles();

// w2m_gdi の mutex
int LockMutexForW2MGdi_phtbl();
int UnlockMutexForW2MGdi_phtbl();

// ここで提供する mutex の初期化と解放
int InitMutexForW2M();
int DestroyMutexForW2M();

#endif //__W2M_MUTEX_H__
