//
//  InterfaceWebService.m
//  EasyLife
//
//  Created by neusoft  on 11-11-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "InterfaceWebService.h"


@implementation InterfacewsHttpResponse
@synthesize error = error_;
@synthesize receiveData = receiveData_;
- (id) init
{
    self = [super init];
    if (self) {
        self.error = nil;
        self.receiveData = nil;
    }
    return self;
}

- (void) dealloc
{
    [receiveData_ release];
    [error_ release];
    [super dealloc];
}
@end


@implementation InterfaceWebService
@synthesize urlConnect = urlConnect_;
@synthesize httpResponse = httpResponse_;

- (id) init
{
    self = [super init];
    if (self) {
        responseData_ = nil;
        urlConnect_ = nil;
    }
    return self;
}

- (void) dealloc
{
    [responseData_ release];
    [urlConnect_ release];
    [httpResponse_ release];
    [super dealloc];
}

- (void) stopHTTPCall
{
    if (urlConnect_ != nil) {
        [urlConnect_ cancel];
        self.urlConnect = nil;
    }
}

- (void) sendHTTPCallUsingRequest:(id)param withConnectMode:(connectMode)connectMode
{
    // 根据param生成request
    NSURLRequest *req = nil;
    
    if (responseData_ != nil) {
        [responseData_ release];
        responseData_ = nil;
    }
    responseData_ = [[NSMutableData alloc] init];
    
    self.httpResponse = [[[InterfacewsHttpResponse alloc] init] autorelease];
    self.urlConnect = [[[NSURLConnection alloc] initWithRequest:req delegate:self] autorelease];
    
    if (connectMode == synchConnect) {
        while (urlConnect_ == nil) 
        {
            //[[NSRunLoop currentRunLoop] runUntilDate:[NSDate distantFuture]];
            [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode 
                                     beforeDate:[NSDate distantFuture]];
        }
    }
}

- (void) sendhttpSynchCallUsingRequest:(id)param
{
    // 根据param生成request
    NSURLRequest *request = nil;
    
    self.httpResponse = [[[InterfacewsHttpResponse alloc] init] autorelease];
    NSURLResponse *response = nil;
    NSError       *err = nil;
    NSData        *responseData = nil;
    responseData = [NSURLConnection sendSynchronousRequest:request 
                                         returningResponse:&response 
                                                     error:&err];
    if (response == nil || responseData == nil || err != nil) 
    {
        // connect failed
        httpResponse_.error = err;
    } 
    else 
    {
        // connect sucess
        httpResponse_.receiveData = responseData;
    }   
}

