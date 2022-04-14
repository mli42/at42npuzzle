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

void print_informations(size_t O_time, size_t O_size, int steps, double time, std::string heuristic)
{
	std::cout << CYAN << "> " << YELLOW << "Heuristic: " << EOC << heuristic \
	<< std::endl << CYAN << "> " << YELLOW << "Steps: " << EOC << steps \
	<< std::endl << CYAN << "> " << YELLOW << "Complexity in time: " << EOC << O_time \
	<< std::endl << CYAN << "> " << YELLOW << "Complexity in size: " << EOC << O_size \
	<< std::endl << CYAN << "> " << YELLOW << "Execution time: " << EOC << time << "s" \
	<< std::endl;
	;
}

bool	isMapRightSize(int size) {
	if (size < 3 || size > 9) return false;
	return true;
}
