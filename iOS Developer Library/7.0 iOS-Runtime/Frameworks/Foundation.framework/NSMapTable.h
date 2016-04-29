/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/Foundation.framework/Foundation
 */

@class NSPointerFunctions;

@interface NSMapTable : NSObject <NSCopying, NSCoding, NSFastEnumeration> {
}

@property(readonly) unsigned int count;
@property(copy,readonly) NSPointerFunctions * keyPointerFunctions;
@property(copy,readonly) NSPointerFunctions * valuePointerFunctions;

+ (id)alloc;
+ (id)allocWithZone:(struct _NSZone { }*)arg1;
+ (id)mapTableWithKeyOptions:(unsigned int)arg1 valueOptions:(unsigned int)arg2;
+ (id)mapTableWithStrongToStrongObjects;
+ (id)mapTableWithStrongToWeakObjects;
+ (id)mapTableWithWeakToStrongObjects;
+ (id)mapTableWithWeakToWeakObjects;
+ (id)newTspStrongObjectsMapTable;
+ (id)newTspWeakObjectsMapTable;
+ (id)strongToStrongObjectsMapTable;
+ (id)strongToWeakObjectsMapTable;
+ (id)weakToStrongObjectsMapTable;
+ (id)weakToWeakObjectsMapTable;

- (id)CKAllKeys;
- (id)allKeys;
- (id)allValues;
- (id)bs_takeObjectForKey:(id)arg1;
- (id)copy;
- (id)copyWithZone:(struct _NSZone { }*)arg1;
- (unsigned int)count;
- (unsigned int)countByEnumeratingWithState:(struct { unsigned long x1; id *x2; unsigned long *x3; unsigned long x4[5]; }*)arg1 objects:(id*)arg2 count:(unsigned int)arg3;
- (id)description;
- (id)dictionaryRepresentation;
- (void)encodeWithCoder:(id)arg1;
- (void)enumerateIdentifiersAndObjectsUsingBlock:(id)arg1;
- (void)enumerateObjectsUsingBlock:(id)arg1;
- (id)enumerator;
- (void*)existingItemForSetItem:(const void*)arg1 forAbsentKey:(const void*)arg2;
- (unsigned int)getKeys:(const void**)arg1 values:(const void**)arg2;
- (id)init;
- (id)initWithCoder:(id)arg1;
- (id)initWithKeyOptions:(unsigned int)arg1 valueOptions:(unsigned int)arg2 capacity:(unsigned int)arg3;
- (id)initWithKeyPointerFunctions:(id)arg1 valuePointerFunctions:(id)arg2 capacity:(unsigned int)arg3;
- (id)keyEnumerator;
- (id)keyPointerFunctions;
- (BOOL)mapMember:(const void*)arg1 originalKey:(const void**)arg2 value:(const void**)arg3;
- (id)mutableCopyWithZone:(struct _NSZone { }*)arg1;
- (id)mutableDictionary;
- (id)objectEnumerator;
- (id)objectForKey:(id)arg1;
- (id)objectForKeyedSubscript:(id)arg1;
- (void)removeAllItems;
- (void)removeAllObjects;
- (void)removeObjectForKey:(id)arg1;
- (void)replaceItem:(const void*)arg1 forExistingKey:(const void*)arg2;
- (void)setItem:(const void*)arg1 forAbsentKey:(const void*)arg2;
- (void)setItem:(const void*)arg1 forKey:(const void*)arg2;
- (void)setItem:(const void*)arg1 forKnownAbsentKey:(const void*)arg2;
- (void)setObject:(id)arg1 forKey:(id)arg2;
- (void)setObject:(id)arg1 forKeyedSubscript:(id)arg2;
- (id)tsp_objectForIdentifier:(long long)arg1;
- (void)tsp_removeObjectForIdentifier:(long long)arg1;
- (void)tsp_setObject:(id)arg1 forIdentifier:(long long)arg2;
- (id)valuePointerFunctions;

@end