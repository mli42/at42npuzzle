#ifndef NODE_UTILS_HPP
# define NODE_UTILS_HPP

# include "Node.hpp"
# include <queue>
# include <set>
# include <stack>

struct Compare
{
	bool operator()(Node const * X, Node const * Y)
	{
		return X->heuristic > Y->heuristic;
	}
};

struct LessNodeMapData
{
	bool operator()(Node const * X, Node const * Y)
	{
		return X->map > Y->map;
	}
};

typedef std::priority_queue<Node *, std::vector<Node *>, Compare> priority_queue;
typedef std::set<Node *, LessNodeMapData> closed_set;
typedef std::stack<Node *> NodeCollector;

void	expand(Node *current, priority_queue *q, closed_set *closed_list, NodeCollector *collector_stack);
void    print_solution(Node const *node);
void	print_node_content(const Node *const node);

#endif
