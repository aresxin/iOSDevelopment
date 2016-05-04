// File: StrWriteData.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 1997-2002 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_WRITE_DATA_H__
#define __STG_WRITE_DATA_H__

#ifndef SFXVW
class ImplStgWriteData {
	
	// Save, SaveAs用

public:
	ImplStgTree*	m_Tree;
	MP_Integer	m_SaveMode;
	long	m_StgObjNum;			// 保存するImplStgObjの数
	long	m_TrailerSize;
	ImplStgMemIO*	m_TreeImage;	// 保存Treeイメージ
	char*	m_CompressedTreeImage;
	long	m_OriginalTreeSize;
	long	m_TreeSize;
	long	m_TreeCheckSum;
	MP_PtrArray*	m_NewBDArray;	// 新規にSetAttributeされたBDのImplAttを作成保持
	long	m_NewBDSize;			// 新規にSetAttributeされたBD全サイズ
	long	m_TreeBDSize;			// ツリー内の削除されていないBD全サイズ
	long*	m_WriteBDOffset;		// ファイルにwriteしたBDのoffsetを保持
	BDID	m_CurrentWriteBDID;		// WriteしたBDのBDID.増加する.
	long	m_CurrentWriteNewBDNum;	// Writeした新規BD数.増加する.
	ImplStgMemIO*	m_MemBuffer;

	//v4
	long	m_TreeEncryptedSize;	// 暗号化後のTreeのサイズ
	MP_Octet*	m_TreeHash;	//暗号化されたTreeのハッシュ値
	char*	m_EncryptedTreeImage;	//暗号化したTreeのイメージ

	long	m_NewBDNum;	//書き出すべき一時BDの数
	long	m_TreeBDNum;	//書き出すべきツリー内BDの数
	BDID*	m_WriteBDTable;	//書き出すべきBDの表
	char*	m_TreeBDValidFlag;	//ツリー内の各BDが必要なデータか調べるワークエリア
	long	m_DeletedLen;	//m_Tree->m_CurrentFileDeletedLenからコピー、検出した不要BDのサイズを加算
	UINT64*	m_InitVectors;	//書き出す各BDの初期化ベクトル(保護文書のみ)
	long	m_ReusableBDNum;	//書き出す因数化可能BDの数
	long*	m_ReusableBDInfo;	//書き出す因数化可能BD情報(BDID＋チェックサム)
	long	m_CurrentReusableBDNum;
	long*	m_OrgSize;

	long m_SignatureDataOffset; // トレーラ内での署名検証データ開始位置

	//V6
	// AR9585 書き込み動作中にツリー内属性アクセスをできないのでメンバ変数で保持
	long m_bHasTMBAttribute;
	long m_iTMPData;
	long m_iStorageVersion;

	ImplStgWriteData( ImplStgTree* tree, HRESULT *phres );
	~ImplStgWriteData();
	HRESULT Destroy(void);
	HRESULT GetNewBDArray(void);
	MP_Integer OptimumSaveMode( ImplStgFileIO* file );
	HRESULT HoldData(void);
	long WriteData( ImplStgFileIO* save_file, HRESULT* phres );
	HRESULT SaveComplete(void);
	ImplStgMemIO* EncodeHeader(void);
	long GetTrailerSize(void);
	ImplStgMemIO* EncodeTrailer(void);

	HRESULT PrepareTreeBD(void);
	BDID SearchSameBDIDInWrittenBD( BDID bdid );
	HRESULT CheckFileSizeLimitation( ImplStgFileIO* file );

private:
	long WriteTreeBD( BDID bdid, BDID new_bdid, ImplStgFileIO* save_file, HRESULT* phres );
	long WriteNewBD( BDID bdid, BDID new_bdid, ImplStgFileIO* save_file, HRESULT* phres );

};
#endif //SFXVW

#endif // __STG_WRITE_DATA_H__

//
//CHANGE LOG
//2002.03.20 - Tashiro - StgTree.h から分離
//2002.04.19 - Tashiro - 署名検証動作の実装
// ---V6
//2004.07.09 - Tashiro - AR9585 書き込み動作中のツリー内属性アクセスによるシークを回避
//----- x64対応
//2005.10.17 - Kudo - x64対応：2.0の宣言追加
//----- 6.2開発
//2006.06.12 - Kudo - の排他処理追加
//---- 7.0 ----
//2007.12.10 - Kitahashi - 2.1対応
