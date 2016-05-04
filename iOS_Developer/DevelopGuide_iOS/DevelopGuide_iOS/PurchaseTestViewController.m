//
//  PurchaseTestViewController.m
//  PurchaseTest
//
//  Created by fanshao on 09-10-16.
//  Copyright Sensky 2009. All rights reserved.
//

#import "PurchaseTestViewController.h"

@implementation PurchaseTestViewController
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    productInfo = [[UITextView alloc] initWithFrame:CGRectMake(5, 5, 310, 350)];
    productInfo.editable = NO;
    [self.view addSubview:productInfo];
}

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}

#pragma mark -
#pragma mark SotoreKit method

- (void) requestProductData{
	NSLog(@"requestProductData");
    productStr = [productStr stringByAppendingFormat:@"requestProductData \n"];
	SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers: [NSSet setWithObjects:@"com.yourcom.yourpid"/*填写你的完整商品ID,多个以逗号分隔*/,nil]];
	request.delegate = self;
	[request start];
}
#pragma mark request delegate
//!收到产品的消息
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
	NSLog(@"ProductsRequest did receiveResponse");
    productStr = [@"" stringByAppendingFormat:@"ProductsRequest did receiveResponse \n"];

	NSArray *myProduct = response.products;
	NSLog(@"the count of products is %d", [myProduct count]);
    productStr = [productStr stringByAppendingFormat:@"the count of products is %d\n", [myProduct count]];

	// populate UI
	for(SKProduct *product in myProduct){
		NSLog(@"%@", [product description]);
		NSLog(@"%@", [product productIdentifier]);       
        SKPayment *payment = [SKPayment paymentWithProduct:product];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
	}
    
    myProduct = response.invalidProductIdentifiers;
    NSLog(@"the count of invalid products is %d", [myProduct count]);
    productStr = [productStr stringByAppendingFormat:@"the count of invalid products is %d\n", [myProduct count]];

	for(NSString *product in myProduct){
	}
    productInfo.text = productStr;
	[request autorelease];
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
	UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert" message:[error localizedDescription]
																										 delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
	
	[alerView show];
	[alerView release];
}

- (void)dealloc {
    [super dealloc];
}
-(IBAction) PayForProduct{
	[self requestProductData];
}

@end
