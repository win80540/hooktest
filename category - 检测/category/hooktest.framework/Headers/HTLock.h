//
//  HTLock.h
//  hooktest
//
//  Created by 田凯 on 15/10/29.
//  Copyright © 2015年 田凯. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HTLock : NSObject

+ (__nonnull instancetype)sharedInstance;

- (BOOL)unlock;

@end
