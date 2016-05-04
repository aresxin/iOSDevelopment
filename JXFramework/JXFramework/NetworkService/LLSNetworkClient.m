//
//  LLSNetworkClient.m
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "LLSNetworkClient.h"

NSString *const backgrounSessionIdentifier = @"request when app in background";


NSTimeInterval const timeOut = 20.0f;


@interface LLSNetworkClient()
@property (nonatomic,strong) AFHTTPSessionManager *manager;
@property (nonatomic,strong) AFHTTPSessionManager *backgroundmanager;
@property (nonatomic,strong) NSMutableDictionary  *requestsRecord;
@end

@implementation LLSNetworkClient
+ (LLSNetworkClient *)sharedInstance {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (id)init{
    if (self = [super init]){
        //  1.0 create manager use in front
        self.manager = [AFHTTPSessionManager manager];
        self.manager.requestSerializer  = [AFJSONRequestSerializer serializer];
        [self.manager.requestSerializer setValue:@"gzip" forHTTPHeaderField:@"Content-Encoding"];        
        [self.manager.requestSerializer setTimeoutInterval:timeOut];
        self.manager.responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"application/json", @"text/json",@"plain/json",@"text/plain",nil];
        self.manager.securityPolicy = [AFSecurityPolicy policyWithPinningMode:AFSSLPinningModeNone];
        
        self.manager.securityPolicy.allowInvalidCertificates = NO;
        self.manager.securityPolicy.validatesDomainName = YES;
        self.manager.securityPolicy.validatesCertificateChain = YES;
        
        // 2.0 create manager use in backgroun
//        if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"8.0")) {
//            NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration backgroundSessionConfigurationWithIdentifier:backgrounSessionIdentifier];
//            self.backgroundmanager = [[AFHTTPSessionManager alloc] initWithSessionConfiguration:configuration];
//        } else {
//            self.backgroundmanager = [AFHTTPSessionManager manager];
//        }
        self.backgroundmanager = [AFHTTPSessionManager manager];
        
        self.backgroundmanager.requestSerializer  =  [AFJSONRequestSerializer serializer];
        [self.backgroundmanager.requestSerializer setValue:@"gzip" forHTTPHeaderField:@"Content-Encoding"];
        [self.backgroundmanager.requestSerializer setTimeoutInterval:timeOut];
        self.backgroundmanager.responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"application/json", @"text/json",@"plain/json",@"text/plain",nil];
        self.backgroundmanager.securityPolicy = [AFSecurityPolicy policyWithPinningMode:AFSSLPinningModeNone];
        
        
        self.backgroundmanager.securityPolicy.allowInvalidCertificates = NO;
        self.backgroundmanager.securityPolicy.validatesDomainName = YES;
        self.backgroundmanager.securityPolicy.validatesCertificateChain = YES;
        
        // 3.0 record all request
        _requestsRecord = [NSMutableDictionary dictionary];
    }
    return self;
}

- (void)setTimeOut:(NSTimeInterval)timeOut
{
    _manager.requestSerializer.timeoutInterval = timeOut;
}

- (void)setBackgrounTimeOut:(NSTimeInterval)timeOut
{
    _backgroundmanager.requestSerializer.timeoutInterval = timeOut;
}

- (void) addHeadField:(NSDictionary *)headFiled
{
    if (headFiled == nil) {
        return;
    }
    
    if (_manager.requestSerializer == nil) {
        _manager.requestSerializer = [AFJSONRequestSerializer serializer];
    }
    
    for (NSString *key in [headFiled allKeys]) {
        NSString *value = [headFiled objectForKey:key];
        [_manager.requestSerializer setValue:value forHTTPHeaderField:key];
    }
    
    
    if (_backgroundmanager.requestSerializer == nil) {
        _backgroundmanager.requestSerializer = [AFJSONRequestSerializer serializer];
    }
    
    for (NSString *key in [headFiled allKeys]) {
        NSString *value = [headFiled objectForKey:key];
        [_backgroundmanager.requestSerializer setValue:value forHTTPHeaderField:key];
    }
}


- (NSURLSessionTask *) requestWithPath:(NSString *)url
                                method:(NSInteger)method
                            parameters:(id)parameters
                   requestInBackground:(BOOL)inBackground
                               success:(void (^)(NSURLSessionDataTask *task, id responseObject))success
                               failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure
{
    

    
    AFHTTPSessionManager *mgr = [self getSessionManager:inBackground];
    NSURLSessionTask     *task = nil;
    
    switch (method) {
        case kHttpRequestGet:
            task = [mgr GET:url parameters:parameters success:success failure:failure];
            break;
            
        case kHttpRequestPost:
            task = [mgr POST:url parameters:parameters success:success failure:failure];
            break;
            
        default:
            break;
    }
    
    // add task
    //NSString *taskid = [NSString stringWithFormat:@"%ld",(unsigned long)task.taskIdentifier];
    //[_requestsRecord setObject:task forKey:taskid];
    
    return task;
    
}


- (AFHTTPSessionManager *) getSessionManager:(BOOL)inBackground
{
    if (inBackground) {
        return self.backgroundmanager;
    }
    
    return self.manager;
}

@end
