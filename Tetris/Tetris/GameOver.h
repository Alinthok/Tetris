#pragma once
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Score.h"
#include "HighScore.h"
#include "GameStates.h"
#include "LevelSelect.h"

class GameOver : public GameStates
{
private:
	Score* score;
	HighScore* highScore;

	bool pressEnter{ false };

public:
	GameOver(Render* p_renderer, Score* p_score, HighScore* p_highScore);
	void activate();
	void update();
	void render();
	void deactivate();
	bool isDeactivateCondition();
};