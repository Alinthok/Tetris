#include "pch.h"
#include "HighScoreName.h"

void HighScoreName::toggleBool(bool& bl)
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

HighScoreName::HighScoreName(Render* p_renderer, Score* p_score, HighScore* p_highScore)
{
	renderer = p_renderer;
	score = p_score;
	highScore = p_highScore;
}

void HighScoreName::activate()
{
	addHighScore(score->getScore());
	nameSet = false;
	activated = true;
}

void HighScoreName::update()
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
				if (charPos > 0)
				{
					highScore->deleteLetter(setNewScoreIndex, score->getStartLvl());
					charPos--;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
			{
				if (charPos < 6)
				{
					highScore->addLetter(setNewScoreIndex, score->getStartLvl(), highScoreNameChar[charChoice]);
					charPos++;
				}
				if (charPos == 6)
				{
					setName();
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
			{
				if (charChoice < 37)
				{
					charChoice++;
				}
				else
				{
					charChoice = 0;
				}
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
			{
				if (charChoice > 0)
				{
					charChoice--;
				}
				else
				{
					charChoice = 37;
				}
			}
			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				setName();
				timer.deleteTime(0);
			}
		}
	}
}


void HighScoreName::render()
{
	renderer->getWindow()->clear();
	renderer->drawBg(3);

	for (int i = 0; i < MAXHIGHSCORE; ++i)
	{
		if ((highScore->getName(i, score->getStartLvl()) != "-1") and (highScore->getScore(i, score->getStartLvl()) != -1))
		{
			renderer->drawStringColor(highScore->getName(i, score->getStartLvl()), 93, 311 + (i * 24), sf::Color::Black);
			renderer->drawLongIntColor(highScore->getScore(i, score->getStartLvl()), 426, 311 + (i * 24), sf::Color::Black);
		}
	}

	if ((setNewScoreIndex != -1) and (charPos < 6))
	{
		if (timer.isPassed(0))
		{
			toggleBool(flash);
			timer.resetTime(0);
		}
		if (flash)
		{
			renderer->drawStringColor(std::string(1, highScoreNameChar[charChoice]), 93 + (charPos * 24), 311 + (setNewScoreIndex * 24), sf::Color::Black);
		}
		else
		{
			renderer->drawStringColor(std::string(1, ' '), 93 + (charPos * 24), 311 + (setNewScoreIndex * 24), sf::Color::Black);
		}
	}

	renderer->getWindow()->display();
}

void HighScoreName::deactivate()
{
	activated = false;
}

bool HighScoreName::isDeactivateCondition()
{
	return nameSet;
}

void HighScoreName::addHighScore(long p_score)
{
	int i{ 0 };
	bool stop{ false };
	while ((i < MAXHIGHSCORE) and (!stop))
	{
		if (p_score >= highScore->getScore(i, score->getStartLvl()))
		{
			stop = true;
			setNewScoreIndex = i;
			highScore->setScore(i, score->getStartLvl(), p_score);
			timer.startTime(0, sf::milliseconds(200));
		}
		i++;
	}
}

void HighScoreName::setName()
{
	nameSet = true;
	highScore->writeHighScoreFile();
	charChoice = 0;
	charPos = 0;
	setNewScoreIndex = -1;
}

