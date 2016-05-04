//
//  EveryTimeZone.h
//  timeZoneViewer
//
//  Created by wang.pp on 11-12-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface EveryTimeZone : NSObject {
    
   
    
}


+(NSArray*) getAllTimeWithZone;
+(NSString*) getTimeWithSpecialZone:(NSString*)zoneName;

@end
