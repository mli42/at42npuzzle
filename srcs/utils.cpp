#include "../includes/utils.hpp"
#include <iostream>

bool starts_with(const std::string &str, const std::string &target) {
	if (str.length() < target.length()) return false;

	const std::string substr = str.substr(0, target.length());
	return substr == target;
}

bool isFlagSet(int num, int bit) {
	return (num & bit);
}

int setFlag(int num, int bit) {
	return (num | bit);
}

void	display_map_data(MapData const map) {
	for (unsigned long i = 0; i < map.size(); i++)
		display_map_line(map[i]);
	std::cout << "\n";
}

void	display_map_line(MapLine const map)
{
	for (unsigned long i = 0; i < map.size(); i++)
	{
		if (!map[i])
			std::cout << "\033[91m" << map[i] << "\033[0m\t";
		else
			std::cout << map[i] << "\t";
	}
	std::cout << "\n";
}

void display_solution_coord()
{
	extern std::map<int, Coord>	SolutionCoords;
	std::map<int, Coord>::iterator it = SolutionCoords.begin();
	std::map<int, Coord>::iterator ite = SolutionCoords.end();

	std::cout << SolutionCoords.size() << std::endl;

	while (it != ite)
	{
		std::cout << it->first << " (" << it->second.first;
		std::cout << " " << it->second.second << ")" << std::endl;
		it++;
	}
}

bool	isMapRightSize(int size) {
	if (size < 3 || size > 9) return false;
	return true;
}
