/*
 *  LinkAnnotInfo.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-31.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LINK_ANNOT_INFO_H_
#define LINK_ANNOT_INFO_H_

//#include "XdwDocuWorks.h"
#include "mpc_api.h"
#include "linkcmm.h"
#include "linkglob.h"

/**
 * @brief Class of link annotation information.
 */
class LinkAnnotInfo
{
public:
	
    /*! Attribute of link page */
    enum LinkPageAttribute
    {
        /*! No data to link */
        kLinkPageNoData     = -1,
        /*! 「この文書」 */
        kLinkThisFile       = LINK_THIS_FILE,
        /*! 「このバインダの通しページ」指定 */
        kLinkBinderAllPage  = LINK_BINDER_ALLPAGE,
        /*! 「このバインダの他の文書のページ」指定 */
        kLinkBinderOtherDoc = LINK_BINDER_OTHER_DOC
    };
	
    /*! Information about where to link */
    enum LinkTo
    {
        /*! No data to link */
        kLinkToNoData       = -1,
        /*! Link to self */
        kLinkToMe           = LINK_TO_ME,
        /*! Link to a XDW file */
        kLinkToXdw          = LINK_TO_XDW,
        /*! Link to a URL address */
        kLinkToUrl          = LINK_TO_URL,
        /*! Link to other file */
        kLinkToOtherFile    = LINK_TO_OTHERFILE,
        /*! Link to a mail address */
        kLinkToMailAddress  = LINK_TO_MAILADDRESS
    };
	
    /*! types of how to link in the DW file */
    enum LinkToDwType
    {
        /*! No type to link */
        kLinkToDwTypeNoData         = -1,
        /*! Type of link to page */
        kLinkToDwTypePage           = LINK_TO_DWTYPE_PAGE,
        /*! Type of link to a link annotation*/
        kLinkToDwTypeLinkAnnotation = LINK_TO_DWTYPE_LINKANN
    };

	enum 
	{
		kMaxLinkStr    = 2000,
		kMaxLinkStrBuf = 2048
	};
	
	
private:
	
    /*! Position of this link annotation */
    XdwPoint        m_LinkAnnotPos;
    /*! Object for link annotation */
    MPCObject*      m_MPCObject;
    /*! Dim of this link */
    XdwPoint        m_Dim;
    /*! Value of "%LINKATT_XDWPAGENUM" attribute */
    long m_PageNum;
    /*! Value of "%LINKATT_PAGECHECK" attribute */
    LinkPageAttribute m_PageCheck;
    /*! Value of "%LINKATT_LINKTO" attribute */
	LinkTo m_LinkTo;
    /*! Value of "%LINKATT_DW_JUMPTYPE" attribute */
    LinkToDwType m_JumpType;
    /*! Value of "%LINKATT_TITLESTR" attribute */
    char m_LinkTitleString[kMaxLinkStrBuf];
    /*! Value of "%LINKATT_URLSTR" attribute */
    char m_UrlString[kMaxLinkStrBuf];
    /*! Value of "%LINKATT_MAILADDRESS" attribute */
    char m_MailAddressString[kMaxLinkStrBuf];
    /*! Value of "%LINKATT_SHEAFNAME" attribute */
    char m_SheafnameString[kMaxLinkStrBuf];
    /*! Value of "%LINKATT_LINKTITLE" attribute */
    char m_LinkJumpTitleString[kMaxLinkStrBuf];
	/*! Value of "%LINKATT_LINKOTHERFILEPATH" attribute */
	char m_OtherFilePathString[kMaxLinkStrBuf];
	
	long m_LinkToPageNum;
	
	// PostitAnnotation color
	long m_rgbColor;
	
	wchar_t* m_AnnotText;
	
	bool m_isLinkAnnot;
	
	
    /**
	 * @brief Set the object of this link annotation
	 *
	 * @param mpcObject Object of this link annotation
	 *
	 * @retval HRESULT
	 */
    virtual HRESULT SetContent(MPCObject* const mpcObject);
	
