#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

MapData map_data_generation(void)
{
	int size = 3; // a enlever quand on aura une variable globale
	int top = 0;
	int bottom = size - 1;
	int left = 0;
	int right = size - 1;
	int index = 0;
	MapData mat = MapData(size, MapLine(size));

	while (1) {
		if (left > right)
				break;
		for (int i = left; i <= right; i++)
				mat[top][i] = index++;
		top++;
		if (top > bottom)
				break;
		for (int i = top; i <= bottom; i++)
				mat[i][right] = index++;
		right--;
		if (left > right)
				break;
		for (int i = right; i >= left; i--)
				mat[bottom][i] = index++;
		bottom--;
		if (top > bottom)
				break;
		for (int i = bottom; i >= top; i--)
				mat[i][left] = index++;
		left++;
	}

	display_map_data(mat); // pour debug
	return mat;
}

MapLine map_line_generation(void)
{
	int size = 3; // a enlever quand on aura une variable globale
	int top = 0;
	int bottom = size - 1;
	int left = 0;
	int right = size - 1;
	int index = 0;
	MapLine mat = MapLine(size * size);

	while (1) {
		if (left > right)
				break;
		for (int i = left; i <= right; i++)
				mat[top * size + i] = index++;
		top++;
		if (top > bottom)
				break;
		for (int i = top; i <= bottom; i++)
				mat[i * size + right] = index++;
		right--;
		if (left > right)
				break;
		for (int i = right; i >= left; i--)
				mat[bottom * size + i] = index++;
		bottom--;
		if (top > bottom)
				break;
		for (int i = bottom; i >= top; i--)
				mat[i * size + left] = index++;
		left++;
	}

	display_map_line(mat); // pour debug
	return mat;
}

MapData randomize(MapData map, int moves = 10);
