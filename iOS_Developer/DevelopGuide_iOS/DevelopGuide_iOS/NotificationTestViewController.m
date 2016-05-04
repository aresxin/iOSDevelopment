//
//  NotificationTestViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-7-15.
//
//

#import "NotificationTestViewController.h"
#import "ReciveNotiViewController.h"

@interface NotificationTestViewController ()

@end

@implementation NotificationTestViewController

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
    [NSTimer scheduledTimerWithTimeInterval:10
                                     target:self
                                   selector:@selector(postNotification)
                                   userInfo:nil
                                    repeats:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) postNotification
{
    for (int i = 0; i < 10; i++)
    {
        [[NSNotificationCenter  defaultCenter] postNotificationName:@"test test test"
                                                             object:nil
                                                           userInfo:nil];
    }
   
}

- (IBAction) actionNext :(id)sender
{
    ReciveNotiViewController *re = [[ReciveNotiViewController alloc] init];
    [self.navigationController pushViewController:re
                                         animated:YES];
    [re release];
}

@end
