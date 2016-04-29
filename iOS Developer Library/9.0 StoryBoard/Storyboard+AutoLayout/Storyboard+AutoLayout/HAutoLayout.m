//
//  HAutoLayout.m
//  Storyboard+AutoLayout
//
//  Created by yangjinxin on 15/2/5.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "HAutoLayout.h"
@interface HAutoLayout () {
    UILabel *autoLabel;
    
    UILabel *autoLabel2;
}

@end

@implementation HAutoLayout

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    autoLabel = [[UILabel alloc] init];
    autoLabel.backgroundColor = [UIColor redColor];
    [self.view addSubview:autoLabel];
    [autoLabel setTranslatesAutoresizingMaskIntoConstraints:NO];
    
    autoLabel2 = [[UILabel alloc] init];
    [self.view addSubview:autoLabel2];
    autoLabel2.text = @"1";
    autoLabel2.backgroundColor = [UIColor yellowColor];
    [autoLabel2 setTranslatesAutoresizingMaskIntoConstraints:NO];
}


- (IBAction)actionButton:(id)sender
{
   
    autoLabel2.text = [autoLabel2.text stringByAppendingString:@"123456"];
}

- (void) updateViewConstraints
{
    [super updateViewConstraints];
    
    NSDictionary *views = @{@"autoLabel":autoLabel,
                            @"autoLabel2":autoLabel2};
    
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-84-[autoLabel(==80@1000)]-(>=0)-|" options:0 metrics:nil views:views]];
    
    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-84-[autoLabel2(==80@1000)]-(>=0)-|" options:0 metrics:nil views:views]];
    
    
    
    // H
//    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-1-[autoLabel(>=30@1000)]-10-[autoLabel2(>=80@1000)]-10-|" options:0 metrics:nil views:views]];
    
     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-1-[autoLabel(>=30@1000)]-10-[autoLabel2(>=80@1000)]-10-|" options:0 metrics:nil views:views]];
    
    
//    NSLayoutConstraint *h = [NSLayoutConstraint  constraintWithItem:autoLabel
//                                                          attribute:NSLayoutAttributeWidth
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:autoLabel2
//                                                          attribute:NSLayoutAttributeWidth
//                                                         multiplier:0.75 constant:0];
//    //h.priority = 1000;
//    [self.view addConstraint:h];
//    
//    
//    
//    [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-10-[autoLabel]-10-[autoLabel2]-10-|" options:0 metrics:nil views:views]];
    
}

@end
