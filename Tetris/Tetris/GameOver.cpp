#include "pch.h"
#include "GameOver.h"

GameOver::GameOver(Render* p_renderer, Score* p_score, HighScore* p_highScore)
{
	renderer = p_renderer;
	score = p_score;
	highScore = p_highScore;
}

void GameOver::activate()
{
	activated = true;
}

void GameOver::update()
{
	if (activated)
	{
		sf::Event event;

		while (renderer->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				renderer->getWindow()->close();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				pressEnter = true;
			}
		}
	}
}

void GameOver::render()
{
	renderer->getWindow()->clear();
	renderer->drawBg(2);
	renderer->drawLongIntColor(score->getScore(), 450.0f, 69.0f, sf::Color::Black);
	renderer->drawLongIntColor(static_cast<long>(score->getLineCleared()), 426.0f, 237.0f, sf::Color::Black);
	renderer->drawLongIntColor(static_cast<long>(score->getLevel()), 426.0f, 165.0f, sf::Color::Black);
	renderer->getWindow()->display();
}

void GameOver::deactivate()
{
	pressEnter = false;
	activated = false;
}

bool GameOver::isDeactivateCondition()
{
	if (pressEnter && highScore->canPlaceHighScoreAndDropScore(score->getScore(), score->getStartLvl()))
	{
		nextState = SET_HIGHSCORE_NAME;
		return true;
	}
	else if (pressEnter)
	{
		nextState = SELECT_LEVEL;
		return true;
	}
	return false;
}
