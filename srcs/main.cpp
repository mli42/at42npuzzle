#include "../includes/main.hpp"
#include "../includes/utils.hpp"

std::map<int, Coord> SolutionCoords;

Coord directionsCoords[4] = {
	{/*U*/ Coord(-1, 0)},
	{/*D*/ Coord(1, 0)},
	{/*R*/ Coord(0, 1)},
	{/*L*/ Coord(0, -1)}
};

int main(int argc, char **argv) {
	// PuzzleMap map;

	// if (parsing(argc, argv, &map) == false)
	// 	return 1;

	// return 0;
	(void)argc; (void)argv;
	std::priority_queue<Node *, std::vector<Node * >, Compare> q;


	MapData map = map_data_generation();

	Node * node = new Node(map, SolutionCoords[0], NULL);

	randomize(&node->map, &node->empty_tile, 1, 1);

	q.push(node);

	int i = 0;
	int run = 1;
	while (run)
	{
		Node * tmp = q.top();
		if (!(tmp->heuristic - tmp->g))
		{
			std::cout << "Solution : " << std::endl;
			print_solution(tmp);
			break;
		}
		q.pop();
		expand(tmp, &q);
		i++;
	}
}
