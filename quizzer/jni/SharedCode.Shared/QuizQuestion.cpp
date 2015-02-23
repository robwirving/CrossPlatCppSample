#include "QuizQuestion.h"

QuizQuestion::QuizQuestion()
{

}

QuizQuestion::QuizQuestion(std::string question, std::vector<std::string> answerChoices, unsigned int answer)
	: _question(question)
	, _answerChoices(answerChoices)
	, _answer(answer)
{

}

QuizQuestion::~QuizQuestion()
{

}

std::string QuizQuestion::GetQuestion() const
{
	return _question;
}

std::vector<std::string> QuizQuestion::GetAnswers() const
{
	return _answerChoices;
}

bool QuizQuestion::IsCorrectAnswer(unsigned int answerChoice) const
{
	return (_answer == answerChoice);
}