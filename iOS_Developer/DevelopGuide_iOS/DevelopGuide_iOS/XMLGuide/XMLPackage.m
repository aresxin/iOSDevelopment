//
//  XMLPackage.m
//  ControllerSystem
//
//  Created by neusoft  on 11-12-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "XMLPackage.h"
#import "GDataXMLNode.h"

@implementation XMLNode

@synthesize rootElement = rootElement_;
@synthesize childElemetns = childElemetns_;
@synthesize stringValue = stringValue_;

/* 
 NSObject alloc  执行三步
 1.分配内存
 2.初始化isa指针，明确实例化对象所指向的类
 3.将实例化对象的属性设置为nil 
*/

- (id) init
{
    self = [super init];
    if (self != nil) {
        self.childElemetns = nil;
        self.rootElement = nil;
        self.stringValue = nil;
    }
    return  self;
}

/*
    初始化Node节点XML的一个元素
*/
- (id) initWithRootElement:(NSString *)_rootElement 
         withChildElements:(NSMutableArray *)_childElements
           withStringValue:(NSString *)_stringValue
{
    self = [super init];
    if (self != nil) {
        self.rootElement = _rootElement;
        self.childElemetns = _childElements;
        self.stringValue = _stringValue;
    }
    return  self;
}

- (void) dealloc
{
    [rootElement_ release];
    [childElemetns_ release];
    [stringValue_ release];
    [super dealloc];
}

@end

@implementation XMLPackage

#ifdef _TEST_CODE_
// 测试方法
+ (XMLNode *)createXMLNode
{
    XMLNode *roorNode = nil;
    NSMutableArray *nodes = [[NSMutableArray alloc] init];
    
    
    XMLNode *insNode = [[XMLNode alloc] initWithRootElement:@"instruction" 
                                          withChildElements:nil 
                                            withStringValue:@"run"];
    
    XMLNode *devIdNode = [[XMLNode alloc] initWithRootElement:@"deviceId" 
                                          withChildElements:nil 
                                            withStringValue:@"001"];
    
    XMLNode *devNode = [[XMLNode alloc] initWithRootElement:@"device" 
                                          withChildElements:[NSMutableArray arrayWithObject:devIdNode] 
                                            withStringValue:nil];
    [nodes addObject:devNode];
    [nodes addObject:insNode];
    
    roorNode = [[XMLNode alloc] initWithRootElement:@"request" 
                                  withChildElements:nodes 
                                    withStringValue:nil];
    [insNode release];
    [devIdNode release];
    [devNode release];
    [nodes release];
    
    return roorNode;
}
// 测试方法
+ (XMLNode *) getXML
{
    XMLNode *app = [[XMLNode alloc]initWithRootElement:@"app" 
                                     withChildElements:nil 
                                       withStringValue:@"appid"];
    
    XMLNode *apps = [[XMLNode alloc] initWithRootElement:@"applicas" 
                                       withChildElements:[NSMutableArray arrayWithObject:app]
                                         withStringValue:nil];
    
    XMLNode *devid = [[XMLNode alloc] initWithRootElement:@"devid" 
                                       withChildElements:nil
                                         withStringValue:@"000"];
    
    XMLNode *dev = [[XMLNode alloc] initWithRootElement:@"device" 
                                      withChildElements:[NSMutableArray arrayWithObjects:devid,apps, nil] 
                                        withStringValue:nil];
    XMLNode *res = [[XMLNode alloc] initWithRootElement:@"res" 
                                      withChildElements:[NSMutableArray arrayWithObject:dev]
                                        withStringValue:nil];
    return res;
}
#endif

/*
 将创建的xml节点，转换成GDataXMLElement
*/
+ (GDataXMLElement *) PackageXMLWithXMLNode:(XMLNode *)xmlNode_
{
    if (xmlNode_ == nil) 
    {
        return nil;
    }

    XMLNode *packNode = [xmlNode_ retain];
    // 创建XML节点
    GDataXMLElement * rootElement = [GDataXMLNode elementWithName:packNode.rootElement];
    
    for (XMLNode *node in packNode.childElemetns) 
    {
        GDataXMLElement * childElement = nil;
        
        // 子节点包含子节点
        if ([node.childElemetns count] > 0) 
        {
            childElement = [XMLPackage PackageXMLWithXMLNode:node];
        }
        else
        {
            childElement = [GDataXMLNode elementWithName:node.rootElement 
                                             stringValue:node.stringValue];
        }
        
        [rootElement addChild:childElement];
    }
    
       
    return rootElement;
}

/*
    把GDataXMLElement转换成GDataXMLDocument文档
    GDataXMLDocument的XMLData既为xml数据
*/ 
+ (GDataXMLDocument *)  getXMLDocument:(GDataXMLElement *)xmlElement
{
    GDataXMLDocument *xmlDoc = nil;
    
    if (xmlElement == nil) {
        return nil;
    }
    
    GDataXMLElement *rootElement = [xmlElement retain];
    // 创建XML文件
    xmlDoc = [[GDataXMLDocument alloc] initWithRootElement:rootElement];
    [rootElement release];
    
    // test start
    NSData *xmlData = xmlDoc.XMLData;
    // 得到输出路径
    NSString *homePath = [[NSHomeDirectory() stringByAppendingPathComponent:@"Documents"] stringByAppendingPathComponent:@"party.xml"];
    // 输出
    [xmlData writeToFile:homePath atomically:YES];
    // test end
    
    return [xmlDoc autorelease];
}

+ (NSData *) getXmlDataWithXmlNode:(XMLNode *)xmlNode_
{
    NSData *xmlData = nil;
    
    if (xmlNode_ == nil) {
        return xmlData;
    }
    
    GDataXMLElement *xmlElement = [[XMLPackage PackageXMLWithXMLNode:xmlNode_] retain];
    GDataXMLDocument *xmlDocument = [[XMLPackage getXMLDocument:xmlElement] retain];
    
    if (xmlDocument != nil) {
        xmlData = xmlDocument.XMLData;
    }
    
    // release
    [xmlElement release];
    [xmlDocument release];
    
    return xmlData;
}

+ (NSString *) getXmlStringWithXmlNode:(XMLNode *)xmlNode_
{
    NSString *xmlStr = nil;
    
    if (xmlNode_ == nil) {
        return xmlStr;
    }
    
    NSData *xmlData = [[XMLPackage getXmlDataWithXmlNode:xmlNode_] retain];
    
    if (xmlData != nil && [xmlData length] > 0) {
        xmlStr = [[[NSString alloc] initWithData:xmlData 
                                       encoding:NSUTF8StringEncoding] autorelease];
    }
   
    // release
    [xmlData release];
    
    return xmlStr;
}
@end
