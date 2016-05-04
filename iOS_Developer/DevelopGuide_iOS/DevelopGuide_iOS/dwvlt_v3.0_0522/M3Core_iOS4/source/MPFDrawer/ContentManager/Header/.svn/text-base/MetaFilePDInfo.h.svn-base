#ifndef METAFILEPDINFO_H
#define METAFILEPDINFO_H

#include "DocuWorksDecoder/Include/XdwDocuWorksContentManager.h"
#include "DocuWorksDecoder/Access/Header/XdwDocuWorksAccessLittleEndianBinary.h"
#include "DataObject/Base/Include/XdwDataObjectBaseInterface.h"

/*!
 WMF,EMFデータを供給するBinaryInterfaceオブジェクトを管理する
*/

class MetaFilePDInfo : public XdwDocuWorks::ContentManager::PDInfo
{
public:
	/*!
	@brief コンストラクタ
	@note BinaryInterfaceオブジェクトは呼び出し元が所有し、MetaFilePDInfoの生存中は維持すること
	@param[in] binary BinaryIntefaceオブジェクト
	*/
	MetaFilePDInfo(XdwDocuWorks::BinaryInterface* binary);

	/*!
	@brief デストラクタ
	*/
	~MetaFilePDInfo();

	virtual XdwDocuWorks::ContentManager::PDInfo::DataFormat GetFormat();
	virtual long GetMapMode();
	virtual long GetXExt();
	virtual long GetYExt();
	virtual long GetWidth();
	virtual long GetHeight();
	virtual long GetOpaque();
	virtual long GetXPPM();
	virtual long GetYPPM();
	virtual long GetQuality();
	virtual long GetPalette();
	virtual long GetDataSize();
	virtual long GetCompressedSize();

	/*!
	@brief WMF,EMFデータを供給するBinaryInterfaceオブジェクトを取得する
	@note 取得したオブジェクトを破棄してはならない
	@return BinaryInterfaceオブジェクト
	*/
	virtual XdwDocuWorks::BinaryInterface* GetBinaryData();

	virtual bool GetXYExt(long width, long height);

protected:
	/*!
	@brief デフォルトコンストラクタ(使用不可)
	*/
	MetaFilePDInfo();
	
	// 関連
	XdwDocuWorks::BinaryInterface *fBinary;
};

#endif

