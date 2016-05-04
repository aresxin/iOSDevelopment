//
//  SEImage.m
//  TimerTest
//  Author：seven	
//  Created by seven on 08-9-17.
//  Copyright 2008 sz. All rights reserved.
//

#import "SEImage.h"


@implementation SEImage

+ (void) drawImage:(CGContextRef)context Image:(CGImageRef)aImage 
              Rect:(CGRect)rect
{
    //CGContextRetain(context);
    CGContextScaleCTM(context, 1, -1);
    CGContextTranslateCTM(context, 0, -rect.size.height);
    CGContextDrawImage(context, rect, aImage);
    //CGContextRelease(context);
}

+(void)drawImage:(CGContextRef) context
		   Image:(CGImageRef)aImage
		 AtPoint:(CGPoint)aPoint
{
	CGRect imageRect;
	imageRect.origin = aPoint;
	imageRect.size = CGSizeMake(CGImageGetWidth(aImage), CGImageGetHeight(aImage));
	CGContextDrawImage(context, imageRect, aImage);
}

+(void)drawImage:(CGContextRef) context
		   Image:(CGImageRef)aImage
		 AtPoint:(CGPoint)aPoint
		   FlipX:(BOOL)aFlipX
{
	if(aFlipX)
	{
		[SEImage drawImage:context Image:aImage AtPoint:aPoint Zoom:1.0 FlipX:aFlipX];
	}else{
		[SEImage drawImage:context Image:aImage AtPoint:aPoint];
	}
}



+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
			Zoom:(float)aZoom
		   FlipX:(BOOL)aFlipX
{
	CGContextSaveGState(context);
	
	CGAffineTransform aT = CGAffineTransformMakeTranslation(aPoint.x,aPoint.y);
	
	if(aFlipX)
	{
		aT = CGAffineTransformScale(aT, -aZoom, aZoom);
		CGContextConcatCTM(context, aT); 
	
		[SEImage drawImage:context Image:aImage AtPoint:CGPointMake(0.0-CGImageGetWidth(aImage),0.0)];
		
	}
	else{
		aT = CGAffineTransformScale(aT, aZoom, aZoom);
		CGContextConcatCTM(context, aT); 
		
		[SEImage drawImage:context Image:aImage AtPoint:CGPointMake(0.0,0.0)];
		
	}
	
		
	CGContextRestoreGState(context);
	
}

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
			Zoom:(float)aZoom
{
	[SEImage drawImage:context Image:aImage AtPoint:aPoint Zoom:aZoom FlipX:FALSE];
}

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
		   FlipX:(BOOL)aFlipX
{
	if(aFlipX)
	{
		[SEImage drawImage:context Image:aImage AtPoint:aPoint RolateAtPoint:aRolatePoint Rolate:aRolate Zoom:1.0 FlipX:TRUE];
	}else{
		[SEImage drawImage:context Image:aImage AtPoint:aPoint RolateAtPoint:aRolatePoint Rolate:aRolate];
	}
}



+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
{
	CGContextSaveGState(context);
	
	CGAffineTransform aT = CGAffineTransformMakeTranslation(aPoint.x+aRolatePoint.x, aPoint.y+aRolatePoint.y);
	aT = CGAffineTransformRotate(aT, aRolate*M_PI/180);
	CGContextConcatCTM(context, aT); 
	
	[SEImage drawImage:context Image:aImage AtPoint:CGPointMake(-aRolatePoint.x,-aRolatePoint.y)];
	
	CGContextRestoreGState(context);
}

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
			Zoom:(float)aZoom
		   FlipX:(BOOL)aFlipX
{
	CGContextSaveGState(context);
	
	CGAffineTransform aT = CGAffineTransformMakeTranslation(aPoint.x+aRolatePoint.x, aPoint.y+aRolatePoint.y);
	aT = CGAffineTransformRotate(aT, aRolate*M_PI/180);
	if(aFlipX)
	{
		aT = CGAffineTransformScale(aT, -aZoom, aZoom);
	}
	else{
		aT = CGAffineTransformScale(aT, aZoom, aZoom);
	}
	CGContextConcatCTM(context, aT); 
	
	[SEImage drawImage:context Image:aImage AtPoint:CGPointMake(-aRolatePoint.x,-aRolatePoint.y)];
	
	CGContextRestoreGState(context);
}

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
			Zoom:(float)aZoom
{
	[SEImage drawImage:context Image:aImage AtPoint:aPoint RolateAtPoint:aRolatePoint Rolate:aRolate Zoom:aZoom FlipX:FALSE];
}


//grid

