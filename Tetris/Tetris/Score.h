#pragma once

class Score
{
private:
	long score{ 0 };
	int lvl{ 0 };
	int startLvl{ 0 };
	int lineCleared{ 0 };

public:
	void addLineCleared(int n);
	void addClearLineScore(int n);
	void addScore(long n);
	void updateLevel();
	void setLvl(int n);
	void setStartLvl(int n);
	void reset();
	long getScore();
	int getLevel();
	int getStartLvl();
	int getLineCleared();
};

