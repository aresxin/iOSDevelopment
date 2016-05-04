//
//  SettingsMode.m
//  DWViewerPrint
//
//  Created by neusoft  on 12-1-11.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//
/*
 * 单例模式的使用
 */
#import "SettingsMode.h"
#import "GuiConst.h"
#define SPACE_VALUE  4.6

@implementation SettingsMode
@synthesize orientationInfo = orientationInfo_;
@synthesize outPutType = outPutType_;
@synthesize paperSize = paperSize_;
@synthesize contentInsets = contentInsets_;
@synthesize printSetting = printSetting_;
@synthesize duplerInfo = duplerInfo_;
@synthesize printRange = printRange_;
@synthesize isPrintPdf = isPrintPdf_;
@synthesize dpi = dpi_;

// 获得静态指针
static SettingsMode  *settings_ = nil;

- (id) init
{
    self = [super init];
    if (self) {
        printSetting_ = UIPrintPaperFirst;
        outPutType_ = UIPrintInfoOutputGeneral;

        orientationInfo_ = -1;
        contentInsets_ = UIEdgeInsetsMake(SPACE_VALUE, SPACE_VALUE, 
                                          SPACE_VALUE, SPACE_VALUE);
        
        duplerInfo_ = UIPrintInfoDuplexNone;
        printRange_ = PrintAllPage;
        isPrintPdf_ = YES;
        
        dpi_ = 0;
        
    }
    return self;
}

+ (SettingsMode *) shareSettings
{
    //@synchronized线程保护
    @synchronized(self) {
        if (settings_ == nil) {
            settings_ = [[self alloc] init];
        }
    }
    return settings_;
}

- (void) dealloc
{
    [super dealloc];
}
@end
