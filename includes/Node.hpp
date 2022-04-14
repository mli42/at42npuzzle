#ifndef NODE_HPP
# define NODE_HPP

# include "./HeuristicType.hpp"
# include "./Types.hpp"
# include <cmath>

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

		static std::string heuristic_type;
		static size_t size;
		static size_t double_size;
		static bool unsolvable;
		static bool visualizer;
		static bool greedy;
		static bool cost;
		static int iteration;

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

        void calculate_heuristic(void)
        {
			if (Node::cost)
				this->heuristic = (this->manhattan() ? 1 : 0);
			else
			{
				if (heuristic_type == HeuristicType::manhattan)
					this->heuristic = this->manhattan() + this->get_g();
				else if (heuristic_type == HeuristicType::euclidian)
					this->heuristic = this->euclidian() + this->get_g();
				else if (heuristic_type == HeuristicType::misplaced)
					this->heuristic = this->misplaced() + this->get_g();
				else if (heuristic_type == HeuristicType::conflicts)
					this->heuristic = this->manhattan() + 2 * this->conflicts() + this->get_g();
				else if (heuristic_type == HeuristicType::custom)
					this->heuristic = this->manhattan() * this->misplaced() + 4 * this->conflicts() + this->get_g();
			}
		}

        int misplaced()
        {
            int s = 0;
			const size_t &size = Node::size;
            extern std::map<int, Coord> SolutionCoords;

            for (size_t i = 0; i < Node::double_size; i++)
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
			const size_t &size = Node::size;
            extern std::map<int, Coord>	SolutionCoords;

            for (size_t i = 0; i < Node::double_size; i++)
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

		int euclidian()
		{
            int s = 0;
			const size_t &size = Node::size;
            extern std::map<int, Coord>	SolutionCoords;

            for (size_t i = 0; i < Node::double_size; i++)
            {
				const int x = i % size, y = i / size;

                if (this->map[y][x])
                {
                    const Coord tmp = SolutionCoords[this->map[y][x]];
                    s += std::sqrt(std::pow(y - tmp.first, 2) + std::pow(x - tmp.second, 2));
                }
            }
            return s;
		}

		int conflicts()
		{
			const size_t &size = Node::size;
			int conflicts = 0;
			MapLine solution = map_line_generation();
			extern std::map<int, Coord> SolutionCoords;
			bool in_col[size * size];
			bool in_row[size * size];

			for (size_t y = 0; y < size; y++)
			{
				for (size_t x = 0; x < size; x++)
				{
					size_t i = y * size + x;

					Coord sol = SolutionCoords[this->map[y][x]];

					in_col[i] = (sol.second == (int)x);
					in_row[i] = (sol.first == (int)y);
				}
			}

			for (size_t y = 0; y < size; y++)
			{
				for (size_t x = 0; x < size; x++)
				{
					size_t i = y * size + x;

					if (!this->map[y][x])
						continue;

					if (in_col[i])
					{
						for (size_t r = y + 1; r < size; r++)
						{
							size_t j = r * size + x;

							if (!this->map[r][x])
								continue;
							if (in_col[j] && !isInf(solution, this->map[r][x], this->map[y][x]))
								conflicts++;
						}
					}

					if (in_row[i])
					{
						for (size_t c = x + 1; c < size; c++)
						{
							size_t j = y * size + c;

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

		int get_g() const
		{
			if (Node::greedy || Node::cost)
				return 0;
			return this->g;
		}
};

#endif
