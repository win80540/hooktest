//
//  validate.h
//  category
//
//  Created by 田凯 on 15/10/28.
//  Copyright © 2015年 田凯. All rights reserved.
//

#ifndef validate_h
#define validate_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <objc/message.h>
#include <dlfcn.h>
#include <CoreFoundation/CoreFoundation.h>
#define __inline __attribute__ ((always_inline))
#endif /* validate_h */

void printMethodFrameInfo(const char *cls,const char *sel);
void printClassMethodFrameInfo(const char *cls);
void printClassMethodsInfo(const char *cls);
const char ** getImagePaths(const char *cls);
const char * getSandboxPath();
const char * getExecutablePath();

typedef enum
{
    ValidateFrameName = 1 << 0,
    ValidateIgnoreSandBoxFrameName = 1 << 1,
    ValidateIgnoreFramePath = 1 << 2,
    ValidateSymbolName = 1 << 3,
}
ValildateFlag;
typedef enum
{
    ValildateErrorNoError = 0,
    ValildateErrorFrameError = 1,
    ValildateErrorSymbolError = 2,
}
ValildateResult;


/** @brief validate the specified method whether modified
 *  @sa ValildateFlag
 *  @param cls class name
 *  @param sel method name
 *  @param flag valildateFlag validate option
 *  @param ... validate frame list
 *  @return int 0／1 failed/success
 */
static inline int validate_class_method(const char *cls,const char *sel, ValildateFlag flag,...) __inline;

int validate_class_method(const char *cls,const char *sel,ValildateFlag flag,...){
    Class aClass = objc_getClass(cls);
    Dl_info info;
    IMP imp;
    char buf[128];
    const char *fname;
    ValildateResult validateResult = ValildateErrorNoError;
    
    if(!aClass)
        return 0;
    
    int ignore_sandbox = flag & ValidateIgnoreSandBoxFrameName;
    int ignore_framepath = flag & ValidateIgnoreFramePath;
    int validate_frame = flag & ValidateFrameName;
    int validate_symbol = flag & ValidateSymbolName;
    
    printf("validating [%s %s]\n",cls,sel);
    imp = class_getMethodImplementation(aClass, sel_registerName(sel));
    if(!imp){
        printf("error:method_getImplementation(%s) failed\n",sel);
        return 0;
    }
    
    if(!dladdr(imp, &info)){
        printf("error:dladdr() failed for %s\n",sel);
        return 0;
    }
    
    if (validate_frame) { /*Validate image path*/
        int isNeedCmp = 1;
        
        if (ignore_sandbox) {
            const char * sandboxPath =  getSandboxPath();
            if(strncmp(info.dli_fname, sandboxPath, strlen(sandboxPath)) == 0){
                isNeedCmp = 0;
            }
        }
        
        if (isNeedCmp) {
            int validate = 1;
            va_list paramList;
            va_start(paramList, flag);
            fname = va_arg(paramList, const char *);
            while (strcmp(fname, "")) {
                if (ignore_framepath) {
                    validate = strncmp(info.dli_fname + (strlen(info.dli_fname) - strlen(fname)), fname, strlen(fname)) == 0;
                }else{
                    validate = strcmp(info.dli_fname, fname) == 0;
                }
                if (validate) {
                    break;
                }
                fname = va_arg(paramList, const char *);
            }
            if(!validate){
                validateResult = ValildateErrorFrameError;
                goto FAIL;
            }
        }
    }
    
    if (validate_symbol) { /*Validate in symbol*/
        if (info.dli_sname != NULL && strcmp(info.dli_sname, "<redacted>") != 0) {
            /*Validate class name in symbol*/
            snprintf(buf, sizeof(buf), "[%s ",(const char *) class_getName(aClass));
            if(strncmp(info.dli_sname + 1, buf, strlen(buf))){
                snprintf(buf, sizeof(buf),"[%s(",(const char *)class_getName(aClass));
                if(strncmp(info.dli_sname + 1, buf, strlen(buf))){
                    validateResult = ValildateErrorSymbolError;
                    goto FAIL;
                }
            }
            
            /*Validate selector in symbol*/
            snprintf(buf, sizeof(buf), " %s]",sel);
            if(strncmp(info.dli_sname + (strlen(info.dli_sname) - strlen(buf)), buf, strlen(buf))){
                validateResult = ValildateErrorSymbolError;
                goto FAIL;
            }
        }else{
            printf("<redacted>  \n");
        }
    }
    
    
    return 1;
    
FAIL:
    printf("method %s failed integrity test(%s):\n",
           sel,validateResult == ValildateErrorFrameError?"Frame Failed":"Symbol Failed");
    printf("    dli_fname:%s\n",info.dli_fname);
    printf("    dli_sname:%s\n",info.dli_sname);
    printf("    dli_fbase:%p\n",info.dli_fbase);
    printf("    dli_saddr:%p\n",info.dli_saddr);
    return 0;
}

