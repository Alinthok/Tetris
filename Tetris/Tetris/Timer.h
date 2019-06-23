#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Timer
{
private:
	struct timeData
	{
		sf::Time tNow, tWaitFor;
		unsigned int ID;
	};

	sf::Clock clock;
	std::vector<timeData> tDataVec;

	int searchID(int p_ID);

public:
	void startTime(unsigned int p_ID, sf::Time waitFor);
	void resetTime(int p_ID);
	void deleteTime(int p_ID);
	bool isPassed(int p_ID);
};