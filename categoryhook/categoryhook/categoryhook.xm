
// Logos by Dustin Howett
// See http://iphonedevwiki.net/index.php/Logos


%hook CTGLock

+ (id)sharedInstance
{
	%log;

	return %orig;
}

- (void)messageWithNoReturnAndOneArgument:(id)originalArgument
{
	%log;

	%orig(originalArgument);
	
	// or, for exmaple, you could use a custom value instead of the original argument: %orig(customValue);
}

- (id)messageWithReturnAndNoArguments
{
	%log;

	id originalReturnOfMessage = %orig;
	
	// for example, you could modify the original return value before returning it: [SomeOtherClass doSomethingToThisObject:originalReturnOfMessage];

	return originalReturnOfMessage;
}
- (BOOL)unlock{
    %log;

    BOOL resultO = %orig;
    NSLog(@"orig result %@",resultO?@"YES":@"NO");
    return YES;
}
%end
