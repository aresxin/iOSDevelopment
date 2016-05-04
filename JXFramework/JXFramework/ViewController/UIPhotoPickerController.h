//
//  UIPhotoPickerController.h
//  JXFramework
//
//  Created by yangjinxin on 15/9/8.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AssetsLibrary/AssetsLibrary.h>

@protocol UIPhotoPickerControllerDelegate <NSObject>

@required
- (void) didFinishPickingImage:(UIImage *)image
                        picker:(UIImagePickerController *)picker;
- (void) didCancelPickingImage:(UIImagePickerController *)picker;
@end


@interface UIPhotoPickerController : NSObject

@property (nonatomic, strong) UIImagePickerController *picker;

@property (nonatomic, assign) id <UIPhotoPickerControllerDelegate> delegate;

@property (nonatomic, strong) NSString *cameraDisableMessage;

- (void)showCameraInViewController:(UIViewController *)viewController;

- (void)showPhotoLibraryInViewController:(UIViewController *)viewController;
@end
