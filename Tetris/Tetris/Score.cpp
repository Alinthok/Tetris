#include "pch.h"
#include "Score.h"

void Score::addScore(long n)
{
	score += n;
}

void Score::updateLevel()
{
	if (lineCleared == (lvl + 1) * 10)
	{
		lvl++;
	}
}

void Score::setLvl(int n)
{
	lvl = n;
}

void Score::setStartLvl(int n)
{
	startLvl = n;
}

void Score::reset()
{
	score = 0;
	lvl = 0;
	lineCleared = 0;
}

void Score::addLineCleared(int n)
{
	lineCleared += n;
}

void Score::addClearLineScore(int n)
{
	switch (n)
	{
	case 1:
		addScore(40 * (lvl + 1));
		break;
	case 2:
		addScore(100 * (lvl + 1));
		break;
	case 3:
		addScore(300 * (lvl + 1));
		break;
	case 4:
		addScore(1200 * (lvl + 1));
		break;
	default:
		break;
	}
}

long Score::getScore()
{
	return score;
}

int Score::getLevel()
{
	return lvl;
}

int Score::getStartLvl()
{
	return startLvl;
}

int Score::getLineCleared()
{
	return lineCleared;
}
