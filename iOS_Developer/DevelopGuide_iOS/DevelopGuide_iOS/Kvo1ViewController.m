//
//  Kvo1ViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import "Kvo1ViewController.h"
@implementation kvo1
@synthesize name;
@synthesize num;
@end

@interface Kvo1ViewController ()

@end

@implementation Kvo1ViewController
@synthesize k1;

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
    k1 = [[kvo1 alloc] init];
    k1.name = @"k1111";
    k1.num = @"11111111111";
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
        [k1 setValue:newv forKey:@"name"];
    }
    
    if([keyPath isEqualToString:@"num"])
    {
        NSString *newv = [change objectForKey:@"new"];
         [k1 setValue:newv forKey:@"num"];
    }

}

@end
