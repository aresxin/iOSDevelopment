//
//  MXDFileMap.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface MXDFileMap : NSObject {
    char	_filename[256];
	int		_fd;
	char*   _mapPtr;
	size_t  _size;
	
}

- (char*)createFileMapBySize:(size_t)size;
- (char*)fileMap;
- (size_t)size;
- (void)closeFileMap;
- (void*)releaseCallbackFunction;
@end
