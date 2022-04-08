# include "./utils.hpp"

class Node
{
    public:

        MapData map;
        Coord empty_tile;
        int heuristic;
        int g;
        Node * parent;

        Node(MapData const map, Coord const empty_tile, Node * parent = NULL)
        {
            this->map = map;
            this->empty_tile = empty_tile;
            if (parent)
            {
                this->g = parent->g + 1;
                this->parent = parent;
            }
            return ;
        }

        ~Node() { return; }

        void move(Coord const dir)
        {
            int tmp = this->map[empty_tile.first][empty_tile.second];
            this->map[empty_tile.first][empty_tile.second] = this->map[empty_tile.first + dir.first][empty_tile.second + dir.second];
            this->map[empty_tile.first + dir.first][empty_tile.second + dir.second] = tmp;

            this->empty_tile.first += dir.first;
            this->empty_tile.second += dir.second;
        }

        void calculate_heuristic(std::string const heuristic)
        {
            if (heuristic == "manhattan")
                this->h = this->manhattan() + this->g;
        }

        int manhattan()
        {
            int s = 0;
            int size = this->map.size();
            extern std::map<int, Coord>	SolutionCoords;

            for (int i = 0; i < size * size; i++)
            {
                Coord tmp = SolutionCoords[this->map[i / size][i % size]];
                s += std::abs(i / size - tmp.first) + std::abs(i % size - tmp.second);
            }
            
            return s;
        }
};