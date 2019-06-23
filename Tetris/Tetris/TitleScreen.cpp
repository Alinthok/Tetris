#include "pch.h"
#include "TitleScreen.h"

TitleScreen::TitleScreen(Render* p_renderer)
{
	renderer = p_renderer;
	nextState = SELECT_LEVEL;
}

void TitleScreen::activate()
{
	activated = true;
}

void TitleScreen::update()
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

void TitleScreen::render()
{
	renderer->getWindow()->clear();
	renderer->drawBg(4);
	renderer->getWindow()->display();
}

void TitleScreen::deactivate()
{
	activated = true;
	pressEnter = false;
}

bool TitleScreen::isDeactivateCondition()
{
	return pressEnter;
}
