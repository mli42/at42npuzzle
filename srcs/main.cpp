#include "../includes/main.hpp"

int main(int argc, char **argv) {
	PuzzleMap map;

	if (parsing(argc, argv, &map) == false)
		return 1;

	return 0;
}
