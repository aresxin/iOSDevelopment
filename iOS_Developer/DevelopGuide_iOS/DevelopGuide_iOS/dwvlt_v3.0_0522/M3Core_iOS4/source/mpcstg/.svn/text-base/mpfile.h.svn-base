// File: MPFILE.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

#include "mp_file.h"
//#include "windows.h"

#ifndef ZINTEGSFX
#include "errorreport.h"
#endif
#include "mpcwcstr.h"

class ImplMPFile : public MP_File {

friend MP_File* MP_File_Create_Impl(const MP_WPath* fileName, HRESULT* phres, MP_Integer deleteFileOnClose, MP_Integer overwrite, MP_Integer hidden);
friend MP_File* MP_File_Open_Impl(const MP_WPath* fileName, MP_OpenMode omMode, HRESULT* phres, MP_Integer deleteFileOnClose, MP_Integer canBeShared);
friend ImplMPFile* MP_File_From_Handle_Impl(const MP_WPath* fileName, HANDLE hFile, MP_OpenMode omMode, HRESULT* phres);
friend MP_File* MP_File_Open_From_Handle(const MP_WPath* fileName, HANDLE hFile, MP_OpenMode omMode, HRESULT* phres, MP_Integer deleteFileOnClose);

public:
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL) {
		return NULL; }
	STDMETHOD(Destroy)();
	STDMETHOD_(long, Seek)(long seekPos, MP_SeekMethod seekMode=MP_SEEK_BEGIN);
	STDMETHOD_(long, Read)(void *buf, long readSize);
	STDMETHOD_(long, Write)(const void* buf, long writeSize);
	STDMETHOD(Close)(long bDestroy=1);
	STDMETHOD_(long, Size)();
	STDMETHOD_(const char*, GetFilePath)();
	STDMETHOD(GetFilePathW)(MP_String& path);

	STDMETHOD_(MP_OpenMode, GetOpenMode)(){
		return m_omode; };
	STDMETHOD(SetFileSize)(MP_Integer size);
	STDMETHOD(CheckValidity)();

	HRESULT WillBeDeletedOnClose();

private:
	HANDLE m_nHandle;
	mpcwcstring m_filepath;
	std::string m_mbfilepath;
	MP_OpenMode	m_omode;
	long m_pos;
	long m_size;
	ImplMPFile();
	~ImplMPFile();

	DWORD m_dwCreateAtt;
	DWORD m_dwLastWrittenTimeLow;

	// WindowsAPIレベルのエラー情報 (AR13054)
#if defined _PF_WIN32_ || defined _PF_WINCE_
 #ifndef ZINTEGSFX
	CErrorReport m_ErrorReport;
 #endif
#endif

	long OpenOnDemand();
	long CloseOnDemand();
};

class ImplPartialMPFile : public MP_File {
 public:
	MP_File* m_MPFile;
	long m_startOffset;
	long m_endOffset;
	long m_size;
	long m_realOffset;

	ImplPartialMPFile(MP_File* mpfile, long start_offset, long size);
	~ImplPartialMPFile();

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL);
	STDMETHOD(Destroy)();
	STDMETHOD_(long, Seek)(long seekPos, MP_SeekMethod seekMode=MP_SEEK_BEGIN);
	STDMETHOD_(long, Read)(void *buf, long readSize);
	STDMETHOD_(long, Write)(const void* buf, long writeSize);
	STDMETHOD(Close)(long bDestroy=1);
	STDMETHOD_(long, Size)();
	STDMETHOD_(const char*, GetFilePath)();
	STDMETHOD(GetFilePathW)(MP_String& path);

	STDMETHOD_(MP_OpenMode, GetOpenMode)();
	STDMETHOD(SetFileSize)(MP_Integer size);
	STDMETHOD(CheckValidity)();
};

//2004.04.06 - Tashiro - V6.0 ImplMPFileをmpcstg内の他からも使うためMPFILE.CPPから分離
//2004.04.07 - Tashiro - V6.0 IsValid→CheckValidity名称変更
//2004.08.23 - Tashiro - AR9951 ファイル生成時から隠し属性を付ける関数を追加
//2006.07.20 - Tashiro - V6.2 DE向けファイルオープン機能追加
//2006.12.22 - Tashiro - V6.2 AR13054 WindowsAPIのエラー情報を保持する
//2007.08.17 - Komoda  - V7.0 Unicode I/Fの追加
