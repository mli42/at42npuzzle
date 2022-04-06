#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

int	isInf(MapLine const solution, int val1, int val2)
{
	int size = 3; // a enlever quand on aura une variable globale
	int check1 = 0;

	for (int i = 0; i < size * size; i++)
	{
		if (solution[i] == val1)
			check1 = 1;
		if (solution[i] == val2 && !check1)
			return 1;
	}
	return 0;
}

int isMapValid(MapData const map)
{
	MapLine sol = map_line_generation();
	int size = 3; // a enlever quand on aura une variable globale
	int s = 0;

	for (int i = 0; i < size * size; i++)
		for (int j = i + 1; j < (size * size) - 1; j++)
			s += isInf(sol, map[i / 3][i % 3], map[j / 3][j % 3]);

	return (!(s % 2));
}
