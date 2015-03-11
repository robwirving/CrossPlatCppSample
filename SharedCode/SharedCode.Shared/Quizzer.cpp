#include "Quizzer.h"
#include "CalculateDistance.h"
#include "SoundEffectPlayer.h"
#include <algorithm>

using namespace std;

Quizzer::Quizzer()
	: _gpsPosition(GetGpsPosition())
	, _ttsPlayer(GetTTSPlayer())
	, _soundPlayer(GetSoundEffectPlayer())
	, _questionIndex(0)
{
	_cities.emplace_back(CityLocation("Redmond, WA", 47.669444, -122.123889, 0.0));
	_cities.emplace_back(CityLocation("Mountain View, CA", 37.3896713256836, -122.081596374512, 0.0));
	_cities.emplace_back(CityLocation("Cupertino, CA", 37.3189582824707, -122.029281616211, 0.0));
}

Quizzer::~Quizzer()
{

}

void Quizzer::Load()
{
	_gpsPosition->GetCurrentPosition();

	DetermineNearestCity();

	LoadQuestions();
}

void Quizzer::DetermineNearestCity()
{
	for ( CityLocation& city : _cities )
		city.SetDistance(CalculateDistance::BetweenPoints(city.GetLatitude(), city.GetLongitude(), _gpsPosition->GetLatitude(), _gpsPosition->GetLongitude()));

	std::sort(begin(_cities), end(_cities), [](CityLocation a, CityLocation b) {
		return a.GetDistance() < b.GetDistance();
	});

	_nearestCity = _cities[0];
}

void Quizzer::LoadQuestions()
{
	if ( _nearestCity.GetName() == "Redmond, WA" )
	{
		_questions.emplace_back(QuizQuestion("Which tech company's main HQ is located in Redmond, Washington?", 
			{ "Microsoft", "Amazon", "Google"}, 0));
		_questions.emplace_back(QuizQuestion("Microsoft employees are said to celebrate their anniversaries with pounds of what candy?", 
			{ "KitKat bars", "M&Ms", "Twizzlers"}, 1));
		_questions.emplace_back(QuizQuestion("Bill Gates originally planned to release Windows under what name?", 
			{ "Longhorn", "Gateways", "Interface Manager"}, 2));
	}
	else if ( _nearestCity.GetName() == "Mountain View, CA" )
	{
		_questions.emplace_back(QuizQuestion("Which tech company's main HQ is located in Mountain View, California?", 
			{ "Google", "Yahoo", "Firefox"}, 0));
		_questions.emplace_back(QuizQuestion("Google is known for adding what to it's search home page?", 
			{ "Clippy", "Google Doodles", "Lots of clutter"}, 1));
		_questions.emplace_back(QuizQuestion("What company did Google buy in July 2006?", 
			{ "Microsoft", "Android", "Youtube"}, 2));
	}
	else if ( _nearestCity.GetName() == "Cupertino, CA" )
	{
		_questions.emplace_back(QuizQuestion("Which fruit-named tech company's main HQ is located in Cupertino, California?", 
			{ "Apple", "Blackberry", "Raspberry Pi"}, 0));
		_questions.emplace_back(QuizQuestion("What is Apple's future HQ rumored to look like?", 
			{ "An Apple", "A UFO", "A Giant iPhone"}, 1));
		_questions.emplace_back(QuizQuestion("Who designed the Apple 1 & Apple 2 Computers?", 
			{ "Steve Jobs", "Bill Gates", "Steve Wozniak"}, 2));
	}
}

void Quizzer::NextQuestion()
{
	if (IsNextQuestion())
		_questionIndex++;
}

bool Quizzer::IsNextQuestion() const
{
	return  (_questionIndex + 1) < _questions.size();
}

const QuizQuestion& Quizzer::GetQuestion() const
{
	auto question = _questions[_questionIndex];

	_ttsPlayer->SpeakText(question.GetQuestion());

	return _questions[_questionIndex];
}

bool Quizzer::SelectAnswer(unsigned int answerChoice) const
{
	if( _questions[_questionIndex].IsCorrectAnswer(answerChoice) )
	{
		// play a clapping sound
		_soundPlayer->PlayEffect("clapping.mp3");
		return true;
	}
	else
	{
		// play a buzzer sound
		_soundPlayer->PlayEffect("buzzer.mp3");
		return false;
	}
}
