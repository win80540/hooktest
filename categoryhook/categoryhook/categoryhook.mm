#line 1 "/Users/tiankai/Documents/Project/Learn/网易分享相关/函数拦截与检测/categoryhook/categoryhook/categoryhook.xm"





#include <logos/logos.h>
#include <substrate.h>
@class CTGLock; 
static id (*_logos_meta_orig$_ungrouped$CTGLock$sharedInstance)(Class, SEL); static id _logos_meta_method$_ungrouped$CTGLock$sharedInstance(Class, SEL); static void (*_logos_orig$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$)(CTGLock*, SEL, id); static void _logos_method$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$(CTGLock*, SEL, id); static id (*_logos_orig$_ungrouped$CTGLock$messageWithReturnAndNoArguments)(CTGLock*, SEL); static id _logos_method$_ungrouped$CTGLock$messageWithReturnAndNoArguments(CTGLock*, SEL); static BOOL (*_logos_orig$_ungrouped$CTGLock$unlock)(CTGLock*, SEL); static BOOL _logos_method$_ungrouped$CTGLock$unlock(CTGLock*, SEL); 

#line 6 "/Users/tiankai/Documents/Project/Learn/网易分享相关/函数拦截与检测/categoryhook/categoryhook/categoryhook.xm"



static id _logos_meta_method$_ungrouped$CTGLock$sharedInstance(Class self, SEL _cmd) {
	NSLog(@"+[<CTGLock: %p> sharedInstance]", self);

	return _logos_meta_orig$_ungrouped$CTGLock$sharedInstance(self, _cmd);
}


static void _logos_method$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$(CTGLock* self, SEL _cmd, id originalArgument) {
	NSLog(@"-[<CTGLock: %p> messageWithNoReturnAndOneArgument:%@]", self, originalArgument);

	_logos_orig$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$(self, _cmd, originalArgument);
	
	
}


static id _logos_method$_ungrouped$CTGLock$messageWithReturnAndNoArguments(CTGLock* self, SEL _cmd) {
	NSLog(@"-[<CTGLock: %p> messageWithReturnAndNoArguments]", self);

	id originalReturnOfMessage = _logos_orig$_ungrouped$CTGLock$messageWithReturnAndNoArguments(self, _cmd);
	
	

	return originalReturnOfMessage;
}
static BOOL _logos_method$_ungrouped$CTGLock$unlock(CTGLock* self, SEL _cmd){
    NSLog(@"-[<CTGLock: %p> unlock]", self);

    BOOL resultO = _logos_orig$_ungrouped$CTGLock$unlock(self, _cmd);
    NSLog(@"orig result %@",resultO?@"YES":@"NO");
    return YES;
}

static __attribute__((constructor)) void _logosLocalInit() {
{Class _logos_class$_ungrouped$CTGLock = objc_getClass("CTGLock"); Class _logos_metaclass$_ungrouped$CTGLock = object_getClass(_logos_class$_ungrouped$CTGLock); MSHookMessageEx(_logos_metaclass$_ungrouped$CTGLock, @selector(sharedInstance), (IMP)&_logos_meta_method$_ungrouped$CTGLock$sharedInstance, (IMP*)&_logos_meta_orig$_ungrouped$CTGLock$sharedInstance);MSHookMessageEx(_logos_class$_ungrouped$CTGLock, @selector(messageWithNoReturnAndOneArgument:), (IMP)&_logos_method$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$, (IMP*)&_logos_orig$_ungrouped$CTGLock$messageWithNoReturnAndOneArgument$);MSHookMessageEx(_logos_class$_ungrouped$CTGLock, @selector(messageWithReturnAndNoArguments), (IMP)&_logos_method$_ungrouped$CTGLock$messageWithReturnAndNoArguments, (IMP*)&_logos_orig$_ungrouped$CTGLock$messageWithReturnAndNoArguments);MSHookMessageEx(_logos_class$_ungrouped$CTGLock, @selector(unlock), (IMP)&_logos_method$_ungrouped$CTGLock$unlock, (IMP*)&_logos_orig$_ungrouped$CTGLock$unlock);} }
#line 42 "/Users/tiankai/Documents/Project/Learn/网易分享相关/函数拦截与检测/categoryhook/categoryhook/categoryhook.xm"
