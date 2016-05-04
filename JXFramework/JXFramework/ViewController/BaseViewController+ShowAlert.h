//
//  BaseViewController+ShowAlert.h
//  UnderGroundApp
//
//  Created by auid on 15/7/30.
//  Copyright (c) 2015年 Ohey. All rights reserved.
//

#import "BaseViewController.h"


typedef void (^UIAlertCallback)(NSInteger buttonIndex, BOOL isCancelButton);

typedef void (^UIActionSheetCallback)(NSInteger buttonIndex, BOOL isCancelButton);


@interface UIActionSheet (Callback)<UIActionSheetDelegate>
@property (nonatomic, copy) UIActionSheetCallback callback;
@end

@interface BaseViewController (ShowAlert)

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSArray *)otherButtonTitles callback:(UIAlertCallback)callback;

- (void)showActionWithTitle:(NSString *)title cancelButtonTitle:(NSString *)cancelButtonTitle destructiveButtonTitle:(NSString *)destructiveButtonTitle otherButtonTitles:(NSArray *)otherButtonTitles callback:(UIActionSheetCallback)callback;


@end
