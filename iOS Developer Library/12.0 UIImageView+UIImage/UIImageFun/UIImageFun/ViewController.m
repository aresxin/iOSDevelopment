//
//  ViewController.m
//  UIImageFun


#import "ViewController.h"
#import "Note.h"

@interface ViewController ()
{
    UIImage *img;
    UIImageView *iv;
    NSMutableArray *ivs;
}
@end
@implementation ViewController


// Part 1:

/*
- (void)viewDidLoad
{
    [super viewDidLoad];
    // (1) Creating a bitmap context, filling it with yellow as "background" color:
    CGSize size = CGSizeMake(self.view.bounds.size.width, self.view.bounds.size.height);
    UIGraphicsBeginImageContextWithOptions(CGSizeMake(size.width, size.height), YES, 0.0);
    [[UIColor yellowColor] setFill];
    UIRectFill(CGRectMake(0, 0, size.width, size.height));
    // (2) Create a circle via a bezier path and stroking+filling it in the bitmap context:
    UIBezierPath *bezierPath = [UIBezierPath bezierPathWithArcCenter:CGPointMake(size.width/2, size.height/2) radius:140 startAngle:0 endAngle:2 * M_PI clockwise:YES];
    [[UIColor blackColor] setStroke];
    bezierPath.lineWidth = 5.0;
    [bezierPath stroke];
    [[UIColor redColor] setFill];
    [bezierPath fill];
    // (3) Creating an array of images:
    NSArray *rocks = @[[UIImage imageNamed:@"rock1"],
                       [UIImage imageNamed:@"rock2"],
                       [UIImage imageNamed:@"rock3"],
                       [UIImage imageNamed:@"rock4"],
                       [UIImage imageNamed:@"rock5"],
                       [UIImage imageNamed:@"rock6"],
                       [UIImage imageNamed:@"rock7"],
                       [UIImage imageNamed:@"rock8"],
                       [UIImage imageNamed:@"rock9"]];
    // (4) Drawing rocks in a loop, each chosen randomly from the image set and drawn at a random position in a circular pattern:
    for ( int i = 0; i < 100; i++)
    {
        int idx = arc4random() % rocks.count;
        NSLog(@"idx = %d", idx);
        int radius = 100;
        int revolution = 360;
        float r = (float)(arc4random() % radius);
        float angle = (float)(arc4random() % revolution);
        float x = size.width/2 + r * cosf(angle * M_PI/180.0);
        float y = size.height/2 + r * sinf(angle * M_PI/180.0);
        CGSize rockSize = ((UIImage *)rocks[idx]).size;
        [rocks[idx] drawAtPoint:CGPointMake(x-rockSize.width/2, y-rockSize.height/2)];
    }
    // (5) Deriving a new UIImage instance from the bitmap context:
    UIImage *fImg = UIGraphicsGetImageFromCurrentImageContext();
    // (6) Closing the context:
    UIGraphicsEndImageContext();
    // (7) Setting the image view's image property to the created image, and displaying
    iv = [[UIImageView alloc] initWithImage:fImg];
    [self.view addSubview:iv];
}
 */

// Part 2:
/*

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSString *text1 = @"Hi!";
    NSString *text2 = @"I size myself according to my content!";
    NSString *text3 = @"Standard boring random text: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    UIImage *noteChrome = [UIImage imageNamed:@"squeezednote"];
    UIEdgeInsets edgeInsets = UIEdgeInsetsMake(37, 12, 12, 12);
    Note *note1 = [[Note alloc] initWithText:text1 fontSize:25.0 noteChrome:noteChrome edgeInsets:edgeInsets maximumWidth:300 topLeftCorner:CGPointMake(10, 10)];
    Note *note2 = [[Note alloc] initWithText:text2 fontSize:30.0 noteChrome:noteChrome edgeInsets:edgeInsets maximumWidth:300 topLeftCorner:CGPointMake(200, 10)];
    Note *note3 = [[Note alloc] initWithText:text3 fontSize:16.0 noteChrome:noteChrome edgeInsets:edgeInsets maximumWidth:300 topLeftCorner:CGPointMake(10, 200)];
    [self.view addSubview:note1.noteView];
    [self.view addSubview:note2.noteView];
    [self.view addSubview:note3.noteView];
}

 */

// Part 3:

- (void)viewDidLoad
{
    [super viewDidLoad];
    ivs = [NSMutableArray array];
    img = [UIImage animatedImageNamed:@"explosion" duration:2.0];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(explosion:)];
    [self.view addGestureRecognizer:tap];
}


- (void)explosion:(UITapGestureRecognizer *)t
{
    CGPoint loc = [t locationInView:self.view];
    
    for (UIImageView *v in ivs)
    {
        if ([v pointInside:[v convertPoint:loc fromView:self.view] withEvent:nil])
        {
            [ivs removeObject:v];
            [v removeFromSuperview];
            return;
        }
    }
    UIImageView *v = [[UIImageView alloc] initWithImage:img];
    v.center = loc;
    [ivs addObject:v];
    [self.view addSubview:v];
}
@end