+(void)drawGrid:(CGContextRef) context
	   DrawRect:(CGRect)aRect
	   GridSize:(CGSize)aSize
{
	float i;
	float amx = aRect.origin.x + aRect.size.width;
	float amy = aRect.origin.y + aRect.size.height;
	for(i = aRect.origin.x; i < amx; i+=aSize.width)
	{
		CGContextMoveToPoint(context, i, 0);
		CGContextAddLineToPoint(context, i, amy);
	}
	
	for(i = aRect.origin.y; i < amy; i+=aSize.height)
	{
		CGContextMoveToPoint(context, 0, i);
		CGContextAddLineToPoint(context, amx, i);
	}
	
	CGContextStrokePath(context);
}

+(NSDictionary*)SeparateImage:(UIImage*)image ByX:(int)x andY:(int)y cacheQuality:(float)quality
{
	
	//kill errors
	if (x<1) {
		NSLog(@"illegal x!");
		return nil;
	}else if (y<1) {
		NSLog(@"illegal y!");
		return nil;
	}
	if (![image isKindOfClass:[UIImage class]]) {
		NSLog(@"illegal image format!");
		return nil;
	}
	
	//attributes of element
	float _xstep=image.size.width*1.0/(y+1);
	float _ystep=image.size.height*1.0/(x+1);
	NSMutableDictionary*_mutableDictionary=[[[NSMutableDictionary alloc]initWithCapacity:1]autorelease];
	//NSArray*_array=[imageName componentsSeparatedByString:@"."];
	//NSString*prefixName=[_array objectAtIndex:0];
	NSString*prefixName=@"win";
	
	//snap in context and create element image view
	for (int i=0; i<x; i++) 
	{
		for (int j=0; j<y; j++) 
		{
			CGRect rect=CGRectMake(_xstep*j, _ystep*i, _xstep, _ystep);
			CGImageRef imageRef=CGImageCreateWithImageInRect([image CGImage],rect);
			UIImage* elementImage=[UIImage imageWithCGImage:imageRef];
			UIImageView*_imageView=[[UIImageView alloc] initWithImage:elementImage];
			_imageView.frame=rect;
			NSString*_imageString=[NSString stringWithFormat:@"%@_%d_%d.jpg",prefixName,i,j];
			[_mutableDictionary setObject:_imageView forKey:_imageString];
			//CFRelease(imageRef);
			
			if (quality<=0) 
			{
				continue;
			}
			quality=(quality>1)?1:quality;
			NSString*_imagePath=[NSHomeDirectory() stringByAppendingPathComponent:_imageString];
			NSData* _imageData=UIImageJPEGRepresentation(elementImage, quality);
			[_imageData writeToFile:_imagePath atomically:NO];
		}
	}
	//return dictionary including image views
	NSDictionary*_dictionary=_mutableDictionary;
	return _dictionary;
}

// add by clay start
/*压缩图片的方法，会在指定目录生成一张压缩图片：
 compression压缩质量，0-1
 orientation图片的方向
 */
+ (NSData *) getCompressionImageToFileName:(NSString *)fileName
                               compression:(float)com
                               orientation:(UIImageOrientation)ori
                              writeCGImage:(CGImageRef)image
{
    if (fileName == nil || image == NULL)
    {
        return nil;
    }
    
    // 1.0 创建图片压缩后生成的路径
    NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)
                                    objectAtIndex:0];
    NSString *imagePath = [documentsDirectory stringByAppendingPathComponent:fileName];
    NSURL *imagePathUrl = [NSURL fileURLWithPath:imagePath];
    
    // 2.0 设置图片压缩质量，方向
    float compression = com; // Lossless compression if available.
    int orientation; // Origin is at bottom, left.
    UIImageOrientation orient = ori;
    switch(orient)
    {
        case UIImageOrientationUp: //EXIF = 1
        {
            orientation = 1;
            break;
        }
        case UIImageOrientationUpMirrored: //EXIF = 2
        {
            
            orientation = 2;
            break;
        }
        case UIImageOrientationDown: //EXIF = 3
        {
            orientation = 3;
            break;
        }
        case UIImageOrientationDownMirrored: //EXIF = 4
        {
            orientation = 4;
            break;
        }
        case UIImageOrientationLeftMirrored: //EXIF = 5
        {
            orientation = 5;
            break;
        }
        case UIImageOrientationLeft: //EXIF = 6
        {
            orientation = 6;
            break;
        }
        case UIImageOrientationRightMirrored: //EXIF = 7
        {
            orientation = 7;
            break;
        }
        case UIImageOrientationRight: //EXIF = 8
        {
            orientation = 8;
            break;
        }
        default:
        {
            [NSException raise:NSInternalInconsistencyException format:@"Invalid image orientation"];
            break;
        }
    }
    
    
    CFStringRef myKeys[3];
    CFTypeRef   myValues[3];
    CFDictionaryRef myOptions = NULL;
    // 图片方向的设定
    myKeys[0] = kCGImagePropertyOrientation;
    myValues[0] = CFNumberCreate(NULL, kCFNumberIntType, &orientation);
    
    myKeys[1] = kCGImagePropertyHasAlpha;
    myValues[1] = kCFBooleanTrue;
    
    //图片压缩质量的设定
    myKeys[2] = kCGImageDestinationLossyCompressionQuality;
    myValues[2] = CFNumberCreate(NULL, kCFNumberFloatType, &compression);
    
    // 3.0 创建图片属性字典
    myOptions = CFDictionaryCreate( NULL, (const void **)myKeys, (const void **)myValues, 3,
                                   &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    // 4.0 创建图片目标
    CGImageDestinationRef myImageDest = CGImageDestinationCreateWithURL((CFURLRef)imagePathUrl, CFSTR("public.jpeg"), 1,
                                                                        NULL);
    // 5.0 根据图片属性字典生成图片
    CGImageDestinationAddImage(myImageDest, image, myOptions);
    
    // 6.0 释放
    CGImageDestinationFinalize(myImageDest);
    CFRelease(myImageDest);
    
    NSData *imageData = [NSData dataWithContentsOfFile:imagePath];
    return imageData;
}
// add by clay end


