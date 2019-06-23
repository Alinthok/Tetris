#include "pch.h"
#include "Grid.h"

Grid::Grid()
{
	for (size_t y = 0; y < COLUMN; ++y)
	{
		for (size_t x = 0; x < ROW; ++x)
		{
			Piece temp(0, x, y);
			board[y][x] = temp;
		}
	}
}

void Grid::drawBoard()
{
	system("CLS");
	for (size_t y = 0; y < COLUMN; ++y)
	{
		for (size_t x = 0; x < ROW; ++x)
		{
			std::cout << board[y][x].getColor() << " ";
		}	
		std::cout << std::endl;
	}
}

bool Grid::checkPiece(int x, int y)
{
	if (board[y][x].getColor() == 0)
	{
		return false;
	}
	return true;
}

void Grid::addPiece(Piece pc)
{
	board[pc.getPos().y][pc.getPos().x] = pc;
}

void Grid::flashLine()
{
	for (int y = COLUMN - 1; y >= 0; --y)
	{
		if (checkLine(y))
		{
			for (int x = 0; x < ROW; ++x)
			{
				board[y][x].FlashIt();
			}
		}
	}
}

void Grid::reset()
{
	for (int y = 0; y < COLUMN; ++y)
	{
		for (int x = 0; x < ROW; ++x)
		{
			removePiece(x, y);
		}
	}
}

int Grid::GetLineClearCount()
{
	int lineCount{ 0 };
	for (int y = COLUMN - 1; y >= 0; --y)
	{
		if (checkLine(y))
		{
			lineCount++;
		}
	}
	return lineCount;
}

void Grid::removePiece(int x, int y)
{
	Piece temp(0, x, y);
	board[y][x] = temp;
}

bool Grid::checkLine(int y)
{
	for (int x = 0; x < ROW; ++x)
	{
		if (board[y][x].getColor() == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::CheckRemoveLine()
{
	for (int y = COLUMN - 1; y >= 0; --y)
	{
		if (checkLine(y))
		{
			removeLine(y);
			dropLine(y);
			CheckRemoveLine();
		}
	}
}

void Grid::removeLine(int y)
{
	for (int x = 0; x < ROW; ++x)
	{
		removePiece(x, y);
	}
}

void Grid::dropLine(int s)
{
	for (int y = s; y >= 1; --y)
	{
		for (int x = 0; x < ROW; ++x)
		{
			board[y][x] = board[y - 1][x];
			board[y][x].setPos(board[y][x].getPos().x, board[y][x].getPos().y + 1);
		}
	}
}

std::vector<Piece> Grid::getPieces()
{
	std::vector<Piece> pieces;
	for (size_t y = 0; y < COLUMN; ++y)
	{
		for (size_t x = 0; x < ROW; ++x)
		{
			if (board[y][x].getColor() != 0)
			{
				pieces.push_back(board[y][x]);
			}
		}
	}
	return pieces;
}

int Grid::getRow()
{
	return ROW;
}

int Grid::getCol()
{
	return COLUMN;
}