#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

/*
	Check valididy only on mapped map
*/
int isMapValid(MapData map)
{
	int size = 3;
	MapLine tmp;
	int s = 0;

	for (int i = 0; i < size * size; i++)
		for (int j = i + 1; j < (size * size) - 1; j++)
			if (map[i / 3][i % 3] > map[j / 3][j % 3])
				s++;

	return (!(s % 2));
}
