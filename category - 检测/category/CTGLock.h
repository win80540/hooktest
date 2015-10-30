//
//  CTGLock.h
//  category
//
//  Created by 田凯 on 15/10/28.
//  Copyright © 2015年 田凯. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTGLock : NSObject

+ (__nonnull instancetype)sharedInstance;

- (BOOL)unlock;

@end
