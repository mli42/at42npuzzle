#include "../includes/Node.hpp"

std::string Node::heuristic_type;
size_t Node::size = 3;
size_t Node::double_size = Node::size * Node::size;
bool Node::unsolvable = false;
bool Node::visualizer = false;
bool Node::greedy = false;
bool Node::cost = false;
int Node::iteration = 5000;
