#include "../includes/NodeUtils.hpp"
#include "../includes/utils.hpp"
#include <iostream>
#include <unistd.h>

void	print_solution(Node const * node, int steps, bool viz)
{
	if (!node)
		return ;
	print_solution(node->parent, steps, viz);
	display_map_data(node->map, viz);
	std::cout << "Duration : " << 3 * (steps - node->g) * node->size / steps << "s" << std::endl;
	if (viz)
		usleep(3000000 * node->size / steps );
	
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
