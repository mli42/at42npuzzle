#ifndef NODE_HPP
# define NODE_HPP

# include "./utils.hpp"

class Node
{
    public:

        MapData map;
        Coord empty_tile;
        int heuristic;
        int g;
        Node * parent;

		Node(MapData const map, Coord const empty_tile, Node * parent = NULL) :
			map(map), empty_tile(empty_tile), heuristic(-1), g(parent ? parent->g + 1 : 0), parent(parent) {
			return ;
		}

        ~Node() { return; }

        void move(Coord const dir)
        {
			std::swap(this->map[empty_tile.first][empty_tile.second],
				this->map[empty_tile.first + dir.first][empty_tile.second + dir.second]);

            this->empty_tile.first += dir.first;
            this->empty_tile.second += dir.second;
        }

        void calculate_heuristic(std::string const heuristic)
        {
            if (heuristic == "manhattan")
                this->heuristic = this->manhattan() + this->g;
            if (heuristic == "misplaced")
                this->heuristic = this->manhattan() * this->misplaced() + this->g;
        }

        int misplaced()
        {
            int s = 0;
            int size = this->map.size();
            extern std::map<int, Coord> SolutionCoords;

            for (int i = 0; i < size * size; i++)
            {
				const int x = i % size, y = i / size;

                Coord sol = SolutionCoords[this->map[y][x]];
                s += (y ^ sol.first || x ^ sol.second);
            }
            return s;
        }

        int manhattan()
        {
            int s = 0;
            int size = this->map.size();
            extern std::map<int, Coord>	SolutionCoords;

            for (int i = 0; i < size * size; i++)
            {
				const int x = i % size, y = i / size;

                if (this->map[y][x])
                {
                    const Coord tmp = SolutionCoords[this->map[y][x]];
                    s += std::abs(y - tmp.first) + std::abs(x - tmp.second);
                }
            }
            return s;
        }
};

#endif
