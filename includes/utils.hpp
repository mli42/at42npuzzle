#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <cmath>
# include <time.h>
# include <queue>
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
void    randomize(MapData * map, Coord * empty_tile, int moves = 1000, int solvability = 1);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

bool	isMapRightSize(int size);
bool    isMovementValid(int size, int y, int x, Coord dir);

struct Compare
{
	bool operator()(Node const * X, Node const * Y)
	{
		return X->heuristic > Y->heuristic;
	}
};

void	expand(Node * current, std::priority_queue<Node * , std::vector<Node * >, Compare> * q);

#endif // UTILS_HPP
