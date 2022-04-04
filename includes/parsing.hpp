#ifndef PARSING_HPP
# define PARSING_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <cstring>

enum e_flag {
	ARG_NONE = 0,
	ARG_PATH = 1,
	ARG_SIZE = 1 << 1,
	ARG_H = 1 << 2
};

struct parsing_flag_exec {
	e_flag type;
	const char *start;
	bool (*fct)(const std::string &str);
};

#endif // PARSING_HPP
