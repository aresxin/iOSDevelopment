//
//  webViewController.h
//  BookTicket
//
//  Created by neusoft  on 11-4-13.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface webViewController : UIViewController <UIWebViewDelegate> {
	NSString*	url;
    UIWebView   *webView_;
}

@property (nonatomic, retain) NSString *url;
- (void) loadWebsitWithURL:(NSString *)websitUrl;
- (void) stopLoadingWebView;
@end
