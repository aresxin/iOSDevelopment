//
//  InterfaceWebService.h
//  EasyLife
//
//  Created by neusoft  on 11-11-28.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//  
//

#import <Foundation/Foundation.h>
#import "ASIHttpHeaders.h"
typedef enum{
    synchConnect = 0,
    AsynchConnect = 1,
}connectMode;

#pragma mark WebService Binding Response
@interface InterfacewsHttpResponse : NSObject {
	//NSArray *headers;
	//NSArray *bodyParts;
	NSError *error_;
    NSData  *receiveData_;
}
//@property (nonatomic, retain) NSArray *headers;
//@property (nonatomic, retain) NSArray *bodyParts;
@property (nonatomic, retain) NSData  *receiveData;
@property (nonatomic, retain) NSError *error;
@end

@interface InterfaceWebService : NSObject {
    NSURLConnection             *urlConnect_;
    NSMutableData               *responseData_;
    InterfacewsHttpResponse     *httpResponse_;
    
    ASINetworkQueue             *networkQueue;
	ASIFormDataRequest          *requestUp;
}
@property (nonatomic, retain) NSURLConnection            *urlConnect;
@property (nonatomic, retain) InterfacewsHttpResponse    *httpResponse;

- (void) sendHTTPCallUsingRequest:(id)param withConnectMode:(connectMode)connectMode;
- (void) sendhttpSynchCallUsingRequest:(id)param;
- (InterfacewsHttpResponse *) getWebServiceResponseInfo;
@end


