//
//  LinkAnnotationManager.m
//  DWViewer
//
//  Created by liuqw on 10-11-24.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "LinkAnnotationManager.h"
#import "DocumentViewController.h"
// AR NO.17516 の対応 start
#import "DWScrollView.h"
// AR NO.17516 の対応 end

#import "FileInfo.h"
#import "XdwFileInfo.h"
#import "XdwDocumentHandle.h"

// 20110331 M.Chikyu start
// 国際化ドメイン対応

#import "punycode.h"

// 20110331 M.Chikyu end

// 20110407 M.Chikyu start
// AR17765, AR17766

#import "MXCTextUtl.h"

// 20110407 M.Chikyu end

@implementation LinkAnnotationManager

- (id) initWithDocumentViewController:(DocumentViewController*) viewController
						  XdwFileInfo:(XdwFileInfo*)xdwFileInfo
						LinkAnnotInfo:(LinkAnnotInfo*)linkInfo

{
	documentViewController = viewController;
	fileInfo = xdwFileInfo;
	linkAnnoInfo = linkInfo;
	return self;
}


- (BOOL) isSupportLinkTo
{

	if (nil == linkAnnoInfo) {
		return NO;
	}
	// check linkto 
	bool otherFile = NO;
	bool profile = NO;
	
	switch (linkAnnoInfo->GetLinkTo())  {
		case LINK_TO_ME: 
			if (linkAnnoInfo->GetLinkToPageNum() == 0) {
				profile = YES;
			}	
			break;
		case LINK_TO_OTHERFILE:
		case LINK_TO_XDW:
			otherFile = YES;	
			break;
		default:
			break;
	}
	// warning profile
	if (profile) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
														message:NSLocalizedString(@"MSG_WARNING_ANNO_SETJUMPWARNING", nil) 
													   delegate:nil 
											  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
											  otherButtonTitles:nil];
		[alert show];
		[alert release];
		
		return NO;
	}
	// warning ohterfile
	if (otherFile) {
		UIAlertView *alert=[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil)  
													  message:NSLocalizedString(@"MSG_WARNING_ANNO_LINKTOOTHERDOCWARNING", nil) 
													 delegate:nil 
											cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											otherButtonTitles:nil];
		[alert show];
		[alert release];
		
		return NO;
	}
	
	return YES;
}


- (BOOL) isConfilictLinkTo
{
	if (nil == fileInfo) {
		return YES;
	}
	if (nil == linkAnnoInfo) {
		return YES;
	}

	LinkAnnotInfo::LinkTo linkTo =  linkAnnoInfo->GetLinkTo();
	if (!fileInfo->IsBinder() && linkTo == LINK_TO_ME) {
		LinkAnnotInfo::LinkPageAttribute pageAttr = linkAnnoInfo->GetPageCheck();
		if (pageAttr == LINK_BINDER_ALLPAGE ||
			pageAttr == LINK_BINDER_OTHER_DOC) {
			
			UIAlertView *alert=[[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil)  
														  message:NSLocalizedString(@"MSG_WARNING_ANNO_LINKCONFLICTWARNING", nil) 
														 delegate:nil 
												cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
												otherButtonTitles:nil];
			[alert show];
			[alert release];
			return YES;
		}
	}
	return NO;
}



- (NSString *) getLinkToContent;
{
	if (nil == linkAnnoInfo) {
		return nil;
	}
	NSString* message = nil;
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	switch (linkAnnoInfo->GetLinkTo())  {
		case LINK_TO_ME: 
			message = [self getToolTipMessage];
			break;
		case LINK_TO_MAILADDRESS:
			message = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
										 encoding:NSShiftJISStringEncoding];
			break;
		case LINK_TO_URL:
			message = [NSString stringWithCString:linkAnnoInfo->GetUrlString() 
										 encoding:NSShiftJISStringEncoding];
			break;
		case LINK_TO_OTHERFILE:
			message = [NSString stringWithCString:linkAnnoInfo->GetOtherFilePathString() 
										 encoding:NSShiftJISStringEncoding];
		case LINK_TO_XDW:
		default:
			break;
	}
	*/
	
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	
	switch (linkAnnoInfo->GetLinkTo())
	{
		case LINK_TO_ME: 
			message = [self getToolTipMessage];
			break;
			
		case LINK_TO_MAILADDRESS:
			message = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
										 encoding:nsEnc];
			break;
			
		case LINK_TO_URL:
			message = [NSString stringWithCString:linkAnnoInfo->GetUrlString() 
										 encoding:nsEnc];
			break;
			
		case LINK_TO_OTHERFILE:
			message = [NSString stringWithCString:linkAnnoInfo->GetOtherFilePathString() 
										 encoding:nsEnc];
		case LINK_TO_XDW:
		default:
			break;
	}
	
	// 20110407 M.Chikyu end
	
	return message;
}

