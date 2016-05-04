//
//  DWRemoveLimitViewController.h
//  DWViewer
//
//  Created by xinjun xu on 12-3-22.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "StoreKit/StoreKit.h"
#import <QuartzCore/QuartzCore.h>

@interface DWPaymentTransactionObserver : NSObject<SKPaymentTransactionObserver>
{
	NSString *productIdentifier_;
}
@property (nonatomic, retain) NSString *productIdentifier;

- (void) completeTransaction:(SKPaymentTransaction *)transaction;
- (void) failedTransaction:(SKPaymentTransaction *)transaction;
- (void) restoreTransaction:(SKPaymentTransaction *)transaction;

- (void) recordTransaction;
- (void) postNotification;
@end


@interface DWRemoveLimitViewController : UITableViewController<SKProductsRequestDelegate, UITableViewDelegate>
{
	UIInterfaceOrientation		orientation_;
	
	NSString                    *productIdentifier_;
	SKProduct                   *product_;
	
	UIButton                    *buttonPurchase_;
    UIButton                    *buttonRestore_;
	
    BOOL                        isIndicatorAnimating;
    UIActivityIndicatorView     *activityIndicator_;
}
@property (nonatomic, retain) NSString  *productIdentifier;
@property (nonatomic, retain) SKProduct *product;
@property (nonatomic, retain) UIButton  *buttonPurchase;
@property (nonatomic, retain) UIButton  *buttonRestore;

- (void) initLeftBarItem;
- (void) initPruchaseAndRestoreButtons;

- (void) actionOnTouchPurchaseButton:(id)sender;
- (void) actionOnTouchRestoreButton:(id)sender;
- (void) actionOnTouchCloseButton;

- (BOOL) canMakePayment;
- (void) requestProductData;
- (void) sendPaymentRequest;

- (void) showCannotPaymentWarning;
- (void) showPaymentPriceWarning:(SKProduct *)product;

- (void) didReceiveNotification;

- (void) setUIButtonsEnabled:(BOOL)enable;

- (void) displayActivityIndicator;
- (void) hideActivityIndicator;

- (CGSize) getScreenSizeWithOrientation:(UIInterfaceOrientation)orientation;
- (float)  getFooterLabelHeightWithOrientation:(UIInterfaceOrientation)orientation;
- (CGRect) getFooterlabelFrameWithOrientation:(UIInterfaceOrientation)orientation;
- (CGRect) getRestoreButtonFrameWithOrientation:(UIInterfaceOrientation)orientation;
@end