#include "../includes/main.hpp"
#include "../includes/utils.hpp"
#include <algorithm>

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
	priority_queue q;
	closed_set closed_list;


	MapData map = map_data_generation();

	Node * node = new Node(map, SolutionCoords[0], NULL);

	randomize(&node->map, &node->empty_tile, 400, 1);

	q.push(node);
	closed_list.insert(node);

	int i = 0;
	while (1)
	{
		Node *top = q.top();
		if (!(top->heuristic - top->g))
		{
			std::cout << "Solution : " << std::endl;
			print_solution(top);
			std::cout << "G: " << top->g << std::endl;
			break;
		}
		q.pop();
		expand(top, &q, &closed_list);
		i++;
	}

	// std::vector<Node *> cleared_node;

	// while (!q.empty()) {
	// 	Node *top = q.top();

	// 	// if (std::find(cleared_node.begin(), cleared_node.end(), top) == cleared_node.end()) {
	// 	if (std::find(closed_list.begin(), closed_list.end(), top) == closed_list.end())
	// 	{
	// 		delete top;
	// 		// cleared_node.push_back(top);
	// 	}
	// 	q.pop();
	// }

	// closed_set::iterator closed_it = closed_list.begin(), closed_ite = closed_list.end();
	// for (; closed_it != closed_ite; closed_it++) {
	// 	Node *tmp = *closed_it;

		// if (std::find(cleared_node.begin(), cleared_node.end(), tmp) == cleared_node.end()) {
			// delete tmp;
		// 	cleared_node.push_back(tmp);
		// }
		// closed_list.erase(closed_it);
		// delete tmp;
	// }
}
