// File: ErrorReport.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 2006 by Fuji Xerox Co,. Ltd. All right reserved.

#if !defined(AFX_ERRORREPORT_H__293092AC_4429_4FE8_80F1_B73BC4AA4F70__INCLUDED_)
#define AFX_ERRORREPORT_H__293092AC_4429_4FE8_80F1_B73BC4AA4F70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <windows.h>

#include "win2mpf.h"
#include "mpc_api.h"
#include "mpcwcstr.h"
#include "stg.h"

class CErrorReport  
{
public:
	CErrorReport();
	virtual ~CErrorReport();

	HRESULT ResetErrorInfo();
	HRESULT SetAPIErrorCode( long int iErrorCode );
	HRESULT SetFilePath( const MP_WPath* pszFilePath );
	HRESULT SetErrorAPI( const MP_Text* pszErrorAPI );
	//HRESULT GetErrorInfo( MP_ErrorInfo* pErrorInfo ) const;
	//HRESULT SetErrorInfo( const MP_ErrorInfo* pErrorInfo );
	HRESULT WriteLogIfNotPrevented() const;


private:
	static HRESULT CopyStr( int iMaxBytes, const char* pszSrc, char* pszDst );
	HRESULT GetFilePath( mpcwcstring& filePath ) const;
	HRESULT GetErrorAPI( mpcwcstring& errorAPI ) const;
	HRESULT AddLogLineKeepingNLines( int iLines, const MP_WPath* pszLogPath ) const;
	HRESULT KeepLatestNLines( int iLines, const MP_WPath* pszLogPath ) const;
	MP_ErrorInfo m_ErrorInfo;


	static HRESULT GetLogFileName(mpcwcstring& path);

};

#endif // !defined(AFX_ERRORREPORT_H__293092AC_4429_4FE8_80F1_B73BC4AA4F70__INCLUDED_)
