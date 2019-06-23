#pragma once
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Grid.h"
#include "Piece.h"
#include "InstanceManager.h"
#include "Drawer.h"
#include "Score.h"
#include "Timer.h"
#include "GameStates.h"


class Game : public GameStates
{
private:
	InstanceManager manager;
	Grid board;
	Drawer rng;
	Score* score;
	Timer timer;
	int lvlDropSpeed[21]{ 53, 49, 45, 41, 37, 33, 28, 22, 17, 11, 10, 9, 8, 7, 6, 6, 5, 5, 4, 4, 3 };
	int gameOverFillLevel{ 0 };
	bool downHold{ false };
	bool leftHold{ false };
	bool rightHold{ false };
	bool wait{ false };
	bool gameOver{ false };
	bool gameOverFillAnimation{ false };

	void resetKeyboard();
	void dropTetromino();
	void spawnTeromino();
	void startLineClearAnim();
	void addScoreLine();

public:
	Game(Render *p_renderer, Score* p_score);
	void activate();
	void update();
	void render();
	void deactivate();
	bool isDeactivateCondition();
	bool isGameOver();
};



