//
//  BlockTestViewController.m
//  DevelopGuide_iOS
//
//  Created by clay on 12-12-5.
//
//

#import "BlockTestViewController.h"
#import "InputViewController.h"

@interface BlockTestViewController ()

@end

@implementation BlockTestViewController

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


- (IBAction)edit:(id)sender {
    
    InputViewController *input = [[InputViewController alloc] initWithNibName:@"InputViewController" bundle:nil];
    [self presentModalViewController:input animated:YES];
    
    
    
    //看这里
    [input receiveObject:^(id object) {
        
        result.text = object;
        
    }];
    
    
//    [UIView animateWithDuration:0.2
//                     animations:^{
//                         
//                     } completion:^(BOOL finished){
//                         
//                     }];
}

//下面没用


@end
