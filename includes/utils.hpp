#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include "Types.hpp"

void	ft_exit(const std::string &msg, bool doPrintUsage = false);
bool	starts_with(const std::string &str, const std::string &target);

void	display_map_data(MapData const map);
void	display_map_line(MapLine const map);
void	display_solution_coord(void);

MapData map_data_generation(void);
void    randomize(MapData * map, Coord * empty_tile, int moves = 1000, int solvability = 1);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

bool	isMapRightSize(int size);
bool    isMovementValid(int size, int y, int x, Coord dir);

#endif // UTILS_HPP
