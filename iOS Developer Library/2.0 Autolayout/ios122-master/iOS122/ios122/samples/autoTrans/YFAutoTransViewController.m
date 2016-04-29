//
//  YFAutoTransViewController.m
//  iOS122
//
//  Created by 颜风 on 15/10/5.
//  Copyright (c) 2015年 iOS122. All rights reserved.
//

#import "YFAutoTransViewController.h"
#import "YFAutoTransView.h"

@interface YFAutoTransViewController ()

@end

@implementation YFAutoTransViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"设计图自动转代码";
    
    YFAutoTransView * autoTestView = [[YFAutoTransView alloc] init];
    
    autoTestView.frame = CGRectMake(0, 100, [UIScreen mainScreen].bounds.size.width, 155.0/2);
    
    autoTestView.imageView.image = [UIImage imageNamed:@"autoTrans.png"];
    
    autoTestView.titleLabel.text = @"爱马仕版苹果表开售8688元起";
    
    autoTestView.detailLabel.text = @"爱马仕版苹果表盘和表带并不会单独销售.爱马仕版苹果表盘和表带并不会单独销售.";
    
    [autoTestView.chatBtn setTitle:@"跟帖" forState: UIControlStateNormal];
    autoTestView.chatBtn.backgroundColor = [UIColor redColor];
    
    [self.view addSubview: autoTestView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
