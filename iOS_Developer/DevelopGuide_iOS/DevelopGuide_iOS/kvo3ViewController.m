//
//  kvo3ViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import "kvo3ViewController.h"


@implementation kvo3
@synthesize name;
@synthesize num;
@end

@interface kvo3ViewController ()

@end

@implementation kvo3ViewController
@synthesize k3;

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
    k3 = [[kvo3 alloc] init];
    k3.name = @"k33";
    k3.num = @"33333333333333";
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
                       change:(NSDictionary *)change context:(void *)context
{
    
    NSLog(@"chang is %@",change);
    
    if([keyPath isEqualToString:@"name"])
    {
        NSString *newv = [change objectForKey:@"new"];
        [k3 setValue:newv forKey:@"name"];
    }
    
    if([keyPath isEqualToString:@"num"])
    {
        NSString *newv = [change objectForKey:@"new"];
        [k3 setValue:newv forKey:@"num"];
    }
    
}


@end
