#include "pch.h"
#include "ShapeList.h"

Vector3Di ShapeList::getShape(int n)
{
	switch (n)
	{
	case 1:
		return shapeL;
		break;
	case 2:
		return shapeJ;
		break;
	case 3:
		return shapeS;
		break;
	case 4:
		return shapeZ;
		break;
	case 5:
		return shapeT;
		break;
	case 6:
		return shapeO;
		break;
	case 7:
		return shapeI;
		break;
	default:
		return shapeX;
		break;
	}
}

std::vector<Piece> ShapeList::getPieces(int n)
{
	Vector3Di shape = getShape(n);
	std::vector<Piece> pieces;
	for (size_t z = 0; z < shape.size(); ++z)
	{
		for (size_t y = 0; y < shape[0].size(); ++y)
		{
			for (size_t x = 0; x < shape[0][0].size(); ++x)
			{
				if (shape[z][y][x] == 1)
				{
					Piece temp(n, x - 1, y - 1);
					if (n == 7)
					{
						if (z % 2 == 0)
						{
							if (temp.getPos().x == -1)
							{
								temp.setPlace(0);
							}
							else if (temp.getPos().x == 0 or temp.getPos().x == 1)
							{
								temp.setPlace(1);
							}
							else
							{
								temp.setPlace(2);
							}
						}
						else
						{
							if (temp.getPos().y == -1)
							{
								temp.setPlace(3);
							}
							else if (temp.getPos().y == 0 or temp.getPos().y == 1)
							{
								temp.setPlace(4);
							}
							else
							{
								temp.setPlace(5);
							}
						}
					}
					pieces.push_back(temp);
				}
			}
		}
	}
	return pieces;
}
