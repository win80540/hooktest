//
//  ViewController.m
//  category
//
//  Created by 田凯 on 15/10/27.
//  Copyright © 2015年 田凯. All rights reserved.
//
#import "CTGLock.h"
#import "ViewController.h"
#import <hooktest/hooktest.h>
#import "HTLock+CTG.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    printMethodFrameInfo("NSMutableArray", "addObject:");
    
//    if(validate_class_method("NSMutableArray", "addObject:", ValidateSymbolName ,
//                      "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation",
//                      ""
//                      ))
//    {
//        NSLog(@"safe");
//    }else{
//        NSLog(@"dangerous");
//    }
    
//    printClassMethodsInfo("NSMutableArray");

//    printClassMethodFrameInfo(cls);
    
    
    
//    HTLock *htLock = [HTLock sharedInstance];
//    BOOL isLock = [htLock unlock];
    

 
//    
//    if(validate_class("CTGLock",ValidateFrameName | ValidateIgnoreSandBoxFrameName |ValidateSymbolName,
//                   getExecutablePath(),
//                   ""
//                      ))
//    {
//        NSLog(@"safe");
//    }else{
//        NSLog(@"dangerous");
//    }

//    printClassMethodFrameInfo("NSMutableArray");
    



#if TARGET_OS_SIMULATOR
    if(validate_class("NSMutableArray",ValidateSymbolName,
                      "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation",
                      "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/Foundation.framework/Foundation",
                      "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/PrivateFrameworks/BaseBoard.framework/BaseBoard",
                      "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/System/Library/Frameworks/UIKit.framework/UIKit",
                      ""
                      ))
#else
    if(validate_class("NSMutableArray",ValidateFrameName | ValidateIgnoreSandBoxFrameName,
                      getExecutablePath(),
                      "/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation",
                      "/System/Library/PrivateFrameworks/IMFoundation.framework/IMFoundation",
                      "/System/Library/Frameworks/UIKit.framework/UIKit",
                      "/System/Library/Frameworks/Foundation.framework/Foundation",
                      "/System/Library/PrivateFrameworks/ProtocolBuffer.framework/ProtocolBuffer",
                      "/System/Library/PrivateFrameworks/CoreMediaStream.framework/CoreMediaStream",
                      "/System/Library/PrivateFrameworks/AccessibilityUtilities.framework/AccessibilityUtilities",
                      ""
                      ))
#endif
    
    {
        NSLog(@"safe");
    }else{
        NSLog(@"dangerous");
    }

    
    
 
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end




