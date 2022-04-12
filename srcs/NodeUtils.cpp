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
	std::cout << "Size: " << node->size << " | Double size: " << node->double_size << \
		" | Heuristic_type: " << node->heuristic_type << " | Parent: " << node->parent << " | G: " << node->g << std::endl \
		<< "Map length: " << node->map.size() << " | Map:" << std::endl;
	display_map_data(node->map);
}
