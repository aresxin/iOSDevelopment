//
//  DWRemoveLimitViewController.m
//  DWViewer
//
//  Created by xinjun xu on 12-3-22.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import "DWRemoveLimitViewController.h"
#import "DWViewerAppDelegate.h"
#import "DWViewerGUIConst.h"
#import "Utility.h"

#define TAG_ALERT_PAY_CONFIRM			100
#define TAG_BUTTON_RESTORE				101
#define TAG_BUTTON_PURCHASE             102

#define BUTTON_PURCHASE_HEIGHT			44.0f

#define BUTTON_PURCHASE_WIDTH_H_IPAD	680.0f
#define BUTTON_PURCHASE_WIDTH_V_IPAD	936.0f
#define BUTTON_PURCHASE_WIDTH_H_IPHONE	300.0f
#define BUTTON_PURCHASE_WIDTH_V_IPHONE	460.0f

#define LABEL_NOTICE_WIDTH_H_IPAD		680.0f - 10.0f
#define LABEL_NOTICE_WIDTH_V_IPAD		936.0f - 10.0f
#define LABEL_NOTICE_WIDTH_H_IPHONE		300.0f - 10.0f
#define LABEL_NOTICE_WIDTH_V_IPHONE		460.0f - 10.0f

#define LIMIT_LABEL_FONT_SIZE			12

#define NOTIFICATION_NAME				@"NotificationProductPurchased"

#pragma mark -
#pragma mark SKProduct
@interface  SKProduct (LocalizePrice)
@property (nonatomic, readonly) NSString *localizePrice;
@end

@implementation SKProduct (LocalizePrice)

- (NSString *)localizePrice
{
    if (nil == self.priceLocale || nil == self.price || [[self.price stringValue] isEqualToString:@""]) 
    {
        return  nil;
    }
    
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:self.priceLocale];
    NSString *formatteString = [numberFormatter stringFromNumber:self.price];
    [numberFormatter release];
    
    return formatteString;
}
@end


#pragma mark -
#pragma mark DWPaymentTransactionObserver class
@implementation DWPaymentTransactionObserver
@synthesize productIdentifier = productIdentifier_;

- (id) init
{
	self = [super init];
	if (self)
	{
		[[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        self.productIdentifier = PRODUCT_ID_ANNOTATION_EDITION;
	}
    
    return self;
}

- (void) dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [productIdentifier_ release];
    
	[super dealloc];
}

#pragma mark -
#pragma mark Observer method

- (void) recordTransaction
{
	[[NSUserDefaults standardUserDefaults] setBool:YES forKey:TRANSACTION_STATE];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void) postNotification
{
	[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_NAME 
														object:self 
													  userInfo:nil];
}

- (void) completeTransaction:(SKPaymentTransaction *)transaction
{
	// 1. record transaction.
	[self recordTransaction];
	
	// 2. 制限画面を更新する
	[self postNotification];
	
	// 3. finish transaction.
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void) failedTransaction:(SKPaymentTransaction *)transaction
{
	// 1. show error message.
	NSString* message_ = [transaction.error localizedDescription];
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil 
													   message:message_
													  delegate:nil
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:nil];
	[alertView show];
	[alertView release];
	
	// 2. 制限画面を更新する
    [self postNotification];
	
	// 3. finish transaction.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

- (void) restoreTransaction:(SKPaymentTransaction *)transaction
{
	[self completeTransaction:transaction];
}

#pragma mark -
#pragma mark SKPaymentTransactionObserver delegate
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{ 
	for (SKPaymentTransaction *transaction in transactions)
	{
		if ([transaction.payment.productIdentifier isEqualToString:self.productIdentifier] == YES)
		{
			switch (transaction.transactionState)
			{
					// 購入が成功
				case SKPaymentTransactionStatePurchased:
					[self completeTransaction:transaction];
					break;
					
					// 購入が失敗
				case SKPaymentTransactionStateFailed:
					[self failedTransaction:transaction];
					break;
					
					// リストア
				case SKPaymentTransactionStateRestored:
                    [self restoreTransaction:transaction];
					break;
                    
					// 購入中
                case SKPaymentTransactionStatePurchasing:
                    break;
                    
				default:
					break;
			}
		}
	}
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
    for (SKPaymentTransaction *transaction in queue.transactions)
	{
		if ([transaction.payment.productIdentifier isEqualToString:self.productIdentifier] == YES)
		{
			// 1. show error message.
			if (SKErrorPaymentCancelled != error.code) 
			{
				NSString* message_ = [error localizedDescription];
				UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil 
																   message:message_
																  delegate:nil
														 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
														 otherButtonTitles:nil];
				[alertView show];
				[alertView release];
			}

			// 2. finish transaction.
            [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
		}
	}
    
    // 3. 制限画面を更新する
    [self postNotification];
}

@end


#pragma mark -
#pragma mark DWRemoveLimitViewController class
@implementation DWRemoveLimitViewController
@synthesize productIdentifier	= productIdentifier_;
@synthesize product				= product_;
@synthesize buttonPurchase		= buttonPurchase_;
@synthesize buttonRestore		= buttonRestore_;

#pragma mark - init
- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) 
	{ 
		self.title = NSLocalizedString(@"MSG_PAYM_CELL_TEXTLABLE_TEXT", nil);
		
		self.productIdentifier = PRODUCT_ID_ANNOTATION_EDITION;
        
		orientation_ = self.interfaceOrientation;
		
        // init left button item.
        [self initLeftBarItem];
        
        // init purchase and restore button.
        [self initPruchaseAndRestoreButtons];
		
		isIndicatorAnimating = NO;
		activityIndicator_ = nil;
    }
	
    return self;
}

