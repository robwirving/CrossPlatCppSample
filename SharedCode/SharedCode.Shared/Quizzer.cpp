#include "Quizzer.h"
#include "CalculateDistance.h"
#include <algorithm>

using namespace std;

Quizzer::Quizzer()
	: _gpsPosition(GetGpsPosition())
	, _ttsPlayer(GetTTSPlayer())
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
		city.distance = CalculateDistance::BetweenPoints(city.latitude, city.longitude, _gpsPosition->GetLatitude(), _gpsPosition->GetLongitude());

	std::sort(begin(_cities), end(_cities), [](CityLocation a, CityLocation b) {
		return a.distance < b.distance;
	});

	_nearestCity = _cities[0];
}

void Quizzer::LoadQuestions()
{
	if ( _nearestCity.name == "Redmond, WA" )
	{
		_questions.emplace_back(QuizQuestion("Redmond Question 1", { "Answer 1", "Answer 2", "Answer 3"}, 0));
		_questions.emplace_back(QuizQuestion("Redmond Question 2", { "Answer 1", "Answer 2", "Answer 3"}, 1));
		_questions.emplace_back(QuizQuestion("Redmond Question 3", { "Answer 1", "Answer 2", "Answer 3"}, 2));
	}
	else if ( _nearestCity.name == "Mountain View, CA" )
	{
		_questions.emplace_back(QuizQuestion("Mountain View Question 1", { "Answer 1", "Answer 2", "Answer 3"}, 0));
		_questions.emplace_back(QuizQuestion("Mountain View Question 2", { "Answer 1", "Answer 2", "Answer 3"}, 1));
		_questions.emplace_back(QuizQuestion("Mountain View Question 3", { "Answer 1", "Answer 2", "Answer 3"}, 2));
	}
	else if ( _nearestCity.name == "Cupertino, CA" )
	{
		_questions.emplace_back(QuizQuestion("Cupertino Question 1", { "Answer 1", "Answer 2", "Answer 3"}, 0));
		_questions.emplace_back(QuizQuestion("Cupertino Question 2", { "Answer 1", "Answer 2", "Answer 3"}, 1));
		_questions.emplace_back(QuizQuestion("Cupertino Question 3", { "Answer 1", "Answer 2", "Answer 3"}, 2));
	}
}

bool Quizzer::NextQuestion()
{
	if ( (_questionIndex + 1) < _questions.size() )
	{
		_questionIndex++;
		return true;
	}
	else
		return false;
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
		return true;
	}
	else
	{
		// play a buzzer sound
		return false;
	}
}
