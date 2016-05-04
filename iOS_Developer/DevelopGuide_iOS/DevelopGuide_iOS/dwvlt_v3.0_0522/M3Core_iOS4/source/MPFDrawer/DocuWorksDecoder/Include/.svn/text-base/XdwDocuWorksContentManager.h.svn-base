/**
 * @file  XdwDocuWorksContentManager.h
 * @brief XdwDocuWorks::ContentManagerインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksContentManager.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 * @date 2002-11-19 LinkAnnotInfoを追加 Yasuhiro Ito <br>
 *
 * @date 2003-09-08 多言語、署名アノテーション対応 Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-06-16 MRC(V6対応) Yasuhiro.Ito@fujixerox.co.jp
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_CONTENT_MANAGER_H_
#define _XDW_DOCUWORKS_CONTENT_MANAGER_H_

/* パッケージを記述したIncludeファイル */
#include "XdwDocuWorks.h"

/**
 * @interface XdwDocuWorks:::ContentManager XdwDocuWorksContentManager.h
 * @brief DocuWorksファイルの指定されたコンテントに関する情報を管理するインターフェース
 *
 * クライアントは本インターフェースのインスタンスの削除は認めない<br>
 * 本インターフェースを利用して、コンテントの表示位置や
 * コンテントの種類などを取得することができる
 */
class XdwDocuWorks::ContentManager
{
public:
  
	/********************************************/
    /* クラス */
    
    /**
     * @interface XdwDocuWorks:::ContentManager::LinkAnnotInfo XdwDocuWorks:FileFormatContentManager.h
     * @brief DocuWorksファイルのLinkAnnotationの情報を取得するためのインターフェース
     *
     * クライアントは本インターフェースのインスタンスの削除は認めない<br>
     * 本インターフェースを利用して、コンテントの表示位置やリンクに関する情報，
     * コンテントのグラフィックフォーマットなどを取得することができる<br><Br>
	 * V5の情報まで取得可能
     */    
	class LinkAnnotInfo{
	public:
		/********************************************/
        /* 列挙型(V4) */	
		/*! リンクアノテーションの参照先属性(V4) */
		enum LinkTo{
			/*! 自分自身 */
			LINK_TO_ME = 0,
			/*! DocuWorksファイル */
			LINK_TO_XDW = 1,
			/*! URL */
			LINK_TO_URL = 2,
			/*! 他ファイル */
			LINK_TO_OTHERFILE = 3,
			/*! メールアドレス */
			LINK_TO_MAILADDRESS = 4,
			/*! データなし*/
			LINK_TO_NO_DATA
		};
		/*! ページ属性(V4) */
		enum LinkPageAttribute{
			/*! 「この文書」指定*/
			LINK_THIS_FILE = 0,
			/*! 「このバインダの通しページ」指定*/
			LINK_BINDER_ALLPAGE = 1,
			/*! 「このバインダの他の文書ページ」指定*/
			LINK_BINDER_OTHER_DOC = 2,
			/*! データなし*/
			LINK_PAGE_NO_DATA
		};

        /********************************************/
        /* メソッド (V4対応)*/
        
