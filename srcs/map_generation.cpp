#include "../includes/PuzzleMap.hpp"
#include "../includes/utils.hpp"

MapData map_generation(void)
{
	int size = 3;
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

	display_map(mat);
	return mat;
}

MapData randomize(MapData map, int moves = 10);
