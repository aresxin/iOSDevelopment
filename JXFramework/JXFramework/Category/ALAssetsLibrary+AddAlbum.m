//
//  ALAssetsLibrary+AddAlbum.m
//  SnapMovie
//
//  Created by yangjinxin on 15/3/3.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "ALAssetsLibrary+AddAlbum.h"
#import "UtilMacro.h"

#define INVALID_URL_ERROR_DOMAIN @"Application Domain == url is vaild please check video url."
#define INVALID_URL_ERROR_CODE   1009

@implementation ALAssetsLibrary (AddAlbum)


-(void)saveVideo:(NSURL*)videoURL toAlbum:(NSString*)albumName withCompletionBlock:(SaveVideoCompletion)completionBlock
{
    if (!videoURL) {
        NSError *error = [NSError errorWithDomain:INVALID_URL_ERROR_DOMAIN code:INVALID_URL_ERROR_CODE userInfo:nil];
        if (completionBlock) {
            completionBlock(error);
        }
        
        return;
    }
    
    [self writeVideoAtPathToSavedPhotosAlbum:videoURL
                                completionBlock:^(NSURL *assetURL, NSError *error){
                                    if (error) {
                                        if (completionBlock) {
                                             completionBlock(error);
                                        }
                                        return;
                                    }
                                    
//                                    [self addAssetURL:assetURL
//                                              toAlbum:albumName
//                                  withCompletionBlock:completionBlock];
                                    
                                    [self addAssetURL:assetURL
                                              toAlbum:albumName
                                             videoURL:videoURL
                                  withCompletionBlock:completionBlock];

                                }];

}



- (void)addAssetURL:(NSURL *)assetURL
             toAlbum:(NSString *)albumName videoURL:(NSURL *)videoURL
withCompletionBlock:(SaveVideoCompletion)completionBlock
{
    __block BOOL albumWasFound = NO;

    [self enumerateGroupsWithTypes:ALAssetsGroupAlbum usingBlock:^(ALAssetsGroup *group, BOOL *stop) {
        if ([albumName compare:[group valueForProperty:ALAssetsGroupPropertyName]] == NSOrderedSame)
        {
            albumWasFound = YES;
            
            [self assetForURL: assetURL
                  resultBlock:^(ALAsset *asset) {
                      
                      //add photo to the target album
                      BOOL sucess = [group addAsset: asset];
                      if (sucess) {
                          //run the completion block
                          completionBlock(nil);
                      } else {
                          NSError *error = [NSError errorWithDomain:@"WriteDiskSpaceError"
                                                               code:ALAssetsLibraryWriteDiskSpaceError
                                                           userInfo:nil];
                          
                          completionBlock(error);
                      }
                      
                      
                  } failureBlock: completionBlock];

            
            *stop = YES;
            
        }
        
        // create group
        if (group == nil && albumWasFound == NO){
            
            __weak ALAssetsLibrary* weakSelf = self;
            if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"8.0")) {
                PHPhotoLibrary* photoLib = [PHPhotoLibrary sharedPhotoLibrary];
                
                if (photoLib)
                {
                    // ---------  iOS 8.0 dynamic runtime code  -----------
                    
                    __block PHAssetCollectionChangeRequest* collectionRequest;
                    [photoLib performChanges:^
                     {
                         PHFetchResult* fetchCollectionResult;
                         
                         fetchCollectionResult = [PHAssetCollection fetchAssetCollectionsWithLocalIdentifiers:@[albumName] options:nil];
                         
                         // Create a new album
                         if ( !fetchCollectionResult || fetchCollectionResult.count==0 )
                         {
                             
                             collectionRequest = [PHAssetCollectionChangeRequest creationRequestForAssetCollectionWithTitle:albumName];
                             
                         }
                         // Use existing album
                         else
                         {
                             PHAssetCollection* exisitingCollection = fetchCollectionResult.firstObject;
                             collectionRequest = [PHAssetCollectionChangeRequest changeRequestForAssetCollection:exisitingCollection];
                         }
                         
                         
                         PHAssetChangeRequest* createAssetRequest;
                         createAssetRequest = [PHAssetChangeRequest creationRequestForAssetFromVideoAtFileURL:videoURL];
                         
                         [collectionRequest addAssets:@[createAssetRequest.placeholderForCreatedAsset]];
                         
                     }
                           completionHandler:^(BOOL success, NSError *error)
                     {
                         if (success)
                         {
                             completionBlock(nil);
                         }
                         else {
                             
                             NSError *diskError = [NSError errorWithDomain:@"WriteDiskSpaceError"
                                                                  code:ALAssetsLibraryWriteDiskSpaceError
                                                              userInfo:nil];
                             
                             completionBlock(diskError);
                         }
                     }];
                    
                } 
                

            } else {
                
                [self addAssetsGroupAlbumWithName:albumName
                                      resultBlock:^(ALAssetsGroup *group) {
                                          
                                          //get the photo's instance
                                          [weakSelf assetForURL: assetURL
                                                    resultBlock:^(ALAsset *asset) {
                                                        
                                                        //add photo to the newly created album
                                                        BOOL sucess = [group addAsset: asset];
                                                        
                                                        //call the completion block
                                                        if (sucess) {
                                                            completionBlock(nil);
                                                        } else {
                                                            NSError *error = [NSError errorWithDomain:@"WriteDiskSpaceError"
                                                                                                 code:ALAssetsLibraryWriteDiskSpaceError
                                                                                             userInfo:nil];

                                                            completionBlock(error);
                                                        }
                                                        
                                                        
                                                    } failureBlock: completionBlock];
                                          
                                      } failureBlock: completionBlock];
            }
            
            
            
             *stop = YES;
       
        }

    } failureBlock:^(NSError *error) {
        completionBlock(error);
    }];
    
}


