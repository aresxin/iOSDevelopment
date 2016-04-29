//
//  ViewController.m
//  Storyboard+AutoLayout
//
//  Created by yangjinxin on 15/2/5.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () {
    UILabel *autoLabel;
    
    UILabel *autoLabel2;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    autoLabel = [[UILabel alloc] init];
    autoLabel.backgroundColor = [UIColor redColor];
    [self.view addSubview:autoLabel];
    [autoLabel setTranslatesAutoresizingMaskIntoConstraints:NO];
    
    autoLabel2 = [[UILabel alloc] init];
    [self.view addSubview:autoLabel2];
    autoLabel2.backgroundColor = [UIColor yellowColor];
    [autoLabel2 setTranslatesAutoresizingMaskIntoConstraints:NO];
}




- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) updateViewConstraints
{
    [super updateViewConstraints];
    
    NSDictionary *views = @{@"autoLabel":autoLabel,
                            @"autoLabel2":autoLabel2};
    
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-10-[autoLabel]-10-|" options:0 metrics:nil views:views]];
    
     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-10-[autoLabel2]-10-|" options:0 metrics:nil views:views]];
    
//    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-64-[autoLabel(>=172@900)]-10-[autoLabel2(>=300@750)]-44-|" options:0 metrics:nil views:views]];
//    
    
//     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-64-[autoLabel(==162@100)]-(<=254@1000)-|" options:0 metrics:nil views:views]];
//    
//     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-(<=236@750)-[autoLabel2(==200@200)]-44-|" options:0 metrics:nil views:views]];
    
    
    
    
    NSLayoutConstraint *h = [NSLayoutConstraint  constraintWithItem:autoLabel
                                  attribute:NSLayoutAttributeHeight
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:autoLabel2
                                  attribute:NSLayoutAttributeHeight
                                                         multiplier:0.75 constant:0];
    //h.priority = 1000;
    [self.view addConstraint:h];
    
    
    
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-64-[autoLabel]-10-[autoLabel2]-44-|" options:0 metrics:nil views:views]];

}

@end