- (void) doJump
{
	if (nil == linkAnnoInfo) {
		return;
	}
	switch (linkAnnoInfo->GetLinkTo()) {
		case LINK_TO_ME:
			[self linkToMe];
			break;
		case LINK_TO_MAILADDRESS:
			[self linkToMailAddress];
			break;
		case LINK_TO_URL:
			[self linkToURL];
			break;
		case LINK_TO_OTHERFILE:
		case LINK_TO_XDW:
		default:
			break;
	}
}

- (void) linkToMe
{
	if (linkAnnoInfo != nil) {
		switch (linkAnnoInfo->GetDwJumpType()) {
			case LINK_TO_DWTYPE_PAGE:
				[self linkToDWTypePage];
				break;
			case LINK_TO_DWTYPE_LINKANN:
				[self linkToDWTypeLinkAnn];
				break;
			default:
				break;
		}
	}
}

- (void) linkToURL
{
	if (nil == linkAnnoInfo) {
		return;
	}
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* Url = [NSString stringWithCString:linkAnnoInfo->GetUrlString() encoding:NSShiftJISStringEncoding];
	 */
	
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* Url = [NSString stringWithCString:linkAnnoInfo->GetUrlString() encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	
	// 20110331 M.Chikyu start
	// 国際化ドメイン対応
	
	/*
	// AR17721の対応 start.
	// get URL with encoding NSUTF8StringEncoding
	Url = [Url stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	// AR17721の対応 end.
	 
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:Url]];
	*/
	
	// Punycodeに変換
	NSString *destUrl = [NSString stringWithString:[self getPunycodeURL:Url]];
	
	if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:destUrl]] == YES)
	{
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:destUrl]];
	}
	
	return;
	
	// 20110331 M.Chikyu start
}


- (void) linkToMailAddress
{
	if (nil == linkAnnoInfo) {
		return;
	}
	Class mailController = (NSClassFromString(@"MFMailComposeViewController"));
	if (mailController != nil) {
		if ([mailController canSendMail]) {
			[self showMailComposeView];
		} else {
			[self launchMailApplication];
		}
	} else {
		[self launchMailApplication];
	}
}

- (void) showMailComposeView
{
	if (nil == linkAnnoInfo) {
		return;
	}
	
	MFMailComposeViewController* mailController = [[MFMailComposeViewController alloc] init];
	mailController.mailComposeDelegate = documentViewController;
	[mailController setSubject:@""];
	
	// Set up recipients
	
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* eMailString = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* eMailString = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
											   encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	
	NSArray* toRecipients = [NSArray arrayWithObject:eMailString];  
	
	[mailController setToRecipients:toRecipients];
	[mailController setCcRecipients:nil];
	[mailController setBccRecipients:nil];
	
	// Fill out the email body text
	NSString* eMailBody = @"";
	[mailController setMessageBody:eMailBody isHTML:NO];
	
	[documentViewController presentModalViewController:mailController animated:YES];
	[mailController release];
	
}

- (void) launchMailApplication
{
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* eMailString = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* eMailString = [NSString stringWithCString:linkAnnoInfo->GetMailadressString() 
											   encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	
	
	NSString *recipients = [NSString stringWithFormat:@"mailto:%@?cc=&subject=", eMailString];
	NSString *body = @"&body=";
	
	NSString *email = [NSString stringWithFormat:@"%@%@", recipients, body];
	email = [email stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:email]];
}



- (void) linkToDWTypePage
{
	if (linkAnnoInfo != nil) {
		switch (linkAnnoInfo->GetPageCheck()) {
			case LINK_THIS_FILE:
				[self linkToThisFile];
				break;
			case LINK_BINDER_ALLPAGE:
				[self linkToBinderAllPage];
				break;
			case LINK_BINDER_OTHER_DOC:
				[self linkToBinderOtherDocument];
				break;
			default :
				break;
		}
	}
}

- (void) linkToThisFile
{
	if (nil == fileInfo) {
		return;
	}
	
	if (fileInfo->IsBinder()) {
		[self linkToThisFileXBD];
	} else {
		[self linkToThisFileXDW];
	}
}

