//
//  SoundEffectPlayer_iOS.h
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#ifndef SampleApp_iOS_SoundEffectPlayer_iOS_h
#define SampleApp_iOS_SoundEffectPlayer_iOS_h

#import <AVFoundation/AVFoundation.h>
#include "SoundEffectPlayer.h"

class SoundEffectPlayer_iOS : public SoundEffectPlayer
{
public:
    SoundEffectPlayer_iOS();
    virtual ~SoundEffectPlayer_iOS();
    
    void PlayEffect(std::string text) override;
    
private:
    AVAudioPlayer*  player;
};

#endif
