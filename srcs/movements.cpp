# include "../includes/utils.hpp"

bool    isMovementValid(int size, int y, int x, Coord dir)
{
    return (y + dir.first < size && y + dir.first >= 0
    && x + dir.second < size && x + dir.second >= 0);
}


void    expand(Node * current, std::priority_queue<Node * , std::vector<Node * >, Compare> * q)
{
	extern Coord directionsCoords[];

    for (int dir = 0; dir < 4; dir++)
    {
        if (isMovementValid(current->map.size(), current->empty_tile.first, \
        current->empty_tile.second, directionsCoords[dir]) /* && vérifier closed list*/)
        {
            Node * child = new Node(current->map, current->empty_tile, current);
            child->move(directionsCoords[dir]);
            child->calculate_heuristic("misplaced");
            q->push(child);
        }
    }
}
