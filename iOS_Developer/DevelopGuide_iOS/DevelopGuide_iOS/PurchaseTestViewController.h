//
//  PurchaseTestViewController.h
//  PurchaseTest
//
//  Created by fanshao on 09-10-16.
//  Copyright Sensky 2009. All rights reserved.
//

#import <UIKit/UIKit.h>
#import<StoreKit/StoreKit.h>

@interface PurchaseTestViewController : UIViewController <SKProductsRequestDelegate> {
    UITextView *productInfo;
    NSString *productStr;

}

-(IBAction) PayForProduct;
@end