- (void) initLeftBarItem
{
    UIButton* buttonBack = [UIButton buttonWithType:(UIButtonType)101];
    [buttonBack setTitle:NSLocalizedString(@"MENU_SETTINGVIEW_TITLE", nil) forState:UIControlStateNormal];
    [buttonBack addTarget:self action:@selector(actionOnTouchCloseButton) forControlEvents:UIControlEventTouchDown];
    UIBarButtonItem* leftButtonItem = [[UIBarButtonItem alloc]initWithCustomView:buttonBack];
    self.navigationItem.leftBarButtonItem = leftButtonItem;
    [leftButtonItem release];
}

- (void) initPruchaseAndRestoreButtons
{
	CGRect buttonRect = CGRectMake(0, 0, 100, 30);
	
	// 1. init purchase button.
    self.buttonPurchase = [UIButton buttonWithType:UIButtonTypeCustom];
    self.buttonPurchase.frame = buttonRect;
    [self.buttonPurchase addTarget:self 
							action:@selector(actionOnTouchPurchaseButton:) 
				  forControlEvents:UIControlEventTouchUpInside];
    [self.buttonPurchase setTitleColor:[UIColor blackColor] 
							  forState:UIControlStateNormal];
    self.buttonPurchase.layer.cornerRadius = 3.0;
    self.buttonPurchase.layer.borderColor = [UIColor darkGrayColor].CGColor;
    self.buttonPurchase.layer.borderWidth = 1.5;
    self.buttonPurchase.tag = TAG_BUTTON_PURCHASE;
    
    // 2. init Restore button.
    self.buttonRestore = [UIButton buttonWithType:UIButtonTypeCustom];
    self.buttonRestore.frame = [self getRestoreButtonFrameWithOrientation:orientation_];
    
    UIColor *titleColor = [UIColor colorWithRed:0.96 green:0.59 blue:0.47 alpha:1];
    [self.buttonRestore setTitleColor:titleColor forState:UIControlStateNormal];
    
    [self.buttonRestore setTitle:NSLocalizedString(@"MSG_PAYM_CELL_TEXTLABEL_RESTORE", nil) 
						forState:UIControlStateNormal];
    [self.buttonRestore addTarget:self
						   action:@selector(actionOnTouchRestoreButton:) 
				 forControlEvents:UIControlEventTouchUpInside]; 
    self.buttonRestore.titleLabel.textAlignment = UITextAlignmentCenter;
    self.buttonRestore.titleLabel.font = [UIFont systemFontOfSize:14.0];
    
	// 3. init button enable status.
	if ([[NSUserDefaults standardUserDefaults] boolForKey:TRANSACTION_STATE]) 
    {
        [self.buttonPurchase setEnabled:NO];
        [self.buttonPurchase setTitle:NSLocalizedString(@"TITLE_BUTTON_PAY_END", nil) 
							 forState:UIControlStateNormal];
		
		[self.buttonRestore setEnabled:NO];
    }
    else
    {
        [self.buttonPurchase setEnabled:YES];
        [self.buttonPurchase setTitle:NSLocalizedString(@"TITLE_BUTTON_PAY_PRO", nil) 
							 forState:UIControlStateNormal];
		
		[self.buttonRestore setEnabled:YES];
    }
}

