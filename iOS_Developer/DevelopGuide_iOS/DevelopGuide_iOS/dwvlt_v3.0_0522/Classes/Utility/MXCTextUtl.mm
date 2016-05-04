//
//  MXCTextUtl.cpp
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.12 $, $Date: 2007/03/12 10:07:53 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCTextUtl.cpp
 *
 *	テキストに関する関数群の定義
 */
#include "MXCTextUtl.h"
#include "secret.h"
#include "hcntdoc.h"

#ifdef __cplusplus
/**
 * [DWVLT62 add 2006.10.25 by Marumo,K.]
 * OCRにCHARSET未設定（＝DEFALUT_CHARSET）の場合、いくつかのエンコーディングを試す。
 * 試すエンコーディングは以下の通り。
 * (1) 日本語変換する。
 * (2) 失敗したら、簡体中文変換する。
 * (3) 失敗したら、繁体中文変換する。
 * (4) 失敗したら、韓国語変換する。
 * (5) 失敗したら、ラテン変換する。
 * (6) それでも駄目なら、最後に OS デフォルトエンコーディングを試す。
 * ＜注意＞
 *   ラテン変換すると簡体／繁体／韓国語を文字化けした状態でbyte落ちせずに変換してしまうので、
 *   ラテン変換を最後に試す。
 */
static NSString* _convertToNSStringEnhDefaultCharset(NSData* ocrData, int charSet) 
{
	NSStringEncoding encoding = MXCGetNSStringEncoding(charSet);
	NSString *ocrString = [[NSString alloc] initWithData:ocrData encoding:encoding];
	
	// 変換が正しく行われたかどうかチェックし、失敗している場合は他のencodingを試す
	// <注意>変換の成否は sdk によって異なる。
	//      10.2.8.sdk : 文字化け（byte落ちする可能性大）
	//      10.4u.sdk : nilになる
	long ocrStringLength = 0;
	if (ocrString) {
		ocrStringLength = [[ocrString dataUsingEncoding:encoding] length];
	}
	
	if (ocrStringLength == [ocrData length]) {
		return ocrString;	// 成功したらここで終了
	}
	
	// 失敗したら他のCHARSET で変換する
	[ocrString release];
	switch(charSet) {
		case DEFAULT_CHARSET:		// DEFAULT_CHARSETは日本語変換している。
		case SHIFTJIS_CHARSET:		// 日本語変換に失敗したら、繁体中文を試す
			return _convertToNSStringEnhDefaultCharset(ocrData, CHINESEBIG5_CHARSET);
		case CHINESEBIG5_CHARSET:	// 繁体中文変換に失敗したら、簡体中文を試す
			return _convertToNSStringEnhDefaultCharset(ocrData, GB2312_CHARSET);
		case GB2312_CHARSET:		// 簡体中文変換に失敗したら、韓国語を試す
			return _convertToNSStringEnhDefaultCharset(ocrData, HANGEUL_CHARSET);
		case HANGEUL_CHARSET:		// 韓国語変換に失敗したら、ラテンを試す
			return _convertToNSStringEnhDefaultCharset(ocrData, ANSI_CHARSET);
		case ANSI_CHARSET:			// Latin変換にも失敗したらOSデフォルト
		default:
			return [[NSString alloc] initWithData:ocrData 
										 encoding:[NSString defaultCStringEncoding]];
	}	
}

/**
 * MXCGetOcrText : OCRテキストを引数のバッファにコピーする
 * 
 * 引数：
 * MXCImage* raster			IN  コアラッパー 画像オブジェクト
 *							（ラスタ画像でないMXCImageを指定された場合は何もコピーされない）
 * UniChar** buf			IN/OUT OCRテキストバッファ(Unicode)、領域解放は呼び出し側が必ず行うこと
 * int* length				OUT  OCRテキストバッファのサイズ
 *
 * 返り値：
 * MXC_OK           OK
 * MXC_ERROR        エラー
 *
 * [DWVLT62 2006.09.13 by akiyoshi]
 * Unicode化したデータを返すようにする。
 * そのため引数を変更 
 *     char* → UniChar**
 *     int → int*
 * 
 * [DWVLT70 2008.01.31 by futamata]
 * 通常のOCRテキスト取得処理でサイズが0の場合、
 * Unicodeとしてデータを取得し直す。[#ocrtext(w]
 * 
 */