- (void) linkToThisFileXDW
{
	
	if (nil == fileInfo) {
		return;
	}
	if (nil == linkAnnoInfo) {
		return;
	}
	long linkToPageNum = linkAnnoInfo->GetLinkToPageNum();
	if (linkToPageNum > fileInfo->GetPageCount()) {
		linkToPageNum = fileInfo->GetPageCount();
	}
	[self jumpToTarget:linkToPageNum];
}

- (void) linkToThisFileXBD
{
	if (nil == fileInfo) {
		return;
	}
	if (nil == linkAnnoInfo) {
		return;
	}
	
	long linkToPageNum = linkAnnoInfo->GetLinkToPageNum();
	long linkAtPageNum = linkAnnoInfo->GetXdwPageNum();

	long currPageNum = 0;
	for (int i = 0; i < fileInfo->GetBinderCount(); i++) {
		long docPageCount = fileInfo->GetPageCntOfBinderDoc(i);
		if (docPageCount <= 0) {
			continue;
		}
		if (linkAtPageNum < currPageNum + docPageCount) {
			if (linkToPageNum > docPageCount) {
				linkToPageNum = docPageCount;
			}
			linkToPageNum += currPageNum;
			break;
		}
		currPageNum += docPageCount;

	}
	[self jumpToTarget:linkToPageNum];
}

