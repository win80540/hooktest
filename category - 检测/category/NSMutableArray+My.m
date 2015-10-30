//
//  NSMutableArray+My.m
//  category
//
//  Created by 田凯 on 15/10/27.
//  Copyright © 2015年 田凯. All rights reserved.
//

#import "NSMutableArray+My.h"
#import <objc/message.h>
@implementation NSMutableArray (My)
//+ (void)load {
//    static dispatch_once_t onceToken;
//    dispatch_once(&onceToken, ^{
//        Class class = [self class];
//        
//        SEL originalSelector = @selector(addObject:);
//        SEL swizzledSelector = @selector(__addObject:);
//        
//        Method originalMethod = class_getInstanceMethod(class, originalSelector);
//        Method swizzledMethod = class_getInstanceMethod(class, swizzledSelector);
//        
//        BOOL didAddMethod =
//        class_addMethod(class,
//                        originalSelector,
//                        method_getImplementation(swizzledMethod),
//                        method_getTypeEncoding(swizzledMethod));
//        
//        if (didAddMethod) {
//            class_replaceMethod(class,
//                                swizzledSelector,
//                                method_getImplementation(originalMethod),
//                                method_getTypeEncoding(originalMethod));
//        } else {
//            method_exchangeImplementations(originalMethod, swizzledMethod);
//        }
//    });
//}
- (void)addObject:(id)anObject{
    printf("---------My------\n");
}
//- (void)__addObject:(id)anObject{
//    printf("---------My------\n");
//}
@end