#pragma mark - memory lifecycle
- (void)dealloc
{
	self.productIdentifier = nil;
    self.product = nil;
    self.buttonPurchase = nil;
    self.buttonRestore = nil;
    
	[super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle
- (void)viewDidLoad
{
	[super viewDidLoad];
	
    [[NSNotificationCenter defaultCenter] addObserver:self 
											 selector:@selector(didReceiveNotification) 
												 name:NOTIFICATION_NAME 
											   object:nil];
}

- (void)viewWillAppear:(BOOL)animated 
{
	[super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[[NSNotificationCenter defaultCenter] removeObserver:self 
													name:NOTIFICATION_NAME 
												  object:nil];
    [super viewDidUnload];
}

#pragma mark - notification funcation
- (void) didReceiveNotification
{
	// 1. restore buttons enable.
	[self setUIButtonsEnabled:YES];
	
	// 2. hide activity indicator.
	[self hideActivityIndicator];
	
	// 3. reset purchase and restore button state.
	if ([[NSUserDefaults standardUserDefaults] boolForKey:TRANSACTION_STATE] == YES)
    {
        [self.buttonPurchase setEnabled:NO];
        [self.buttonPurchase setTitle:NSLocalizedString(@"TITLE_BUTTON_PAY_END", nil) 
						 forState:UIControlStateNormal];
		
		[self.buttonRestore setEnabled:NO];
    }
}

#pragma mark - View Rotation
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
	orientation_ = toInterfaceOrientation;
	
    [self.tableView reloadData];
    
    if (isIndicatorAnimating == YES) 
    {
        [activityIndicator_ setCenter:self.tableView.center];
        [self setUIButtonsEnabled:NO];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    CGFloat footerHeight = 0.0f;
    
    if (0 == section) 
    {
        footerHeight = [self getFooterLabelHeightWithOrientation:self.interfaceOrientation];
    }
    
    return footerHeight;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
	if (section == 0)
    {
        CGRect cgFrame = [[UIScreen mainScreen] applicationFrame];
        CGFloat viewheight = [self getFooterLabelHeightWithOrientation:self.interfaceOrientation];
        UIView *footer_ = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, cgFrame.size.width, viewheight)] autorelease];
        footer_.autoresizesSubviews = YES;
        footer_.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        footer_.opaque = NO;
        
        CGRect rect = [self getFooterlabelFrameWithOrientation:self.interfaceOrientation];
        UILabel *labelNotice_ = [[[UILabel alloc] initWithFrame:rect]autorelease];
        labelNotice_.backgroundColor = [UIColor clearColor];
        labelNotice_.opaque = NO;
        labelNotice_.text = NSLocalizedString(@"MSG_PAYM_TABLEVIEW_SECTION", nil);
        labelNotice_.textColor = [UIColor blackColor];
        labelNotice_.font = [UIFont boldSystemFontOfSize:LIMIT_LABEL_FONT_SIZE];
        labelNotice_.shadowColor = [UIColor whiteColor];
        labelNotice_.shadowOffset = CGSizeMake(0, 1);
        labelNotice_.textAlignment = UITextAlignmentLeft;
        labelNotice_.numberOfLines = 0;
        labelNotice_.lineBreakMode = UILineBreakModeWordWrap;
        [footer_ addSubview:labelNotice_];

        return footer_;
    }
	
	return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{    
    static NSString *CellIdentifier = nil;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) 
    {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
    }
    
    for (UIView *subview in [cell.contentView subviews] ) 
    {
		[subview removeFromSuperview];
	}
    
    cell.textLabel.font = [UIFont systemFontOfSize:14.0];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    
	if (indexPath.section == 0) 
	{  
		cell.textLabel.text = NSLocalizedString(@"MSG_PAYM_CELL_ANN_EDIT_TEXT", nil);
		cell.accessoryView = self.buttonPurchase;
	} 
    else if (indexPath.section == 1)
    {
        cell.textLabel.text = nil;
        cell.accessoryView = nil;
        self.buttonRestore.frame = [self getRestoreButtonFrameWithOrientation:orientation_];
        [cell.contentView addSubview:self.buttonRestore];
    }
    
    return cell;
}

#pragma mark - action event
- (void) actionOnTouchPurchaseButton:(id)sender
{    
    if ([self canMakePayment] == NO)
    {
        [self showCannotPaymentWarning];
    }
    else
    {
        [self requestProductData];
		
#if !(TARGET_IPHONE_SIMULATOR)
        [self setUIButtonsEnabled:NO];
        [self displayActivityIndicator];
#endif		
    }
}

