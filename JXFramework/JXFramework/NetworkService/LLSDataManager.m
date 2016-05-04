//
//  LLSDataManager.m
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "LLSDataManager.h"
#import "LLSModel.h"



#define ERROR_DOMAIN @"LocationShare"

NSString *const resultKey = @"result";
NSString *const result    = @"ok";

@interface LLSDataManager ()
@end

@implementation LLSDataManager
@synthesize accessToken = _accessToken;
@synthesize authKey = _authKey;

+ (LLSDataManager *)sharedInstance {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.baseURL = nil;
    }
    return self;
}

#pragma mark - authkey/token
- (void) setAuthKey:(NSString *)authKey
{
    _authKey = authKey;
    if ([_authKey length]) {
    }
    
}

- (NSString *)authKey
{
    if ([_authKey length]) {
        return _authKey;
    }
    
    return _authKey;
}

- (void) setAccessToken:(NSString *)accessToken
{
    _accessToken = accessToken;
    if ([_accessToken length]) {
    }
}

- (NSString *)accessToken
{
    if ([_accessToken length]) {
        return _accessToken;
    }
    
    return _accessToken;
}

#pragma mark - server api
- (NSURLSessionTask *) requestPostListDataWithUri:(NSString *)aUri
                                         andParam:(NSArray *)param
                               andCompletionBlock:(compeleteBlock)compeleteBlock
{
    if (![aUri length]) {
        //
        NSError *error = [NSError errorWithDomain:ERROR_DOMAIN code:0 userInfo:nil];
        if (compeleteBlock != nil) {
            compeleteBlock(nil,  error);
        }
        return nil;
    }
    
    // add head field
    [self addHeadFieldWithUri:aUri];
    
    // create base url
    NSString *requestURL = [NSString stringWithFormat:@"%@%@",self.baseURL,aUri];
    
    BOOL isBackGround = NO;
    if ([UIApplication sharedApplication].applicationState == UIApplicationStateBackground) {
        isBackGround = YES;
    }
    
    NSURLSessionTask *task = [[LLSNetworkClient sharedInstance] requestWithPath:requestURL
                                                                         method:kHttpRequestPost
                                                                     parameters:param
                                                            requestInBackground:isBackGround
                                                                        success:^(NSURLSessionDataTask *task, id responseObject) {
                                                                            [self handleResponse:responseObject
                                                                                            task:task
                                                                              andCompletionBlock:compeleteBlock];
                                                                        } failure:^(NSURLSessionDataTask *task, NSError *error) {
                                                                            [self handleError:error task:task andCompletionBlock:compeleteBlock];
                                                                        }];
    
    return task;


}

- (NSURLSessionTask *) requestDataWithUri:(NSString *)aUri
                                andMethod:(LLSHttpRequestType)method
                                 andParam:(NSDictionary *)param
                       andCompletionBlock:(compeleteBlock)compeleteBlock
{
    if (![aUri length]) {
        //
        NSError *error = [NSError errorWithDomain:ERROR_DOMAIN code:0 userInfo:nil];
        if (compeleteBlock != nil) {
            compeleteBlock(nil,  error);
        }
        return nil;
    }
    
    // add head field
    [self addHeadFieldWithUri:aUri];
    
    // create base url
    NSString *requestURL = [NSString stringWithFormat:@"%@%@",self.baseURL,aUri];
    
    BOOL isBackGround = NO;
    if ([UIApplication sharedApplication].applicationState == UIApplicationStateBackground) {
        isBackGround = YES;
    }
    
    
    NSURLSessionTask *task = [[LLSNetworkClient sharedInstance] requestWithPath:requestURL
                                                                         method:method
                                                                     parameters:param
                                                            requestInBackground:isBackGround
                                                                        success:^(NSURLSessionDataTask *task, id responseObject) {
                                                                            [self handleResponse:responseObject
                                                                                            task:task
                                                                              andCompletionBlock:compeleteBlock];
                                                                        } failure:^(NSURLSessionDataTask *task, NSError *error) {
                                                                            [self handleError:error task:task andCompletionBlock:compeleteBlock];
                                                                        }];
    
    return task;

}

- (NSDictionary *)getAuthHeader
{
    if (![self.accessToken length] || ![self.authKey length]) {
        return nil;
    }
    
    NSMutableDictionary *headDic = [NSMutableDictionary dictionary];
    [headDic setObject:self.accessToken forKey:@"Access-Token"];
    [headDic setObject:self.authKey forKey:@"Auth-Key"];
    return headDic;
}

- (void) addHeadFieldWithUri:(NSString *)uri
{
    NSMutableDictionary *headDic = [NSMutableDictionary dictionary];
    if ([self.accessToken length] > 0) {
        [headDic setObject:self.accessToken forKey:@"Access-Token"];
    }
   
    
    
    
    [headDic setObject:@"application/json" forKey:@"Content-Type"];
        
    [[LLSNetworkClient sharedInstance] addHeadField:headDic];
}

