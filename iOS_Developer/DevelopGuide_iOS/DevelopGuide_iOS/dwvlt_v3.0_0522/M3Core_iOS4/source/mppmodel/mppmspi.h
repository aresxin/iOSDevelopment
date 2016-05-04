// File: mppmspi.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999-2004 by Fuji Xerox Co., Ltd. All right reserved.

#include "mpc_api.h"
#include "mppmodel.h"

// V60NA:TOC対応
class CTOCPageFactory;

class ImplMPPModelSPI : MPPModelSPI
{
STDMETHOD(MPPMUpdatePages)(MPCSession* session, MPCObject* mp, MPCContDocument* contDoc);
STDMETHOD(MPPMBreakUpdatePages)(MPCObject* mp, MPCContDocument* contDoc);
STDMETHOD(MPPMMergeMP)(MPCObject* dst_mp, MPCObject* src_mp, MP_Integer nth = -1);
STDMETHOD_(MPCObject*, MPPMCreateNewMetaPaper)(MPCSession* session, MP_Octet* name, MP_Dim dim, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMPullOutOnePage)(MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMCopyOnePage)(MPCObject* mp, MP_Integer nth, HRESULT* phres = NULL);
STDMETHOD(MPPMDIBFileToMetaPaper)(MPCSession* session, const char* srcPath, const char* dstPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level);
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPage)(MPCSession* session, const char* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPage)(MPCSession* session, const char* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageAdv)(MPCSession* session, const char* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);
STDMETHOD_(MPCObject*, MPPMHDIBToBasicPageAdv)(MPCSession* session, void* hDIB, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);
STDMETHOD_(MPCObject*, MPPMTIFFMPFileToBasicPage)(MPCSession* session, MP_File* mpfile, MP_Integer nth, MP_Integer* ppage, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, HRESULT* phres = NULL);
STDMETHOD_(void*, MPPMConvertBasicPageToHDIB)(MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL);
STDMETHOD(MPPMConvertBasicPageToDIBFile)(MPCSession* session, MPCObject* bp, const char* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);
STDMETHOD_(void*, MPPMConvertPDToHDIB)(MPCSession* session, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL);
STDMETHOD(MPPMConvertPDToDIBFile)(MPCSession* session, MP_PD* pd, const char* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);
STDMETHOD_(MPCObject*, MPPM4PullOutOnePage)(MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMDivideAtCurrentPage)(MPCObject* mp, MP_Integer nth, MP_Integer withContDoc, HRESULT* phres = NULL);
STDMETHOD(MPPMEraseBorder)(MPCSession* session, MPCObject* basicPage, MP_Integer top, MP_Integer bottom, MP_Integer left, MP_Integer right, MP_Integer centerLeft, MP_Integer centerRight, MPC_AdvCancelInfo* info = NULL);
STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres);
STDMETHOD(Destroy)();
STDMETHOD(MPPMSetDocumentAttribute)(MPCObject* mp, const char* lpszAttributeName, int nAttributeType, char* pAttributeValue) ;
STDMETHOD(MPPMGetDocumentAttributeNumber)(MPCObject* mp) ;
STDMETHOD(MPPMGetDocumentAttributeByName)(MPCObject* mp, const char* lpszAttributeName, int* nAttributeType, char* pAttributeValue,int nDataSize) ;
STDMETHOD(MPPMGetDocumentAttributeByOrder)(MPCObject* mp, int nOrder, char*lpszAttributeName, int* nAttributeType, char* pAttributeValue, int nDataSize) ;
STDMETHOD(MPPMSucceedAttribute)(MPCObject* mp, DW_refinf* refDWInfo, MP_Integer nSuccession) ;
STDMETHOD_(void*, MPPMConvertBasicPageToHDIBEx)(MPCSession* session, MPCObject* bp, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres = NULL, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);
STDMETHOD(MPPMConvertBasicPageToDIBFileEx)(MPCSession* session, MPCObject* bp, const char* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);
STDMETHOD_(MPCObject*, MPPMDirectImportIMSFileToBasicPage)(MPCSession* session, const char* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer iRotate, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMConvertIMSFileToBasicPage)(MPCSession* pSession, const char* pszImsPath, MP_Dim dimPd, MP_Dim dimPage, MP_Pos posPd, MP_Integer iRotate, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo* pCancelInfo = NULL);
STDMETHOD(MPPMDIBFileToIMSFile)(const char* pszDibPath, const char* pszImsPath,	MP_Integer level, MPC_AdvCancelInfo *info = NULL);
STDMETHOD_(void*, MPPMDIBMemToIMSMem)(const unsigned char* pDibMem, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);
STDMETHOD(MPPMGetIMSInfo)(const char* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes);
STDMETHOD(MPPMGetPDFFromMRCPDPage)(MPCSession* pSession, MPCObject* pPage, const char* pszDestPath );
STDMETHOD_(MP_PD*, MPPMCreatePDfromMemBitmap)(MPCSession* pSession, void* pBmpInfo, unsigned char* pImageData, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo);
STDMETHOD_(MP_PD*, MPPMCreatePDfromBmpFile)(MPCSession* pSession, const char* pszBmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo);
STDMETHOD(MPPMSetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim dimOrgPage, MP_Pos posOrgImage, MP_Dim dimOrgImage );
STDMETHOD(MPPMGetPageLayoutInfo)( MPCObject* pBasicPage, MP_Dim* pDimOrgPage, MP_Pos *pPosOrgImage, MP_Dim* pDimOrgImage );
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRC)( MPCSession* session, const char* srcPath, MP_Integer iCompLevel, MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo );
STDMETHOD_(MPCObject*, MPPMCreateNewMetaPaperW)(MPCSession* session, const MP_Text* name, MP_Dim dim, HRESULT* phres = NULL);
STDMETHOD(MPPMDIBFileToMetaPaperW)(MPCSession* session, const MP_WPath* srcPath, const MP_WPath* dstPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level);
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos,	HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMDIBFileToBasicPageAdvW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo *info = NULL);
STDMETHOD(MPPMConvertBasicPageToDIBFileW)(MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);
STDMETHOD(MPPMConvertPDToDIBFileW)(MPCSession* session, MP_PD* pd, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL);
STDMETHOD(MPPMSetDocumentAttributeW)(MPCObject* mp, const MP_Text* attributeName, int attributeType, const void* pAttributeValue, MP_TAType tatype, int codepage);
STDMETHOD(MPPMGetDocumentAttributeByNameW)(MPCObject* mp, const MP_Text* attributeName, int& attributeType, void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage);
STDMETHOD(MPPMGetDocumentAttributeByOrderW)(MPCObject* mp, int nOrder, MP_String &attributeName, int& attributeType, void* pAttributeValue, int datasize, MP_TAType& tatype, int codepage);
STDMETHOD(MPPMConvertBasicPageToDIBFileExW)(MPCSession* session, MPCObject* bp, const MP_WPath* dstPath, MP_Integer dpi, MPPM_CONVDIB_MODE mode, MPC_AdvCancelInfo* info = NULL, bool bWithAnno = true);
STDMETHOD_(MPCObject*, MPPMDirectImportIMSFileToBasicPageW)(MPCSession* session, const MP_WPath* srcPath, MP_Dim  dimPd, MP_Dim  dimPage, MP_Pos  pos, MP_Integer iRotate, HRESULT* phres = NULL);
STDMETHOD_(MPCObject*, MPPMConvertIMSFileToBasicPageW)(MPCSession* pSession, const MP_WPath* imsPath, MP_Dim dimPd, MP_Dim dimPage, MP_Pos posPd, MP_Integer iRotate, MP_Integer level, HRESULT* phres = NULL, MPC_AdvCancelInfo* pCancelInfo = NULL);
STDMETHOD(MPPMDIBFileToIMSFileW)(const MP_WPath* dibPath, const MP_WPath* imsPath, MP_Integer level, MPC_AdvCancelInfo *info = NULL);
STDMETHOD(MPPMGetIMSInfoW)(const MP_WPath* srcPath, MP_Dim* pImagePix, MP_Dim* pImageRes);
STDMETHOD(MPPMGetPDFFromMRCPDPageW)(MPCSession* pSession, MPCObject* pPage, const MP_WPath* destPath );
STDMETHOD_(MP_PD*, MPPMCreatePDfromBmpFileW)(MPCSession* pSession, const MP_WPath* bmpPath, MP_Dim dimPD, MP_Integer iCompLevel, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo);
STDMETHOD_(MPCObject*, MPPMJPEGFileToBasicPageTryingMRCW)( MPCSession* session, const MP_WPath* srcPath, MP_Integer iCompLevel, MP_Dim dimPd, MP_Dim dimPage, MP_Pos pos, HRESULT* phres, MPC_AdvCancelInfo* pCancelInfo );
STDMETHOD(MPPMGetCustomAttributes)(MPCObject* pObj, MP_PtrArray** ppAttributes);
STDMETHOD(MPPMDestroyCustomAttributes)(MP_PtrArray* pAttributes);
STDMETHOD(MPPMGetCustomAttributeByOrder)(MPCObject* pObj, int order, MP_CustomAttribute* pAttribute);
STDMETHOD(MPPMGetCustomAttributeByName)(MPCObject* pObj, MP_CustomAttribute* pAttribute);
STDMETHOD(MPPMGetCustomAttributeNumber)(MPCObject* pObj);
STDMETHOD(MPPMSetCustomAttribute)(MPCObject* pObj, MP_CustomAttribute* pAttribute);

