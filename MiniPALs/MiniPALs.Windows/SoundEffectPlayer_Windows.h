#pragma once

#include <windows.h>
#include <XAudio2.h>
#include <wrl/client.h>

#include "SoundEffectPlayer.h"

class SoundEffectPlayer_Windows : public SoundEffectPlayer
{
public:
	SoundEffectPlayer_Windows();
	virtual ~SoundEffectPlayer_Windows();

	void PlayEffect(std::string text);
};