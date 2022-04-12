#ifndef NODE_HPP
# define NODE_HPP

# include "./utils.hpp"

MapLine map_line_generation();
int		isInf(MapLine const solution, int val1, int val2);

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
			if (heuristic == "conflicts")
				this->heuristic = this->manhattan() * this->misplaced() + 4 * this->conflicts() + this->g;
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

		int conflicts()
		{
			int size = 5;
			int conflicts = 0;
			MapLine solution = map_line_generation();
			extern std::map<int, Coord> SolutionCoords;
			bool in_col[size * size];
			bool in_row[size * size];

			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					int i = y * size + x;

					Coord sol = SolutionCoords[this->map[y][x]];

					in_col[i] = (sol.second == x);
					in_row[i] = (sol.first == y);
				}
			}

			for (int y = 0; y < size; y++)
			{
				for (int x = 0; x < size; x++)
				{
					int i = y * size + x;

					if (!this->map[y][x])
						continue;

					if (in_col[i])
					{
						for (int r = y + 1; r < size; r++)
						{
							int j = r * size + x;

							if (!this->map[r][x])
								continue;
							if (in_col[j] && !isInf(solution, this->map[r][x], this->map[y][x]))
								conflicts++;
						}
					}

					if (in_row[i])
					{
						for (int c = x + 1; c < size; c++)
						{
							int j = y * size + c;

							if (!this->map[y][c])
								continue;
							if (in_row[j] && !isInf(solution, this->map[y][c], this->map[y][x]))
								conflicts++;
						}
					}
				}
			}
			return conflicts;
		}
};

#endif
