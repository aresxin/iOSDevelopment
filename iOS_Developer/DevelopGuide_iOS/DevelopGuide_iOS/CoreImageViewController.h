//
//  CoreImageViewController.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
/*
 iOS5新特性:强大的Core Image(教你做自己的美图秀秀))  
 iOS5给我们带来了很多很好很强大的功能和API。Core Image就是其中之一，它使我们很容易就能处理图片的各种效果，色彩啊，曝光啊，饱和度啊，变形啊神马的。
 可惜苹果一直没能完善官方文档,也没有推出示例代码,所以国内很多同学可能还没有开始使用。
 但国外的大神们已经证明这是个相当强悍的框架，不仅功能强大，而且可以直接使用GPU，效率奇高，甚至可以实时的对视频进行渲染。
 下面让我们来看看，如何具体使用它：
 首先你需要导入 CoreImage.framework 框架；进行Mac（不是iOS）开发的同学请导入 QuartzCore.framework 框架，包含在其中了。
 
 然后我们先来看看3个主要的类：
 CIContext：它与Core Graphics 和 OpenGL context类似，所有Core Image的处理流程都通过它来进行；
 CIImage：它用来存放图片数据，可以通过UIImage，图片文件或像素数据创建；
 CIFilter：通过它来定义过滤器的详细属性。
 
 CIContext有两种初始化方法，分别对应GPU和CPU
 
 // 创建基于GPU的CIContext对象
 context = [CIContext contextWithOptions: nil];
 // 创建基于CPU的CIContext对象
 context = [CIContext contextWithOptions: [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:kCIContextUseSoftwareRenderer]];
 
 
 一般采用第一种基于GPU的，因为效率要比CPU高很多，但是要注意的是基于GPU的CIContext对象无法跨应用访问。
 比如你打开UIImagePickerController要选张照片进行美化，如果你直接在UIImagePickerControllerDelegate的委托方法里调用CIContext对象进行处理，那么系统会自动将其降为基于CPU的，速度会变慢，所以正确的方法应该是在委托方法里先把照片保存下来，回到主类里再来处理。（代码里你将会看到）
 
 CIImage的初始化方法有很多，常用的也是2种：
 
 // 通过图片路径创建CIImage
 NSString *filePath = [[NSBundle mainBundle] pathForResource:@"image" ofType:@"png"];
 NSURL *fileNameAndPath = [NSURL fileURLWithPath:filePath];
 beginImage = [CIImage imageWithContentsOfURL:fileNameAndPath];
 
 // 通过UIImage对象创建CIImage
 UIImage *gotImage = ...;
 beginImage = [CIImage imageWithCGImage:gotImage.CGImage];
 
 
 
 CIFilter初始化：
 
 // 创建过滤器
 filter = [CIFilter filterWithName:@"CISepiaTone"];
 [filter setValue:beginImage forKey:kCIInputImageKey];
 [filter setValue:[NSNumber numberWithFloat:slideValue] forKey:@"inputIntensity"];
 
 第一行：指定使用哪一个过滤器，通过[CIFilter filterNamesInCategory: kCICategoryBuiltIn]能得到所有过滤器的列表
 第二行：指定需要处理的图片
 第三行：指定过滤参数，每个过滤器的参数都不一样，可以在官方文档里搜索“Core Image Filter Reference”查看
 
 得到过滤后的图片并输出：
 CIImage *outputImage = [filter outputImage];
 CGImageRef cgimg = [context createCGImage:outputImage fromRect:[outputImage extent]];
 UIImage *newImg = [UIImage imageWithCGImage:cgimg];    
 [imgV setImage:newImg];
 CGImageRelease(cgimg);
 
 第一行：通过[filter outputImage]可以得到过滤器输出的图片
 第二行：通过CIContext的方法createCGImage: fromRect:得到CGImage
 第三行：转化为UIImage，这样我们就可以跟据需要显示在界面上了
 
 至此一个过滤周期就完成了，简单来说分以下几个步骤：
 1 初始化CIContext，CIImage
 2 初始化CIFilter并设置参数
 3 得到输出的图片
 4 将图片转化成能显示的UIImage类型
 如果想一张图片有多种过滤效果就需要重复2，3两步，并且要将上一个过滤器输出的图片作为下一个过滤器的参数
 */

#import <UIKit/UIKit.h>
//#import <AssetsLibrary/AssetsLibrary.h>

@interface CoreImageViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>{
    IBOutlet UIImageView *imgV;
    IBOutlet UISlider *slider;
    IBOutlet UISlider *slider2;
    IBOutlet UISlider *slider3;
    
    CIContext *context;
    CIFilter *filter;
    CIFilter *filter2;
    CIFilter *filter3;
    CIImage *beginImage;

}
@property (nonatomic, retain) CIContext *context;
@property (nonatomic, retain) CIFilter *filter;
@property (nonatomic, retain) CIFilter *filter2;
@property (nonatomic, retain) CIFilter *filter3;
@property (nonatomic, retain) CIImage *beginImage;

- (IBAction)changeValue:(id)sender;
- (IBAction)changeValue2:(id)sender;
- (IBAction)changeValue3:(id)sender;

- (IBAction)loadPhoto:(id)sender;
- (IBAction)savePhoto:(id)sender;
- (IBAction)resetImage:(id)sender;

- (void)logAllFilters;

@end
