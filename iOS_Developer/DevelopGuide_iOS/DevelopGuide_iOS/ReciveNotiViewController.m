//
//  ReciveNotiViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-7-15.
//
//

#import "ReciveNotiViewController.h"
#import "XMLViewController.h"
@interface ReciveNotiViewController ()

@end

@implementation ReciveNotiViewController

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
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reciNoti)
                                                 name:@"test test test"
                                               object:nil ];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) reciNoti
{
    NSLog(@"jidaotongzhi");
}

- (IBAction) actionNext :(id)sender
{
    XMLViewController *vc = [[XMLViewController alloc] init];
    [self.navigationController pushViewController:vc
                                         animated:YES];
    [vc release];
}

@end
