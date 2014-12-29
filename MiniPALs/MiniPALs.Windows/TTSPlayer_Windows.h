#pragma once

#include <windows.h>
#include <wrl/client.h>

#include "TTSPlayer.h"

class TTSPlayer_Windows : public TTSPlayer
{
public:
	TTSPlayer_Windows();
	virtual ~TTSPlayer_Windows();

	void SpeakText(std::string text);

private:
	Platform::Agile<Windows::Media::SpeechSynthesis::SpeechSynthesizer> _speechSynth;
};