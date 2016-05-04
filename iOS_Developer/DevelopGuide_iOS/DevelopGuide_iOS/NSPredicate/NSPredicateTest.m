//
//  NSPredicateTest.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-7-5.
//
//

#import "NSPredicateTest.h"

@interface NSPredicateTest ()

@end

@implementation NSPredicateTest

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
    //[self test1];
    [self test2];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) test1//对NSArray进行过滤
{
    NSArray *array = [[NSArray alloc]initWithObjects:@"beijing",@"shanghai",@"guangzou",@"wuhan", nil];
    NSString *string = @"ang";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF CONTAINS %@",string];
    NSLog(@"%@",[array filteredArrayUsingPredicate:pred]); //SELF代表array本身
}

- (void) test2 
{
    NSMutableArray* oldPaths = [[NSMutableArray alloc] init];
    [oldPaths addObject:@"a"];
    [oldPaths addObject:@"b"];
    [oldPaths addObject:@"c"];
    [oldPaths addObject:@"4"];
    
    NSMutableArray* newPaths = [[NSMutableArray alloc] init];
    [newPaths addObject:@"a"];
    [newPaths addObject:@"b"];
    [newPaths addObject:@"c"];
    [newPaths addObject:@"d"];
    
    // 过滤newPath的元素在oldPaths中不存在的
    NSPredicate* thePreDicate = [NSPredicate predicateWithFormat:@"NOT (SELF in %@)", newPaths];
    [oldPaths filterUsingPredicate:thePreDicate];
    
    for (int i = 0; i < [oldPaths count]; i++)
    {
        NSString *str = [oldPaths objectAtIndex:i];
        NSLog(@"str is %@",str);
    }

}
@end
