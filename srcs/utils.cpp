#include "../includes/utils.hpp"

void	ft_exit(const std::string &msg)
{
	std::cerr << msg << std::endl;
	exit(1);
}

bool starts_with(const std::string &str, const std::string &target) {
	if (str.length() < target.length()) return false;

	const std::string substr = str.substr(target.length());
	return substr == target;
}

int isFlagSet(int num, int bit) {
	return (num & bit);
}

int setFlag(int num, int bit) {
	return (num | bit);
}

void	display_map_data(MapData const map) {
	for (unsigned long i = 0; i < map.size(); i++)
	{
		for (unsigned long j = 0; j < map[i].size(); j++)
			std::cout << map[i][j] << "\t";
		std::cout << "\n";
	}
}

void	display_map_line(MapLine const map)
{
	for (unsigned long i = 0; i < map.size(); i++)
		std::cout << map[i] << "\t";
	std::cout << "\n";
}
