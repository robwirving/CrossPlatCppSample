//
//  TTSPlayer_iOS.h
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#ifndef SampleApp_iOS_TTSPlayer_iOS_h
#define SampleApp_iOS_TTSPlayer_iOS_h

#import <AVFoundation/AVFoundation.h>

#include "TTSPlayer.h"

class TTSPlayer_iOS : public TTSPlayer
{
public:
    TTSPlayer_iOS();
    virtual ~TTSPlayer_iOS();
    
    void SpeakText(std::string text) override;
    
private:
    AVSpeechSynthesizer* _speechSynthesizer;
};

#endif
