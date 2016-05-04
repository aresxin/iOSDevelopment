//
//  ServiceManager.m
//  EasyLife
//
//  Created by neusoft  on 11-11-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "ServiceManager.h"
#import "InterfaceWebService.h"

static ServiceManager *_instance = nil;

@implementation ServiceManager

+ (ServiceManager *) shareServiceManager
{
    @synchronized([ServiceManager class])
	{
		if (_instance == nil)
			_instance = [[self alloc] init];
		
		return _instance;
	}
	
	return nil;

}

- (id) init
{
    self = [super init];
    if (self) {
        
    }
    return  self;
}

- (id)CallWebService:(id)param  error:(NSError**)error
{
    InterfaceWebService *appSvc = [[[InterfaceWebService alloc] init] autorelease];
    [appSvc sendhttpSynchCallUsingRequest:param];
    
    InterfacewsHttpResponse *response_ = [appSvc  getWebServiceResponseInfo];
    
    if (response_.receiveData != nil) {
        return  [[[NSString alloc] initWithData:response_.receiveData encoding:NSUTF16LittleEndianStringEncoding] autorelease];
    }
    
    if (response_.error != nil) {
        *error = response_.error;
    }
    return nil;
}

#pragma mark -
#pragma mark 接口
- (NSString*)getFlightList:(NSArray*)param error:(NSError **)error
{
	return [self CallWebService:param 
						  error:error];
}

- (void) dealloc
{
    [super dealloc];
}

@end
