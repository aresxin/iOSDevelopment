//
//  Student.h
//  DevelopGuide_iOS
//
//  Created by clay on 12-8-23.
//
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class Teacher;

@interface Student : NSManagedObject

@property (nonatomic, retain) NSNumber * number;
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSSet *teachers;
@end

@interface Student (CoreDataGeneratedAccessors)

- (void)addTeachersObject:(Teacher *)value;
- (void)removeTeachersObject:(Teacher *)value;
- (void)addTeachers:(NSSet *)values;
- (void)removeTeachers:(NSSet *)values;

@end
