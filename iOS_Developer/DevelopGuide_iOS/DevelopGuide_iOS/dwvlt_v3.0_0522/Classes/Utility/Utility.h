/*
 *  Utility.h
 *  DWViewer
 *
 *  Created by tongjo on 10-11-14.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *	
 */

#import <CoreGraphics/CoreGraphics.h>
#import <sys/utsname.h>

#ifndef UTILTY_H
#define UTILTY_H

#define  UI_ACTIVITY_VIEW_TAG   2002
// Define common setting and method in this class.
class Utility
{
public:
	
#pragma mark -
#pragma mark constant
	
	// More view will need more memory!
	// But 3 is least size, we need at last 3 view when change page.
	// If change this value, please use singular. 
	static const int INIT_VIEW_COUNT;

	// PageFit scale * 1
	static const float MIN_SCALE;

	// PageFit scale * 4
	static const float MAX_SCALE;
	
	// 75
	static const int DW_DEFAULT_DPI;
    
    // liuqw 20110622 start
    // AR NO.17847 の対応
    static const int DW_IPAD_DPI;
    static const int DW_IPHONE_DPI;
    // liuqw 20110622 end

	// 1.0
	static const float DEFAULT_DEVICE_SCALE_FACTOR;
	
	// For higher resolution.
	// NO useing for V4, get this value from UIView's contentScaleFactor.
	static float CURR_DEVICE_SCALE_FACTOR;
	
	// back ground's cloor
	static const float BACK_GROUND_WHITE_COLOR;
	static const float BACK_GROUND_GRAY_COLOR;
	
	// file list 500 limit message font size. add by lixin 20101220
	static const int IPHONE_LIMIT_UI_FONT_SIZE;
	static const int IPAD_LIMIT_UI_FONT_SIZE;
	
	// FileSort の対応 start
	static const int IPHONE_LIMIT_UI_FONT_ATTRIBUTESIZE;
	static const int IPAD_LIMIT_UI_FONT_ATTRIBUTESIZE;
	// FileSort の対応 end
    
    // 「拡大操作の基準の変更」の対応 start
    static const int MAX_SPECIFY_SCALE;
    // 「拡大操作の基準の変更」の対応 end
	
	// lixin 20110821 DW_iPhoneViewer_20 start	
	// annotation property default setting
	/*
	static const UIColor* DEFAULT_COLOR_FREEHAND;
	static const int      DEFAULT_LINESIZE_FREEHAND;
	static const UIColor* DEFAULT_COLOR_NOTEPAD;
	static const UIColor* DEFAULT_FONTCOLOR_NOTEPAD;
	static const int      DEFAULT_FONTSIZE_NOTEPAD;
	 */
	static UIColor* DEFAULT_COLOR_FREEHAND;
	static const int      DEFAULT_LINESIZE_FREEHAND;
	
	//  wangpp 2012.2.28 start
    // freehand transparent
    static const BOOL DEFAULT_TRANSPARENT_FREEHAND;
    //  wangpp 2012.2.28 end
	
	static UIColor* DEFAULT_COLOR_NOTEPAD;
	static UIColor* DEFAULT_FONTCOLOR_NOTEPAD;
	static const int      DEFAULT_FONTSIZE_NOTEPAD;
	
	// wangpp 2012.4.13 start
	// login
	static const int DEFAULT_INDEX_LOGIN;
	// wangpp 2012.4.13 end
	
	// DW_iPhoneViewer_20 end
#pragma mark -
#pragma mark Utility method	
	
	static float GetDeviceScaleFactor()
	{
		// For V4 
		//return CURR_DEVICE_SCALE_FACTOR;
		return DEFAULT_DEVICE_SCALE_FACTOR;
	}
	
	static void UpdateDeviceScaleFactor(float factor)
	{
		CURR_DEVICE_SCALE_FACTOR = factor;
	}
	
	static double MMToPixel(double mm)
	{
        // liuqw 20110622 start
        // AR NO.17847 の対応
        
		//return mm * Utility::DW_DEFAULT_DPI / 254000.0;
        return mm * Utility::GetDeviceDPI() / 254000.0;
        
        // liuqw 20110622 end
	}
	
	static double MMToPixelWithScale(double mm, double scale)
	{
		return MMToPixel(mm) * scale;
	}

	static double MMToPixelWithScaleAndScaleFactor(double mm, double scale)
	{

		return MMToPixelWithScale(mm, scale) * Utility::GetDeviceScaleFactor();
	}
	
