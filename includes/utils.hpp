#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <cmath>
# include <time.h>
# include "PuzzleMap.hpp"
# include "Node.hpp"

void	ft_exit(const std::string &msg, bool doPrintUsage = false);
bool	starts_with(const std::string &str, const std::string &target);
void	display_map(PuzzleMap const * map);

void	display_map_data(MapData const map);
void	display_map_line(MapLine const map);
void	display_solution_coord(void);
void    print_solution(Node const * node);

MapData map_data_generation(void);
MapLine map_line_generation(void);
void    randomize(MapData * map, int moves = 10, int solvability = 1);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

bool	isMapRightSize(int size);
bool    isMovementValid(int size, int y, int x, Coord dir);

bool    cmp(Node const * X, Node const * Y);

#endif // UTILS_HPP
