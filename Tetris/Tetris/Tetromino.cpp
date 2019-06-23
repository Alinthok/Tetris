#include "pch.h"
#include "Tetromino.h"

bool Tetromino::checkCollisionFromVector(Grid board, std::vector<Piece> pieceVec)
{
	for (auto piece : pieceVec)
	{
		if (board.checkPiece(piece.getPos().x + pos.x, piece.getPos().y + pos.y) or
			piece.getPos().y + pos.y >= board.getCol() or piece.getPos().x + pos.x >= board.getRow() or piece.getPos().x + pos.x < 0)
		{
			return false;
		}
	}
	return true;
}

Tetromino::Tetromino(int n)
{
	ShapeList List;
	pieceVec = List.getPieces(n);

	if (n != 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			usedPieceVec.push_back(pieceVec[i]);
		}
	}
}

void Tetromino::moveLeft(Grid board)
{
	for (auto piece : usedPieceVec)
	{
		if ((piece.getPos().x + pos.x) - 1 < 0 or board.checkPiece((piece.getPos().x + pos.x) - 1, piece.getPos().y + pos.y))
		{
			return;
		}
	}
	pos.x -= 1;
}

void Tetromino::moveDown(Grid board)
{
	if (!dropped)
	{
		for (auto piece : usedPieceVec)
		{
			if ((piece.getPos().y + pos.y) + 1 >= board.getCol() or board.checkPiece(piece.getPos().x + pos.x, (piece.getPos().y + pos.y) + 1))
			{
				dropped = true;
				return;
			}
		}
	}
	pos.y += 1;
}

void Tetromino::moveRight(Grid board)
{
	for (auto piece : usedPieceVec)
	{
		if ((piece.getPos().x + pos.x) + 1 >= board.getRow() or board.checkPiece((piece.getPos().x + pos.x) + 1, piece.getPos().y + pos.y))
		{
			return;
		}
	}
	pos.x += 1;
	
}

void Tetromino::rotate(Grid board)
{
	int availableRot = pieceVec.size() / MAXPIECE;
	if (availableRot > 0)
	{
		++rotCycle;
		if (rotCycle >= availableRot)
		{
			rotCycle = 0;
		}
		int iStart = MAXPIECE * rotCycle;
		std::vector<Piece> temp;
		for (int i = iStart; i < iStart + 4; ++i)
		{
			temp.push_back(pieceVec[i]);
		}

		if (checkCollisionFromVector(board, temp))
		{
			usedPieceVec = temp;
		}
		else
		{
			--rotCycle;
		}
	}
}

bool Tetromino::isDropped()
{
	return dropped;
}

std::vector<Piece> Tetromino::getPieces()
{
	std::vector<Piece> temp;
	for (auto piece : usedPieceVec)
	{
		Piece pieceTemp = piece;
		pieceTemp.setPos(pieceTemp.getPos().x + pos.x, pieceTemp.getPos().y + pos.y);
		temp.push_back(pieceTemp);
	}

	return temp;
}

