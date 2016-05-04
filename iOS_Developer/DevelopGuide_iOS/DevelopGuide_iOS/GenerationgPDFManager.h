//
//  GenerationgPDFManager.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GenerationgPDFManager : NSObject
- (void) GenerationgPDFWithFilePath:(NSString *)filePath 
                           withRect:(CGRect)rect 
                     withPDFInfoDic:(NSDictionary *)pdfInfo;
+ (GenerationgPDFManager *) shareGenerationgPDFManager;
@end