	static double PixelToMM(double pixel)
	{
        // liuqw 20110622 start
        // AR NO.17847 の対応
        
		//return pixel * 254000 / Utility::DW_DEFAULT_DPI;
        return pixel * 254000 / Utility::GetDeviceDPI();
        
        // liuqw 20110622 end
	}
	
	static double PixelToMMWithScale(double pixel, double scale)
	{
		return PixelToMM(pixel) / scale;
	}


	//
	// 2012.02.01(Ver2.1 New) M.Chikyu
	//
	static float MMToPixel_F(float mm)
	{
        return mm * Utility::GetDeviceDPI() / 254000.0;
	}
	
	static float MMToPixelWithScale_F(float mm, float scale)
	{
		return MMToPixel_F(mm) * scale;
	}
	
	static float PixelToMM_F(float pixel)
	{
        return pixel * 254000 / Utility::GetDeviceDPI();
	}
	
	static float PixelToMMWithScale_F(float pixel, float scale)
	{
		return PixelToMM_F(pixel) / scale;
	}
	//
	// 2012.02.01(Ver2.1 New) M.Chikyu
	//

	
	static CGRect MakeRectWithScaleFactor( CGRect src)
	{
		return CGRectMake(src.origin.x		* Utility::GetDeviceScaleFactor(), 
						  src.origin.y		* Utility::GetDeviceScaleFactor(), 
						  src.size.width	* Utility::GetDeviceScaleFactor(), 
						  src.size.height	* Utility::GetDeviceScaleFactor());

	}
	
	enum PageMode {
		PAGE_MODE_NORMAL = 0,
		PAGE_MODE_FACE_NO,
		PAGE_MODE_FACE_YES,
		PAGE_MODE_NONE
	};
	
	// add by lixin 20110815 for edit toolbar
	// start DW_iPhoneViewer_20
	enum PROPERTY_TYPE {
		kFreehandColor = 0,
		kFreehandLine,
		
		// wangpp 2012.3.8 start 
		// freehand transparent
		kFreehandTransparent,
		// wangpp 2012.3.8 end
		
		kNotepadColor,
		kTextFontColor,
		kTextFontSize,
	};
	// end DW_iPhoneViewer_20
	static int TransformPageModeFromFaceNoToNormal( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		if( iCurrentPage < 0 ){
			return -1;
		}
		iPageIndex = iCurrentPage * 2;
		return iPageIndex;
	}
	
	static int TransformPageModeFromNormalToFaceNo( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		if( iCurrentPage < 0 ){
			return -1;
		}
		iPageIndex = iCurrentPage / 2;
		return iPageIndex;
	}
	
	static int TransformPageModeFromFaceYesToNormal( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		if( iCurrentPage < 0 ){
			return -1;
		}
		if( 0 == iCurrentPage ){
			iPageIndex = 0;
		}else{
			iPageIndex = iCurrentPage * 2 - 1;	
		}
		
		return iPageIndex;
	}
	
	static int TransformPageModeFromNormalToFaceYes( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		if( iCurrentPage < 0 ){
			return -1;
		}
		
		iPageIndex = iCurrentPage / 2 + iCurrentPage % 2;
		
		return iPageIndex;
	}
	
	static int TransformPageModeFromFaceNoToFaceYes( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		// to normal
		iPageIndex = iCurrentPage * 2;
		
		// to double2
		iPageIndex = iPageIndex / 2 + iPageIndex % 2;
		
		return iPageIndex;
	}
	
	static int TransformPageModeFromFaceYesToFaceNo( int iCurrentPage )
	{
		int iPageIndex = 0;
		
		// to normal
		if( 0 == iCurrentPage ){
			iPageIndex = 0;
		}else{
			iPageIndex = iCurrentPage * 2 - 1;	
		}
		
		// to double1
		iPageIndex = iPageIndex / 2;
		
		return iPageIndex;
	}
	
