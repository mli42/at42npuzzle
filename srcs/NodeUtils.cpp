#include "../includes/NodeUtils.hpp"
#include "../includes/utils.hpp"
#include <iostream>
#include <unistd.h>

void	print_solution(Node const * node, int steps)
{
	if (!node)
		return ;
	print_solution(node->parent, steps);
	display_map_data(node->map);
	if (Node::visualizer)
	{
		std::cout << "Duration : " << 3 * (steps - node->g) * node->size / steps \
		<< "s" << std::endl;
		usleep(3000000 * node->size / steps );
	}

}

void	print_node_content(const Node *const node) {
	std::cout
		<< "Size: " << Node::size << std::endl << \
		"Double size: " << Node::double_size << std::endl << \
		"Heuristic_type: " << Node::heuristic_type << std::endl;

	if (node == NULL) {
		std::cout << "NODE IS NULL" << std::endl;
		return ;
	}

	std::cout <<
		"Parent: " << node->parent << std::endl << \
		"G: " << node->g << std::endl << \
		"Map length: " << node->map.size() << std::endl << \
		"Map:" << std::endl;
	display_map_data(node->map);
}

void	display_map_data(MapData const map) {
	extern std::map<int, Coord> SolutionCoords;

	if (Node::visualizer) system("clear");
	for (unsigned long i = 0; i < map.size(); i++)
	{
		for (unsigned long j = 0; j < map.size(); j++)
		{
			if (!map[i][j])
				std::cout << YELLOW << map[i][j] << "\t" << EOC;
			else
			{
				if (Node::visualizer)
				{
					Coord tmp = SolutionCoords[map[i][j]];
					std::cout << (tmp.first == (int)i && tmp.second == (int)j ? GREEN : RED) \
					<< map[i][j] << EOC << "\t";
				}
				else
					std::cout << map[i][j] << "\t";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
