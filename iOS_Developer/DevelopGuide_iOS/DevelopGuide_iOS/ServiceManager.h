//
//  ServiceManager.h
//  EasyLife
//
//  Created by neusoft  on 11-11-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface ServiceManager : NSObject {
    
}
+ (ServiceManager *) shareServiceManager;
- (NSString*)CallWebService:(id)param  error:(NSError**)error;
- (NSString*)getFlightList:(NSArray*)param error:(NSError **)error;
@end
