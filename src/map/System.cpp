#pragma once
#include<cstdlib>
bool edgeCondition(int coord_x, int coord_y, int reach, unsigned int Width)
{
	if (coord_x - reach == 0 || coord_x + reach == Width)
		return true;
	if (coord_y - reach == 0 || coord_y + reach == Width)
		return true;

	return false;
}
int random(int a, int b)
{
	return (a + rand() % int(b - a + 1));
}
