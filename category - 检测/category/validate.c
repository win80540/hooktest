
//  validate.c
//  category
//
//  Created by 田凯 on 15/10/28.
//  Copyright © 2015年 田凯. All rights reserved.
//

#include "validate.h"

int containStrInArray(const char ** array,const char * str,unsigned int length);



void printMethodFrameInfo(const char *cls,const char *sel){
    Dl_info info;
    IMP imp = class_getMethodImplementation(objc_getClass(cls), sel_registerName(sel));

    printf("function pointer %p\n",imp);

    if (dladdr(imp, &info)) {
        printf("dli_fname %s\n",info.dli_fname);
        printf("dli_fbase %p\n",info.dli_fbase);
        printf("dli_sname %s\n",info.dli_sname);
        printf("dli_saddr %p\n",info.dli_saddr);
    }

}

void printClassMethodFrameInfo(const char *cls){
    const char ** paths = getImagePaths(cls);
    int length = 0;
    printf("----%s method implemetation come from:----\n",cls);
    while (NULL != paths[length]) {
        printf("     \"%s\",\n",paths[length]);
        length++;
    }
    printf("----%s----\n",cls);
}

void printClassMethodsInfo(const char *cls){
    Dl_info info;
    Class aClass = objc_getClass(cls);
    Method *methods;
    Method m;
    unsigned int nMethod;
    IMP imp;
    
    if (!aClass) {
        printf("%s is not a Class",cls);
        return;
    }
    
    methods = class_copyMethodList(aClass, &nMethod);
    while (nMethod--) {
        m = methods[nMethod];
        imp = method_getImplementation(m);
        printf("function pointer %p\n",imp);
        
        if (dladdr(imp, &info)) {
            printf("dli_fname %s\n",info.dli_fname);
            printf("dli_fbase %p\n",info.dli_fbase);
            printf("dli_sname %s\n",info.dli_sname);
            printf("dli_saddr %p\n",info.dli_saddr);
        }
    }
    free(methods);
}

const char **  getImagePaths(const char *cls){
    Dl_info info;
    Class aClass = objc_getClass(cls);
    Method *methods;
    Method m;
    unsigned int nMethod;
    unsigned int i = 0;
    IMP imp;
    const char ** paths;
    
    if (!aClass) {
        printf("%s is not a Class",cls);
        return NULL;
    }
    methods = class_copyMethodList(aClass, &nMethod);
    paths = (const char **)calloc(nMethod, sizeof(char *));
    while (nMethod--) {
        m = methods[nMethod];
        imp = method_getImplementation(m);
        if (dladdr(imp, &info)) {
            if(containStrInArray(paths, info.dli_fname,i)){
                continue;
            }
            paths[i] = info.dli_fname;
            i++;
        }
    }
    free(methods);
    return paths;
}

int containStrInArray(const char ** array,const char * str,unsigned int length){
    for (unsigned int i = 0; i < length; i++) {
        if (strcmp(array[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

const char * getExecutablePath()
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef url = CFBundleCopyExecutableURL(mainBundle);
    CFStringRef strPath = CFURLCopyFileSystemPath(url,kCFURLPOSIXPathStyle);
    const char* cstr = CFStringGetCStringPtr( strPath, kCFStringEncodingUTF8 );
    return cstr;
}

const char * getSandboxPath()
{
    char * result;
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef url = CFBundleCopyExecutableURL(mainBundle);
    CFStringRef strPath = CFURLCopyFileSystemPath(url,kCFURLPOSIXPathStyle);
    const char* cstr = CFStringGetCStringPtr( strPath, kCFStringEncodingUTF8 );
    int index = 0;
    int length = (int)strlen(cstr);
    for (int i=0; i< length;i++ ) {
        if(cstr[i] == '/'){
            index = i;
        }
    }
    result = (char *)calloc(index+2, sizeof(char));
    strncpy(result, cstr, index+1);
    result[index+2] = '\0';
    return result;
}