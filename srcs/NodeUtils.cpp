#include "../includes/NodeUtils.hpp"
#include "../includes/utils.hpp"
#include <iostream>

void	print_solution(Node const * node)
{
	if (!node)
		return ;
	print_solution(node->parent);
	// std::cin.ignore();
	display_map_data(node->map);
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
