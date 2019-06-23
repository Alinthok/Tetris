#pragma once
#include "Tetromino.h"

class InstanceManager
{
private:
	Tetromino *tr, *nullTr{ nullptr };

public:
	InstanceManager();
	void addPiece(int n);
	void removePiece();
	Tetromino * getPiece();
	~InstanceManager();
};