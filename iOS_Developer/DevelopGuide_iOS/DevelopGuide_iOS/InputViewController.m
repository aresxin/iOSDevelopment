//
//  InputViewController.m
//  Demo
//
//  Created by 张玺 on 12-11-25.
//  Copyright (c) 2012年 张玺. All rights reserved.
//

#import "InputViewController.h"


@implementation InputViewController





- (IBAction)confirm:(id)sender {
    //看这里
    [self sendObject:text.text];
    [self dismissModalViewControllerAnimated:YES];
}



















- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidUnload {
    [self setText:nil];
    [super viewDidUnload];
}

@end
