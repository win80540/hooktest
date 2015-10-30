//
//  HTLock.m
//  hooktest
//
//  Created by 田凯 on 15/10/29.
//  Copyright © 2015年 田凯. All rights reserved.
//

#import "HTLock.h"
#import <objc/message.h>
#include "validate.h"
@implementation HTLock

+ (__nonnull instancetype)sharedInstance{
    static HTLock * instance;
    static dispatch_once_t t;
    dispatch_once(&t, ^{
        if(validate_class(class_getName([self class]),ValidateFrameName | ValidateSymbolName | ValidateIgnoreFramePath,
                          "hooktest.framework/hooktest",
                          ""))
        {
            instance = [[HTLock alloc] init];
        }
    });
    return instance;
}

- (BOOL)unlock{
    return false;
}

@end
