#ifndef META_FILE_CONTENT_MANAGER_H
#define META_FILE_CONTENT_MANAGER_H

#include "DocuWorksDecoder/Include/XdwDocuWorksContentManager.h"
#include "DataObject/Base/Include/XdwDataObjectBaseInterface.h"

class MetaFilePDInfo;
class MetaFilePDNthInfo;
class NthDataGenerator;

/*!
 WMF,EMFのデータを提供するオブジェクト(MetaFilePDInfo)を管理する
 MetaFile外部イメージデータを提供するオブジェクト(MetaFilePDNthInfo,NthDataGenerator)を管理する
 再利用ビットマップを扱うオブジェクト(ImageCache)を管理する
*/

class MetaFileContentManager : public XdwDocuWorks::ContentManager
{
public:
	/*!
	@brief コンストラクタ
	@note NthDataGeneratorは呼び出し元が保持し、MetaFileContentManagerが生存している間は維持すること
	@param pdbinary　WMF,EMFを供給するBinaryIntefaceオブジェクト
	@param nthdataGenerator NthDataGeneratorオブジェクト
	*/

	MetaFileContentManager(XdwDocuWorks::BinaryInterface* pdbinary, NthDataGenerator* nthdataGenerator);
	/*!
	@brief デストラクタ
	*/
	~MetaFileContentManager();

public:
	virtual long GetX();
	virtual long GetY();
	virtual long GetWidth();
	virtual long GetHeight();
	virtual XdwDocuWorks::ContentManager::ContentType WhichIsType();
	virtual long GetAngle();
	virtual long GetContentCount();

	/*!
	@brief WMF,EMFデータを供給するPDInfoオブジェクトを取得する
	@note 取得したオブジェクトはMetaFileContentManagerが所有するので、破棄してはならない
	@param なし
	@return PDInfoオブジェクト
	*/
	virtual XdwDocuWorks::ContentManager::PDInfo* GetPD();
	virtual XdwErrorCode SetThumbnailPD();
	virtual XdwDocuWorks::ContentManager::PDInfo* GetThumbnailPD();

	/*!
	@brief N番目の外部イメージの情報を取得する
	@note SetJpeg recordで使われる
	@param[in] id 外部イメージのインデックス(N番目)
	@param[in] isRstRef (使用せず)
	@return XdwErrorCode
	*/
	virtual XdwErrorCode SetPDNth(long id, bool isRstRef);

	/*!
	@brief N番目の外部イメージの情報を取得する
	@note 取得したオブジェクトはMetaFileContentManagerが所有するので、破棄してはならない
	@param なし
	@return PDNthInfoオブジェクト
	*/
	virtual XdwDocuWorks::ContentManager::PDNthInfo* GetPDNth();

	/*!
	@brief 再利用ビットマップをキャッシュに登録する
	@note SetDIB recordで使われる
	@param[in] offset 参照するバイナリオブジェクトからのオフセット(WMF,EMF中のオフセット)
	@param[in] size キャッシュするバイナリデータのサイズ
	@return XdwErrorCode
	*/
	virtual XdwErrorCode SetCache(long offset, long size);

	/*!
	@brief 再利用ビットマップのキャッシュをクローズする
	@param なし
	@return XdwErrorCode
	*/
	virtual XdwErrorCode CloseCache();

	/*!
	@brief 再利用ビットマップを供給するオブジェクトを取得する
	@note SetDIB recordで使われる
	@note 取得したオブジェクトはMetaFileContentManagerが所有するので、破棄してはならない
	@param なし
	@return BinaryInterfaceオブジェクト
	*/
	virtual XdwDocuWorks::BinaryInterface* GetCacheData();

	virtual XdwDocuWorks::ContentManager::LinkAnnotInfo* GetLinkAnnotInfo();
	virtual bool GetContentSize(long width, long height);
	virtual bool GetWMFSize(long width, long height);

protected:
	MetaFileContentManager();
	
	// 集約
	long fContentWidth;
	long fContentHeight;
	//! WMF,EMFデータを供給する
	MetaFilePDInfo* fPdInfo;
	//! キャッシュを管理する
	XdwDocuWorks::BinaryInterface* fImageCache;
	//! 外部イメージを供給する
	MetaFilePDNthInfo* fPDNthInfo;
	//! 外部イメージのインデックス番号
	int fPdNthIndex;

	// 関連
	NthDataGenerator* fNthDataGenerator;
};

#endif