-(void)addAssetURL:(NSURL*)assetURL
           toAlbum:(NSString*)albumName
withCompletionBlock:(SaveVideoCompletion)completionBlock
{
    __block BOOL albumWasFound = NO;
    
    //search all photo albums in the library
    [self enumerateGroupsWithTypes:ALAssetsGroupAlbum
                        usingBlock:^(ALAssetsGroup *group, BOOL *stop) {
                            
                            //compare the names of the albums
                            if ([albumName compare: [group valueForProperty:ALAssetsGroupPropertyName]]==NSOrderedSame) {
                                
                                //target album is found
                                albumWasFound = YES;
                                
                                //get a hold of the photo's asset instance
                                [self assetForURL: assetURL
                                      resultBlock:^(ALAsset *asset) {
                                          
                                          //add photo to the target album
                                          BOOL res =  [group addAsset: asset];
                                          if (res) {
                                               completionBlock(nil);
                                          } else {
                                              NSError *error = [NSError errorWithDomain:@"space error"
                                                                                   code:ALAssetsLibraryWriteDiskSpaceError
                                                                               userInfo:nil];
                                              completionBlock(error);
                                          }
                                          //run the completion block
                                         
                                          
                                      } failureBlock:^(NSError *error) {
                                          
                                          completionBlock(error);
                                      }];
                                
                                //album was found, bail out of the method
                                return;
                            }
                            
                            if (group==nil && albumWasFound==NO) {
                                //photo albums are over, target album does not exist, thus create it
                                
                                __weak ALAssetsLibrary* weakSelf = self;
                                
                                //create new assets album
                                [self addAssetsGroupAlbumWithName:albumName
                                                      resultBlock:^(ALAssetsGroup *group) {
                                                          
                                                          //get the photo's instance
                                                          [weakSelf assetForURL: assetURL
                                                                    resultBlock:^(ALAsset *asset) {
                                                                        
                                                                        //add photo to the newly created album
                                                                        BOOL res = [group addAsset: asset];
                                                                        
                                                                        //call the completion block
                                                                        if (res) {
                                                                            completionBlock(nil);
                                                                        } else {
                                                                            NSError *error = [NSError errorWithDomain:@"space error"
                                                                                                                 code:ALAssetsLibraryWriteDiskSpaceError
                                                                                                             userInfo:nil];
                                                                            completionBlock(error);
                                                                        }
                                                                        
                                                                    } failureBlock: completionBlock];
                                                          
                                                      } failureBlock:^(NSError *error) {
                                                          
                                                          completionBlock(error);
                                                      }];
                                
                                //should be the last iteration anyway, but just in case
                                return;
                            }
                            
                        } failureBlock:^(NSError *error) {
                            
                            
                            completionBlock(error);
                        }];
    
}

@end
