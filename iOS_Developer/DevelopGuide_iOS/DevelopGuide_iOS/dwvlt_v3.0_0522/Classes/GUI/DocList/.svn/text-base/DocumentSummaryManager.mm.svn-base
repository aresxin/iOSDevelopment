//
//  DocumentSummaryManager.m
//  DWViewer
//
//  Created by liuqw on 11-6-19.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DocumentSummaryManager.h"
#include "MXCUnicodeUtl.h"

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
#include "mppmodel.h"
// zhaijie 2012.03.30 end

// 属性名の数を格納する属性名
#define SUMMARY_ATT_COUNT	"%doc_att_Count"

// 属性名prefix
#define SUMMARY_ATT_NAME	"%doc_att_N_"
#define SUMMARY_ATT_TYPE	"%doc_att_T_"
#define SUMMARY_ATT_VALUE	"%doc_att_V_"


@implementation DocumentSummaryManager
@synthesize fileTitle;
@synthesize fileSubtitle;
@synthesize fileAuthor;
@synthesize fileKeyword;
@synthesize fileComment;

- (BOOL) getDocumentSummaryDataWithFilePath:(NSString *)filePath
{
    BOOL result = YES;
    if (filePath != nil) {
        XdwAttributeParser *attributeParse = new XdwAttributeParser();
        if (attributeParse != XdwNull) {
            const char *cFilePath = [filePath UTF8String];
            
			// xuxinjun 2012.03.23 start
			// 保護文書の対応
			/*
			 XdwErrorCode retCode = attributeParse->SetFile(cFilePath);
			 */

			XdwErrorCode retCode = attributeParse->SetFile(cFilePath, NULL);
			// xuxinjun 2012.03.23 end

            if (retCode != XDW_ERRORCODE_SUCCESS) {
				delete attributeParse;
                return NO;
            }
        }  
        
        MPCProfile* profile = attributeParse->profile();
        
        result = [self loadDocumentSummaryDataWithProfile:profile];
		
        delete attributeParse;
        attributeParse = XdwNull;
    }
    
    return result;
}

