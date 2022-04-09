#include "../includes/main.hpp"
#include "../includes/utils.hpp"

std::map<int, Coord> SolutionCoords;

std::map<int, Coord> directionsCoords = { {0 /*U*/, Coord(-1, 0)},
                                          {1 /*D*/, Coord(1, 0)},
                                          {2 /*R*/, Coord(0, 1)},
                                          {3 /*L*/, Coord(0, -1)} };

enum dir
{
	U,
	D,
	R,
	L
};

int main(int argc, char **argv) {
	// PuzzleMap map;

	// if (parsing(argc, argv, &map) == false)
	// 	return 1;

	// return 0;
	(void)argc; (void)argv;

	MapData map = map_data_generation();
	randomize(&map, 1000, 0);
	std::cout << "vvvvv Map vvvvv" << std::endl;
	display_map_data(map);

	std::cout << "Is map solvable ? : " << (isMapValid(map) == 0 ? "False" : "True") << std::endl;

	Node node = Node(map, SolutionCoords[0], NULL);
	node.calculate_heuristic("manhattan");
	node.move(directionsCoords[U]);
	node.calculate_heuristic("manhattan");
	node.move(directionsCoords[R]);
}
