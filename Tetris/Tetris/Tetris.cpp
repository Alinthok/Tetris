// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Grid.h"
#include "Piece.h"
#include "InstanceManager.h"
#include "Drawer.h"
#include "Score.h"
#include "Game.h"
#include "LevelSelect.h"
#include "GameOver.h"
#include "HighScoreName.h"
#include "GameStates.h"
#include "TitleScreen.h"

int main()
{


	Score score;
	Render renderer;
	HighScore highScore;
	Game* game = new Game(&renderer, &score);
	LevelSelect* levelSelect = new LevelSelect(&renderer, &score, &highScore);
	GameOver* gameOver = new GameOver(&renderer, &score, &highScore);
	HighScoreName* highScoreName = new HighScoreName(&renderer, &score, &highScore);
	TitleScreen* titleScreen = new TitleScreen(&renderer);
	std::vector<GameStates*> stateVec{ levelSelect, game, gameOver, highScoreName, titleScreen };
	
	GameStates::gameState state{ GameStates::TITLE_SCREEN };
	stateVec[state]->activate();

	while (renderer.getWindow()->isOpen())
	{
		stateVec[state]->update();
		stateVec[state]->render();

		if (stateVec[state]->isDeactivateCondition())
		{
			stateVec[state]->deactivate();
			state = stateVec[state]->getNextState();
			stateVec[state]->activate();
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
