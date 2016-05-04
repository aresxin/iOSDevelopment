//
//  CoreImageViewController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CoreImageViewController.h"
#import <AssetsLibrary/AssetsLibrary.h>

@implementation CoreImageViewController
@synthesize context;
@synthesize filter;
@synthesize filter2;
@synthesize filter3;
@synthesize beginImage;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    // 打印所有过滤器信息
    [self logAllFilters];
    
    // 得到图片路径创建CIImage对象
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"image" ofType:@"png"];
    NSURL *fileNameAndPath = [NSURL fileURLWithPath:filePath];
    self.beginImage = [CIImage imageWithContentsOfURL:fileNameAndPath];
    
    // 创建基于GPU的CIContext对象
    self.context = [CIContext contextWithOptions: nil];
    
    // 创建基于CPU的CIContext对象
    //context = [CIContext contextWithOptions: [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:kCIContextUseSoftwareRenderer]];
    
    // 创建过滤器
    self.filter = [CIFilter filterWithName:@"CISepiaTone"];
    self.filter2 = [CIFilter filterWithName:@"CIHueAdjust"];
    self.filter3 = [CIFilter filterWithName:@"CIStraightenFilter"];
    
    // 设置界面
    slider.value = 0.0;
    slider2.minimumValue = -3.14;
    slider2.maximumValue = 3.14;
    slider2.value = 0.0;
    slider3.minimumValue = -3.14;
    slider3.maximumValue = 3.14;
    slider3.value = 0.0;
    imgV.image = [UIImage imageWithContentsOfFile:filePath];
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.toolbarHidden = YES;
}
- (void) viewWillDisappear:(BOOL)animated
{
    self.navigationController.toolbarHidden = NO;
    [super viewWillDisappear:animated];
}
- (void)logAllFilters {
    NSArray *properties = [CIFilter filterNamesInCategory:
                           kCICategoryBuiltIn];
    NSLog(@"FilterName:\n%@", properties);
    for (NSString *filterName in properties) {
        CIFilter *fltr = [CIFilter filterWithName:filterName];
        NSLog(@"%@:\n%@", filterName, [fltr attributes]);
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)changeValue:(id)sender
{
    slider2.value = 0.0;
    slider3.value = 0.0;
    float slideValue = slider.value;
    // 设置过滤器参数
    [filter setValue:beginImage forKey:kCIInputImageKey];
    [filter setValue:[NSNumber numberWithFloat:slideValue] forKey:@"inputIntensity"];
    
    // 得到过滤后的图片
    CIImage *outputImage = [filter outputImage];
    
    // 转换图片
    CGImageRef cgimg = [context createCGImage:outputImage fromRect:[outputImage extent]];
    UIImage *newImg = [UIImage imageWithCGImage:cgimg];    
    // 显示图片
    [imgV setImage:newImg];
    // 释放C对象
    CGImageRelease(cgimg);

}
- (IBAction)changeValue2:(id)sender
{
    slider.value = 0.0;
    slider3.value = 0.0;
    
    float slideValue = slider2.value;
    // 设置过滤器参数
    [filter2 setValue:beginImage forKey:kCIInputImageKey];
    [filter2 setValue:[NSNumber numberWithFloat:slideValue] forKey:@"inputAngle"];
    
    // 得到过滤后的图片
    CIImage *outputImage = [filter2 outputImage];
    // 转换图片
    CGImageRef cgimg = [context createCGImage:outputImage fromRect:[outputImage extent]];
    UIImage *newImg = [UIImage imageWithCGImage:cgimg];    
    // 显示图片
    [imgV setImage:newImg];
    // 释放C对象
    CGImageRelease(cgimg);

}
- (IBAction)changeValue3:(id)sender
{
    slider.value = 0.0;
    slider2.value = 0.0;
    
    float slideValue = slider3.value;
    // 设置过滤器参数
    [filter3 setValue:beginImage forKey:kCIInputImageKey];
    [filter3 setValue:[NSNumber numberWithFloat:slideValue] forKey:@"inputAngle"];
    
    // 得到过滤后的图片
    CIImage *outputImage = [filter3 outputImage];
    // 转换图片
    CGImageRef cgimg = [context createCGImage:outputImage fromRect:[outputImage extent]];
    UIImage *newImg = [UIImage imageWithCGImage:cgimg];    
    // 显示图片
    [imgV setImage:newImg];
    // 释放C对象
    CGImageRelease(cgimg);

}

- (IBAction)loadPhoto:(id)sender
{
    UIImagePickerController *pickerC = 
    [[UIImagePickerController alloc] init];
    pickerC.delegate = self;
    [self presentModalViewController:pickerC animated:YES];

}
- (IBAction)savePhoto:(id)sender
{
//    CIImage *saveToSave = [filter outputImage];
//    CGImageRef cgImg = [context createCGImage:saveToSave fromRect:[saveToSave extent]];
//    
//    ALAssetsLibrary* library = [[ALAssetsLibrary alloc] init];
//    [library writeImageToSavedPhotosAlbum:cgImg 
//                                 metadata:[saveToSave properties] 
//                          completionBlock:^(NSURL *assetURL, NSError *error) {
//                              CGImageRelease(cgImg);
//                          }];
}
- (IBAction)resetImage:(id)sender
{
    // 得到图片路径
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"image" ofType:@"png"];
    
    // 创建CIImage对象
    NSURL *fileNameAndPath = [NSURL fileURLWithPath:filePath];
    beginImage = [CIImage imageWithContentsOfURL:fileNameAndPath];
    
    // 设置界面
    slider.value = 0.0;
    slider2.value = 0.0;
    slider3.value = 0.0;
    imgV.image = [UIImage imageWithContentsOfFile:filePath];
}

#pragma mark UIImagePickerController Delegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info 
{
    [self dismissModalViewControllerAnimated:YES];
    
    UIImage *gotImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    beginImage = [CIImage imageWithCGImage:gotImage.CGImage];
    imgV.image = gotImage;
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker 
{
    [self dismissModalViewControllerAnimated:YES];
}

@end
