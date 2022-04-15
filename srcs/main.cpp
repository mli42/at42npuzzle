#include "../includes/main.hpp"
#include "../includes/Errno.hpp"
#include "../includes/utils.hpp"
#include "../includes/NodeUtils.hpp"
#include <chrono>

std::map<int, Coord> SolutionCoords;

Coord directionsCoords[4] = {
	{/*U*/ Coord(-1, 0)},
	{/*D*/ Coord(1, 0)},
	{/*R*/ Coord(0, 1)},
	{/*L*/ Coord(0, -1)}
};

void free_collector(NodeCollector * collector_stack)
{
	while (!collector_stack->empty()) {
		delete collector_stack->top();
		collector_stack->pop();
	}
}

void a_star(priority_queue & q, closed_set & closed_list, NodeCollector & collector_stack)
{
	size_t	O_size = 0;
	size_t	O_time = 1;
	auto t1 = std::chrono::high_resolution_clock::now();

	while (1)
	{
		Node *top = q.top();
		if (O_size < q.size())
			O_size = q.size();
		if (!(top->heuristic - top->get_g()))
		{
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> ms_double = t2 - t1;
			print_solution(top, top->g);
			print_informations(O_time, O_size, top->g, ms_double.count(), Node::heuristic_type);
			break;
		}
		q.pop();
		expand(top, &q, &closed_list, &collector_stack, &O_time);
	}
}

int main(int argc, char **argv) {
	Node::heuristic_type = HeuristicType::conflicts;
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
		randomize(&node->map, &node->empty_tile, Node::iteration, !Node::unsolvable);
	}

	if (Node::visualizer)
	{
		display_map_data(node->map);
		std::cout << "Searching..." << std::endl;
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
	a_star(q, closed_list, collector_stack);
	free_collector(&collector_stack);
	return (0);
}