	void SetXdwAnnotText(MPCObject* const mpcObject);
	
public:
    /**
	 * @brief Get the rectangle of this link annotation
	 *
	 * @retval Rectangle of this link annotation
	 */
    virtual XdwRectangle GetRectangle() const;
	
	// add by zhangshuai 10/11/10
	/**
	 * @brief Get the text of this position annotation
	 *
	 * @retval text of this position annotation
	 */
	const wchar_t* GetAnnotText();
	
	// add by zhangshuai 10/11/10
	/**
	 * @brief if this annotation is a link annotation
	 *
	 * @retval true for link annotation
	 * @retval false for position annotation
	 */
	bool IsLinkAnnotation();
	
	
private:
    /**
	 * @brief Set the width and height of this link annotation
	 *
	 * @retval HRESULT
	 */
    virtual HRESULT CalculateContentDim();
	
    /**
	 * @brief Set the position of this link annotation
	 *
	 * @param pos Position of this link annotation
	 *
	 * @retval -
	 */
    virtual void SetContentPos(MP_Pos pos);
	
	
	// add by zhangshuai 10/11/10
	bool IsLinkAnnot(MPCObject* const mpcContentObject);
	
	void SetContentDim(MP_Dim dim);
	
public:
    /**
	 * @brief Constructor of this class
	 */
    LinkAnnotInfo();
	
    /**
	 * @brief Destructor of this class
	 */
    ~LinkAnnotInfo();
	//added now
	const char* GetOtherFilePathString() const;
    /**
	 * @brief Get the value of "%LINKATT_XDWPAGENUM" about this link annotation
	 *
	 * @retval Value of "%LINKATT_XDWPAGENUM" about this link annotation
	 */
    long GetXdwPageNum() const;
	
	/**
	 * @brief Get the value of "%LINKATT_LINKTOPAGENUM" about this link annotation
	 *
	 * @retval Value of "%LINKATT_LINKTOPAGENUM" about this link annotation
	 */
	long GetLinkToPageNum() const;
	
    /**
	 * @brief Get the value of "%LINKATT_PAGECHECK" about this link annotation
	 *
	 * @retval Value of "%LINKATT_PAGECHECK" about this link annotation
	 */
    LinkPageAttribute GetPageCheck() const;
	
    /**
	 * @brief Get the value of "%LINKATT_LINKTO" about this link annotation
	 *
	 * @retval Value of "%LINKATT_LINKTO" about this link annotation
	 */
	LinkTo GetLinkTo() const;
	
    /**
	 * @brief Get the value of "%LINKATT_DW_JUMPTYPE" about this link annotation
	 *
	 * @retval Value of "%LINKATT_DW_JUMPTYPE" about this link annotation
	 */
    LinkToDwType GetDwJumpType() const;
	
    /**
	 * @brief Get the value of "%LINKATT_TITLESTR" about this link annotation
	 *
	 * @retval Value of "%LINKATT_TITLESTR" about this link annotation
	 */
    const char* GetLinkTitleString() const;
	
    /**
	 * @brief Get the value of "%LINKATT_URLSTR" about this link annotation
	 *
	 * @retval Value of "%LINKATT_URLSTR" about this link annotation
	 */
    const char* GetUrlString() const;
	
    /**
	 * @brief Get the value of "%LINKATT_MAILADDRESS" about this link annotation
	 *
	 * @retval Value of "%LINKATT_MAILADDRESS" about this link annotation
	 */
    const char* GetMailadressString() const;
	
    /**
	 * @brief Get the value of "%LINKATT_SHEAFNAME" about this link annotation
	 *
	 * @retval Value of "%LINKATT_SHEAFNAME" about this link annotation
	 */
    const char* GetSheafnameString() const;
	
    /**
	 * @brief Get the value of "%LINKATT_LINKTITLE" about this link annotation
	 *
	 * @retval Value of "%LINKATT_LINKTITLE" about this link annotation
	 */
    const char* GetLinkJumpTitleString() const;
	