public:
	// V60NA:TOC対応 メンバ変数を増やしたので、初期化のためのコンストラクタを追加
	ImplMPPModelSPI();

private:
	// V60NA:TOC対応
	CTOCPageFactory* m_pTOCPageFactory;
};

// CHANGE LOG
// 2000.09.26 - Nakazawa - V4.1 新規作成
// 2002.01.30 - Ichikawa - V5.0 追加
// 2002.07.18 - Nakazawa - V5.0 AR7859対応 イメージ変換にアノテ有無フラグを追加
//----V6開発
// 2004.05.21 - Tashiro - V6.0 MRC関連の実装追加
// 2004.06.08 - Tashiro - V6.0 MPPMDirectImportIMSFileToBasicPageの不要引数を削除
// 2004.08.10 - Tashiro - V6.0新規追加関数をインタフェース・クラスにも追加
// 2004.10.07 - Tashiro - AR11341 元のPDFのページレイアウト情報をset/getする関数を追加
// 2004.10.07 - Tashiro - AR11303 JPEGのMRC変換を試み失敗したら直接取り込む関数を追加
// 2004.10.18 - Tashiro - AR11421 PDFの回転状態をDWページに反映させるための機能追加
//----V6NA開発
// 2005.04.01 - Nakazawa - TOCページ処理のインタフェース追加
//----V7開発
// 2007.08.13 - Komoda - V7.0 Unicode I/Fの追加
// 2008.01.17 - Kudo - V7.0 アノテユーザー定義の追加
