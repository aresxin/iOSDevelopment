//
//  ImageLayerViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-23.
//
//

#import "ImageLayerViewController.h"


@interface ImageLayerViewController ()

@end

@implementation ImageLayerViewController

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
    UIScrollView   *scrV  = [[UIScrollView alloc] initWithFrame:self.view.frame];
    scrV.minimumZoomScale = 1.0;
    scrV.maximumZoomScale = 8.0;
    scrV.backgroundColor = [UIColor blackColor];
    scrV.delegate        = self;
    [self.view addSubview:scrV];
    [scrV release];
    
    showV  = [[UIView alloc] initWithFrame:scrV.frame];
    showV.backgroundColor = [UIColor redColor];
    imageLayer = [[CAImageLayer alloc] init];
    imageLayer.frame = CGRectMake(0, 0, 320, 480);
    [showV.layer addSublayer:imageLayer];
    [imageLayer setNeedsDisplay];
    
    [scrV addSubview:showV];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return showV;
}
@end