/** @brief validate class whether modified
 *  @sa ValildateFlag
 *  @param cls class name
 *  @param flag valildateFlag validate option
 *  @param ... validate frame list
 *  @return int 0／1 failed/success
 */
static inline int validate_class(const char *cls,ValildateFlag flag,...) __inline;

int validate_class(const char *cls,ValildateFlag flag,...){
    Class aClass = objc_getClass(cls);
    Method *methods;
    unsigned int nMethods;
    Dl_info info;
    IMP imp;
    char buf[128];
    Method m;
    const char *fname;
    ValildateResult validateResult = ValildateErrorNoError;
    
    if(!aClass)
        return 0;
    
    int ignore_sandbox = flag & ValidateIgnoreSandBoxFrameName;
    int ignore_framepath = flag & ValidateIgnoreFramePath;
    int validate_frame = flag & ValidateFrameName;
    int validate_symbol = flag & ValidateSymbolName;
    
    methods = class_copyMethodList(aClass, &nMethods);
    while (nMethods--) {
        m = methods[nMethods];
        printf("validating [%s %s]\n",(const char *)class_getName(aClass),sel_getName(method_getName(m)));
        
        imp = method_getImplementation(m);
        //imp = class_getMethodImplementation(aClass, sel_registerName("allObjects"));
        if(!imp){
            printf("error:method_getImplementation(%s) failed\n",sel_getName(method_getName(m)));
            free(methods);
            return 0;
        }
        
        if(!dladdr(imp, &info)){
            printf("error:dladdr() failed for %s\n",sel_getName(method_getName(m)));
            free(methods);
            return 0;
        }
        
        if (validate_frame) { /*Validate image path*/
            int isNeedCmp = 1;
            
            if (ignore_sandbox) {
                const char * sandboxPath =  getSandboxPath();
                if(strncmp(info.dli_fname, sandboxPath, strlen(sandboxPath)) == 0){
                    isNeedCmp = 0;
                }
            }
            
            if (isNeedCmp) {
                int validate = 1;
                va_list paramList;
                va_start(paramList, flag);
                fname = va_arg(paramList, const char *);
                while (strcmp(fname, "")) {
                    if (ignore_framepath) {
                        validate = strncmp(info.dli_fname + (strlen(info.dli_fname) - strlen(fname)), fname, strlen(fname)) == 0;
                    }else{
                        validate = strcmp(info.dli_fname, fname) == 0;
                    }
                    if (validate) {
                        break;
                    }
                    fname = va_arg(paramList, const char *);
                }
                if(!validate){
                    validateResult = ValildateErrorFrameError;
                    goto FAIL;
                }
            }
        }

        if (validate_symbol) { /*Validate in symbol*/
            if (info.dli_sname != NULL && strcmp(info.dli_sname, "<redacted>") != 0) {
                /*Validate class name in symbol*/
                snprintf(buf, sizeof(buf), "[%s ",(const char *) class_getName(aClass));
                if(strncmp(info.dli_sname + 1, buf, strlen(buf))){
                    snprintf(buf, sizeof(buf),"[%s(",(const char *)class_getName(aClass));
                    if(strncmp(info.dli_sname + 1, buf, strlen(buf))){
                        validateResult = ValildateErrorSymbolError;
                        goto FAIL;
                    }
                }
                
                /*Validate selector in symbol*/
                snprintf(buf, sizeof(buf), " %s]",sel_getName(method_getName(m)));
                if(strncmp(info.dli_sname + (strlen(info.dli_sname) - strlen(buf)), buf, strlen(buf))){
                    validateResult = ValildateErrorSymbolError;
                    goto FAIL;
                }
            }else{
                printf("<redacted>  \n");
            }
        }
    }
    
    return 1;
    
FAIL:
    printf("method %s failed integrity test(%s):\n",
           sel_getName(method_getName(m)),validateResult == ValildateErrorFrameError?"Frame Failed":"Symbol Failed");
    printf("    dli_fname:%s\n",info.dli_fname);
    printf("    dli_sname:%s\n",info.dli_sname);
    printf("    dli_fbase:%p\n",info.dli_fbase);
    printf("    dli_saddr:%p\n",info.dli_saddr);
    free(methods);
    return 0;
}