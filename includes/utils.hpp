#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>

void	ft_exit(const std::string &msg);
bool starts_with(const std::string &str, const std::string &target);

bool isFlagSet(const int num, const int &bit);
int setFlag(const int num, const int bit);

#endif // UTILS_HPP
