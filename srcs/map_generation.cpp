#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

void	display_coord(std::vector<Coord> coord)
{
	std::cout << "Start :" << std::endl;
	for (unsigned long i = 0; i < coord.size(); i++)
		std::cout << coord[i].first << " " << coord[i].second << std::endl;
	std::cout << "Endc" << std::endl;
}

void randomize(MapData * map, int moves, int solvability)
{
	/*
		Rajouter fonction swap
	*/
	std::vector<Coord> indexes;
	extern std::map<int, Coord> SolutionCoords;
	extern std::map<int, Coord> directionsCoords;
	Coord empty_tile = SolutionCoords[0];
	srand(time(NULL));

	for (int m = 0; m < moves; m++)
	{
		for (int i = 0; i < 4; i++)
			if (isMovementValid(map->size(), empty_tile.first, empty_tile.second, directionsCoords[i]))
				indexes.push_back(directionsCoords[i]);

		Coord dir = indexes[rand() % indexes.size()];
		int tmp = (*map)[empty_tile.first + dir.first][empty_tile.second + dir.second];
		(*map)[empty_tile.first + dir.first][empty_tile.second + dir.second] = (*map)[empty_tile.first][empty_tile.second];
		(*map)[empty_tile.first][empty_tile.second] = tmp;
		empty_tile.first += dir.first;
		empty_tile.second += dir.second;
		display_map_data((*map));
		indexes.clear();
	}

	if (!solvability)
	{
		if ((*map)[0][0] && (*map)[0][1])
		{
			int tmp = (*map)[0][0];
			(*map)[0][0] = (*map)[0][1];
			(*map)[0][1] = tmp;
		}
		else
		{
			int tmp = (*map)[map->size() - 1][map->size() - 1];
			(*map)[map->size() - 1][map->size() - 1] = (*map)[map->size() - 1][map->size() - 2];
			(*map)[map->size() - 1][map->size() - 2] = tmp;
		}
	}
}

MapData map_data_generation(void)
{
	int size = 4; // a enlever quand on aura une variable globale
	int top = 0;
	int bottom = size - 1;
	int left = 0;
	int right = size - 1;
	int index = 1;
	int value;
	MapData mat = MapData(size, MapLine(size));
	extern std::map<int, Coord>	SolutionCoords;

	while (1) {
		if (left > right)
				break;
		for (int i = left; i <= right; i++) {
			value = index != size * size ? index++ : 0;
			mat[top][i] = value;
			SolutionCoords.insert({value, Coord(top, i)});
		}
		top++;
		if (top > bottom)
				break;
		for (int i = top; i <= bottom; i++) {
			value = index != size * size ? index++ : 0;
			mat[i][right] = value;
			SolutionCoords.insert({value, Coord(i, right)});
		}
		right--;
		if (left > right)
				break;
		for (int i = right; i >= left; i--) {
			value = index != size * size ? index++ : 0;
			mat[bottom][i] = value;
			SolutionCoords.insert({value, Coord(bottom, i)});
		}
		bottom--;
		if (top > bottom)
				break;
		for (int i = bottom; i >= top; i--) {
			value = index != size * size ? index++ : 0;
			mat[i][left] = value;
			SolutionCoords.insert({value, Coord(i, left)});
		}
		left++;
	}

	display_map_data(mat); // pour debug
	//display_solution_coord();
	return mat;
}

MapLine map_line_generation(void)
{
	int size = 4; // a enlever quand on aura une variable globale
	int top = 0;
	int bottom = size - 1;
	int left = 0;
	int right = size - 1;
	int index = 1;
	int value;
	MapLine mat = MapLine(size * size);

	// calculer qu'une fois size * size

	while (1) {
		if (left > right)
				break;
		for (int i = left; i <= right; i++)
		{
			value = index != size * size ? index++ : 0;
			mat[top * size + i] = value;
		}
		top++;
		if (top > bottom)
				break;
		for (int i = top; i <= bottom; i++)
		{
			value = index != size * size ? index++ : 0;
			mat[i * size + right] = value;
		}
		right--;
		if (left > right)
				break;
		for (int i = right; i >= left; i--)
		{
			value = index != size * size ? index++ : 0;
			mat[bottom * size + i] = value;
		}
		bottom--;
		if (top > bottom)
				break;
		for (int i = bottom; i >= top; i--)
		{
			value = index != size * size ? index++ : 0;
			mat[i * size + left] = value;
		}
		left++;
	}

	//display_map_line(mat); // pour debug
	return mat;
}