        /**
         * @brief リンク先情報の取得(V4)
         * 
         * @return XdwDocuWorks::ContentManager::LinkAnnotInfo::LinkTo参照
         */		
		virtual LinkTo GetLinkTo() = 0;
		 /**
         * @brief 透過属性をもつかどうか？(V4)
         *
		 * @retval true 透過
		 * @retval false 不透過
         * @return bool
         */		
		virtual bool IsTransparent() = 0;
		 /**
         * @brief アイコン表示をするかどうか？(V4)
         *
		 * @retval true する
		 * @retval false しない
         * @return bool
         */		
		virtual bool IsDisplayIcon() = 0;
		 /**
         * @brief オートリサイズをするかどうか？(V4)
         *
		 * @retval true する
		 * @retval false しない
         * @return bool
         */	
		virtual bool IsAutoResize() = 0;
		 /**
         * @brief リンクボタンのタイトル文字取得(V4)
         *
		 * @return char*
         */	
		virtual const char* GetTitleString() = 0;
		 /**
         * @brief URL文字列取得(V4)
         * @retval XdwNullはデータなし
         * @return char*
         */	
		virtual const char* GetUrlString() = 0;
		/**
        * @brief XDW文書パス文字列取得(V4)
        * @retval XdwNullはデータなし
        * @return char*
        */	
		virtual const char* GetXdwString() = 0;
		/**
        * @brief 内部文書名(V4)
        * @retval XdwNullはデータなし
        * @return char*
        */	
		virtual const char* GetSeafnameString() = 0;
		/**
        * @brief タイトル文字のフォントフェイス(V4)
        * @retval XdwNullはデータなし
        * @return char*
        */	
		virtual const char* GetTitleFace() = 0;		
		/**
        * @brief タイトル文字のフォントスタイル(V4)
        * @retval XdwNullはデータなし
        * @return long
        */			
		virtual long GetTitleStyle() = 0;
		/**
        * @brief タイトル文字のポイントサイズ(V4)
        * @retval -1はデータなし
        * @return long
        */		
		virtual long GetTitlePointSize() = 0;	
		/**
        * @brief タイトル文字のフォントカラー(V4)
        * @retval -1はデータなし
        * @return long
        */		
		virtual long GetTitleColor() = 0;
		/**
        * @brief タイトル文字のファミリー (V4)
        * @retval -1はデータなし
        * @return long
        */		
		virtual long GetTitlePitchAndFamily() = 0;
		/**
        * @brief タイトル文字の文字セット(V4)
        * @retval -1はデータなし
        * @return long
        */		
		virtual long GetTitleCharSet() = 0;
		/**
        * @brief Xdw文書のページ番号(0ならprofile)(V4)
        * @retval -1はデータなし
        * @return char*
        */	
		virtual long GetXdwPageNum() = 0;
		/**
		* @brief ページ属性(V4)
		*
		* リンク先の指定がどのページをさしているかを示している．<br>
		* 詳細はXdwDocuWorks::ContentManager::LinkAnnotInfo::LinkPageAttribute
		*
		* @return XdwDocuWorks::ContentManager::LinkAnnotInfo::LinkPageAttribute
		*/
		virtual LinkPageAttribute GetPageCheck() = 0;

		/**
		* @brief リンクアノテの幅が約2700mmを超えているかどうか？<br> 
		*
		* Viewer上では、このフラグがTRUEの場合は通常の表示ですが、サイズを超えた場合は、格子表示になります。 
		* 
		* @retval true :通常表示
		* @retval false:格子表示する
		* @return bool
		*/
		virtual bool IsTextTooLarge() = 0;

	public:
		 /********************************************/
        /* 列挙型(V5) */
		/*! ページ指定かリンクアノテへのジャンプかどうか(V5)*/
		enum LinkJumpType{
			/*! ページへのジャンプ*/
			LINK_TO_DWTYPE_PAGE = 0,
			/*! リンクアノテへのジャンプ*/
			LINK_TO_DWTYPE_LINKANN = 1,
			/*! データなし*/
			LINK_TO_DWTYPE_NO_DATA
		};
		/*! コンボボックスで使用するときの定義，LinkToと整合性を取る(V5)*/
		enum LinkCombType{
			/*! WWWへのリンク*/
			LINK_TARGET_WWW = 0,
			/*! DWデータへのリンク*/
			LINK_TARGET_DWDATA = 1,
			/*! 他ファイルへのリンク*/
			LINK_TARGET_OTHER = 2,
			/*! Eメールへのリンク*/
			LINK_TARGET_MAIL = 3,
			/*! データなし*/
			LINK_TARGET_NO_DATA
		};

		/********************************************/
        /* メソッド (V5対応)*/
		/**
        * @brief メールアドレス文字列の取得(V5)
        *
        * @return char*
        */		
		virtual const char* GetMailadressString() = 0;
		/**
        * @brief DW以外のファイルへのパス文字列の取得(V5)
        *
        * @return char*
        */		
		virtual const char* GetOtherFilePathString() = 0;
		/**
        * @brief DW文書のリンクタイトルジャンプのタイトル文字列の取得(V5)
        *
        * @return char*
        */		
		virtual const char* GetLinkTitleString() = 0;
		/**
        * @brief ユーザが指定したツールチップ文字列の取得(V5)
        *
        * @return char*
        */		
		virtual const char* GetUserTooltipString() = 0;
		/**
        * @brief DW文書のジャンプで，このファイル，他のファイルの指定を取得(V5)
        *
        * @return  XdwDocuWorks::ContentManager::LinkAnnotInfo::LinkJumpType
        */		
		virtual LinkCombType GetDwJumpFileType() = 0;
		/**
        * @brief DW文書の場合のページ指定かリンク指定かの取得(V5)
        *
        * @return XdwDocuWorks::ContentManager::LinkAnnotInfo:: LinkCombType
        */		
		virtual LinkJumpType GetDwJumpType() = 0;
		/**
        * @brief ツールチップのユーザ指定の判別(V5)
        * 
		* @retval true ユーザ指定あり
		* @retval false ユーザ指定なし
        * @return bool
        */		
		virtual bool IsUserTooltip() = 0;
		/**
        * @brief 糊付pけ属性の判別
        * 
		* リンクアノテーションの固定フラグ(V5)
		* 
		* @retval true 指定あり
		* @retval false 指定なし
        * @return bool
        */		
		virtual bool IsStarch() = 0;
		/**
        * @brief DWファイル以外のファイルパスが相対パスであるかどうかの判別(V5)
        * 
		* @retval true 相対パス
		* @retval false 絶対パス
        * @return bool
        */		
		virtual bool IsOtherFileRelative() = 0;
		/**
        * @brief DWファイルのファイルパスが相対パスであるかどうかの判別(V5)
        * 
		* @retval true 相対パス
		* @retval false 絶対パス
        * @return bool
        */	
		virtual bool IsDwFileRelative() = 0;

	};

