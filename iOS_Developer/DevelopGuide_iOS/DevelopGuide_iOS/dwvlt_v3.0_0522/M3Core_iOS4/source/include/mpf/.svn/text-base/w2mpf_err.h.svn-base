//
//  w2m_err.h
//
//  Updater : $Author: komoda $
//  Version : $Revision: 1.1 $, $Date: 2009/01/15 08:03:30 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#ifndef W2M_ERR_H
#define W2M_ERR_H

#include <errno.h>
#include "w2mpf_error.h"

#define initError() (errno = 0)

// Windwos のエラーコード(winerror.h)と UNIXのエラーコード(errno.h)の
// 変換テーブル。
////////////////////////////////////////////////
// errtbl[Windowsエラーコード][UNIXエラーコード]
typedef struct w2u_errtrance {
	unsigned int winerr;
	int unixerr;
} W2U_ERRTRANCE;

#define toWinErr(_cd)	(unsigned int)(_cd & 0xFF0FFFFF)
#define toUnixErr(_cd)	(int)(_cd | 0x00F00000)

static W2U_ERRTRANCE errtrancetbl[] = {
	{ERROR_FILE_NOT_FOUND,        ENOENT},
	{ERROR_PATH_NOT_FOUND,        ENXIO},
	{ERROR_ACCESS_DENIED,         EACCES},
	{ERROR_BAD_FORMAT,            ENOEXEC},
	{ERROR_OUTOFMEMORY,           ENOMEM},
	{ERROR_INVALID_DRIVE,         ENODEV},
	{ERROR_WRITE_FAULT,           EBADF},
	{ERROR_SHARING_VIOLATION,     ETXTBSY},
	{ERROR_LOCK_VIOLATION,        EDEADLK},
	{ERROR_HANDLE_DISK_FULL,      ENOSPC},
//#ifdef _LINUX
#if 0
	{ERROR_BAD_NETPATH,           EREMOTEIO},
	{ERROR_BAD_NET_NAME,          EREMOTEIO},
#endif // _LINUX
	{ERROR_NETWORK_ACCESS_DENIED, ESTALE},
	{ERROR_INVALID_PASSWORD,      EACCES},
	{ERROR_FILE_EXISTS,           EEXIST},
	{ERROR_INVALID_PARAMETER,     EINVAL},
	{ERROR_DISK_FULL,             ENOSPC},
	{ERROR_INSUFFICIENT_BUFFER,   ENOBUFS},
	{ERROR_INVALID_NAME,          EIO},
	{ERROR_BAD_PATHNAME,          ENOENT},
	{ERROR_FILENAME_EXCED_RANGE,  ENAMETOOLONG},
	{ERROR_NO_SUCH_USER,          EACCES},
	{ERROR_LOGON_FAILURE,         EACCES},
	//
	{ERROR_DLL_INIT_FAILED,       toUnixErr(ERROR_DLL_INIT_FAILED)},
	//
	{E_NOTIMPL,                   ENOSYS},
	{E_NOINTERFACE,               toUnixErr(E_NOINTERFACE)},
	{STG_E_CANTSAVE,              toUnixErr(STG_E_CANTSAVE)},
	{STG_E_OLDFORMAT,             toUnixErr(STG_E_OLDFORMAT)},
	{STG_E_OLDDLL,                toUnixErr(STG_E_OLDDLL)},
	{E_INVALIDARG,                EINVAL},
	{0, 0} //
};
////////////////////////////////////////////////

// UNIXでのシステムエラーコードを示す errno の値を、
// Windows の winerror.h に定義されているコードに
// 変換して返す。
unsigned int unixerr2winerr();

// Windows の winerror.h に定義されているコードを
// UNIXでのシステムエラーコードに変換して返す。
int winerr2unixerr(unsigned int winerr);

#endif /* W2M_ERR_H */

