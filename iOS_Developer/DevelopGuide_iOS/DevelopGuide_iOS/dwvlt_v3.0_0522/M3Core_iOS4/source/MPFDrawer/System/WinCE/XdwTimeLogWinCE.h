// XdwTimeLogWinCE.h: XdwTimeLogWinCE クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////
// created by t.kitahashi 2003.1.31

#if !defined(AFX_XDWTIMELOGWINCE_H__EA026FA1_030D_40F5_92B0_80DAA66EDEC3__INCLUDED_)
#define AFX_XDWTIMELOGWINCE_H__EA026FA1_030D_40F5_92B0_80DAA66EDEC3__INCLUDED_

#include "XdwFileIOWinCE.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class XdwTimeLogWinCE  
{
public:
	virtual void Write(const char* str);
	XdwTimeLogWinCE();
	virtual ~XdwTimeLogWinCE();


protected:
	XdwFileIOWinCE fFileIO;
	void* fFile;
};

#endif // !defined(AFX_XDWTIMELOGWINCE_H__EA026FA1_030D_40F5_92B0_80DAA66EDEC3__INCLUDED_)