- (void) sendSynchRequestWith:(id)param
{
    self.httpResponse = [[[InterfacewsHttpResponse alloc] init] autorelease];
    
    // 获取设定ip
    NSString *urlString = nil;
    
    NSURL *url = [NSURL URLWithString:[urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    
    ASIFormDataRequest *request=[ASIFormDataRequest requestWithURL:url];
    //根据param生产request
    [request appendPostData:[param dataUsingEncoding:NSUTF8StringEncoding]];
    // 设定链接超时
	[request setTimeOutSeconds:10];
	[request startSynchronous];
    
	NSError *error = [request error];
	if (error == nil) 
    {
       httpResponse_.receiveData = [request responseData];
	} 
    else 
    {
        httpResponse_.error = error;
    }
}

- (void) authen:(id)param
{
	ASIHTTPRequest *request;
	request=[ASIHTTPRequest requestWithURL:[NSURL URLWithString:@"http://allseeing-i.com/top_secret/"]];
	[request setUseKeychainPersistence:NO];
	[request setDelegate:self];
    //根据param生产request
    NSData *postData = [param dataUsingEncoding:NSUTF16LittleEndianStringEncoding];
    [request appendPostData:postData];
	[request setShouldPresentAuthenticationDialog:YES];
	[request setDidFinishSelector:@selector(topSecretFetchComplete:)];
	[request setDidFailSelector:@selector(topSecretFetchFailed:)];
	[request startAsynchronous];
}

#pragma make -
#pragma make request delegate
- (void)topSecretFetchFailed:(ASIHTTPRequest *)theRequest
{
    
	NSLog(@"error");
}

- (void)topSecretFetchComplete:(ASIHTTPRequest *)theRequest
{
    
	NSLog(@"complete");
}

- (void) requestRUL:(id)param
{
	NSURL *url = [NSURL URLWithString:@"http://allseeing-i.com/"];
	ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	//Customise our user agent, for no real reason
	[request addRequestHeader:@"User-Agent" value:@"ASIHTTPRequest"];
	// Start the request
	[request startSynchronous];
	//[request start];
	NSError *error = [request error];
    
	if (!error) {
		NSString *response = [request responseString];
		NSLog(@"response string===%@",response);
		NSLog(@"response headers==%@",[request responseHeaders]);
	}
}

-(IBAction)downLoad:(id)param{
	//ASINetworkQueue *networkQueue;
	if (!networkQueue) {
		networkQueue = [[ASINetworkQueue alloc] init];	
	}
	assert(networkQueue!=nil);
	//failed = NO;
	[networkQueue reset];
	[networkQueue setDownloadProgressDelegate:nil];
	[networkQueue setRequestDidFinishSelector:@selector(imageFetchComplete:)];
	[networkQueue setRequestDidFailSelector:@selector(imageFetchFailed:)];
	[networkQueue setShowAccurateProgress:YES];
	[networkQueue setDelegate:self];
	
	ASIHTTPRequest *request;
	request = [ASIHTTPRequest requestWithURL:[NSURL URLWithString:@"http://allseeing-i.com/ASIHTTPRequest/tests/images/small-image.jpg"]];
	[request setDownloadDestinationPath:[[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"1.png"]];
	[request setDownloadProgressDelegate:nil];
	[networkQueue addOperation:request];
	
	request = [[[ASIHTTPRequest alloc] initWithURL:[NSURL URLWithString:@"http://allseeing-i.com/ASIHTTPRequest/tests/images/medium-image.jpg"]] autorelease];
	[request setDownloadDestinationPath:[[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"2.png"]];
	[request setDownloadProgressDelegate:nil];
	[networkQueue addOperation:request];
	
	request = [[[ASIHTTPRequest alloc] initWithURL:[NSURL URLWithString:@"http://allseeing-i.com/ASIHTTPRequest/tests/images/large-image.jpg"]] autorelease];
	[request setDownloadDestinationPath:[[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"3.png"]];
	[request setDownloadProgressDelegate:nil];
	[networkQueue addOperation:request];
	
	[networkQueue go];
	
}

- (void)imageFetchComplete:(ASIHTTPRequest *)request
{
}

- (void)imageFetchFailed:(ASIHTTPRequest *)request
{
}

-(void)upLoad:(id)param{
	
	[requestUp cancel];
	requestUp=[ASIFormDataRequest requestWithURL:[NSURL URLWithString:@"http://10.0.0.116:8595/photos/photoAdd.aspx"]];
	[requestUp setPostValue:@"test" forKey:@"value1"];
	[requestUp setPostValue:@"test" forKey:@"value2"];
	[requestUp setPostValue:@"test" forKey:@"value3"];
	[requestUp setTimeOutSeconds:20];
	[requestUp setUploadProgressDelegate:nil];
	[requestUp setDelegate:self];
	[requestUp setDidFailSelector:@selector(uploadFailed:)];
	[requestUp setDidFinishSelector:@selector(uploadFinished:)];
	
	//Create a 256KB file
	NSData *data = [[[NSMutableData alloc] initWithLength:256*1024] autorelease];
	//NSString *path = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"file"];
	NSString *path=@"/myData";
	[data writeToFile:path atomically:NO];
	
	//Add the file 8 times to the request, for a total request size around 2MB
	int i;
	for (i=0; i<8; i++) {
		[requestUp setFile:path forKey:[NSString stringWithFormat:@"file-%hi",i]];
	}
	
	[requestUp startAsynchronous];
	
	NSLog(@"Uploading data...");
}
- (void)uploadFailed:(ASIHTTPRequest *)theRequest
{
	NSLog(@"uploadFailed");
}

- (void)uploadFinished:(ASIHTTPRequest *)theRequest
{
	NSLog(@"uploadFinished");
}


- (InterfacewsHttpResponse *) getWebServiceResponseInfo
{
    return httpResponse_;
}

#pragma arguments -
#pragma arguments connectionDelegate
-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{
    
}

-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data{
    [responseData_ appendData:data];
}

-(void)connectionDidFinishLoading:(NSURLConnection *)connection{
    httpResponse_.receiveData = [NSData dataWithData:responseData_];
    self.urlConnect = nil;
}

-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error{
    httpResponse_.error = error;
    self.urlConnect = nil;
}

@end

