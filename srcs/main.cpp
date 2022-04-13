#include "../includes/main.hpp"
#include "../includes/Errno.hpp"
#include "../includes/utils.hpp"
#include "../includes/NodeUtils.hpp"
#include <chrono>

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
	MapData map = map_data_generation();

	if (node == NULL) {
		node = new Node(map, SolutionCoords[0], NULL);
		randomize(&node->map, &node->empty_tile, 1000, 1);
	}


	if (!isMapValid(node->map)) {
		delete node;
		Errno::setError(Errno::NP_NO_ERR, "Map unsolvable!");
		Errno::show();
		return 0;
	}

	node->calculate_heuristic();
	q.push(node);
	closed_list.insert(node);
	collector_stack.push(node);

	size_t	max = 0;
	int		O_time = 1;
	auto t1 = std::chrono::high_resolution_clock::now();

	display_map_data(node->map);
	std::cout << node->heuristic << " " << node->g << std::endl;

	while (1)
	{
		Node *top = q.top();
		if (max < q.size())
			max = q.size();
		if (!(top->heuristic - top->g))
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			std::cout << "Solution : " << std::endl;
			print_solution(top);
			std::cout << "Heuristic : " << Node::heuristic_type << std::endl;
			std::cout << "Number of moves: " << top->g << std::endl;
			std::cout << "Complexity in time : " << O_time << std::endl;
			std::cout << "Complexity in size : " << max << std::endl;
			std::chrono::duration<double> ms_double = t2 - t1;
			std::cout << "Algorithm execution time : " << GREEN << ms_double.count() << "s"<< EOC << std::endl;
			break;
		}
		q.pop();
		expand(top, &q, &closed_list, &collector_stack, &O_time);
	}

	while (!collector_stack.empty()) {
		delete collector_stack.top();
		collector_stack.pop();
	}

	return (0);
}
