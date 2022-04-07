#ifndef PUZZLEMAP_HPP
# define PUZZLEMAP_HPP

# include <iostream>
# include <vector>
# include <map>

typedef std::vector<int> MapLine;
typedef std::vector<MapLine> MapData;
typedef std::pair<int, int> Coord;

class PuzzleMap {
	public:
	size_t size;
	MapData map;

	PuzzleMap(void) : size(0), map() {};
	~PuzzleMap() {};
};

#endif // PUZZLEMAP_HPP
