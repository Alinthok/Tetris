#pragma once
#include <SFML/Graphics.hpp>
#include "Render.h"
#include "Timer.h"
#include "Score.h"
#include "GameStates.h"
#include "HighScore.h"

class HighScoreName : public GameStates
{
private:
	const int MAXHIGHSCORE{ 3 };
	const int ROW{ 2 };
	const int COLUMN{ 5 };

	char highScoreNameChar[38]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G' ,'H', 'I', 'F', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6' ,'7' ,'8', '9', '0', '.' };
	int charChoice{ 0 };
	int charPos{ 0 };
	int setNewScoreIndex{ -1 };
	HighScore* highScore;
	Score* score;
	Timer timer;
	bool flash{ false };
	bool nameSet{ false };

	void toggleBool(bool& bl);

public:
	HighScoreName(Render* p_renderer, Score* p_score, HighScore* p_highScore);
	void activate();
	void update();
	void render();
	void deactivate();
	bool isDeactivateCondition();
	void addHighScore(long score);
	void setName();
};