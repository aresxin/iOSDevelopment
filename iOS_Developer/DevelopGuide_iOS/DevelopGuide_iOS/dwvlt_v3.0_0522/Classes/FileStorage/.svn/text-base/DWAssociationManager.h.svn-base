//
//  DWAssociationManager.h
//  DWViewer
//
//  Created by tongtiexin on 11-8-12.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface DWAssociationManager : NSObject {

}


+ (BOOL) readDataFromPasteBoard:(NSString *)directoryPath 
                           file:(NSString *)filename;

+ (BOOL) writeDataToPasteBoard:(NSString *)path;

// tongtx 20120206 start
// MTA連動機能の対応
+ (NSData *) readFileDataFromPasteBoard:(NSString *)name 
                                   type:(NSString *)type;

+ (BOOL) writeFileDataToPasteBoard:(NSString *)name 
                              type:(NSString *)type 
                          filepath:(NSString *)path;
// tongtx 20120206 end
@end
