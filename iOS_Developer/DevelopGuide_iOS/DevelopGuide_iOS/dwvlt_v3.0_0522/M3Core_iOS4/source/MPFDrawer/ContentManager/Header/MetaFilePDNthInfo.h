#ifndef METAFILEPDNTHINFO_H
#define METAFILEPDNTHINFO_H

#include "DocuWorksDecoder/Include/XdwDocuWorksContentManager.h"
#include "DataObject/Base/Include/XdwDataObjectBaseInterface.h"

/*
MF外部イメージデータを供給するBinaryInterfaceオブジェクトを管理する
*/

class MetaFilePDNthInfo : public XdwDocuWorks::ContentManager::PDNthInfo
{
public:
	/*!
	@brief コンストラクタ
	@note コピーを作るので、イメージデータはすぐ破棄してよい
	@param[in] data  外部イメージデータ(ヘッダ含む)のポインタ
	@param[in] datasize 外部イメージデータのバイト数
	*/
	MetaFilePDNthInfo(const unsigned char* data, long datasize);

	/*!
	@brief デストラクタ
	@param なし
	*/
	~MetaFilePDNthInfo();

	virtual DataFormat GetFormat();
	virtual long GetWidth();
	virtual long GetHeight();
	virtual long GetDataSize();

	/*!
	@brief JPEGデータを供給するBinaryInterfaceオブジェクトを取得する
	@note 受け取ったBinaryInterfaceオブジェクトはMetaFilePDNthInfoの所有、破棄してはならない
	@param なし
	@return BinaryInterfaceオブジェクト
	*/
	virtual XdwDocuWorks::BinaryInterface* GetBinaryData();

protected:
	/*!
	@brief デフォルトコンストラクタ(使用不可)
	*/
	MetaFilePDNthInfo();

	/*!
	@brief イメージデータのヘッダを読み出す
	@param[in] data  外部イメージデータ(ヘッダ含む)のポインタ
	@param[in] datasize 外部イメージデータのバイト数
	@return 成功/失敗
	*/
	bool ReadImageHeader(const unsigned char* data, long dataSize);
	
	// 集約
	long fWidth;
	long fHeight;
	long fDataSize;
	XdwDocuWorks::BinaryInterface *fBinaryInterface;
};

#endif