    /********************************************/
    /* クラス */
    
    /**
     * @interface XdwDocuWorks:::ContentManager::PDInfo XdwDocuWorks:FileFormatContentManager.h
     * @brief DocuWorksファイルのPDの情報を取得するためのインターフェース
     *
     * クライアントは本インターフェースのインスタンスの削除は認めない<br>
     * 本インターフェースを利用して、コンテントの表示位置や
     * コンテントのグラフィックフォーマットなどを取得することができる
     */
    class PDInfo{
    public:
        
        /********************************************/
        /* 列挙型 */
        
        /*! コンテントのグラフィックフォーマットを規定するための定義 */
        enum DataFormat{
            /*! フォーマット不明 */
            INVALID_FORMAT = 0xFFFFFFFF,

            /*! WMFフォーマット */
            WMF_FORMAT = 1,
            /*! EMFフォーマット */
            EMF_FORMAT = 4,
            /*! DocuWorks Ver. 3以前のOKD圧縮されたDIBフォーマット */
            V3_OKD_FORMAT = 2,
            /*! DocuWorks Ver. 4以降のOKD圧縮されたDIBフォーマット */
            V4_OKD_FORMAT = 7,
            /*! DocuWorks Ver. 3以前のMH圧縮されたラスタデータ */
            V3_MH_FORMAT = 3,
            /*! DocuWorks Ver. 4以降のMH圧縮されたラスタデータ */
            V4_MH_FORMAT = 8,
            /*! MMR圧縮されたラスタデータ */
            MMR_FORMAT = 9,
            /*! Jpegフォーマット*/
            JPEG_FORMAT = 5,
            /*! ALLA圧縮されたDIBフォーマット */
            ADAPTIVE_FORMAT = 10,
			/*! MRCフォーマット*/
			MRC_FORMAT = 11
        };
        
        /********************************************/
        /* メソッド */
        
        /**
         * @brief PDに格納されているグラフィックデータのフォーマットを取得する
         *
         * @return XdwDocuWorks::ContentManager::PDInfo::DataFormat参照
         */
        virtual DataFormat GetFormat() = 0;
        
        /**
         * @brief WMFのMETAFILEPICT構造体のマッピングモードの取得
         *
         * @return WMFのMETAFILEPICT構造体のマッピングモード
         */
        virtual long GetMapMode() = 0;
        
        /**
         * @brief WMFのMETAFILEPICT構造体の水平方向の描画サイズの取得
         *
         * @return WMFのMETAFILEPICT構造体の水平方向の描画サイズ
         */
        virtual long GetXExt() = 0;
        
        /**
         * @brief WMFのMETAFILEPICT構造体の垂直方向の描画サイズの取得
         *
         * @return WMFのMETAFILEPICT構造体の垂直方向の描画サイズ
         */
        virtual long GetYExt() = 0;
        
        /**
         * @brief グラフィックデータの横幅の取得
         *
         * @return グラフィックデータの横幅(pixel単位)
         */
        virtual long GetWidth() = 0;

        /**
         * @brief グラフィックデータの縦幅の取得
         *
         * @return グラフィックデータの縦幅(pixel単位)
         */
        virtual long GetHeight() = 0;
        
        /**
         * @brief 不透過扱いの可否の取得
         *
         * @retval 1 不透過PD扱い可(キャッシュBMP利用可)
         * @retval 1以外 (キャッシュBMP利用不可)
         */
        virtual long GetOpaque() = 0;
        
