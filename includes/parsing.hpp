#ifndef PARSING_HPP
# define PARSING_HPP

# include <iostream>
# include <string>
# include <fstream>
# include "Node.hpp"

enum e_flag {
	ARG_NONE = 0,
	ARG_PATH = 1,
	ARG_SIZE = 1 << 1,
	ARG_H = 1 << 2
};

struct FlagExec{
	e_flag type;
	const std::string start;
	bool (*fct)(const std::string &value, Node *const node);
};

#endif // PARSING_HPP
