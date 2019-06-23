#include "pch.h"
#include "Render.h"

Render::Render()
{
	bgTexture[0].loadFromFile("Background.jpg");
	bgTexture[1].loadFromFile("TetrisGameOver.jpg");
	bgTexture[2].loadFromFile("TetrisSelectLevel.jpg");
	bgTexture[3].loadFromFile("TetrisStart.jpg");
	font.loadFromFile("TetrisFont.ttf");
	pieceTexture.loadFromFile("TetrisSheet.jpg");
	previewTexture.loadFromFile("TetrisPreviewSheet.jpg");

	for (int n = 0; n < BGCOUNT; ++n)
	{
		bgSprite[n].setTexture(bgTexture[n]);
	}

	Window.create(sf::VideoMode(480, 432), "Tetris");
	Window.setKeyRepeatEnabled(false);
}

void Render::drawPoints(std::vector<Piece> pieceVec)
{
	sf::VertexArray vertices(sf::Quads, pieceVec.size() * 4);

	for (unsigned int i = 0; i < pieceVec.size(); ++i)
			{
				sf::Vertex* quad = &vertices[i * 4];
				Piece temp = pieceVec[i];

				int color = temp.getColor() - 1;

				if (temp.getFlash())
				{
					color = 12;
				}
				else
				{
					color = temp.getColor() - 1;
				}

				if (temp.getColor() == 7 and color != 12)
				{
					switch (temp.getPlace())
					{
					case 1:
						color += 1;
						break;
					case 2:
						color += 2;
						break;
					case 3:
						color += 3;
						break;
					case 4:
						color += 4;
						break;
					case 5:
						color += 5;
						break;
					default:
						break;
					}
				}

				int tu = color % (pieceTexture.getSize().x / TILESIZE);
				int tv = color / (pieceTexture.getSize().x / TILESIZE);

				quad[0].position = sf::Vector2f(gameScreenTopLeft.x + (temp.getPos().x * TILESIZE), gameScreenTopLeft.y + (temp.getPos().y * TILESIZE));
				quad[1].position = sf::Vector2f(gameScreenTopLeft.x + ((temp.getPos().x + 1) * TILESIZE), gameScreenTopLeft.y + (temp.getPos().y * TILESIZE));
				quad[2].position = sf::Vector2f(gameScreenTopLeft.x + ((temp.getPos().x + 1) * TILESIZE), gameScreenTopLeft.y + ((temp.getPos().y + 1) * TILESIZE));
				quad[3].position = sf::Vector2f(gameScreenTopLeft.x + (temp.getPos().x  * TILESIZE), gameScreenTopLeft.y + ((temp.getPos().y + 1) * TILESIZE));

				quad[0].texCoords = sf::Vector2f(tu * TILESIZE, tv * TILESIZE);
				quad[1].texCoords = sf::Vector2f((tu + 1) * TILESIZE, tv * TILESIZE);
				quad[2].texCoords = sf::Vector2f((tu + 1) * TILESIZE, (tv + 1) * TILESIZE);
				quad[3].texCoords = sf::Vector2f(tu * TILESIZE, (tv + 1) * TILESIZE);
			}
	Window.draw(vertices, &pieceTexture);
}

void Render::drawBg(int n)
{
	Window.draw(bgSprite[n - 1]);
}

void Render::drawLongIntColor(long n, float x, float y, sf::Color color)
{
	sf::Text text;
	text.setString(std::to_string(n));
	text.setFont(font);
	text.setFillColor(color);
	text.setOutlineColor(color);
	text.setCharacterSize(24);
	int textCount = text.getString().getSize();
	int offset{ 3 };
	if (textCount == 0)
	{
		offset = 0;
	}

	sf::FloatRect bounds(sf::Vector2f(x, y), sf::Vector2f((textCount * TILESIZE - offset), 18));
	sf::RectangleShape background(sf::Vector2f(bounds.width, bounds.height));
	background.setFillColor(sf::Color::Color(248, 248, 248));

	background.setPosition(x - bounds.width + 3, y + 6);
	text.setPosition(sf::Vector2f(x - bounds.width + 3, y));

	Window.draw(background);
	Window.draw(text);
}

void Render::drawStringColor(std::string str, float x, float y, sf::Color color)
{
	sf::Text text;
	text.setString(str);
	text.setFont(font);
	text.setFillColor(color);
	text.setOutlineColor(color);
	text.setCharacterSize(24);
	int textCount = text.getString().getSize();
	int offset{ 3 };
	if (textCount == 0)
	{
		offset = 0;
	}

	sf::FloatRect bounds(sf::Vector2f(x, y), sf::Vector2f((textCount * TILESIZE - offset), 18));
	sf::RectangleShape background(sf::Vector2f(bounds.width, bounds.height));
	background.setFillColor(sf::Color::Color(248, 248, 248));

	background.setPosition(x + 3, y + 6);
	text.setPosition(sf::Vector2f(x, y));

	Window.draw(background);
	Window.draw(text);
}

void Render::drawPreview(int n)
{
	sf::VertexArray quad(sf::Quads, 4);

	int color = n - 1;

	int tu = color % (previewTexture.getSize().x / PREVIEWTILESIZEX);
	int tv = color / (previewTexture.getSize().x / PREVIEWTILESIZEX);

	sf::Vector2f pos(360, 336);
	quad[0].position = sf::Vector2f(pos.x, pos.y);
	quad[1].position = sf::Vector2f(pos.x + PREVIEWTILESIZEX, pos.y);
	quad[2].position = sf::Vector2f(pos.x + PREVIEWTILESIZEX, pos.y + PREVIEWTILESIZEY);
	quad[3].position = sf::Vector2f(pos.x, pos.y + PREVIEWTILESIZEY);

	quad[0].texCoords = sf::Vector2f(tu * PREVIEWTILESIZEX, tv * PREVIEWTILESIZEY);
	quad[1].texCoords = sf::Vector2f((tu + 1) * PREVIEWTILESIZEX, tv * PREVIEWTILESIZEY);
	quad[2].texCoords = sf::Vector2f((tu + 1) * PREVIEWTILESIZEX, (tv + 1) * PREVIEWTILESIZEY);
	quad[3].texCoords = sf::Vector2f(tu * PREVIEWTILESIZEX, (tv + 1) * PREVIEWTILESIZEY);

	Window.draw(quad, &previewTexture);
}

sf::RenderWindow * Render::getWindow()
{
	return &Window;
}
