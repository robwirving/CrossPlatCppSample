#pragma once

#include <string>

class SoundEffectPlayer
{
public:
	SoundEffectPlayer();
	virtual ~SoundEffectPlayer();

	virtual void PlayEffect(std::string text);
};

SoundEffectPlayer* GetSoundEffectPlayer();