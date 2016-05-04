//
//  Kvo2ViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import "Kvo2ViewController.h"

@implementation kvo2
@synthesize name;
@synthesize num;
@end

@interface Kvo2ViewController ()

@end

@implementation Kvo2ViewController
@synthesize k2;

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
    k2 = [[kvo2 alloc] init];
    k2.name = @"k222";
    k2.num = @"22222222222222";
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
        [k2 setValue:newv forKey:@"name"];
    }
    
    if([keyPath isEqualToString:@"num"])
    {
        NSString *newv = [change objectForKey:@"new"];
        [k2 setValue:newv forKey:@"num"];
    }
    
}


@end
