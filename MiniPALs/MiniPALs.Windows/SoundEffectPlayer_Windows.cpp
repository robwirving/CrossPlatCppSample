#include "SoundEffectPlayer_Windows.h"

SoundEffectPlayer_Windows::SoundEffectPlayer_Windows()
{
}

SoundEffectPlayer_Windows::~SoundEffectPlayer_Windows()
{
}

void SoundEffectPlayer_Windows::StartupXAudio()
{
	HRESULT hr = XAudio2Create(&m_pXAudio2, 0);

	if( hr == S_OK )
		m_pXAudio2->CreateMasteringVoice(&m_pMasterVoice);
}

void SoundEffectPlayer_Windows::PlayEffect(std::string effect)
{

}