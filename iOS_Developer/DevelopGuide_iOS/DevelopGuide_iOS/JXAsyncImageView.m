//
//  JXAsyncImageView.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "JXAsyncImageView.h"

#define ActivityIndicatorView_TAG   1000

@implementation JXAsyncImageView
@synthesize connection = _connection;
@synthesize data = _data;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame loadingView:(BOOL)has
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        _showLoading = has;
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

- (void)loadImageFromURL:(NSURL*)url
{
    if (nil == url) 
    {
        return;
    }
    
    NSURLRequest* request = [NSURLRequest requestWithURL:url  
                                             cachePolicy:NSURLRequestUseProtocolCachePolicy  
                                         timeoutInterval:5.0];
    // prepar data
    self.data = [NSMutableData data];
    self.connection = [[[NSURLConnection alloc] initWithRequest:request 
                                                       delegate:self] autorelease];
    
    if (_showLoading) 
    {
        [self addActivityIndicator];
    }
}

- (void) addActivityIndicator
{
    UIActivityIndicatorView *loadView = [[UIActivityIndicatorView alloc] 
                                         initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    loadView.frame = CGRectMake(0, 0, self.frame.size.width/2, self.frame.size.height/2);
    loadView.center = self.center;
    loadView.hidesWhenStopped = YES;
    loadView.tag = ActivityIndicatorView_TAG;
    
    [self addSubview:loadView];

    [loadView performSelectorInBackground:@selector(startAnimating) withObject:nil];
    //[loadView startAnimating];
    [loadView release];
}

- (void) removeActivityIndicator
{
    UIActivityIndicatorView *loadView = (UIActivityIndicatorView *)[self 
                                                                    viewWithTag:ActivityIndicatorView_TAG];
    if (loadView != nil) 
    {
        [loadView stopAnimating];
        [loadView removeFromSuperview];
    }
}

#pragma mark - 
#pragma mare NSURLConnectionDataDelegate
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [_data appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    UIImage *image = [UIImage imageWithData:_data];
    if (image != nil) 
    {
        if (_showLoading) 
        {
            [self removeActivityIndicator];
        }
        
        [self setImage:image];
        [self performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil 
                            waitUntilDone:NO];
        //[self setNeedsDisplay];
    }
    
    self.data = nil;
    self.connection = nil;
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    self.connection = nil;
    self.data = nil;
    self.image = nil;
}

- (void) dealloc
{
    [_connection release];
    [_data release];
    [super dealloc];
}
@end