int MXCGetOcrText(MXCImage* raster, UniChar** buf, int* length)
{
	// MXCImageからHBODYCONT取得
	IHeteroBodyCont* cont = (IHeteroBodyCont*)raster->bodyContent();
	if (cont == NULL) return MXC_ERROR;
	
	// OCR情報取得
	MPCSession* session = cont->GetSession();
	ISpecialAttribute* satt = (ISpecialAttribute*)session->GetInterface(IID_ISpecialAttribute);
	if (satt == NULL) return MXC_ERROR;

	// OCRテキスト取得(マルチバイト文字)
	MP_AValue atext = {0, MP_A_UNKNOWN, 0};
	satt->GetSpecialAttribute(cont, "#ocrtext", &atext);	// サイズ取得
	
	// [DWVLT70 2008.02.12 by futamata] >>>
	if (atext.asize <= 0) {
		// Unicodeが入っていると想定してサイズを取得し直す。
		satt->GetSpecialAttribute(cont, "#ocrtext(w", &atext);	// サイズ取得
		
		// ここに来る前にsize>0を確認しているはずなので、ここでsize<=0はあり得ない。
		if (atext.asize <= 0) return MXC_ERROR;
		
		// データを取得する。
		char* ocrBuffer = (char*)malloc(atext.asize);
		// DWVLT70 MallocCheck :malloc戻り値チェック漏れ対応 <<--
		if (ocrBuffer == NULL) {
			NSLog(@"%s[%d] malloc failed", __FILE__, __LINE__);
			return MXC_ERROR;
		}
		// -->> WVLT70 MallocCheck 
		atext.adata = ocrBuffer;
		satt->GetSpecialAttribute(cont, "#ocrtext(w", &atext);	// 実際にデータを取得
		
		// リトルエンディアンとしてのBOMを付ける
		char tmpChar[atext.asize+2];
		tmpChar[0] = 0xFF;
		tmpChar[1] = 0XFE;
		memcpy(tmpChar+2,ocrBuffer,atext.asize);
		
		// UTF-16としてNSStringに変換。
		NSData *ocrData = [NSData dataWithBytes:tmpChar length:(unsigned)atext.asize];
		NSString *ocrString = [[NSString alloc] initWithData:ocrData encoding:NSUnicodeStringEncoding];
		// いずれにしても、変換結果が nil になったら空文字列で処理する。
		if (ocrString == nil) {
			ocrString = [[NSString stringWithString:@""] retain];
		}
		
		// UniCharを取り出す。
		unsigned int uniCharLength = [ocrString length];
		UniChar* ocrUniChar = new UniChar[uniCharLength];
		[ocrString getCharacters:ocrUniChar];
		
		// 値をセット
		*buf = ocrUniChar;
		*length = uniCharLength;
		
		[ocrString release];
		free(ocrBuffer);
		
		return MXC_OK;
	}
	// <<< [DWVLT70 2008.02.12 by futamata]
	
	// [DWVLT62 2006.09.13 by akiyoshi] >>>
	char* ocrBuffer = (char*)malloc(atext.asize);
	// DWVLT70 MallocCheck :malloc戻り値チェック漏れ対応 <<--
	if (ocrBuffer == NULL) {
		NSLog(@"%s[%d] malloc failed", __FILE__, __LINE__);
		return MXC_ERROR;
	}
	// -->> WVLT70 MallocCheck 
	atext.adata = ocrBuffer;
	satt->GetSpecialAttribute(cont, "#ocrtext", &atext);	// 実際にデータを取得
	
	// CHARSETを取得
	int charSet = DEFAULT_CHARSET;
	MP_AValue acharset = {sizeof(charSet), MP_A_INT, &charSet};
	satt->GetSpecialAttribute(cont, "#ocrcharset", &acharset);

#ifdef _OCR_NO_CHARSET_
	// CHARSET未設定の場合を試すために、故意に charSet を DEFALUT_CHARSET にする
	charSet = DEFAULT_CHARSET;
#endif
	// CHARSETに基づいたエンコーディングでUnicode文字列に変換
	NSData *ocrData = [NSData dataWithBytes:ocrBuffer length:(unsigned)atext.asize];
	NSString *ocrString = nil;
	if (charSet == DEFAULT_CHARSET) {
		// CHARSET未設定の場合は、何種類かのエンコーディングを試す
		ocrString = _convertToNSStringEnhDefaultCharset(ocrData, charSet);
	}
	else {
		// CHARSETが設定されている場合は、CHARESTが示すエンコーディングを使う
		NSStringEncoding encoding = MXCGetNSStringEncoding(charSet);
		ocrString = [[NSString alloc] initWithData:ocrData encoding:encoding];
	}
	
	// いずれにしても、変換結果が nil になったら空文字列で処理する。
	if (ocrString == nil) {
		ocrString = [[NSString stringWithString:@""] retain];
	}
		
	// UniChar確保
	unsigned int uniCharLength = [ocrString length];
	UniChar* ocrUniChar = new UniChar[uniCharLength];
	[ocrString getCharacters:ocrUniChar];
	
	*buf = ocrUniChar;
	*length = uniCharLength;
	
	[ocrString release];
	free(ocrBuffer);
	// <<< [DWVLT62 2006.09.13 by akiyoshi]
	
	return MXC_OK;
}