- (void) actionOnTouchRestoreButton:(id)sender
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
	
#if !(TARGET_IPHONE_SIMULATOR)
    [self setUIButtonsEnabled:NO];
    [self displayActivityIndicator];
#endif	
}

- (void) actionOnTouchCloseButton
{
	[self.navigationController popViewControllerAnimated:YES];
}

#pragma mark -
#pragma mark alertView delegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (alertView.tag == TAG_ALERT_PAY_CONFIRM) 
	{
		if (buttonIndex == 0)
		{
			// 1. set request.
			[self sendPaymentRequest];
			
			// 2. set buttionitems disenable.
			[self setUIButtonsEnabled:NO];
			
			// 3. display wating indicator.
			[self displayActivityIndicator];
		}
	}
}

#pragma mark -
#pragma mark request delegate
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
	NSArray *products_ = response.products;
	for(SKProduct *product in products_)
	{
		if ([product.productIdentifier isEqualToString:self.productIdentifier] == YES)
		{		
			// 1. show payment price warning message.
			[self showPaymentPriceWarning:product];
			break;
		}
	}
	
	// 2. resotre buttons enable.
	[self setUIButtonsEnabled:YES];
    
    // 3. hide activity indicator.
    [self hideActivityIndicator];
        
	[request release];
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
	// 1. resotre buttons enable.
	[self setUIButtonsEnabled:YES];
	
	// 2. hide activity indicator.
    [self hideActivityIndicator];
	
	// 3. show error message.
	NSString *message_	= [error localizedDescription];
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil 
													   message:message_
													  delegate:self
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:nil];
	[alertView show];
	[alertView release];
    
    [request release];
}

#pragma mark -
#pragma mark public method
- (BOOL) canMakePayment
{
	return [SKPaymentQueue canMakePayments];
}

- (void) requestProductData
{
	NSArray	*productInfos_			= [[NSArray alloc]initWithObjects:self.productIdentifier, nil];
	NSSet	*productIndentifiers_	= [NSSet setWithArray:productInfos_];
	SKProductsRequest* request_		= [[SKProductsRequest alloc]initWithProductIdentifiers:productIndentifiers_];
	request_.delegate				= self;
	
	[request_ start];
	[productInfos_ release];
}

- (void) sendPaymentRequest
{
	SKPayment *payment_ = [SKPayment paymentWithProduct:self.product];
	[[SKPaymentQueue defaultQueue] addPayment:payment_];
}

- (void) showCannotPaymentWarning
{
	// 1. resotre buttons enable.
	[self setUIButtonsEnabled:YES];
	
    // 2. hide activity indicator.
    [self hideActivityIndicator];
	
	// 2. show error message.
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil 
													   message:NSLocalizedString(@"MSG_PAYM_ALERT_BUYLIMIT_MESSAGE", nil)
													  delegate:self
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
											 otherButtonTitles:nil];
	[alertView show];
	[alertView release];
}

- (void) showPaymentPriceWarning:(SKProduct *)product
{   	
    self.product = product;
	
    NSString *price = [product localizePrice];
    if (nil == price) 
    {
        return;
    }
	
    NSString* message_ = [NSString stringWithFormat:NSLocalizedString(@"MSG_PAYM_ALERT_PURCHASEBUTTON_MESSAGE", nil), price];
	UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"MSG_PAYM_ALERT_PURCHASEBUTTON_TITLE", nil) 
													   message:message_
													  delegate:self
											 cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES", nil)
											 otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil), 
                              (char*)nil];
	alertView.delegate = self;
	alertView.tag = TAG_ALERT_PAY_CONFIRM;
	[alertView show];
	[alertView release];
}

- (void) setUIButtonsEnabled:(BOOL)enable
{
	self.tableView.allowsSelection = enable;
    self.tableView.scrollEnabled = enable;
    [self.buttonRestore setEnabled:enable];
    [self.buttonPurchase setEnabled:enable];

    self.navigationItem.leftBarButtonItem.enabled = enable;  
}

