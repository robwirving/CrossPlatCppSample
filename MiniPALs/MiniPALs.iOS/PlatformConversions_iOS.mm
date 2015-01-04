//
//  PlatformConversions_iOS.m
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#include "PlatformConversions_iOS.h"

NSString* convertToPlatformString(std::string string)
{
    NSString* nsString = [[NSString alloc] initWithCString:string.c_str() encoding:[NSString defaultCStringEncoding]];
    return nsString;
}