//
//  LLSDataManager.h
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLSNetworkClient.h"

typedef void (^compeleteBlock) (id data, NSError *error);

typedef NSDictionary* (^constructingBodyBlock) ();

typedef NSString* (^constructingGetForm) ();

@interface LLSDataManager : NSObject

+ (LLSDataManager *)sharedInstance;

@property (nonatomic, strong) NSString *baseURL;

@property (nonatomic, strong) NSString *accessToken;

@property (nonatomic, strong) NSString *authKey;


/*
 * request data post array
 */
- (NSURLSessionTask *) requestPostListDataWithUri:(NSString *)aUri
                                         andParam:(NSArray *)param
                               andCompletionBlock:(compeleteBlock)compeleteBlock;

/*
 * request data block return dictionary
 */
- (NSURLSessionTask *) requestDataWithUri:(NSString *)aUri
                                andMethod:(LLSHttpRequestType)method
                                 andParam:(NSDictionary *)param
                       andCompletionBlock:(compeleteBlock)compeleteBlock;
/*
 * request data block return one model or array
 * param is model or array
 */
- (NSURLSessionTask *) requestDataWithUri:(NSString *)aUri
                                andMethod:(LLSHttpRequestType)method
                                 andParam:(id)param
                                 mapModel:(NSString *)modelType
                       andCompletionBlock:(compeleteBlock)compeleteBlock;


/*
 * post request block constructing post body
 * compeleteBlock return NSDictionary
 */
- (NSURLSessionTask *) requestPostDataWithUri:(NSString *)aUri
                        constructingBodyBlock:(constructingBodyBlock)constructingBlock
                                     mapModel:(NSString *)modelType
                           andCompletionBlock:(compeleteBlock)compeleteBlock;


/*
 * get request block constructing get form-data
 * compeleteBlock return NSDictionary
 */
- (NSURLSessionTask *) requestGetDataWithUri:(NSString *)aUri
                         constructingGetForm:(constructingGetForm)constructingForm
                                    mapModel:(NSString *)modelType
                          andCompletionBlock:(compeleteBlock)compeleteBlock;


- (NSString *)getUrlStringWithPath:(NSString *)path
                        parameters:(NSDictionary *)parameters;

- (NSDictionary *)getAuthHeader;
@end
