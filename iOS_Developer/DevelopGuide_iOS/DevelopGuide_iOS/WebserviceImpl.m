//
//  WebserviceImpl.m
//  EasyLife
//
//  Created by neusoft  on 11-11-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "WebserviceImpl.h"
#import "ServiceManager.h"

@implementation WebserviceImpl

- (id) init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

- (id) getDataWit:(id)param errMsg:(NSError **)error
{
    ServiceManager *svcMgr = [ServiceManager shareServiceManager];
    id data = [svcMgr getFlightList:param error:nil];
    // 数据解析
    
    return data;
}

@end
