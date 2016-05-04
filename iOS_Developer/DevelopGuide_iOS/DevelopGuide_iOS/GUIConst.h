//
//  GUIConst.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-1.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#define     _STUDYMODELIST_             @"studyMode.plist"
#define     _RootViewController_TITLE_  @"iOS_Guide"
#define     DIR_KEY                     @"guide"

/****************alert start************************/
#define     ERROR_TITLE                 @"Error"
#define     ERROR_MESSAGE_SOCKET_FAILED @"socket断开链接"
#define     ERROR_OK                    @"OK"
/****************alert end**************************/

typedef enum  {
	deviceXML = 0,
	errorXML  = 1,
	statusXML = 2,
	applicationsXML = 3,
	ortherXML = 4,
    messageXML = 5,
}XMLType;
