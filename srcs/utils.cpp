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

bool isFlagSet(const int num, const int bit) {
	return (num & bit);
}

int setFlag(const int num, const int bit) {
	return (num | bit);
}