	static int TransformPageMode(int      iCurrentPage, 
								 PageMode fromPageMode, 
								 PageMode toPageMode)
	{
		int iPageIndex = 0;
		
		if( iCurrentPage < 0 ){
			return -1;
		}
		switch( fromPageMode ){
			case PAGE_MODE_NORMAL:
				switch( toPageMode ){
					case PAGE_MODE_NORMAL:
						iPageIndex = iCurrentPage;
						break;
					case PAGE_MODE_FACE_NO:
						iPageIndex = TransformPageModeFromNormalToFaceNo( iCurrentPage );
						break;
					case PAGE_MODE_FACE_YES:
						iPageIndex = TransformPageModeFromNormalToFaceYes( iCurrentPage );
						break;
					default:
						break;
				}
				break;
			case PAGE_MODE_FACE_NO:
				switch( toPageMode ){
					case PAGE_MODE_NORMAL:
						iPageIndex = TransformPageModeFromFaceNoToNormal( iCurrentPage );
						break;
					case PAGE_MODE_FACE_NO:
						iPageIndex = iCurrentPage;
						break;
					case PAGE_MODE_FACE_YES:
						iPageIndex = TransformPageModeFromFaceNoToFaceYes( iCurrentPage );
						break;
					default:
						break;
				}
				break;
			case PAGE_MODE_FACE_YES:
				switch( toPageMode ){
					case PAGE_MODE_NORMAL:
						iPageIndex = TransformPageModeFromFaceYesToNormal( iCurrentPage );
						break;
					case PAGE_MODE_FACE_NO:
						iPageIndex = TransformPageModeFromFaceYesToFaceNo( iCurrentPage );
						break;
					case PAGE_MODE_FACE_YES:
						iPageIndex = iCurrentPage;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		return iPageIndex;
	}
	
	// add by lixin 2010.11.27 check device type
	static BOOL UIDeviceIsiPad()
	{
        // 20110708 M.Chikyu start
        /*
		static  BOOL  isPad = false;
		
		NSString* model = [[UIDevice currentDevice] model];
		isPad = [model rangeOfString:@"iPad"].location != NSNotFound;
		
		return isPad;
        */
		
		static BOOL initCheck = NO;
		static BOOL isIPAD = NO;
		
		if (initCheck == NO)
		{
			NSString* model = [[UIDevice currentDevice] model];
			isIPAD = [model rangeOfString:@"iPad"].location != NSNotFound;
			initCheck = YES;
		}
		
		return isIPAD;
		
		// 20110708 M.Chikyu end
	}


	//
	// スクリーンサイズに対してメモリが少ないデバイス(iPad1)を判定
	//
	enum deviceName
	{
		ipod3g,
		ipod4g,
		iphone3gs,
		iphone4,
		ipad1,
		ipad2,
		other
	};

	static deviceName GetDeviceName()
	{
		static BOOL initCheck = NO;
		static deviceName devName = other;

		if (initCheck == NO)
		{
			struct utsname uts;
			uname(&uts);
			NSString* model = [NSString stringWithCString:uts.machine
												 encoding:NSUTF8StringEncoding];

			if ([model rangeOfString:@"iPod3"].location != NSNotFound)
			{
				devName = ipod3g;
			}

			if ([model rangeOfString:@"iPod4"].location != NSNotFound)
			{
				devName = ipod4g;
			}
			
			if ([model rangeOfString:@"iPhone2"].location != NSNotFound)
			{
				devName = iphone3gs;
			}
			
			if ([model rangeOfString:@"iPhone3"].location != NSNotFound)
			{
				devName = iphone4;
			}
			
			if ([model rangeOfString:@"iPad1"].location != NSNotFound)
			{
				devName = ipad1;
			}
			
			if ([model rangeOfString:@"iPad2"].location != NSNotFound)
			{
				devName = ipad2;
			}
			
			initCheck = YES;
		}

		return devName;
	}

	
	//
	// ページフィット時の倍率でスクリーンの倍率（解像度）を決定
	//

	// AR19007
	// 2012.02.20 M.Chikyu start.

	/*
	static float GetScreenScale(float coreScale)
	{
		float DEV_WAIT = UIDeviceIsiPad() ? 1.0 : 0.5;

		float scaleFactor = (100.0 / coreScale) * DEV_WAIT;

		switch (GetDeviceName())
		{
			case ipod3g:
				scaleFactor = scaleFactor < 6.0 ? scaleFactor : 6.0;
				break;
				
			case ipod4g:
				scaleFactor = scaleFactor < 4.0 ? scaleFactor : 4.0;
				break;
				
			case iphone3gs:
				scaleFactor = scaleFactor < 6.0 ? scaleFactor : 6.0;
				break;
				
			case iphone4:
				scaleFactor = scaleFactor < 4.0 ? scaleFactor : 4.0;
				break;
				
			case ipad1:
				scaleFactor = scaleFactor < 3.0 ? scaleFactor : 3.0;
				break;

			case ipad2:
				scaleFactor = scaleFactor < 4.0 ? scaleFactor : 4.0;
				break;
				
			default:
				scaleFactor = scaleFactor < 4.0 ? scaleFactor : 4.0;
				break;
		}

		return scaleFactor;
	}
	 */

	// はみ出し付箋との面積比で上限を超えないようにする
	static float GetScreenScale(float coreScale, float ratio)
	{
		float DEV_WAIT = UIDeviceIsiPad() ? 1.0 : 0.5;
		
		float scaleFactor = (100.0 / coreScale) * DEV_WAIT;

		float maxScale;

		switch (GetDeviceName())
		{
			case ipod3g:
				maxScale = 6.0;
				break;
				
			case ipod4g:
				maxScale = 4.0;
				break;
				
			case iphone3gs:
				maxScale = 6.0;
				break;
				
			case iphone4:
				maxScale = 4.0;
				break;
				
			case ipad1:
				maxScale = 3.0;
				break;
				
			case ipad2:
				maxScale = 4.0;
				break;
				
			default:
				maxScale = 4.0;
				break;
		}
		
		scaleFactor = scaleFactor * ratio < maxScale ? scaleFactor : maxScale / ratio;

		// scale factorの下限を超えないようにする
		scaleFactor = scaleFactor > 0.2 ? scaleFactor : 0.2;
			
		return scaleFactor;
	}

	// 2012.02.20 M.Chikyu end.
	

	static NSString* formatFileSize(NSNumber *fileSize)
	{
		NSString *formattedFileSize = nil;
		if (fileSize == nil) {
			return nil;
		}
		CGFloat size = [fileSize floatValue];
		if (size == 0) 
		{
			formattedFileSize = @"0 bytes";
		}
		else 
		{
			if (size > 0 && size < 1024) 
			{
				formattedFileSize = [NSString stringWithFormat:@"%.0f bytes  ", size];
			}
			else
			{
				if (size >= 1024 && size < pow(1024, 2)) 
				{
					formattedFileSize = [NSString stringWithFormat:@"%.1f KB  ", (size / 1024.)];
				}
				else
				{
					if (size >= pow(1024, 2) && size < pow(1024, 3))
					{
						formattedFileSize = [NSString stringWithFormat:@"%.2f MB  ", (size / pow(1024, 2))];
					}
					else 
					{
						if (size >= pow(1024, 3)) 
						{
							formattedFileSize = [NSString stringWithFormat:@"%.3f GB  ", (size / pow(1024, 3))];
						}
					}
				}
				
			}
		}
		
		return formattedFileSize;
	}


	static NSString* formatFileUpdateDate(NSDate *date, NSString *formatType)
	{
		NSString *formatteddDate = nil;
		if (date != nil) {
			NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
			[formatter setDateFormat:formatType];
			formatteddDate = [formatter stringFromDate:date];
			[formatter release];
		}
		
		return formatteddDate;
	}


	static NSString* getAttachmentMIMEType(NSString *filePath)
	{
		
		// tongtx 20110627 start
		// AR17880
		/*
		if ([pathExtension caseInsensitiveCompare:@"xdw"] == NSOrderedSame) 
		{
			return  @"application/vnd.fujixerox.docuworks";
		} 
		if ([pathExtension caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
		{
			return  @"application/vnd.fujixerox.docuworks.binder";
		}
		if ([pathExtension caseInsensitiveCompare:@"pdf"] == NSOrderedSame)
		{
			return @"application/pdf";
		}
		return nil;
		 */
		NSString *pathExtension = [filePath pathExtension]; 
		if ([pathExtension caseInsensitiveCompare:@"xdw"] == NSOrderedSame) 
		{
			return  @"application/vnd.fujixerox.docuworks";
		} 
		if ([pathExtension caseInsensitiveCompare:@"xbd"] == NSOrderedSame)
		{
			return  @"application/vnd.fujixerox.docuworks.binder";
		}
		NSURL* fileUrl = [NSURL fileURLWithPath:filePath];
		NSURLRequest* fileUrlRequest = [NSURLRequest requestWithURL:fileUrl];
		NSError* error = nil;
		NSURLResponse* response = nil;
		NSData* fileData = [NSURLConnection sendSynchronousRequest:fileUrlRequest returningResponse:&response error:&error];
		if (error == nil && response != nil) {
			return [response MIMEType];
		}
		return nil;
		// tongtx 20110627 end
	}
    
    // liuqw 20110622 start
    // AR NO.17847 の対応
    static long GetDeviceDPI()
    {
        if(Utility::UIDeviceIsiPad() == YES)
        {
            return Utility::DW_IPAD_DPI;
        } 
        else 
        {
            return Utility::DW_IPHONE_DPI;
        }
    }
    // liuqw 20110622 end
    
private:
	Utility();
	~Utility();
};

#endif