/*
 通过图片文件路径，初始化图片，初始化是可以指定生成CGImageRef的方向，质量等
 */
CGImageRef MyCreateCGImageFromFile (NSString* path ,float pCompression,int pOrientation)
{
    
    
    // Get the URL for the pathname passed to the function.
    NSURL *url = [NSURL fileURLWithPath:path];
    CGImageRef        myImage = NULL;
    CGImageSourceRef  myImageSource;
    
    
    float compression = 0.35; // Lossless compression if available.
    int orientation = 4; // Origin is at bottom, left.
    CFStringRef myKeys[3];
    CFTypeRef   myValues[3];
    CFDictionaryRef myOptions = NULL;
    myKeys[0] = kCGImagePropertyOrientation;
    myValues[0] = CFNumberCreate(NULL, kCFNumberIntType, &orientation);
    
    myKeys[1] = kCGImagePropertyHasAlpha;
    myValues[1] = kCFBooleanTrue;
    
    myKeys[2] = kCGImageDestinationLossyCompressionQuality;
    myValues[2] = CFNumberCreate(NULL, kCFNumberFloatType, &compression);
    
    myOptions = CFDictionaryCreate( NULL, (const void **)myKeys, (const void **)myValues, 3,
                                   &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    
    
    
    // Create an image source from the URL.
    myImageSource = CGImageSourceCreateWithURL((CFURLRef)url, myOptions);
    CFRelease(myOptions);
    // Make sure the image source exists before continuing
    if (myImageSource == NULL){
        fprintf(stderr, "Image source is NULL.");
        return  NULL;
    }
    
    // Create an image from the first item in the image source.
    myImage = CGImageSourceCreateImageAtIndex(myImageSource,
                                              0,
                                              NULL);
    
    CFRelease(myImageSource);
    // Make sure the image exists before continuing
    if (myImage == NULL){
        fprintf(stderr, "Image not created from image source.");
        return NULL;
    }
    
    return myImage;
}


/*
 获得CGContextRef，设定压缩质量，dpi等存储到指定路径
 */
+ (void) saveImage:(CGContextRef) bitmap
              path:(NSString *)strpath
              type:(int)formattype
               dpi:(int)ndpi
{
    CGImageRef imageRef = CGBitmapContextCreateImage(bitmap);
    if (imageRef == NULL) {
        CGImageRelease(imageRef);
        //CGContextRelease(bitmap);
        return ;
    }
    
    NSString *finalPath = [NSString stringWithString:strpath];
    CFURLRef url = CFURLCreateWithFileSystemPath (
                                                  kCFAllocatorDefault,
                                                  (CFStringRef)finalPath,
                                                  kCFURLPOSIXPathStyle,
                                                  false);
    CGImageDestinationRef dest = NULL;
    if (formattype == 0) {
        // 创建目标图片的类型路径
        dest = CGImageDestinationCreateWithURL(url, CFSTR("public.jpeg"), 1, NULL);
        assert(dest);
        
        
        CFMutableDictionaryRef  mSaveMetaAndOpts = CFDictionaryCreateMutable(nil, 0,
                                                                             &kCFTypeDictionaryKeyCallBacks,  &kCFTypeDictionaryValueCallBacks);
        
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImageDestinationLossyCompressionQuality,
                             [NSNumber numberWithFloat:0.8]);
        
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIHeight,
                             [NSNumber numberWithInteger:ndpi]);
        
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIWidth,
                             [NSNumber numberWithInteger:ndpi]);
        // 像目标路径添加图片
        CGImageDestinationAddImage(dest, imageRef, (CFDictionaryRef)mSaveMetaAndOpts);
        CFRelease(mSaveMetaAndOpts);
        //CGImageDestinationAddImage(dest, imageRef, NULL);
        assert(dest);
        if (dest == NULL) {
            NSLog(@"CGImageDestinationCreateWithURL failed");
        }
        //NSLog(@"%@", dest);
        assert(CGImageDestinationFinalize(dest));
        //这三句话用来释放对象
        CFRelease(dest);
        //CGImageRelease(imageRef);
        //CFRetain(url);
        CFRelease(url);
    }
    else if (formattype == 1)
    {
        dest = CGImageDestinationCreateWithURL(url, CFSTR("public.tiff"), 1, NULL);
        assert(dest);
        
        CFMutableDictionaryRef  mSaveMetaAndOpts = CFDictionaryCreateMutable(nil, 0,
                                                                             &kCFTypeDictionaryKeyCallBacks,  &kCFTypeDictionaryValueCallBacks);
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIHeight,
                             [NSNumber numberWithInteger:ndpi]);
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIWidth,
                             [NSNumber numberWithInteger:ndpi]);
        CGImageDestinationAddImage(dest, imageRef, (CFDictionaryRef)mSaveMetaAndOpts);
        assert(dest);
        if (dest == NULL) {
            NSLog(@"CGImageDestinationCreateWithURL failed");
        }
        //NSLog(@"%@", dest);
        assert(CGImageDestinationFinalize(dest));
        //这三句话用来释放对象
        CFRelease(dest);
        //CGImageRelease(imageRef);
        //CFRetain(url);
        CFRelease(url);
    }
    else {
        dest = CGImageDestinationCreateWithURL(url, CFSTR("public.png"), 1, NULL);
        assert(dest);
        
        CFMutableDictionaryRef  mSaveMetaAndOpts = CFDictionaryCreateMutable(nil, 0,
                                                                             &kCFTypeDictionaryKeyCallBacks,  &kCFTypeDictionaryValueCallBacks);
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIHeight,
                             [NSNumber numberWithInteger:ndpi]);
        CFDictionarySetValue(mSaveMetaAndOpts, kCGImagePropertyDPIWidth,
                             [NSNumber numberWithInteger:ndpi]);
        CGImageDestinationAddImage(dest, imageRef, (CFDictionaryRef)mSaveMetaAndOpts);
        CGImageDestinationAddImage(dest, imageRef, NULL);
        assert(dest);
        if (dest == NULL) {
            NSLog(@"CGImageDestinationCreateWithURL failed");
        }
        //NSLog(@"%@", dest);
        assert(CGImageDestinationFinalize(dest));
        //这三句话用来释放对象
        CFRelease(dest);
        //CGImageRelease(imageRef);
        //CFRetain(url);
        CFRelease(url);
    }
    
    CGImageRelease(imageRef);
    CGContextFlush(bitmap);
}