	/**
	 * @brief Get the value of "%LINKATT_ANNOTATIONCOLOR" about this link annotation
	 *
	 * @retval Value of "%LINKATT_ANNOTATIONCOLOR" about this link annotation
	 */
	const long GetAnnotationColor() const;
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	int	GetLinkTitleCharSet()
	{
		int nPF = 0;
		
		MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nPF };
		m_MPCObject->GetAttribute("%LINKATT_TITLE_CHARSET", &avalue);
		
		return nPF;
	};
	
	// 20110407 M.Chikyu end
	
private:
	//added now
	void SetOtherFilePathString();
    /**
	 * @brief Set the value of "%LINKATT_XDWPAGENUM" about this link annotation
	 *
	 * @retval -
	 */
    void SetXdwPageNum(long pageIndex);
	
	/**
	 * @brief Set the value of "%LINKATT_LINKTOPAGENUM" about this link annotation
	 *
	 * @retval -
	 */
	void SetLinkToPageNum();
	
    /**
	 * @brief Set the value of "%LINKATT_PAGECHECK" about this link annotation
	 *
	 * @retval -
	 */
    void SetPageCheck();
	
    /**
	 * @brief Set the value of "%LINKATT_LINKTO" about this link annotation
	 *
	 * @retval -
	 */
    void SetLinkTo();
	
    /**
	 * @brief Set the value of "%LINKATT_DW_JUMPTYPE" about this link annotation
	 *
	 * @retval -
	 */
    void SetDwJumpType();
	
    /**
	 * @brief Set the value of "%LINKATT_TITLESTR" about this link annotation
	 *
	 * @retval -
	 */
    void SetLinkTitleString();
	
    /**
	 * @brief Set the value of "%LINKATT_URLSTR" about this link annotation
	 *
	 * @retval -
	 */
    void SetUrlString();
	
    /**
	 * @brief Set the value of "%LINKATT_MAILADDRESS" about this link annotation
	 *
	 * @retval -
	 */
    void SetMailadressString();
	
    /**
	 * @brief Set the value of "%LINKATT_SHEAFNAME" about this link annotation
	 *
	 * @retval -
	 */
    void SetSheafnameString();
	
    /**
	 * @brief Set the value of "%LINKATT_LINKTITLE" about this link annotation
	 *
	 * @retval -
	 */
    void SetLinkJumpTitleString();
	
    /**
	 * @brief Get the values of this link annotation
	 *
	 * @retval -
	 */
    void OrganiseAttribute();
	
	/**
	 * @brief Set the value of "%LINKATT_ANNOTATIONCOLOR" about this link annotation
	 *
	 * @retval -
	 */
	void SetAnnotationColor(long color);
	
    friend class XdwAttributeParser;
	
}; // class LinkAnnotInfo

typedef std::vector< LinkAnnotInfo * > VecLinkAnnotInfo;

/**
 * @brief Class of link annotation list
 */
class LinkAnnotInfoList
{
private:
	
    /*! List of link annotations */
    VecLinkAnnotInfo m_vecLinkAnnotInfo;
	
public:
	
    /**
	 * @brief Constructor of this class
	 */
    LinkAnnotInfoList();
	
    /**
	 * @brief Destructor of this class
	 */
    virtual ~LinkAnnotInfoList();
	
public:
    /**
	 * @brief Add a link annotation into this list
	 *
	 * @param content Pointer of a LinkAnnotInfo
	 *
	 * @retval -
	 */
    void Add(LinkAnnotInfo* const content);
	
    /**
	 * @brief Clear the list and remove all the link annotations
	 *
	 * @retval -
	 */
    void RemoveAll();
	
    /**
	 * @brief Get a link annotation in the list
	 *
	 * @param index Index of this list
	 *
	 * @retval Pointer of a LinkAnnotInfo
	 */
    LinkAnnotInfo* GetLinkAnnotInfo(int index) const;
	
    /**
	 * @brief Get the size of this list
	 *
	 * @retval Size of this list
	 */
    int Size() const;
};

#endif	// LINK_ANNOT_INFO_H_
