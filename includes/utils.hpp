#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include "Types.hpp"

# define EOC "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[91m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define DBLUE "\033[94m"
# define PURPLE "\033[95m"
# define CYAN "\033[96m"

bool	starts_with(const std::string &str, const std::string &target);

void	display_solution_coord(void);
void    print_informations(size_t O_time, size_t O_size, int steps, double time, std::string heuristic);

MapData map_data_generation(void);
void    randomize(MapData * map, Coord * empty_tile, int moves = 1000, int solvability = 1);

bool	isFlagSet(const int num, const int bit);
int		setFlag(const int num, const int bit);

bool	isMapRightSize(int size);
bool    isMovementValid(int size, int y, int x, Coord dir);

#endif // UTILS_HPP
