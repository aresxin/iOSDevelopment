//
//  NetworkAPI.h
//  Salary
//
//  Created by yangjinxin on 13-5-14.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import <Foundation/Foundation.h>
@protocol NetworkAPIDelegate
@optional
//非队列异步请求
-(void)finishSuccessRequest:(NSString*)request
                requestUser:(id)requestObj;
-(void)finishFailRequest:(NSError*)error
             requestUser:(id)requestObj;
@end

@interface NetworkAPI : NSObject {
    id<NetworkAPIDelegate> delegate;
}
@property(nonatomic,assign) id<NetworkAPIDelegate> delegate;
#pragma mark -
#pragma mark NSURLConnection 同步请求
+ (NSString *) fetchDataWithUrl:(NSString*) url
                 withParameters:(NSDictionary*)params
                          error:(NSError**)error;
#pragma mark -
#pragma mark ASIRequest 在子线程中发同步请求 block
+ (void) syncServiceRequestUrlOnThread:(NSString*)url
                        withParameters:(NSDictionary*)params
                     CompletionHandler:(void (^)(NSString *result, NSError *error))block;

#pragma mark -
#pragma mark ASIRequest 同步请求
+ (NSString*) syncServiceRequestUrl:(NSString*)url
                    withParameters:(NSDictionary*)params
                              error:(NSError**)error;
#pragma mark -
#pragma mark ASIRequest 异步请求
- (void) asynServiceRequestUrl:(NSString*)url
                withParameters:(NSDictionary*)params
                      callBack:(id)callObject
                   callBackSel:(NSString *)sel;
@end
