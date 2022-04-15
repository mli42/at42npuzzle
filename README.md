# N-PUZZLE

The goal of this project is to solve the N-puzzle game using the A* search algorithm or one of its variants.

## Usage
Flags for n-puzzle:
```
	[--help]
	[--file/-f=] (incompatible with -s/-u/-i)
	[--size/-s=] (3 < x < 9) (incompatible with -f)
	[--heuristic/-h=] {manhattan, misplaced, conflicts, euclidian, custom}
	[--unsolvable/-u=] (bool) (incompatible with -f)
	[--visualizer/-v=] (bool)
	[--greedy/-g=] (bool) (incompatible with -c)
	[--cost/-c=] (bool) (incompatible with -g)
	[--iteration/-i=] (0 < x < 100000) (incompatible with -f)
```

## Sources

### Heuristics

- [Wikipedia definition](https://fr.wikipedia.org/wiki/Heuristique_(math%C3%A9matiques))
- [Attacking the n-puzzle using SAT solvers](https://theses.liacs.nl/pdf/LucEdixhoven.pdf)

### Solvability

- [MicMath: Le taquin impossible (YT)](https://www.youtube.com/watch?v=-3IsCOJieCc)
- [Why is this 15-Puzzle Impossible? - Numberphile (YT)](https://www.youtube.com/watch?v=YI1WqYKHi78)
- [How to check if an instance of 15 puzzle is solvable?](https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/)

### Data Structure
- [Priority Queue](https://en.cppreference.com/w/cpp/container/priority_queue)
- [Set](https://en.cppreference.com/w/cpp/container/set)

### Bonuses
- [Greedy Search](https://en.wikipedia.org/wiki/Greedy_algorithm)
- [Uniform Cost](https://ai.stackexchange.com/questions/9182/how-do-i-show-that-uniform-cost-search-is-a-special-case-of-a)
