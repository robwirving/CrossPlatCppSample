#pragma once

#include <string>

class TTSPlayer
{
public:
	TTSPlayer();
	virtual ~TTSPlayer();

	virtual void SpeakText(std::string text);
};

TTSPlayer* GetTTSPlayer();