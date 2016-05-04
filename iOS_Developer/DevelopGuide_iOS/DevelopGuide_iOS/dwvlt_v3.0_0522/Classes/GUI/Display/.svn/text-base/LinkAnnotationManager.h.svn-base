//
//  LinkAnnotationManager.h
//  DWViewer
//
//  Created by liuqw on 10-11-24.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LinkAnnotInfo.h"

class XdwFileInfo;
@class DocumentViewController;

@interface LinkAnnotationManager : NSObject
{
	DocumentViewController* documentViewController;
	XdwFileInfo* fileInfo;
	LinkAnnotInfo* linkAnnoInfo;
}

- (id) initWithDocumentViewController:(DocumentViewController*) viewController
						  XdwFileInfo:(XdwFileInfo*)xdwFileInfo
						LinkAnnotInfo:(LinkAnnotInfo*)linkInfo;

// check not support linkto.
- (BOOL) isSupportLinkTo;
// check Confilict linkto.
- (BOOL) isConfilictLinkTo;
// get linkto title.
- (NSString *) getLinkToContent;


#pragma mark -
#pragma mark private
- (void) doJump;

- (void) linkToURL;

- (void) linkToMailAddress;
- (void) showMailComposeView;
- (void) launchMailApplication;

- (void) linkToMe;
- (void) linkToDWTypePage;
- (void) linkToThisFile;
- (void) linkToBinderAllPage;
- (void) linkToBinderOtherDocument;

- (void) linkToThisFileXDW;
- (void) linkToThisFileXBD;

- (NSString *) getToolTipMessage;

// リンクアノテーション表示不具合(AR17722)対応 M.Chikyu 20110224 -start
- (NSString *) getPageToolTipMessage;
- (NSString *) getLinkAnnToolTipMessage;
// リンクアノテーション表示不具合(AR17722)対応 M.Chikyu 20110224 -end

- (NSString *) getLinkToThisFileMessage;
- (NSString *) getLinkToBinderAllPageMessage;
- (NSString *) getLinkToBinderOtherDocumentMessage;

- (void) linkToDWTypeLinkAnn;
- (void) jumpToTarget:(long)pageNum;

// 20110331 M.Chikyu start
// 国際化ドメイン対応

- (NSString *) getPunycodeURL:(NSString *)srcUrl;

// 20110331 M.Chikyu end
@end
