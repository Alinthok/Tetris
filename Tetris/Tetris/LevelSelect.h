#pragma once
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Timer.h"
#include "Score.h"
#include "GameStates.h"
#include "HighScore.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class LevelSelect : public GameStates
{
private:
	const int ROW{ 2 };
	const int COLUMN{ 5 };
	const int MAXHIGHSCORE{ 3 };

	bool flash{ false };
	int selectedLvl{ -1 };
	sf::Vector2i choice{ 0,0 };
	HighScore* highScore;
	Score* score;
	Timer timer;

	void toggleBool(bool& bl);

public:
	LevelSelect(Render* p_renderer, Score* p_score, HighScore* p_highScore);
	void activate();
	void update();
	void render();
	void deactivate();
	bool isDeactivateCondition();
};