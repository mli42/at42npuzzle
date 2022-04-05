#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include "PuzzleMap.hpp"

void	ft_exit(const std::string &msg, bool doPrintUsage = false);
bool	starts_with(const std::string &str, const std::string &target);
void	display_map(PuzzleMap const * map);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

#endif // UTILS_HPP
