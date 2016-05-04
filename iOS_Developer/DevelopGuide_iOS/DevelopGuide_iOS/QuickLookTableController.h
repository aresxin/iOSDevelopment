//
//  QuickLookTableController.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuickLook/QuickLook.h>

@interface QuickLookTableController : UITableViewController <QLPreviewControllerDelegate,QLPreviewControllerDataSource>{
    NSMutableArray *files;
    NSMutableArray *documentURLs;
}
- (NSString *)formattedFileSize:(unsigned long long)size;
@end
