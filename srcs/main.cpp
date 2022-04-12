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
	priority_queue q;
	closed_set closed_list;
	NodeCollector collector_stack;

	MapData map = map_data_generation();
	Node *node = new Node(map, SolutionCoords[0], NULL);

	randomize(&node->map, &node->empty_tile, 10000, 1);

	q.push(node);
	closed_list.insert(node);
	collector_stack.push(node);

	size_t max = 0;

	int i = 0;
	while (1)
	{
		Node *top = q.top();
		if (max < q.size())
			max = q.size();
		if (!(top->heuristic - top->g))
		{
			std::cout << "Solution : " << std::endl;
			print_solution(top);
			std::cout << "G: " << top->g << std::endl;
			std::cout << "Size complexity : " << max << std::endl;
			break;
		}
		q.pop();
		expand(top, &q, &closed_list, &collector_stack);
		i++;
	}

	while (!collector_stack.empty()) {
		delete collector_stack.top();
		collector_stack.pop();
	}
}
