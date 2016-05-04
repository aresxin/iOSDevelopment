//
//  KvoMainController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import "KvoMainController.h"

@interface KvoMainController ()

@end

@implementation KvoMainController

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
	// Do any additional setup after loading the view.
   
    kC1 = [[Kvo1ViewController alloc] init];
    [self.view addSubview:kC1.view];
    NSLog(@"kc1 name is %@ num is %@",kC1.k1.name,kC1.k1.num);
    
    kC2 = [[Kvo2ViewController alloc] init];
    [self.view addSubview:kC2.view];

     NSLog(@"kc2 name is %@ num is %@",kC2.k2.name,kC2.k2.num);
    
    KC3 = [[kvo3ViewController alloc] init];
      [self.view addSubview:KC3.view];
     NSLog(@"kc3 name is %@ num is %@",KC3.k3.name,KC3.k3.num);
    
    
    
    // 测试button
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(0, 80, 80, 30)];
    [btn setBackgroundColor:[UIColor redColor]];
    [btn setTitle:@"ki change" forState:UIControlStateNormal];
    [btn addTarget:self
            action:@selector(action1)
  forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    [btn release];
    
    
    UIButton *btn1 = [[UIButton alloc] initWithFrame:CGRectMake(0, 120, 80, 30)];
    [btn1 setTitle:@"k2 change" forState:UIControlStateNormal];
      [btn1 setBackgroundColor:[UIColor yellowColor]];
    [btn1 addTarget:self
            action:@selector(action2)
  forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn1];
    [btn1 release];
    
    
    UIButton *btn3 = [[UIButton alloc] initWithFrame:CGRectMake(0, 160, 80, 30)];
    [btn3 setTitle:@"k3 change" forState:UIControlStateNormal];
     [btn3 setBackgroundColor:[UIColor blueColor]];
    [btn3 addTarget:self
             action:@selector(action3)
   forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn3];
    [btn3 release];

    
    
    // 设定观察关系
    [kC1.k1 addObserver:self forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [kC1.k1 addObserver:self forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];
    
    [kC1.k1 addObserver:self forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [kC1.k1 addObserver:self forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];

    
    
    
    [kC2.k2 addObserver:self forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [kC2.k2 addObserver:KC3 forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];
    [kC2.k2 addObserver:self forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [kC2.k2 addObserver:KC3 forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];

    
    
    [KC3.k3 addObserver:self forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [KC3.k3 addObserver:kC2 forKeyPath:@"name" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];
    [KC3.k3 addObserver:self forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld  context:NULL];
//    [KC3.k3 addObserver:kC2 forKeyPath:@"num" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:NULL];
}


-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
                       change:(NSDictionary *)change context:(void *)context
{
    NSLog(@"function is %@",NSStringFromSelector(_cmd));
    NSLog(@"chang is %@",change);
    NSLog(@"object is %@",object);
    
     NSString *newv = [change objectForKey:@"new"];
     NSString *oldv = [change objectForKey:@"old"];
    if ([newv compare:oldv] == 0)
    {
        return;
    }
    
    if([keyPath isEqualToString:@"name"])
    {
        NSString *newv = [change objectForKey:@"new"];
        [kC1.k1 setValue:newv forKey:@"name"];
        [kC2.k2 setValue:newv forKey:@"name"];
        [KC3.k3 setValue:newv forKey:@"name"];
    }
    
    if([keyPath isEqualToString:@"num"])
    {
        NSString *newv = [change objectForKey:@"new"];
        [kC1.k1 setValue:newv forKey:@"num"];
        [kC2.k2 setValue:newv forKey:@"num"];
        [KC3.k3 setValue:newv forKey:@"num"];
    }
     
}

- (void) action1
{
    kC1.k1.name = @"chang1nameend";
    kC1.k1.num = @"chang1numend";
    
    
    NSLog(@"kc1 name is %@ num is %@",kC1.k1.name,kC1.k1.num);
    NSLog(@"kc2 name is %@ num is %@",kC2.k2.name,kC2.k2.num);
    NSLog(@"kc3 name is %@ num is %@",KC3.k3.name,KC3.k3.num);

}

- (void) action2
{
    kC2.k2.name = @"chang2nameend";
    kC2.k2.num = @"chang2numend";
    
    
    NSLog(@"kc1 name is %@ num is %@",kC1.k1.name,kC1.k1.num);
    NSLog(@"kc2 name is %@ num is %@",kC2.k2.name,kC2.k2.num);
    NSLog(@"kc3 name is %@ num is %@",KC3.k3.name,KC3.k3.num);
}


- (void) action3
{
    KC3.k3.name = @"chang3nameend";
    KC3.k3.num  = @"chang3numend";
    
    
    NSLog(@"kc1 name is %@ num is %@",kC1.k1.name,kC1.k1.num);
    NSLog(@"kc2 name is %@ num is %@",kC2.k2.name,kC2.k2.num);
    NSLog(@"kc3 name is %@ num is %@",KC3.k3.name,KC3.k3.num);
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
