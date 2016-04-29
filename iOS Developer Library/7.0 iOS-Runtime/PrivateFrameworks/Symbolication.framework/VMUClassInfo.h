/* Generated by RuntimeBrowser
   Image: /System/Library/PrivateFrameworks/Symbolication.framework/Symbolication
 */

/* RuntimeBrowser encountered an ivar type encoding it does not handle. 
   See Warning(s) below.
 */

@class NSString, VMUClassInfo;

@interface VMUClassInfo : NSObject <NSCoding> {
    const char *_extendedLayout;
    BOOL _hasSpecificLayout;
    unsigned int _instanceSize;
    unsigned int _ivarCount;
    int *_ivarScanSizes;
    struct objc_ivar {} **_localIvarList;
    id _reader;
    NSString *_remoteBinaryName;
    NSString *_remoteClassName;
    unsigned long long _remoteIsa;
    unsigned int _remotePointerSize;
    unsigned int _remoteType;
    unsigned int _ro_flags;
    unsigned int _rw_flags;
    char *_scanMap;
    unsigned long long _specificInstance;
    const char *_strongLayout;
    VMUClassInfo *_superclassLayout;
    unsigned int _superclassOffset;
    const char *_weakLayout;
}

@property(readonly) NSString * binaryName;
@property(readonly) NSString * className;
@property(readonly) NSString * fullIvarDescription;
@property(readonly) BOOL hasCppConstructorOrDestructor;
@property(readonly) BOOL hasSpecificLayout;
@property(readonly) int infoType;
@property(readonly) unsigned int instanceSize;
@property(readonly) BOOL isARR;
@property(readonly) BOOL isMetaClass;
@property(readonly) BOOL isRealized;
@property(readonly) BOOL isRootClass;
@property(readonly) unsigned long long remoteIsa;
@property(readonly) NSString * shortIvarDescription;
@property(readonly) unsigned long long specificInstance;
@property(readonly) VMUClassInfo * superclassInfo;
@property(readonly) NSString * typeName;

+ (id)classInfoWithClassName:(id)arg1 binaryName:(id)arg2 type:(int)arg3;
+ (id)descriptionForTypeEncoding:(const char *)arg1 ivarName:(const char *)arg2;
+ (void)initialize;

- (struct objc_ivar { }*)_copyRemoteIvarAt:(unsigned long long)arg1;
- (const char *)_copyRemoteLayout:(unsigned long long)arg1;
- (const char *)_copyRemoteStringAt:(unsigned long long)arg1;
- (void)_faultScanMap;
- (id)_initWithClass:(unsigned long long)arg1 realizedOnly:(BOOL)arg2 infoMap:(id)arg3 symbolicator:(struct _CSTypeRef { unsigned int x1; unsigned int x2; })arg4 type:(int)arg5 memoryReader:(id)arg6;
- (id)_instanceSpecificInfoForObject:(unsigned long long)arg1 pointerSize:(unsigned int)arg2 reader:(id)arg3;
- (id)_ivarDescription:(unsigned int)arg1 withSpacing:(unsigned int)arg2;
- (void)_logDescriptionWithSuperclasses:(BOOL)arg1 indentation:(int)arg2 toLogger:(id)arg3;
- (void)_parseIvarsAndLayouts;
- (void)_processARRLayout:(const char *)arg1 scanType:(int)arg2;
- (void)_processExtendedLayout:(const char *)arg1;
- (int)_readRemoteIntAt:(unsigned long long)arg1;
- (unsigned long long)_readRemotePointerAt:(unsigned long long)arg1;
- (void)_setClassNameWithAddress:(unsigned long long)arg1;
- (void)_setExtendedLayout:(const char *)arg1;
- (id)_specificCopy:(unsigned long long)arg1 instanceSize:(unsigned int)arg2 superclassOffset:(unsigned int)arg3;
- (id)binaryName;
- (id)className;
- (void)dealloc;
- (id)debugDescription;
- (id)description;
- (void)encodeWithCoder:(id)arg1;
- (void)enumerateIvarsWithBlock:(id)arg1;
- (void)enumerateKnownSublayoutsForObject:(unsigned long long)arg1 withBlock:(id)arg2;
- (void)enumerateScanLocationsToSize:(unsigned int)arg1 withBlock:(id)arg2;
- (id)fullIvarDescription;
- (BOOL)hasCppConstructorOrDestructor;
- (BOOL)hasSpecificLayout;
- (unsigned int)hash;
- (int)infoType;
- (id)initWithClass:(unsigned long long)arg1 infoMap:(id)arg2 symbolicator:(struct _CSTypeRef { unsigned int x1; unsigned int x2; })arg3 type:(int)arg4 memoryReader:(id)arg5;
- (id)initWithClassName:(id)arg1 binaryName:(id)arg2 type:(int)arg3;
- (id)initWithCoder:(id)arg1;
- (id)initWithIsaPointer:(unsigned int)arg1 symbolicator:(struct _CSTypeRef { unsigned int x1; unsigned int x2; })arg2;
- (id)initWithRealizedClass:(unsigned long long)arg1 infoMap:(id)arg2 symbolicator:(struct _CSTypeRef { unsigned int x1; unsigned int x2; })arg3 type:(int)arg4 memoryReader:(id)arg5;
- (unsigned int)instanceSize;
- (id)instanceSpecificInfoForObject:(unsigned long long)arg1;
- (BOOL)isARR;
- (BOOL)isEqual:(id)arg1;
- (BOOL)isMetaClass;
- (BOOL)isRealized;
- (BOOL)isRootClass;
- (struct objc_ivar { }*)ivarWithOffset:(unsigned long long)arg1;
- (unsigned long long)remoteIsa;
- (void)scanObject:(unsigned long long)arg1 ofSize:(unsigned int)arg2 withBlock:(id)arg3;
- (void)setMemoryReader:(id)arg1;
- (id)shortIvarDescription;
- (unsigned long long)specificInstance;
- (id)superclassInfo;
- (id)type;
- (id)typeName;

@end