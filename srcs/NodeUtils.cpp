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
