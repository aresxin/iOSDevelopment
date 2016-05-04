//
//  XMLParser.m
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "XMLParser.h"
#import "GDataXMLNode.h"

@implementation XMLParser
@synthesize deveices = deveices_;
@synthesize Element = Element_;
@synthesize device = device_;
@synthesize application = application_;
@synthesize project = project_;
@synthesize xmlType;
@synthesize deviceStatus = deviceStatus_;
@synthesize errorCode = errorCode_;
@synthesize key;
@synthesize value;
@synthesize messageDic;
@synthesize socketip;
- (id) init {
	self = [super init];
	if (self) {
		self.deviceStatus = nil;
		self.errorCode = nil;
		deveices_ = nil;
        messageDic = nil;
        self.key = nil;
        self.value = nil;
        //self.Element = @"";
	}
	return self;
}

- (void) reSetParser
{
	self.errorCode = nil;
	self.deviceStatus = nil;
}
#pragma mark -
#pragma mark XML parser  Delegate Methods
//解析xml
- (void) parserXMLFileAtData:(NSData *)data 
				  parseError:(NSError **)error 
				 withXMLType:(XMLType)xml
{
	// 1.0
	xmlType = xml;
	
	// 2.0
	switch (xmlType) {
		case deviceXML:
			deveices_ = [[NSMutableArray alloc] init];
			break;
		default:
			break;
	}
	
	// 3.0
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    // Set self as the delegate of the parser so that it will receive the parser delegate methods callbacks.
    [parser setDelegate:self];
    // Depending on the XML document you're parsing, you may want to enable these features of NSXMLParser.
    [parser setShouldProcessNamespaces:NO];
    [parser setShouldReportNamespacePrefixes:NO];
    [parser setShouldResolveExternalEntities:NO];
    [parser parse];
    
    NSError *parseError = [parser parserError];
    if (parseError && error) {
        *error = parseError;
    }
    
    [parser release];
	
	
}
- (void)parseXMLFileAtURL:(NSURL *)URL 
			   parseError:(NSError **)error 
			  withXMLType:(XMLType)xml {	
	// 1.0
	xmlType = xml;
	
	// 2.0
	switch (xmlType) {
		case deviceXML:
			deveices_ = [[NSMutableArray alloc] init];
			break;
        case messageXML:
            messageDic = [[NSMutableDictionary alloc] init];
            break;
		default:
			break;
	}
	
	// 3.0
    NSXMLParser *parser = [[NSXMLParser alloc] initWithContentsOfURL:URL];
    // Set self as the delegate of the parser so that it will receive the parser delegate methods callbacks.
    [parser setDelegate:self];
    // Depending on the XML document you're parsing, you may want to enable these features of NSXMLParser.
    [parser setShouldProcessNamespaces:NO];
    [parser setShouldReportNamespacePrefixes:NO];
    [parser setShouldResolveExternalEntities:NO];
    [parser parse];
    
    NSError *parseError = [parser parserError];
    if (parseError && error) {
        *error = parseError;
    }
    
    [parser release];
}