// lixin 20110623 DW_iPhoneEnhance_12 start
// AR.17855 の対応 
/*
- (BOOL) loadDocumentSummaryDataWithProfile:(MPCObject*)profile
{
    _title[0] = 0;			// タイトル
    _subject[0] = 0;		// サブタイトル
    _author[0] = 0;			// 作成者
    _keywords[0] = 0;		// キーワード
    _comments[0] = 0;		// コメント
    
	// [DWVLT70 2008.02.06 by ushijima] >>>
    _unititle[0] = 0;			// タイトル
    _unisubject[0] = 0;			// サブタイトル
    _uniauthor[0] = 0;			// 作成者
    _unikeywords[0] = 0;		// キーワード
    _unicomments[0] = 0;		// コメント
	_unititlen = 0;				// タイトル文字長
	_unisublen = 0;				// サブタイトル文字長
	_uniautlen = 0;				// 作成者文字長
	_unikeylen = 0;				// キーワード文字長
	_unicomlen = 0;				// コメント文字長
    
    // ----------------------------------------------------------
	// 文書概要属性は拡張可能な様式で格納されている。
	// %doc_att_Countに属性の数が格納されており、その数だけ
	// %doc_att_N_n (属性名 : octs)
	// %doc_att_T_n (タイプ : int)
	// %doc_att_V_n (属性値 : octs)
	// (※ nは整数)
	// という属性名で%doc_att_Countの数だけ属性が格納されている。
	// (%doc_att_N_1, %doc_att_N_2, %doc_att_N_3...等)
	//
	// %doc_att_N_nの値でその属性が何を指すのかを判断し、
	// %doc_att_V_nの値を取得し設定する。
	//
	// 文書概要情報に使用する属性(%doc_att_N_nの値)は以下の通り。
	// %doc_att_title		タイトル
	// %doc_att_subject		表題
	// %doc_att_author		作成者
	// %doc_att_keywords	キーワード
	// %doc_att_comments	コメント
	// ----------------------------------------------------------
    
    if (profile == nil) {
        return NO;
    }
	
	// 属性数
	int attCount = 0;
	MP_AValue attCountValue = { 0, MP_A_INT, NULL }; 
	if (profile->GetAttribute(SUMMARY_ATT_COUNT, &attCountValue) == MP_NOERROR) {
		attCountValue.adata = &attCount;
		profile->GetAttribute(SUMMARY_ATT_COUNT, &attCountValue);
	}
	
	char attributeNName[16];		// %doc_att_N_n
	char attributeVName[16];		// %doc_att_V_n
	char attributeValue[128];		// 属性値
	char uniattributeNName[32];		// %doc_att_N_n(unicode用)
	char uniattributeVName[32];		// %doc_att_V_n(unicode用)
	int  uniattlen = 0;
    
	for (int i = 0; i < attCount; i++) {
        
		sprintf(attributeNName, "%s%d", SUMMARY_ATT_NAME, i+1);
		sprintf(attributeVName, "%s%d", SUMMARY_ATT_VALUE, i+1);
		sprintf(uniattributeNName, "%s%s", attributeNName, "(w");
		sprintf(uniattributeVName, "%s%s", attributeVName, "(w");
        
		// %doc_att_N_n(属性名) 取得
		MP_AValue attNameValue = { 0, MP_A_OCTS, NULL }; 
		if (profile->GetAttribute(attributeNName , &attNameValue) == MP_NOERROR) {
			attNameValue.adata = attributeValue;
			profile->GetAttribute(attributeNName , &attNameValue);
		}
		
		if (attNameValue.adata != NULL) {
            
			// %doc_att_V_n(属性値) 取得
			// %doc_att_T_n(タイプ)に関しては全て文字列なので、今の所MP_A_OCTS決めうちで行く。
			MP_AValue attValueValue = { 0, MP_A_OCTS, NULL }; 
			if (strcmp(attributeValue, "%doc_att_title") == 0) {
				// タイトル
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _title;
					profile->GetAttribute(attributeVName , &attValueValue);
				}
			}
			if (strcmp(attributeValue, "%doc_att_subject") == 0) {
				// サブタイトル
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _subject;
					profile->GetAttribute(attributeVName , &attValueValue);
				}
			}
			if (strcmp(attributeValue, "%doc_att_author") == 0) {
				// 作成者
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _author;
					profile->GetAttribute(attributeVName , &attValueValue);
				}
			}
			if (strcmp(attributeValue, "%doc_att_keywords") == 0) {
				// キーワード
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _keywords;
					profile->GetAttribute(attributeVName , &attValueValue);
				}
			}
			if (strcmp(attributeValue, "%doc_att_comments") == 0) {
				// コメント
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _comments;
					profile->GetAttribute(attributeVName , &attValueValue);
				}
			}
            
		} else {

			if (profile->GetAttribute(uniattributeNName , &attNameValue) == MP_NOERROR) {
				attNameValue.adata = attributeValue;
				uniattlen = attNameValue.asize;
				profile->GetAttribute(uniattributeNName , &attNameValue);
			}
            
			// %doc_att_V_n(unicode属性値) 取得
			MP_AValue attValueValue = { 0, MP_A_OCTS, NULL }; 
			if (attValueValue.adata == NULL) {
                
				if (MXCUnicodeCmp(attributeValue, uniattlen, "%doc_att_title") == 0) {
					// タイトル
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						attValueValue.adata = _unititle;
						_unititlen = attValueValue.asize;
						profile->GetAttribute(uniattributeVName , &attValueValue);
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, "%doc_att_subject") == 0) {
					// サブタイトル
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						attValueValue.adata = _unisubject;
						_unisublen = attValueValue.asize;
						profile->GetAttribute(uniattributeVName , &attValueValue);
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, "%doc_att_author") == 0) {
					// 作成者
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						attValueValue.adata = _uniauthor;
						_uniautlen = attValueValue.asize;
						profile->GetAttribute(uniattributeVName , &attValueValue);
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, "%doc_att_keywords") == 0) {
					// キーワード
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						attValueValue.adata = _unikeywords;
						_unikeylen = attValueValue.asize;
						profile->GetAttribute(uniattributeVName , &attValueValue);
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, "%doc_att_comments") == 0) {
					// コメント
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						attValueValue.adata = _unicomments;
						_unicomlen = attValueValue.asize;
						profile->GetAttribute(uniattributeVName , &attValueValue);
					}
				}
			}
		}
	}
	
	return YES;
}

- (void) setDocumentSummaryPropertyValue
{
    if (strlen(_title) > 0) {
        self.fileTitle = [NSString stringWithCString:_title encoding: NSShiftJISStringEncoding];
    } else {
        self.fileTitle = [NSString stringWithCString:_unititle encoding:NSUTF16StringEncoding];
    }
    
    if (strlen(_subject) > 0) {
        self.fileSubtitle = [NSString stringWithCString:_subject encoding: NSShiftJISStringEncoding];
    } else {
        self.fileSubtitle = [NSString stringWithCString:_unisubject encoding:NSUTF16StringEncoding];
    }
    
    if (strlen(_author) > 0) {
        self.fileAuthor = [NSString stringWithCString:_author encoding: NSShiftJISStringEncoding];
    } else {
        self.fileAuthor = [NSString stringWithCString:_uniauthor encoding:NSUTF16StringEncoding];
    }
    
    if (strlen(_keywords) > 0) {
        self.fileKeyword = [NSString stringWithCString:_keywords encoding: NSShiftJISStringEncoding];
    } else {
        self.fileKeyword = [NSString stringWithCString:_unikeywords encoding:NSUTF16StringEncoding];
    }
    
    if (strlen(_comments) > 0) {
        self.fileComment = [NSString stringWithCString:_comments encoding: NSShiftJISStringEncoding];
    } else {
        self.fileComment = [NSString stringWithCString:_unicomments encoding:NSUTF16StringEncoding];
    }
}
*/

