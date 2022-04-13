#include "../includes/utils.hpp"
#include "../includes/Node.hpp"
#include <time.h>
#include <iostream>

void	display_coord(std::vector<Coord> coord)
{
	std::cout << "Start :" << std::endl;
	for (unsigned long i = 0; i < coord.size(); i++)
		std::cout << coord[i].first << " " << coord[i].second << std::endl;
	std::cout << "Endc" << std::endl;
}

void randomize(MapData * map, Coord * empty_tile, int moves, int solvability)
{
	std::vector<Coord> indexes;
	extern std::map<int, Coord> SolutionCoords;
	extern Coord directionsCoords[];
	srand(time(NULL));

	for (int m = 0; m < moves; m++)
	{
		for (int i = 0; i < 4; i++)
			if (isMovementValid(map->size(), empty_tile->first, empty_tile->second, directionsCoords[i]))
				indexes.push_back(directionsCoords[i]);

		Coord dir = indexes[rand() % indexes.size()];
		std::swap((*map)[empty_tile->first][empty_tile->second],
			(*map)[empty_tile->first + dir.first][empty_tile->second + dir.second]);


		empty_tile->first += dir.first;
		empty_tile->second += dir.second;
		indexes.clear();
	}

	if (!solvability)
	{
		const int last_index = map->size() - 1;

		if ((*map)[0][0] && (*map)[0][1])
			std::swap((*map)[0][0], (*map)[0][1]);
		else
			std::swap((*map)[last_index][last_index], (*map)[last_index][last_index - 1]);
	}
}

void make_snake(int y, int x, size_t *index, MapData &mat)
{
	extern std::map<int, Coord>	SolutionCoords;

	const int value = *index != Node::double_size ? (*index)++ : 0;

	mat[y][x] = value;
	SolutionCoords.insert({value, Coord(y, x)});
}

MapData map_data_generation(void)
{
	const size_t &size = Node::size;
	int top = 0;
	int bottom = size - 1;
	int left = 0;
	int right = size - 1;
	size_t index = 1;
	MapData mat = MapData(size, MapLine(size));
	extern std::map<int, Coord>	SolutionCoords;

	while (1) {
		if (left > right)
				break;
		for (int i = left; i <= right; i++)
			make_snake(top, i, &index, mat);
		top++;

		if (top > bottom)
				break;
		for (int i = top; i <= bottom; i++)
			make_snake(i, right, &index, mat);
		right--;

		if (left > right)
				break;
		for (int i = right; i >= left; i--)
			make_snake(bottom, i, &index, mat);
		bottom--;

		if (top > bottom)
				break;
		for (int i = bottom; i >= top; i--)
			make_snake(i, left, &index, mat);
		left++;
	}
	return mat;
}