/**
 * MXCGetOcrRectSize : OCR領域情報のサイズを返す
 * OCRテキストの選択領域情報の配列サイズを返す
 * 
 * 引数：
 * MXCImage* raster   IN	コアラッパー 画像オブジェクト
 *							（ラスタ画像でないMXCImageを指定された場合は0が返る）
 *
 * 返り値：
 * OCR領域情報の配列のサイズ
 * OCR領域情報が無い場合は0を返す。
 */
int MXCGetOcrRectSize(MXCImage* raster)
{
	// MXCImageからHBODYCONT取得
	IHeteroBodyCont* cont = (IHeteroBodyCont*)raster->bodyContent();
	if (cont == NULL) return 0;
	
	// OCR情報取得
	MPCSession* session = cont->GetSession();
	ISpecialAttribute* satt = (ISpecialAttribute*)session->GetInterface(IID_ISpecialAttribute);
	if (satt == NULL) return 0;

	// OCR領域情報取得
	MP_AValue arect = {0, MP_A_UNKNOWN, 0};
	satt->GetSpecialAttribute(cont, "#ocrrect", &arect);	// サイズ取得
	if (arect.asize <= 0) return 0;
	
	int rectNum = arect.asize / 4; // 4 : sizeof(int)
	return rectNum;
}

/**
 * MXCGetOcrRect : OCR領域情報を引数のバッファにコピーする
 * OCRテキストの選択領域情報を引数の配列にコピーする
 * 
 * 引数：
 * MXCImage* raster			IN  コアラッパー 画像オブジェクト
 *							（ラスタ画像でないMXCImageを指定された場合は何もコピーされない）
 * int* rect				OUT OCRテキストをコピーするバッファ
 * int size					IN  バッファのサイズ
 *
 * 返り値：
 * MXC_OK           OK
 * MXC_ERROR        エラー
 */
int MXCGetOcrRect(MXCImage* raster, int* rect, int size)
{
	// MXCImageからHBODYCONT取得
	IHeteroBodyCont* cont = (IHeteroBodyCont*)raster->bodyContent();
	if (cont == NULL) return MXC_ERROR;
	
	// OCR情報取得
	MPCSession* session = cont->GetSession();
	ISpecialAttribute* satt = (ISpecialAttribute*)session->GetInterface(IID_ISpecialAttribute);
	if (satt == NULL) return MXC_ERROR;

	// OCR領域情報取得
	MP_AValue arect = {0, MP_A_UNKNOWN, 0};
	satt->GetSpecialAttribute(cont, "#ocrrect", &arect);	// サイズ取得
	if (arect.asize < size) return MXC_ERROR;
	
	arect.adata = rect;
	satt->GetSpecialAttribute(cont, "#ocrrect", &arect);	// 実際にデータを取得
	
	return MXC_OK;
}

#endif // __cplusplus

/**
 * DWVLT62 del 2006/10/17
 * MXCConvertExChar : 機種依存文字を変換する
 * Shift-JISの機種依存文字を"◆"に変換する。
 *
 * 機種依存文字の判定は以下の通り
 *  (Classic版同等処理)
 *		Shift-JISコード 0x8740〜0x879c のコードを代替文字に変換。
 *  (OSX版独自処理)
 *		・Shift-JISコード 0x84BF〜0x889E
 *		・Shift-JISコード 0xED40〜0xEDFC
 *		・Shift-JISコードの１バイト目が 0xFA/0xFB/0xFC
 *		以上のコードを"◆"に変換。(Classic版処理の範囲のコードは上記Classic版処理)
 * 
 * 引数：
 * char* buf				IN/OUT  変換対象テキスト
 * int length				IN		変換対象テキストの長さ
void MXCConvertExChar(char* buf, int length)
*/