- (NSURLSessionTask *) requestDataWithUri:(NSString *)aUri
                                andMethod:(LLSHttpRequestType)method
                                 andParam:(id)param
                                 mapModel:(NSString *)modelType
                       andCompletionBlock:(compeleteBlock)compeleteBlock;
{
    NSURLSessionTask *task = nil;

    NSDictionary *dicParam = nil;
    NSString     *requestURL = aUri;
    
    if (method == kHttpRequestPost && param) {
        dicParam = [self constructingBody:param arrayKey:nil];
    } else if (method == kHttpRequestGet) {
        if (param && [param isKindOfClass:[NSDictionary class]]) {
            requestURL = [self getUrlStringWithPath:aUri parameters:param];
        } else {
            requestURL = aUri;
        }
    }
    
    task = [self requestDataWithUri:requestURL
                          andMethod:method
                           andParam:dicParam
                 andCompletionBlock:^(id data, NSError *error) {
                     if (error != nil) {
                         compeleteBlock (nil,error);
                     } else {
                         if ([modelType length] > 0) {
                             // change json to model
                             if ([data isKindOfClass:[NSArray class]]) {
                                 NSMutableArray *resultArrary = [NSMutableArray array];
                                 for (NSDictionary *dic in (NSArray *)data)
                                 {
                                     Class model = NSClassFromString(modelType);
                                     if ([model isSubclassOfClass:[LLSModel class]]) {
                                         LLSModel *lModel = [model  objectFromJsonDictionary:dic];
                                         [resultArrary addObject:lModel];
                                     }
                                 }
                                 
                                 compeleteBlock(resultArrary,nil);
                             } else if ([data isKindOfClass:[NSDictionary class]]) {
                                 Class model = NSClassFromString(modelType);
                                 if ([model isSubclassOfClass:[LLSModel class]]) {
                                     LLSModel *lModel = [model  objectFromJsonDictionary:data];
                                     compeleteBlock(lModel ,nil);
                                 }
                             }
                         } else {
                             // no change json to model
                             compeleteBlock(data,nil);
                         }
                         
                     }
                 }];
    return task;
    
}

- (NSURLSessionTask *) requestPostDataWithUri:(NSString *)aUri
                        constructingBodyBlock:(constructingBodyBlock)constructingBlock
                                     mapModel:(NSString *)modelType
                           andCompletionBlock:(compeleteBlock)compeleteBlock
{
    NSDictionary *param = nil;
    if (constructingBlock) {
        param = constructingBlock();
    }
    
    if (!param) {
        return nil;
    }
    
    NSURLSessionTask *task = nil;
    
    task =  [self requestDataWithUri:aUri
                           andMethod:kHttpRequestPost
                            andParam:param
                            mapModel:modelType
                  andCompletionBlock:compeleteBlock];
    
    return task;
}

- (NSURLSessionTask *) requestGetDataWithUri:(NSString *)aUri
                         constructingGetForm:(constructingGetForm)constructingForm
                                    mapModel:(NSString *)modelType
                          andCompletionBlock:(compeleteBlock)compeleteBlock;
{
    NSString *getURL = nil;

    NSString *formData = constructingForm();
    if ([formData length] > 0) {
        getURL = [NSString stringWithFormat:@"%@?%@",aUri,formData];
    } else {
        getURL = aUri;
    }
    
    NSURLSessionTask *task = nil;
    
    task =  [self requestDataWithUri:getURL
                           andMethod:kHttpRequestGet
                            andParam:nil
                            mapModel:modelType
                  andCompletionBlock:compeleteBlock];
    return task;
}


- (NSDictionary *) constructingBody:(id)param
                           arrayKey:(NSString *)arrayKey
{
    if (!param) {
        return nil;
    }
    
    NSDictionary *dic = nil;
    
    if ([param isKindOfClass:[NSDictionary class]]) {
        dic = [NSDictionary dictionaryWithDictionary:param];
    } else if ([param isKindOfClass:[LLSModel class]]) {
        dic = [param getObjDictionaryFromObj];
    } else if ([param isKindOfClass:[NSArray class]]) {
        NSMutableArray *array = [NSMutableArray array];
        for (LLSModel *model in param) {
            NSDictionary *modelDic = [model getObjDictionaryFromObj];
            [array addObject:modelDic];
        }
        dic = [NSDictionary dictionaryWithObject:array forKey:arrayKey];
    }
    
    return dic;
    
}

- (NSString *)getUrlStringWithPath:(NSString *)path
                        parameters:(NSDictionary *)parameters
{
    NSString* retString = path;
    
    if (!retString) {
        retString = @"";
    }
    
    if (parameters) {
        
        retString =[retString stringByAppendingString:@"?"];
        
        NSMutableArray *mutablePairs = [NSMutableArray array];
        for (id key in [parameters allKeys]) {
            NSString* str = [NSString stringWithFormat:@"%@=%@",key, [parameters objectForKey:key]];
            
            [mutablePairs addObject:str];
        }
        
        NSString* sendString = [mutablePairs componentsJoinedByString:@"&"];
        
        retString = [retString stringByAppendingString:sendString];
    }
    
    return retString;
}


- (void) handleResponse:(id)responseObject
                   task:(NSURLSessionDataTask *)task
     andCompletionBlock:(compeleteBlock)compeleteBlock;

{
    // statue 200
    NSHTTPURLResponse *response = (NSHTTPURLResponse *)task.response;
    if (response.statusCode == 200) {
        
        // set auth-key
        [self setResponsAuthKey:response];
        
        if ([responseObject objectForKey:resultKey] != nil
            && [[responseObject objectForKey:resultKey] isEqualToString:result]) {
            id responseData = [responseObject objectForKey:@"message"];
            compeleteBlock(responseData,nil);
        } else {
            NSError *error = [NSError errorWithDomain:@"server data error"
                                                 code:999 userInfo:nil];
            compeleteBlock(nil,error);
        }
    }
}

- (void)handleError:(NSError *)error
               task:(NSURLSessionDataTask *)task
 andCompletionBlock:(compeleteBlock)compeleteBlock
{
    
    compeleteBlock(nil,error);
}


- (void) setResponsAuthKey:(NSHTTPURLResponse *)respons
{
    NSDictionary *headers = [respons allHeaderFields];
    if (headers != nil && [headers objectForKey:@"Auth-Key"] != nil) {
        self.authKey = [headers objectForKey:@"Auth-Key"];
    }
}




@end
