#pragma once
#include <SFML/Graphics.hpp>
#include "GameStates.h"

class TitleScreen : public GameStates
{
private:
	bool pressEnter{ false };

public:
	TitleScreen(Render* p_renderer);
	void activate();
	void update();
	void render();
	void deactivate();
	bool isDeactivateCondition();
};

