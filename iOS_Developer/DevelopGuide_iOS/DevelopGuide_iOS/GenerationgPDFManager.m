//
//  GenerationgPDFManager.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GenerationgPDFManager.h"
#import "SEImage.h"

@implementation GenerationgPDFManager

static GenerationgPDFManager *GeneratPDFMgr_ = nil;

- (id) init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

+ (GenerationgPDFManager *) shareGenerationgPDFManager
{
    @synchronized(self) {
        if (GeneratPDFMgr_ == nil) {
            GeneratPDFMgr_ = [[self alloc] init];
        }
    }
    
    return GeneratPDFMgr_;
}

- (void) GenerationgPDFWithFilePath:(NSString *)filePath 
                           withRect:(CGRect)rect 
                     withPDFInfoDic:(NSDictionary *)pdfInfo
{
    // Create the PDF context using the default page size of rect.
    BOOL res = UIGraphicsBeginPDFContextToFile(filePath, rect, pdfInfo);
    if (res) {
        // create pdf page
        UIGraphicsBeginPDFPageWithInfo(rect, nil);
        CGContextRef ctx = UIGraphicsGetCurrentContext();
        NSString *imgPath = [[NSBundle mainBundle] pathForResource:@"super_1200" 
                                                       ofType:@"jpg"]; 
        UIImage *img = [UIImage imageWithContentsOfFile:imgPath];
        [SEImage drawImage:ctx Image:img.CGImage Rect:rect];
    }
    // end create pdf file
    UIGraphicsEndPDFContext();
}
@end
