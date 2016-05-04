//
//  XMLParser.h
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DeviceObject.h"
#import "applicationObject.h"
#import "projectObject.h"
#import "GUIConst.h"

@interface XMLParser : NSObject <NSXMLParserDelegate>{
	NSString                 *Element_;
	NSMutableArray           *deveices_;
	// status
	DeviceObject             *deviceStatus_;
	//error
	NSString                 *errorCode_;
	
	// data
	DeviceObject             *device_;
	applicationObject        *application_;
	projectObject            *project_;
	XMLType                  xmlType;
    
    // message
    NSMutableDictionary      *messageDic;
    NSString                 *key;
    NSString                 *value;
	
	NSString                 *socketip;
    
    
    int                      lineNum;
}
@property (nonatomic, retain) NSMutableArray       *deveices;
@property (nonatomic, retain) NSString             *Element;
@property XMLType  xmlType;
// status 
@property (nonatomic, retain) DeviceObject        *deviceStatus;
// error
@property (nonatomic, retain) NSString            *errorCode;

@property (nonatomic, retain) DeviceObject         *device;
@property (nonatomic, retain) applicationObject    *application;
@property (nonatomic, retain) projectObject        *project;

@property (nonatomic, retain) NSString             *key;
@property (nonatomic, retain) NSString             *value;
@property (nonatomic, retain) NSMutableDictionary   *messageDic;
@property (nonatomic, retain) NSString              *socketip;
- (void)parseXMLFileAtURL:(NSURL *)URL parseError:(NSError **)error withXMLType:(XMLType)xml;
//解析xml
- (void) parserXMLFileAtData:(NSData *)data 
				  parseError:(NSError **)error 
				 withXMLType:(XMLType)xml;
- (void) reSetParser;

+ (NSMutableString *) parseGDataXMLPath:(NSString *)filePath;
+ (NSMutableString *) parseGDataXML:(NSData *)xmlData_;

@end
