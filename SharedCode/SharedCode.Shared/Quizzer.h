#pragma once

#include <vector>
#include <string.h>
#include <memory>

#include "CityLocation.h"
#include "QuizQuestion.h"
#include "GpsPosition.h"
#include "TTSPlayer.h"
#include "SoundEffectPlayer.h"

class Quizzer
{
public:
	Quizzer();
	~Quizzer();

	void Load();

	void NextQuestion();
	bool IsNextQuestion() const;
	const QuizQuestion& GetQuestion() const;

	bool SelectAnswer(unsigned int answerChoice) const;

private:
	void DetermineNearestCity();
	void LoadQuestions();

private:
	std::vector<QuizQuestion> _questions;
	std::vector<CityLocation> _cities;
	CityLocation _nearestCity;

	unsigned int _questionIndex;

	std::shared_ptr<GpsPosition> _gpsPosition;
	std::shared_ptr<TTSPlayer> _ttsPlayer;
	std::shared_ptr<SoundEffectPlayer> _soundPlayer;
};
