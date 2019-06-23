#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class HighScore
{
private:
	struct HighScoreData
	{
		long score = 0;
		std::string name;
	};

	const int MAXHIGHSCORE{ 3 };
	const int MAXLEVEL{ 10 };
	HighScoreData HighScoreDataArray[3][10];
	std::string fileName{ "HighScores.txt" };

	void swapHighScoreDate(HighScoreData& h1, HighScoreData& h2);
	void dropScore(int place, int level);
	void makeFile();
	
public:
	HighScore();
	void readHighScoreFile();
	void writeHighScoreFile();
	void setName(int place, int level, std::string);
	void setScore(int place, int level, long score);
	void addLetter(int place, int level, char letter);
	void deleteLetter(int place, int level);
	bool canPlaceHighScoreAndDropScore(long score, int level);
	long getScore(int place, int level);
	std::string getName(int place, int level);
	void draw();
};