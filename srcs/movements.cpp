# include "../includes/utils.hpp"

std::map<int, Coord> directionsCoords = { {0 /*U*/, Coord(-1, 0)},
                                          {1 /*D*/, Coord(1, 0)},
                                          {2 /*R*/, Coord(0, 1)},
                                          {3 /*L*/, Coord(0, -1)});

bool isMovementValid(int size, int y, int x, Coord dir)
{
    return (y + dir.first < size && y + dir.first >= 0
    && x + dir.second < size && x + dir.second >= 0);
}


void    expand(PuzzleMap const * map, Node current, std::priority_queue<Node, std::vector<Node>, cmp> q)
{
    for (int dir = 0; dir < 4; dir++)
    {
        if (isMovementValid(map->size, current.empty_tile.first, \
        current.empty_tile.second, directionsCoords[dir]) /* && vérifier closed list*/)
        {
            Node child = Node(map->map, empty_tile, &current);
            child.move(directionsCoords[dir])
            child.calculate_heuristic(map->heuristic);
            q.push(child);
        }
    }
}

/*

    Pour print la solution il faudrait faire une fonction récursive sur le parent et print à chaque fois.
    Comme ça, si je ne me trompe pas, j'aurais à chaque fois le premier élément print puis tous les autres dans le bon ordre

*/