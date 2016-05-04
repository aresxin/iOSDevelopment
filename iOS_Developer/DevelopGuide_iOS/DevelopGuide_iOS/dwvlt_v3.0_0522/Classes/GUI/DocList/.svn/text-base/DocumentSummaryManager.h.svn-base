//
//  DocumentSummaryManager.h
//  DWViewer
//
//  Created by liuqw on 11-6-19.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "mpc_api.h"
#import "XdwAttributeParser.h"

@interface DocumentSummaryManager : NSObject {

    char		_title[1025];			// タイトル
    char		_subject[1025];			// サブタイトル
    char		_author[1025];			// 作成者
    char		_keywords[1025];		// キーワード
    char		_comments[1025];		// コメント
    
    char		_unititle[2050];		// タイトル
    char		_unisubject[2050];		// サブタイトル
    char		_uniauthor[2050];		// 作成者
    char		_unikeywords[2050];		// キーワード
    char		_unicomments[2050];		// コメント
	int			_unititlen;				// タイトル長
	int			_unisublen;				// サブタイトル長
	int			_uniautlen;				// 作成者長
	int			_unikeylen;				// キーワード長
	int			_unicomlen;				// コメント長
    
    NSString*   fileTitle;
    NSString*   fileSubtitle;
    NSString*   fileAuthor;
    NSString*   fileKeyword;
    NSString*   fileComment;
}
@property (nonatomic, retain) NSString*   fileTitle;
@property (nonatomic, retain) NSString*   fileSubtitle;
@property (nonatomic, retain) NSString*   fileAuthor;
@property (nonatomic, retain) NSString*   fileKeyword;
@property (nonatomic, retain) NSString*   fileComment;

- (BOOL) getDocumentSummaryDataWithFilePath:(NSString *)filePath;

- (BOOL) loadDocumentSummaryDataWithProfile:(MPCObject*)profile;

// lixin 20110623 DW_iPhoneEnhance_12 start
// AR.17855 の対応 
//- (void) setDocumentSummaryPropertyValue;
// lixin 20110623 DW_iPhoneEnhance_12 end

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
- (long) getFilePermission:(NSString*)filepath;
// zhaijie 2012.03.30 end
@end
