//
//  XMLPackage.h
//  ControllerSystem
//
//  Created by neusoft  on 11-12-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@class GDataXMLElement;
@class GDataXMLDocument;

@interface XMLNode : NSObject {
    NSString            *rootElement_;
    NSMutableArray      *childElemetns_;
    NSString            *stringValue_;
}

@property (nonatomic, copy)     NSString            *rootElement;
@property (nonatomic, retain)   NSMutableArray      *childElemetns;
@property (nonatomic, copy)     NSString            *stringValue;

- (id) initWithRootElement:(NSString *)_rootElement 
         withChildElements:(NSMutableArray *)_childElements
           withStringValue:(NSString *)_stringValue;
@end


@interface XMLPackage : NSObject {
    
}

#ifdef _TEST_CODE_
+ (XMLNode *)createXMLNode;
+ (XMLNode *) getXML;
#endif

// interal interface
+ (GDataXMLElement *) PackageXMLWithXMLNode:(XMLNode *)xmlNode_;
+ (GDataXMLDocument *)  getXMLDocument:(GDataXMLElement *)xmlElement;
// exteral interface 
+ (NSData *) getXmlDataWithXmlNode:(XMLNode *)xmlNode_;
+ (NSString *) getXmlStringWithXmlNode:(XMLNode *)xmlNode_;
@end