        /**
         * @brief DIBのBITMAPINFOHEADER構造体の水平方向の解像度の取得
         *
         * @return DIBのBITMAPINFOHEADER構造体の水平方向の解像度
         */
        virtual long GetXPPM() = 0;
        
        /**
         * @brief DIBのBITMAPINFOHEADER構造体の垂直方向の解像度の取得
         *
         * @return DIBのBITMAPINFOHEADER構造体の垂直方向の解像度
         */
        virtual long GetYPPM() = 0;
        
        /**
         * @brief 圧縮時の画質の取得
         *
         * @return 圧縮時の画質
         */
        virtual long GetQuality() = 0;
        
        /**
         * @brief 極性の取得
         *
         * @retval 0 黒が0
         * @retval 1 白が0
         */
        virtual long GetPalette() = 0;
        
        /**
         * @brief グラフィックデータのサイズの取得
         *
         * @return グラフィックデータのサイズ(Byte数)
         */
        virtual long GetDataSize() = 0;
        
        /**
         * @brief グラフィックデータの圧縮サイズの取得
         *
         * @return グラフィックデータの圧縮サイズ(Byte数)
         */
        virtual long GetCompressedSize() = 0;
        
        /**
         * @brief グラフィックデータが格納されているバイナリデータを管理するクラスを取得する
         *
         * @return XdwDocuWorks::BinaryInterfaceのインスタンス
         */
        virtual XdwDocuWorks::BinaryInterface* GetBinaryData() = 0;
    };
    
    /**
     * @interface XdwDocuWorks:::ContentManager::PDNthInfo XdwDocuWorks:FileFormatContentManager.h
     * @brief DocuWorksファイルの配列指定型PDの情報を取得するためのインターフェース
     *
     * クライアントは本インターフェースのインスタンスの削除は認めない<br>
     * 本インターフェースを利用して、コンテントの表示位置や
     * コンテントのグラフィックフォーマットなどを取得することができる
     */
    class PDNthInfo{
    public:
        
        /********************************************/
        /* 列挙型 */
        
        /*! コンテントのグラフィックフォーマットを規定するための定義 */
        enum DataFormat{
            /*! Jpegフォーマット */
            JPEG_FORMAT = 0
        };
        
        /********************************************/
        /* メソッド */
        
        /**
         * @brief 配列指定型PDに格納されているグラフィックデータのフォーマットを取得する
         *
         * @return XdwDocuWorks::ContentManager::PDNthInfo::DataFormat参照
         */
        virtual DataFormat GetFormat() = 0;
        
        /**
         * @brief グラフィックデータの横幅の取得
         *
         * @return グラフィックデータの横幅(pixel単位)
         */
        virtual long GetWidth() = 0;

        /**
         * @brief グラフィックデータの縦幅の取得
         *
         * @return グラフィックデータの縦幅(pixel単位)
         */
        virtual long GetHeight() = 0;

        /**
         * @brief グラフィックデータのサイズの取得
         *
         * @return グラフィックデータのサイズ(Byte数)
         */
        virtual long GetDataSize() = 0;
        
        /**
         * @brief グラフィックデータが格納されているバイナリデータを管理するクラスを取得する
         *
         * @return XdwDocuWorks::BinaryInterfaceのインスタンス
         */
        virtual XdwDocuWorks::BinaryInterface* GetBinaryData() = 0;
    };

    /********************************************/
    /* 列挙型 */

    /*! ページを構成するコンテントの種類 */
    enum ContentType{
        /*! 不明なコンテント */
        INVALID_CONTENT = 0xFFFFFFFF,

        /*! OLEアノテーション */
        OLE_ANNOTATION = 0x800F,
        /*! 地のコンテント */
        BASIC_CONTENT = 0x8010,
        /*! テキストアノテーション */
        TEXT_ANNOTATION = 0x8011,
        /*! 付箋アノテーション */
        POSTIT_ANNOTATION = 0x801A,
        /*! ストロークアノテーション */
        STROKE_ANNOTATION = 0x801B,
        /*! ページヘッダ */
        PAGE_HEADER = 0x802E,
        /*! デート印アノテーション */
        DATE_STAMP_ANNOTATION = 0x8033,
        /*! 直線アノテーション */
        LINE_ANNOTATION = 0x803C,
        /*! 四角形アノテーション */
        RECTANGLE_ANNOTATION = 0x803D,
        /*! 円弧アノテーション */
        ARC_ANNOTATION = 0x803E,
        /*! ビットマップアノテーション */
        BITMAP_ANNOTATION = 0x803F,
        /*! 多角形アノテーション */
        POLYGON_ANNOTATION = 0x8042,
        /*! リンクアノテーション */
        LINK_ANNOTATION = 0xC02F,
		/*! 英語版日付印*/
		ENG_DATE_ANNOTATION = 0x8040,
		/*! 韓国語版Received印*/
    	KOR_RECEIVED_ANNOTATION = 0x8041,
		/*!署名オブジェクト*/
		SIGNATURE_ANNOTATION = 0x8043,
		/*!印鑑ケース*/
		SEAL_CASE_ANNOTATION = 0xC044
    };

