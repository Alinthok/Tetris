#include "pch.h"
#include "LevelSelect.h"

void LevelSelect::toggleBool(bool& bl)
{
	if (bl)
	{
		bl = false;
	}
	else
	{
		bl = true;
	}
}

LevelSelect::LevelSelect(Render* p_renderer, Score* p_score, HighScore* p_highScore)
{
	renderer = p_renderer;
	score = p_score;
	highScore = p_highScore;
	nextState = PLAY;
}

void LevelSelect::activate()
{
	timer.startTime(0, sf::milliseconds((16 * 1000) / 60));
	selectedLvl = -1;
	activated = true;
}

void LevelSelect::update()
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

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
			{
				if (choice.x > 0)
				{
					choice.x--;
				}

				else if (choice.x <= 0 and choice.y == 1)
				{
					choice.y--;
					choice.x = 4;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
			{
				if (choice.x < 4)
				{
					choice.x++;
				}

				else if (choice.x >= 4 and choice.y == 0)
				{
					choice.y++;
					choice.x = 0;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
			{
				if (choice.y < 1)
				{
					choice.y++;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
			{
				if (choice.y > 0)
				{
					choice.y--;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				selectedLvl = choice.x + (COLUMN * choice.y);
			}
		}

		if (timer.isPassed(0))
		{
			toggleBool(flash);
			timer.resetTime(0);
		}
	}

}

void LevelSelect::render()
{
	renderer->getWindow()->clear();
	renderer->drawBg(3);
	for (int y = 0; y < ROW; ++y)
	{
		for (int x = 0; x < COLUMN; ++x)
		{
			float xx = static_cast<float>((x * 48) + 138);
			float yy = static_cast<float>((y * 48) + 143);
			if (choice.x == x and choice.y == y)
			{
				if (flash)
				{
					renderer->drawLongIntColor(static_cast<long>(x + (COLUMN * y)), xx, yy, sf::Color::Black);
				}
			}
		}
	}

	int lvlChoice = choice.x + (5 * choice.y);

	for (int i = 0; i < MAXHIGHSCORE; ++i)
	{
		if ((highScore->getName(i, lvlChoice) != "-1") and (highScore->getScore(i, lvlChoice) != -1))
		{
			renderer->drawStringColor(highScore->getName(i, lvlChoice), 93, 311 + (i * 24), sf::Color::Black);
			renderer->drawLongIntColor(highScore->getScore(i, lvlChoice), 426, 311 + (i * 24), sf::Color::Black);
		}
	}

	renderer->getWindow()->display();
}

void LevelSelect::deactivate()
{
	activated = false;
	score->reset();
	score->setLvl(selectedLvl);
	score->setStartLvl(selectedLvl);
	timer.deleteTime(0);
}

bool LevelSelect::isDeactivateCondition()
{
	return selectedLvl != -1;
}






