#ifndef PUZZLEMAP_HPP
# define PUZZLEMAP_HPP

# include <iostream>
# include <vector>

class PuzzleMap {
	public:
	int size;
	std::vector<std::vector<int>> map;

	PuzzleMap(void) : size(0), map() {};
	~PuzzleMap() {};
};

#endif // PUZZLEMAP_HPP
