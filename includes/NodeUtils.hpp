#ifndef NODE_UTILS_HPP
# define NODE_UTILS_HPP

# include "Node.hpp"
# include <queue>
# include <set>
# include <stack>

# define EOC "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[91m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define DBLUE "\033[94m"
# define PURPLE "\033[95m"
# define CYAN "\033[96m"

struct Compare
{
	bool operator()(Node const * X, Node const * Y) const
	{
		return X->heuristic >= Y->heuristic;
	}
};

struct LessNodeMapData
{
	bool operator()(Node const * X, Node const * Y) const
	{
		return X->map > Y->map;
	}
};

typedef std::priority_queue<Node *, std::vector<Node *>, Compare> priority_queue;
typedef std::set<Node *, LessNodeMapData> closed_set;
typedef std::stack<Node *> NodeCollector;

void	expand(Node *current, priority_queue *q, closed_set *closed_list, NodeCollector *collector_stack, size_t * O_time);
void	print_solution(Node const *node, int steps);
void	print_node_content(const Node *const node);
void	display_map_data(MapData const map);

#endif
