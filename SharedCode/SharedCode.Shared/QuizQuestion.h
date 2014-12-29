#pragma once

#include <vector>
#include <string.h>

class QuizQuestion
{
public:
	QuizQuestion();
	QuizQuestion(std::string question, std::vector<std::string> answerChoices, unsigned int answer);
	~QuizQuestion();

	std::string GetQuestion() const;
	std::vector<std::string> GetAnswers() const;
	bool IsCorrectAnswer(unsigned int answerChoice) const;

private:
	std::string _question;
	std::vector<std::string> _answerChoices;
	unsigned int _answer;
};