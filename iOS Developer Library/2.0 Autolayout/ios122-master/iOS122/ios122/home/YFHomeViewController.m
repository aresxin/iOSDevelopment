//
//  YFHomeViewController.m
//  iOS122
//
//  Created by 颜风 on 15/9/22.
//  Copyright (c) 2015年 iOS122. All rights reserved.
//

#import "YFHomeViewController.h"
#import "YFAutoLayoutCellViewController.h"
#import "YFAutoTransViewController.h"
#import <AFNetworking.h>

@interface YFHomeViewController ()<UITableViewDataSource, UITableViewDelegate>
@property (strong, nonatomic) UITableView * tabelView;

@end

@implementation YFHomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.title = @"主页";
    self.tabelView = [[UITableView alloc] init];
}

- (void)setTabelView:(UITableView *)tabelView
{
    _tabelView = tabelView;
    
    
    [self.view addSubview: self.tabelView];
    
    self.tabelView.delegate = self;
    self.tabelView.dataSource = self;
    
    [self.tabelView remakeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.view);
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - UITabelView 代理方法.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 2;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell * cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier: @"cell"];
    
    cell.textLabel.text = @"Masonry + UITableView-FDTemplateLayoutCell";
    
    cell.detailTextLabel.text = @"实现基于约束的自适应单元格的高度tabelView";
    
    if (1 == indexPath.row) {
        cell.textLabel.text = @"UI设计图自动转iOS UI控件";
        cell.detailTextLabel.text = @"给出设计图,就能立即自动生成相应的代码.";
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (0 == indexPath.row) {
        YFAutoLayoutCellViewController * cellVC = [[YFAutoLayoutCellViewController alloc] init];
        
        [self.navigationController pushViewController: cellVC animated: YES];
    }
    
    if (1 == indexPath.row) {
        YFAutoTransViewController * autoTransVC = [[YFAutoTransViewController alloc] init];
        
        [self.navigationController pushViewController: autoTransVC animated: YES];
    }
}

@end
