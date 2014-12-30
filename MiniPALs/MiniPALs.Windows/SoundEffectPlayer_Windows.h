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

	void StartupXAudio();

	void PlayEffect(std::string text);

private:
	IXAudio2*					m_pXAudio2;
	IXAudio2MasteringVoice*		m_pMasterVoice;
};