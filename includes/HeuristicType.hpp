#ifndef HEURISTICTYPE_HPP
# define HEURISTICTYPE_HPP

# include <string>

struct HeuristicType {
	static const std::string misplaced;
	static const std::string manhattan;
	static const std::string conflicts;
	static const std::string euclidian;
	static const std::string custom;
};

#endif
