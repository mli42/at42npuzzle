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
            std::cout << "New coord : " << this->empty_tile.first << " " << this->empty_tile.second << std::endl;
        }

        void calculate_heuristic(std::string const heuristic)
        {
            if (heuristic == "manhattan")
                this->heuristic = this->manhattan() + this->g;
            if (heuristic == "misplaced")
                this->heuristic = this->misplaced() + this->g;
            std::cout << "Heuristic : " << this->heuristic << std::endl;
        }

        int misplaced()
        {
            int s = 0;
            int size = this->map.size();
            extern std::map<int, Coord> SolutionCoords;

            for (int i = 0; i < size * size; i++)
            {
                Coord sol = SolutionCoords[this->map[i / size][i % size]];
                s += (i / size ^ sol.first || i % size ^ sol.second);
            }
            return s;
        }

        int manhattan()
        {
            /*
                Voir is il faut compter la distance du 0 (J'ai l'impression que ça fausse la mesure)
            */
            int s = 0;
            int size = this->map.size();
            extern std::map<int, Coord>	SolutionCoords;

            for (int i = 0; i < size * size; i++)
            {
                if (this->map[i / size][i % size])
                {
                    Coord tmp = SolutionCoords[this->map[i / size][i % size]];
                    s += std::abs(i / size - tmp.first) + std::abs(i % size - tmp.second);
                }
            }
            return s;
        }
};

#endif