    /********************************************/
    /* メソッド */

    /**
     * @brief ペーパー上でのコンテントの水平方向の表示位置を取得する
     *
     * @return ペーパー上でのコンテントの水平方向の表示位置(1/100mm単位)<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetX() = 0;

    /**
     * @brief ペーパー上でのコンテントの垂直方向の表示位置を取得する
     *
     * @return ペーパー上でのコンテントの垂直方向の表示位置(1/100mm単位)<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetY() = 0;

    /**
     * @brief ペーパー上でのコンテントの横幅を取得する
     *
     * @return ペーパー上でのコンテントの横幅(1/100mm単位)
     * @return エラーの場合は-1以下
     */
    virtual long GetWidth() = 0;

    /**
     * @brief ペーパー上でのコンテントの縦幅を取得する
     *
     * @return ペーパー上でのコンテントの縦幅(1/100mm単位)
     * @return エラーの場合は-1以下
     */
    virtual long GetHeight() = 0;

    /**
     * @brief コンテントの種類を取得する
     *
     * @return コンテントの種類<br>
     *         XdwDocuWorks::ContentManager::ContentType参照
     */
    virtual XdwDocuWorks::ContentManager::ContentType WhichIsType() = 0;

    /**
     * @brief ページに対するコンテントの傾きを取得する
     *
     * 現在のDWファイルフォーマットでは、地のコンテント、およびページヘッダでないと意味がない
     *
     * @return コンテントの傾き(degree単位)<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetAngle() = 0;

    /**
     * @brief コンテントに含まれるコンテント数を取得する
     *
     * 現在のDWファイルフォーマットでは、付箋アノテーションでないと意味がない
     *
     * @return コンテントに含まれるコンテント数<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetContentCount() = 0;
    
    /**
     * @brief PDの情報を取得するためのインターフェースを取得する
     *
     * @return XdwDocuWorks::ContentManager::PDInfo参照
     */
    virtual PDInfo* GetPD() = 0;

    /**
     * @brief サムネイル用PDをセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetThumbnailPD() = 0;
    
    /**
     * @brief サムネイル用PDの情報を取得するためのインターフェースを取得する
     *
     * @return XdwDocuWorks::ContentManager::PDInfo参照
     */
    virtual PDInfo* GetThumbnailPD() = 0;
    
    /**
     * @brief 配列指定型PDをセットする
     *
     * @param id 配列指定型PDのID
	 * @param DW拡張の参照型Rasterを指しているPDかどうかのフラグ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetPDNth(long id,bool isRstRef = false) = 0;

    /**
     * @brief 配列指定型PDの情報を取得するためのインターフェースを取得する
     *
     * @return XdwDocuWorks::ContentManager::PDNthInfo参照
     */
    virtual PDNthInfo* GetPDNth() = 0;

    /**
     * @brief キャッシュにバイナリデータをセットする
     *
     * キャッシュはアクセス速度向上のため、DataObjectを使用したバイナリオブジェクトしか、認めない
     *
     * @param offset 参照するバイナリオブジェクトからのオフセット
     * @param size キャッシュするバイナリデータのサイズ
     *
     * @retval XDW_ERRORCODE_SUCCESS キャッシュ成功
     * @retval XDW_ERRORCODE_NOT_CAHCE_USED キャッシュの使用は不可
     * @return その他はXdwErrorCode参照
     */
    virtual XdwErrorCode SetCache(long offset, long size) = 0;

    /**
     * @brief キャッシュ用のバイナリデータを閉じる
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CloseCache() = 0;
    
    /**
     * @brief キャッシュ用のバイナリデータを取得する
     *
     * @return XdwDocuWorks::BinaryInterfaceのインスタンス
     */
    virtual XdwDocuWorks::BinaryInterface* GetCacheData() = 0;

		/**
	 * @brief リンクアノテーション情報を取得する
	 *
	 * @return XdwDocuWorks::ContentManager::LinkAnnotInfo
	 */
	virtual LinkAnnotInfo* GetLinkAnnotInfo() = 0;
};


#endif
