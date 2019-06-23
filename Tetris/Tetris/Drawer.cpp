#include "pch.h"
#include "Drawer.h"

Drawer::Drawer()
	{
		shuffleBag();
	}

void Drawer::shuffleBag()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);
		for (int i = 0; i < SIZE; ++i)
		{
			int r = dist6(rng);
			int temp = bag[i];
			bag[i] = bag[r];
			bag[r] = temp;
		}
	}

int Drawer::getNum()
	{
		int n = bag[choice];
		choice++;
		if (choice > 6)
		{
			shuffleBag();
			choice = 0;
		}
		return n;
	}

int Drawer::getNext()
{
	return bag[choice];
}

