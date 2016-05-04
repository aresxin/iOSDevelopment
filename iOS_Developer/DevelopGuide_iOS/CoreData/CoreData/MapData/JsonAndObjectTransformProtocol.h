//
//  JsonAndObjectTransformProtocol.h
//  CRMSalesConsultant
//
//  Created by Mars on 13-1-1.
//  Copyright (c) 2013年 Xin. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol JsonAndObjectTransformProtocol <NSObject>
@optional
+ (id)getObjectFromJson:(NSDictionary*)json;

@required
- (NSDictionary*)getJsonFromObject;
@end