#pragma mark -
#pragma mark parserDeviceXML
- (void) parseDeviceXMLWithStatus:(BOOL)isStart withElement:(NSString *)elementName
{
	if (isStart == YES) {
		// level 1
		if ([elementName isEqualToString:@"device"]) 
		{
			self.device = [[[DeviceObject alloc] init] autorelease];
		}
		// level 2
		if([elementName isEqualToString:@"application"])
		{
			self.application = [[[applicationObject alloc] init] autorelease];
		}
		
		if ([elementName isEqualToString:@"projector"]) {
			self.application = [[[applicationObject alloc] init] autorelease];
		}
		
		// level 3
		if ([elementName isEqualToString:@"scene"]) {
			self.project = [[[projectObject alloc] init] autorelease];
		}
		
		if ([elementName isEqualToString:@"video"]) {
			self.project = [[[projectObject alloc] init] autorelease];
		}
		
	}else {
		// level 1
		if ([elementName isEqualToString:@"device"]) 
		{
			[deveices_ addObject:device_];
		}
		
		if ([elementName isEqualToString:@"deviceId"]) {
			device_.deviceId = Element_;
		}
		
		if ([elementName isEqualToString:@"deviceName"]) {
			device_.deviceName = Element_;
		}
		
		if ([elementName isEqualToString:@"deviceCL"]) {
			device_.deviceCL = Element_;
		}
		
		if ([elementName isEqualToString:@"ipAddress"]) {
			device_.ipAddress = Element_;
		}
		
		// level 2
		if([elementName isEqualToString:@"application"])
		{
			[device_.applications addObject:application_];
		}
		
		if ([elementName isEqualToString:@"applicationId"]) {
			application_.applicationId = Element_;
		}
		
		if ([elementName isEqualToString:@"applicationName"]) {
			application_.applicationName = Element_;
		}
		
		if ([elementName isEqualToString:@"applicationCL"]) {
			application_.applicationCL = Element_;
		}
		
		if ([elementName isEqualToString:@"projector"]) {
			[device_.applications addObject:application_];
		}
		
		if ([elementName isEqualToString:@"projectorId"]) {
			application_.applicationId = Element_;
		}else if ([elementName isEqualToString:@"projectorName"]) {
			application_.applicationName = Element_;
		}
		
		
		if ([elementName isEqualToString:@"scene"]) {
			[application_.members addObject:project_];
		}
		
		if ([elementName isEqualToString:@"sceneId"]) {
			project_.projectId = Element_;
		}else if ([elementName isEqualToString:@"sceneName"]) {
			project_.projectName = Element_;
		}
        
        if ([elementName isEqualToString:@"sceneIndex"]) {
            project_.videoindex = Element_;
        }
		
		
		if ([elementName isEqualToString:@"video"]) {
			[application_.members addObject:project_];
		}
		
		if ([elementName isEqualToString:@"videoId"]) {
			project_.projectId = Element_;
		}else if ([elementName isEqualToString:@"videoName"]) {
			project_.projectName = Element_;
		}
		
		if ([elementName isEqualToString:@"videoIndex"]) {
			project_.videoindex = Element_;
		}
	}

}

#pragma mark -
#pragma mark parserstatusxml
- (void) parseStatusXMLWithStatus:(BOOL)isStart withElement:(NSString *)elementName
{
	if (isStart) {
		//parse start
		if ([elementName isEqualToString:@"status"]) {
			self.deviceStatus = [[[DeviceObject alloc] init] autorelease];
		}
		
		// level 2
		if([elementName isEqualToString:@"application"])
		{
			self.application = [[[applicationObject alloc] init] autorelease];
		}
		
	}else {
		//parse end
		if ([elementName isEqualToString:@"deviceId"]) {
			deviceStatus_.deviceId = Element_;
		}
		
		if ([elementName isEqualToString:@"power"]) {
			deviceStatus_.power = Element_;
		}
		
		if ([elementName isEqualToString:@"appid"]) {
			application_.applicationId = Element_;
		}
		
		if ([elementName isEqualToString:@"running"]) {
			application_.running = Element_;
		}
		
		if ([elementName isEqualToString:@"application"]) {
			[deviceStatus_.applications addObject:application_];
		}
	}

}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict {
    self.Element = @"";
	switch (xmlType) {
		case deviceXML:
			[self parseDeviceXMLWithStatus:YES withElement:elementName];
			break;
		case errorXML:
			
			break;
		case applicationsXML:
				
			break;
		case statusXML:
			[self parseStatusXMLWithStatus:YES withElement:elementName];
			break;
        case messageXML:
            break;
		default:
			break;
	}
}


- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
	switch (xmlType) {
		case deviceXML:
			[self parseDeviceXMLWithStatus:NO withElement:elementName];
			if ([elementName isEqualToString:@"errorCode"]) {
				self.errorCode = Element_;
			}
			break;
		case applicationsXML:
			
			break;
		case statusXML:
			[self parseStatusXMLWithStatus:NO withElement:elementName];
			if ([elementName isEqualToString:@"errorCode"]) {
				self.errorCode = Element_;
			}
			break;
        case messageXML:
            if ([elementName isEqualToString:@"errorCode"]) {
                self.key = Element_;
            }
            if ([elementName isEqualToString:@"message"]) {
                self.value = Element_;
            }
            if ([elementName isEqualToString:@"error"]) {
                [messageDic setObject:value forKey:key];
            }
            break;
		default:
			break;
	}
	self.Element = nil;
}



- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    self.Element = [Element_ stringByAppendingString:string];
#ifndef  LOGDEBUG    
	NSLog(@"%@",Element_);
#endif	
}

//当xml解析完成后的操作
-(void)parserDidEndDocument:(NSXMLParser *)parser{
#ifndef LOGDEBUG
	switch (xmlType) {
		case deviceXML:
			for (DeviceObject *dev in deveices_) {
				NSLog(@"devid is %@",dev.deviceId);
				NSLog(@"devname is %@",dev.deviceName);
				NSLog(@"devcl is %@",dev.deviceCL);
				NSLog(@"ipaddress is %@",dev.ipAddress);
				NSLog(@"device power is %@",dev.power);
				for (applicationObject *app in dev.applications) {
					NSLog(@"appid is %@",app.applicationId);
					NSLog(@"appname is %@",app.applicationName);
					NSLog(@"appcl is %@",app.applicationCL);
					NSLog(@"appp is runn %@",app.running);
					for (projectObject *p in app.members) {
						NSLog(@"project id is %@",p.projectId);
						NSLog(@"project name is %@",p.projectName);
					}
				}
			}
			break;
		case statusXML:
			NSLog(@"devid is %@",deviceStatus_.deviceId);
			NSLog(@"device power is %@",deviceStatus_.power);	
			NSLog(@"device power is %d",[deviceStatus_.applications count]);	
			for (applicationObject *app in deviceStatus_.applications) {
				NSLog(@"appid is %@",app.applicationId);
				NSLog(@"appp is runn %@",app.running);
			}
			break;
		case errorXML:
			NSLog(@"%@",errorCode_);
			break;

		default:
            NSLog(@"%@",errorCode_);
			break;
	}
#endif
}


#pragma make -
#pragma make GDataXMLparser

+ (NSMutableString *) parseGDataXMLPath:(NSString *)filePath
{
    NSError *error = nil;
    NSMutableString *resultString = [[NSMutableString alloc] 
                                     initWithString:@"XML数据内容: \n"];
    NSString *xmlString = [[NSString alloc] 
                           initWithContentsOfFile:filePath 
                           encoding:NSUTF8StringEncoding 
                           error:nil];
    
    GDataXMLDocument *doc = [[GDataXMLDocument alloc] 
                             initWithXMLString:xmlString
                             options:0 
                             error:&error];
    
    if (doc == nil) { return nil; }
    
    // 解析
    
    // 使用XPath语法解析
    NSArray *partyMembers = [doc.rootElement nodesForXPath:@"//Party/Player" error:nil];
    // 遍历节点
    for (GDataXMLElement *partyMember in partyMembers) 
    {
        
        NSString *_name;
        NSString *_level;
        NSString *_class;
        
        // 取值
        NSArray *names = [partyMember elementsForName:@"Name"];
        if (names.count > 0) {
            GDataXMLElement *firstName = (GDataXMLElement *) [names objectAtIndex:0];
            _name = firstName.stringValue;
        } else continue;
        
        // Level
        NSArray *levels = [partyMember elementsForName:@"Level"];
        if (levels.count > 0) {
            GDataXMLElement *firstLevel = (GDataXMLElement *) [levels objectAtIndex:0];
            _level = firstLevel.stringValue;
        } else continue;
        
        // Class
        NSArray *classes = [partyMember elementsForName:@"Class"];
        if (classes.count > 0) {
            GDataXMLElement *firstClass = (GDataXMLElement *) [classes objectAtIndex:0];
            _class = firstClass.stringValue;
            
        } else continue;
        
        [resultString appendFormat:@"Name=%@",_name ];
        [resultString appendFormat:@" Level=%@",_level ];
        [resultString appendFormat:@" Class=%@\n",_class ];
        
    }

    
    return [resultString autorelease];
}

+ (NSMutableString *) parseGDataXML:(NSData *)xmlData_
{
    return nil;
}

- (void)dealloc {
	[Element_  release];
	[deveices_ release];
	[device_   release];
	[project_  release];
	[application_   release];
	[deviceStatus_  release];
	[errorCode_  release];
    [key release];
    [value release];
    [messageDic release];
	[socketip release];
    [super dealloc];
}

@end