/**
 * MXCConvertReturn : 改行コードを変換する
 * Windowsの改行コード(¥r:0x0d, ¥n:0x0a)をMacOSXの改行コードに変換する。
 * 
 * 引数：
 * UniChar* buf				IN/OUT  変換対象テキスト
 * int* length				IN/OUT  変換対象テキストの長さ
 *
 * [DWVLT62 2006.09.21 by Marumo,K.]
 * OSXテキストエディタの改行コードの初期値がLFであることが判明したので、LFを残すように変更。
 * また、文字列をUniCharで扱うように統一されたことを受けて、引数の型を変更
 */
void MXCConvertReturn(UniChar *buf, int* length)
{
	UniChar DEL_CHAR = 0x0d;		// キャリッジリターン(¥r)を削除

	long l;

	UniChar *pUniChar = buf;
	long lengthTemp = *length;
	for (l = 0; l < lengthTemp; ) {
		if(*pUniChar == DEL_CHAR) {
			memmove(pUniChar, pUniChar+1, (lengthTemp-l)*sizeof(UniChar));
			lengthTemp--;
		}
		else {
			pUniChar++;
			l++;
		}
	}
	
	// 改行コードを変換していたら、末尾にNULL文字を入れておく。
	if (*length > lengthTemp) {
		buf[lengthTemp] = 0x0000;
	}
	
	*length = lengthTemp;
	return;
}

/**
* DWVLT62 add 2006.09.13 by Marumo,K.
 * フォント情報に含まれる Windows CHARSET を、NSStringEncoding に変換する。
 *
 * 引数：
 * unsigned char charset				IN  Windows CHARSET
 */
NSStringEncoding MXCGetNSStringEncoding(unsigned char charset) {
	// テキストエンコーディング（Symbolフォントの場合はシンボルエンコーディング、それ以外はUTF8）
	switch(charset) {
		case GB2312_CHARSET:		// 簡体中文(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseSimplif);
		case CHINESEBIG5_CHARSET:	// 繁体中文(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseTrad);
		case HANGEUL_CHARSET:		// 韓国語(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSKorean);
		case ANSI_CHARSET:			// Latin
			return NSWindowsCP1252StringEncoding;
		case EASTEUROPE_CHARSET:	// 東ヨーロッパ(since v6.1) _FONT_DEBUG_61_
			return NSWindowsCP1250StringEncoding;
		case RUSSIAN_CHARSET:		// ロシア語(since v6.1) _FONT_DEBUG_61_
			return NSWindowsCP1251StringEncoding;
		case GREEK_CHARSET:			// ギリシャ語(since v6.1) _FONT_DEBUG_61_
			return NSWindowsCP1253StringEncoding;
		case TURKISH_CHARSET:		// トルコ語(since v6.1) _FONT_DEBUG_61_
			return NSWindowsCP1254StringEncoding;
		case HEBREW_CHARSET:		// ヘブライ語(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsHebrew);
		case ARABIC_CHARSET:		// アラビア語(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsArabic);
		case BALTIC_CHARSET:		// バルト海(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsBalticRim);
		case VIETNAMESE_CHARSET:	// ベトナム語(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingWindowsVietnamese);
		case THAI_CHARSET:			// タイ語(since v6.1) _FONT_DEBUG_61_
			return CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSThai);
		case DEFAULT_CHARSET:
		case SHIFTJIS_CHARSET:		// 日本語
			return NSShiftJISStringEncoding;
		case SYMBOL_CHARSET:		// シンボル
			// BasicLatinで変換した場合の0x20〜0x7Eが表示可能な絵文字となる
			return NSWindowsCP1252StringEncoding;
		default:
			return NSUnicodeStringEncoding;
	}
}

/**
 * DWVLT62 add 2006.09.13 by Marumo,K.
 * 引数で指定された文字列を１文字ずつチェックして、必要であれば文字コードを変換する。
 * 現在サポートしている変換は以下の通り。
 * (1) SHIFTJIS_CHARSETの場合のみ、バックスラッシュ(U+005C)を円マーク(U+00A5)に変換する。
 *
 * 引数：
 * UniChar* uniCharPtr			IN/OUT  変換対象文字列
 * unsigned int* charLength     IN/OUT  文字列長。処理後に文字列長が変わる場合に対応
 * unsigned char charset        IN      CHARSET
 */
