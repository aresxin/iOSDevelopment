//
//  JXAsyncImageView.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface JXAsyncImageView : UIImageView <NSURLConnectionDelegate,NSURLConnectionDataDelegate>{
    NSURLConnection   *_connection;
    NSMutableData     *_data;
    BOOL              _showLoading;
}
@property (nonatomic, retain) NSURLConnection *connection;
@property (nonatomic, retain) NSMutableData   *data;

- (id)initWithFrame:(CGRect)frame 
        loadingView:(BOOL)has;

- (void)loadImageFromURL:(NSURL*)url;
- (void) addActivityIndicator;
- (void) removeActivityIndicator;
@end
