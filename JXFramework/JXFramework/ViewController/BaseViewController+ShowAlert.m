//
//  BaseViewController+ShowAlert.m
//  UnderGroundApp
//
//  Created by audi on 15/7/30.
//  Copyright (c) 2015年 Ohey. All rights reserved.
//

#import "BaseViewController+ShowAlert.h"
#import <objc/runtime.h>


static const void *UIAlertCallbackKey = &UIAlertCallbackKey;

@implementation UIActionSheet (Callback)

- (void)setCallback:(UIActionSheetCallback)callback
{
    if (callback) {
        objc_setAssociatedObject(self, UIAlertCallbackKey, callback, OBJC_ASSOCIATION_COPY_NONATOMIC);
        self.delegate = (id<UIActionSheetDelegate>)self;
    }
}

- (UIActionSheetCallback)callback
{
    return objc_getAssociatedObject(self, UIAlertCallbackKey);
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex;
{
    BOOL isCancelButton = NO;
    
    if (buttonIndex == actionSheet.cancelButtonIndex) {
        isCancelButton = YES;
    }
    UIActionSheetCallback callback = self.callback;
    if (callback) {
        callback(buttonIndex, isCancelButton);
        self.callback = nil;
    }
}

- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    
}

@end

@interface UIAlertView (Callback)<UIAlertViewDelegate>
@property (nonatomic, copy) UIAlertCallback callback;
@end

@implementation UIAlertView (Callback)

- (void)setCallback:(UIAlertCallback)callback
{
    if (callback) {
        objc_setAssociatedObject(self, UIAlertCallbackKey, callback, OBJC_ASSOCIATION_COPY_NONATOMIC);
        self.delegate = (id<UIAlertViewDelegate>)self;
    }
}

- (UIAlertCallback)callback
{
    return objc_getAssociatedObject(self, UIAlertCallbackKey);
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    BOOL isCancelButton = NO;
    
    if (buttonIndex == alertView.cancelButtonIndex) {
        isCancelButton = YES;
    }
    
    UIAlertCallback callback = self.callback;
    if (callback) {
        callback(buttonIndex, isCancelButton);
        self.callback = nil;
    }
}
@end

@implementation BaseViewController (ShowAlert)

- (void)showAlertWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSArray *)otherButtonTitles callback:(UIAlertCallback)callback
{
    NSString *titleString = nil;
    if (!title) {
        titleString = @"";
    } else {
        titleString = title;
    }
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:titleString message:message delegate:nil cancelButtonTitle:cancelButtonTitle otherButtonTitles:nil, nil];
    
    // save callback
    if (callback) {
        alert.callback = callback;
    }
    
    // add other buttons if necessary
    for (NSString *buttonTitle in otherButtonTitles) {
        [alert addButtonWithTitle:buttonTitle];
    }
    
    // show alert
    [alert show];

}

- (void)showActionWithTitle:(NSString *)title cancelButtonTitle:(NSString *)cancelButtonTitle destructiveButtonTitle:(NSString *)destructiveButtonTitle otherButtonTitles:(NSArray *)otherButtonTitles callback:(UIActionSheetCallback)callback
{
    // create an instance for UIActionSheet
    UIActionSheet *sheet = [[UIActionSheet alloc] initWithTitle:title delegate:nil cancelButtonTitle:nil destructiveButtonTitle:destructiveButtonTitle otherButtonTitles:nil, nil];
    
    // save callback
    if (callback) {
        sheet.callback = callback;
    }
    
    // add other buttons if necessary
    NSInteger cancelButtonIndex = -1;
    if ([destructiveButtonTitle length]) {
        cancelButtonIndex++;
    }
    for (NSString *buttonTitle in otherButtonTitles) {
        [sheet addButtonWithTitle:buttonTitle];
        cancelButtonIndex++;
    }
    if (cancelButtonTitle) {
        [sheet addButtonWithTitle:cancelButtonTitle];
        cancelButtonIndex++;
    }
    sheet.cancelButtonIndex = cancelButtonIndex;
    
    // show action sheet
    [sheet showInView:self.view];
}
@end
