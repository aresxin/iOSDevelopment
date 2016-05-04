//
//  JOSNParse.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface JOSNParse : NSObject {
    
}
+ (NSArray *) parseJOSNData:(NSData *)data withRootKey:(NSString *)key;
+ (NSString *) parseJOSN;
@end
