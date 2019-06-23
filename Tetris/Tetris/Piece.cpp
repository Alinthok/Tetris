#include "pch.h"
#include "Piece.h"

Piece::Piece(int n, int x, int y)
{
	pos.x = x;
	pos.y = y;
	color = n;
}

sf::Vector2i Piece::getPos()
{
	return pos;
}

void Piece::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

int Piece::getColor()
{
	return color;
}

void Piece::setColor(int n)
{
	color = n;
}

void Piece::FlashIt()
{
	if (!flash)
	{
		flash = true;
	}
	else
	{
		flash = false;
	}
}

bool Piece::getFlash()
{
	return flash;
}

int Piece::getPlace()
{
	return place;
}

void Piece::setPlace(int n)
{
	place = n;
}
