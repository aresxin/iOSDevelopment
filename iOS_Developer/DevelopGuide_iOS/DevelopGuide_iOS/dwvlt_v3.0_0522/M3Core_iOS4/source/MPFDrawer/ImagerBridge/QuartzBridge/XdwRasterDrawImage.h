/*
 *  XdwRasterDrawImage.h
 *  DWQuartzBridge
 *
 *  Created by tongjo on 10-9-4.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#import "XdwBridgeDrawIF.h"
#import "XdwBridgeViewerContIF.h"
#import "MXDDeviceContext.h"

#import "XdwBridgeRasterDecodeStrategy.h"
#import "XdwBridgeRasterDecodeStrategyDIB.h"
#import "XdwBridgeRasterOutputAdapterMac.h"

class XdwRasterDrawImage
{
protected:
	XdwBridgeRasterOutputAdapter *current_out;
	XdwBridgeDecodeStrategy	     *image;
	XdwBridgeDecodeStrategy	     *mask;
	void	*imagerF;
	
	XdwBridgeDecodeStrategy* GenerateDecoder(XdwBridgeRasterOutputAdapter	*out,
											 const XdwRasterImageAttribute	&img_attr,
											 XdwDataObject::Binary		    *img_data );
	
    void DestroyDecoder(XdwBridgeDecodeStrategy*);
public:
	XdwRasterDrawImage();
	virtual ~XdwRasterDrawImage();
	
	
	XdwErrorCode DrawImage(XdwBridgeRasterOutputAdapter		*out,
						   const XdwRasterImageAttribute	&img_attr,
						   XdwDataObject::Binary			*img_data,
						   const long						&img_offset,
						   const long						&img_size,
						   const XdwRasterImageAttribute	&mask_attr,
						   XdwDataObject::Binary			*mask_data,
						   const long						&mask_offset,
						   const long						&mask_size );
	
    XdwErrorCode StartDrawDividedImage(XdwBridgeRasterOutputAdapter		*out,
									   const XdwRasterImageAttribute	&img_attr,
									   XdwDataObject::Binary			*img_data,
									   const long						&img_offset,
									   const long						&img_size,
									   const XdwRasterImageAttribute	&mask_attr,
									   XdwDataObject::Binary			*mask_data,
									   const long						&mask_offset,
									   const long						&mask_size,
									   long								nlines );
	
	XdwErrorCode DrawDividedImage( void );
	
	XdwErrorCode EndDrawDividedImage( void );

	XdwErrorCode GetInfoAndDecodedData(XdwBridgeRasterOutputAdapter		*out,
									   const XdwRasterImageAttribute	&img_attr,
						               XdwDataObject::Binary		    *img_data,
						               const long						&img_offset,
						               const long						&img_size,
									   BITMAPINFO*&                     pBmpInfo,
									   unsigned char*&                  imgBufferF);
};

