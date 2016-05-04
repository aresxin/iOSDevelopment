//
//  DWAuthenticationManager.m
//  DWViewer
//
//  Created by xinjun xu on 12-3-22.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import "DWAuthenticationManager.h"

@implementation DWAuthenticationManager

- (id)init
{
	self = [super init];
	if (self != nil) 
	{
		mpcSession_		= NULL;
		mpcDocObject_	= NULL;
		mpcPageRoot_	= NULL;
		mpcProfile_		= NULL;
	}
	
	return self;
}

- (DW_PROTECTED_TYPE) checkDocumentProtectedType:(NSString*)filepath;
{
	DW_PROTECTED_TYPE result = kProtectTypeNull;
	
	if (filepath == nil)
	{
		return kProtectTypeNull;
	}
	
	const char *filepath_const_char = [filepath UTF8String];
	char filepath_char[1024] = { 0 };
	strcpy(filepath_char, filepath_const_char);
	HRESULT hres	= MP_NOERROR;
	mpcSession_		= ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession_ == XdwNull)
	{
		return kProtectTypeNull;
	}
	
	mpcDocObject_ = mpcSession_->OpenFile(filepath_char, &hres, MP_READONLY);
	if (hres != MP_NOERROR || mpcDocObject_ == XdwNull)
	{
		::MPCDestroyMPCSession(mpcSession_);
		
		return kProtectTypeNull;
	}
	
	mpcProfile_ = (MPCProfile*)mpcDocObject_->GetInterface(IID_MPCProfile, &hres);
	if (hres != MP_NOERROR || mpcProfile_ == XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
		
		return kProtectTypeNull;
	}
	
	hres = mpcProfile_->OpenMP();
	if (hres == MP_S_PROTECTED_BY_PSWD || hres == MP_S_PROTECTED_BY_PSWD128)
	{
		if ([self openProtectedDocument:mpcProfile_ andPassword:@""] == YES)
		{
			result = kProtectTypeNoPwd;
		}
		else
		{
			result = kProtectTypePwd;
		}
	}
	
	if (mpcSession_ != XdwNull && mpcDocObject_ != XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
	}
	
	return result;
}

- (BOOL) isDocumentProtected:(NSString*)filepath
{
	BOOL result = NO;
	
	if (filepath == nil)
	{
		return result;
	}
	
	const char *filepath_const_char = [filepath UTF8String];
	char filepath_char[1024] = { 0 };
	strcpy(filepath_char, filepath_const_char);
	HRESULT hres	= MP_NOERROR;
	mpcSession_		= ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession_ == XdwNull)
	{
		return result;
	}
	
	mpcDocObject_ = mpcSession_->OpenFile(filepath_char, &hres, MP_READONLY);
	if (hres != MP_NOERROR || mpcDocObject_ == XdwNull)
	{
		::MPCDestroyMPCSession(mpcSession_);
		
		return result;
	}
	
	mpcProfile_ = (MPCProfile*)mpcDocObject_->GetInterface(IID_MPCProfile, &hres);
	if (hres != MP_NOERROR || mpcProfile_ == XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
		
		return result;
	}
	
	hres = mpcProfile_->OpenMP();
	if (hres == MP_S_PROTECTED_BY_PSWD || 
		hres == MP_S_PROTECTED_BY_PSWD128 || 
		hres == MP_S_PROTECTED_BY_DDSA ||
		hres == MP_S_PROTECTED_BY_PKST ||
		hres == MP_S_PROTECTED_BY_SDES)
	{
		result = YES;
	}
	
	if (mpcSession_ != XdwNull && mpcDocObject_ != XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
	}
	
	return result;
}

- (BOOL) canOpenProtectedDocument:(NSString*)filepath withPassword:(NSString*)pwd
{
	BOOL canOpen = NO;
	
	if (filepath == nil || pwd == nil)
	{
		return canOpen;
	}
	
	const char *filepath_const_char = [filepath UTF8String];
	char filepath_char[1024] = { 0 };
	strcpy(filepath_char, filepath_const_char);
	
	HRESULT hres	= MP_NOERROR;
	mpcSession_		= ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession_ == XdwNull)
	{
		return canOpen;
	}
	
	mpcDocObject_ = mpcSession_->OpenFile(filepath_char, &hres, MP_READONLY);
	if (hres != MP_NOERROR || mpcDocObject_ == XdwNull)
	{
		return canOpen;
	}
	
	mpcProfile_ = (MPCProfile*)mpcDocObject_->GetInterface(IID_MPCProfile, &hres);
	if (hres != MP_NOERROR || mpcProfile_ == XdwNull)
	{
		return canOpen;
	}
	
	if ([self openProtectedDocument:mpcProfile_ andPassword:pwd] == YES)
	{
		canOpen = YES;
	}
	
	if (mpcSession_ != XdwNull && mpcDocObject_ != XdwNull)
	{
		mpcSession_->CloseFile(mpcDocObject_, 0);
		::MPCDestroyMPCSession(mpcSession_);
	}
	
	return canOpen;
}

- (BOOL) openProtectedDocument:(MPCProfile*)mpcProfile andPassword:(NSString*)pwd
{
	if (mpcProfile == NULL)
	{
		return NO;
	}
	
	MP_AuthInfo authInfo;
	authInfo.mode = MP_AUTH_DIALOGUE;
	authInfo.perm = 0;
	
	PasswordSecurityAuthData authdata;
	authdata.size = sizeof(PasswordSecurityAuthData);
	authdata.type = 0;
	
	const char *password_const_char = [pwd UTF8String];
	strcpy(authdata.password, password_const_char);
	
	HRESULT hres = mpcProfile_->OpenMP(&authInfo, &authdata);
	if (hres == MP_NOERROR)
	{
		return YES;
	}
	
	return NO;
}

- (void)dealloc
{
	mpcSession_		= NULL;
	mpcDocObject_	= NULL;
	mpcPageRoot_	= NULL;
	mpcProfile_		= NULL;
	
	[super dealloc];
}

@end
