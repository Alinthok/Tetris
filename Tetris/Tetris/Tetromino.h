#pragma once 
#include <vector>
#include <SFML/Graphics.hpp>
#include "ShapeList.h"
#include "Grid.h"
#include "Piece.h"
#include <iostream>

class Tetromino
{
private:
	const int MAXPIECE = 4;
	int rotCycle{ 0 };
	sf::Vector2i pos{ 5, 3 };
	std::vector<Piece> pieceVec;
	std::vector<Piece> usedPieceVec;
	bool dropped = false;

	bool checkCollisionFromVector(Grid board, std::vector<Piece> pieceVec);

public:
	Tetromino(int n = 0);
	void moveRight(Grid board);
	void moveLeft(Grid board);
	void moveDown(Grid board);
	void rotate(Grid board);
	bool isDropped();
	std::vector<Piece> getPieces();
};