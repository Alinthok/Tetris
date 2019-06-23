#include "pch.h"
#include "HighScore.h"

void HighScore::swapHighScoreDate(HighScoreData& h1, HighScoreData& h2)
{
	HighScoreData temp = h1;
	h1 = h2;
	h2 = temp;
}

void HighScore::dropScore(int place, int level)
{
	for (int i = MAXHIGHSCORE - 1; i > place; i--)
	{
		swapHighScoreDate(HighScoreDataArray[i - 1][level], HighScoreDataArray[i][level]);
	}
	HighScoreDataArray[place][level].score = -1;
	HighScoreDataArray[place][level].name = "";
}

void HighScore::makeFile()
{
	std::ofstream outFile;
	outFile.open(fileName);

	for (int level = 0; level < MAXLEVEL; ++level)
	{
		for (int place = 0; place < MAXHIGHSCORE; ++place)
		{
			outFile << "-1" << std::endl;
			outFile << "-1" << std::endl;
		}
		outFile << "########################################" << std::endl;
	}
}

HighScore::HighScore()
{
	readHighScoreFile();
}

void HighScore::readHighScoreFile()
{
	std::ifstream inFile;

	inFile.open(fileName);
	if (!inFile) {
		makeFile();
		inFile.open(fileName);
	}

	for (int level = 0; level < MAXLEVEL; ++level)
	{
		for (int place = 0; place < MAXHIGHSCORE; ++place)
		{
			std::string name;
			std::string number;
			std::getline(inFile, name);
			std::getline(inFile, number);
			long num = stoi(number);

			HighScoreData highScore;
			highScore.name = name;
			highScore.score = num;
			HighScoreDataArray[place][level] = highScore;
		}
		std::string skipLine;
		std::getline(inFile, skipLine);
	}
	inFile.close();
}

void HighScore::writeHighScoreFile()
{
	std::ofstream outFile;
	outFile.open(fileName);

	for (int level = 0; level < MAXLEVEL; ++level)
	{
		for (int place = 0; place < MAXHIGHSCORE; ++place)
		{
			outFile << HighScoreDataArray[place][level].name << std::endl;
			outFile << HighScoreDataArray[place][level].score << std::endl;
		}
		outFile << "########################################" << std::endl;
	}
}

void HighScore::setName(int place, int level, std::string name)
{
	HighScoreDataArray[place][level].name = name;
}

void HighScore::setScore(int place, int level, long score)
{
	HighScoreDataArray[place][level].score = score;
}

void HighScore::addLetter(int place, int level, char letter)
{
	HighScoreDataArray[place][level].name.push_back(letter);
}

void HighScore::deleteLetter(int place, int level)
{
	HighScoreDataArray[place][level].name.pop_back();
}

bool HighScore::canPlaceHighScoreAndDropScore(long score, int level)
{
	for (int i = 0; i < MAXHIGHSCORE; i++)
		if (score >= getScore(i, level))
		{
			dropScore(i, level);
			return true;
		}
	return false;
}

long HighScore::getScore(int place, int level)
{
	return HighScoreDataArray[place][level].score;
}


std::string HighScore::getName(int place, int level)
{
	return HighScoreDataArray[place][level].name;
}

void HighScore::draw()
{
	for (int level = 0; level < MAXLEVEL; ++level)
	{
		for (int place = 0; place < MAXHIGHSCORE; ++place)
		{
			std::cout << HighScoreDataArray[place][level].name << " " << HighScoreDataArray[place][level].score << std::endl;
		}
	}
}
