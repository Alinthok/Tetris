#pragma once
#include <SFML/Graphics.hpp>

class Piece
{
private:
	sf::Vector2i pos;
	int place{ 0 };
	int color;
	bool flash{ false };

public:
	Piece(int n = 0, int x = 0, int y = 0);
	sf::Vector2i getPos();
	void setPos(int x, int y);
	void setPlace(int n);
	void setColor(int n);
	void FlashIt();
	bool getFlash();
	int getColor();
	int getPlace();
};