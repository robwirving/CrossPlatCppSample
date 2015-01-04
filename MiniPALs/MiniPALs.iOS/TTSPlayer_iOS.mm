//
//  TTSPlayer_iOS.m
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "TTSPlayer_iOS.h"
#include "PlatformConversions_iOS.h"

TTSPlayer* GetTTSPlayer()
{
    return new TTSPlayer_iOS();
}

TTSPlayer_iOS::TTSPlayer_iOS()
{
    _speechSynthesizer = [[AVSpeechSynthesizer alloc] init];
}

TTSPlayer_iOS::~TTSPlayer_iOS()
{
    
}

void TTSPlayer_iOS::SpeakText(std::string text)
{
    AVSpeechUtterance *utterance = [AVSpeechUtterance speechUtteranceWithString:convertToPlatformString(text)];
    [utterance setRate:0.4f];
    [_speechSynthesizer speakUtterance:utterance];
}
