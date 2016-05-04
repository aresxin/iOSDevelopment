//
//  LLSNetworkClient.h
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"

typedef NS_ENUM(NSInteger, LLSHttpRequestType) {
    kHttpRequestGet,
    kHttpRequestPost,
    kHttpRequestDelete,
    kHttpRequestPut,
};


@interface LLSNetworkClient : NSObject

+ (LLSNetworkClient *)sharedInstance;

- (void)addHeadField:(NSDictionary *)headFiled;

- (void)setTimeOut:(NSTimeInterval) timeOut;

- (void)setBackgrounTimeOut:(NSTimeInterval)timeOut;

- (NSURLSessionTask *) requestWithPath:(NSString *)url
                                method:(NSInteger)method
                            parameters:(id)parameters
                   requestInBackground:(BOOL)inBackground
                               success:(void (^)(NSURLSessionDataTask *task, id responseObject))success
                               failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
@end