//大图片的分割描画
+ (void) incrementallyLoadingImage:(NSString *)filePath
{
    //
    
    NSData *data = [NSData dataWithContentsOfFile:filePath];
    NSInteger length = [data length];
    NSRange rang1 =  NSMakeRange(0, length/2);
    NSRange rang2 =  NSMakeRange(length/2 , length/2);
    
    NSData *data1 = [data subdataWithRange:rang1];
    NSData *data2 = [data subdataWithRange:rang2];
    
    NSArray *arra = [NSArray arrayWithObjects:data1,data2, nil];
    // 用于放image data
    NSMutableData *imageData  = [[NSMutableData alloc] init];
    
    CGImageSourceRef imageSource = CGImageSourceCreateIncremental(NULL);
    
    //for (int i = 0 ; i < 10; i++)
    //{
        //
        [imageData appendData:nil];
        
        
        CGImageSourceUpdateData(imageSource,(CFDataRef)data , YES);
        
        CGImageSourceStatus  imageSourceStatus =  CGImageSourceGetStatusAtIndex(imageSource, 0);
        
        if (imageSourceStatus == kCGImageStatusComplete)
        {
            // Create the image
            CGImageRef partialImageRef = CGImageSourceCreateImageAtIndex(imageSource, 0, NULL);
        }
   // }
    
    CFRelease(imageSource);
}

@end
