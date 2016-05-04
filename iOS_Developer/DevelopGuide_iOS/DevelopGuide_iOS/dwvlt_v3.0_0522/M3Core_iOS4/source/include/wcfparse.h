// $Archive: /DocuWorks/60/Source/include/wcfparse.h $
//
// Copyright (c) 2002-2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:30 $
// $Revision: 1.4 $

// File: findparse.h
// Author: Michiko Miyazaki

#ifndef _WCFPARSE_H_
#define _WCFPARSE_H_

/***********************************************************************
WideChar検索文字列をOR検索出来るように分解するクラスCDwFindParse

この分解機能は、Deskでの検索、mpctsの検索で共通利用されている。
  
[概要]
コンストラクタで指定された文字列に対してパースされた文字列リストの作成を行う。
デストラクタで文字列リストを削除する。

呼び出し側でGetItemCountを呼ぶと文字列の要素数が判定できるので
パースされた部分文字列を取り出すときはGetElementで指定要素番号の文字列を取り出す。
exe.
int main(int argc, char* argv[])
{
	const WCHAR *text = L"\"United　States\" \"Afgan\"";
	CDwFindParse parse(text);
	for (int i = 0; i < parse.GetItemCount(); i++)
	{
		char *p = parse.GetElement(i);
	}
	return 0;
}

******************************
パースの制御文字について
v5viewer機能仕様書より抜粋
******************************
検索文字列では、ダブルクォート(")と円記号(\)を制御文字とみなされる。
これら制御文字はともに半角である。全角の場合は制御文字とはみなされない。
スペースを含む文字列を検索する場合は、ダブルクォート(")でくくること。
ダブルクォートを含む文字列を検索する場合は、ダブルクォートの直前に円記号(\)を置くこと。
円記号(\)を含む文字列を検索する場合は、円記号の直前に円記号(\)を置くこと。
"\"は直後の文字を制御文字として扱わない(Escapeする)という意味で用いられる。

例：	("_"は全角または半角スペース)
(入力された検索文字列）→(分解後の文字列)
「"United_States" "Afgan"」→「United_States」「Afgan」
「"A" "B_C" "D"」→「A」「B_C」「D」
「A"B_C」→「A」「B_C」
(")が出てきたらそこで語の区切りとする。
2つ目の(")がない場合は末尾に"があるものとして処理する。
「A\"B」→「A"B」
(")を検索対象に含めたい時の指定
「A\\B」→「A\B」
(\)を検索対象に含めたい時の指定
「A\_B」→「A_B」
(\)を使うことでもスペースを検索対象に含めることができる
「A\BC」→「ABC」
(\)の直後の文字はそのまま検索文字列になる
「A""B_C"_D」→「A」「B」「C」「_D」
AとBの間の""は空白文字列とみなされ、検索文字列から除外される
「A"B_C"D"EF"G""HI」→「A」「B_C」「D」「EF」「G」「HI」
GとHIの間の""は空白文字列とみなされ、検索文字列から除外される
***************************************************************************************/

class CDwFindParse
{
public:
	//! コンストラクタ 内部で検索文字列の分割も行う
	CDwFindParse(const MP_Text *pszText);
	//! デストラクタ
	virtual ~CDwFindParse();
	//! 検索語の個数を取得
	int GetItemCount() const;
	//! 検索語を1個取得
	const MP_Text* GetElement(int i) const;
	//! 検索語の配列を取得
	const MP_Text*const* GetStringList() const;

private:
	MP_Text** m_stringList;	//!< 検索語のリスト
	int  m_nItemCount;		//!< 検索語の個数

	void ParseString(const MP_Text *pszText);
	int ParseStringSub(const MP_Text *pszText, MP_Text **stringList) const;
	bool GetToken(const MP_Text *pszText, int length, int& index, bool& checkSpace, MP_Text** stringList, int& nItem) const;
	int GetToken(const MP_Text *pszText, int length, int& index, bool& checkSpace, MP_Text* buffer) const;
	bool AllocStringList();
	void FreeStringList();
};

#endif //_WCFPARSE_H_

// $History: wcfparse.h $
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/11/11   Time: 21:21
// Updated in $/DocuWorks/60/Source/include
// AR11726対応
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/05/20   Time: 10:19
// Created in $/DocuWorks/60/Source/include