#pragma mark - Activity Indicator
- (void) displayActivityIndicator
{
	// 1. init activity indicator.	
    activityIndicator_ = [[UIActivityIndicatorView alloc]
						  initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    
    if (activityIndicator_ != nil)
    {
        activityIndicator_.frame = CGRectMake(0, 0, 40, 40);
        
        if ([activityIndicator_ respondsToSelector:@selector(color)])
        {
            activityIndicator_.color = [UIColor blackColor];
        }
        else
        {
            activityIndicator_.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        }
    }
    [activityIndicator_ setCenter:self.tableView.center];
    [self.tableView addSubview:activityIndicator_];
    [activityIndicator_ startAnimating];
	
	isIndicatorAnimating = YES;
}

- (void) hideActivityIndicator
{
	if (isIndicatorAnimating)
    {
		isIndicatorAnimating = NO;
        
		if (activityIndicator_ != nil)
		{
			[activityIndicator_ stopAnimating];
			[activityIndicator_ removeFromSuperview];
			[activityIndicator_ release];
			activityIndicator_ = nil;
		}
	}
}

#pragma mark - 
#pragma mark private method
- (CGSize) getScreenSizeWithOrientation:(UIInterfaceOrientation)orientation
{
    CGSize size_ = [[UIScreen mainScreen] bounds].size;
    if (UIInterfaceOrientationIsLandscape(orientation) == YES) 
    {
        size_ = CGSizeMake(size_.height, size_.width);
    }
    
    return size_;
}

- (float) getFooterLabelHeightWithOrientation:(UIInterfaceOrientation)orientation
{
    float  offset	= 10.0f;
    float  width	= 0.0f;
    
    if (UIInterfaceOrientationIsPortrait(orientation)) 
    {
        if (Utility::UIDeviceIsiPad() == NO)
        {
            width = LABEL_NOTICE_WIDTH_H_IPHONE;
        }
        else
        {
			width = LABEL_NOTICE_WIDTH_H_IPAD;
        }	
    }
	else
	{
		if (Utility::UIDeviceIsiPad() == NO)
        {
            width = LABEL_NOTICE_WIDTH_V_IPHONE;
        }
        else
        {
			width = LABEL_NOTICE_WIDTH_V_IPAD;
        }
	}
    
	NSString *string_ = NSLocalizedString(@"MSG_PAYM_TABLEVIEW_SECTION", nil);
    CGSize size = [string_ sizeWithFont:[UIFont systemFontOfSize:LIMIT_LABEL_FONT_SIZE] 
					  constrainedToSize:CGSizeMake(width, 10000) 
						  lineBreakMode:UILineBreakModeWordWrap];
    
    return size.height + offset;
}

- (CGRect) getFooterlabelFrameWithOrientation:(UIInterfaceOrientation)orientation
{
	float originX = 0.0f;
	float originY = 0.0f;
	float width   = 0.0f;
	float height  = 0.0f;
	
	if (Utility::UIDeviceIsiPad() == NO)
	{
		originX = 18.0f;
	}
	else
	{
		originX = 50.0f;
	}
	
	if (UIInterfaceOrientationIsPortrait(orientation)) 
    {
        if (Utility::UIDeviceIsiPad() == NO)
        {
            width = LABEL_NOTICE_WIDTH_H_IPHONE;
        }
        else
        {
			width = LABEL_NOTICE_WIDTH_H_IPAD;
        }	
    }
	else
	{
		if (Utility::UIDeviceIsiPad() == NO)
        {
            width = LABEL_NOTICE_WIDTH_V_IPHONE;
        }
        else
        {
			width = LABEL_NOTICE_WIDTH_V_IPAD;
        }
	}
	
	height = [self getFooterLabelHeightWithOrientation:orientation];
	
	return CGRectMake(originX, originY, width, height);
}

- (CGRect) getRestoreButtonFrameWithOrientation:(UIInterfaceOrientation)orientation
{
	float originX = 0.0f;
	float originY = 0.0f;
	float width   = 0.0f;
	float height  = 0.0f;
	
	if (UIInterfaceOrientationIsPortrait(orientation)) 
    {
        if (Utility::UIDeviceIsiPad() == NO)
        {
            width = BUTTON_PURCHASE_WIDTH_H_IPHONE;
        }
        else
        {
			width = BUTTON_PURCHASE_WIDTH_H_IPAD;
        }	
    }
	else
	{
		if (Utility::UIDeviceIsiPad() == NO)
        {
            width = BUTTON_PURCHASE_WIDTH_V_IPHONE;
        }
        else
        {
			width = BUTTON_PURCHASE_WIDTH_V_IPAD;
        }
	}
	
	height = BUTTON_PURCHASE_HEIGHT;
	
	return CGRectMake(originX, originY, width, height);
}

@end
