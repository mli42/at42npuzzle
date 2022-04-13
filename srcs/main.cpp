#include "../includes/main.hpp"
#include "../includes/Errno.hpp"
#include "../includes/utils.hpp"
#include "../includes/NodeUtils.hpp"

std::map<int, Coord> SolutionCoords;
std::string Node::heuristic_type;
size_t Node::size = 4;
size_t Node::double_size = Node::size * Node::size;

Coord directionsCoords[4] = {
	{/*U*/ Coord(-1, 0)},
	{/*D*/ Coord(1, 0)},
	{/*R*/ Coord(0, 1)},
	{/*L*/ Coord(0, -1)}
};

int main(int argc, char **argv) {
	Node::heuristic_type = HeuristicType::misplaced;
	Node *node = NULL;

	parsing(argc, argv, &node);
	if (Errno::hasErr()) {
		Errno::show();
		return (1);
	}

	priority_queue q;
	closed_set closed_list;
	NodeCollector collector_stack;

	if (node == NULL) {
		MapData map = map_data_generation();
		node = new Node(map, SolutionCoords[0], NULL);
		randomize(&node->map, &node->empty_tile, 220, 1);
	}

	if (!isMapValid(node->map)) {
		delete node;
		Errno::setError(Errno::NP_NO_ERR, "Map unsolvable!");
		Errno::show();
		return 0;
	}

	q.push(node);
	closed_list.insert(node);
	collector_stack.push(node);

	size_t max = 0;
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
	}

	while (!collector_stack.empty()) {
		delete collector_stack.top();
		collector_stack.pop();
	}

	return (0);
}
