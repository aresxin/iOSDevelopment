/*
 *  DocAttributeParser.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "AttributeParser.h"

AttributeParser::AttributeParser()
{
}

AttributeParser::~AttributeParser()
{
	
}

PageInfo* AttributeParser::GetPageInfo(int pageIndex)
{
	return XdwNull;
}

XdwErrorCode AttributeParser::SetFileInfo(FileInfo* fileInfo)
{
	return XDW_ERRORCODE_SUCCESS;
}

XdwErrorCode AttributeParser::SetLinkAnnotInfoList(LinkAnnotInfoList* annotInfoList)
{
	return XDW_ERRORCODE_SUCCESS;
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode AttributeParser::SetFile(const char* filePath)
XdwErrorCode AttributeParser::SetFile(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	return XDW_ERRORCODE_SUCCESS;
}

void AttributeParser::Destroy(void)
{
	return ;
}

HANDLE AttributeParser::GetDocSession()
{
	return XdwNull;
}

bool AttributeParser::SetAnnotationDisplay(int mode)
{
	return false;
}

// liuqw 20110801 start
// ページ編集機能の追加

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode AttributeParser::SetFileForUpdate(const char* filePath)
XdwErrorCode AttributeParser::SetFileForUpdate(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	return XDW_ERRORCODE_SUCCESS;
}
// liuqw 20110801 end

// xuxinjun 2012.03.23 start
// パーミッションの対応.

MP_Permission AttributeParser::GetPermission()
{
	return 0;
}

// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
HRESULT AttributeParser::SearchText(int& nPageNum, 
									int  startPageIndex,
									int  endPageIndex,
									unsigned short* text, 
									bool next, 
									bool display,
									MP_TextInfo*  textInfoInput,
									MP_TextInfo** textInfoResult, 
									MP_AnnoInfo* annoInfo)
{
	return MP_S_NO_RES;
}
// xujj 2012.03.22 end

// tongtx 2012.03.12 start
// 選択機能の追加
HRESULT AttributeParser::GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType, LogicAnnoInfoList* list)
{
	return NULL;
}

bool AttributeParser::SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo)
{
	return false;
}

bool AttributeParser::GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo)
{
	return false;
}
// tongtx 2012.03.12 end