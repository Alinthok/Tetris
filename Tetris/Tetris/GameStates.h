#pragma once
#include <SFML/Graphics.hpp>
#include "Render.h"

class GameStates
{
public:
	enum gameState
	{
		SELECT_LEVEL = 0, PLAY = 1, GAME_OVER = 2, SET_HIGHSCORE_NAME = 3, TITLE_SCREEN = 4
	};

	virtual void activate() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void deactivate() = 0;
	virtual bool isDeactivateCondition() = 0;
	gameState getNextState();

protected:
	Render* renderer;
	gameState nextState;
	bool activated{ false };
};