package com.example.quizzer;

import java.util.Arrays;
import java.util.List;

public class QuizQuestion {
	String question;
	List<String> answers;
	
	public QuizQuestion(String q, String[] a) {
		question = q;
		answers = Arrays.asList(a);
	}
	
	/*public void setQuestion(String q) {
		question = q;
	}*/
	
	public String GetQuestion() {
		return question;
	}
	
	/*public void setAnswers(String[] a) {
		answers = Arrays.asList(a);
	}*/
	
	public List<String> getAnswers() {
		return answers;
	}
}
