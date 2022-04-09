#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

int	isInf(MapLine const solution, int val1, int val2)
{
	int size = 4; // a enlever quand on aura une variable globale
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
	int size = 4; // a enlever quand on aura une variable globale
	int s = 0;
	Coord empty_tile;
	extern std::map<int, Coord> SolutionCoords;

	for (int i = 0; i < size * size - 1; i++)
	{
		if (!map[i / size][i % size])
			empty_tile = Coord(i / size, i % size);
		for (int j = i + 1; j < size * size; j++)
			s += isInf(sol, map[i / size][i % size], map[j / size][j % size]);
	}

	Coord empty_tile_sol = SolutionCoords[0];
	int dist = std::abs(empty_tile.first - empty_tile_sol.first)
			   + std::abs(empty_tile.second - empty_tile_sol.second);

	return (s % 2 == dist % 2);
}
