# include "../includes/utils.hpp"

bool    isMovementValid(int size, int y, int x, Coord dir)
{
    return (y + dir.first < size && y + dir.first >= 0
    && x + dir.second < size && x + dir.second >= 0);
}


void    expand(Node *current, priority_queue *q, closed_set *closed_list)
{
	extern Coord directionsCoords[];

    for (int dir = 0; dir < 4; dir++)
    {
        if (isMovementValid(current->map.size(), current->empty_tile.first, \
        current->empty_tile.second, directionsCoords[dir]))
        {
            Node * child = new Node(current->map, current->empty_tile, current);
            child->move(directionsCoords[dir]);
            child->calculate_heuristic("misplaced");

			closed_set::iterator closed_child = closed_list->find(child);

			if (closed_child == closed_list->end()) {
				q->push(child);
				closed_list->insert(child);
			}
			else if (child->g < (*closed_child)->g) {
				q->push(child);
				(*closed_child)->g = child->g;
			}
        }
    }
}
