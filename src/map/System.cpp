#include<cstdlib>

bool edgeCondition(int coord_x, int coord_y, int reach, unsigned int _width)
{
	if (coord_x - reach == 0 || coord_x + reach == _width)
		return true;
	if (coord_y - reach == 0 || coord_y + reach == _width)
		return true;

	return false;
}
int random(int a, int b)
{
	return (a + rand() % int(b - a + 1));
}
