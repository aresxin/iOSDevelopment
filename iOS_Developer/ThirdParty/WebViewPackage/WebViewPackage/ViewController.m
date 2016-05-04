//
//  ViewController.m
//  WebViewPackage
//
//  Created by yangjinxin on 14-10-23.
//  Copyright (c) 2014年 yangjinxin. All rights reserved.
//

#import "ViewController.h"
#import "KINWebBrowserExampleViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    
}

- (IBAction)actionNext:(id)sender
{
    KINWebBrowserExampleViewController *exampleC = [[KINWebBrowserExampleViewController alloc] init];
    
    [self.navigationController pushViewController:exampleC animated:YES];
}
@end
