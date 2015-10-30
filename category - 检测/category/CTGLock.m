//
//  CTGLock.m
//  category
//
//  Created by 田凯 on 15/10/28.
//  Copyright © 2015年 田凯. All rights reserved.
//

#import "CTGLock.h"

@implementation CTGLock

+ (__nonnull instancetype)sharedInstance{
    static CTGLock * instance;
    static dispatch_once_t t;
    dispatch_once(&t, ^{
         instance = [[CTGLock alloc] init];
    });
    return instance;
}

- (BOOL)unlock{
    return NO;
}
@end
