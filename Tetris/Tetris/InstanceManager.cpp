#include "pch.h"
#include "InstanceManager.h"

InstanceManager::InstanceManager()
{
	nullTr = new Tetromino();
	tr = nullTr;
}

void InstanceManager::addPiece(int n)
{
	if (tr == nullTr)
	{
		tr = new Tetromino(n);
	}
}

void InstanceManager::removePiece()
{
	if (tr != nullTr)
	{
		delete tr;
		tr = nullTr;
	}
}

Tetromino * InstanceManager::getPiece()
{
	return tr;
}

InstanceManager::~InstanceManager()
{
	if (tr != nullTr)
	{
		delete tr;
	}
	delete nullTr;
}
