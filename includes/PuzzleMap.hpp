#ifndef PUZZLEMAP_HPP
# define PUZZLEMAP_HPP

# include <iostream>
# include <vector>
# include <map>

typedef typename std::vector<int> MapLine;
typedef typename std::vector<MapLine> MapData;

class PuzzleMap {
	public:
	size_t size;
	MapData map;

	PuzzleMap(void) : size(0), map() {};
	~PuzzleMap() {};
};

#endif // PUZZLEMAP_HPP
