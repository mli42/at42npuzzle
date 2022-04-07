#include "../includes/main.hpp"

std::map<int, Coord> SolutionCoords;

int main(int argc, char **argv) {
	PuzzleMap map;

	if (parsing(argc, argv, &map) == false)
		return 1;

	return 0;
}
