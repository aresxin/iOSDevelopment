//
//  SettingsMode.h
//  DWViewerPrint
//
//  Created by neusoft  on 12-1-11.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    UIPrintDefault,
    UIPrintPaperFirst,
    UIprintDocumentFirst,
    UIPrintScale,
    UIprintScaleIn,
} UIPrintSetttings;

typedef enum {
    PrintAllPage,
    PrintCurrentPage,
    PrintRangePage,
}UIPrintRange;

@interface SettingsMode : NSObject {
    UIPrintInfoOrientation     orientationInfo_;
    UIEdgeInsets               contentInsets_;
    CGSize                     paperSize_;
    UIPrintInfoOutputType      outPutType_;
    UIPrintSetttings           printSetting_;
    UIPrintInfoDuplex          duplerInfo_;
    UIPrintRange               printRange_;
    BOOL                       isPrintPdf_;
    int                        dpi_;
}

@property (nonatomic, assign) UIPrintInfoOrientation orientationInfo;
@property (nonatomic, assign) UIEdgeInsets           contentInsets;
@property (nonatomic, assign) CGSize                 paperSize;
@property (nonatomic, assign) UIPrintInfoOutputType  outPutType;
@property (nonatomic, assign) UIPrintSetttings       printSetting;
@property (nonatomic, assign) UIPrintInfoDuplex      duplerInfo;
@property (nonatomic, assign) UIPrintRange           printRange;
@property (nonatomic, assign) BOOL     isPrintPdf;
@property (nonatomic, assign) int      dpi;
+ (SettingsMode *) shareSettings;
@end
