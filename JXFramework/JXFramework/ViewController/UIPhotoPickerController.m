//
//  UIPhotoPickerController.m
//  JXFramework
//
//  Created by yangjinxin on 15/9/8.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "UIPhotoPickerController.h"


@interface UIPhotoPickerController () <UIImagePickerControllerDelegate,UINavigationControllerDelegate>
{
    
}
@end



@implementation UIPhotoPickerController

- (void)createPickerWithType:(UIImagePickerControllerSourceType)type
{
    self.picker = [[UIImagePickerController alloc] init];
    self.picker.delegate = self;
    self.picker.sourceType = type;
}

- (void)showCameraInViewController:(UIViewController *)viewController
{
    
    if (!viewController) {
        return;
    }
    
    
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if(authStatus == AVAuthorizationStatusAuthorized)
    {
        [self createPickerWithType:UIImagePickerControllerSourceTypeCamera];
        
        if (viewController) {
            [viewController presentViewController:self.picker
                                         animated:YES completion:NULL];
            
        }
    }
    else if(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:NSLocalizedString(@"set.cam.msg", nil)
                                                       delegate:nil
                                              cancelButtonTitle:NSLocalizedString(@"com.btn.ok", nil)
                                              otherButtonTitles:nil, nil];
        [alert show];
    }
    else if(authStatus == AVAuthorizationStatusNotDetermined)
    {
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            dispatch_async(dispatch_get_main_queue(), ^{
                if(granted){
                    [self createPickerWithType:UIImagePickerControllerSourceTypeCamera];
                    if (viewController) {
                        [viewController presentViewController:self.picker
                                                     animated:YES completion:NULL];
                        
                    }
                } else {
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                                    message:NSLocalizedString(@"set.cam.msg", nil)
                                                                   delegate:nil
                                                          cancelButtonTitle:NSLocalizedString(@"com.btn.ok", nil)
                                                          otherButtonTitles:nil, nil];
                    [alert show];
                }
                
            });
        }];
    }
}

- (void)showPhotoLibraryInViewController:(UIViewController *)viewController
{
    if (!viewController) {
        return;
    }
    
    ALAuthorizationStatus author = [ALAssetsLibrary authorizationStatus];
    if (author == ALAuthorizationStatusNotDetermined)
    {
        ALAssetsLibrary *lib = [[ALAssetsLibrary alloc] init];
        [lib assetForURL:nil
             resultBlock:^(ALAsset *asset) {
                 dispatch_async(dispatch_get_main_queue(), ^{
                     [self createPickerWithType:UIImagePickerControllerSourceTypePhotoLibrary];
                     if (viewController) {
                         [viewController presentViewController:self.picker
                                                      animated:YES completion:NULL];
                     }
                 });
             } failureBlock:^(NSError *error) {
                 dispatch_async(dispatch_get_main_queue(), ^{
                     [self createPickerWithType:UIImagePickerControllerSourceTypePhotoLibrary];
                     if (viewController) {
                         [viewController presentViewController:self.picker
                                                      animated:YES completion:NULL];
                     }
                 });
             }];
    }
    else
    {
        [self createPickerWithType:UIImagePickerControllerSourceTypePhotoLibrary];
        if (viewController) {
            [viewController presentViewController:self.picker
                                         animated:YES completion:NULL];
        }
    }
    
}

#pragma mark UIImagePickerControllerDelegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    
}


- (void)imagePickerController:(UIImagePickerController *)picker
        didFinishPickingImage:(UIImage *)image
                  editingInfo:(NSDictionary *)editingInfo
{
    if (self.delegate) {
        [self.delegate didFinishPickingImage:image picker:picker];
    }

    [picker dismissViewControllerAnimated:NO completion:NULL];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;
{
    if (self.delegate) {
        [self.delegate didCancelPickingImage:picker];
    }
    
    [picker dismissViewControllerAnimated:NO completion:NULL];
}


@end
