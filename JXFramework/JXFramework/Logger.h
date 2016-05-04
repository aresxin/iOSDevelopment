//
//  Logger.h
//  JXFramework
//
//  Created by yangjinxin on 15/9/11.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, LCCLoggerLevel) {
    LCCLoggerLevelNone,
    LCCLoggerLevelInfo,
    LCCLoggerLevelWarning,
    LCCLoggerLevelError,
};

#ifndef LCC_Logger_h
#define LCC_Logger_h

#ifdef STORE
#define WriteInfo(fmt, ...)
#define WriteWarning(fmt, ...)
#define WriteError(fmt, ...)
#define Benchmark(name)
#define WriteMark(name)
#else
#ifndef __LOG_LOCATION__
#define __LOG_LOCATION__ ([NSString stringWithFormat:@"%s:%d %s", ([[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String]), __LINE__, __PRETTY_FUNCTION__])
#define WriteInfo(fmt, ...) LCCLoggerInfo([NSString stringWithFormat:@"[I] %@", [NSString stringWithFormat:fmt, ##__VA_ARGS__]]);
#define WriteWarning(fmt, ...) LCCLoggerWarning([NSString stringWithFormat:@"[W] %@", [NSString stringWithFormat:fmt, ##__VA_ARGS__]]);
#define WriteFatal(fmt, ...) LCCLoggerFatal([NSString stringWithFormat:@"[F] %@ %@", __LOG_LOCATION__, [NSString stringWithFormat:fmt, ##__VA_ARGS__]]);
#define WriteError(err, act) LCCLoggerError(err, [NSString stringWithFormat:@"[E] %@", __LOG_LOCATION__], act);
#define Benchmark(name) LCCLoggerBenchmark(name);
#define WriteMark(name) LCCLoggerMarkName(name);
#endif

#endif

void LCCLogger(LCCLoggerLevel level);
void LCCLoggerInfo(NSString *format, ...);
void LCCLoggerWarning(NSString *format, ...);
void LCCLoggerFatal(NSString *format, ...);
void LCCLoggerError(NSError *error, NSString *location, NSString *action);

void LCCLoggerBenchmark(NSString *function);
void LCCLoggerMarkName(NSString *name);

#endif

