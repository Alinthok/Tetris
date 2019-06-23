#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Piece.h"

class Render
{
private:
	const int TILESIZE = 24;
	const int BGCOUNT = 4;
	const int PREVIEWTILESIZEX = 96;
	const int PREVIEWTILESIZEY = 48;

	sf::Texture bgTexture[4];
	sf::Sprite bgSprite[4];
	sf::RenderWindow Window;
	sf::Vector2i gameScreenTopLeft{ 48, -(3 * TILESIZE) };
	sf::Vector2i gameScreenBottomRight{ 288, 432 };
	sf::Texture pieceTexture;
	sf::Texture previewTexture;
	sf::Font font;

public:
	Render();
	void drawPoints(std::vector<Piece> pieceVec);
	void drawBg(int n);
	void drawLongIntColor(long n, float x, float y, sf::Color color);
	void drawStringColor(std::string str, float x, float y, sf::Color color);
	void drawPreview(int n);
	sf::RenderWindow * getWindow();
};

