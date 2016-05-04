//
//  ALAssetsLibrary+AddAlbum.h
//  SnapMovie
//
//  Created by yangjinxin on 15/3/3.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <AssetsLibrary/AssetsLibrary.h>
#import <Photos/Photos.h>

typedef void(^SaveVideoCompletion)(NSError* error);

@interface ALAssetsLibrary (AddAlbum)

-(void)saveVideo:(NSURL*)videoURL
         toAlbum:(NSString*)albumName
withCompletionBlock:(SaveVideoCompletion)completionBlock;

-(void)addAssetURL:(NSURL*)assetURL
           toAlbum:(NSString*)albumName
withCompletionBlock:(SaveVideoCompletion)completionBlock;

@end