- (void) linkToBinderOtherDocument
{
	
	if (nil == fileInfo) {
		return;
	}
	if (nil == linkAnnoInfo) {
		return;
	}
	
	long linkToPageNum = linkAnnoInfo->GetLinkToPageNum();
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString *SheafName = [NSString stringWithCString:linkAnnoInfo->GetSheafnameString() 
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString *SheafName = [NSString stringWithCString:linkAnnoInfo->GetSheafnameString() 
											 encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	
	long currPageNum = 0;
	BOOL bFind = NO;
	for (int i = 0; i < fileInfo->GetBinderCount(); i++) {
		
		// 20110407 M.Chikyu start
		// AR17765, AR17766
		
		/*
		 NSString *nameOfBinderDoc = [NSString stringWithCString:fileInfo->GetNameOfBinderDoc(i) 
		 encoding:NSShiftJISStringEncoding];
		 */
		NSString *nameOfBinderDoc = [NSString stringWithCString:fileInfo->GetNameOfBinderDoc(i)
													   encoding:nsEnc];
		
		// 20110407 M.Chikyu end
		
		long docPageCount = fileInfo->GetPageCntOfBinderDoc(i);
		if (docPageCount <= 0) {
			continue;
		}
		if ([SheafName isEqualToString:nameOfBinderDoc]) {
			if (linkToPageNum > docPageCount) {
				linkToPageNum = docPageCount;
			}
			currPageNum += linkToPageNum;
			bFind = YES;
			break;
		} else {
			currPageNum += docPageCount;
		}
		
	}
	linkToPageNum = currPageNum;
	if (!bFind) {
		linkToPageNum = 1;
	}
	[self jumpToTarget:linkToPageNum];
}

- (void) linkToBinderAllPage
{
	if (nil == fileInfo) {
		return;
	}
	if (nil == linkAnnoInfo) {
		return;
	}
	long linkToPageNum = linkAnnoInfo->GetLinkToPageNum();
	if (linkToPageNum > fileInfo->GetPageCount()) {
		linkToPageNum = fileInfo->GetPageCount();
	}
	[self jumpToTarget:linkToPageNum];
}


- (void) linkToDWTypeLinkAnn
{
	if (nil == fileInfo) {
		return;
	}
	if (nil == linkAnnoInfo) {
		return;
	}

	PageViewManager* mgr = documentViewController.pageViewMgr;
	if (nil == mgr) {
		return;
	}
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* title = [NSString stringWithCString:linkAnnoInfo->GetLinkJumpTitleString() 
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* title = [NSString stringWithCString:linkAnnoInfo->GetLinkJumpTitleString()
										 encoding:nsEnc];
	
	// 20110407 M.Chikyu end

	LinkAnnotInfoList *linkAnnInfoList = [mgr getLinkAnnotationInfoList];
	
	if (NULL == linkAnnInfoList) {
		return;
	}
	//AR NO.31 
	for (int i = 0; i < linkAnnInfoList->Size(); i++) {
		LinkAnnotInfo *info = linkAnnInfoList->GetLinkAnnotInfo(i);
		
		// 20110407 M.Chikyu start
		// AR17765, AR17766
		
		/*
		 NSString* targetTitle = [NSString stringWithCString:info->GetLinkTitleString()
		 encoding:NSShiftJISStringEncoding]; 
		 */
		NSString* targetTitle = [NSString stringWithCString:info->GetLinkTitleString()
												   encoding:nsEnc];
		
		// 20110407 M.Chikyu end 
		
		if ([title isEqualToString:targetTitle]) {
			long pageNum = info->GetXdwPageNum();
			[self jumpToTarget:(pageNum + 1)];
			return;
		}

	}
	[self jumpToTarget:1];
}

// リンクアノテーション表示不具合(AR17722)対応 M.Chikyu 20110224 -start

/*
//get the tooltip message
- (NSString *) getToolTipMessage
{
	NSString *showMessage = nil;
	if (linkAnnoInfo != nil) {
		switch (linkAnnoInfo->GetPageCheck()) {
			case LINK_THIS_FILE:
				showMessage = [self getLinkToThisFileMessage];
				break;
			case LINK_BINDER_ALLPAGE:
				showMessage = [self getLinkToBinderAllPageMessage];
				break;
			case LINK_BINDER_OTHER_DOC:
				showMessage = [self getLinkToBinderOtherDocumentMessage];
				break;
			default :
				break;
		}
	}
	return showMessage;
}
*/

//get the tooltip message
- (NSString *) getToolTipMessage
{
	NSString *showMessage = nil;
	
	if (linkAnnoInfo != nil)
	{
		switch (linkAnnoInfo->GetDwJumpType())
		{
			case LINK_TO_DWTYPE_PAGE:
				showMessage = [self getPageToolTipMessage];
				break;
				
			case LINK_TO_DWTYPE_LINKANN:
				showMessage = [self getLinkAnnToolTipMessage];
				break;
				
			default:
				break;
		}
	}
	
	return showMessage;
}

- (NSString *) getPageToolTipMessage
{
	NSString *showMessage = nil;
	
	if (linkAnnoInfo != nil)
	{
		switch (linkAnnoInfo->GetPageCheck())
		{
			case LINK_THIS_FILE:
				showMessage = [self getLinkToThisFileMessage];
				break;
				
			case LINK_BINDER_ALLPAGE:
				showMessage = [self getLinkToBinderAllPageMessage];
				break;
				
			case LINK_BINDER_OTHER_DOC:
				showMessage = [self getLinkToBinderOtherDocumentMessage];
				break;
				
			default :
				break;
		}
	}
	return showMessage;
}

- (NSString *) getLinkAnnToolTipMessage
{
	NSString *showMessage = nil;
	
	if (fileInfo == nil)
	{
		return showMessage;
	}
	
	if (linkAnnoInfo == nil)
	{
		return showMessage;
	}
	
	PageViewManager* mgr = documentViewController.pageViewMgr;
	if (mgr == nil)
	{
		return showMessage;
	}
	
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* title = [NSString stringWithCString:linkAnnoInfo->GetLinkJumpTitleString() 
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* title = [NSString stringWithCString:linkAnnoInfo->GetLinkJumpTitleString() 
										 encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	if (title == nil)
	{
		return showMessage;
	}
	
	showMessage = [NSString stringWithFormat:NSLocalizedString(@"MSG_LINKANNO_TITLE", nil), title];
	
	return showMessage;
}

// リンクアノテーション表示不具合(AR17722)対応 M.Chikyu 20110224 -end

- (NSString *) getLinkToThisFileMessage
{
	if (nil == linkAnnoInfo) {
		return NULL;
	}
	NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_LINKANNO_XDWPAGENUMBER", nil),
						 linkAnnoInfo->GetLinkToPageNum() ];
	return message;
}


- (NSString *) getLinkToBinderAllPageMessage
{
	if (nil == linkAnnoInfo) {
		return NULL;
	}
	NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_LINKANNO_XBDPAGENUMBER", nil), 
						 linkAnnoInfo->GetLinkToPageNum()];
	
	return message;
}


- (NSString *) getLinkToBinderOtherDocumentMessage
{
	// 20110407 M.Chikyu start
	// AR17765, AR17766
	
	/*
	 NSString* SheafName = [NSString stringWithCString:linkAnnoInfo->GetSheafnameString()
	 encoding:NSShiftJISStringEncoding];
	 */
	NSStringEncoding nsEnc = MXCGetNSStringEncoding(linkAnnoInfo->GetLinkTitleCharSet());
	NSString* SheafName = [NSString stringWithCString:linkAnnoInfo->GetSheafnameString()
											 encoding:nsEnc];
	
	// 20110407 M.Chikyu end
	
	if (linkAnnoInfo->GetLinkToPageNum() <= 0) {
		NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_LINKANNO_PROFILE", nil), SheafName];
		return message;
	}
	else {
		NSString* message = [NSString stringWithFormat:NSLocalizedString(@"MSG_LINKANNO_INTERNALFILE", nil), 
							 SheafName, linkAnnoInfo->GetLinkToPageNum()];
		return message;
	}
}

- (void) jumpToTarget:(long)pageNum
{
	// AR NO.17516 の対応 start
	int position = 0;
	PageViewManager *pageViewMgr = documentViewController.pageViewMgr;
	DWScrollView *pageView = [documentViewController getActivePageView];
	if (pageView != nil) {
		if (pageView.isFacingPage == NO) {
			position = pageNum - 1;
		} else {
			
			if (pageViewMgr.facingMode == MODE_FACE_NO) {
				position = (pageNum - 1) / 2;
			} else {
				if (pageNum == 1) {
					position = 0;
				} else {
					position = (pageNum - 1) / 2 + (pageNum - 1) % 2;
				}
			}
		}
		
		if (pageViewMgr.fontOrient == NO) {
			int pageCount = [pageViewMgr getPageViewCount];
			position = pageCount - 1 - position;
		}
	}
	
	// liuqw 20110330 start
	// リンクアノテーションのジャンプの不具合の対応
	/*
	[documentViewController actionMoveOnePageWithPosition:position 
										 withMovePageMode:MODE_PAGE_OTHER];
	*/
	[documentViewController actionMovePageWithPosition:position 
									  withMovePageMode:MODE_PAGE_OTHER];
	// liuqw 20110330 emd
	// AR NO.17516 の対応 end
}

// 20110331 M.Chikyu start
// 国際化ドメイン対応

- (NSString *) getPunycodeURL:(NSString *)srcUrl
{
	int index;
	
	NSMutableString *scheme	= [NSMutableString stringWithString:@""];
	NSMutableString *path	= [NSMutableString stringWithString:@""];
	NSMutableString *host	= [NSMutableString stringWithString:@""];
	NSMutableString *dstUrl	= [NSMutableString stringWithString:@""];
	
	// schemeとhost+pathに分離
	NSArray *all;

	if ([srcUrl rangeOfString:@"://"].location != NSNotFound)
	{
		all	= [srcUrl componentsSeparatedByString:@"://"];
	}
	else if ([srcUrl rangeOfString:@":"].location != NSNotFound)
	{
		all	= [srcUrl componentsSeparatedByString:@":"];
	}
	else
	{
		return srcUrl;
	}
	
	// hostと各path要素に分離
	NSArray *paths	= [(NSString *)[all objectAtIndex:1] componentsSeparatedByString:@"/"];
	
	// 各host要素に分離
	NSArray *hosts	= [(NSString *)[paths objectAtIndex:0] componentsSeparatedByString:@"."];
	
	
	//
	// scheme(ex. http://)を再構成
	//
	
	[scheme appendString:[all objectAtIndex:0]];
	[scheme appendString:@"://"];
	
	
	//
	// host(ex. domain.jp)を再構成
	//
	
	// 配列の先頭要素をPunycodeに変換してhostに追加
	std::string host_str = Punycode::encode([(NSString *)[hosts objectAtIndex:0] UTF8String]);
	[host appendString:[NSString stringWithCString:host_str.c_str()
										  encoding:NSUTF8StringEncoding]];
	
	for (index = 1; index < [hosts count]; index++)
	{
		// セパレータを追加
		[host appendString:@"."];
		
		// 配列のindex要素をPunycodeに変換してhostに追加
		host_str = Punycode::encode([(NSString *)[hosts objectAtIndex:index] UTF8String]);
		[host appendString:[NSString stringWithCString:host_str.c_str()
											  encoding:NSUTF8StringEncoding]];
	}
	
	
	//
	// path(ex. /doc/index.html)を再構成
	//
	
	for (index = 1; index < [paths count]; index++)
	{
		// セパレータを追加
		[path appendString:@"/"];
		
		// 配列のindex要素をエスケープ表現に変換してpathに追加
		NSString *path_str = [paths objectAtIndex:index];
		[path appendString:[path_str stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
	}
	
	
	// 全ての要素を結合
	[dstUrl appendString:scheme];
	[dstUrl appendString:host];
	[dstUrl appendString:path];
	
	return dstUrl;
}

// 20110331 M.Chikyu end


@end 
