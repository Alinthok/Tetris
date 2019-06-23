#include "pch.h"
#include "Timer.h"

int Timer::searchID(int p_ID)
{
	for (int i = 0; i < tDataVec.size(); ++i)
	{
		if (tDataVec[i].ID == p_ID)
		{
			return i;
		}
	}
	return -1;
}

void Timer::startTime(unsigned int p_ID, sf::Time waitFor)
{
	timeData tData;
	tData.tNow = clock.getElapsedTime();
	tData.tWaitFor = waitFor;
	tData.ID = p_ID;

	int index = searchID(p_ID);
	if (index != -1)
	{
		tDataVec[index] = tData;
	}
	else
	{
		tDataVec.push_back(tData);
	}
}

void Timer::resetTime(int p_ID)
{
	int index = searchID(p_ID);
	if (index != -1)
	{
		tDataVec[index].tNow = clock.getElapsedTime();
	}
}

void Timer::deleteTime(int p_ID)
{
	int index = searchID(p_ID);
	if (index != -1)
	{
		tDataVec.erase(tDataVec.begin() + index);
	}
}

bool Timer::isPassed(int p_ID)
{
	int index = searchID(p_ID);
	if (index != -1)
	{
		if (clock.getElapsedTime() - tDataVec[index].tNow >= tDataVec[index].tWaitFor)
		{
			return true;
		}
	}
	return false;
}
