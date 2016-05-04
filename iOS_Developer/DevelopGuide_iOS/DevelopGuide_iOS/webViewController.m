    //
//  webViewController.m
//  BookTicket
//
//  Created by neusoft  on 11-4-13.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "webViewController.h"
#import "FileManager.h"

@implementation webViewController
@synthesize url;

- (void)viewDidLoad {
    [super viewDidLoad];

	webView_ = [[UIWebView alloc] init];
	[webView_ setOpaque:NO];
	webView_.delegate = self;
	[webView_ setBackgroundColor:[UIColor scrollViewTexturedBackgroundColor]];
	webView_.frame = CGRectMake(0, 0, 320, 400);
    
    // if YES, the webpage is scaled to fit and the user can zoom in and zoom out. If NO, user zooming is disabled. The default value is NO. 
    webView_.scalesPageToFit = YES;
    
	[self.view addSubview:webView_];

	//url = @"http://www.google.com.hk/";
    
    
    url = [[NSBundle mainBundle] pathForResource:@"[2012-08-01]最美CC 伴您“速”质生活.html" ofType:nil];
    //url = [NSURL fileURLWithPath:wordPath];
	[self loadWebsitWithURL:url];
    
    
    
    // 转换pdf按钮
	self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc] 
                                              initWithBarButtonSystemItem:UIBarButtonSystemItemEdit 
                                              target:self action:@selector(actionWordToPdf)] autorelease];	
 
}

- (void) actionWordToPdf
{
    NSString *pdfPath = [FileManager createFilePath:@"Word"];
    NSString *pdfName = [pdfPath stringByAppendingPathComponent:@"word.pdf"];
    //GenerationgPDFManager *pdfMge = [[GenerationgPDFManager alloc] init];
    CGRect rect = CGRectMake(0, 0, 595, 842);

    // Create the PDF context using the default page size of rect.
    BOOL res = UIGraphicsBeginPDFContextToFile(pdfName, rect, nil);
    if (res) {
        // create pdf page
        UIGraphicsBeginPDFPageWithInfo(rect, nil);
        CGContextRef ctx = UIGraphicsGetCurrentContext();
        [webView_.layer renderInContext:ctx];
    }
    // end create pdf file
    UIGraphicsEndPDFContext();

}

- (void) loadWebsitWithURL:(NSString *)websitUrl
{
	if (websitUrl != nil) {
        /*
         * url的编码格式为UTF8,所以将用来创建url的字符串转换为UTF8编码格式。
         */
		//NSString *fullUrl = [websitUrl stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
		//NSURL* url_ = [[NSURL alloc] initWithString:fullUrl];
        NSURL *url_ = [NSURL fileURLWithPath:websitUrl];
		[webView_ loadRequest:[NSURLRequest requestWithURL:url_]];
		//[url_ release];
	}
}

- (void) stopLoadingWebView
{
    [webView_ stopLoading];
}

#pragma mark -
#pragma mark UIWebView delegate
- (void)webViewDidStartLoad:(UIWebView *)webView
{
	
}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
	
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
	
}
// 定义是否可以载入NSURLRequest的类型，以及是否支持webview的navigationType类型
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}


- (void)dealloc {
	//[url release];
    [webView_ release];
    [super dealloc];
}


@end
