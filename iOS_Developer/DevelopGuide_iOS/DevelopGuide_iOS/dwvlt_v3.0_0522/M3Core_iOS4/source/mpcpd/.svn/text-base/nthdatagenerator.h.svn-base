#ifndef NTHDATAGENERATOR_H
#define NTHDATAGENERATOR_H

struct MPCSession;
struct IStgObject;

/*!
MetaFile外部イメージデータを供給するオブジェクト
 */

class NthDataGenerator
{
public:
	/*!
	@brief コンストラクタ
	@param[in] session MPCSessionオブジェクトのポインタ
	@param[in] stgobj ストレージオブジェクトのポインタ
	*/
	NthDataGenerator(MPCSession* session, IStgObject* stgobj);

	/*!
	@brief デストラクタ
	@param なし
	*/
	virtual ~NthDataGenerator();

	/*!
	@brief イメージデータのサイズを取得する
	@param[in] n イメージの番号
	@return イメージデータのサイズ
	*/
	virtual long GetDataSize(int n);

	/*!
	@brief イメージデータを取得する
	@param[in] n イメージの番号
	@param[out] buffer イメージデータを受け取るバッファ
	@return 成功/失敗
	*/
	virtual bool GetData(int n, unsigned char* buffer);

//protected:
	/*!
	@brief デフォルトコンストラクタ(使用不可)
	*/
	NthDataGenerator();

protected:
	// 関連
	MPCSession* fSession;
	IStgObject* fStgObject;
};

#endif

