#pragma once

#include "TTSPlayer.h"

class TTSPlayer_Android : public TTSPlayer
{
public:
	TTSPlayer_Android();
	virtual ~TTSPlayer_Android();

	void SpeakText(std::string text);
};
