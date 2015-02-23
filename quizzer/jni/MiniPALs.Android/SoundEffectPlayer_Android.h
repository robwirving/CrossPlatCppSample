#pragma once

#include "SoundEffectPlayer.h"

class SoundEffectPlayer_Android : public SoundEffectPlayer
{
public:
	SoundEffectPlayer_Android();
	virtual ~SoundEffectPlayer_Android();

	void PlayEffect(std::string text);
};
