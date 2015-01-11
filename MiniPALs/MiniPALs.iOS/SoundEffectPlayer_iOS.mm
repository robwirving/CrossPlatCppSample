//
//  SoundEffectPlayer_iOS.m
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#include "SoundEffectPlayer_iOS.h"
#include "PlatformConversions_iOS.h"

SoundEffectPlayer* GetSoundEffectPlayer()
{
    return new SoundEffectPlayer_iOS();
}

SoundEffectPlayer_iOS::SoundEffectPlayer_iOS()
{
    
}

SoundEffectPlayer_iOS::~SoundEffectPlayer_iOS()
{
    
}

void SoundEffectPlayer_iOS::PlayEffect(std::string text)
{
    NSString* audioFile = convertToPlatformString(text);
    NSString* audioFileName = [audioFile stringByDeletingPathExtension];
    NSString* audioFileType = [audioFile pathExtension];
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle]
                                         pathForResource:audioFileName
                                         ofType:audioFileType]];
    
    player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
    [player play];
}
