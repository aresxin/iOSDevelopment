//
//  Logger.m
//  JXFramework
//
//  Created by yangjinxin on 15/9/11.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "Logger.h"

static BOOL LCCLoggerInfoEnabled = YES;
static BOOL LCCLoggerWarningEnabled = YES;
static BOOL LCCLoggerErrorEnabled = YES;
static BOOL LCCLoggerFatalEnabled = YES;
static NSMutableDictionary *sharedTimeCache = nil;

void LCCLoggerRedirection()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                         NSUserDomainMask, YES);
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd"];
    NSDate* date = [[NSDate alloc] init];
    NSString *fileName = [NSString stringWithFormat:@"%@%@", [dateFormatter stringFromDate:date], @".log" ];
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *logPath = [documentsDirectory stringByAppendingPathComponent:fileName];
    WriteWarning(@"Log Path:%@", logPath);
    freopen([logPath fileSystemRepresentation],"a+",stderr);
    freopen([logPath fileSystemRepresentation],"a+",stdout);
}

void LCCLogger(LCCLoggerLevel level)
{
    // set log level according to deploy configuration.
    switch (level) {
        case LCCLoggerLevelInfo:
            // Enable all levels.
            LCCLoggerInfoEnabled = YES;
            LCCLoggerWarningEnabled = YES;
            LCCLoggerErrorEnabled = YES;
            LCCLoggerFatalEnabled = YES;
            break;
            
        case LCCLoggerLevelWarning:
            // Warning
            LCCLoggerInfoEnabled = NO;
            LCCLoggerWarningEnabled = YES;
            LCCLoggerErrorEnabled = YES;
            LCCLoggerFatalEnabled = YES;
            break;
            
        case LCCLoggerLevelError:
            // Error
            LCCLoggerInfoEnabled = NO;
            LCCLoggerWarningEnabled = NO;
            LCCLoggerErrorEnabled = YES;
            LCCLoggerFatalEnabled = YES;
            break;
            
        default:
            // Silent mode. Disable all levels.
            LCCLoggerInfoEnabled = NO;
            LCCLoggerWarningEnabled = NO;
            LCCLoggerErrorEnabled = NO;
            LCCLoggerFatalEnabled = NO;
            break;
    }
    
    if (LCCLoggerInfoEnabled || LCCLoggerWarningEnabled || LCCLoggerFatalEnabled || LCCLoggerErrorEnabled) {
#if DEBUG
        // debug log redirection
        LCCLoggerRedirection();
#endif
        // initialize time cache for benchmark
        if (!sharedTimeCache) {
            sharedTimeCache = [NSMutableDictionary dictionary];
        }
    }
}

void LCCLoggerWrite(NSString *string)
{
    CFAbsoluteTime currentTime = CFAbsoluteTimeGetCurrent();
    NSDate *date = [NSDate dateWithTimeIntervalSinceReferenceDate:currentTime];
    
    NSTimeZone *zone = [NSTimeZone systemTimeZone];
    
    NSInteger seconds = [zone secondsFromGMTForDate:date];
    NSDate *localDate = [NSDate dateWithTimeInterval:seconds sinceDate:date];
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyy-MM-dd HH:mm:ss";
    NSString *formatedDate = [formatter stringFromDate:localDate];
    fprintf(stdout,"%s %s\n", [formatedDate UTF8String], [string UTF8String]);
    fflush(stdout);
}

void LCCLoggerInfo(NSString *format, ...)
{
    if (LCCLoggerInfoEnabled && format) {
        va_list args;
        va_start(args, format);
        NSString *string = [[NSString alloc] initWithFormat:format arguments:args];
        va_end(args);
        LCCLoggerWrite(string);
    }
}

void LCCLoggerWarning(NSString *format, ...)
{
    if (LCCLoggerWarningEnabled && format) {
        va_list args;
        va_start(args, format);
        NSString *string = [[NSString alloc] initWithFormat:format arguments:args];
        va_end(args);
        LCCLoggerWrite(string);
    }
}

void LCCLoggerFatal(NSString *format, ...)
{
    if (LCCLoggerFatalEnabled &&format) {
        va_list args;
        va_start(args, format);
        NSString *string = [[NSString alloc] initWithFormat:format arguments:args];
        va_end(args);
        LCCLoggerWrite(string);
    }
}

void LCCLoggerError(NSError *error, NSString *location, NSString *action)
{
    if (!LCCLoggerErrorEnabled) {
        return;
    }
    
    if (!error) {
        return;
    }
    
    NSString *detail = [NSString stringWithFormat:@"%@ - (%ld)", [error localizedDescription], (long)[error code]];
    NSString *message = nil;
    
    if (action) {
        message = [NSString stringWithFormat:@"%@ When trying to [%@] an error has occurred:\n%@", location, action, detail];
    } else {
        message = [NSString stringWithFormat:@"%@ An error has occurred:\n%@", location, detail];
    }
    LCCLoggerWrite(message);
}

void LCCLoggerBenchmark(NSString *function)
{
    NSNumber *object = [sharedTimeCache objectForKey:function];
    if (object) {
        // end
        CFAbsoluteTime startTime = [object doubleValue];
        CFAbsoluteTime elapsedTime = CFAbsoluteTimeGetCurrent() - startTime;
        [sharedTimeCache removeObjectForKey:function];
        fprintf(stdout,"%s : %.09f(s)\n", [function UTF8String] ,elapsedTime);
        fflush(stdout);
    } else {
        // start
        CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent();
        NSNumber *object = [NSNumber numberWithDouble:startTime];
        [sharedTimeCache setObject:object forKey:function];
    }
}

void LCCLoggerMarkName(NSString *name)
{
    NSString *line = @"----------------------------------------------------------------------------------------------------";
    LCCLoggerWrite(line);
    LCCLoggerWrite(name);
    LCCLoggerWrite(line);
}
