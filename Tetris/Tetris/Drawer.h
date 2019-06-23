#pragma once
#include <random>

class Drawer
{
private:
	const int SIZE{ 7 };
	int bag[7]{ 1, 2, 3, 4, 5, 6, 7 };
	int choice{ 0 };

public:
	Drawer();
	void shuffleBag();
	int getNum();
	int getNext();
};