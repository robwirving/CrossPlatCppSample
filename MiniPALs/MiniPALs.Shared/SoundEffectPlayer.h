#pragma once

#include <string.h>

class SoundEffectPlayer
{
public:
	SoundEffectPlayer();
	virtual ~SoundEffectPlayer();

	virtual void PlayEffect(std::string text);
};

SoundEffectPlayer* GetSoundEffectPlayer();