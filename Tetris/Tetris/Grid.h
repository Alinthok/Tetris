#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <iostream>

class Grid
{
private:
	const int ROW = 10;
	const int COLUMN = 21;
	Piece board[21][10];

	void removeLine(int y);
	void dropLine(int s);
	bool checkLine(int y);
	void removePiece(int x, int y);

public:
	Grid();
	void drawBoard();
	bool checkPiece(int x, int y);
	void addPiece(Piece pc);
	void flashLine();
	void reset();
	int GetLineClearCount();
	void CheckRemoveLine();
	std::vector<Piece> getPieces();
	int getRow();
	int getCol();
};