#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include "PuzzleMap.hpp"

void	ft_exit(const std::string &msg, bool doPrintUsage = false);
bool	starts_with(const std::string &str, const std::string &target);
void	display_map(PuzzleMap const * map);

void	display_map_data(MapData const map);
void	display_map_line(MapLine const map);
void	display_solution_coord(void);

MapData map_data_generation(void);
MapLine map_line_generation(void);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

bool	isMapRightSize(int size);

#endif // UTILS_HPP