void MXCConvertChar(UniChar* uniCharPtr, unsigned int* charLength, unsigned char charset) {
	// 文字化け調整
	unsigned int length = *charLength;
	unsigned int p;
	for (p = 0; p < length; p++) {
		switch (uniCharPtr[p]) {
			case 0x5c:		// '/'(バックスラッシュ)
				if (charset == SHIFTJIS_CHARSET) {
					uniCharPtr[p] = 0x00A5;			// 日本語の場合は¥(円マーク)に変換
				}
				break;
		}
	}	
}

/**
 * DWVLT62 BTS#44 Marumo,K. 2007.03.08
 * システムデフォルトのエンコーディングをWindowsの対応するエンコーディングとして取得する。
 * 変換は以下の２種類（正式サポート分）。それ以外はシステムデフォルトをそのまま返す。
 *    MacJapanese -> NSShiftJISStringEncoding
 *    MacRoman    -> NSWindowsCP1252StringEncoding
 */
NSStringEncoding MXCGetDefaultEncodingAsWindows()
{
	NSStringEncoding defaultEncoding = [NSString defaultCStringEncoding];
	CFStringEncoding cfEncoding = CFStringConvertNSStringEncodingToEncoding(defaultEncoding);

	switch (cfEncoding) {
		case kCFStringEncodingMacJapanese:		// 日本語
			return NSShiftJISStringEncoding;
		case kCFStringEncodingMacRoman:			// 英語／フランス語
			return NSWindowsCP1252StringEncoding;
		default:
			return defaultEncoding;
	}
}
	
/**
 * DWVLT62 BTS#44 Marumo,K.
 * デフォルトエンコーディングで文字列を生成する。
 * 
 * [引数]
 *   cString - nullターミネートのchar*。
 * [戻り値]
 *   生成した文字列(autorelease)を返す。
 *   文字列を生成できない場合またはcStringがNULLの場合は、空文字列を返す。
 */
NSString* MXCGetStringWithCString(char* cString)
{
	if (cString == NULL) {
		return [NSString stringWithString:@""];
	}
	
	NSString* retStr = [
		[NSString alloc] initWithData:[NSData dataWithBytes:cString length:strlen(cString)]
							 encoding:MXCGetDefaultEncodingAsWindows()];

	// デフォルトエンコーディングと互換するエンコーディングがcString生成時のエンコーディングと合っていなくて
	// 文字列に変換できない場合は、デフォルトエンコーディングで変換する。
	// (例えば、日本語環境で作った文書をフランス語環境で見た場合など）
	// 何もでないよりは文字化けした状態でも出た方がましなことと、以前のバージョンとの互換のため。
	if (retStr == nil) {
		retStr = [[NSString alloc] initWithCString:cString
										  encoding:[NSString defaultCStringEncoding]];
	}
	
	// それでも駄目なら空文字列にする。
	if (retStr == nil) {
		retStr = [[NSString alloc] initWithString:@""];
	}
	
	return [retStr autorelease];
}

/**[DWVLT70 2008.02.08 by ushijima]
 * DWVLT70 ushijima
 * NSUnicodeStringEncodingでエンコードした文字列を生成する。
 * 
 * [引数]
 *   stringW - UTF16のchar*。
 * [戻り値]
 *   生成した文字列(autorelease)を返す。
 *   文字列を生成できない場合またはstringWがNULLの場合は、空文字列を返す。
 */
NSString* MXCGetStringWithUTF16(char* stringW,int numChar)
{
	//入力値がNULLの場合は空文字を返す
	if (stringW == NULL || numChar <= 0) {
		return [NSString stringWithString:@""];
	}

	// ビックエンディアンに変更する。
	char tmpChar[numChar+2];
	tmpChar[0] = 0xFF;
	tmpChar[1] = 0XFE;
	memcpy(tmpChar+2, stringW, numChar);

	// unicodeエンコード。
	NSString* retStrW = [[NSString alloc] initWithData:[NSData dataWithBytes:tmpChar
							 length:numChar]
							 encoding:NSUnicodeStringEncoding];

	// エンコードできなかった場合は空文字列にする。
	if (retStrW == nil) {
		retStrW = [[NSString alloc] initWithString:@""];
	}
	
	return [retStrW autorelease];
}