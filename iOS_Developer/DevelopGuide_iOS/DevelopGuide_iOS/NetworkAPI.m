//
//  NetworkAPI.m
//  Salary
//
//  Created by yangjinxin on 13-5-14.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "NetworkAPI.h"
#import "JSONKit.h"
#import "ASIHttpHeaders.h"

#define CALL_BACK_OBJECT @"CallBackSel"
#define CALL_BACK_SEL    @"CallBackObject"
#define REQUEST_URL      @"RequestURL"
@implementation NetworkAPI
@synthesize delegate;

static NetworkAPI* instance;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

+(NetworkAPI*)sharedInstance{
    if (instance == nil) {
        instance = [[NetworkAPI alloc]init];
    }
    return instance;
}


#pragma mark -
#pragma mark NSURLConnection 同步请求
+ (NSString *) fetchDataWithUrl:(NSString*) url
              withParameters:(NSDictionary*)params
                       error:(NSError**)error
{
    NSURL *nsUrl = [NSURL URLWithString:url];
    NSMutableURLRequest *request = nil;
    request = [NSMutableURLRequest requestWithURL:nsUrl];
    [request setCachePolicy:NSURLRequestUseProtocolCachePolicy];
    [request setHTTPMethod:@"POST"];
    [request addValue:@"application/x-www-form-urlencoded; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
    NSData *postBody = [params JSONData];
    if (postBody == nil || [postBody length] == 0)
    {
        return nil;
    }
    [request setHTTPBody:postBody];
    
    NSError     *resError = nil;
    NSData      *responseData = nil;
    NSString    *result  = nil;
    
    responseData = [NSURLConnection sendSynchronousRequest:request
                                         returningResponse:nil
                                                    error:&resError];
    
    if (resError == nil)
    {
        result = [[[NSString alloc] initWithData:responseData
                                             encoding:NSUTF8StringEncoding]autorelease];
    }
    else
    {
        if (error != nil)
        {
            *error = [resError copy];
        }
    }
    
    return result;
}


#pragma mark -
#pragma mark ASIRequest 在子线程中发同步请求 block
+ (void) syncServiceRequestUrlOnThread:(NSString*)url
                        withParameters:(NSDictionary*)params
                     CompletionHandler:(void (^)(NSString *result, NSError *error))block
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        NSError *error = nil;
        NSString *res = [NetworkAPI syncServiceRequestUrl:url
                                           withParameters:params
                                                    error:&error];
        dispatch_async(dispatch_get_main_queue(), ^{
            // 主线程执行的方法
            block(res,error);
        });
    });
}


#pragma mark -
#pragma mark ASIRequest 同步请求
+ (NSString*) syncServiceRequestUrl:(NSString*)url
                     withParameters:(NSDictionary*)params
                              error:(NSError**)error;
{
    NSURL *requestUrl = [NSURL URLWithString:url];
    ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:requestUrl];
    [request setRequestMethod:@"POST"];
    [request addRequestHeader:@"Content-Type" value:@"application/x-www-form-urlencoded; charset=utf-8"];
    NSData *postBody = [params JSONData];
    if (postBody == nil || [postBody length] == 0)
    {
        return nil;
    }
    [request setPostBody:[NSMutableData dataWithData:postBody]];
    [request startSynchronous];
    
    
    NSError *resError = [request error];
    NSString *result = nil;
    if(resError == nil)
    {
        result = [request responseString];
        NSLog(@"response info %@", result);
    }
    else
    {
        if (error!=nil)
        {
            *error = [resError copy];
        }
    }
    
    return result;
}

#pragma mark -
#pragma mark ASIRequest 异步请求
- (void) asynServiceRequestUrl:(NSString*)url
                withParameters:(NSDictionary*)params
                      callBack:(id)callObject
                   callBackSel:(NSString *)sel
{
    
    NSURL *requestUrl = [NSURL URLWithString:url];
    ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:requestUrl];
    [request setRequestMethod:@"POST"];
    [request addRequestHeader:@"Content-Type"
                        value:@"application/x-www-form-urlencoded; charset=utf-8"];
    NSData *postBody = [params JSONData];
    if (postBody == nil || [postBody length] == 0)
    {
        return;
    }
    [request setPostBody:[NSMutableData dataWithData:postBody]];
    
    // set userinfo
    NSMutableDictionary *userInfoDic = [NSMutableDictionary dictionary];
    
    // 识别同一个对象发送的什么请求
    [userInfoDic setObject:url forKey:REQUEST_URL];
    if (callObject != nil)
    {
        // 识别哪一个对象发送的请求
        [userInfoDic setObject:callObject
                        forKey:CALL_BACK_OBJECT];
    }
    if (sel != nil && [sel length] > 0)
    {
        // 识别对象请求成功的执行的方法
        [userInfoDic setObject:sel
                        forKey:CALL_BACK_SEL];
        
    }
    [request setUserInfo:userInfoDic];
   
    [request setDidFailSelector:@selector(requestFinished:)];
    [request setDidFinishSelector:@selector(requestFailed:)];
    //异步请求
    [request startAsynchronous];
  
}


#pragma mark -
#pragma mark ASIHTTPRequest delegate Methods
- (void)requestFinished:(ASIHTTPRequest *)request
{
    NSString *result= [request responseString];
    
    
    // delegate
    [delegate finishSuccessRequest:result requestUser:request.userInfo];
    
    // call back action
    id callBackObj = [request.userInfo objectForKey:@"CallBackObject"];
    NSString *callBackSel = [request.userInfo objectForKey:@"CallBackSel"];
    if (callBackObj == nil || callBackSel == nil || [callBackSel length] == 0)
    {
        return;
    }
    
    SEL callBackFun = NSSelectorFromString(callBackSel);

    if (callBackFun == nil)
    {
        return;
    }
    
    [callBackObj performSelector:callBackFun
                      withObject:result];
    
    
}


- (void)requestFailed:(ASIHTTPRequest *)request
{
	NSError *error = [request error];
    // delegate
    [delegate finishFailRequest:error
                    requestUser:request.userInfo];
}

@end
