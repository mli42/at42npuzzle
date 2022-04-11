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


	MapData map = map_data_generation();

	Node * node = new Node(map, SolutionCoords[0], NULL);

	randomize(&node->map, &node->empty_tile, 250, 1);

	q.push(node);

	int i = 0;
	while (1)
	{
		Node * tmp = q.top();
		if (!(tmp->heuristic - tmp->g))
		{
			std::cout << "Solution : " << std::endl;
			print_solution(tmp);
			break;
		}
		q.pop();
		expand(tmp, &q, &closed_list);
		i++;
	}

	closed_set::iterator closed_it = closed_list.begin(), closed_ite = closed_list.end();
	for (; closed_it != closed_ite; closed_it++) {
		const Node *tmp = *closed_it;

		closed_list.erase(closed_it);
		delete tmp;
	}

	while (!q.empty()) {
		// delete q.top();
		// q.top() = NULL;
		q.pop();
	}
}