- (BOOL) loadDocumentSummaryDataWithProfile:(MPCObject*)profile
{
	self.fileTitle      = nil;
	self.fileSubtitle   = nil;
    self.fileAuthor     = nil;
	self.fileKeyword    = nil;
    self.fileComment    = nil;
    
	_title[0] = 0;			// タイトル
    _subject[0] = 0;		// サブタイトル
    _author[0] = 0;			// 作成者
    _keywords[0] = 0;		// キーワード
    _comments[0] = 0;		// コメント
    
	// [DWVLT70 2008.02.06 by ushijima] >>>
    _unititle[0] = 0;			// タイトル
    _unisubject[0] = 0;			// サブタイトル
    _uniauthor[0] = 0;			// 作成者
    _unikeywords[0] = 0;		// キーワード
    _unicomments[0] = 0;		// コメント
	_unititlen = 0;				// タイトル文字長
	_unisublen = 0;				// サブタイトル文字長
	_uniautlen = 0;				// 作成者文字長
	_unikeylen = 0;				// キーワード文字長
	_unicomlen = 0;				// コメント文字長
	
    // ----------------------------------------------------------
	// 文書概要属性は拡張可能な様式で格納されている。
	// %doc_att_Countに属性の数が格納されており、その数だけ
	// %doc_att_N_n (属性名 : octs)
	// %doc_att_T_n (タイプ : int)
	// %doc_att_V_n (属性値 : octs)
	// (※ nは整数)
	// という属性名で%doc_att_Countの数だけ属性が格納されている。
	// (%doc_att_N_1, %doc_att_N_2, %doc_att_N_3...等)
	//
	// %doc_att_N_nの値でその属性が何を指すのかを判断し、
	// %doc_att_V_nの値を取得し設定する。
	//
	// 文書概要情報に使用する属性(%doc_att_N_nの値)は以下の通り。
	// %doc_att_title		タイトル
	// %doc_att_subject		表題
	// %doc_att_author		作成者
	// %doc_att_keywords	キーワード
	// %doc_att_comments	コメント
	// ----------------------------------------------------------
    
    if (profile == nil) {
        return NO;
    }
	
	// 属性数
	int attCount = 0;
	MP_AValue attCountValue = { 0, MP_A_INT, NULL }; 
	if (profile->GetAttribute(SUMMARY_ATT_COUNT, &attCountValue) == MP_NOERROR) {
		attCountValue.adata = &attCount;
		profile->GetAttribute(SUMMARY_ATT_COUNT, &attCountValue);
	}
	
	char attributeNName[16];		// %doc_att_N_n
	char attributeVName[16];		// %doc_att_V_n
    
    // tongtx 20110713 start
    // AR NO.17892 の対応
	//char attributeValue[128];		// 属性値
    char attributeValue[527];		// 属性値
    // tongtx 20110713 end
    
	char uniattributeNName[32];		// %doc_att_N_n(unicode用)
	char uniattributeVName[32];		// %doc_att_V_n(unicode用)
	int  uniattlen = 0;
    
	// 20110701 M.Chikyu (AR17887,AR17889) start
	// マルチバイトでの文字コードを言語設定で決定する
	
	NSString *encString = NSLocalizedString(@"LOCAL_ENCODING", nil);
	NSStringEncoding nsEnc;
	
	if      ([encString isEqualToString:@"SHIFTJIS_CHARSET"])
	{
		nsEnc = NSShiftJISStringEncoding;
	}
	else if ([encString isEqualToString:@"ANSI_CHARSET"])
	{
		nsEnc = NSWindowsCP1252StringEncoding;
	}
	else if ([encString isEqualToString:@"GB2312_CHARSET"])
	{
		nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseSimplif);
	}
	else if ([encString isEqualToString:@"CHINESEBIG5_CHARSET"])
	{
		nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseTrad);
	}
	else if ([encString isEqualToString:@"HANGEUL_CHARSET"])
	{
		nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSKorean);
	}
	else if ([encString isEqualToString:@"THAI_CHARSET"])
	{
		nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSThai);
	}
	else
	{
		nsEnc = NSWindowsCP1252StringEncoding;
	}
	
	// 20110701 M.Chikyu (AR17887,AR17889) end
    
	for (int i = 0; i < attCount; i++) {
        
        // 20111004 M.Chikyu AR17927 start
		/*
        sprintf(attributeNName, "%s%d", SUMMARY_ATT_NAME, i+1);
        sprintf(attributeVName, "%s%d", SUMMARY_ATT_VALUE, i+1);
        */
		sprintf(attributeNName, "%s%x", SUMMARY_ATT_NAME, i+1);
		sprintf(attributeVName, "%s%x", SUMMARY_ATT_VALUE, i+1);
		// 20111004 M.Chikyu AR17927 end
        
		sprintf(uniattributeNName, "%s%s", attributeNName, "(w");
		sprintf(uniattributeVName, "%s%s", attributeVName, "(w");
        
		// %doc_att_N_n(属性名) 取得
		MP_AValue attNameValue = { 0, MP_A_OCTS, NULL }; 
		if (profile->GetAttribute(attributeNName , &attNameValue) == MP_NOERROR) {
			attNameValue.adata = attributeValue;
			profile->GetAttribute(attributeNName , &attNameValue);
		}
		
		if (attNameValue.adata != NULL) {
            
			// %doc_att_V_n(属性値) 取得
			// %doc_att_T_n(タイプ)に関しては全て文字列なので、今の所MP_A_OCTS決めうちで行く。
			MP_AValue attValueValue = { 0, MP_A_OCTS, NULL }; 
			if (strcmp(attributeValue, "%doc_att_title") == 0) {
				// タイトル
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _title;
					profile->GetAttribute(attributeVName , &attValueValue);
					
					// 20110701 M.Chikyu (AR17887,AR17889) start
					/*
                     self.fileTitle = [NSString stringWithCString:_title encoding: NSShiftJISStringEncoding];
					 */
					self.fileTitle = [NSString stringWithCString:_title encoding: nsEnc];
					// 20110701 M.Chikyu (AR17887,AR17889) end
				}
			}
			if (strcmp(attributeValue, "%doc_att_subject") == 0) {
				// サブタイトル
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _subject;
					profile->GetAttribute(attributeVName , &attValueValue);
					
					// 20110701 M.Chikyu (AR17887,AR17889) start
					/*
                     self.fileSubtitle = [NSString stringWithCString:_subject encoding: NSShiftJISStringEncoding];
					 */
					self.fileSubtitle = [NSString stringWithCString:_subject encoding: nsEnc];
					// 20110701 M.Chikyu (AR17887,AR17889) end
				}
			}
			if (strcmp(attributeValue, "%doc_att_author") == 0) {
				// 作成者
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _author;
					profile->GetAttribute(attributeVName , &attValueValue);
					
					// 20110701 M.Chikyu (AR17887,AR17889) start
					/*
                     self.fileAuthor = [NSString stringWithCString:_author encoding: NSShiftJISStringEncoding];
					 */
					self.fileAuthor = [NSString stringWithCString:_author encoding: nsEnc];
					// 20110701 M.Chikyu (AR17887,AR17889) end
				}
			}
			if (strcmp(attributeValue, "%doc_att_keywords") == 0) {
				// キーワード
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _keywords;
					profile->GetAttribute(attributeVName , &attValueValue);
					
					// 20110701 M.Chikyu (AR17887,AR17889) start
					/*
                     self.fileKeyword = [NSString stringWithCString:_keywords encoding: NSShiftJISStringEncoding];
					 */
					self.fileKeyword = [NSString stringWithCString:_keywords encoding: nsEnc];
					// 20110701 M.Chikyu (AR17887,AR17889) end
				}
			}
			if (strcmp(attributeValue, "%doc_att_comments") == 0) {
				// コメント
				if (profile->GetAttribute(attributeVName , &attValueValue) == MP_NOERROR) {
					attValueValue.adata = _comments;
					profile->GetAttribute(attributeVName , &attValueValue);
					
					// 20110701 M.Chikyu (AR17887,AR17889) start
					/*
                     self.fileComment = [NSString stringWithCString:_comments encoding: NSShiftJISStringEncoding];
					 */
					self.fileComment = [NSString stringWithCString:_comments encoding: nsEnc];
					// 20110701 M.Chikyu (AR17887,AR17889) end
				}
			}
            
		} else {
			
			if (profile->GetAttribute(uniattributeNName , &attNameValue) == MP_NOERROR) {
				attNameValue.adata = attributeValue;
				uniattlen = attNameValue.asize;
				profile->GetAttribute(uniattributeNName , &attNameValue);
			}
            
			// %doc_att_V_n(unicode属性値) 取得
			MP_AValue attValueValue = { 0, MP_A_OCTS, NULL }; 
			if (attValueValue.adata == NULL) {
                
				if (MXCUnicodeCmp(attributeValue, uniattlen, (char*)"%doc_att_title") == 0) {
					// タイトル
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						WCHAR* uniValue = new WCHAR[attValueValue.asize + 1];
						memset(uniValue, 0x00, (attValueValue.asize + 1) * sizeof(WCHAR));
						attValueValue.adata = uniValue;
						
						if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR)
						{
							self.fileTitle =  [NSString stringWithCharacters:uniValue length:(attValueValue.asize)];
						}
						if (uniValue != NULL) {
							delete[] uniValue;
						}
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, (char*)"%doc_att_subject") == 0) {
					// サブタイトル
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						
						WCHAR* uniValue = new WCHAR[attValueValue.asize + 1];
						memset(uniValue, 0x00, (attValueValue.asize + 1) * sizeof(WCHAR));
						attValueValue.adata = uniValue;
						
						if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR)
						{
							self.fileSubtitle =  [NSString stringWithCharacters:uniValue length:(attValueValue.asize)];
						}
						if (uniValue != NULL) {
							delete[] uniValue;
						}
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, (char*)"%doc_att_author") == 0) {
					// 作成者
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						WCHAR* uniValue = new WCHAR[attValueValue.asize + 1];
						memset(uniValue, 0x00, (attValueValue.asize + 1) * sizeof(WCHAR));
						attValueValue.adata = uniValue;
						
						if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR)
						{
							self.fileAuthor =  [NSString stringWithCharacters:uniValue length:(attValueValue.asize)];
						}
						if (uniValue != NULL) {
							delete[] uniValue;
						}
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, (char*)"%doc_att_keywords") == 0) {
					// キーワード
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						WCHAR* uniValue = new WCHAR[attValueValue.asize + 1];
						memset(uniValue, 0x00, (attValueValue.asize + 1) * sizeof(WCHAR));
						attValueValue.adata = uniValue;
						
						if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR)
						{
							self.fileKeyword =  [NSString stringWithCharacters:uniValue length:(attValueValue.asize)];
						}
						if (uniValue != NULL) {
							delete[] uniValue;
						}
					}
				}
				if (MXCUnicodeCmp(attributeValue, uniattlen, (char*)"%doc_att_comments") == 0) {
					// コメント
					if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR) {
						WCHAR* uniValue = new WCHAR[attValueValue.asize + 1];
						memset(uniValue, 0x00, (attValueValue.asize + 1) * sizeof(WCHAR));
						attValueValue.adata = uniValue;
						
						if (profile->GetAttribute(uniattributeVName , &attValueValue) == MP_NOERROR)
						{
							self.fileComment =  [NSString stringWithCharacters:uniValue length:(attValueValue.asize)];
						}
						if (uniValue != NULL) {
							delete[] uniValue;
						}
					}
				}
			}
		}
	}
	
	return YES;
}
// lixin 20110623 DW_iPhoneEnhance_12 end

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
- (long) getFilePermission:(NSString*)filepath
{
	long result = 0;
	
	if (filepath == nil)
	{
		return 0;
	}
	
	const char *filepath_const_char = [filepath UTF8String];
	char filepath_char[1024] = { 0 };
	strcpy(filepath_char, filepath_const_char);
	HRESULT hres	= MP_NOERROR;
	MPCSession	*mpcSession_ = ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession_ == XdwNull)
	{
		return 0;
	}
	
	MPCObject *mpcDocObject_ = mpcSession_->OpenFile(filepath_char, &hres, MP_READONLY);
	if (hres != MP_NOERROR || mpcDocObject_ == XdwNull)
	{
		::MPCDestroyMPCSession(mpcSession_);
		
		return 0;
	}
	
	MPCProfile *mpcProfile_ = (MPCProfile*)mpcDocObject_->GetInterface(IID_MPCProfile, &hres);
	if (hres != MP_NOERROR || mpcProfile_ == XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
		
		return 0;
	}
	
	result = mpcProfile_->GetPermission();
	
	if (mpcSession_ != XdwNull && mpcDocObject_ != XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
	}
	
	return result;
}
// zhaijie 2012.03.30 end

- (void)dealloc {

    [fileTitle release];
    [fileSubtitle release];
    [fileAuthor release];
    [fileKeyword release];
    [fileComment release];
    
    [super dealloc];
}
@end
